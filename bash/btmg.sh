#!/bin/sh

PLAYER=$(qstat -hls cstrike -P | grep BtmG)
CSTRIKE=$(ps aux | grep cstrike | grep -v grep)

while true ; do
	if [ "${PLAYER}x" != "x" ] ; then
		if [ "${CSTRIKE}x" == "x" ] ; then
			/home/haaner/bin/hl.sh +connect cstrike.hirnfilter.de:27015 +rcon_password letmein

			break
		fi
	fi

	sleep 60
done
