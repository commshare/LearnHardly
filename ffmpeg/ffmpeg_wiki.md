

## 提取音频
- 保存为m4a 失败了
$ ffmpeg -i 14_lost_audio.ts -acodec copy -vn 14_lost_audio.ts.audioES.m4a
ffmpeg version N-81364-gf85842b Copyright (c) 2000-2016 the FFmpeg developers
  built with gcc 5.4.0 (GCC)
  configuration: --enable-gpl --enable-version3 --disable-w32threads --enable-dxva2 --enable-libmfx --enable-nvenc --enable-avisynth --enable-bzlib --enable-libebur128 --enable-fontconfig --enable-frei0r --enable-gnutls --enable-iconv --enable-libass --enable-libbluray --enable-libbs2b --enable-libcaca --enable-libfreetype --enable-libgme --enable-libgsm --enable-libilbc --enable-libmodplug --enable-libmp3lame --enable-libopencore-amrnb --enable-libopencore-amrwb --enable-libopenjpeg --enable-libopus --enable-librtmp --enable-libschroedinger --enable-libsnappy --enable-libsoxr --enable-libspeex --enable-libtheora --enable-libtwolame --enable-libvidstab --enable-libvo-amrwbenc --enable-libvorbis --enable-libvpx --enable-libwavpack --enable-libwebp --enable-libx264 --enable-libx265 --enable-libxavs --enable-libxvid --enable-libzimg --enable-lzma --enable-decklink --enable-zlib
  libavutil      55. 28.100 / 55. 28.100
  libavcodec     57. 53.100 / 57. 53.100
  libavformat    57. 46.101 / 57. 46.101
  libavdevice    57.  0.102 / 57.  0.102
  libavfilter     6. 51.100 /  6. 51.100
  libswscale      4.  1.100 /  4.  1.100
  libswresample   2.  1.100 /  2.  1.100
  libpostproc    54.  0.100 / 54.  0.100
Input #0, mpegts, from '14_lost_audio.ts':
  Duration: 00:00:04.74, start: 79.615989, bitrate: 2780 kb/s
  Program 1
    Metadata:
      service_name    : Service01
      service_provider: FFmpeg
    Stream #0:0[0x100]: Audio: aac (HE-AACv2) ([15][0][0][0] / 0x000F), 44100 Hz, stereo, fltp, 24 kb/s
    Stream #0:1[0x101]: Video: h264 (High) ([27][0][0][0] / 0x001B), yuv420p, 1920x1080, 25 fps, 25 tbr, 90k tbn, 50 tbc
[ipod @ 0000000002970160] Using AVStream.codec to pass codec parameters to muxers is deprecated, use AVStream.codecpar instead.
Output #0, ipod, to '14_lost_audio.ts.audioES.m4a':
  Metadata:
    encoder         : Lavf57.46.101
    Stream #0:0: Audio: aac (HE-AACv2) (mp4a / 0x6134706D), 44100 Hz, stereo, 24 kb/s
Stream mapping:
  Stream #0:0 -> #0:0 (copy)
Press [q] to stop, [?] for help
保存为m4a失败了
[ipod @ 0000000002970160] Malformed难看的，畸形的； AAC bitstream detected: use the audio bitstream filter 'aac_adtstoasc' to fix it ('-bsf:a aac_adtstoasc' option with ffmpeg)
av_interleaved_write_frame(): Operation not permitted
size=       0kB time=00:00:00.04 bitrate=  43.8kbits/s speed=81.8x
video:0kB audio:0kB subtitle:0kB other streams:0kB global headers:0kB muxing overhead: 62.820515%
Conversion failed!

zhangbin@DESKTOP-1QV8QU4 MINGW64 /f/TEST/M3U8_DOWN/0504
$

