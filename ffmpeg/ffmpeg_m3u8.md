
#

## 网络下载
- 这样会有问题啊，会卡主呢，所以应该是下注来，本地处理
```
 ffmpeg  -protocol_whitelist file,tcp,http  -i  15012_1101277597_22490906_1522291509554.m3u8 2.mp4

```

## 合并


### ts 变为 mp4,还做了转码

```
ffmpeg.exe -fflags +genpts -i "V:\演示视频.ts" -acodec copy -vcodec copy -absf aac_adtstoasc "V:\演示视频.mp4"
```

- "first pts value must set" or "Can't write packet with unknown timestamp" （https://trac.ffmpeg.org/ticket/1979）
- Adding -fflags +genpts fixes the problem, maybe this should be added automatically if necessary:

- (https://gist.github.com/lemenkov/2947110) 重新生成时间戳，解决不能给包写入未知时间戳问题
``` 

# "-fflags +genpts" - add this to regenerate packet timestamps (in case of error "Can't write packet with unknown timestamp")

./ffmpeg -fflags +genpts -i "/media/nfs/Nostromo/video/Japan Sinks (Nihon Chinbotsu) 1973 - WMV/NihonChinbotsu_1973.wmv" -acodec copy -vcodec copy ~/Desktop/NihonChinbotsu_1973.mkv

```

```
remove filelist file: V:\RECORD_TEST\refref\hjM3U8Down\videodownloadv2.0.0.5\cache\9d36f6af61043e343a332487b7131fa7\filelist.txt

Combine ts file finished!

Start transcode ts to mp4...
transcode command=ffmpeg.exe -fflags +genpts -i "V:\RECORD_TEST\refref\hjM3U8Down\videodownloadv2.0.0.5\cache\9d36f6af61043e343a332487b7131fa7\演示视频.ts" -acodec copy -vcodec copy -absf aac_adtstoasc "V:\RECORD_TEST\refref\hjM3U8Down\videodownloadv2.0.0.5\cache\9d36f6af61043e343a332487b7131fa7\演示视频.mp4"
```

### 怎么把一堆ts 变为一个ts呢？

```
Combine ts file start...
nCombine ts file command=ffmpeg.exe -f concat -safe 0 -i "V:\filelist.txt" -c copy "V:\演示视频.ts"
```

末尾加个 -y -report
- https://superuser.com/questions/1069556/ffmpeg-concat-demuxer-unsafe-file-name

```
ffmpeg.exe -f concat -safe 0 -i
"C:\Users\mtst\Desktop\Clips\keep\keep.txt" -c copy
"C:\Users\mtst\Desktop\Clips\keep\keep.mp4
Or don't use absolute (full) paths in keep.txt
```


## -safe 0
 - https://github.com/WritingMinds/ffmpeg-android/issues/44
```
In newer versions this was disabled in ffmpeg, you need to use the command -safe 0 to allow the use of concat.
```