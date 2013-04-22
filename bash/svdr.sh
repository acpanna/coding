#!/bin/sh

x=$1
x=${x##*-} # alles vorm Minus wegschneiden

case $x in 	
	
	"c") 
		if [ "$2"x == ""x ] ; then
			ssh haaner@grisu /usr/local/bin/svdrpsend.pl -p 2001 LSTC \
			| grep -v "grisu" \
			| sed -e "s/250-//g" -e "s/250 //g" -e "s/;.*//g" -e "s/:.*//g"

			ssh haaner@grisu /usr/local/bin/svdrpsend.pl -p 2001 CHAN \
			| grep "250 "  \
			| sed -e "s/250 /\nActual channel: /g"
		else
			ssh haaner@grisu /usr/local/bin/svdrpsend.pl -p 2001 CHAN $2
		fi
	;;
	
	"r") 
		ssh haaner@grisu /usr/local/bin/svdrpsend.pl -p 2001 HITK Record
	;;

	"l")
  		echo "Recordings:"
  		echo "-----------"
		ssh haaner@grisu /usr/local/bin/svdrpsend.pl -p 2001 LSTR
  		echo ""
  		echo "Timers:"
  		echo "-------"
		ssh haaner@grisu /usr/local/bin/svdrpsend.pl -p 2001 LSTT
	;;
	
	"x") 
		ssh haaner@grisu /usr/local/bin/svdrpsend.pl -p 2001 "$2"
	;;

	"e")
		ssh haaner@grisu /usr/local/bin/svdrpsend.pl -p 2001 LSTE "$2" | less 
	;;

	"n")
		if [ "$2"x == ""x ] ; then
			echo "Usage: $(basename $0) -n Ch Date	Start End  Name"
			echo "       $(basename $0) -n 23 $(date +%Y-%m-%d) $(date +%H%M)  0000 AufnahmeXY"
		else
			STR="1:$2:$3:$4:$5:    50:99    :$6:"
			ssh haaner@grisu /usr/local/bin/svdrpsend.pl -p 2001 NEWT "${STR}"
		fi
	;;

	"u")
		if [ "$2"x == ""x ] ; then
			$0 -l
			echo ""
			echo "Usage: $(basename $0) -u Status:Ch:Date:Start:End:50:99:Name:"
		else
			ssh haaner@grisu /usr/local/bin/svdrpsend.pl -p 2001 UPDT "$2"
		fi
	;;

	"d")
		if [ "$2"x == ""x ] ; then
			echo "Usage: Delete the timer with the number x:"
			echo "       $(basename $0) -d x"
		else
			ssh haaner@grisu /usr/local/bin/svdrpsend.pl -p 2001 DELT "$2"
		fi
	;;

	*)
		echo "-c  change channel, -r  record current channel, -l  list timers, -n  new timer, -d  delete timer, -e  print epg for the channel"
	;;
esac
