#!/bin/sh

rm -ri /var/svn
mkdir /var/svn

svnadmin create /var/svn/repos

chgrp -R svnusers /var/svn/repos

chmod -R g-w /var/svn/repos
chmod -R 775 /var/svn/repos/db
chmod -R 775 /var/svn/repos/locks
