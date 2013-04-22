#!/bin/sh

if [ "$1" == "" ] ; then
	echo "Usage: $0 directory"
	exit;
fi

cd $1

function killspecial() {
	
	j=$(echo "$1" | sed -e 's/ä/ae/g')
	j=$(echo "$j" | sed -e 's/ö/oe/g')
	j=$(echo "$j" | sed -e 's/ü/ue/g')
	j=$(echo "$j" | sed -e 's/Ä/Ae/g')
	j=$(echo "$j" | sed -e 's/Ö/Oe/g')
	j=$(echo "$j" | sed -e 's/Ü/Ue/g')
	j=$(echo "$j" | sed -e 's/ß/ss/g')
	
	j=$(echo "$j" | sed -e 's/[^0-9a-zA-Z./]/_/g')


	if [ "$1" == "$j" ] ; then 
		return 
	fi

	if [ -f "$j" ] ; then
		for k in $(seq 1 10000) ; do
			z=${j}_${k}
			if [ ! -f "$z" ] ; then
				j=$z
				break
			fi
		done
	fi

	mv "$1" "$j"
}

find . -type d | {
	while read line ; do
		killspecial "${line}" 
	done
}

for i in $(find . -type d) ; do
	cd "$i"
	find . -type f | {
		while read line ; do
			killspecial "${line}" 
		done
	}
	cd -
done

cd -

