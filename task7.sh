#!/bin/bash
 echo "Enter a number"
read input
temp=$input
fact=1
while [ $input -gt 0 ];do
	fact=`expr $input \* $fact`
	input=`expr $input \- 1`
done

echo "Factorial of $temp is $fact"
exit 0
