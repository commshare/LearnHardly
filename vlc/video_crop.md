#


##1

- yuv420p 和 YUV420的区别 在存储格式上有区别
- yuv420p：yyyyyyyy uuuuuuuu vvvvv 
- yuv420： yuv yuv yuv


- YUV420P，Y，U，V三个分量都是平面格式，分为I420和YV12。I420格式和YV12格式的不同处在U平面和V平面的位置不同。在I420格式中，U平面紧跟在Y平面之后，然后才是V平面（即：YUV）；但YV12则是相反（即：YVU）。
- YUV420SP, Y分量平面格式，UV打包格式, 即NV12。 NV12与NV21类似，U 和 V 交错排列,不同在于UV顺序。
I420: YYYYYYYY UU VV    =>YUV420P
YV12: YYYYYYYY VV UU    =>YUV420P
NV12: YYYYYYYY UVUV     =>YUV420SP
NV21: YYYYYYYY VUVU     =>YUV420SP



##2
这个代码不好，看不懂。
```
/*像素数据存在char * 内存里，逐个复制*/
int video_crop(char* src, int src_width, int src_height,
		enum AVPixelFormat in_pix_format, char* dst, int dst_width,
		int dst_height, enum AVPixelFormat out_pix_format,
		VIDEO_CROP_TYPE crop_type, int rotate_angle) {
	if (src == NULL || dst == NULL ||
			src_width < dst_width || src_height < dst_height) {
		LOGE("invalid crop params, %d->%d : %d->%d\n",
				src_width,dst_width ,src_height , dst_height);
		return -1;
	}

	if (in_pix_format != AV_PIX_FMT_NV21  || out_pix_format != AV_PIX_FMT_YUV420P) {
		LOGE("支持 AV_PIX_FMT_NV12->AV_PIX_FMT_YUV420P 转换");
		return -1;
	}

	if (crop_type == VIDEO_CROP_TYPE_UP_LEFT) {

		if (rotate_angle == 90) {
			// Y
			int i,j;
			for (i=0; i<dst_height; i++) {  /*高度,按照行来复制*/
				for (j=0; j<dst_width; j++) {  /*只从src复制dst所需的宽度的一行数据到dst里*/
					dst[i*dst_width+j]=src[i*src_width+j];
				}
			}

			// UVUV --> UUVV  这是NV12转I420的吧
            /*找到各个数据的起始地址，到时候直接用index来复制就ok了*/
			char *src_uv = src + src_width*src_height;  /*NV12中，UV数据的起始地址*/
			char *u = dst + dst_width*dst_height; /*I420中，U分量起始地址*/
			char *v = u + dst_width*dst_height/4;  /*I420中，V分量起始地址*/
            /*从NV21的UVUV中，分别复制U和V到I420,UV分量大小是1/2*/
			for (i=0; i<dst_width*dst_height/2; i=i+2) {
                /* %取余的意思 规定在图像的一半的宽度范围内去递加，一旦超出就回到0 */
				int pos = (i/2)/(dst_width/2) * src_width + ((i/2)%(dst_width/2))*2;
                /*V U 分量各占1/4*W*H的存储空间*/
				v[i/2] = src_uv[pos];
				u[i/2] = src_uv[pos+1];
			}
		} else if (rotate_angle == -90) {
			// Y
			int i,j;
			for (i=0; i<dst_height; i++) {
				for (j=0; j<dst_width; j++) {
					dst[i*dst_width+j]=src[i*src_width+j+src_width-dst_width];
				}
			}

			// UVUV --> UUVV
			char *src_uv = src + src_width*src_height;
			char *u = dst + dst_width*dst_height;
			char *v = u + dst_width*dst_height/4;
			for (i=0; i<dst_width*dst_height/2; i=i+2) {
				int pos = (i/2)/(dst_width/2) * src_width +
						(((i/2)%(dst_width/2))+(src_width-dst_width)/2)*2;
				v[i/2] = src_uv[pos];
				u[i/2] = src_uv[pos+1];
			}
		}
		LOGD("src:%d*%d, dst:%d*%d\n", src_width, src_height, dst_width, dst_height);

	}else if (crop_type == VIDEO_CROP_TYPE_MIDDLE) {
		int dh, dw;
		int i,j;
		dh = (src_height-dst_height+1)/2;
		dw = (src_width-dst_width+1)/2;
		// Y
		for (i=0; i<dst_height; i++) {
			for (j=0; j<dst_width; j++) {
				dst[i*dst_width+j]=src[(i+dh)*src_width+j+dw];
			}
		}

		// UVUV --> UUVV
		char *src_uv = src + src_width*src_height;
		char *u = dst + dst_width*dst_height;
		char *v = u + dst_width*dst_height/4;
		for (i=0; i<dst_width*dst_height/2; i=i+2) {
			int pos = (dh/2 + (i/2)/(dst_width/2)) * src_width + (dw/2 + (i/2)%(dst_width/2))*2;
			v[i/2] = src_uv[pos];
			u[i/2] = src_uv[pos+1];
		}
		LOGD("src:%d*%d, dst:%d*%d, dw:%d, dh:%d\n", src_width, src_height,
				dst_width, dst_height, dw, dh);
	} else {
		LOGE("crop type not support\n");
		return -1;
	}
	return 0;
}
```




