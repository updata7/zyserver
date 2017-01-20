.PHONY:all gamesv dbmgr clean_gamesv clean_dbmgr clean

all:
	make -C gamesv
	make -C dbmgr

gamesv:
	make -C gamesv

dbmgr:
	make -C dbmgr

clean_gamesv:
	make clean -C gamesv

clean_dbmgr:
	make clean -C dbmgr

clean:
	make clean -C gamesv
	make clean -C dbmgr