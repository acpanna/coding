#!/bin/sh

NR=$(cat ~/.zap)
if [ "${NR}"x = ""x ] ; then
	NR=0
fi

if [ "$1"x = "up"x ] ; then
	NR=$((${NR}+1))
else
	NR=$((${NR}-1))
fi

echo "${NR}" > .zap

cd ~/nfs

CHAN=$(head -n "${NR}" channels.conf | tail -n1 | sed -e "s/:.*//g" -e "s/;.*//g" -e "s/,.*//g")

echo "${CHAN}" > channel.txt
echo "Switching to ${CHAN} -- Please wait ..."

sleep 30

#killall mplayer
mplayer -fs "dvb/${CHAN}.mpg"
