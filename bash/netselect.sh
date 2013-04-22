#!/bin/bash

/usr/local/sbin/net.sh home &> /dev/null
AT_HOME=$(ping -c5 192.168.0.1 | grep ttl)
if [ "${AT_HOME}"x != ""x ] ; then
	exit
fi

/usr/local/sbin/net.sh gok &> /dev/null
AT_HOME=$(ping -c5 192.168.1.1 | grep ttl)
if [ "${AT_HOME}"x != ""x ] ; then
	exit
fi

#/usr/local/sbin/net.sh work &> /dev/null
#AT_WORK=$(ping -c5 132.180.198.254 | grep ttl)
#AT_WORK=(arp -n | grep 132.180.198.254)
#if [ "${AT_WORK}"x != ""x ] ; then
#	exit;
#fi
#
#/usr/local/sbin/net.sh campus &> /dev/null
#AT_CAMPUS=$(ping -c5 132.180.198.254 | grep ttl)
#if [ "${AT_CAMPUS}"x != ""x ] ; then
#	exit;
#fi

#/usr/local/sbin/wlan.sh home &> /dev/null
/usr/local/sbin/wlan.sh gok &> /dev/null
AT_HOME=$(ping -c5 192.168.0.1 | grep ttl)
if [ "${AT_HOME}"x != ""x ] ; then
	exit
fi

/usr/local/sbin/wlan.sh iphone &> /dev/null
AT_HOME=$(ping -c5 192.168.0.1 | grep ttl)
if [ "${AT_HOME}"x != ""x ] ; then
	exit
fi

#/usr/local/sbin/wlan.sh work &> /dev/null
#AT_WORK=$(ping -c5 132.180.198.254 | grep ttl)
#if [ "${AT_WORK}"x != ""x ] ; then
#	exit;
#fi

/usr/local/sbin/wlan.sh campus &> /dev/null
