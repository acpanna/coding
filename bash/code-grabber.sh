#!/bin/sh

SRC="${HOME}/codes/"

GEN_MARKLAT="${HOME}/doctor/prb2lat"
CONV_CODE2PRB="${HOME}/doctor/code2prb"

MINSIZE="0"
MAXSIZE="1000"

q=$1
k=$2

mkdir -p ${SRC}
cd ${SRC}

if [[ "${q}"x != ""x ]] && [[ "${k}"x != ""x ]] ; then 

	echo "Fetching code instances for: q = $q, k = $k"

	#rm -rf ${SRC}/*

	wget --no-clobber http://www.mathe2.uni-bayreuth.de/cgi-bin/axel/codedb?printnurqk+$q+$k &> /dev/null
	wget --no-clobber --force-html -i codedb?printnurqk+$q+$k --base=http://www.mathe2.uni-bayreuth.de/cgi-bin/axel/ &> /dev/null

	for i in $(ls codedb?printqknd+$q+$k+* 2> /dev/null | randomize.pl 2> /dev/null | head -n3) ; do  
		wget --no-clobber --force-html --base=http://www.mathe2.uni-bayreuth.de/cgi-bin/axel/ -i ${i} &> /dev/null

		for ii in $(ls codedb?groupcodeid+*+$q+$k 2> /dev/null) ; do  
			wget --no-clobber --force-html --base=http://www.mathe2.uni-bayreuth.de/cgi-bin/axel/ -i ${ii} &> /dev/null
		done
	done
fi



echo "Fetching some extra groups: q = $q, k = $k"
for i in $(seq 1 1157 | randomize.pl | head -n 20) ; do
	wget --no-clobber --force-html http://www.mathe2.uni-bayreuth.de/cgi-bin/axel/codedb?groupid+${i}+${q}+${k} &> /dev/null
done

echo "Sorting code instances ..."

for q in 2 3 4 5 7 8 9 ; do 
	for k in $(seq 3 16) ; do

		for i in $(ls codedb?groupid+*+${q}+${k} 2> /dev/null) ; do

			if [ -f ${i} ] ; then

				ORBIT=$(grep "	orbitsizes" ${i} | sed -e "s/.*\[//g" -e "s/\]//g" -e "s/,/+/g")
				n=$((${ORBIT}))

				if [ ${n} -gt 0 ] ; then
					DIR="q${q}/k${k}/n${n}"
					mkdir -p ${DIR}

					cp ${i} ${DIR} # vorher: mv
				fi
			fi
		done
		
	done
done

rm -rf probs
mkdir probs

echo "Generating integer, linear code problems ..."

for q in 2 3 4 5 7 8 9 ; do 
	for k in $(seq 3 16) ; do

		DIR="q${q}/k${k}"

		for i in $(ls codedb?printnurqk+${q}+${k} 2> /dev/null | randomize.pl 2> /dev/null) ; do 

			if [ -f ${i} ] ; then

				while read l ; do

					d=""

					TMP=$(echo ${l} | grep "up=" | sed -e "s/.*up=//g" -e "s/<.*//g")
					if  [	"${TMP}"x != ""x ] ; then
						u=${TMP}
					fi

					TMP=$(echo ${l} | grep "d=" | sed -e "s/d=.*\">//g" -e "s/<.*//g")
					if  [	"${TMP}"x != ""x ] ; then
						d=${TMP}
						n=$(echo ${l} | grep "d=" | sed -e "s/.*codedb?printqknd+${q}+${k}+//g" -e "s/+.*//g")

					fi

					if  [	"${d}"x != ""x ] ; then
						if [ $d -lt $u ] ; then 

							echo "--> Open problem: q-(n,k,d) = $q-($n,$k,$u)"

							for ii in $(ls ${DIR} 2> /dev/null | randomize.pl 2> /dev/null) ; do
								N=${ii#n}

								if [ $n -le $N ] ; then

									for iii in $(ls ${DIR}/${ii} 2> /dev/null | randomize.pl 2> /dev/null) ; do

										GROUP="${DIR}/${ii}/${iii}"

										ORBIT=$(awk '$1 == "orbitsizes", $1 == "sorted"' ${GROUP})
										ORBIT=$(echo $ORBIT | sed -e "s/ sort.*//g" -e "s/.*\[/\[/g" -e "s/ //g")

										LINES=$(cat ${GROUP} | wc -l)
										POS=$(grep -n "point" ${GROUP} | sed -e "s/:.*//g")

										START=$((${LINES}-${POS}))
										GID=$(echo ${GROUP} | sed -e "s/.*groupid+//g" -e "s/+.*//g")

										CFILE="probs/q${q}_n${n}_k${k}_g${GID}_d${u}.code"
										PFILE="probs/q${q}_n${n}_k${k}_g${GID}_d${u}.prb"


										echo "[" > ${CFILE}
										tail -n ${START} ${GROUP} | head -n $((${START}-2)) >> ${CFILE}
										echo "]" >> ${CFILE}
										echo "" >> ${CFILE}
										echo ${ORBIT} >> ${CFILE}
										echo "" >> ${CFILE}
										echo "${n}" >> ${CFILE}
										echo "${u}" >> ${CFILE}

										sed -i ${CFILE} -e "s/:/ /g" -e "s/,/ /g"
										
										SIZE=$(du -k ${CFILE} | sed -e "s/\t.*//g")
										
										if [[ ${SIZE} -le ${MAXSIZE} && ${SIZE} -ge ${MINSIZE} ]] ; then
											${CONV_CODE2PRB} --slacks=1 ${CFILE}
											${GEN_MARKLAT}	${PFILE}
										else 
											rm ${CFILE} 
										fi
									done

								fi
							done

							echo ""

						fi
					fi

				done < ${i}
			fi

		done
	done
done
