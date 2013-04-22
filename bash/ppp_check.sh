#!/bin/sh

PPP=$(ps aux | grep pppd | grep -v grep)

if [ "${PPP}x" = "x" ] ; then 
	/etc/init.d/net.ppp0 stop
	/etc/init.d/net.ppp0 zap
	/etc/init.d/net.ppp0 start

	/etc/init.d/svscan stop
	/etc/init.d/svscan zap
	/etc/init.d/svscan start
fi
