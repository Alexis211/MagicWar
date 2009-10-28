#!/bin/sh

for i in `ls | grep cpp`; do
	a=`echo $i | egrep -o ^[a-z]+`
	gcc -o $a $i -lstdc++
done
