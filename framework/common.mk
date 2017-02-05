CC = g++
CFLAGS = -O3 -std=c++0x -D_DEBUG -g -Wall -Wno-write-strings -DUSE_PTHREAD_LOCK -DEVENT__HAVE_EVENTFD
BASE_OBJECT := log.c timer.c server_env.c util.c server_config.c server_thread.c \
	servant.c mq.c net_work.c db_ops.c zredis.c
FRAME_OBJECT = MessageDispatch.cpp NetWork.cpp ServantBase.cpp ServantHandler.cpp ServerMain.cpp ServerStart.cpp TimerMgr.cpp
LIBS := -levent_core -lpthread -lrt -levent_pthreads -lmysqlclient -lhiredis
FLATCC_PATH ?= $(SERVER_BUILD_PATH)/../3rd/flatcc
LIBEVENT_PATH ?= $(SERVER_BUILD_PATH)/../3rd/libevent
FBS = $(SERVER_BUILD_PATH)/../fbs
3RD = $(SERVER_BUILD_PATH)/../3rd
LIB_PATH = -L$(FLATCC_PATH)/lib/