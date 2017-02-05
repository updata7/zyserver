.PHONY:all gameserver dbmgr clean_gameserver clean_dbmgr clean

all:
	make -C gameserver
	make -C dbmgr
	make -C globalmgr

gameserver:
	make -C gameserver

dbmgr:
	make -C dbmgr

globalmgr:
	make -C globalmgr

clean_gameserver:
	make clean -C gameserver

clean_dbmgr:
	make clean -C dbmgr

clean_globalmgr:
	make clean -C globalmgr
	
clean:
	make clean -C gameserver
	make clean -C dbmgr
	make clean -C globalmgr