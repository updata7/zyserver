.PHONY:clean
SERVER_BUILD_PATH ?= .
CC = g++
CFLAGS = -O3 -std=c++0x -pg -D_DEBUG -g -Wall -Wno-write-strings -DUSE_PTHREAD_LOCK -DEVENT__HAVE_EVENTFD
TAGET = libzyserver.so
SHARED := -fPIC --shared

MODULE = log.c timer.c server_env.c util.c server_config.c server_thread.c \
	servant.c mq.c net_work.c
FLATCC_PATH ?= $(SERVER_BUILD_PATH)/../3rd/flatcc
LIBEVENT_PATH ?= $(SERVER_BUILD_PATH)/../3rd/libevent
FBS = $(SERVER_BUILD_PATH)/../fbs
3RD = $(SERVER_BUILD_PATH)/../3rd
LIB_PATH = -L$(FLATCC_PATH)/lib/

INC = -I$(SERVER_BUILD_PATH) -I$(3RD) -I$(LIBEVENT_PATH)/include -I$(FLATCC_PATH)/portable \
	-I$(FLATCC_PATH)/reflection -I$(FLATCC_PATH)/support -I$(FLATCC_PATH) -I$(FBS)
LIBS = -levent_core -lpthread -lrt -lmysqlclient -levent_pthreads

$(TAGET): \
  $(foreach v, $(MODULE), $(SERVER_BUILD_PATH)/$(v))
	$(CC) $(CFLAGS) $(SHARED) $^ -o $@ $(INC) $(LIB_PATH) $(LIBS)
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(TAGET)