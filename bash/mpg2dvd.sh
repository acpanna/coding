#!/bin/bash

cd ~

output_file_directory="~/dvd"
input_file_one="$1"

cat $input_file_one > dvd.avi

mencoder -o finalmovie.avi -noidx -oac copy -ovc copy dvd.avi
ffmpeg -i finalmovie.avi -y -target pal-dvd -sameq -aspect 4:3 finalmovie.mpg
#ffmpeg -i finalmovie.avi -y -target ntsc-dvd -sameq -aspect 16:9 finalmovie.mpg

dvdauthor --title -o dvd -f finalmovie.mpg
dvdauthor -o dvd -T

mkisofs -dvd-video -o dvd.iso dvd/

rm finalmovie.* dvd.avi
echo "Now burn ${PWD}/dvd.iso to a DVD"
