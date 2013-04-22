#!/bin/sh

emerge -1 portage

emerge -euND world 
while [ $? == 1 ]; do
	emerge --resume --skipfirst 
done
