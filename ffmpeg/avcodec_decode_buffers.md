# VLC使用了avcodec的get_buffer2机制

##1
> [回调函数getbuffer2](http://stackoverflow.com/questions/28339980/ffmpeg-while-decoding-video-is-possible-to-generate-result-to-users-provided)
- 调用avcodec_decode_video2 时，getbuffer2会被回调。
-  this callback function is responsible to delegate buffers and some informations to AVFrame, then avcodec_decode_video2 generate the result to the buffers of AVFrame.
- 这说明内存的处理、相关信息的添加是在getbuffer2这回调函数里搞的。

###1.1

> avcodec默认的回调函数
```
int avcodec_default_get_buffer2(AVCodecContext *avctx, AVFrame *frame, int flags)
{
    int ret;

    if ((ret = update_frame_pool(avctx, frame)) < 0)
        return ret;

#if FF_API_GET_BUFFER
FF_DISABLE_DEPRECATION_WARNINGS
    frame->type = FF_BUFFER_TYPE_INTERNAL;
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    switch (avctx->codec_type) {
    case AVMEDIA_TYPE_VIDEO:
        return video_get_buffer(avctx, frame);
    case AVMEDIA_TYPE_AUDIO:
        return audio_get_buffer(avctx, frame);
    default:
        return -1;
    }
}
```

```
static int video_get_buffer(AVCodecContext *s, AVFrame *pic)
{
    FramePool *pool = s->internal->pool;
    int i;

    if (pic->data[0]) {
        av_log(s, AV_LOG_ERROR, "pic->data[0]!=NULL in avcodec_default_get_buffer\n");
        return -1;
    }

    memset(pic->data, 0, sizeof(pic->data));
    pic->extended_data = pic->data;

    for (i = 0; i < 4 && pool->pools[i]; i++) {
        pic->linesize[i] = pool->linesize[i];

        pic->buf[i] = av_buffer_pool_get(pool->pools[i]);
        if (!pic->buf[i])
            goto fail;

        pic->data[i] = pic->buf[i]->data;
    }
    for (; i < AV_NUM_DATA_POINTERS; i++) {
        pic->data[i] = NULL;
        pic->linesize[i] = 0;
    }
    if (pic->data[1] && !pic->data[2])
        avpriv_set_systematic_pal2((uint32_t *)pic->data[1], s->pix_fmt);

    if (s->debug & FF_DEBUG_BUFFERS)
        av_log(s, AV_LOG_DEBUG, "default_get_buffer called on pic %p\n", pic);

    return 0;
fail:
    av_frame_unref(pic);
    return AVERROR(ENOMEM);
}
```

###1.2

> 可以这么添加自己的回调函数实现
```
void our_buffer_default_free(void *opaque, uint8_t *data)
{
    // empty
}
int our_get_buffer(struct AVCodecContext *c, AVFrame *pic, int flags)
{
    assert(c->codec_type == AVMEDIA_TYPE_VIDEO);
    /*AVFrame的data赋值*/
    pic->data[0] = lrY.pBits;
    pic->data[1] = lrU.pBits;
    pic->data[2] = lrV.pBits;
    /**/
    picture->linesize[0] = lrY.Pitch;
    picture->linesize[1] = lrU.Pitch;
    picture->linesize[2] = lrV.Pitch;
    pic->buf[0] = av_buffer_create(pic->data[0], pic->linesize[0] * pic->height, our_buffer_default_free, NULL, 0);
    pic->buf[1] = av_buffer_create(pic->data[1], pic->linesize[1] * pic->height / 2, our_buffer_default_free, NULL, 0);
    pic->buf[2] = av_buffer_create(pic->data[2], pic->linesize[2] * pic->height / 2, our_buffer_default_free, NULL, 0);
    return 0;
}
```

###1.3 最关键是alignment

- 注意性能是收到CODEC要求的对齐的影响的	。
- 对于这个buffer，以及每个行（通过strides），要求最少要128个位，也就是16个字节的对齐
- 如果和你的输出不兼容， 你对齐了会更快。
 ``` 	 	
Note that performance will suffer if you don't meet the alignment expectations of the CODEC. If it's compatible with your output device, I would ensure at least 128b alignment of the buffer and each row (via strides). If that is not compatible with your output it may be faster to do the copy as you originally had it. – Ben Jackson Feb 6 '15 at 7:00

```



##2 
> 参考 [vlc使用ffmepg get_buffer2流程] (https://my.oschina.net/yagerfgcs/blog/701030)

```
解码前可以new出内存=解码对象Length+YUV占用数据空间+ffmepg解码所需的padding空间。一次申请这样一块连续内存，配合下面详细流程中偏移到YUV地址，将Y\U\V三个picth指针地址记录后交由ffmpeg解码，解码后将解码参数赋值到解码对象中
```


```
三、详细流程
1   modules\codec\avcodec\video.c           InitVideoDec    get_buffer2 = lavc_GetFrame;  函数指针

2   modules\codec\avcodec\video.c           lavc_GetFrame  
3   modules\codec\avcodec\video.c           lavc_dr_GetFrame   直接渲染
4   modules\codec\avcodec\video.c           ffmpeg_NewPictBuf   从vout模块获取分配的picture_t的内存
5   src\input\decoder.c                     decoder_NewPicture 从vout模块获取分配的picture_t的内存
6   src\input\decoder.c                     vout_new_buffer 
7   if (p_owner->p_vout == NULL) goto 8 else goto 13 
8       src\input\resource.c                if (p_owner->p_vout == NULL) input_resource_RequestVout  请求vout资源
9       src\input\resource.c                RequestVout 
10      src\video_output\video_output.c     VoutCreate   创建vout对象
11      src\video_output\video_output.c     vlc_clone(&vout->p->thread, Thread, vout, VLC_THREAD_PRIORITY_OUTPUT) 创建线程 goto 15   
12      src\video_output\video_output.c     vout_control_WaitEmpty(&vout->p->control); 等待线程创建picture_pool完毕 goto 13 
     
13  src\video_output\video_output.c         vout_GetPicture 这是准备从picture_pool里获取内存
14  src\misc\picture_pool.c                 picture_pool_Get 从picture_pool取出一帧pciture_t 


15  src\video_output\video_output.c         Thread  线程创建
16  src\video_output\video_output.c         ThreadControl 
17  src\video_output\video_output.c         ThreadStart 

18  src\video_output\vout_wrapper.c         vout_OpenWrapper goto 24 

19  src\video_output\vout_wrapper.c         vout_InitWrapper 
20  src\misc\picture_pool.c                 picture_pool_NewFromFormat 
21  src\misc\picture_pool.c                 picture_pool_New 创建picturepool 
22  src\misc\picture.c                      33次picture_NewFromFormat 
23  src\misc\picture.c                      picture_NewFromResource     return 11 to 12 

24  src\video_output\display.c              vout_NewDisplay 
25  src\video_output\display.c              DisplayNew 
26  src\video_output\display.c              vout_display_New 
27  src\modules\modules.c                   module_need 
28  src\modules\modules.c                   vlc_module_load 
29  modules\video_output\msw\direct3d.c     Open 
30  modules\video_output\msw\direct3d.c     Direct3DOpen 
31  modules\video_output\msw\direct3d.c     Direct3DCreateResources 
32  modules\video_output\msw\direct3d.c     Direct3DCreatePool 
33  src\misc\picture.c                      picture_NewFromResource     return 18 to 19 

```



##3 

- [webrtc的实现] (https://github.com/lancerajee/webrtc/blob/ce302b82c919182887784eff6e6aca7716c6c9c1/webrtc/modules/video_coding/codecs/h264/h264_decoder_impl.cc)

```
/*
 *  Copyright (c) 2015 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 *
 */

#include "webrtc/modules/video_coding/codecs/h264/h264_decoder_impl.h"

#include <algorithm>
#include <limits>

extern "C" {
#include "third_party/ffmpeg/libavcodec/avcodec.h"
#include "third_party/ffmpeg/libavformat/avformat.h"
#include "third_party/ffmpeg/libavutil/imgutils.h"
}  // extern "C"

#include "webrtc/api/video/i420_buffer.h"
#include "webrtc/base/checks.h"
#include "webrtc/base/criticalsection.h"
#include "webrtc/base/keep_ref_until_done.h"
#include "webrtc/base/logging.h"
#include "webrtc/common_video/include/video_frame_buffer.h"
#include "webrtc/system_wrappers/include/metrics.h"

namespace webrtc {

namespace {

const AVPixelFormat kPixelFormat = AV_PIX_FMT_YUV420P;
const size_t kYPlaneIndex = 0;
const size_t kUPlaneIndex = 1;
const size_t kVPlaneIndex = 2;

// Used by histograms. Values of entries should not be changed.
enum H264DecoderImplEvent {
  kH264DecoderEventInit = 0,
  kH264DecoderEventError = 1,
  kH264DecoderEventMax = 16,
};

#if defined(WEBRTC_INITIALIZE_FFMPEG)

rtc::CriticalSection ffmpeg_init_lock;
bool ffmpeg_initialized = false;

// Called by FFmpeg to do mutex operations if initialized using
// |InitializeFFmpeg|.
int LockManagerOperation(void** lock, AVLockOp op)
    EXCLUSIVE_LOCK_FUNCTION() UNLOCK_FUNCTION() {
  switch (op) {
    case AV_LOCK_CREATE:
      *lock = new rtc::CriticalSection();
      return 0;
    case AV_LOCK_OBTAIN:
      static_cast<rtc::CriticalSection*>(*lock)->Enter();
      return 0;
    case AV_LOCK_RELEASE:
      static_cast<rtc::CriticalSection*>(*lock)->Leave();
      return 0;
    case AV_LOCK_DESTROY:
      delete static_cast<rtc::CriticalSection*>(*lock);
      *lock = nullptr;
      return 0;
  }
  RTC_NOTREACHED() << "Unrecognized AVLockOp.";
  return -1;
}

void InitializeFFmpeg() {
  rtc::CritScope cs(&ffmpeg_init_lock);
  if (!ffmpeg_initialized) {
    if (av_lockmgr_register(LockManagerOperation) < 0) {
      RTC_NOTREACHED() << "av_lockmgr_register failed.";
      return;
    }
    av_register_all();
    ffmpeg_initialized = true;
  }
}

#endif  // defined(WEBRTC_INITIALIZE_FFMPEG)

}  // namespace

/*======他们是在这里实现的=============*/
int H264DecoderImpl::AVGetBuffer2(
    AVCodecContext* context, AVFrame* av_frame, int flags) {
  // Set in |InitDecode|.
  H264DecoderImpl* decoder = static_cast<H264DecoderImpl*>(context->opaque);
  // DCHECK values set in |InitDecode|.
  RTC_DCHECK(decoder);
  RTC_DCHECK_EQ(context->pix_fmt, kPixelFormat);
  // Necessary capability to be allowed to provide our own buffers.  必需设置这个，才能允许使用我们自己的提供的buffer
  RTC_DCHECK(context->codec->capabilities | AV_CODEC_CAP_DR1);

  // |av_frame->width| and |av_frame->height| are set by FFmpeg. These are the
  // actual image's dimensions and may be different from |context->width| and
  // |context->coded_width| due to reordering.   av_frame的宽度高度是ffmpeg设置的，这俩值是实际的图像的分辨率，可能跟content的宽度高度不一样，这是因为有可能被重新排序了。
  int width = av_frame->width;
  int height = av_frame->height;
  // See |lowres|, if used the decoder scales the image by 1/2^(lowres). This 如果使用了解码器来对图像做缩放
  // has implications on which resolutions are valid, but we don't use it.
  RTC_CHECK_EQ(context->lowres, 0);
  // Adjust the |width| and |height| to values acceptable by the decoder. 根据解码器的需要来做宽度和高度值的调整。如果不做这个操作，ffmpeg可能会覆盖这个buffer。
  // Without this, FFmpeg may overflow the buffer. If modified, |width| and/or 如果修改之后，宽度或者高度，比实际的图像要大，那么解码后，就得对图像（左上角）做裁剪，
  // |height| are larger than the actual image and the image has to be cropped  以避免在实际图像的右下方出现可见的边缘。
  // (top-left corner) after decoding to avoid visible borders to the right and
  // bottom of the actual image.
  avcodec_align_dimensions(context, &width, &height);

  RTC_CHECK_GE(width, 0);
  RTC_CHECK_GE(height, 0);
  int ret = av_image_check_size(static_cast<unsigned int>(width),
                                static_cast<unsigned int>(height), 0, nullptr);
  if (ret < 0) {
    LOG(LS_ERROR) << "Invalid picture size " << width << "x" << height;
    decoder->ReportError();
    return ret;
  }

  // The video frame is stored in |frame_buffer|. |av_frame| is FFmpeg's version
  // of a video frame and will be set up to reference |frame_buffer|'s data.

  // FFmpeg expects the initial allocation to be zero-initialized according to
  // http://crbug.com/390941. Our pool is set up to zero-initialize new buffers.
  // TODO(nisse): Delete that feature from the video pool, instead add
  // an explicit call to InitializeData here.
  rtc::scoped_refptr<I420Buffer> frame_buffer =  /*webrtc的视频帧是存在这个frame_buffer的，av_frame是ffmpeg的视频帧版本，需要引用到frame_buffer的data*/
      decoder->pool_.CreateBuffer(width, height);

  int y_size = width * height; /*Y分量的大小*/
  int uv_size = ((width + 1) / 2) * ((height + 1) / 2);   /*UV分量的大小*/
  // DCHECK that we have a continuous buffer as is required.   检查我们是不是以后所需的连续的内存
  RTC_DCHECK_EQ(frame_buffer->DataU(), frame_buffer->DataY() + y_size);  /*检查U分量空间够不够*/
  RTC_DCHECK_EQ(frame_buffer->DataV(), frame_buffer->DataU() + uv_size);  /*检查V分量空间够不够*/
  int total_size = y_size + 2 * uv_size;    /*视频内存的总大小*/

  av_frame->format = context->pix_fmt;
  av_frame->reordered_opaque = context->reordered_opaque;  /*PTS相关的，用户设置，TODO */

  // Set |av_frame| members as required by FFmpeg. 这是把数据从frame_buffer导入到AVFrame版本
  av_frame->data[kYPlaneIndex] = frame_buffer->MutableDataY();  /*Y分量*/
  av_frame->linesize[kYPlaneIndex] = frame_buffer->StrideY();
  av_frame->data[kUPlaneIndex] = frame_buffer->MutableDataU();  /*u分量*/
  av_frame->linesize[kUPlaneIndex] = frame_buffer->StrideU();
  av_frame->data[kVPlaneIndex] = frame_buffer->MutableDataV(); /*v分量*/
  av_frame->linesize[kVPlaneIndex] = frame_buffer->StrideV();
  RTC_DCHECK_EQ(av_frame->extended_data, av_frame->data);   /*pointers to the data planes/channels. 这个值要被设置，指向的就是AVFrame的data[]*/

  // Create a VideoFrame object, to keep a reference to the buffer.  传递了一个new出来的VideoFrame对象，用来保持对这个buffer的引用。
  // TODO(nisse): The VideoFrame's timestamp and rotation info is not used.
  // Refactor to do not use a VideoFrame object at all.
  av_frame->buf[0] = av_buffer_create(
      av_frame->data[kYPlaneIndex],
      total_size,  /*直接把整个yuv大小都弄来了*/
      AVFreeBuffer2,
      static_cast<void*>(new VideoFrame(frame_buffer,
                                        0 /* timestamp */,
                                        0 /* render_time_ms */,
                                        kVideoRotation_0)),
      0);
  RTC_CHECK(av_frame->buf[0]);
  return 0;
}

void H264DecoderImpl::AVFreeBuffer2(void* opaque, uint8_t* data) {
  // The buffer pool recycles the buffer used by |video_frame| when there are no
  // more references to it. |video_frame| is a thin buffer holder and is not
  // recycled.
  VideoFrame* video_frame = static_cast<VideoFrame*>(opaque);
  delete video_frame;
}

H264DecoderImpl::H264DecoderImpl() : pool_(true),
                                     decoded_image_callback_(nullptr),
                                     has_reported_init_(false),
                                     has_reported_error_(false) {
}

H264DecoderImpl::~H264DecoderImpl() {
  Release();
}

int32_t H264DecoderImpl::InitDecode(const VideoCodec* codec_settings,
                                    int32_t number_of_cores) {
  ReportInit();
  if (codec_settings &&
      codec_settings->codecType != kVideoCodecH264) {
    ReportError();
    return WEBRTC_VIDEO_CODEC_ERR_PARAMETER;
  }

  // FFmpeg must have been initialized (with |av_lockmgr_register| and
  // |av_register_all|) before we proceed. |InitializeFFmpeg| does this, which
  // makes sense for WebRTC standalone. In other cases, such as Chromium, FFmpeg
  // is initialized externally and calling |InitializeFFmpeg| would be
  // thread-unsafe and result in FFmpeg being initialized twice, which could
  // break other FFmpeg usage. See the |rtc_initialize_ffmpeg| flag.
#if defined(WEBRTC_INITIALIZE_FFMPEG)
  // Make sure FFmpeg has been initialized. Subsequent |InitializeFFmpeg| calls
  // do nothing.
  InitializeFFmpeg();
#endif

  // Release necessary in case of re-initializing.
  int32_t ret = Release();
  if (ret != WEBRTC_VIDEO_CODEC_OK) {
    ReportError();
    return ret;
  }
  RTC_DCHECK(!av_context_);

  // Initialize AVCodecContext.
  av_context_.reset(avcodec_alloc_context3(nullptr));

  av_context_->codec_type = AVMEDIA_TYPE_VIDEO;
  av_context_->codec_id = AV_CODEC_ID_H264;
  if (codec_settings) {
    av_context_->coded_width = codec_settings->width;
    av_context_->coded_height = codec_settings->height;
  }
  av_context_->pix_fmt = kPixelFormat;
  av_context_->extradata = nullptr;
  av_context_->extradata_size = 0;

  // If this is ever increased, look at |av_context_->thread_safe_callbacks| and
  // make it possible to disable the thread checker in the frame buffer pool.
  av_context_->thread_count = 1;
  av_context_->thread_type = FF_THREAD_SLICE;

  // Function used by FFmpeg to get buffers to store decoded frames in. FFmpeg用这个函数来获取内存，以存储解码后的frame
  av_context_->get_buffer2 = AVGetBuffer2;  
  // |get_buffer2| is called with the context, there |opaque| can be used to get
  // a pointer |this|.
  av_context_->opaque = this;
  // Use ref counted frames (av_frame_unref).
  av_context_->refcounted_frames = 1;  // true

  AVCodec* codec = avcodec_find_decoder(av_context_->codec_id);
  if (!codec) {
    // This is an indication that FFmpeg has not been initialized or it has not
    // been compiled/initialized with the correct set of codecs.
    LOG(LS_ERROR) << "FFmpeg H.264 decoder not found.";
    Release();
    ReportError();
    return WEBRTC_VIDEO_CODEC_ERROR;
  }
  int res = avcodec_open2(av_context_.get(), codec, nullptr);
  if (res < 0) {
    LOG(LS_ERROR) << "avcodec_open2 error: " << res;
    Release();
    ReportError();
    return WEBRTC_VIDEO_CODEC_ERROR;
  }

  av_frame_.reset(av_frame_alloc());
  return WEBRTC_VIDEO_CODEC_OK;
}

int32_t H264DecoderImpl::Release() {
  av_context_.reset();
  av_frame_.reset();
  return WEBRTC_VIDEO_CODEC_OK;
}

int32_t H264DecoderImpl::RegisterDecodeCompleteCallback(
    DecodedImageCallback* callback) {
  decoded_image_callback_ = callback;
  return WEBRTC_VIDEO_CODEC_OK;
}

int32_t H264DecoderImpl::Decode(const EncodedImage& input_image,
                                bool /*missing_frames*/,
                                const RTPFragmentationHeader* /*fragmentation*/,
                                const CodecSpecificInfo* codec_specific_info,
                                int64_t /*render_time_ms*/) {
  if (!IsInitialized()) {
    ReportError();
    return WEBRTC_VIDEO_CODEC_UNINITIALIZED;
  }
  if (!decoded_image_callback_) {
    LOG(LS_WARNING) << "InitDecode() has been called, but a callback function "
        "has not been set with RegisterDecodeCompleteCallback()";
    ReportError();
    return WEBRTC_VIDEO_CODEC_UNINITIALIZED;
  }
  if (!input_image._buffer || !input_image._length) {
    ReportError();
    return WEBRTC_VIDEO_CODEC_ERR_PARAMETER;
  }
  if (codec_specific_info &&
      codec_specific_info->codecType != kVideoCodecH264) {
    ReportError();
    return WEBRTC_VIDEO_CODEC_ERR_PARAMETER;
  }

  // FFmpeg requires padding due to some optimized bitstream readers reading 32
  // or 64 bits at once and could read over the end. See avcodec_decode_video2.
  RTC_CHECK_GE(input_image._size, input_image._length +
                   EncodedImage::GetBufferPaddingBytes(kVideoCodecH264));
  // "If the first 23 bits of the additional bytes are not 0, then damaged MPEG
  // bitstreams could cause overread and segfault." See
  // AV_INPUT_BUFFER_PADDING_SIZE. We'll zero the entire padding just in case.
  memset(input_image._buffer + input_image._length,
         0,
         EncodedImage::GetBufferPaddingBytes(kVideoCodecH264));

  AVPacket packet;
  av_init_packet(&packet);
  packet.data = input_image._buffer;
  if (input_image._length >
      static_cast<size_t>(std::numeric_limits<int>::max())) {
    ReportError();
    return WEBRTC_VIDEO_CODEC_ERROR;
  }
  packet.size = static_cast<int>(input_image._length);
  av_context_->reordered_opaque = input_image.ntp_time_ms_ * 1000;  // ms -> μs

  int frame_decoded = 0;
  int result = avcodec_decode_video2(av_context_.get(),
                                     av_frame_.get(),
                                     &frame_decoded,
                                     &packet);
  if (result < 0) {
    LOG(LS_ERROR) << "avcodec_decode_video2 error: " << result;
    ReportError();
    return WEBRTC_VIDEO_CODEC_ERROR;
  }
  // |result| is number of bytes used, which should be all of them.
  if (result != packet.size) {
    LOG(LS_ERROR) << "avcodec_decode_video2 consumed " << result << " bytes "
        "when " << packet.size << " bytes were expected.";
    ReportError();
    return WEBRTC_VIDEO_CODEC_ERROR;
  }

  if (!frame_decoded) {
    LOG(LS_WARNING) << "avcodec_decode_video2 successful but no frame was "
        "decoded.";
    return WEBRTC_VIDEO_CODEC_OK;
  }

  // Obtain the |video_frame| containing the decoded image.
  VideoFrame* video_frame = static_cast<VideoFrame*>(
      av_buffer_get_opaque(av_frame_->buf[0]));
  RTC_DCHECK(video_frame);
  RTC_CHECK_EQ(av_frame_->data[kYPlaneIndex],
               video_frame->video_frame_buffer()->DataY());
  RTC_CHECK_EQ(av_frame_->data[kUPlaneIndex],
               video_frame->video_frame_buffer()->DataU());
  RTC_CHECK_EQ(av_frame_->data[kVPlaneIndex],
               video_frame->video_frame_buffer()->DataV());
  video_frame->set_timestamp(input_image._timeStamp);

  rtc::Optional<uint8_t> qp;
  // TODO(sakal): Maybe it is possible to get QP directly from FFmpeg.
  h264_bitstream_parser_.ParseBitstream(input_image._buffer,
                                        input_image._length);
  int qp_int;
  if (h264_bitstream_parser_.GetLastSliceQp(&qp_int)) {
    qp.emplace(qp_int);
  }

  // The decoded image may be larger than what is supposed to be visible, see
  // |AVGetBuffer2|'s use of |avcodec_align_dimensions|. This crops the image
  // without copying the underlying buffer.
  rtc::scoped_refptr<VideoFrameBuffer> buf = video_frame->video_frame_buffer();
  if (av_frame_->width != buf->width() || av_frame_->height != buf->height()) {
    rtc::scoped_refptr<VideoFrameBuffer> cropped_buf(
        new rtc::RefCountedObject<WrappedI420Buffer>(
            av_frame_->width, av_frame_->height,
            buf->DataY(), buf->StrideY(),
            buf->DataU(), buf->StrideU(),
            buf->DataV(), buf->StrideV(),
            rtc::KeepRefUntilDone(buf)));
    VideoFrame cropped_frame(
        cropped_buf, video_frame->timestamp(), video_frame->render_time_ms(),
        video_frame->rotation());
    // TODO(nisse): Timestamp and rotation are all zero here. Change decoder
    // interface to pass a VideoFrameBuffer instead of a VideoFrame?
    decoded_image_callback_->Decoded(cropped_frame, rtc::Optional<int32_t>(),
                                     qp);
  } else {
    // Return decoded frame.
    decoded_image_callback_->Decoded(*video_frame, rtc::Optional<int32_t>(),
                                     qp);
  }
  // Stop referencing it, possibly freeing |video_frame|.
  av_frame_unref(av_frame_.get());
  video_frame = nullptr;

  return WEBRTC_VIDEO_CODEC_OK;
}

const char* H264DecoderImpl::ImplementationName() const {
  return "FFmpeg";
}

bool H264DecoderImpl::IsInitialized() const {
  return av_context_ != nullptr;
}

void H264DecoderImpl::ReportInit() {
  if (has_reported_init_)
    return;
  RTC_HISTOGRAM_ENUMERATION("WebRTC.Video.H264DecoderImpl.Event",
                            kH264DecoderEventInit,
                            kH264DecoderEventMax);
  has_reported_init_ = true;
}

void H264DecoderImpl::ReportError() {
  if (has_reported_error_)
    return;
  RTC_HISTOGRAM_ENUMERATION("WebRTC.Video.H264DecoderImpl.Event",
                            kH264DecoderEventError,
                            kH264DecoderEventMax);
  has_reported_error_ = true;
}

}  // namespace webrtc
```




##4 AVFrame里我之前没有注意到的内存分配方法


###4.1

```
    /**
     * AVBuffer references backing the data for this frame. If all elements of
     * this array are NULL, then this frame is not reference counted. This array
     * must be filled contiguously -- if buf[i] is non-NULL then buf[j] must
     * also be non-NULL for all j < i.
     *
     * There may be at most one AVBuffer per data plane, so for video this array
     * always contains all the references. For planar audio with more than
     * AV_NUM_DATA_POINTERS channels, there may be more buffers than can fit in
     * this array. Then the extra AVBufferRef pointers are stored in the
     * extended_buf array.
     */
    AVBufferRef *buf[AV_NUM_DATA_POINTERS];
```



```
/**
 * Create an AVBuffer from an existing array.
 *
 * If this function is successful, data is owned by the AVBuffer. The caller may
 * only access data through the returned AVBufferRef and references derived from
 * it.
 * If this function fails, data is left untouched.
 * @param data   data array
 * @param size   size of data in bytes
 * @param free   a callback for freeing this buffer's data
 * @param opaque parameter to be got for processing or passed to free
 * @param flags  a combination of AV_BUFFER_FLAG_*
 *
 * @return an AVBufferRef referring to data on success, NULL on failure.
 */
AVBufferRef *av_buffer_create(uint8_t *data, int size,
                              void (*free)(void *opaque, uint8_t *data),
                              void *opaque, int flags);

```



##5
> video.c
- lavc_dr_GetFrame
- lavc_GetFrame
- p_context->get_buffer2 = lavc_GetFrame;  /*走这里啊*/
- InitVideoDec


###5.1  创建解码器到创建vout过程的打印
-1 CreateDecoder  i_width=268 i_height=480
-2  avcodec decoder: avcodec: trying to use direct rendering
-3  avcodec decoder: allowing 4 thread(s) for decoding
-4 video.c_270_OpenVideoCodec]SET Visble to w and h, set w[0]h[0] to coded before ffmpeg_OpenCodec
-5   avcodec decoder: codec (h264) started
-6 es_out.c_1660_EsCreateDecoder]es is buffering :  decoder should wait ,call input_DecoderStartWait
-7 video.c_693_DecodeVideo]----1---AFTER avcodec_decode_video2 W[0] H[0] 竟然是0
-8  avcodec decoder: available software decoder output format 0 (yuv420p)
-9 video.c_1079_lavc_dr_GetFrame]--lavc_dr_GetFrame--AVFrame: w[272] h[480] begin
-10 video.c_131_ffmpeg_NewPictBuf]-1-ffmpeg_NewPictBuf-use coded : w[272] h[480]
-11 video.c_137_ffmpeg_NewPictBuf]-2-after avcodec_align_dimensions2  w[272] h[482]
-12 decoder.c_2319_dumpVideoFmt]caller[p_dec->fmt_out.video] [vout_update_format] v_w[268] v_h[480] w[272] h[482]
-13 [RequestVout] v_w[268] v_h[480] w[272] h[482]
-14 video_output.c_241_vout_Request] cfg.change_fmt=1 vout=0x0
-15 video_output.c_131_VoutCreate]VoutCreate
-16 video_output.c_83_VoutValidateFormat]CFG FMT IS SRC : i_width[272] i_height[482]
-17 video_output.c_94_VoutValidateFormat]-after video_format_Copy-ORIGINAL FMT IS DST : i_width[272] i_height[482]
-18 video_output.c_99_VoutValidateFormat]-after vlc_ureduce-ORIGINAL FMT IS DST : i_width[272] i_height[482]
-19 video_output.c_106_VoutValidateFormat]-at last， after video_format_FixRgb-ORIGINAL FMT IS DST : i_width[272] i_height[482]

