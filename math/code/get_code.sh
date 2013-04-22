#!/bin/sh

#PRB2LAT="${HOME}/rasa/prb2lat"
#CODE2PRB="${HOME}/rasa/code2prb"

TMPDIR="~/.codes/"

par[1]=$1
par[2]=$2
par[3]=$3
par[4]=$4

for i in $(seq 1 4) ; do
	OUT=$(echo ${par[$i]} | sed -e "s/.*q=//g" -e "s/.*=.*//g")
	if [ "${OUT}"x != ""x ] ; then
		q=${OUT}
		continue;
	fi

	OUT=$(echo ${par[$i]} | sed -e "s/.*k=//g" -e "s/.*=.*//g")
	if [ "${OUT}"x != ""x ] ; then
		k=${OUT}
		continue;
	fi

	OUT=$(echo ${par[$i]} | sed -e "s/.*n=//g" -e "s/.*=.*//g")
	if [ "${OUT}"x != ""x ] ; then
		n=${OUT}
		continue;
	fi

	OUT=$(echo ${par[$i]} | sed -e "s/.*d=//g" -e "s/.*=.*//g")
	if [ "${OUT}"x != ""x ] ; then
		d=${OUT}
		continue;
	fi
done

if [[ "${q}"x != ""x ]] && [[ "${k}"x != ""x ]] \
	&& [[ "${n}"x != ""x ]] && [[ "${d}"x != ""x ]] ; then

	rm -rf ${TMPDIR} &> /dev/null
	mkdir -p ${TMPDIR} && cd ${TMPDIR} 

	echo "Fetching code files for: q = $q, k = $k, n = $n, d = $d"

	wget --no-clobber --force-html http://www.mathe2.uni-bayreuth.de/cgi-bin/axel/codedb?printqknd+$q+$k+$n+$d &> /dev/null

	wget --no-clobber --force-html --base=http://www.mathe2.uni-bayreuth.de/cgi-bin/axel/ -i codedb?printqknd+$q+$k+$n+$d  &> /dev/null

	for i in $(ls codedb?groupcodeid+*+$q+$k) ; do  
		wget --no-clobber --force-html --base=http://www.mathe2.uni-bayreuth.de/cgi-bin/axel/ -i ${i} &> /dev/null
	done

	for GROUP in $(ls codedb?groupid+*+$q+$k) ; do

		ORBIT=$(awk '$1 == "orbitsizes", $1 == "sorted"' ${GROUP})
		ORBIT=$(echo $ORBIT | sed -e "s/ sort.*//g" -e "s/.*\[/\[/g" -e "s/ //g")
		LINES=$(cat ${GROUP} | wc -l)
		POS=$(grep -n "point" ${GROUP} | sed -e "s/:.*//g")

		START=$((${LINES}-${POS}))
		GID=$(echo ${GROUP} | sed -e "s/.*groupid+//g" -e "s/+.*//g")

		CFILE="q${q}_n${n}_k${k}_g${GID}_d${d}.code"
		PFILE="q${q}_n${n}_k${k}_g${GID}_d${d}.prb"

		echo "[" > ${CFILE}
		tail -n ${START} ${GROUP} | head -n $((${START}-2)) >> ${CFILE}
		echo "]" >> ${CFILE}
		echo "" >> ${CFILE}
		echo ${ORBIT} >> ${CFILE}
		echo "" >> ${CFILE}
		echo "${n}" >> ${CFILE}
		echo "${d}" >> ${CFILE}

		sed -i ${CFILE} -e "s/:/ /g" -e "s/,/ /g"
		SIZE=$(du -k ${CFILE} | sed -e "s/\t.*//g")

	done

	cd - &> /dev/null
	mv ${TMPDIR}/*.{code,prb,lat} . &> /dev/null
	rm -rf ${TMPDIR} &> /dev/null

else

	echo "Usage: "
	echo -e "\t$0 q=2 k=10 n=252 d=120"

fi
