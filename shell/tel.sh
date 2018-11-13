#!/bin/bash
#set -x
echo $1
if [ -n "$1" ]; then 
  str4=`(sleep 1;echo flush cmd_$1;sleep 1; echo quit;sleep 1) | telnet   192.168.127.128  8000`
  echo ${str4}
fi

