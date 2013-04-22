#!/bin/sh

for i in /dev/sda /dev/sdb /dev/hda /dev/hdb ; do
  	smartctl --smart=on --offlineauto=on --saveauto=on $i
	smartctl $i --all
done
