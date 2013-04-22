#!/bin/sh

for a in $*
{ 
  echo " " 
  echo ====Domain: $a 
  echo --Zone transfer: 
  host -l $a 
  echo --Webserver: 
  host www.$a 
  echo --Nameservers: 
  host -t NS $a 
  echo --Mailservers: 
  host -t MX $a
}
