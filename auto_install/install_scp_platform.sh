
source $(dirname $0)/config
source $(dirname $0)/common.sh
function choose_pkg(){
    local i=0;
    local choice=0;
    declare -A map_pkg=()
    for ch in `$1`
    do
            i=`expr $i + 1`;
            echo "$i) " $ch;
			
            map_pkg["$i"]=$ch;
    done

    while true; 
    do
            read -p "input your choice: " choice;
            if [ $choice -gt 0 ] && [ $choice -lt $i ]; then
                echo "INSTALL IS " ${map_pkg["$choice"]};
				install_pkg=${map_pkg["$choice"]};
                return;
            else
                echo "invalid node_number number, please input a node_number ranges from [1 - $i]";
            fi
    done

}

function check_install_rabbitmq_server(){
    logc    "0" $log_ret
    logc    "0" $log_showpgr
    {
        # $shell_path/show_cond_progress.sh "install_rabbitmq"  "find $rabbitmq_server_path -name rabbitmq-server 2>/dev/null | wc -l"
        $shell_path/show_cond_progress.sh "install_rabbitmq"  "cat $log_showpgr"
    } &
    expect $shell_path/exp/su_cmd.exp root $root_pwd "sh $shell_path/install_rabbitmq_server.sh $pkg_path $shell_path $root_pwd $install_path $rabbitmq_server_path">>$log_path/process.log
    logc    "1" $log_showpgr
}

# $1 install_path
function check_install_consul(){
    logc    "0" $log_ret
    expect $shell_path/exp/su_cmd.exp root $root_pwd "sh $shell_path/install_consul.sh $shell_path $install_path $app_user $consul_path" >> $log_file
}

function check_install_jdk(){
    logc    "0" $log_ret
    {
        $shell_path/show_cond_progress.sh "install_jdk" "java -version 2>&1 |grep \"java version\" | wc -l"
    } &
    expect $shell_path/exp/su_cmd.exp root $root_pwd "sh $shell_path/install_jdk.sh $pkg_path $install_path $shell_path $root_pwd" >> $log_file
}


# nohup java -jar XXX.jar >temp.out &
# $1 
function start_java_exe(){
    expect $shell_path/exp/su_cmd.exp root $root_pwd "sh $shell_path/start_java_exe.sh $jar_path $app_user $log_path" 
    logi    "start java exe suc ."  $log_file
    logc "1"    $log_ret
}

# $1 -- pkg path
# $2 -- log path
function check_install_expect(){
    local count=`rpm -qa | grep expect | grep x86_64 | wc -l`
    if [ $count -eq 1 ]; then 
        echo "[`date "+%Y-%m-%d %H:%M:%S"`]expect has been installed.">>$2/process.log
        return 0;
    fi
    
    local expect_pkg_name=`find $1 -name expect*.rpm`
    local expect_pkg_dir=`dirname $expect_pkg_name`
    cd $expect_pkg_dir;
    
    echo "input root passwd:"
    su - root -c "rpm -ivh $expect_pkg_dir/*.rpm"
    echo "[`date "+%Y-%m-%d %H:%M:%S"`]expect install suc..">>$2/process.log
    echo ""
}


function boot_consul(){
    logc    "0" $log_ret
    expect $shell_path/exp/su_cmd.exp "root" $root_pwd "$shell_path/check_start_process.sh $app_user consul agent agent $log_path" >> $log_file
    ret=`cat $log_path/ret`
    if [ $ret -eq 0 ]; then
        if [ -z $consul_persistence_path ]; then
            read -p "input consul_persistence_path:" consul_persistence_path;
            if [ ! -d $consul_persistence_path ]; then
                mkdir -p "$consul_persistence_path"; 
            	if [ ! -d $consul_persistence_path ]; then
                    echo "persion deny to create dir."
                    exit 0;
                fi
            fi
            logd    "consul_persistence_path is [$consul_persistence_path]."    $log_file
        fi

        local boot_consul_str="consul agent -server -bootstrap-expect 1 -data-dir $consul_persistence_path -bind=127.0.0.1 -client 0.0.0.0 -ui"
        logi    "$boot_consul_str"  $log_file
        logi    "CONSUL_START_PARA: $boot_consul_str" $log_boot

        expect $shell_path/exp/su_cmd.exp "root" $root_pwd "$shell_path/start_consul.sh $app_user \"$boot_consul_str\"  " >> $log_file

        expect $shell_path/exp/su_cmd.exp "root" $root_pwd "$shell_path/check_start_process.sh $app_user \"consul\" \"agent\" \"agent\" $log_path" >> $log_file
        ret=`cat $log_path/ret`
        if [ $ret -eq 0 ]; then
            loge "boot consul failed. please check log" $log_file
            exit 0;
        fi
    fi
    

    logi    "boot consul suc."    $log_file
}

