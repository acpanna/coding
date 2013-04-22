#!/bin/bash

killall joy2key &> /dev/null

case $1 in 	
		joy)
			joy2key Joy2Key -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -X -axis A B C D E F G H I J K L Z Z Z Z Z Z Z Z Z Z Z Z Z Z -buttons A B Z Y X Z L R 3 T 0 1 Up Right Down Left 2 &> /dev/null
		;;

		amarok)
			joy2key Amarok -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -X -axis A B C D 3270_Jump 3270_Jump G H I J 3270_Rule 3270_Rule Z Z Z Z Z Z Z Z Z Z Z Z Z Z -buttons 3270_Duplicate 3270_Play Z 3270_Play 3270_Duplicate Z 3270_Reset 3270_Setup 3270_Record 3270_Attn 0 1 Up Right Down Left 3270_Copy Z
		;;

		mplayer)
			sleep 1
			joy2key MPlayer2Key -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -X -axis L R U D slash slash B H J K asterisk asterisk Z Z Z Z Z Z Z Z Z Z Z Z Z Z -buttons O F Z Y M Z S E N C T I V W A X P Z
		;;

		vdr)
			sleep 3

			joy2key VDR -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -X -axis X X X X 3270_Reset 3270_Reset X X X X 3270_Setup 3270_Setup Z Z Z Z Z Z Z Z Z Z Z Z Z Z -buttons G R Z Y B Z 3270_Reset 3270_Setup Return space 0 Escape Up Right Down Left BackSpace Z
		;;

		*)
			rxvt -e xev -name "Xev2Key" &
			sleep 1 
			joy2key Xev2Key -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -thresh -16384 16384 -16384 16384 -X -axis A B C D E F G H I J K L Z Z Z Z Z Z Z Z Z Z Z Z Z Z -buttons A B Z Y X Z L R 3 T 0 1 Up Right Down Left 2 Z
		;;
esac
