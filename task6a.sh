#!/bin/sh
#task6.sh

echo "Enter a number that is odd and greater than 3: "
read input
if [ `expr $input % 2` -eq 0 ] || [ $input -lt 3 ];then  #Can also use $(( )) instead of expr
	echo "Invalid number"
	exit 1
fi

numSpace=`expr $input / 2`
starCount=1

for i in $(seq 0 $numSpace);do
	for j in $(seq 1 $numSpace);do
		echo -n " "
	done
	for k in $(seq 1 $starCount);do
		echo -n "*"
	done
	starCount=`expr $starCount + 2`
	numSpace=`expr $numSpace - 1`
	echo
done
starCount=`expr $input \- 2`
numSpace=1
for i in $(seq $starCount -1 1);do
	for j in $(seq $numSpace -1 1);do
		echo -n " "
	done
	for k in $(seq $starCount -1 1);do
		echo -n "*"
	done
	starCount=`expr $starCount \- 2`
	numSpace=`expr $numSpace + 1`
	echo
done
exit 0