function boot_rabbitmq(){
    logc    "0" $log_ret
    expect $shell_path/exp/su_cmd.exp "root" $root_pwd "$shell_path/check_start_process.sh $app_user rabbit erlang rabbit $log_path" >> $log_file
    ret=`cat $log_path/ret`
    if [ $ret -eq 0 ]; then
        local mq_init_1="rabbitmq-plugins enable rabbitmq_management"
        local mq_init_2="rabbitmq-server start";
        local mq_init_3="rabbitmqctl eval 'rabbit_amqqueue:declare({resource, <<"/">>, queue, <<"scpServiceLog">>}, true, false, [], none).'"
        local mq_init_4="rabbitmqctl eval 'rabbit_amqqueue:declare({resource, <<"/">>, queue, <<"scpTransLog">>}, true, false, [], none).'"


        expect $shell_path/exp/su_cmd.exp "root" $root_pwd "$shell_path/start_rabbit.sh $app_user \"$mq_init_1\" \"$mq_init_2\" \"$mq_init_3\" \"$mq_init_4\"" >> $log_file
	    sleep 1; # for boot rabbit time delay 
        expect $shell_path/exp/su_cmd.exp "root" $root_pwd "$shell_path/check_start_process.sh $app_user erlang rabbit rabbit $log_path">>$log_file
        ret=`cat $log_path/ret`
        if [ $ret -eq 0 ]; then
            echo "mq init or start failed. please check log $log_path/process.log"
            exit 0;
        fi

        # sava mq boot info 
        local mq_port_count=`netstat -an | grep -v grep | grep 5672 | wc -l`
        if [ $mq_port_count -ne 0 ]; then
            echo "RABBIT_MQ_START_PARA:" $local_ip "5672" "$mq_init_2" >> $log_boot
        else
            echo "RABBIT_MQ_START_PARA:" $local_ip "0000" "$mq_init_2" >> $log_boot
        fi

        app_home_path=`cat /etc/passwd | grep $app_user | awk -F: '{print $6}'`
    	expect $shell_path/exp/su_cmd.exp "root" $root_pwd "cp -r $shell_path/init_rabbit.sh $app_home_path; chmod 777 $app_home_path/init_rabbit.sh" >> $log_file
        expect $shell_path/exp/su_cmd.exp "$app_user" $app_pwd "sh $app_home_path/init_rabbit.sh; rm -f $app_home_path/init_rabbit.sh" >> $log_file
    fi

    logi "boot mq suc." $log_file
}

# 
# SCPDBSERVER
# SCPCONFIGSERVER
# SCPRABBITMQSERVER
# $1 hostName
# $2 IP
function config_host_file(){
    local rep_config=$2" "$1
    local edit_flag=0
    local count=`grep -wi $1 /etc/hosts | wc -l`  
    if [ $count -eq 1 ];then
        local ip_count=`grep -wi $1 /etc/hosts | grep $2 | wc -l`
        if [ $ip_count -eq 0 ]; then
            # modify
            local ori_cfg=`grep -wi $1 /etc/hosts`
            local exp_str=s/${ori_cfg}/${rep_config}/g 
            sed -i "$exp_str" /etc/hosts
            edit_flag=1;
        fi
    else
        # add
        expect $shell_path/exp/su_cmd.exp "root" $root_pwd "echo $rep_config >> /etc/hosts " >> $log_path/process.log;
        edit_flag=2;
    fi

    count=`grep -wi $1 /etc/hosts | grep $2 | wc -l`
    if [ $count -eq 0 ]; then 
        echo "write host file failed. $1 $2"; >> $log_path/process.log
        exit 0;
    fi

    [ $edit_flag -ne 0 ] && echo "add host config suc. $1 $2" >> $log_path/process.log
}

