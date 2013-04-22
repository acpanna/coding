#!/bin/sh
 
NORMSIZE=500

cd /nfs/dvb

for i in *.mpg ; do
  
	FILE="${i}"
	SIZE=$(echo $(du -m  "${i}" | sed -e "s/\t.*//g"))

	CUTSIZE=$((${SIZE}-${NORMSIZE}))

	if [ ${CUTSIZE} -gt 0 ] ; then
		dd if="${FILE}" skip=${CUTSIZE} bs=1M of=cut.mpg
		mv cut.mpg "${FILE}"
	fi

done
