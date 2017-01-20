.PHONY:clean
SERVER_BUILD_PATH ?= .
SRC_PATH ?= $(SERVER_BUILD_PATH)/../src
TAGET = dbmgr
MODULE = base.c db_task_insert.c db_task_update.c db_task_select.c
INC = -I$(SRC_PATH) -I$(COMMON) -I$(3RD) -I$(LIBEVENT_PATH)/include -I$(FLATCC_PATH)/portable \
	-I$(FLATCC_PATH)/reflection -I$(FLATCC_PATH)/support -I$(FLATCC_PATH) -I$(FBS)

LIB_PATH = -L$(FLATCC_PATH)/lib/

include $(SRC_PATH)/common.mk

$(TAGET): \
  $(foreach v, $(OBJECT), $(SRC_PATH)/$(v)) \
  $(foreach v, $(MODULE), $(SERVER_BUILD_PATH)/$(v))
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) $(LIB_PATH) $(INC)
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(TAGET)