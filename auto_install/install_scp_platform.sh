
pkg_path=""
install_path=""
shell_path=""
cur_date=`date "+%Y_%m_%d_%H_%M_%S"`
install_cpx_log="/pkg/install_cpx_log_$cur_date"
erlang_path=/usr/local/erlang
consul_path=/usr/local/consul/bin
rabbitmq_server_path=/usr/local/rabbitmq_server
tomcat_path=/usr/local/tomcat
install_pkg=""

#db_type=1 # DB2(1) ORACLE(2) MYSQL(3)
#db_location="2"  # 1 -- LOCAL 2 -- REMOTE

db_type="" # DB2(1) ORACLE(2) MYSQL(3)
db_location=""  # 1 -- LOCAL 2 -- REMOTE

db_instance="scp"
root_pwd="ashen"
app_user="scp"
app_pwd="scp"
db_name="scp"
db_node_name="nodescp"
test_table="env_config"
db_server_ip="192.168.70.151"
db_server_port="50000"
db_is_crt_db_flag="" # 1 -- create  other; -- not create 
db_is_init_db_flag="" # 1 -- init   other; -- not init 

USEAGE="USEAGE:\n\tinstall_cbs_platform.sh  <pkg_path> <install_path>\n\tinstall_cbs_platform.sh <install_path> "

source ./common.sh
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
    expect $shell_path/exp/su_cmd.exp root $root_pwd "sh $shell_path/install_rabbitmq_server.sh $pkg_path $shell_path $root_pwd $install_path $rabbitmq_server_path";
}

# $1 install_path
function check_install_consul(){
    expect $shell_path/exp/su_cmd.exp root $root_pwd "sh $shell_path/install_consul.sh $pkg_path $install_path $shell_path $root_pwd $app_user $consul_path";
}

function check_install_jdk(){
    expect $shell_path/exp/su_cmd.exp root $root_pwd "sh $shell_path/install_jdk.sh $pkg_path $install_path $shell_path $root_pwd";
}


# nohup java -jar XXX.jar >temp.out &
# $1 
function start_java_exe(){
    expect $shell_path/exp/su_cmd.exp root $root_pwd "sh $shell_path/start_java_exe.sh $pkg_path $app_user";
    echo "[`date "+%Y-%m-%d %H:%M:%S"`]start java exe suc .">>$pkg_path/process.log
    echo "1">>$pkg_path/ret
}

# $1 -- pkg path
function check_install_expect(){
    local count=`find / -name "expect" &> $1/tmp ; grep "expect" $1/tmp | wc -l; echo "">$1/tmp`
    if [ $count -eq 1 ]; then 
        echo "[`date "+%Y-%m-%d %H:%M:%S"`]expect has been installed.">>$1/process.log
        return 0;
    fi
    
    local expect_pkg_name=`find $1 -name expect*.rpm`
    local expect_pkg_dir=`dirname $expect_pkg_name`
    cd $expect_pkg_dir;
    
    echo "input root passwd:"
    su - root -c "rpm -ivh $expect_pkg_dir/*.rpm"
    echo "[`date "+%Y-%m-%d %H:%M:%S"`]expect install suc..">>$1/process.log
}


function boot_consul(){

    expect $shell_path/exp/su_cmd.exp "root" $root_pwd "$shell_path/check_start_process.sh $app_user consul agent dev $pkg_path";
    ret=`cat $pkg_path/ret`
    if [ $ret -eq 0 ]; then
        expect $shell_path/exp/su_cmd.exp "root" $root_pwd "$shell_path/start_consul.sh $app_user \"consul agent -dev\"" ;
        expect $shell_path/exp/su_cmd.exp "root" $root_pwd "$shell_path/check_start_process.sh $app_user \"consul\" \"agent\" \"dev\" $pkg_path";
        ret=`cat $pkg_path/ret`
        if [ $ret -eq 0 ]; then
            echo "boot consul failed. please check log $pkg_path/process.log"
            exit 0;
        fi
    fi

    echo "[`date "+%Y-%m-%d %H:%M:%S"`]boot consul suc.">>$pkg_path/process.log
}

function boot_rabbitmq(){
    expect $shell_path/exp/su_cmd.exp "root" $root_pwd "$shell_path/check_start_process.sh $app_user rabbit rabbit rabbit $pkg_path";
    ret=`cat $pkg_path/ret`
    if [ $ret -eq 0 ]; then
        local mq_init_1="rabbitmq-server start";
        #local mq_init_1="nohup rabbitmq-server start>/dev/null 2>&1 &";
        #local mq_init_2="rabbitmqctl add_user scp scp"
        #local mq_init_3="rabbitmqctl set_user_tags scp administrator"
        #local mq_init_4="rabbitmqctl  set_permissions  -p  '/'  scp'.' '.' '.'"

        expect $shell_path/exp/su_cmd.exp "root" $root_pwd "$shell_path/start_rabbit.sh $app_user $pkg_path  $mq_init_1 $mq_init_2 $mq_init_3 $mq_init_4";
	sleep 1; # for boot rabbit time delay 
        expect $shell_path/exp/su_cmd.exp "root" $root_pwd "$shell_path/check_start_process.sh $app_user erlang rabbit rabbit $pkg_path";
        ret=`cat $pkg_path/ret`
        if [ $ret -eq 0 ]; then
            echo "mq init or start failed. please check log $pkg_path/process.log"
            exit 0;
        fi
    fi

    echo "[`date "+%Y-%m-%d %H:%M:%S"`]boot mq suc.">>$pkg_path/process.log
}

