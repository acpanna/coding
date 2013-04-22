#!/bin/sh

PS=$(ps aux | grep rasa | grep -v grep)

if [ "${PS}x" = "x" ] ; then
	ssh -p 65535 root@localhost /sbin/shutdown $*
else
	/usr/bin/Xdialog --wrap --screen-center --allow-close --msgbox "Bist du daemlich? Ich muss doch wach bleiben ... ;)\n\n${PS}" 20 120
fi
