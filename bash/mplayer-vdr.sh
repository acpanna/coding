#!/bin/bash

find . -name "*[0-9].vdr" -exec mplayer '{}' ';'
exit

clean_exit()
{
	trap '-' INT TERM

	echo "${CURR_NUMBER}" > ${LAST_FILE}
	echo -n "000" > /home/haaner/nfs/dvb/channel.txt

	umount /home/haaner/nfs

	killall mplayer
	killall mplayerd

	exit
}

trap clean_exit INT TERM

##################################################

APID=0
VPID=0
DPID=0

EPG1=""
EPG2=""
MODE=1

FREQ=1
POL="h"

CHANNEL=""
CURR_NUMBER=-1

NUMBER=0
SEL_NUMBER=0

REC_DIR=/home/haaner/nfs/mpg/
REC_FILE=""
LOCK_FILE=""

CHAN_FILE=$1
if [ "${CHAN_FILE}x" = "x" ] ; then
	CHAN_FILE="/home/haaner/nfs/channels.conf"
fi
		
LAST_FILE=/home/haaner/.mplayer/number
PLAY_FILE=/home/haaner/.mplayer/playlist
FULL_FILE=/home/haaner/.mplayer/fullscreen
EPG_FILE=/home/haaner/.mplayer/epg
TMP_FILE=/home/haaner/.mplayer/tmp
	
CTIME=""

CHAN_NR=0
CURR_NR=0
PLAY_NR=0

CURR_FILE=""

LEFTRIGHT="false"
SEEK_FACTOR=1

LAST=0

##################################################

load_file() 
{
	CHAN="$1"
	ZAP="$2"
	
	echo 'osd_show_text "Please wait ..." 10000' | nc localhost 1234

	i=1	
	while [ ! -f "/home/haaner/nfs/dvb/${CHAN}.mpg" ] ; do
	
		i=$((${i}+1))
		if [ ${i} -eq 10 ] ; then
		   #nr_0
			return
		fi
		
		sleep 1
	done

	if [ "${ZAP}"x = "true"x ] ; then
		echo 'zapfile /home/haaner/nfs/dvb/'${CHAN}'.mpg' | nc localhost 1234
	else
		echo 'loadfile "/home/haaner/nfs/dvb/'${CHAN}'.mpg"' | nc localhost 1234
	fi
		
	echo 'osd off' | nc localhost 1234
	echo 'loop -1' | nc localhost 1234
	echo 'osd on' | nc localhost 1234
	
	echo 'osd_show_text "'${NUMBER}' '${CHAN}'" 1000' | nc localhost 1234
}

check_time() 
{
	TIME=$(echo $1 | sed -e "s/ .*//g" -e "s/\t.*//g")
	
	STIME=$(echo ${TIME} | sed -e "s/--.*//g")
	ETIME=$(echo ${TIME} | sed -e "s/.*--//g")

	SHOUR=$(echo ${STIME} | sed -e "s/:.*//g")
	SMIN=$(echo ${STIME} | sed -e "s/.*://g")
	
	EHOUR=$(echo ${ETIME} | sed -e "s/:.*//g")
	EMIN=$(echo ${ETIME} | sed -e "s/.*://g")
	
	CHOUR=$(date "+%H")
	CMIN=$(date "+%M")

	# Startzeit <= Endzeit
	if [ ${SHOUR} -le ${EHOUR} -a ${CHOUR} -ge ${SHOUR} ] ; then
		if [ ${CHOUR} -gt ${SHOUR} -o \( ${CHOUR} -eq ${SHOUR} -a ${CMIN} -ge ${SMIN} \) ] ; then
			if [ ${CHOUR} -le ${EHOUR} -a \( ${CHOUR} -lt ${EHOUR} -o ${CMIN} -le ${EMIN} \) ] ; then
				return 1
			fi
		fi
	else # Startzeit > Endzeit
		if [ ${CHOUR} -gt ${SHOUR} -o \( ${CHOUR} -eq ${SHOUR} -a ${CMIN} -ge ${SMIN} \) ] ; then
			return 1
		fi
	fi

	return 0
}

