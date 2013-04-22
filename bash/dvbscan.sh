#!/bin/sh

#dvbscan -U -o vdr -p -e 4 -t 1 /usr/share/dvb/dvb-s/Astra-19.2E > ~haaner/.vdr/channels.conf
dvbscan -U -5 -o zap -t 1 /usr/share/dvb/dvb-s/Astra-19.2E > ~haaner/zap_tv_all.conf
