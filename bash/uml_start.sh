#!/bin/sh

DATE=$(date)
RUN=$(ps | grep uml_linux | grep -v grep)

cd /uml

if [ "${RUN}x" == "x" ] ; then

	echo "[ ${DATE} ] UMLs (re)started"
	tunctl -u 1000 -t tap0 &> /dev/null
	ifconfig tap0 192.168.0.254 &> /dev/null

	/uml/uml_linux umid=haaner ubd0=uml.fs rw ubd1=/dev/sda1 eth0=tuntap,tap0 mem=512M &> /uml/uml.log &

fi

#sed -e "s/search.*/domain foellmar.de/" /etc/resolv.conf > /gentoo/etc/resolv.conf
#/uml_linux umid=haaner ubd0=/var/lib/uml/swap rootfstype=hostfs rootflags=/gentoo rw eth0=tuntap,tap0 mem=128M > /var/log/uml.log &