epg()
{
	echo -n "" > ${EPG_FILE} &> /dev/null 
	cat /home/haaner/.mplayer/"${CHANNEL}.epg" 2> /dev/null | (

		while [ true ] ; do 

			read -t 1 PRG  

			if [ "${PRG}x" = "x" ] ; then 
				break
			fi

			check_time ${PRG}

			if [ $? -eq 1 ] ; then
				echo ${PRG} > ${EPG_FILE}
				read -t 1 PRG 
				echo ${PRG} >> ${EPG_FILE}
			fi


		done
	)

	EPG1=$(head -n1 ${EPG_FILE})
	EPG2=$(tail -n1 ${EPG_FILE})

#	if [ "${EPG1}x" = "x" ] ; then
#		EPG1="Keine EPG Infos!"	
#	fi
	
#	if [ "${EPG2}x" = "x" ] ; then
#		EPG2="Keine EPG Infos!"	
#	fi

	if [ "${EPG1}x" = "x" ] ; then
		if [ "${EPG2}x" != "x" ] ; then
			EPG1=${EPG2}
		else
			EPG1="Keine EPG Infos!"	
		fi
	fi

	echo 'osd_show_text "'${SEL_NUMBER}' '${CHANNEL}' | '${EPG1}'" 5000' | nc localhost 1234
}

set_chan_name()
{
	LINES=$(wc -l ${CHAN_FILE} | sed -e "s/\t.*//g" -e "s/ .*//g")
	
	if [ ${SEL_NUMBER} -le 0 ] ; then
		SEL_NUMBER=${LINES}
	fi

	if [ ${SEL_NUMBER} -gt ${LINES} ] ; then
		SEL_NUMBER=1
	fi
	
	NUMBER=${SEL_NUMBER}

	CHANNEL=$(tail -n $((${LINES}-${NUMBER}+1)) ${CHAN_FILE} | head -n 1)

	FREQ=$(echo $CHANNEL | cut -d ':' -f 2)
	POL=$(echo $CHANNEL | cut -d ':' -f 3)
	VPID=$(echo $CHANNEL | cut -d ':' -f 6)
	APID=$(echo $CHANNEL | cut -d ':' -f 7)
	DPID=$(echo $CHANNEL | cut -d ':' -f 8)
	
	CHANNEL=$(echo $CHANNEL | cut -d ':' -f 1 | sed -e "s/;.*//g")

	epg	
}

step()
{
	echo 'osd off' | nc localhost 1234
	echo 'loop 100' | nc localhost 1234
	echo 'osd on' | nc localhost 1234

	echo "pt_step $1"  | nc localhost 1234

	echo "vo_fullscreen ${MODE}" | nc localhost 1234

	echo "${MODE}" > ${FULL_FILE}

	echo 'osd off' | nc localhost 1234
	echo 'loop -1' | nc localhost 1234
	echo 'osd on' | nc localhost 1234

	echo 'osd_show_property_text "${filename}" 5000' | nc localhost 1234
}

left_load()
{
	CURR_NR=$((${CURR_NR}-1))
	if [ ${CURR_NR} -le 0 ] ; then
		CURR_NR=${PLAY_NR}
	fi

	CURR_FILE="$(head -n ${CURR_NR} ${PLAY_FILE} | tail -n 1)"
	echo 'osd_show_text "'$(basename "${CURR_FILE}")'" 1000' | nc localhost 1234

	LEFTRIGHT="true"
}

right_load()
{
	CURR_NR=$((${CURR_NR}+1))
	if [ ${CURR_NR} -gt ${PLAY_NR} ] ; then
		CURR_NR=1
	fi

	CURR_FILE="$(head -n ${CURR_NR} ${PLAY_FILE} | tail -n 1)"
	echo 'osd_show_text "'$(basename "${CURR_FILE}")'" 1000' | nc localhost 1234

	LEFTRIGHT="true"
}

#
#	ACT=$(ls -1 -u . | head -n1)
#	if [ "${ACT}x" != "$ ] ; then
#
#		NEW=${ACT}_$(date +"%y_%X")
#		mv ${ACT} "${NEW}"
#		
#		NR=$(echo ${ACT} | sed -e "s/_.*//g")
#		NUMBER=$((${NR}-1))
#		
	#CHANNEL=$(echo ${CHANNEL} | sed -e "s/ /_/g" -e "s/\t//g" -e "s/\./_/g")
	#CHANNEL=${NUMBER}_${CHANNEL}
#		echo $CHANNEL
#		echo $ACT ${NR} ${NUMBER}
#	fi
#
#	echo "audio_delay 0.1" 
#	echo "audio_delay -0.1" 

up_down_select()
{
	zap
}

up()
{
	SEL_NUMBER=$((${SEL_NUMBER}+1))
	set_chan_name 
}

down()
{
	SEL_NUMBER=$((${SEL_NUMBER}-1))
	set_chan_name
}

