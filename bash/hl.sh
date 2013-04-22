#!/bin/bash

mount /home/haaner/.wine/drive_c/Programme
cd /home/haaner/.wine/drive_c/Programme/CStrike

xgamma -gamma 1.2
wine cstrike.exe -console -toconsole -heapsize 512000 -nojoy -noipx -novid -nocrashdialog -doublebuffer -width 1024 -height 768 -fullscreen $@
xgamma -gamma 1

killall cstrike.exe || killall -9 cstrike.exe
killall wine || killall -9 wine
killall wineserver || killall -9 wineserver
killall explorer.exe || killall -9 explorer.exe

cd -
