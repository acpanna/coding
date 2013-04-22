#!/bin/sh

DIR=$1

if [ "${DIR}x" = "x" ] ; then
	DIR=/home/haaner/pics/erotic
fi

cd ${DIR}
mkdir scaled

find . -maxdepth 1 -type f -exec convert -scale 1600x900 -antialias -enhance -quality 100 '{}' scaled/'{}' ';'
cd -
