.PHONY:clean
SERVER_BUILD_PATH ?= .
CC = g++
CFLAGS = -O3 -std=c++0x -pg -D_DEBUG -g -Wall -Wno-write-strings -DUSE_PTHREAD_LOCK -DEVENT__HAVE_EVENTFD
TAGET = main
MODULE = server_main.cpp log.c timer.c malloc.c server_env.c util.c ServerStart.cpp server_config.c server_thread.c \
	servant.c mq.c NetWork.cpp EndpointServer.cpp net_work.c TimerMgr.cpp MessageDispatch.cpp ServantBase.cpp \
	ServantHandler.cpp
INC = -I$(SRC_PATH) -I$(COMMON) -I$(3RD) -I$(LIBEVENT_PATH)/include -I$(FLATCC_PATH)/portable \
	-I$(FLATCC_PATH)/reflection -I$(FLATCC_PATH)/support -I$(FLATCC_PATH) -I$(FBS)
LIBS = -levent_core -lpthread -lrt -lmysqlclient -levent_pthreads
FLATCC_PATH ?= $(SERVER_BUILD_PATH)/../3rd/flatcc
LIBEVENT_PATH ?= $(SERVER_BUILD_PATH)/../3rd/libevent
FBS = $(SERVER_BUILD_PATH)/../fbs
3RD = $(SERVER_BUILD_PATH)/../3rd
LIB_PATH = -L$(FLATCC_PATH)/lib/

$(TAGET): \
  $(foreach v, $(MODULE), $(SERVER_BUILD_PATH)/$(v))
	$(CC) $(CFLAGS) $^ -o $@ $(INC) $(LIBS) $(LIB_PATH)
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(TAGET)