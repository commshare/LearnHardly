Ubuntu 16.04 安装 RabbitMQ

- [参考] (http://blog.topspeedsnail.com/archives/4750)
- rabbit mq有单机、默认（主从）和集群三种模式。这里是最简单的单机，用来测试几个go的rabbitmq测试程序。


#1 更新

```
 sudo apt-get update
 sudo apt-get upgrade

 sudo apt-get update
 sudo apt-get upgrade
```

#2 安装Erlang

```
cd /tmp
 wget http://packages.erlang-solutions.com/ubuntu/erlang_solutions.asc
 sudo apt-key add erlang_solutions.asc
 sudo apt-get update
 sudo apt-get install erlang
 sudo apt-get install erlang-nox

 cd /tmp
 wget http://packages.erlang-solutions.com/ubuntu/erlang_solutions.asc
 sudo apt-key add erlang_solutions.asc
 sudo apt-get update
 sudo apt-get install erlang
 sudo apt-get install erlang-nox

```
#3 安装RabbitMQ

添加RabbitMQ仓库源：

```
 sudo vim /etc/apt/sources.list

 sudo vim /etc/apt/sources.list
```

在文件中添加一行：

```
deb http://www.rabbitmq.com/debian/ testing main
```


添加密钥：
```

 cd /tmp
 wget https://www.rabbitmq.com/rabbitmq-signing-key-public.asc
 sudo apt-key add rabbitmq-signing-key-public.asc



 cd /tmp
 wget https://www.rabbitmq.com/rabbitmq-signing-key-public.asc
 sudo apt-key add rabbitmq-signing-key-public.asc
```


安装rabbitmq-server：

```
 sudo apt-get update
 sudo apt-get install rabbitmq-server


 sudo apt-get update
 sudo apt-get install rabbitmq-server
```

启动RabbitMQ服务：

```
 sudo systemctl enable rabbitmq-server
 sudo systemctl start rabbitmq-server


 sudo systemctl enable rabbitmq-server
 sudo systemctl start rabbitmq-server

```

查看RabbitMQ服务状态：

```
 sudo systemctl status rabbitmq-server
```



#4 RabbitMQ web管理接口

- 启用rabbitmq-management插件：

```
 sudo rabbitmq-plugins enable rabbitmq_management
```

重启RabbitMQ：

```
 sudo systemctl restart rabbitmq-server

```


使用浏览器访问 http://your_server_domain_or_IP:15672，使用默认的guest/guest用户登录：

- 遇到log fail的问题
- [参考] (http://stackoverflow.com/questions/22850546/cant-access-rabbitmq-web-management-interface-after-fresh-install)

- 新增一个test的用户, 管理员权限： 可登陆管理控制台(启用management plugin的情况下)，可查看所有的信息，并且可以对用户，策略(policy)进行操作。


```
rabbitmqctl add_user test test
rabbitmqctl set_user_tags test administrator 
rabbitmqctl set_permissions -p / test ".*" ".*" ".*"
```
使用test test登录。


查看指定用户的权限信息
```
root@ubuntu:/tmp# rabbitmqctl  list_user_permissions test
Listing permissions for user "test" ...
/       .*      
```


#5 发现没有配置文件

```
Config file	/etc/rabbitmq/rabbitmq.config (not found)
Database directory	/var/lib/rabbitmq/mnesia/rabbit@ubuntu
Log file	/var/log/rabbitmq/rabbit@ubuntu.log
SASL log file	/var/log/rabbitmq/rabbit@ubuntu-sasl.log
```



#6 验证rabbitmq 的端口
- [RabbitMQ 消息队列 配置] (http://jicki.blog.51cto.com/1323993/1631170)
- 其中5672为默认的rabbitmq监听端口，15672端口为WEB界面访问需要打开的端口。

```
root@ubuntu:/tmp# netstat -plantup|grep 15672
tcp        0      0 0.0.0.0:15672           0.0.0.0:*               LISTEN      53115/beam.smp  
tcp        0      0 172.25.21.13:15672      172.25.21.8:20663       TIME_WAIT   -               
tcp        0      0 172.25.21.13:15672      172.25.21.8:20688       TIME_WAIT   -               
tcp        0      0 172.25.21.13:15672      172.25.21.8:20693       ESTABLISHED 53115/beam.smp  
root@ubuntu:/tmp# netstat -plantup|grep 5672
tcp        0      0 0.0.0.0:25672           0.0.0.0:*               LISTEN      53115/beam.smp  
tcp        0      0 0.0.0.0:15672           0.0.0.0:*               LISTEN      53115/beam.smp  
tcp        0      0 172.25.21.13:15672      172.25.21.8:20688       TIME_WAIT   -               
tcp        0      0 172.25.21.13:15672      172.25.21.8:20693       ESTABLISHED 53115/beam.smp  
tcp6       0      0 :::5672                 :::*                    LISTEN      53115/beam.smp  
root@ubuntu:/tmp# 
```