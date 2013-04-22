#!/bin/sh

mkdir /tmp/dvb &> /dev/null

wget -O /tmp/dvb/seca http://www.rdi-files.com/seca2.php 

grep -A 33 -i ">ORF<" /tmp/dvb/seca > /tmp/dvb/orf
grep -A 33 -i ">Premiere<" /tmp/dvb/seca > /tmp/dvb/premiere
grep -A 33 -i ">D+<" /tmp/dvb/seca > /tmp/dvb/d+
grep -A 33 -i ">D+ (new ID)<" /tmp/dvb/seca > /tmp/dvb/d+_new
grep -A 33 -i ">Kabel Deutschland<" /tmp/dvb/seca > /tmp/dvb/kabel

for i in orf premiere d+ d+_new kabel ; do

	ID=$(grep -i "id" /tmp/dvb/$i | head -n1 | sed -e 's/.*8888">//g' -e 's/<.*//g' -e 's/ //g')
	BLUE=$(grep -i "blue" /tmp/dvb/$i | head -n1 | sed -e 's/.*blue>//g' -e 's/<br>//g' -e 's/<.*//g' -e 's/ //g')
	GREEN=$(grep -i "green" /tmp/dvb/$i | head -n1 | sed -e 's/.*green">//g' -e 's/<br>//g' -e 's/<.*//g' -e 's/ //g')

  	NR=$(sed -e "s/key/\nkey/g" -e "s/Key/\nkey/g" -e "s/<\//\n<\//g" /tmp/dvb/seca  | grep "key.*&nbsp;" | grep -i "${i}" | cut -d ';' -f 2 | sed -e "s/\&.*//g" | head -n1)
	
	if [ "${NR}x" = "x" ] ; then
		NR="00"
	fi

	echo "N $ID $NR $BLUE"
	
	if [ "${GREEN}x" != "x" ] ; then
		echo "N $ID M1 $GREEN"
	fi

	if [ "${ID}" = "0501" ] ; then
		   echo "N 0503 $NR $BLUE"
		   echo "N 0503 M1 $GREEN"
		   echo "N 0505 $NR $BLUE"
		   echo "N 0505 M1 $GREEN"
		   echo "N 0511 $NR $BLUE"
		   echo "N 0511 M1 $GREEN"
	fi
done