-20  core scale: looking for video filter2 module matching "any": 17 candidates
-21 arm_neon/yuv_rgb.c_184_Open]enter into arm_neon YUV2RGB Open
filter->fmt_in.video.i_width [32] filter->fmt_in.video.i_height [32] 输入的宽度高度
filter->fmt_in.video.i_width [32] == filter->fmt_out.video.i_width [16] 输入宽度和输出宽度
filter->fmt_in.video.i_height [32] ==  filter->fmt_out.video.i_height [16] 输入高度vs输出高度
filter->fmt_in.video.orientation [0] ==  filter->fmt_out.video.orientation [0]
yuv_rgb.c_202_Open]yuv_rgb.c open fail

-21 video_chroma/swscale.c_319_GetParameters]---------p_fmti->i_chroma [1096176985]-p_fmto->i_chroma[1094862674]
video_chroma/swscale.c_319_GetParameters]---------p_fmti->i_chroma [1096176985]-p_fmto->i_chroma[1094862674]
video_chroma/swscale.c_423_Init]-----SWSCALE: owidth[32] oheight[16] iwidth[64] iheight[32]
swscale scale: 32x32 (32x32) chroma: YUVA -> 16x16 (16x16) chroma: RGBA with scaling using Bicubic (good quality)
core scale: using video filter2 module "swscale"

