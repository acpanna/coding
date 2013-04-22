#!/bin/sh


for i in $(seq $1 254) ; do
	for j in $(seq $2 254) ; do
		for k in $(seq $3 254) ; do
			for l in $(seq $4 254) ; do

				DIR=$(echo -e "GET / HTTP/1.0\r\n\r\n" | nc -w 1 $i.$j.$k.$l 80 2>&1 | grep -i "<title>Index Of \/.*<\/title>")

				if [ "${DIR}x" != "x" ] ; then
					echo $i.$j.$k.$l : ${DIR}
				fi

			done
		done
	done
done
