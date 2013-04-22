#!/bin/sh

function usage() {
	echo "Usage: $1 title sender start-time end-time"
}

if [ $# != 4 ] ; then
  usage $0
  exit
fi  

TITLE=$1
SENDER=$2
START=$3
END=$4

GREP=$(grep "${SENDER}" /etc/dvb_channels.conf)

if [ "${GREP}x" != "x" ] ; then
	
	if [ "${TITLE}x" = "x" ] ; then
		TITLE="${SENDER}"
	fi 
	
	echo "${TITLE}|${SENDER}|${START}|${END}" >> /home/haaner/dvb/timer.txt
	
	#echo 'touch /home/haaner/dvb/RECORDING ; echo "'${SENDER}'" > /home/haaner/dvb/channel.txt' | at ${START}
	#echo 'echo "000" > /home/haaner/dvb/channel.txt ; rm /home/haaner/dvb/RECORDING ; mv "/home/haaner/dvb/'${SENDER}'" "/home/haaner/mpg/'${TITLE}'"' | at ${END}

else
	echo "The sender ${SENDER} is invalid!"	
  	usage $0
fi
