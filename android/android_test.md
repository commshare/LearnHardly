#记录一些调试和测试用的命令

##1

cur capture fps
onSurfaceChanged

480X640 


##2   看内存和cpu

`
 top -d 3| grep  com.ycloud.mediarecord.demo
 `

通过以下命令，主要看app summary的内容：
 `
 dumpsys meminfo  com.ycloud.mediarecord.demo
 `

 
