#!/bin/sh

export PATH=$PATH:/usr/local/bin:/sbin:/usr/sbin:/usr/local/sbin
source /etc/conf.d/net.ppp0

HOURS=$(nc localhost 1111 | awk -- '/Gesamt/ {FS=" ";print $2;exit}' | tr -d h)

if [ $HOURS -ge 120 ] && [ "$PROVIDER" = "t-online" ] ; then
	echo 'PROVIDER="freenet"' > /etc/conf.d/net.ppp0
	/etc/init.d/net.ppp0 restart
fi

if [ $HOURS -lt 120 ] && [ "$PROVIDER" = "freenet" ] ; then
	echo 'PROVIDER="t-online"' > /etc/conf.d/net.ppp0
	/etc/init.d/net.ppp0 restart
fi
