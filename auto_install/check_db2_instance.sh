# para 1 -- root_pwd
# para 2 -- instance name
# para 3 -- shell path
# para 4 -- pkg path
# para 5 -- instance user
# para 6 -- db2 version 
# para 7 -- db2 config port
# para 8 -- dbs location

source $(dirname $0)/common.sh

scp_base_path=`dirname $3`
log_path=$scp_base_path/log
log_file=$scp_base_path/log/process.log
log_ret=$scp_base_path/log/ret

logc    "0" $log_ret   
db2_instance_size=""
if [ $8 -eq 2 ];then  # REMOTE
    if [ $6 -eq 10 ];then 
        db2_instance_size=8620000
    else
        db2_instance_size=9149173
    fi
else #local 
    if [ $6 -eq 10 ];then 
        db2_instance_size=31755048
    else
        db2_instance_size=31755048
    fi
fi

ret=`su - $5 -c "db2ilist 2>/dev/null | grep $2 | wc -l"`
if [ $ret -eq 0 ]; then 
    count=`find / -name db2icrt | wc -l`;
    if [ $count -ne 1 ]; then
        loge    "can't find db2icrt."   $log_file
        logc    "0"                     $log_ret
        exit 0;
    fi

    db2_cmd_db2icrt=`find / -name db2icrt 2>/dev/null`;

    home_path=`cat /etc/passwd | grep $5 | awk -F: '{print $6}'`;

    {
        sh $3/show_progress.sh $home_path/sqllib $db2_instance_size "crt_db2instance"
    }&
    $db2_cmd_db2icrt -u $5 $2>>$log_path/install_db.log
    wait;

    ret=`su - $5 -c "db2ilist 2>/dev/null | grep $2 | wc -l"`
    if [ $ret -ne 1 ]; then
        loge    "error while do [db2icrt -u scp scp]"   $log_file
        logc    "0"                                     $log_ret        
        exit 0;
    fi
fi

# if install version is v10, we need config port in /etc/hosts
if [ $6 -eq 10 ]; then
    count=`grep db2c_$2 /etc/services | wc -l`
    if [ $count -eq 1 ];then
        port=`grep db2c_$2 /etc/services | grep -wi tcp | awk '{print $2}' | awk -F "/" '{print $1}'`
        logi    "configuration port already exists in /etc/services and will not be updated. port is [$port]."  $log_file
        su - $5 -c "db2 update database manager configuration using svcename db2c_$2;db2set DB2COMM=tcpip;db2stop;set instance;db2start;" >> $log_file
    elif [ $count -eq 0 ];then
        check_ret=`grep $7 /etc/services | wc -l`
        if [ $check_ret -ne 0 ]; then
            loge    "port [$7] has been used in /etc/services."     $log_file
            logc    "0"                                             $log_ret        
            exit 0;
        fi
        new_config="db2c_$2        $7/tcp                # $2"
        echo "$new_config" >> /etc/services
        su - $5 -c "db2 update database manager configuration using svcename db2c_$2;db2set DB2COMM=tcpip;db2stop;set instance;db2start;" >> $log_file
    else
        loge    "config error in /etc/services."                $log_file
        logc    "0"                                             $log_ret        
        exit 0;
    fi

fi


logi "db2 instance check $2 suc."   $log_file
logc "1"                            $log_ret
echo ""