-22  core scale: looking for video filter2 module matching "any": 17 candidates
-23 arm_neon/yuv_rgb.c_184_Open]enter into arm_neon YUV2RGB Open
arm_neon/yuv_rgb.c_193_Open] filter->fmt_in.video.i_width [32] filter->fmt_in.video.i_height [32]
arm_neon/yuv_rgb.c_194_Open]filter->fmt_in.video.i_width [32] == filter->fmt_out.video.i_width [32]
arm_neon/yuv_rgb.c_195_Open]filter->fmt_in.video.i_height [32] ==  filter->fmt_out.video.i_height [32]
arm_neon/yuv_rgb.c_196_Open] filter->fmt_in.video.orientation [0] ==  filter->fmt_out.video.orientation [0]
arm_neon/yuv_rgb.c_248_Open]OPEN FAIL, UNKOWN ,filter->fmt_out.video.i_chroma[1096176985]

-24 ../../modules/video_chroma/swscale.c_319_GetParameters]---------p_fmti->i_chroma [1347835225]-p_fmto->i_chroma[1096176985]
../../modules/video_chroma/swscale.c_354_GetParameters] ---fail : i_fmti < 0 || i_fmto < 0---
video_filter/yuvp.c_66_Open]p_filter->fmt_in.video.i_chroma [1347835225] should be == VLC_CODEC_YUVP [1347835225]
video_filter/yuvp.c_67_Open] p_filter->fmt_out.video.i_chroma  [1096176985] should be  == VLC_CODEC_YUVA [1096176985]
video_filter/yuvp.c_68_Open] p_filter->fmt_in.video.i_width [32] should be == p_filter->fmt_out.video.i_width [32]
video_filter/yuvp.c_69_Open] p_filter->fmt_in.video.i_height [32] should be == p_filter->fmt_out.video.i_height [32]
video_filter/yuvp.c_72_Open] VLC_CODEC_YUVP [1347835225]  VLC_CODEC_YUVA [1096176985] VLC_CODEC_RGBA[1094862674] VLC_CODEC_ARGB[1111970369]

