#!/bin/sh

mlterm -name "Sancho" -e ssh haaner@foellmar.de &

sleep 3

konqueror http://localhost:4080 &
sancho-bin
