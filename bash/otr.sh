#!/bin/sh

otrdecoder -e ge@hirnfilter.de -p opensource -i $1

AVI=${1%.otrkey}

otrcut.sh -i ${AVI} 
