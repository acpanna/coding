#!/bin/sh

cd /home/haaner/

while [ true ] ; do
	rm dvb/channel.txt
	
	while [ ! -f "dvb/channel.txt" ] ; do

		if [ -f "dvb/timer.txt" ] ; then
	
			cat "dvb/timer.txt" | while read line ; do

				TITLE=$(echo "${line}" | cut -f 1 -d '|')
				SENDER=$(echo "${line}" | cut -f 2 -d '|')
				START=$(echo "${line}" | cut -f 3 -d '|')
				END=$(echo "${line}" | cut -f 4 -d '|')

				echo 'touch dvb/RECORDING ; echo "'${SENDER}'" > dvb/channel.txt' | at ${START}
				echo 'rm dvb/RECORDING ; echo "000" > dvb/channel.txt ; mv dvb/"'${SENDER}'.mpg" dvb/"'${TITLE}'.mpg"' | at ${END}
		
			done
			rm "dvb/timer.txt"
		fi
			
		sleep 1 
	done 

	killall -9 ts2ps
	killall -9 dvbstream
	
	CHANNEL="$(cat dvb/channel.txt)" 
	if [ "${CHANNEL}" != "000" ] ; then
		bin/dvbstream.sh "${CHANNEL}" &
	fi

done