-25 yuvp scale: YUVP to YUVA converter
core scale: using video filter2 module "yuvp"

-26  core video output: Deinterlacing available

-27 video_output/video_output.c_1728_ThreadControl]VOUT_CONTROL_INIT
-28 video_output.c_1554_ThreadStart]ThreadStart----------BEGIN---
-29 video_output.c_713_VoutGetDisplayCfg]VoutGetDisplayCfg cfg  is_fullscreen=0      display[title=(null) width=0 height=0 num=1 den=1]      align[horizontal=0 vertical=0]    is_display_filled=1    zoom[num=1 den=1] isscale=73

-30 core video output: Opening vout display wrapper
DisplayNew. : video_format_t : i_chroma=30323449 name=Planar 4:2:0 YUV i_width=272 i_height=482 i_x_offset=0 i_y_offset=0 i_visible_width=268                            i_visible_height=480 i_bits_per_pixel=0 i_sar_num=1 i_sar_den=1 i_frame_rate=10 i_frame_rate_base=1 orientation=0

-31 video_output/display.c_1447_DisplayNew]DisplayNew cfg display_width=268 display_height=480 zoom.num=1 osys->zoom.den=1
-32 video_output/display.c_92_vout_display_New]vout_display_New cfg  is_fullscreen=0                  display[title=(null) width=268 height=480 num=1 den=1] align[horizontal=0 vertical=0] is_display_filled=1 zoom[num=1 den=1]