function main(){
    cd `dirname $0`
    shell_path=`pwd`
    scp_install_path=`dirname $shell_path`
    cat $shell_path/logo_start
    log_path=$scp_install_path/log
    jar_path=$scp_install_path/jar
    log_file=$log_path/process.log
    log_ret=$log_path/ret
    log_boot=$log_path/boot_info
    log_showpgr=$log_path/show_progress_ret

    if [ $# -eq 1 ]; then
        # para 1 -- install_path
        if [ ! -d $scp_install_path/3rd ]; then
            echo "no package directory found in $scp_install_path"
            echo -e $USEAGE;
            exit 0;
        fi

        pkg_path=$scp_install_path/3rd;

        if [ ! -d $1 ]; then  
            mkdir -p $1 ; 
            if [ ! -d $1 ]; then  
                echo "permission denied. please check current user.";
                exit 0;
            fi
        fi  
        cd $1;
        install_path=`pwd`;

    elif [ $# -eq 2 ]; then 
        # para 1 -- package path
        # para 2 -- install path

        if [ ! -d $1 ]; then  
            echo "no package directory found ."
            echo -e $USEAGE;
            exit 0;
        fi
        cd $1;
        pkg_path=`pwd`;
        cd - > /dev/null;
        
        if [ ! -d $2 ]; then  
            mkdir -p $2 ; 
            if [ ! -d $2 ]; then  
                echo "permission denied. please check current user.";
                exit 0;
            fi
        fi  
        cd $2;
        install_path=`pwd`;
    
    else
        echo -e $USEAGE;   
        exit 0;
    fi

    find $scp_install_path -name \*.sh  | xargs chmod 777;
    find $scp_install_path -name \*.exp | xargs chmod 777;
    find $scp_install_path -name \*.sql | xargs chmod 777;


    if [ -z $app_user ]; then 
        read -p "input app_user:" app_user;
    fi 

    if [ -z $app_pwd ]; then 
        read -p "input app_name:" app_pwd;
    fi 

    if [ -z $db_name ]; then 
        read -p "input db_name:" db_name;
    fi 

    if [ -z $db_node_name ]; then 
        read -p "input db_node_name:" db_node_name;
    fi 

    if [ -z $root_pwd ]; then 
        read -p "input root passwd:" root_pwd;
    fi 

    if [ -z $db_instance ]; then 
        read -p "input db instance:" db_instance;
    fi 

    touch $log_path/process.log && chmod 777 $log_path/process.log 
    touch $log_path/ret && chmod 777 $log_path/ret
    touch $log_path/tmp && chmod 777 $log_path/tmp
    touch $log_showpgr && chmod 777 $log_showpgr
    touch $log_boot && chmod 777 $log_boot

    local_ip=`/sbin/ifconfig -a|grep inet|grep -v 127.0.0.1|grep -v inet6|awk '{print $2}'|tr -d "addr:"`

    # main start
    # install expect 
    check_install_expect  $pkg_path $log_path;

    # config hosts
    if [ -z $SCPDBSERVER ]; then 
        read -p "input SCPDBSERVER IP:" SCPDBSERVER
    fi 
    if [ -z $SCPCONFIGSERVER ]; then 
        read -p "input SCPCONFIGSERVER IP:" SCPCONFIGSERVER;
    fi 
    if [ -z $SCPRABBITMQSERVER ]; then 
        read -p "input SCPRABBITMQSERVER IP:" SCPRABBITMQSERVER;
    fi 

    config_host_file "SCPDBSERVER"          "$SCPDBSERVER";
    config_host_file "SCPCONFIGSERVER"      "$SCPCONFIGSERVER";
    config_host_file "SCPRABBITMQSERVER"    "$SCPRABBITMQSERVER";

    # chech user. create if not exist
    echo "0" > $log_path/ret
    expect $shell_path/exp/su_cmd.exp "root" "$root_pwd" "sh $shell_path/crt_user.sh $app_user $app_pwd $log_path" >> $log_path/process.log
    ret=`cat $log_path/ret`
    if [ $ret -eq 0 ]; then
        echo " user create failed."
        exit 0;
    fi

    local install_mode="";
    while true;
    do
        read -p "
            input your install mode:
                              1) one key install
                              2) bundle install
            install_mode:" install_mode;
        if [ $install_mode -gt 0 ] && [ $install_mode -lt 3 ]; then
            break;
        else
            echo "invalid input, please input a choice ranges from [1 - 2]";
        fi
    done

    if [ $install_mode -eq 1 ]; then 
        one_key_install;
    else
        bundle_install;
    fi
}

