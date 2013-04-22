#!/bin/sh

W=1024
H=768

DIR=$1

if [ "${DIR}x" = "x" ] ; then
	DIR=/home/haaner/pics/erotic
fi

cd ${DIR}

if [ -f slideshow.avi ] ; then
	mplayer -idx slideshow.avi
	exit
fi

rm -rf extended
mkdir extended

find . -maxdepth 1 -type f -iname "*.jpg" -exec convert -scale ${W}x${H} -extent ${W}x${H} -antialias -enhance -quality 100 '{}' extended/'{}' ';'

cd extended

mencoder mf://*.jpg -mf w=${W}:h=${H}:fps=0.3:type=jpg -ofps 25 -ffourcc XVID -ovc lavc -lavcopts vcodec=mpeg4:vbitrate=9800:aspect=1.50:vhq:keyint=15 -o ../slideshow.avi -audiofile /home/haaner/mp3/1/10\ cc/Bloody\ Tourists/Dreadlock\ Holiday.mp3 -oac copy -vf scale=${W}:${H} -sws 2 

#encoder -mf w=${W}:h=${H}:type=jpg:fps=0.3 -ofps 25 -ffourcc XVID -ovc lavc -lavcopts vcodec=mpeg4:vbitrate=9800:aspect=1.50:vhq:keyint=15 -audiofile /home/haaner/mp3/1/10\ cc/Bloody\ Tourists/Dreadlock\ Holiday.mp3 -oac copy -vf scale=${W}:${H} -sws 2 -o ~haaner/mpg/erotic/misc/slideshow.avi mf://*.jpg

mplayer ../slideshow.avi
