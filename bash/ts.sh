#!/bin/sh

esddsp aoss /opt/bin/TeamSpeak "cstrike.foellmar.de?nickname=Problemloeser?loginname=Problemloeser?password=letmein"

killall TeamSpeak.bin || killall -9 TeamSpeak.bin
