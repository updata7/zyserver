.PHONY:clean
SERVER_BUILD_PATH ?= .
SRC_PATH ?= $(SERVER_BUILD_PATH)/../../src
FLATCC_PATH ?= $(SERVER_BUILD_PATH)/../../3rd/flatcc
CC = gcc
CFLAGS = -g -Wall -std=gnu99 -DUSE_PTHREAD_LOCK
TAGET = client
MODULE = client.c
FBS = $(SERVER_BUILD_PATH)/../../fbs
3RD = $(SERVER_BUILD_PATH)/../../3rd
COMMON = $(SERVER_BUILD_PATH)/../../common
INC = -I$(SRC_PATH) -I$(COMMON) -I$(3RD) -I$(FLATCC_PATH)/portable \
	-I$(FLATCC_PATH)/support -I$(FLATCC_PATH)/reflection -I$(FLATCC_PATH) -I$(FBS)
LIB = -lpthread -lflatcc -lflatccrt
LIB_PATH = -L$(FLATCC_PATH)/lib/

$(TAGET): \
  $(foreach v, $(OBJECT), $(SRC_PATH)/$(v)) \
  $(foreach v, $(MODULE), $(SERVER_BUILD_PATH)/$(v))
	$(CC) $(CFLAGS) $^ -o $@ $(LIB) $(LIB_PATH) $(INC)
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(TAGET)