function boot_tomcat(){
    logc    "0" $log_ret
    expect $shell_path/exp/su_cmd.exp "root" $root_pwd "$shell_path/check_start_process.sh $app_user tomcat  tomcat  tomcat $log_path" >> $log_file
    ret=`cat $log_path/ret`

    if [ $ret -eq 0 ]; then
        expect $shell_path/exp/su_cmd.exp "root" $root_pwd "$shell_path/start_tomcat.sh $app_user $log_path $tomcat_path/bin/startup.sh" >> $log_file
        sleep 1; # 
        expect $shell_path/exp/su_cmd.exp "root" $root_pwd "$shell_path/check_start_process.sh $app_user tomcat  tomcat  tomcat $log_path" >> $log_file
        ret=`cat $log_path/ret`
        if [ $ret -eq 0 ]; then
            echo "boot tomcat failed. please check log $log_path/process.log"
            exit 0;
        fi
    fi

}

function bundle_install(){
    local choice=();
    while true;
    do
        choice=();
        while true;
        do
            read -p "
            input your bundle install choice, if mult choice, separated by space which like \"1 3 4\":
                              1) db2
                              2) consul 
                              3) rabbitmq-server
                              4) jdk
                              5) tomcat
                              6) start java application
                              7) exit installation

                your choice:" -a choice
            # CHECK TO DO
            if [ ${#choice[@]} -ne 0 ]; then
                break;
            fi
        done

        for i in ${choice[@]}
        do
            if [ $i -eq 7 ]; then
                exit 0;
            elif [ $i -eq 1 ]; then
                check_install_db;
                ret=`cat $log_path/ret`
                if [ $ret -eq 0 ]; then 
                    echo "check_install_db failed. please check log $log_path/process.log"
                    exit 0;
                fi
                echo "----> check and install db finished."
                echo ""
            elif  [ $i -eq 2 ]; then
                check_install_consul;
                ret=`cat $log_path/ret`
                if [ $ret -eq 0 ]; then 
                    loge "install_consul failed. please check log" $log_file
                    exit 0;
                fi
                boot_consul;
                echo "----> check and install consul finished."
                echo ""
                
            elif  [ $i -eq 3 ]; then
                check_install_rabbitmq_server;
                ret=`cat $log_path/ret`
                if [ $ret -eq 0 ]; then 
                    echo "install_rabbitmq_server failed."
                    exit 0;
                fi

                boot_rabbitmq;
                echo ""
                echo "----> check and install rabbit finished."
            elif  [ $i -eq 4 ]; then
                check_install_jdk;
                ret=`cat $log_path/ret`
                if [ $ret -eq 0 ]; then 
                    echo "install_jdk failed. please check log $log_path/process.log"
                    exit 0;
                fi
                printf "\n"
                echo "----> check and install jdk finished."
                printf "\n"

            elif  [ $i -eq 5 ]; then
                check_install_tomcat;
                ret=`cat $log_path/ret`
                if [ $ret -eq 0 ]; then 
                    echo "install_tomcat failed. please check log $log_path/process.log"
                    exit 0;
                fi

                boot_tomcat;
                echo ""
                echo "----> check and install tomcat finished."
                echo ""

            elif  [ $i -eq 6 ]; then
                start_java_exe;    
                echo "----> check and install java exe finished. install complete."
                echo ""
            fi 
        done 
    done
}

function one_key_install(){
    check_install_db;
    ret=`cat $log_path/ret`
    if [ $ret -eq 0 ]; then 
        echo "check_install_db failed. please check log $log_path/process.log"
        exit 0;
    fi
    echo "----> check and install db finished. start to check and install consul."
    echo ""

    check_install_consul;
    ret=`cat $log_path/ret`
    if [ $ret -eq 0 ]; then 
        echo "install_consul failed. please check log $log_path/process.log"
        exit 0;
    fi
    boot_consul;
    echo ""
    echo "----> check and install consul finished.  start to check and install rabbitmq_server. "
    echo ""

    check_install_rabbitmq_server;
    ret=`cat $log_path/ret`
    if [ $ret -eq 0 ]; then 
        echo "install_rabbitmq_server failed. please check log $log_path/process.log"
        exit 0;
    fi

    boot_rabbitmq;
    echo ""
    echo "----> check and install rabbit finished.  start to check and install jdk."
    echo ""

    check_install_jdk;
    ret=`cat $log_path/ret`
    if [ $ret -eq 0 ]; then 
        echo "install_jdk failed. please check log $log_path/process.log"
        exit 0;
    fi
    echo ""
    echo "----> check and install jdk finished.  start to check and install tomcat."
    echo ""

    check_install_tomcat;
    ret=`cat $log_path/ret`
    if [ $ret -eq 0 ]; then 
        echo "install_tomcat failed. please check log $log_path/process.log"
        exit 0;
    fi
    boot_tomcat;
    echo ""
    echo "----> check and install tomcat finished.  start to check and start java process."
    echo ""

    start_java_exe;    
    echo "----> check and install java exe finished. install complete."
    echo ""
}

function check_install_mysql(){
    # TODO:
    echo "TODO list. not supported currently."
    return 1;
}

# $1 dbs_location
function check_is_installed_db2(){
    # check is not complete.
    local count=0;
    if [ $1 -eq 1 ]; then
        # LOCAL
        count=`find / -name db2icrt 2>/dev/null | wc -l`;
    else
        # REMOTE
        # TODO: find a tag replace db2icrt
        count=`find / -name db2icrt 2>/dev/null | wc -l`;
    fi 
    return $count
}

function check_install_oracle(){
    # TODO:
    echo "TODO list. not supported currently."
    return 1;
}

# user	 -- $1 
# passwd -- $2
function check_user_exist(){
    if id $1 &> /dev/null; then
        echo "user has been exist."
    else
        useradd $1
        echo $1 | passwd $1 --stdin  &>/dev/null
        if [ $? -eq 0 ]; then
            echo "add user $username suc."
        else
            echo "can not add $username."
        fi
    fi
}

function check_install_tomcat(){
    logc    "0" $log_ret
    logc    "0" $log_showpgr

    {
        #$shell_path/show_cond_progress.sh "install_tomcat"  "find $tomcat_path -name bin 2>/dev/null | wc -l"
        $shell_path/show_cond_progress.sh "install_tomcat"  "cat $log_showpgr"
    } &

    expect $shell_path/exp/su_cmd.exp "root" $root_pwd "$shell_path/install_tomcat.sh $pkg_path $install_path $shell_path $app_user $tomcat_path">>$log_path/process.log
    logc    "1" $log_showpgr
}

function check_install_db2(){ 
    if [ -z $dbs_location ]; then
        while true; 
        do
            read -p "
            input your database location:
                              1) LOCAL
                              2) REMOTE
            dbs_location:" dbs_location;
            if [ $dbs_location -gt 0 ] && [ $dbs_location -lt 3 ]; then
                break;
            else
                echo "invalid input, please input a choice ranges from [1 - 2]";
            fi
        done
    fi

    logd "dbs_location is [$dbs_location]" $log_file    
    
    if [ $dbs_location -eq 2 ];then
        # REMOTE
        if [ -z $db_server_ip ]; then
            read -p "input remote db_server_ip:" db_server_ip;
        fi

        if [ -z $db_server_port ]; then
            read -p "input remote db_server_port:" db_server_port;
        fi

        logd "db_server_ip is [$db_server_ip]. db_server_port is [$db_server_port]." $log_file    
    fi 

    if [ -z $db_is_crt_db_flag ]; then
        read -p "
            whether to build a database :[Y|N]
            your choice:" db_is_crt_db_flag;
        if [ $db_is_crt_db_flag = "Y" ] || [ $db_is_crt_db_flag = "yes" ] || [ $db_is_crt_db_flag = "YES" ] || [ $db_is_crt_db_flag = "y" ]; then 
            db_is_crt_db_flag=1;
        else
            db_is_crt_db_flag=0;
        fi 
    fi
    logd "db_is_crt_db_flag is [$db_is_crt_db_flag]." $log_file    

    if [ -z $db_is_init_flag ]; then
        read -p "
            whether to initialize db :[Y|N]
            your choice:" db_is_init_flag;
        if [ $db_is_init_flag = "Y" ] || [ $db_is_init_flag = "yes" ] || [ $db_is_init_flag = "YES" ] || [ $db_is_init_flag = "y" ]; then 
            db_is_init_flag=1;
        else
            db_is_init_flag=0;
        fi 
    fi
    logd "db_is_init_flag is [$db_is_init_flag]." $log_file    

    check_is_installed_db2 $dbs_location;
    if [ $? -eq 0 ]; then
        if [ -z $db2_version ]; then
            while true;
            do
                read -p "
            input your database location:
                           1) v10.5
                           2) v11
            db_version:" version_choice;
                if [ $version_choice -eq 1 ]; then
                    db2_version=10
                    break;
                elif [ $version_choice -eq 2 ]; then
                    db2_version=11
                    break;
                else
                    echo "invalid input, please input a choice ranges from [1 - 2]"
                fi
            done
        fi
        logd "db_version is [$db2_version]." $log_file    

        expect $shell_path/exp/su_cmd.exp "root" $root_pwd "sh $shell_path/install_db2.sh $pkg_path $install_path $shell_path $dbs_location $root_pwd $db2_version";
        check_is_installed_db2 $dbs_location;
        if [ $? -eq 0 ]; then
            loge "db2 install failed. " $log_file
            exit 0;
        fi
    fi

    cd $shell_path;

    # check_db2 instance scp;
    expect $shell_path/exp/su_cmd.exp "root" "$root_pwd" "sh $shell_path/check_db2_instance.sh $root_pwd $db_instance $shell_path $pkg_path $app_user $db2_version $db_server_port $dbs_location";
    ret=`cat $log_path/ret`
    if [ $ret -eq 0 ]; then 
        loge " db2 instance create failed." $log_file
        exit 0;
    fi 

    # db2start if local is server; connect test if local is client
    expect $shell_path/exp/su_cmd.exp "root" "$root_pwd" "sh $shell_path/db2_test.sh $db_instance $pkg_path $app_user $dbs_location $db_server_ip $db_server_port $db_name $db_node_name $app_pwd ";
    ret=`cat $log_path/ret`
    if [ $ret -eq 0 ]; then 
        loge "db2 start failed. please check it."   $log_file
        exit 0;
    fi 

    # if needed, create db
    if [ $db_is_crt_db_flag -eq 1 ];then
        # db2init
        expect $shell_path/exp/su_cmd.exp "root" "$root_pwd" "sh $shell_path/db2_init.sh $db_name $shell_path $log_path $app_user $app_pwd $test_table $db_instance $db_is_init_flag $dbs_location";
        ret=`cat $log_path/ret`
        if [ $ret -eq 0 ]; then 
            loge "db2 init failed. please check it." $log_file
            exit 0;
        fi 
    fi
}

function check_install_db(){
    if [ -z $db_type ]; then
        while true; 
        do
            read -p "
            input your database type which your platform dependended: 
                              1) DB2
                              2) ORACLE
                              3) MYSQL
            db_type:" db_type;
            if [ $db_type -gt 0 ] && [ $db_type -lt 4 ]; then
                break;
            else
                echo "invalid input, please input a choice ranges from [1 - 3]";
            fi
        done
    fi 

    case "$db_type" in
        1)
            check_install_db2;;
        2)
            check_install_oracle;;
        3)
            check_install_mysql;;
    esac
}

main $1 $2;
