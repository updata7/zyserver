# !bin/bash

if [[ -e $1 ]]; then
	for args in $@
	do
		./3rd/flatcc/bin/flatcc -w $args -o ./fbs/
	done
else
	echo "use $0 file_name.fbs"
fi