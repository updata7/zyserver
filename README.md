# zyserver

#libevent:2.0.22 stable
	./configure -prefix=/usr
	make
	make install
#if success：
	ls -al /usr/lib | grep libevent

#mysql in ubuntu:
	install: sudo apt-get install mysql-server-5.5
	start: sudo start mysql
	stop: sudo stop mysql
	change port: sudo vi /etc/mysql/my.cnf(two point:client port and mysqld port)
