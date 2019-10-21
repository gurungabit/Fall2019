#!/bin/bash
go=0
while [ $go ]; do
	echo Enter one of the following action or press CTRL-D to exit.
	echo C - create a new course record
	echo R - read an existing course record
	echo U - upate an exsisting course record
	echo D - delete an existing course record
	echo E - update enrolled student count record
	echo T - show total course count
if ! read choice; then
	# got EOF
	break
fi
	declare -u fchoice=$choice
		if [ $fchoice == "C" ]
		then
			./create.bash
		elif [ $fchoice == "R" ]
		then
			./read.bash
		elif [ $fchoice == "U" ]
		then
			./update.bash
		elif [ $fchoice == "D" ]
		then
			./delete.bash
		elif [ $fchoice == "E" ]
		then
			./enroll.bash
		elif [ $fchoice == "T" ]
		then
			./total.bash
		else
			echo "Error: invalid option"
		fi
done 
