#!/bin/sh

hex=$1
hex=${hex#*x}
hex="0x${hex}"

echo $((${hex}))