##3


[FFmpegAdapter/android/FFmpegAdapter/jni/ffmpeg_adapter_crop.h](https://github.com/chloette/FFmpegAdapter/blob/master/android/FFmpegAdapter/jni/ffmpeg_adapter_crop.h)
```
/*
 *  It seems that you are not a coder if DO NOT start with Copyrights.
 *  What's wrong with you guys ? 
 *
 *  -- E
 */

#ifndef __INCLUDE_FFMPEG_ADAPTER_CROP_H__
#define __INCLUDE_FFMPEG_ADAPTER_CROP_H__

#include "ffmpeg_adapter_common.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

  //TODO to support Height crop

  //Y means Y of YUV
  //y means y of x & y
  inline static int YUV420P_crop(uint8_t* src, uint8_t* dst, int src_width, int src_height, int dst_x, int dst_y, int dst_width, int dst_height) {
    int src_Y_size = src_width * src_height;
    int dst_Y_size = dst_width * dst_height;
    int offset_Y_x = dst_x;  /*水平偏移*/
    int offset_Y_y = dst_y;
    int offset_uv_x = (dst_x >> 1);  /*水平偏移量是Y的1/2*/
    int offset_uv_y = (dst_y >> 1);
    int src_uv_width = (src_width >> 1);  /*U或者V的的宽/高度也是Y宽/高度的1/2*/
    int src_uv_height = (src_height >> 1);
    int dst_uv_width = (dst_width >> 1);
    int dst_uv_height = (dst_height >> 1);
    int index = 0;

    uint8_t* src_cb = src + src_Y_size;
    uint8_t* src_cr = src + src_Y_size + (src_Y_size >> 2); // (Y * 5 / 4)   /*U大小是Y大小的1/4，所以V的内存地址偏移就是Y+Y/4（右移两位）即Y*5/4*/
    uint8_t* dst_cb = dst + dst_Y_size;
    uint8_t* dst_cr = dst + dst_Y_size + (dst_Y_size >> 2); // (Y * 5 / 4)

    for (index = 0; index < src_height; index++) {
      //Y
      memcpy(dst + dst_width * index,
        src + src_width * index + offset_Y_x,
        dst_width);
    }

    for (index = 0; index < src_uv_height; index++) {
      //Cb
      memcpy(dst_cb + dst_uv_width * index,
        src_cb + src_uv_width * index + offset_uv_x,
        dst_uv_width);

      //Cr
      memcpy(dst_cr + dst_uv_width * index,
        src_cr + src_uv_width * index + offset_uv_x,
        dst_uv_width);
    }

    return 0;
  }

  inline static int YUV420SP_crop(uint8_t* src, uint8_t* dst, int src_width, int src_height, int dst_x, int dst_y, int dst_width, int dst_height) {
    int src_Y_size = src_width * src_height;
    int dst_Y_size = dst_width * dst_height;
    int offset_Y_x = dst_x;
    int offset_Y_y = dst_y;
    int offset_uv_x = (dst_x);
    int offset_uv_y = (dst_y >> 1);
    int src_uv_width = (src_width);
    int src_uv_height = (src_height >> 1);
    int dst_uv_width = (dst_width);
    int dst_uv_height = (dst_height >> 1);
    int index = 0;

    uint8_t* src_cbcr = src + src_Y_size;
    uint8_t* dst_cbcr = dst + dst_Y_size;

    for (index = 0; index < src_height; index++) {
      //Y
      memcpy(dst + dst_width * index,
        src + src_width * index + offset_Y_x,
        dst_width);
    }

    for (index = 0; index < src_uv_height; index++) {
      //CbCr
      memcpy(dst_cbcr + dst_uv_width * index,
        src_cbcr + src_uv_width * index + offset_uv_x,
        dst_uv_width);
    }

    return 0;
  }

#if defined(__cplusplus) || defined(c_plusplus)
}    // extern "C"
#endif

#endif  // __INCLUDE_FFMPEG_ADAPTER_CROP_H__
```


##java层做的crop

[Step 5 - Video cropping](http://blog.lemberg.co.uk/surface-view-video-cropping) (http://www.edumobile.org/android/video-cropping-example/)
[] (https://github.com/dmytrodanylyk/dmytrodanylyk/blob/gh-pages/articles/surface-view-video-cropping.md)
[android视频适配与裁剪] (https://my.oschina.net/u/1403288/blog/634051)

[crop窗口+美颜] (https://github.com/985557461/QuadrilateralCropImage)