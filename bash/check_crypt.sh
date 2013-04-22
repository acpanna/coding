#!/bin/sh

MOUNT=$(mount | grep crypt)
WHO=$(w | grep haaner)

if [[ "${MOUNT}x" != "x" ]] && [[ "${WHO}x" = "x" ]] ; then
	umount ~/crypt
fi