##6
###6.1 [avtranscoder的demo]  (https://gist.github.com/MarcAntoine-Arnaud/8912183)
###6.2 [kodi的demo] （https://github.com/w3techie/MediaLibre.tv/blob/bb504ddc4ce3375623acbd1f11569af7697c94ca/xbmc/cores/VideoPlayer/DVDCodecs/Video/MMALFFmpeg.cpp）

```
int CDecoder::FFGetBuffer(AVCodecContext *avctx, AVFrame *frame, int flags)
{
  CDVDVideoCodecFFmpeg *ctx = (CDVDVideoCodecFFmpeg*)avctx->opaque;
  CDecoder *dec = (CDecoder*)ctx->GetHardware();
  if (g_advancedSettings.CanLogComponent(LOGVIDEO))
    CLog::Log(LOGDEBUG,"%s::%s %dx%d format:%x:%x flags:%x", CLASSNAME, __FUNCTION__, frame->width, frame->height, frame->format, dec->m_fmt, flags);

  if ((avctx->codec && (avctx->codec->capabilities & AV_CODEC_CAP_DR1) == 0) || frame->format != dec->m_fmt)
  {
    assert(0);
    return avcodec_default_get_buffer2(avctx, frame, flags);
  }

  uint32_t mmal_format = 0;
  if (dec->m_fmt == AV_PIX_FMT_YUV420P)
    mmal_format = MMAL_ENCODING_I420;
  else if (dec->m_fmt == AV_PIX_FMT_ARGB)
    mmal_format = MMAL_ENCODING_ARGB;
  else if (dec->m_fmt == AV_PIX_FMT_RGBA)
    mmal_format = MMAL_ENCODING_RGBA;
  else if (dec->m_fmt == AV_PIX_FMT_ABGR)
    mmal_format = MMAL_ENCODING_ABGR;
  else if (dec->m_fmt == AV_PIX_FMT_BGRA)
    mmal_format = MMAL_ENCODING_BGRA;
  else if (dec->m_fmt == AV_PIX_FMT_RGB565LE)
    mmal_format = MMAL_ENCODING_RGB16;
  if (mmal_format ==  0)
    return -1;

  dec->m_pool->SetFormat(mmal_format, frame->width, frame->height, frame->width, frame->height, 0, dec->m_avctx);
  CMMALYUVBuffer *YUVBuffer = dynamic_cast<CMMALYUVBuffer *>(dec->m_pool->GetBuffer(500));
  if (!YUVBuffer || !YUVBuffer->mmal_buffer || !YUVBuffer->gmem)
  {
    CLog::Log(LOGERROR,"%s::%s Failed to allocated buffer in time", CLASSNAME, __FUNCTION__);
    return -1;
  }

  CSingleLock lock(dec->m_section);
  CGPUMEM *gmem = YUVBuffer->gmem;
  AVBufferRef *buf = av_buffer_create((uint8_t *)gmem->m_arm, (YUVBuffer->m_aligned_width * YUVBuffer->m_aligned_height * 3)>>1, CDecoder::FFReleaseBuffer, gmem, AV_BUFFER_FLAG_READONLY);
  if (!buf)
  {
    CLog::Log(LOGERROR, "%s::%s av_buffer_create() failed", CLASSNAME, __FUNCTION__);
    YUVBuffer->Release();
    return -1;
  }

  for (int i = 0; i < AV_NUM_DATA_POINTERS; i++)
  {
    frame->buf[i] = NULL;
    frame->data[i] = NULL;
    frame->linesize[i] = 0;
  }

  if (dec->m_fmt == AV_PIX_FMT_YUV420P)  /*是这么做的*/
  {
    frame->buf[0] = buf;
    frame->linesize[0] = YUVBuffer->m_aligned_width;
    frame->linesize[1] = YUVBuffer->m_aligned_width>>1;
    frame->linesize[2] = YUVBuffer->m_aligned_width>>1;
    frame->data[0] = (uint8_t *)gmem->m_arm;
    frame->data[1] = frame->data[0] + YUVBuffer->m_aligned_width * YUVBuffer->m_aligned_height;
    frame->data[2] = frame->data[1] + (YUVBuffer->m_aligned_width>>1) * (YUVBuffer->m_aligned_height>>1);
  }
  else if (dec->m_fmt == AV_PIX_FMT_BGR0)
  {
    frame->buf[0] = buf;
    frame->linesize[0] = YUVBuffer->m_aligned_width << 2;
    frame->data[0] = (uint8_t *)gmem->m_arm;
  }
  else if (dec->m_fmt == AV_PIX_FMT_RGB565LE)
  {
    frame->buf[0] = buf;
    frame->linesize[0] = YUVBuffer->m_aligned_width << 1;
    frame->data[0] = (uint8_t *)gmem->m_arm;
  }
  else assert(0);
  frame->extended_data = frame->data;
  // Leave extended buf alone

  if (g_advancedSettings.CanLogComponent(LOGVIDEO))
    CLog::Log(LOGDEBUG,"%s::%s buf:%p mmal:%p gmem:%p avbuf:%p:%p:%p", CLASSNAME, __FUNCTION__, YUVBuffer, YUVBuffer->mmal_buffer, gmem, frame->data[0], frame->data[1], frame->data[2]);

  return 0;
}

```

