#!/bin/bash

## declare an servers variable
declare -a servers=("dbmgr" "globalmgr" "gameserver")

for i in "${servers[@]}" ;
do
	echo "start server $i"
	gnome-terminal -t "$i" --working-directory=$(pwd)/$i -e './server_start.sh'
done
