#!/bin/sh

sudo modprobe vboxdrv
sudo modprobe vboxnetadp
sudo modprobe vboxnetflt

LD_LIBRARY_PATH=/opt/VirtualBox:${LD_LIBRARY_PATH} 
export LD_LIBRARY_PATH
VirtualBox
