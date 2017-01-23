CC = g++
CFLAGS = -O3 -std=c++0x -pg -D_DEBUG -g -Wall -Wno-write-strings -DUSE_PTHREAD_LOCK -DEVENT__HAVE_EVENTFD -DSERVANT_TYPE=long \
	-DSERVANT_SIZE=10
OBJECT := server_main.cpp log.c timer.c malloc.c server_env.c util.c ServerStart.cpp server_config.c server_thread.c \
	servant.c mq.c NetWork.cpp net_work.c TimerMgr.cpp MessageDispatch.cpp ServantBase.cpp \
	ServantHandler.cpp db_ops.c
LIBS := -levent_core -lpthread -lrt -levent_pthreads -lmysqlclient