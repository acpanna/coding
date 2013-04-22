#!/bin/sh

function stream_it() {

	LINE=$(grep "^$1:" /etc/dvb_channels.conf)

	if [ "${LINE}x" = "x" ] ; then
		LINE=$(grep "$1" /etc/dvb_channels.conf)
		if [ "${LINE}x" = "x" ] ; then
			echo "$1 not found!"
			exit
		fi
	fi

	FRQ=$(echo ${LINE} | cut -f2 -d ':')
	POL=$(echo ${LINE} | cut -f3 -d ':' | tr '[:lower:]' '[:upper:]')
	SYM=$(echo ${LINE} | cut -f5 -d ':')
	AID=$(echo ${LINE} | cut -f6 -d ':')
	VID=$(echo ${LINE} | cut -f7 -d ':')
	
	echo ""
	echo "$1 [ AID: ${AID}, VID: ${VID} ]"
	echo ""

	#dvbstream -c0 -f ${FRQ} -s ${SYM} -p ${POL} -v ${VID}:1 -a ${AID}:2 -o - | cat > "/home/haaner/dvb/$1.mpg" 
	#dvbstream -c0 -f ${FRQ} -s ${SYM} -p ${POL} -v ${VID} -a ${AID} -o - | ts2ps ${VID} ${AID} > "/home/haaner/dvb/$1.mpg" 

	dvbstream -c0 -f ${FRQ} -s ${SYM} -p ${POL} -o - 8192 | ts2ps ${VID} ${AID} > "/home/haaner/dvb/$1.mpg" 
}

########################################################

#	/usr/local/sbin/sasc-ng -j 0:1 -l /var/log/sasc-ng.log &> /dev/null &
#	sleep 1

stream_it "$1"
