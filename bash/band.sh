#!/bin/bash

I=0
INTERVALL=2

GREP=$(ps aux | grep "band.sh" | grep -v "grep" | wc -l)

if [ ${GREP} -eq 2 ] ; then

while true ; do

	if [ ${I} -eq 0 ] ; then
		PROC=$(cat /proc/net/dev | grep eth0 | sed -e "s/:/ /g")
		SBYTES_T=$(echo $PROC | sed -e "s/ \+/\t/g" | cut -f 10)
		SBYTES_R=$(echo $PROC | sed -e "s/ \+/\t/g" | cut -f 2 | sed -e "s/eth0://g")
		
		if [ "${SBYTES_T}x" = "x" ] ; then
			SBYTES_T=0
		fi

		if [ "${SBYTES_R}x" = "x" ] ; then
			SBYTES_R=0
		fi

		SBYTES=$((${SBYTES_T} + ${SBYTES_R}))
	fi

	I=$((${I}+${INTERVALL}))
	sleep ${INTERVALL}

	PROC=$(cat /proc/net/dev | grep eth0 | sed -e "s/:/ /g")
	EBYTES_T=$(echo $PROC | sed -e "s/ \+/\t/g" | cut -f 10)
	EBYTES_R=$(echo $PROC | sed -e "s/ \+/\t/g" | cut -f 2 | sed -e "s/eth0://g")

	if [ "${EBYTES_T}x" = "x" ] ; then
		EBYTES_T=0
	fi

	if [ "${EBYTES_R}x" = "x" ] ; then
		EBYTES_R=0
	fi
	
	EBYTES=$((${EBYTES_T} + ${EBYTES_R}))

	BYTES=$((($EBYTES - $SBYTES) / 1024))
	KBYTES=$(($BYTES / $I))

	echo -n "" > /home/haaner/.bnd_eth0
	
	for j in $(seq 1 $KBYTES) ; do 
	  ( echo "From stonedbody Fri Ede 23:42 9669";
	    echo "" ) >>  /home/haaner/.bnd_eth0
	done

	if [ ${I} -ge 1 ] ; then
		I=0
	fi
done

else
	echo -n "" > /home/haaner/.bnd_eth0
	killall band.sh
fi
#	REST=$(($BYTES - $KBYTES * 1024))
#	REST=$(($REST / 102)) 
#
#	echo "XXX" 
#	echo "$KBYTES.$REST kB/s" 
#	echo "XXX" 
#	| Xdialog --title "${eth0}" --smooth --no-button --infobox "" 2 20 0 
