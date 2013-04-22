#!/bin/sh

USER=$1
GREP=$(grep "${USER}" /etc/passwd)

ROOTBEER="hgrt6%4%"

if [ "${GREP}x" != "x" ] ; then
	# delete user from passwd/shadow file and remove home directory
	userdel -r ${USER}
	
	# drop the user's mysql database
	echo "DROP DATABASE ${USER}; DELETE FROM mysql.db WHERE User=\"${USER}\"; DELETE FROM mysql.user WHERE User=\"${USER}\";" | mysql -u root --password="${ROOTBEER}"

	exit 1
fi

SALT='\$1\$Qbtz9UhJ'
PASS=$(perl -e "print crypt(\"$2\", \"${SALT}\")")

# add user to passwd/shadow file and create home directory
useradd -g users -s /bin/bash -m -p ${PASS} ${USER}

# create the user's mysql database
echo "CREATE DATABASE ${USER}; GRANT ALL PRIVILEGES ON ${USER}.* TO ${USER}@localhost IDENTIFIED BY \"$2\";" | mysql -u root --password="${ROOTBEER}" 
