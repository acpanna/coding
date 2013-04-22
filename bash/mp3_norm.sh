#!/bin/sh

find ~/mp3 -type f -iname "*.mp3" -exec mp3gain -a -k '{}' ';'
