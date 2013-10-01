#!/bin/bash

temp_app="/tmp/$(basename $0).$$.app"
osacompile -e "display dialog \"$1\"" -x -o $temp_app
open $temp_app