left()
{
	NUMBER=1
	SEL_NUMBER=1
	set_chan_name
	up_down_select
}

nr()
{
	if [ "${NUMBER}" != "$1" ] ; then
		SEL_NUMBER=$(echo "$1" | sed -e "s/[^0-9]*//g")
		
		if [ "${SEL_NUMBER}x" != "x" ] ; then
			if [ ${SEL_NUMBER} -le ${CHAN_NR} ] ; then
				NUMBER=${SEL_NUMBER}
				set_chan_name
				up_down_select
			fi
		fi
	fi
}

nr_0()
{
	if [ "${LAST}x" != "0x" ] ; then

		NEW=${LAST}
		LAST=${NUMBER}

		NUMBER=${NEW}
		SEL_NUMBER=${NEW}
		set_chan_name
		up_down_select

	else
		load_file "${CHANNEL}"
	fi
}

right()
{
	NUMBER=32
	SEL_NUMBER=32
	set_chan_name
	up_down_select
}

incr()
{
	LEFTRIGHT="false"
	SEL_NUMBER=${CURR_NUMBER}

	up
	up_down_select
}

decr()
{
	LEFTRIGHT="false"
	SEL_NUMBER=${CURR_NUMBER}
	
	down
	up_down_select
}

zap() 
{
	set_chan_name
	
	if [ ! -f /home/haaner/nfs/dvb/RECORDING ] ; then
		echo "${CHANNEL}" > /home/haaner/.mplayer/chan
		cp /home/haaner/.mplayer/chan /home/haaner/nfs/dvb/channel.txt
	else
		echo 'osd_show_text "Recording active!" 5000' | nc localhost 1234
	fi

	load_file "${CHANNEL}" "true"
		
	CURR_NUMBER=${NUMBER}
	SEL_NUMBER=${NUMBER}

	echo "vo_fullscreen ${MODE}" | nc localhost 1234

	echo "${MODE}" > ${FULL_FILE}

	CTIME=$(date "+%H:%M")
	
	#echo 'osd_show_text "'${CTIME}' | '${EPG1}'" 5000' | nc localhost 1234
	#echo 'osd_show_text "'${EPG2}'" 5000'
}

clean_start()
{
	mount /home/haaner/nfs

	echo '/home/haaner/guitar/gitarre_layla.mpg' > ${PLAY_FILE}
	
	find /home/haaner/mpg/ -type f -iname "*.mpg" >> ${PLAY_FILE}
	find /home/haaner/mpg/ -type f -iname "*.avi" >> ${PLAY_FILE}
	
	for i in $(seq 1 20) ; do 
		echo "dvd://${i}" >> ${PLAY_FILE}
	done

	PLAY_NR=$(wc -l  ${PLAY_FILE} | sed -e "s/ .*//g")
	CHAN_NR=$(wc -l  ${CHAN_FILE} | sed -e "s/ .*//g")

	SEL_NUMBER=$(cat ${LAST_FILE})
	NUMBER=${SEL_NUMBER}
	
	MODE=$(cat ${FULL_FILE})

	zap

	while [ true ] ; do
		menu
	done
}