###6.3 [chrome的demo] (https://github.com/brave/browser-android-tabs/blob/68074d28d7a7b454c1785d677604f77757f359b2/media/filters/ffmpeg_video_decoder.h)

```
 // Callback called from within FFmpeg to allocate a buffer based on
  // the dimensions of |codec_context|. See AVCodecContext.get_buffer2
  // documentation inside FFmpeg.
  int GetVideoBuffer(struct AVCodecContext* codec_context,
                     AVFrame* frame,
                     int flags);
```


(GetVideoBuffer)[https://github.com/brave/browser-android-tabs/blob/68074d28d7a7b454c1785d677604f77757f359b2/media/filters/ffmpeg_video_decoder.cc]

```
int FFmpegVideoDecoder::GetVideoBuffer(struct AVCodecContext* codec_context,
                                       AVFrame* frame,
                                       int flags) {
  // Don't use |codec_context_| here! With threaded decoding,
  // it will contain unsynchronized width/height/pix_fmt values,
  // whereas |codec_context| contains the current threads's
  // updated width/height/pix_fmt, which can change for adaptive
  // content.
  const VideoPixelFormat format =
      AVPixelFormatToVideoPixelFormat(codec_context->pix_fmt);

  if (format == PIXEL_FORMAT_UNKNOWN)
    return AVERROR(EINVAL);
  DCHECK(format == PIXEL_FORMAT_YV12 || format == PIXEL_FORMAT_YV16 ||
         format == PIXEL_FORMAT_YV24 || format == PIXEL_FORMAT_YUV420P9 ||
         format == PIXEL_FORMAT_YUV420P10 || format == PIXEL_FORMAT_YUV422P9 ||
         format == PIXEL_FORMAT_YUV422P10 || format == PIXEL_FORMAT_YUV444P9 ||
         format == PIXEL_FORMAT_YUV444P10 || format == PIXEL_FORMAT_YUV420P12 ||
         format == PIXEL_FORMAT_YUV422P12 || format == PIXEL_FORMAT_YUV444P12);

  gfx::Size size(codec_context->width, codec_context->height);
  const int ret = av_image_check_size(size.width(), size.height(), 0, NULL);
  if (ret < 0)
    return ret;

  gfx::Size natural_size;
  if (codec_context->sample_aspect_ratio.num > 0) {
    natural_size = GetNaturalSize(size,
                                  codec_context->sample_aspect_ratio.num,
                                  codec_context->sample_aspect_ratio.den);
  } else {
    natural_size = config_.natural_size();
  }

  // FFmpeg has specific requirements on the allocation size of the frame.  The
  // following logic replicates FFmpeg's allocation strategy to ensure buffers
  // are not overread / overwritten.  See ff_init_buffer_info() for details.
  //
  // When lowres is non-zero, dimensions should be divided by 2^(lowres), but
  // since we don't use this, just DCHECK that it's zero.
  DCHECK_EQ(codec_context->lowres, 0);
  gfx::Size coded_size(std::max(size.width(), codec_context->coded_width),
                       std::max(size.height(), codec_context->coded_height));

  if (!VideoFrame::IsValidConfig(format, VideoFrame::STORAGE_UNKNOWN,
                                 coded_size, gfx::Rect(size), natural_size)) {
    return AVERROR(EINVAL);
  }

  // FFmpeg expects the initialize allocation to be zero-initialized.  Failure
  // to do so can lead to unitialized value usage.  See http://crbug.com/390941
  scoped_refptr<VideoFrame> video_frame = frame_pool_.CreateFrame(
      format, coded_size, gfx::Rect(size), natural_size, kNoTimestamp);

  if (!video_frame)
    return AVERROR(EINVAL);

  // Prefer the color space from the codec context. If it's not specified (or is
  // set to an unsupported value), fall back on the value from the config.
  ColorSpace color_space = AVColorSpaceToColorSpace(codec_context->colorspace,
                                                    codec_context->color_range);
  if (color_space == COLOR_SPACE_UNSPECIFIED)
    color_space = config_.color_space();
  video_frame->metadata()->SetInteger(VideoFrameMetadata::COLOR_SPACE,
                                      color_space);

  if (codec_context->color_primaries != AVCOL_PRI_UNSPECIFIED ||
      codec_context->color_trc != AVCOL_TRC_UNSPECIFIED ||
      codec_context->colorspace != AVCOL_SPC_UNSPECIFIED) {
    video_frame->set_color_space(
        gfx::ColorSpace(codec_context->color_primaries,
                        codec_context->color_trc, codec_context->colorspace,
                        codec_context->color_range != AVCOL_RANGE_MPEG
                            ? gfx::ColorSpace::RangeID::FULL
                            : gfx::ColorSpace::RangeID::LIMITED));
  }

  for (size_t i = 0; i < VideoFrame::NumPlanes(video_frame->format()); i++) {
    frame->data[i] = video_frame->data(i);
    frame->linesize[i] = video_frame->stride(i);
  }

  frame->width = coded_size.width();
  frame->height = coded_size.height();
  frame->format = codec_context->pix_fmt;
  frame->reordered_opaque = codec_context->reordered_opaque;

  // Now create an AVBufferRef for the data just allocated. It will own the
  // reference to the VideoFrame object.
  void* opaque = NULL;
  video_frame.swap(reinterpret_cast<VideoFrame**>(&opaque));
  frame->buf[0] =
      av_buffer_create(frame->data[0],
                       VideoFrame::AllocationSize(format, coded_size),
                       ReleaseVideoBufferImpl,
                       opaque,
                       0);
  return 0;
}
```