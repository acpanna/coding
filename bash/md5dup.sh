#!/bin/sh

if [ "$1"x = "x" ] ; then
	echo "Usage: $0 /path/to/dir"
	exit
fi

find "$1" -type d -empty -exec rm -rf "'{}'" ';'
find "$1" -type f -empty -exec rm -rf "'{}'" ';'
find "$1" -type d -empty -exec rm -rf "'{}'" ';'

rm md5.txt
find "$1" -type f -exec md5sum '{}' >> "md5.txt" ';' 
sort -n md5.txt > /tmp/md5.txt
