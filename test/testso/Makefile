.PHONY:clean
CC = g++
CFLAGS = -O3 -std=c++0x -pg -D_DEBUG -g -Wall -Wno-write-strings
TAGET = test
MODULE = test.cpp
SERVER_BUILD_PATH = .
SOURCE = ../../source/
INC = -I$(SOURCE)
LIB_PATH = -L$(SOURCE)
LIBS = -lzyserver

$(TAGET): \
  $(foreach v, $(MODULE), $(SERVER_BUILD_PATH)/$(v))
	$(CC) $(CFLAGS) $^ -o $@ $(INC) $(LIB_PATH) $(LIBS)

clean:
	rm -f $(TAGET)