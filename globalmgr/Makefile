.PHONY:clean
SERVER_BUILD_PATH ?= .
SRC_PATH ?= $(SERVER_BUILD_PATH)/../source
COMMON_PATH ?= $(SERVER_BUILD_PATH)/../common

include $(SRC_PATH)/common.mk

TAGET = main
MODULE := Interface.cpp GbmTask.cpp GbmLogin.cpp
INC = -I$(COMMON_PATH) -I$(SERVER_BUILD_PATH) -I$(SRC_PATH) -I$(COMMON) -I$(3RD) -I$(LIBEVENT_PATH)/include -I$(FLATCC_PATH)/portable \
	-I$(FLATCC_PATH)/reflection -I$(FLATCC_PATH)/support -I$(FLATCC_PATH) -I$(FBS)
# LIBS := -lmysqlclient
FLATCC_PATH ?= $(SERVER_BUILD_PATH)/../3rd/flatcc
LIBEVENT_PATH ?= $(SERVER_BUILD_PATH)/../3rd/libevent
FBS = $(SERVER_BUILD_PATH)/../fbs
3RD = $(SERVER_BUILD_PATH)/../3rd
LIB_PATH = -L$(FLATCC_PATH)/lib/

$(TAGET): \
  $(foreach v, $(OBJECT), $(SRC_PATH)/$(v)) \
  $(foreach v, $(MODULE), $(SERVER_BUILD_PATH)/$(v))
	$(CC) $(CFLAGS) $^ -o $@ $(INC) $(LIBS) $(LIB_PATH)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(TAGET)