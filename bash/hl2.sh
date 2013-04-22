#!/bin/bash

mount /home/haaner/.wine/drive_c/Programme
cd /home/haaner/.wine/drive_c/Programme/Valve/Steam

export DISPLAY=:0

xgamma -gamma 1.2
wine Steam.exe -width 1024 -height 768 -fullscreen -applaunch 220 -heapsize 512000 -novid +map_background none $@
xgamma -gamma 1

killall Steam.exe || killall -9 Steam.exe
killall wine || killall -9 wine
killall wineserver || killall -9 wineserver
killall explorer.exe || killall -9 explorer.exe

cd -
