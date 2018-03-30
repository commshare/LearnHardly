

日志常用统计技巧
最后更新: 2013-01-08

常用命令
用途	常用命令
打包压缩	gzip,tar
内容输出	tail,head,cat,zcat,more,less,管道,>,>>
内容过滤	grep,sed
内容拆分	awk,cut
排序汇总	sort,uniq,awk
日志截取
按时间截取
1
2
# 截取指定时间段日志
sed -n '/^2012-12-26 14:30/,/^2012-12-26 14:32/p' server.log|more
按标识截取
截取特定标识日志的内容(仅特定标识日志行、或标识附近日志行)

1
2
# 过滤包含特定标识(忽略大小写)的日志、并显示前后10行
grep -i  -A 10 -B 10 "error" server.log|more
按指定列截取
1
2
# 截取第7列为'/test'的行
cat server.log|awk 'if($7=="/test"{print $0}'|more
分页显示
使用more,less进行分页显示，more仅能简单地向后翻页，less可上下翻页、并可通过/word来查找包含word的行。

常用快键键
按键	功能	备注
空格	下一页	 
q	退出	 
PgUp	上一页	less
PgDn	下一页	 
/word	查找word所在位置	less
n	查找下一个	less
N	查找下上个	less
使用管道、重定向
通过管道可将截取内容或统计结果直接存入文件中，其中>为覆盖原文件、>>为追加至文件。

1
2
3
4
grep -i  -A 10 -B 10 "error" server.log > server_error.txt
 
# >  : 覆盖文件
# >> : 追加到文件末尾
日志统计
分时访问量统计
对日志中的时间列进行拆分，根据时间格式取YYYY-mm-DD HH:MM部分、进行排序、汇总，即可获得每分钟的访问量统计。


# 按分钟汇总统计访问量
cat server.log | grep "^2012-" | awk -F\: '{print $1" "$2":"$3}'|sort|uniq -c|more
 
# 按小时汇总统计访问量
cat server.log | grep "^2012-" | awk -F\: '{print $1" "$2"}'|sort|uniq -c|more
日志中的IP地址
WEB服务器日志(nginx,apache)中，通常第一列为客户端IP地址，取该段值进行排序、汇总，即可得到IP:访问次数的统计。


# 从日志中统计IP访问次数
cat server.log | awk '{print $1}'|sort|uniq -c|more
 
# 统计来访唯一IP数
cat server.log | awk '{print $1}'|sort|uniq|wc -l
网络连接状态
netstat命令可获取系统当前的侦听、连接状态，包括协议、源IP:端口、目标IP:端口、连接状态信息，取关注的列进行排序、汇总，即可获得连接数、状态等统计。


# TCP连接数
netstat -antp|grep ^tcp|awk '{print $5}'|awk -F\: '{print $1}'|sort|uniq -c|sort -nr
 
      5 0.0.0.0
      2 192.217.199.215
      1 91.189.89.144
      1 172.16.17.4
      1 172.16.17.3
      1 172.16.17.27
 
# TCP连接状态
netstat -antp|grep ^tcp|awk '{print $6}'|sort|uniq -c|sort -nr
 
     17 ESTABLISHED
      8 LISTEN
      1 CLOSE_WAIT
 
# 根据Ficapy的反馈，使用awk的正则匹配进行过滤，减少前面的grep指令(谢谢Ficapy的提醒)
# 不过grep的过滤处理速度似乎比awk的正则匹配速度更快，因此对大日志分析时可能还是先用grep过滤效率更高
time cat netstat.txt |awk '/^tcp/ {print $6}'|sort|uniq -c|sort -nr
   2713 TIME_WAIT
    203 ESTABLISHED
     29 FIN_WAIT1
     18 LISTEN
     17 FIN_WAIT2
 
real    0m0.017s
user    0m0.014s
sys 0m0.002s
time cat netstat.txt |grep ^tcp|awk '{print $6}'|sort|uniq -c|sort -nr
   2713 TIME_WAIT
    203 ESTABLISHED
     29 FIN_WAIT1
     18 LISTEN
     17 FIN_WAIT2
 
real    0m0.008s
user    0m0.005s
sys 0m0.001s
 
# 其他awk匹配方式
cat netstat.txt |awk '{if($1=="tcp")print $6}'|sort|uniq -c|sort -nr
   2713 TIME_WAIT
    203 ESTABLISHED
     29 FIN_WAIT1
     18 LISTEN
     17 FIN_WAIT2
 
cat netstat.txt |awk '$1=="tcp" {print $6}'|sort|uniq -c|sort -nr
   2713 TIME_WAIT
    203 ESTABLISHED
     29 FIN_WAIT1
     18 LISTEN
     17 FIN_WAIT2
 
# 多条件匹配
cat netstat.txt |awk '/^tcp|^udp/ {print $1"-"$6}'|sort|uniq -c|sort -nr
   2713 tcp-TIME_WAIT
    203 tcp-ESTABLISHED
     29 tcp-FIN_WAIT1
     18 tcp-LISTEN
     17 tcp-FIN_WAIT2
      4 udp-32366/rpcbind
      4 udp--
      3 udp-32526/rpc.statd
      2 udp-19339/rpc.mountd
      1 udp-ESTABLISHED
      1 udp-38143/gmond
      1 udp-19335/rpc.rquotad
      1 udp-1282/portreserve
 
cat netstat.txt |awk '{if($1~"^tcp" || $1~"^udp")print $1"-"$6}'|sort|uniq -c|sort -nr
   2713 tcp-TIME_WAIT
    203 tcp-ESTABLISHED
     29 tcp-FIN_WAIT1
     18 tcp-LISTEN
     17 tcp-FIN_WAIT2
      4 udp-32366/rpcbind
      4 udp--
      3 udp-32526/rpc.statd
      2 udp-19339/rpc.mountd
      1 udp-ESTABLISHED
      1 udp-38143/gmond
      1 udp-19335/rpc.rquotad
      1 udp-1282/portreserve
 
cat netstat.txt |awk '{if($1=="tcp" && $6!~"ESTABLISHED")print $6}'|sort|uniq -c|sort -nr
   2713 TIME_WAIT
     29 FIN_WAIT1
     18 LISTEN
     17 FIN_WAIT2
URI、Agent统计
WEB服务器(apache,nginx,iis等)日志中，通常存有每个请求的URI、浏览器版本等信息，对其进行拆分、排序、汇总，即可获得各URI访问量统计。统计的命令与上面的类似。