menu()
{
	read -n 1 INPUT 

	echo ""
	
	if [ "${INPUT}x" = "Fx" ] ; then 
		echo "frame_step" | nc localhost 1234

	elif [ "${INPUT}x" = "Gx" ] ; then 
		echo "pause" | nc localhost 1234
	
	elif [ "${INPUT}x" = "0x" ] ; then 
		nr_0

	elif [[ ${INPUT} -ge 1 ]] && [[ ${INPUT} -le 9 ]] ; then
		ZAHL=${INPUT}
		echo 'osd_show_text "'${ZAHL}'" 1000' | nc localhost 1234
		read -n 1 -t 3 INPUT
		
		while [ $? -eq 0 ] ; do
			if [[ ${INPUT} -ge 0 ]] && [[ ${INPUT} -le 9 ]] ; then
				ZAHL=${ZAHL}${INPUT}
				echo 'osd_show_text "'${ZAHL}'" 1000' | nc localhost 1234
			fi
				
			read -n 1 -t 3 INPUT
		done

		nr ${ZAHL}
	
	elif [ "${INPUT}x" = "Cx" ] ; then 
		echo "osd" | nc localhost 1234

	elif [ "${INPUT}x" = "Zx" ] ; then
		
		if [ "${LEFTRIGHT}" = "true" ] ; then
			echo 'loadfile "'${CURR_FILE}'" 0' | nc localhost 1234
			echo 'seek -10000000' | nc localhost 1234
			LEFTRIGHT=false
		else
				echo "speed_set 1"  | nc localhost 1234
		fi

	elif [ "${INPUT}x" = "Xx" ] ; then 
		echo "speed_incr -1"  | nc localhost 1234

	elif [ "${INPUT}x" = "Yx" ] ; then 
		echo "speed_incr +1"  | nc localhost 1234


	elif [ "${INPUT}x" = "Ox" ] ; then
		up_down_select 
	elif [ "${INPUT}x" = "Ux" ] ; then 
		incr
	elif [ "${INPUT}x" = "Dx" ] ; then 
		decr
	elif [ "${INPUT}x" = "Lx" ] ; then 
		left
	elif [ "${INPUT}x" = "Rx" ] ; then 
		right
	elif [ "${INPUT}x" = "Px" ] ; then 

		ln "${REC_FILE}" "${LOCK_FILE}"
		ln "${REC_FILE}_id" "${LOCK_FILE}_id"

		echo 'osd_show_text "Recording started"' | nc localhost 1234


	elif [ "${INPUT}x" = "Bx" ] ; then 
		echo 'osd_show_text "<'${SEEK_FACTOR}'<"' | nc localhost 1234
		echo "seek -${SEEK_FACTOR}"  | nc localhost 1234

	elif [ "${INPUT}x" = "Hx" ] ; then 

		echo 'osd off' | nc localhost 1234
		echo 'loop 100' | nc localhost 1234
		echo 'osd on' | nc localhost 1234
		
		echo 'osd_show_text ">'${SEEK_FACTOR}'>"' | nc localhost 1234
		echo "seek +${SEEK_FACTOR}"  | nc localhost 1234
	
		echo 'osd off' | nc localhost 1234
		echo 'loop -1' | nc localhost 1234
		echo 'osd on' | nc localhost 1234

	elif [ "${INPUT}x" = "Jx" ] ; then 
		left_load
	
	elif [ "${INPUT}x" = "Kx" ] ; then 
		right_load

	elif [ "${INPUT}x" = "Mx" ] ; then 
		echo "mute"  | nc localhost 1234
	
	elif [ "${INPUT}x" = "Ex" ] ; then 
		echo 'osd_show_text "LAST set"' | nc localhost 1234
		LAST=${SEL_NUMBER}
	
	elif [ "${INPUT}x" = "Sx" ] ; then 

		SEEK_FACTOR=$((${SEEK_FACTOR}*10))
		if [ ${SEEK_FACTOR} -ge 100000 ] ; then
			SEEK_FACTOR=10
		fi
		
		echo 'osd_show_text "Seek-Faktor: '${SEEK_FACTOR}'"' | nc localhost 1234

	elif [ "${INPUT}x" = "Vx" ] ; then 
		echo "volume -1"  | nc localhost 1234
	
	elif [ "${INPUT}x" = "Wx" ] ; then 
		echo "volume 1"  | nc localhost 1234

	elif [ "${INPUT}x" = "Ix" ] ; then 
		echo 'osd_show_property_text "${filename}" 5000' | nc localhost 1234

#	elif [ "${INPUT}x" = "Ix" ] ; then 
#		echo 'osd_show_text "Recording-Mode enabled"';
#
#		read -n 1 INPUT 
#	
#		while [ "${INPUT}x" != "Ix" ] ; do
#
#			if [ "${INPUT}x" = "*x" ] ; then 
#				echo "volume 1" 
#			elif [ "${INPUT}x" = "/x" ] ; then 
#				echo "volume -1" 
#			elif [ "${INPUT}x" = "Bx" ] ; then 
#				echo "pause" 
#			fi
#
#			read -n 1 INPUT
#		done
#		
#		echo 'osd_show_text "Recording-Mode disabled"';
#		load_file ${CHANNEL}

	elif [ "${INPUT}x" = "Nx" ] ; then 
		MODE=$(((${MODE}+1)%2))

		echo "vo_fullscreen ${MODE}" | nc localhost 1234

		echo "${MODE}" > ${FULL_FILE}

	elif [ "${INPUT}x" = "Tx" ] ; then
		clean_exit
	fi
}

##################################################

killall xcompmgr &> /dev/null
killall xscreensaver &> /dev/null

(killall mplayerd || killall -9 mplayerd) &> /dev/null
(killall mplayer || killall -9 mplayer) &> /dev/null

/home/haaner/bin/mplayerd &> /dev/null &

clean_start 
clean_exit
