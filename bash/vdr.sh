#!/bin/sh

killall vdr || (sleep 3 ; killall -9 vdr)

sudo /sbin/modprobe -r dvb-usb-opera
sudo /sbin/modprobe -r dvb-usb
sleep 1
sudo /sbin/modprobe dvb-usb-opera
sudo /sbin/modprobe dvb-usb

LANG="POSIX" esddsp /usr/bin/vdr --no-kbd \
	-s "killall vdr || (sleep 3 ; killall -9 vdr)" --no-kbd -l3 \
	-c /etc/vdr -v /home/haaner/mpg -L /usr/lib/vdr/plugins/ \
	-P "xineliboutput --local=sxfe --video=xshm --remote=none" 
	
#	-P sc -P femon -P streamdev-server 
#	-P "softdevice -vo xv:$1 -ao alsa:pcm=default#ac3=hw:0,1#" \