# $1 -- pkg_path;
# $2 -- install_path
function main(){
    cd `dirname $0`
    shell_path=`pwd`;
    cat $shell_path/logo_start

    if [ $# -eq 1 ]; then
        if [ ! -d $shell_path/package ]; then
            echo "no package directory found in $shell_path"
            echo -e $USEAGE;
            exit 0;
        fi
        cd $shell_path/package;
        pkg_path=`pwd`;

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

    find $shell_path -name \*.sh | xargs chmod 777 
    find $shell_path -name \*.exp | xargs chmod 777
    find $shell_path -name \*.sql | xargs chmod 777


    if [ -z $app_user ]; then 
        read -p "input app_user:" app_user;
    fi 

    if [ -z $app_pwd ]; then 
        read -p "input app_name:" app_pwd;
    fi 

    if [ -z $db_name ]; then 
        read -p "input db_name:" db_name;
    fi 

    if [ -z $root_pwd ]; then 
        read -p "input root passwd:" root_pwd;
    fi 

    if [ -z $db_instance ]; then 
        read -p "input db instance:" db_instance;
    fi 

    touch $pkg_path/process.log && chmod 777 $pkg_path/process.log 
    touch $pkg_path/ret && chmod 777 $pkg_path/ret
    touch $pkg_path/tmp && chmod 777 $pkg_path/tmp

    # main start
    # install expect 
    # global status file 
    check_install_expect  $pkg_path;
    # echo "----> check and install expect finished. start to check and install db."

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

function bundle_install(){
    local choice=();
    while true;
    do
        read -p "
            input your bundle install choice, if mult choice, separated by space which like \"1 3 4\":
                              1) db2
                              2) consul 
                              3) rabbitmq-server
                              4) jdk
                              5) tomcat
                              6) jar
            your choice:" choice
        # CHECK TO DO
        if [ ${#choice[@]} -ne 0 ]; then
            break;
        fi
    done

    for i in ${choice[@]}
    do
        if [ $i -eq 1 ]; then
            check_install_db;
            ret=`cat $pkg_path/ret`
            if [ $ret -eq 0 ]; then 
                echo "check_install_db failed. please check log $pkg_path/process.log"
                exit 0;
            fi
            echo "----> check and install db finished. start to check and install consul."
            echo ""
        elif  [ $i -eq 2 ]; then

            check_install_consul;
            ret=`cat $pkg_path/ret`
            if [ $ret -eq 0 ]; then 
                echo "install_consul failed. please check log $pkg_path/process.log"
                exit 0;
            fi
            boot_consul;
            echo "----> check and install consul finished.  start to check and install rabbitmq_server. "
            echo ""
        elif  [ $i -eq 3 ]; then

            check_install_rabbitmq_server;
            ret=`cat $pkg_path/ret`
            if [ $ret -eq 0 ]; then 
                echo "install_rabbitmq_server failed. please check log $pkg_path/process.log"
                exit 0;
            fi

            boot_rabbitmq;
            echo "----> check and install rabbit finished.  start to check and install jdk."
            echo ""

        elif  [ $i -eq 4 ]; then
            check_install_jdk;
            ret=`cat $pkg_path/ret`
            if [ $ret -eq 0 ]; then 
                echo "install_jdk failed. please check log $pkg_path/process.log"
                exit 0;
            fi
            echo "----> check and install jdk finished.  start to check and install tomcat."
            echo ""

        elif  [ $i -eq 5 ]; then
            check_install_tomcat;
            ret=`cat $pkg_path/ret`
            if [ $ret -eq 0 ]; then 
                echo "install_tomcat failed. please check log $pkg_path/process.log"
                exit 0;
            fi
            echo "----> check and install tomcat finished.  start to check and start java process."
            echo ""

        elif  [ $i -eq 6 ]; then
            start_java_exe;    
            echo "----> check and install java exe finished. install complete."
            echo ""

        fi 
    done 

}

function one_key_install(){
    check_install_db;
    ret=`cat $pkg_path/ret`
    if [ $ret -eq 0 ]; then 
        echo "check_install_db failed. please check log $pkg_path/process.log"
        exit 0;
    fi
    echo "----> check and install db finished. start to check and install consul."
    echo ""

    check_install_consul;
    ret=`cat $pkg_path/ret`
    if [ $ret -eq 0 ]; then 
        echo "install_consul failed. please check log $pkg_path/process.log"
        exit 0;
    fi
    boot_consul;
    echo "----> check and install consul finished.  start to check and install rabbitmq_server. "
    echo ""

    check_install_rabbitmq_server;
    ret=`cat $pkg_path/ret`
    if [ $ret -eq 0 ]; then 
        echo "install_rabbitmq_server failed. please check log $pkg_path/process.log"
        exit 0;
    fi

    boot_rabbitmq;
    echo "----> check and install rabbit finished.  start to check and install jdk."
    echo ""

    check_install_jdk;
    ret=`cat $pkg_path/ret`
    if [ $ret -eq 0 ]; then 
        echo "install_jdk failed. please check log $pkg_path/process.log"
        exit 0;
    fi
    echo "----> check and install jdk finished.  start to check and install tomcat."
    echo ""

    check_install_tomcat;
    ret=`cat $pkg_path/ret`
    if [ $ret -eq 0 ]; then 
        echo "install_tomcat failed. please check log $pkg_path/process.log"
        exit 0;
    fi
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

# $1 db_location
function check_is_installed_db2(){
    # check is not complete.
    if [ $1 -eq 1 ]; then
        # LOCAL
        # local count=`find / -name "db2das" &> ~/pkg/tmp ; grep "db2das" ~/pkg/tmp | wc -l; echo "">~/pkg/tmp`
        local count=`find / -name "db2icrt" &> ~/pkg/tmp ; grep "db2icrt" ~/pkg/tmp | wc -l; echo "">~/pkg/tmp`
    else
        # REMOTE
        local count=`find / -name "db2icrt" &> ~/pkg/tmp ; grep "db2icrt" ~/pkg/tmp | wc -l; echo "">~/pkg/tmp`
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
    expect $shell_path/exp/su_cmd.exp "root" $root_pwd "$shell_path/install_tomcat.sh $pkg_path $install_path $shell_path $app_user $tomcat_path"
}



function check_install_db2(){ 
    if [ -z $db_location ]; then
        while true; 
        do
            read -p "
            input your database location:
                              1) LOCAL
                              2) REMOTE
            db_location:" db_location;
            if [ $db_location -gt 0 ] && [ $db_location -lt 3 ]; then
                break;
            else
                echo "invalid input, please input a choice ranges from [1 - 2]";
            fi
        done
    fi

    if [ $db_location -eq 2 ];then
        # REMOTE
        if [ -z $db_server_ip ]; then
            read -p "input remote db_server_ip:" db_server_ip;
        fi
        if [ -z $db_server_port ]; then
            read -p "input remote db_server_port:" db_server_port;
        fi
    fi 

   if [ -z $db_is_crt_db_flag ]; then
        read -p "
            whether to build a database based on the configuration file:[Y|N]
            your choice:" db_is_crt_db_flag;
        if [ $db_is_crt_db_flag = "Y" ] || [ $db_is_crt_db_flag = "yes" ] || [ $db_is_crt_db_flag = "YES" ] || [ $db_is_crt_db_flag = "y" ]; then 
            db_is_crt_db_flag=1;
        else
            db_is_crt_db_flag=0;
        fi 
    fi

    check_is_installed_db2 $db_location;
    if [ $? -eq 0 ]; then
        expect $shell_path/exp/su_cmd.exp "root" $root_pwd "sh $shell_path/install_db2.sh $pkg_path $install_path $shell_path $db_location $root_pwd";
        check_is_installed_db2 $db_location;
        if [ $? -eq 0 ]; then
            echo "error. db2 install failed. "
            exit 0;
        fi
    fi

    cd $shell_path;
    # check user 
    expect $shell_path/exp/su_cmd.exp "root" "$root_pwd" "sh $shell_path/crt_user.sh $app_user $app_pwd $pkg_path";
    ret=`cat $pkg_path/ret`
    if [ $ret -eq 0 ]; then 
        echo " user create failed."    
        exit 0;
    fi 

    # check_db2 instance scp;
    expect $shell_path/exp/su_cmd.exp "root" "$root_pwd" "sh $shell_path/check_db2_instance.sh $root_pwd $db_instance $shell_path $pkg_path $app_user";
    ret=`cat $pkg_path/ret`
    if [ $ret -eq 0 ]; then 
        echo " db2 instance create failed."    
        exit 0;
    fi 
    # db2start
    expect $shell_path/exp/su_cmd.exp "root" "$root_pwd" "sh $shell_path/db2_start.sh $db_instance $pkg_path $app_user $db_location $db_server_ip $db_server_port $db_name $db_node_name $app_pwd ";
    ret=`cat $pkg_path/ret`
    if [ $ret -eq 0 ]; then 
        echo "db2 start failed. please check it."        
        exit 0;
    fi 
TEST=0
if [ $TEST -eq 1 ]; then
    echo " TEST NOT DO DB2 INIT"
else
    if [ $db_is_crt_db_flag -eq 1 ];then
        # db2init
        expect $shell_path/exp/su_cmd.exp "root" "$root_pwd" "sh $shell_path/db2_init.sh $db_name $shell_path $pkg_path $app_user $app_pwd $test_table $db_instance $db_is_init_db_flag";
        ret=`cat $pkg_path/ret`
        if [ $ret -eq 0 ]; then 
            echo "db2 init failed. please check it."        
            exit 0;
        fi 
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
