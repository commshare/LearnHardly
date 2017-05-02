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

- 新增一个test的用户： 
```
rabbitmqctl add_user test test
rabbitmqctl set_user_tags test administrator
rabbitmqctl set_permissions -p / test ".*" ".*" ".*"
```
使用test test登录。

#5 发现没有配置文件

```
Config file	/etc/rabbitmq/rabbitmq.config (not found)
Database directory	/var/lib/rabbitmq/mnesia/rabbit@ubuntu
Log file	/var/log/rabbitmq/rabbit@ubuntu.log
SASL log file	/var/log/rabbitmq/rabbit@ubuntu-sasl.log
```