- (参考) [https://trac.ffmpeg.org/ticket/2782?cversion=0&cnum_hist=10]
- 加入-bsf aac_adtstoasc 保存为m4a成功

zhangbin@DESKTOP-1QV8QU4 MINGW64 /f/TEST/M3U8_DOWN/0504
$ ffmpeg -i 14_lost_audio.ts -acodec copy  -bsf aac_adtstoasc -vn 14_lost_audio.ts.audioES.m4a
ffmpeg version N-81364-gf85842b Copyright (c) 2000-2016 the FFmpeg developers
  built with gcc 5.4.0 (GCC)
  configuration: --enable-gpl --enable-version3 --disable-w32threads --enable-dxva2 --enable-libmfx --enable-nvenc --enable-avisynth --enable-bzlib --enable-libebur128 --enable-fontconfig --enable-frei0r --enable-gnutls --enable-iconv --enable-libass --enable-libbluray --enable-libbs2b --enable-libcaca --enable-libfreetype --enable-libgme --enable-libgsm --enable-libilbc --enable-libmodplug --enable-libmp3lame --enable-libopencore-amrnb --enable-libopencore-amrwb --enable-libopenjpeg --enable-libopus --enable-librtmp --enable-libschroedinger --enable-libsnappy --enable-libsoxr --enable-libspeex --enable-libtheora --enable-libtwolame --enable-libvidstab --enable-libvo-amrwbenc --enable-libvorbis --enable-libvpx --enable-libwavpack --enable-libwebp --enable-libx264 --enable-libx265 --enable-libxavs --enable-libxvid --enable-libzimg --enable-lzma --enable-decklink --enable-zlib
  libavutil      55. 28.100 / 55. 28.100
  libavcodec     57. 53.100 / 57. 53.100
  libavformat    57. 46.101 / 57. 46.101
  libavdevice    57.  0.102 / 57.  0.102
  libavfilter     6. 51.100 /  6. 51.100
  libswscale      4.  1.100 /  4.  1.100
  libswresample   2.  1.100 /  2.  1.100
  libpostproc    54.  0.100 / 54.  0.100
Input #0, mpegts, from '14_lost_audio.ts':
  Duration: 00:00:04.74, start: 79.615989, bitrate: 2780 kb/s
  Program 1
    Metadata:
      service_name    : Service01
      service_provider: FFmpeg
    Stream #0:0[0x100]: Audio: aac (HE-AACv2) ([15][0][0][0] / 0x000F), 44100 Hz, stereo, fltp, 24 kb/s
    Stream #0:1[0x101]: Video: h264 (High) ([27][0][0][0] / 0x001B), yuv420p, 1920x1080, 25 fps, 25 tbr, 90k tbn, 50 tbc
[ipod @ 0000000002ab0540] Using AVStream.codec to pass codec parameters to muxers is deprecated, use AVStream.codecpar instead.
Output #0, ipod, to '14_lost_audio.ts.audioES.m4a':
  Metadata:
    encoder         : Lavf57.46.101
    Stream #0:0: Audio: aac (HE-AACv2) (mp4a / 0x6134706D), 44100 Hz, stereo, 24 kb/s
Stream mapping:
  Stream #0:0 -> #0:0 (copy)
Press [q] to stop, [?] for help
size=      15kB time=00:00:04.73 bitrate=  26.1kbits/s speed= 263x
video:0kB audio:13kB subtitle:0kB other streams:0kB global headers:0kB muxing overhead: 14.136938%

zhangbin@DESKTOP-1QV8QU4 MINGW64 /f/TEST/M3U8_DOWN/0504
$


- 保存为aac

zhangbin@DESKTOP-1QV8QU4 MINGW64 /f/TEST/M3U8_DOWN/0504
$ ffmpeg -i 14_lost_audio.ts -acodec copy -vn 14_lost_audio.ts.audioES.aac
ffmpeg version N-81364-gf85842b Copyright (c) 2000-2016 the FFmpeg developers
  built with gcc 5.4.0 (GCC)
  configuration: --enable-gpl --enable-version3 --disable-w32threads --enable-dxva2 --enable-libmfx --enable-nvenc --enable-avisynth --enable-bzlib --enable-libebur128 --enable-fontconfig --enable-frei0r --enable-gnutls --enable-iconv --enable-libass --enable-libbluray --enable-libbs2b --enable-libcaca --enable-libfreetype --enable-libgme --enable-libgsm --enable-libilbc --enable-libmodplug --enable-libmp3lame --enable-libopencore-amrnb --enable-libopencore-amrwb --enable-libopenjpeg --enable-libopus --enable-librtmp --enable-libschroedinger --enable-libsnappy --enable-libsoxr --enable-libspeex --enable-libtheora --enable-libtwolame --enable-libvidstab --enable-libvo-amrwbenc --enable-libvorbis --enable-libvpx --enable-libwavpack --enable-libwebp --enable-libx264 --enable-libx265 --enable-libxavs --enable-libxvid --enable-libzimg --enable-lzma --enable-decklink --enable-zlib
  libavutil      55. 28.100 / 55. 28.100
  libavcodec     57. 53.100 / 57. 53.100
  libavformat    57. 46.101 / 57. 46.101
  libavdevice    57.  0.102 / 57.  0.102
  libavfilter     6. 51.100 /  6. 51.100
  libswscale      4.  1.100 /  4.  1.100
  libswresample   2.  1.100 /  2.  1.100
  libpostproc    54.  0.100 / 54.  0.100
Input #0, mpegts, from '14_lost_audio.ts':
  Duration: 00:00:04.74, start: 79.615989, bitrate: 2780 kb/s
  Program 1
    Metadata:
      service_name    : Service01
      service_provider: FFmpeg
    Stream #0:0[0x100]: Audio: aac (HE-AACv2) ([15][0][0][0] / 0x000F), 44100 Hz, stereo, fltp, 24 kb/s
    Stream #0:1[0x101]: Video: h264 (High) ([27][0][0][0] / 0x001B), yuv420p, 1920x1080, 25 fps, 25 tbr, 90k tbn, 50 tbc
    这个是说ffmpeg升级了avcodec的一些用法，不是错误
[adts @ 0000000002960160] Using AVStream.codec to pass codec parameters to muxers is deprecated, use AVStream.codecpar instead.
Output #0, adts, to '14_lost_audio.ts.audioES.aac':
  Metadata:
    encoder         : Lavf57.46.101
    Stream #0:0: Audio: aac (HE-AACv2) ([15][0][0][0] / 0x000F), 44100 Hz, stereo, 24 kb/s
Stream mapping:
  Stream #0:0 -> #0:0 (copy)
Press [q] to stop, [?] for help
size=      14kB time=00:00:04.73 bitrate=  24.1kbits/s speed= 681x
video:0kB audio:15kB subtitle:0kB other streams:0kB global headers:0kB muxing overhead: unknown
