# $1 -- db2instance
# $2 -- log path
# $3 -- db instance user
# $4 -- db location 1 -- LOCAL 2 -- REMOTE
# $5 -- db server ip
# $6 -- db server port
# $7 -- db name 
# $8 -- db node name 
# $9 -- app_user_pwd

source $(dirname $0)/common.sh

log_file=$2/process.log
log_ret=$2/ret

if [ $4 -eq 1 ] ; then 
    port=`cat /etc/services | grep db2c_$1 | awk '{print $2}' | awk -F/ '{print $1}'`
    if [ -z $port ]; then 
        loge    "can't find $1 port in file. please check db instance $1"   $log_file
        logc    "0"                                                         $log_ret
        exit 0;
    fi

    count=`netstat -an | grep $port | wc -l`
    if [ $count -ne 1 ]; then 
        su - $3 -c "db2start"
        count=`netstat -an | grep $port | wc -l`
        if [ $count -ne 1 ]; then 
            loge    "db2start listen port[$port] failed. please check it."  $log_file
            logc    "0"                                                     $log_ret
            exit 0;
        fi
    fi

    logi    "db2start listen port[$port] suc."  $log_file
    logc    "1"                                 $log_ret

else 
    ret=`su - $3 -c "db2 list node directory | grep \"Node name\" | grep -v grep | grep -i $8 | wc -l"`
    if [ -z $ret ] || [ $ret -eq 0 ]; then
        su - $3 -c "db2 catalog tcpip node $8 remote $5 server $6;db2 catalog db $7 at node $8; db2 terminate;">/dev/null
    fi

    # connect test
    su - $3 -c "db2 connect to $7 user $3 using $9; db2 \"select 1 from SYSIBM.SYSDUMMY1 \" |  awk 'NR==2 {print}'">$2/tmp_ret;
    ret=`cat $2/tmp_ret | awk 'END {print}'`
    if [ ${ret:0:1} != "1" ];then
        loge    "db2 connect to $7 user $3 using $9. connect test failed;"  $log_file
        logc    "1" $log_ret
        exit 0;
    fi
fi

logi    "db2 start suc."    $log_file
logc    "1"                 $log_ret
