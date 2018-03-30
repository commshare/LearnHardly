

```  只看视频一xml
root@ubuntu:/home/zhangbin/ffmpeg/RECORD_TEST/refref/testMPEGTS/tsfile# ffprobe  -show_frames sub_108.m3u8_26hours.ts -of xml -select_streams v
ffprobe version 3.4.1-1~16.04.york0 Copyright (c) 2007-2017 the FFmpeg developers
  built with gcc 5.4.0 (Ubuntu 5.4.0-6ubuntu1~16.04.5) 20160609

  configuration: --prefix=/usr --extra-version='1~16.04.york0' --toolchain=hardened --libdir=/usr/lib/x86_64-linux-gnu --incdir=/usr/include/x86_64-linux-gnu --enable-gpl --disable-stripping --enable-avresample --enable-avisynth --enable-gnutls --enable-ladspa --enable-libass --enable-libbluray --enable-libbs2b --enable-libcaca --enable-libcdio --enable-libflite --enable-libfontconfig --enable-libfreetype --enable-libfribidi --enable-libgme --enable-libgsm --enable-libmp3lame --enable-libmysofa --enable-libopenjpeg --enable-libopenmpt --enable-libopus --enable-libpulse --enable-librubberband --enable-librsvg --enable-libshine --enable-libsnappy --enable-libsoxr --enable-libspeex --enable-libssh --enable-libtheora --enable-libtwolame --enable-libvorbis --enable-libvpx --enable-libwavpack --enable-libwebp --enable-libx265 --enable-libxml2 --enable-libxvid --enable-libzmq --enable-libzvbi --enable-omx --enable-openal --enable-opengl --enable-sdl2 --enable-libdc1394 --enable-libdrm --enable-libiec61883 --enable-chromaprint --enable-frei0r --enable-libopencv --enable-libx264 --enable-shared
  libavutil      55. 78.100 / 55. 78.100
  libavcodec     57.107.100 / 57.107.100
  libavformat    57. 83.100 / 57. 83.100
  libavdevice    57. 10.100 / 57. 10.100
  libavfilter     6.107.100 /  6.107.100
  libavresample   3.  7.  0 /  3.  7.  0
  libswscale      4.  8.100 /  4.  8.100
  libswresample   2.  9.100 /  2.  9.100
  libpostproc    54.  7.100 / 54.  7.100
<?xml version="1.0" encoding="UTF-8"?>
<ffprobe>
Input #0, mpegts, from 'sub_108.m3u8_26hours.ts':
  Duration: 26:24:50.57, start: 1.400000, bitrate: 0 kb/s
  Program 1 
    Metadata:
      service_name    : Service01
      service_provider: FFmpeg
    Stream #0:0[0x100]: Video: h264 (High) ([27][0][0][0] / 0x001B), yuv420p(tv, smpte170m/bt709/bt709, progressive), 544x960, 23.83 tbr, 90k tbn, 180k tbc
    Stream #0:1[0x101]: Audio: aac (HE-AACv2) ([15][0][0][0] / 0x000F), 44100 Hz, stereo, fltp, 28 kb/s
    <frames>
        <frame media_type="video" stream_index="0" key_frame="1" pkt_pts="126000" pkt_pts_time="1.400000" pkt_dts="126000" pkt_dts_time="1.400000" best_effort_timestamp="126000" best_effort_timestamp_time="1.400000" pkt_pos="564" pkt_size="5835" width="544" height="960" pix_fmt="yuv420p" pict_type="I" coded_picture_number="0" display_picture_number="0" interlaced_frame="0" top_field_first="0" repeat_pict="0" color_range="tv" color_space="smpte170m" color_primaries="bt709" color_transfer="bt709" chroma_location="left"/>
        <frame media_type="video" stream_index="0" key_frame="0" pkt_pts="8558269263" pkt_pts_time="95091.880700" pkt_dts="129781" pkt_dts_time="1.442011" best_effort_timestamp="8558269263" best_effort_timestamp_time="95091.880700 这个的单位是秒，是根据pts计算出来的，如果除以3600秒，确实是26.41 " pkt_pos="6580" pkt_size="2950" width="544" height="960" pix_fmt="yuv420p" pict_type="P" coded_picture_number="1" display_picture_number="0" interlaced_frame="0" top_field_first="0" repeat_pict="0" color_range="tv" color_space="smpte170m" color_primaries="bt709" color_transfer="bt709" chroma_location="left"/>
        <frame media_type="video" stream_index="0" key_frame="0" pkt_pts="8558269713" pkt_pts_time="95091.885700" pkt_dts="133561" pkt_dts_time="1.484011" best_effort_timestamp="8558269713" best_effort_timestamp_time="95091.885700" pkt_pos="10152" pkt_size="4047" width="544" height="960" pix_fmt="yuv420p" pict_type="P" coded_picture_number="2" display_picture_number="0" interlaced_frame="0" top_field_first="0" repeat_pict="0" color_range="tv" color_space="smpte170m" color_primaries="bt709" color_transfer="bt709" chroma_location="left"/>
        <frame media_type="video" stream_index="0" key_frame="0" pkt_pts="8558270163" pkt_pts_time="95091.890700" pkt_dts="137431" pkt_dts_time="1.527011" best_effort_timestamp="8558270163" best_effort_timestamp_time="95091.890700" pkt_pos="14476" pkt_size="3335" width="544" height="960" pix_fmt="yuv420p" pict_type="P" coded_picture_number="3" display_picture_number="0" interlaced_frame="0" top_field_first="0" repeat_pict="0" color_range="tv" color_space="smpte170m" color_primaries="bt709" color_transfer="bt709" chroma_location="left"/>
        <frame media_type="video" stream_index="0" key_frame="0" pkt_pts="8558270613" pkt_pts_time="95091.895700" pkt_dts="141121" pkt_dts_time="1.568011" best_effort_timestamp="8558270613" best_effort_timestamp_time="95091.895700" pkt_pos="18424" pkt_size="3851" width="544" height="960" pix_fmt="yuv420p" pict_type="P" coded_picture_number="4" display_picture_number="0" interlaced_frame="0" top_field_first="0" repeat_pict="0" color_range="tv" color_space="smpte170m" color_primaries="bt709" color_transfer="bt709" chroma_location="left"/>
        <frame media_type="video" stream_index="0" key_frame="0" pkt_pts="8558271063" pkt_pts_time="95091.900700" pkt_dts="144811" pkt_dts_time="1.609011" best_effort_timestamp="8558271063" best_effort_timestamp_time="95091.900700" pkt_pos="22560" pkt_size="4390" width="544" height="960" pix_fmt="yuv420p" pict_type="P" coded_picture_number="5" display_picture_number="0" interlaced_frame="0" top_field_first="0" repeat_pict="0" color_range="tv" color_space="smpte170m" color_primaries="bt709" color_transfer="bt709" chroma_location="left"/>
        <frame media_type="video" stream_index="0" key_frame="0" pkt_pts="8558271513" pkt_pts_time="95091.905700" pkt_dts="148591" pkt_dts_time="1.651011" best_effort_timestamp="8558271513" best_effort_timestamp_time="95091.905700" pkt_pos="27448" pkt_size="4927" width="544" height="960" pix_fmt="yuv420p" pict_type="P" coded_picture_number="6" display_picture_number="0" interlaced_frame="0" top_field_first="0" repeat_pict="0" color_range="tv" color_space="smpte170m" color_primaries="bt709" color_transfer="bt709" chroma_location="left"/>
        <frame media_type="video" stream_index="0" key_frame="0" pkt_pts="8558271963" pkt_pts_time="95091.910700" pkt_dts="152551" pkt_dts_time="1.695011" best_effort_timestamp="8558271963" best_effort_timestamp_time="95091.910700" pkt_pos="32900" pkt_size="4253" width="544" height="960" pix_fmt="yuv420p" pict_type="P" coded_picture_number="7" display_picture_number="0" interlaced_frame="0" top_field_first="0" repeat_pict="0" color_range="tv" color_space="smpte170m" color_primaries="bt709" color_transfer="bt709" chroma_location="left"/>
        <frame media_type="video" stream_index="0" key_frame="0" pkt_pts="8558272413" pkt_pts_time="95091.915700" pkt_dts="155971" pkt_dts_time="1.733011" best_effort_timestamp="8558272413" best_effort_timestamp_time="95091.915700" pkt_pos="37412" pkt_size="5810" width="544" height="960" pix_fmt="yuv420p" pict_type="P" coded_picture_number="8" display_picture_number="0" interlaced_frame="0" top_field_first="0" repeat_pict="0" color_range="tv" color_space="smpte170m" color_primaries="bt709" color_transfer="bt709" chroma_location="left"/>
        <frame media_type="video" stream_index="0" key_frame="0" pkt_pts="8558272863" pkt_pts_time="95091.920700" pkt_dts="159751" pkt_dts_time="1.775011" best_effort_timestamp="8558272863" best_effort_timestamp_time="95091.920700" pkt_pos="43992" pkt_size="6190" width="544" height="960" pix_fmt="yuv420p" pict_type="P" coded_picture_number="9" display_picture_number="0" interlaced_frame="0" top_field_first="0" repeat_pict="0" color_range="tv" color_space="smpte170m" color_primaries="bt709" color_transfer="bt709" chroma_location="left"/>
        <frame media_type="video" stream_index="0" key_frame="0" pkt_pts="8558273313" pkt_pts_time="95091.925700" pkt_dts="163981" pkt_dts_time="1.822011" best_effort_timestamp="8558273313" best_effort_timestamp_time="95091.925700" pkt_pos="50760" pkt_size="5872" width="544" height="960" pix_fmt="yuv420p" pict_type="P" coded_picture_number="10" display_picture_number="0" interlaced_frame="0" top_field_first="0" repeat_pict="0" color_range="tv" color_space="smpte170m" color_primaries="bt709" color_transfer="bt709" chroma_location="left"/>
    </frames>
</ffprobe>
root@ubuntu:/home/zhangbin/ffmpeg/RECORD_TEST/refref/testMPEGTS/tsfile# 

```