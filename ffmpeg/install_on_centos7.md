
#

##1  centos7可以直接编译安装的脚本
- [https://github.com/jnaqsh/ffmpeg_installer]
- 可以卸载
- root账户默认安装在/root/ffmpeg_build 和 /root/bin/

##2

###2.1  配置环境

``
#!/bin/sh
X264HOME=/home/zhangbin/xlive/ffmpeg
X264DST=/root/ffmpeg_build
#$X264HOME/out/x86
#X264BUILD=$X264HOME/x264build

echo "#######################"
echo "HOME IS  $X264HOME"
echo "DST is $X264DST"
echo "BUILD is $X264BUILD"
echo "#######################"


echo "##########SETENV FOR DEP yasm######"
export PATH=$X264DST/bin:$PATH
export LD_LIBRARY_PATH=$X264DST/lib:$LD_LIBRARY_PATH
export PKG_CONFIG_PATH=$X264DST/lib/pkgconfig:$PKG_CONFIG_PATH
export C_INCLUDE_PATH=$X264DST/include:$C_INCLUDE_PATH
export LIBRARY_PATH=$X264DST/lib:$LIBRARY_PATH



echo "PATH IS $PATH"
echo "LD_LIBRARY_PATH IS $LD_LIBRARY_PATH"
echo "C_INCLUDE_PATH IS $C_INCLUDE_PATH "
echo "LIBRARY_PATH IS $LIBRARY_PATH "
echo "##########dep  done##########"



``

###2.2

- 这些库是有顺序的
- avformat依赖于 avcodec，所以avcodec放在后面

``
gcc -o getyuv getYUV.c -L /root/ffmpeg_build/lib  -lavformat -lavcodec -lavutil -I /root/ffmpeg_build/include/ -lm -ldl -lpthread -lvorbis -logg -lz -lswscale -lopus -lswresample  -lx264 -lvpx -lvorbisenc -lfdk-aac -lmp3lame -lavfilter -lpostproc
``


##3  编译获取yuv的程序 
- 因为版本比较新，是直接git下载的，所以代码有些地方不兼容，直接修改了。
- git-2017-03-25-a044f8d

``
#include <stdio.h>

//#define __STDC_CONSTANT_MACROS

//extern "C"
//{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
//#include <libavutil/frame.h>
//};

 ///#define PIX_FMT_YUV420p  AV_PIX_FMT_YUV420P
#if LIBAVCODEC_VERSION_INT >= AV_VERSION_INT(55,28,1)
#define   avcodec_alloc_frame av_frame_alloc
#endif
int main(int argc, char* argv[])
{
    AVFormatContext *pFormatCtx;
    int             i, videoindex,audioindex;
    AVCodecContext  *pCodecCtx,*iaCodecCtx;
    AVCodec         *pCodec,*iaCodec;
    AVFrame *pFrame,*pFrameYUV,*aFrame;
    uint8_t *out_buffer,*buffer;
    AVPacket *packet;
    int y_size;
    int ret, got_picture;
    struct SwsContext *img_convert_ctx;
    //输入文件路径
    char filepath[]="Titanic.ts";

    int frame_cnt = 0;

    av_register_all();
    //avformat_network_init();
    pFormatCtx = avformat_alloc_context();

    if(avformat_open_input(&pFormatCtx,filepath,NULL,NULL)!=0){
        printf("Couldn't open input stream.\n");
        return -1;
    }
    if(avformat_find_stream_info(pFormatCtx,NULL)<0){
        printf("Couldn't find stream information.\n");
        return -1;
    }
    videoindex=-1;
    audioindex = -1;
    for (i = 0; i < pFormatCtx->nb_streams; i++){
        if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO){
            videoindex=i;
            break;
        }
    }

    for (i = 0; i < pFormatCtx->nb_streams; i++){
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO){
            audioindex = i;
            break;
        }
    }

    if(videoindex==-1){
        printf("Didn't find a video stream.\n");
        return -1;
    }
    if (audioindex == -1){
        printf("Didn't find a audio stream.\n");
        return -1;
    }

    pCodecCtx=pFormatCtx->streams[videoindex]->codec;
    pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
    if(pCodec==NULL){
        printf("Codec not found.\n");
        return -1;
    }
    if(avcodec_open2(pCodecCtx, pCodec,NULL)<0){
        printf("Could not open codec.\n");
        return -1;
    }

    //audio
    iaCodecCtx = pFormatCtx->streams[audioindex]->codec;
    iaCodec = avcodec_find_decoder(iaCodecCtx->codec_id);
    if (iaCodec == NULL){
        printf("Codec not found.\n");
        return -1;
    }
    if (avcodec_open2(iaCodecCtx, iaCodec, NULL)<0){
        printf("Could not open codec.\n");
        return -1;
    }

    /*
     * 在此处添加输出视频信息的代码
     * 取自于pFormatCtx，使用fprintf()
     */
    pFrame=av_frame_alloc();
    pFrameYUV=av_frame_alloc();

    out_buffer = (uint8_t *)av_malloc(avpicture_get_size(AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height));
    avpicture_fill((AVPicture *)pFrameYUV, out_buffer, AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height);
    packet=(AVPacket *)av_malloc(sizeof(AVPacket));
    //Output Info-----------------------------
    printf("--------------- File Information ----------------\n");
    av_dump_format(pFormatCtx,0,filepath,0);
    printf("-------------------------------------------------\n");
    img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, 
        pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);


    //audio
    buffer = (uint8_t*)malloc(1024);
    aFrame = avcodec_alloc_frame();
    int len = 0;
    int pktsize = 0;
    uint8_t * pktdata;
    //读入YUV以及PCM文件,并以指针的形式存储

    FILE *PYUV = fopen("testVideo.yuv","wb+");
    FILE *PCM = fopen("testAudio.pcm", "wb+");

    frame_cnt=0;
    while(av_read_frame(pFormatCtx, packet)>=0){
        if(packet->stream_index==videoindex){
                /*
                 * 在此处添加输出H264码流的代码
                 * 取自于packet，使用fwrite()
                 */
            ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
            if(ret < 0){
                printf("Decode Error.\n");
                return -1;
            }                                                          
            if(got_picture){
                sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height, 
                    pFrameYUV->data, pFrameYUV->linesize);
                printf("Decoded frame index: %d\n",frame_cnt);

                /*
                 * 在此处添加输出YUV的代码
                 * 取自于pFrameYUV，使用fwrite()
                 */

                //write YUV
                y_size = pCodecCtx->width*pCodecCtx->height;
                fwrite(pFrameYUV->data[0], 1, y_size, PYUV);
                fwrite(pFrameYUV->data[1], 1, y_size / 4, PYUV);
                fwrite(pFrameYUV->data[2], 1, y_size / 4, PYUV);
                frame_cnt++;
            }
        }

        //找到音频流
        if (packet->stream_index == audioindex){
            while (packet->size>0)
            {
                int size;
                len = avcodec_decode_audio4(iaCodecCtx, aFrame, &size, packet);
                if (len < 0){
                    pktsize = 0;
                    printf("Error while decoding\n");
                    continue;
                }
                if (size){
                    int data_size = av_samples_get_buffer_size(NULL, iaCodecCtx->channels, 
                        aFrame->nb_samples, iaCodecCtx->sample_fmt, 1);
                    fwrite(aFrame->data[0], 1, aFrame->linesize[0], PCM);
                }
                packet->size -= len;
                packet->data += len;
            }
        }
        av_free_packet(packet);
    } 
    //**这里输出视频宽度和高度信息**
    printf("width : %d\n",pCodecCtx->width);
    printf("height : %d\n", pCodecCtx->height);

    sws_freeContext(img_convert_ctx);

    fclose(PYUV);
    fclose(PCM);

    //audio
    av_frame_free(&aFrame);
    avcodec_close(iaCodecCtx);

    av_frame_free(&pFrameYUV);
    av_frame_free(&pFrame);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);

    getchar();
    return 0;
}
``