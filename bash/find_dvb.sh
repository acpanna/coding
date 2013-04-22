#!/bin/sh

GREP=""
for i in 	"^N \+0501 \+[0-9]\{2\} \+[A-Z0-9]\{32\}" \
		"^N \+0501 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{128\}" \
		"^N \+B001 \+[0-9]\{2\} \+[A-Z0-9]\{32\}" \
		"^N \+B001 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{128\}" \
		"^N \+0511 \+[0-9]\{2\} \+[A-Z0-9]\{32\}" \
		"^N \+0511 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{128\}" \
		"^N \+0503 \+[0-9]\{2\} \+[A-Z0-9]\{32\}" \
		"^N \+0503 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{128\}" \
		"^N \+0505 \+[0-9]\{2\} \+[A-Z0-9]\{32\}" \
		"^N \+0505 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{128\}" ; do
				                         
	if [ "${GREP}x" = "x" ] ; then    
		GREP="\(${i}\)"  
	else 
		GREP="${GREP}\|\(${i}\)"
	fi 
done

KEYDIR="/home/haaner/dvb"
DESDIR="/home/haaner/public_html"

rm -rf ${KEYDIR}
mkdir ${KEYDIR}
cd ${KEYDIR}

DATE=$(date +"%Y-%-m-%-d")
DATE2=$(date +"%Y-%-m-%-d" -r ${DESDIR}/SoftCam.Key)

for UPLOAD in "http://www.funfiles.cc/index.php?showfilesfordate=${DATE}" "http://www.funfiles.cc/index.php?showfilesfordate=${DATE2}" ; do
	COLUMN=$(echo -n ${UPLOAD} | tr / \\n | wc -l)
	SERVER=`echo ${UPLOAD} | cut -d "/" -f 1-${COLUMN}`
	wget -O - ${UPLOAD} | grep "filename" | sed -e "s/.*href=\"//g" -e "s/\".*//g" -e "s!^!${SERVER}/!" >> links
done

PARAM=`tail -n 1 links | sed -e "s/.*&PHP/PHP/" -e "s/&.*//"` 
wget --no-cookies --header "Cookie: ${PARAM}" -i links

find -type f -iname "*.zip" -exec unzip -o '{}' ';' 
find -type f -iname "*.rar" -exec unrar e -or '{}' ';'
find -type f -iname "*.tar" -exec tar -xf '{}' ';' 
find -type f -iname "*.tar.gz" -exec tar -zxf '{}' ';' 

chmod 755 -R . 

find -type f -iname "*.txt*" -exec cat '{}' >> key.raw ';'
find -type f -iname "*.key*" -exec cat '{}' >> key.raw ';'

cat key.raw | tr [:lower:] [:upper:] | sed -e "s/^ \+//" -e "s/ \+/ /g" | cut -d ";" -f 1 > key2.raw

/home/haaner/bin/new_keys.sh > key3.raw

cat key2.raw | grep -i --binary-files="text" "${GREP}" | dos2unix | sort -u >> key3.raw

if [ -s key3.raw ] ; then
	mv key3.raw ${DESDIR}/SoftCam.Key
fi

exit

#		"^N \+4101 \+[0-9]\{2\} \+[A-Z0-9]\{32\}" \
#		"^N \+4101 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{128\}" \
#		"^N \+4102 \+[0-9]\{2\} \+[A-Z0-9]\{32\}" \
#		"^N \+4102 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{128\}" \
#	 	"^S \+002A \+0[CDE] \+[A-Z0-9]\{16\}" \
#	 	"^S \+0030 \+0[CDE] \+[A-Z0-9]\{16\}" \
#		"^W \+0D050C \+[A-Z0-9]\{2\} \+[A-Z0-9]\{32\}" \
#		"^W \+0D050C \+[A-Z0-9]\{2\} \+[A-Z0-9]\{128\}" \
#		"^V \+001C10 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{16\}" \
#		"^V \+005500 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{16\}" \
#		"^V \+007400 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{16\}" \
#		"^V \+007C00 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{16\}" \
#		"^V \+009400 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{16\}" \
#		"^V \+00B000 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{16\}" \
#		"^V \+00E810 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{16\}" \
#		"^V \+010C40 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{16\}" \
#		"^V \+015000 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{16\}" \
#		"^V \+019410 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{16\}" \
#		"^W \+0D0010 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{32\}" \
#		"^W \+0D02A0 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{32\}" \
#		"^W \+0D0304 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{32\}" \
#		"^W \+0D0308 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{32\}" \
#		"^W \+0D03B0 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{32\}" \
#		"^W \+0D0320 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{32\}" \
#		"^W \+0D035C \+[A-Z0-9]\{2\} \+[A-Z0-9]\{32\}" \
#		"^W \+0D0360 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{32\}" \
#		"^W \+0D0504 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{32\}" \
#		"^W \+0D2204 \+[A-Z0-9]\{2\} \+[A-Z0-9]\{32\}" \
