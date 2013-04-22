#!/bin/sh

killall vpnc
killall dhcpcd

sleep 3

for i in eth0 eth1 wlan0 ; do
	route del -net default dev $i
	route del -net 192.168.0.0/24 dev $i
done

if [ "$2"x == ""x ] ; then
	DEV="wlan0"
else
	DEV=$2
fi

case $1 in 	
		home)
			echo "Switching to home profile"
			
			ifconfig eth0 down
			ifconfig ${DEV} down

			iwconfig ${DEV} mode managed
			iwconfig ${DEV} essid "BirdWorX"
			iwconfig ${DEV} key 3025-255a-2b61-753e-6af1-48d1-e4
			#3025255a2b61753e6af148d1e4
			
			ifconfig ${DEV} 192.168.0.7 netmask 255.255.255.0
	
			route add -net default gw 192.168.0.1
			cp /etc/resolv.conf.home /etc/resolv.conf
			;;
	
		gok)
			echo "Switching to gok profile"
			
			ifconfig eth0 down
			ifconfig ${DEV} down

			iwconfig ${DEV} mode managed
			iwconfig ${DEV} essid "BirdWorX"
			iwconfig ${DEV} key 3025-255a-2b61-753e-6af1-48d1-e4
			
			ifconfig ${DEV} 192.168.0.7 netmask 255.255.255.0
			route add -net default gw 192.168.0.1
			cp /etc/resolv.conf.gok /etc/resolv.conf
			;;
	
		iphone)
			echo "Switching to iphone profile"
			
			ifconfig eth0 down
			ifconfig ${DEV} down

			iwconfig ${DEV} mode ad-hoc
			iwconfig ${DEV} essid "HaanNet"
			iwconfig ${DEV} key affeaffeae
		
			ifconfig ${DEV} 0.0.0.0

			ifconfig ${DEV} down
			ifconfig ${DEV} up

			sleep 5

			dhcpcd ${DEV}
			;;
		
		campus)
			echo "Switching to campus profile"
			
			ifconfig eth0 down
			ifconfig ${DEV} down

			iwconfig ${DEV} mode managed
			iwconfig ${DEV} essid "wlanubt"
			iwconfig ${DEV} key 0123456789
			
			ifconfig ${DEV} 0.0.0.0

			ifconfig ${DEV} down
			ifconfig ${DEV} hw ether 7cc5373cd763
			ifconfig ${DEV} up

			dhcpcd ${DEV}
			#vpnc --enable-1des --username btmd14 campus
			vpnc --enable-1des --username s1hevoge@stmail campus
			;;

		office)
			echo "Switching to office profile"
			
			ifconfig eth0 down
			ifconfig ${DEV} down

			iwconfig ${DEV} mode managed
			iwconfig ${DEV} essid "dmi"
			
			ifconfig ${DEV} 0.0.0.0

			ifconfig ${DEV} down
			ifconfig ${DEV} hw ether 000347b49a4b
			ifconfig ${DEV} up

			dhcpcd ${DEV}
			;;

		geogebra)
			echo "Switching to geogebra profile"
			
			ifconfig eth0 down
			ifconfig ${DEV} down

			iwconfig ${DEV} mode managed
			iwconfig ${DEV} essid "GeoGebra"
			
			ifconfig ${DEV} 0.0.0.0
			ifconfig ${DEV} up

			dhcpcd ${DEV}
			;;

		*)
		 	echo "Usage: $0 home|campus"
			;;
esac
