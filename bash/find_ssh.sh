#!/bin/sh

i=0
j=$1

if [ "${j}x" = "x" ] ; then j=1 ; fi

while [ "$i" != "$j" ] ; do
	GREP=""

	while [ "${GREP}x" == "x" ] ; do 
		GREP=$(sudo nmap -sS -iR 1 -PS22 -p 22 --max-retries 3) 
		GREP=$(echo $GREP | grep " open") 
	done 
	
	GREP=$(echo $GREP | sed -e "s/.* ports on //g")
	echo -n $GREP | sed -e "s/:.*//g" -e "s/.*(//g" -e "s/).*//g"
	echo "" | nc -w 3 $GREP 22


	i=$(($i+1))
done
