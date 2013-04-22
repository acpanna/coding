#!/bin/sh

psi &
sleep 1

id=$(xwininfo -name "Psi" | grep "Psi" | sed -e "s/.*://g" -e "s/\".*//g")
xkill -id ${id}
