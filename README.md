# zyserver(the game server base on libevent)

#libevent:2.0.22 stable(download from http://libevent.org/)
	./configure -prefix=/usr
	make
	make install
	if success：
		ls -al /usr/lib | grep libevent

#mysql in ubuntu:
	install: sudo apt-get install mysql-server-5.5
	start: sudo start mysql
	stop: sudo stop mysql
	change port: sudo vi /etc/mysql/my.cnf(two point:client port and mysqld port)

#build all server(at the path of zyserver):
	make

#run server:
	./start_all.sh

#client test: 
	./zyserver/test/client -a address -p port -l msglen -t thread_num
	more detail read the zyserver/test/client/readme

#说明
	1、本服务器还未投入项目使用，存在很多问题，仅供学习。
	2、fbs及3rd/flatcc这两个目录，本是为flatcc准备，后面没用上，暂时搁着，以后也许用得上
	3、数据库方面，有redis的相关测试，考虑到redis和mysql的数据互转时会比较繁琐，暂时没有
	考虑，另外，mysql的操作，也只是简单提供了接口，要用需要再封装优化
	4、本服务器，设计思路如下：
		1)source下均为纯C代码，日志、定时器及数据库等模块，均在此实现
		2)framework是上层架构，C++实现，对source提供的接口进行封装
		3)服务器的入口文件，在framework下的ServerMain.cpp，启动时读配置文件，连接对端服务器及开启监听端口，并加载本服务的业务逻辑代码
		4)写业务逻辑时，关注source下的ServantDef.h，各服务器关注各自的Interface，如dbmgr下的Interface.h和Interface.cpp
		5)每一个业务逻辑，都可以看成是一个servant，servant值在ServantDef.h定义
	5、未完成：
		1)各进程间，需要提供一个等待某个受关注的进程初始化完成的接口，以便后续逻辑处理
		2)各进程间，需要处理等待重连的超时处理
		3)对数据的封包解包，协议选取(google protobuf)
		4)测试优化