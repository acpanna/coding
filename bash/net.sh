#!/bin/sh

killall vpnc
killall dhcpcd

sleep 3

case $1 in 	
		home)
			echo "Switching to home profile"
			ifconfig eth0 down
			ifconfig eth0 192.168.0.6 netmask 255.255.255.0
	
			route add -net default gw 192.168.0.1
			cp /etc/resolv.conf.home /etc/resolv.conf
			;;
		gok)
			echo "Switching to gok profile"
			ifconfig eth0 down
			ifconfig eth0 192.168.1.234 netmask 255.255.255.0
	
			route add -net default gw 192.168.1.1
			cp /etc/resolv.conf.gok /etc/resolv.conf
			;;
		
		work)
			echo "Switching to work profile"
			ifconfig eth0 down
			ifconfig eth0 132.180.198.44 netmask 255.255.255.0
			
			route add -net default gw 132.180.198.254
			cp /etc/resolv.conf.work /etc/resolv.conf
			;;

		campus)
			echo "Switching to campus profile"
			ifconfig eth0 down
			ifconfig eth0 0.0.0.0
			ifconfig eth0 hw ether 7cc5373cd764

			dhcpcd eth0
			vpnc --enable-1des --username s1hevoge campus
			#vpnc --enable-1des --username btmd14 campus
			;;
		*)
		 	echo "Usage: $0 home|campus|woh|work"
			;;
esac
