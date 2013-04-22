#!/bin/sh

if [ "$1" == "-u" ] ; then
	echo "SELECT ip FROM hacking.ssh" |  mysql -u hacking | $0
	exit
fi

for i in $(cat $1) ; do
	j=$(echo "" | nc -q 2 -w 15 $i 22 2>&1 | grep "^SSH" | sed -e "s/\n.*//g")
	
	if [ "${j}x" != "x" ]; then 
		echo "DELETE FROM hacking.ssh WHERE ip=\"$i\";" | mysql -u hacking 
		echo "INSERT INTO hacking.ssh VALUES(\"$i\", \"$j\");" | mysql -u hacking 
	fi  
done
