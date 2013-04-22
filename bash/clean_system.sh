#!/bin/sh

> ~haaner/old_files 
find / -atime +720 -and -ctime +720 -and -mtime +720 >> ~haaner/old_files 

exit;

> /tmp/files
for i in /var/db/pkg/*/*/CONTENTS ; do 
	cut -f 2 -d ' ' $i >> /tmp/files
done
cat /tmp/files | sort -n | uniq > ~haaner/registered_files

> /tmp/files
find / >> /tmp/files
cat /tmp/files | sort -n | uniq > ~haaner/system_files

diff -ubBd ~haaner/registered_files ~haaner/system_files | grep "^+" > diff_files
