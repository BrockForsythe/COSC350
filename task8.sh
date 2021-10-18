#!/bin/bash

if [ $# -lt 1 ]; then
	echo "Enter an integer"
	exit 1
fi

input=$1
sum=0
while [ $input -gt 1 ];do
	nextChar=`expr $input \% 10`
	sum=`expr $sum + $nextChar`
	input=`expr $input / 10`
done
echo "Sum of args is $sum"
exit 0
