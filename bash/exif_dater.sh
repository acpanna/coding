#!/bin/sh

DATE=$(exiftags "$1" 2>&1 | grep "Image Created:" | sed -e "s/.*: //g" -e "s/:/-/" -e "s/:/-/")

touch "$1" -d "${DATE}" -m
