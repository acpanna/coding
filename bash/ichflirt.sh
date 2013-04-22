#!/bin/sh

HOST="www.ichflirt.de"
AGENT="Internet Explorer 6"
USER="larry${RANDOM}"
EMAIL="${USER}@test.xx"

########################################################
# Session-ID besorgen #

cat << _EOF_ > /tmp/request
GET / HTTP/1.1
Host: ${HOST}
User-Agent: ${AGENT}


_EOF_

COOKIE=$(cat /tmp/request | nc -q 5 www.ichflirt.de 80 | grep "PHPSESSID" | head -n1 | sed -e "s/.*PHPSESSID=//g")
PHPID=$(echo ${COOKIE} | sed -e "s/; .*//g")

########################################################
# Register-Page aufrufen #

CONTENT="PHPSESSID=${PHPID}&txt_username=${USER}&txt_email=${EMAIL}&txt_email_repeat=${EMAIL}&m_regstep=2&txt_invite_id=&ccmdsend=true"
CONTENT_LEN=$(echo ${CONTENT} | wc -m)
CONTENT_LEN=$((${CONTENT_LEN}-1))

cat << _EOF_ > /tmp/request
POST /content.php?g_sid=${PHPID}&page=reg&PHPSESSID=${PHPID} HTTP/1.1
Host: ${HOST}
User-Agent: ${AGENT}
Referer: http://${HOST}/
Cookie: ${COOKIE}
Content-Length: ${CONTENT_LEN}

_EOF_

echo -n ${CONTENT} >> /tmp/request

COOKIE=$(cat /tmp/request | nc -q 5 www.ichflirt.de 80 | grep "PHPSESSID" | head -n1 | sed -e "s/.*PHPSESSID=//g")
PHPID=$(echo ${COOKIE} | sed -e "s/; .*//g")
echo ${COOKIE}



exit;


########################################################
# Register-Ende aufrufen #

CONTENT_LEN=$(echo ${CONTENT} | wc -m)
CONTENT_LEN=$((${CONTENT_LEN}-1))

cat << _EOF_ > /tmp/request
POST /eingabeformular HTTP/1.1
Host: ${HOST}
User-Agent: ${AGENT}
Referer: http://${HOST}/content.php?g_sid=${PHPID}&page=reg&PHPSESSID=${PHPID} HTTP/1.1
Content-Type: application/x-www-form-urlencoded
Content-Length: ${CONTENT_LEN}

_EOF_

echo -n ${CONTENT} >> /tmp/request

COOKIE=$(cat /tmp/request | nc -q 5 www.ichflirt.de 80 | grep "PHPSESSID" | head -n1 | sed -e "s/.*PHPSESSID=//g")
PHPID=$(echo ${COOKIE} | sed -e "s/; .*//g")
echo ${COOKIE}

########################################################
# EMail-Account checken und Passwort extrahieren

########################################################
# Einloggen

PASS=""

CONTENT="PHPSESSID=${PHPID}&user=${USER}&hash=&passwd=${PASS}&btn_login=Login"
CONTENT_LEN=$(echo ${CONTENT} | wc -m)
CONTENT_LEN=$((${CONTENT_LEN}-1))

cat << _EOF_ > /tmp/request
POST /usercontrol.php?g_sid=${PHPID} HTTP/1.1
Host: ${HOST}
User-Agent: ${AGENT}
Referer: http://www.ichflirt.de/usercontrol.php?g_sid=${PHPID}
Cookie: ${COOKIE}
Content-Type: application/x-www-form-urlencoded
Content-Length: ${CONTENT_LEN}

_EOF_

echo -n ${CONTENT} >> /tmp/request

COOKIE=$(cat /tmp/request | nc -q 5 www.ichflirt.de 80 | grep "PHPSESSID" | head -n1 | sed -e "s/.*PHPSESSID=//g")
PHPID=$(echo ${COOKIE} | sed -e "s/; .*//g")
echo ${COOKIE}

########################################################
# Gelesene-Mails-Index aufrufen

cat << _EOF_ > /tmp/request
GET /content.php?page=im&filter=read HTTP/1.1
Host: ${HOST}
User-Agent: ${AGENT}
Referer: http://www.ichflirt.de/content.php?page=im
Cookie: ${COOKIE}


_EOF_

COOKIE=$(cat /tmp/request | nc -q 5 www.ichflirt.de 80 | grep "PHPSESSID" | head -n1 | sed -e "s/.*PHPSESSID=//g")
PHPID=$(echo ${COOKIE} | sed -e "s/; .*//g")
echo ${COOKIE}

########################################################
