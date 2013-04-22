#!/bin/sh

if [ "$1xx" == "onxx" ] ; then
	sudo modprobe snd-hda-intel
	sudo modprobe snd-pcm-oss
	sudo modprobe snd-mixer-oss 	
	sleep 2
	/usr/sbin/alsactl -f /etc/asound.state restore
else
	for i in snd-hda-intel \
		snd_hda_codec \
		snd_pcm_oss \
		snd_mixer_oss \
		snd_pcm	\
		snd_timer \
		snd \
		soundcore \
		snd_page_alloc ; do
		
		sudo rmmod $i
	done
fi
