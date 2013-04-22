#!/bin/sh

CAP=$(cat /proc/acpi/battery/BAT0/state  | grep "remain" | sed -e "s/[a-zA-Z]*.*: *//g" -e "s/ .*//g")

echo ${CAP}

if [ ${CAP} -le 10000 ] ; then
	setterm -blength 110
	echo -e "\a" > /dev/console
	sleep 1
	setterm -blength 110
	echo -e "\a" > /dev/console
	sleep 1
	setterm -blength 110
	echo -e "\a" > /dev/console
	sleep 1
	setterm -blength 1100
	echo -e "\a" > /dev/console
fi

setterm -blength 0
