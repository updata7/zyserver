.PHONY:clean
SERVER_BUILD_PATH ?= .
SRC_PATH ?= $(SERVER_BUILD_PATH)/../source
FRAME_PATH ?= $(SERVER_BUILD_PATH)/../framework

include $(FRAME_PATH)/common.mk

TAGET = main
MODULE := Interface.cpp GsTask.cpp GsLogin.cpp
INC = -I$(FRAME_PATH) -I$(SERVER_BUILD_PATH) -I$(SRC_PATH) -I$(COMMON) -I$(3RD) -I$(LIBEVENT_PATH)/include -I$(FLATCC_PATH)/portable \
	-I$(FLATCC_PATH)/reflection -I$(FLATCC_PATH)/support -I$(FLATCC_PATH) -I$(FBS)

$(TAGET): \
  $(foreach v, $(BASE_OBJECT), $(SRC_PATH)/$(v)) \
  $(foreach v, $(MODULE), $(SERVER_BUILD_PATH)/$(v)) \
  $(foreach v, $(FRAME_OBJECT), $(FRAME_PATH)/$(v))
	$(CC) $(CFLAGS) $^ -o $@ $(INC) $(LIBS) $(LIB_PATH)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(TAGET)