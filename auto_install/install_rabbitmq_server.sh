source $2/common.sh
erlang_path=/usr/local/erlang
#cmd_uncompress="tar -zxvf "
rabbitmq_server_path=/usr/local/rabbitmq_server

# $1 pkg_path
# $2 pkg_version like this 4.4.7-23 TODO:
# simple implementation
function check_install_gcc_cpp_dep(){
    local gcc_cpp_path=`find $1 -name gcc_cpp`
    if [ ! -d $gcc_cpp_path ]; then
        echo "install gcc-c++, dir found, please check it. ">>$1/process.log
        echo "0">>$1/ret
        exit 0;
    fi
    rpm -i --force --nodeps $gcc_cpp_path/ins/*;
    rpm -U $gcc_cpp_path/upd/*;
}
# $1 -- install name str
# $2 -- pkg_path
# $3 -- shell_path
# $4 -- root_pwd
# $5 -- install path
# install dependency by name
function do_install_dep(){
    echo "prepare to install " $1
    case "$1" in
        openssl-devel)
            openssldev_path=`find $2 -name openssl-dev`
            if [ ! -d $openssldev_path ];then
                echo "install no openssl-dev dir found, please check it. ">>$2/process.log
                echo "0">>$2/ret
                exit 0;
            fi
            cd $openssldev_path;
            openssldev_path=`pwd`; 
            rpm -i --force --nodeps $openssldev_path/ins/*;
            rpm -U $openssldev_path/upd/*;;
        gcc-c++|ncurses-devel|openssl|unixODBC-devel|unixODBC)
            if [ "$1" == "unixODBC" ] || [ "$1" == "openssl" ]; then
                find_str="eval find $2 -name $1* | grep -v $1-devel";
            else
                find_str="find $2 -name $1*"
            fi

            comvar_install_pkg_name=""
            get_install_package_name "$find_str";
            if [ -z $comvar_install_pkg_name ]; then 
                echo "no package find [$find_str]">>$2/process.log
                echo "0">$2/ret
                exit 0;
            fi

            local install_pkg_full_name=$comvar_install_pkg_name;

            if [ $1 == "gcc-c++" ];then
                local version=`echo $1 | awk -F\- '{print $2 "-" $3} '| awk -F. '{print $1 "." $2 "." $3}'`
                check_install_gcc_cpp_dep $2 "$version";
            fi

            rpm -ivh $install_pkg_full_name;

            #if [ $1 == "unixODBC" ]; then
            if [ "$1" == "unixODBC" ] || [ "$1" == "openssl" ]; then
                ret=`rpm -qa | grep $1 | grep -v $1-devel | grep x86_64 | wc -l`
            else
                ret=`rpm -qa | grep $1 | grep x86_64 | wc -l`
            fi
            if [ 0 -eq $ret ];then
                echo "install $1 failed.please check it.">>$2/process.log;
                echo "0">>$2/ret;
                exit 0;
            fi
            echo "install " $1 "end">>$2/process.log;;

        erlang)
            local find_str="find $2 -name otp_src*.tar.gz"
            comvar_install_pkg_name=""
            get_install_package_name "$find_str";
            if [ -z $comvar_install_pkg_name ]; then
                echo "no package find [$find_str]">>$2/process.log
                echo "0">>$2/ret
                exit 0;
            fi

            local install_pkg_full_name=$comvar_install_pkg_name;
        
            if [ ! -d $5/erlang ]; then
                mkdir -p $5/erlang/
                cmd_uncompress=""
                cmd_uncompress_dir=""
                get_uncompress_cmd `basename $install_pkg_full_name`
                {
                    sh $3/show_progress.sh $5/erlang/ 207691534 "uncompress_erlang..."
                }&
                $cmd_uncompress $install_pkg_full_name $cmd_uncompress_dir $5/erlang/>/dev/null;
                wait;
            fi
            # add progress 
            {
		echo ""
                sh $3/show_progress.sh $5/erlang/ 307963545 "make_erlang..."
            }&

            cd $5/erlang/otp_src_*
            ./configure --prefix=$erlang_path --enable-hipe --enable-threads --enable-smp-support --enable-kernel-poll  --without-javac>/dev/null 2>&1
            make>/dev/null 2>&1;
            make install>/dev/null 2>&1;
            wait;

            env_ret=`echo $PATH | grep $erlang_path/bin | wc -l`
            if [ $env_ret -eq 0 ]; then
                echo "export PATH=$erlang_path/bin:$PATH">>/etc/profile
             fi
         #   echo "export PATH=$erlang_path/bin:$PATH">>/etc/profile

            source /etc/profile
            export PATH=$erlang_path/bin:$PATH;
            ret=`erl 2>/dev/null <<!
halt().
!`;
            local erl_ret=`echo $ret | grep Eshell | wc -l`
            if [ 0 -eq $erl_ret ];then
                echo "install erlang failed .please check log $install_cpx_log">>$2/process.log
                echo "0">>$2/ret
                exit 0;
            fi

            echo "install " $1 "end">>$2/process.log;;
        *)
            echo "not support package .">>$2/process.log
            echo "0">>$2/ret
    esac
}


# $1 pkg_path
# $2 shell_path
# $3 root_pwd
# $4 install path
function check_dependency(){
    # check ncurses-devel
    has_ncurses_devel=`rpm -qa | grep ncurses-devel | grep x86_64 | wc -l`
    if [ 0 -eq $has_ncurses_devel ];then
        do_install_dep "ncurses-devel" $1 $2 $3 $4;
    fi
    echo "[`date "+%Y-%m-%d %H:%M:%S"`]chech ncurses-devel end">>$1/process.log

    # check openssl
    has_openssl=`rpm -qa | grep openssl | grep -v "openssl-devel"| grep x86_64 | wc -l`
    if [ 0 -eq $has_openssl ];then
        do_install_dep "openssl" $1 $2 $3 $4;
    fi
    echo "[`date "+%Y-%m-%d %H:%M:%S"`]chech openssl end">>$1/process.log

    # check openssl-devel
    has_openssl_dev=`rpm -qa | grep -w openssl-devel | grep x86_64 | wc -l`
    if [ 0 -eq $has_openssl_dev ];then
        do_install_dep "openssl-devel" $1 $2 $3 $4;
    fi
    echo "[`date "+%Y-%m-%d %H:%M:%S"`]chech openssl-devel end">>$1/process.log

    # check unixODBC
    has_odbc=`rpm -qa | grep -w unixODBC | grep x86_64 | grep -v devel | wc -l`;
    if [ 0 -eq $has_odbc ];then
        do_install_dep "unixODBC" $1 $2 $3 $4;
    fi
    echo "[`date "+%Y-%m-%d %H:%M:%S"`]chech unixODBC end">>$1/process.log

    has_odbc_devel=`rpm -qa | grep unixODBC-devel|grep x86_64|wc -l`
    if [ 0 -eq $has_odbc_devel ];then
        do_install_dep "unixODBC-devel" $1 $2 $3 $4;
    fi
    echo "[`date "+%Y-%m-%d %H:%M:%S"`]chech unixODBC-devel end">>$1/process.log

    # check gcc-c++
    has_gcc=`rpm -qa | grep -w gcc-c++ | grep x86_64| wc -l`
    if [ 0 -eq $has_gcc ];then
        do_install_dep "gcc-c++" $1 $2 $3 $4;
    fi
    echo "[`date "+%Y-%m-%d %H:%M:%S"`]chech gcc-c++ end">>$1/process.log

    # check erlang
    has_erlang_str=`erl 2>/dev/null <<!
halt().
!`;
    has_erlang=`echo $has_erlang_str | grep Eshell | wc -l`
    if [ 0 -eq $has_erlang ];then
        do_install_dep "erlang" $1 $2 $3 $4;
    fi
    echo "[`date "+%Y-%m-%d %H:%M:%S"`]chech erlang end">>$1/process.log
}

# $1 -- pkg_path
# $2 -- shell_path
# $3 -- root_pwd
# $4 -- install_path
# $5 -- rabbit mq path
# $6 -- 
#
function check_install_rabbitmq_server(){
    echo "[`date "+%Y-%m-%d %H:%M:%S"`]check_install_rabbitmq_server start.">>$1/process.log
    cd $4;

    local find_str="find $1 -name rabbitmq-server*"

    comvar_install_pkg_name=""
    get_install_package_name "$find_str";
    if [ -z $comvar_install_pkg_name ]; then
        echo "[`date "+%Y-%m-%d %H:%M:%S"`]no rabbitmq-server package found.">>$1/process.log
        echo "0">$1/ret
        exit 0;
    fi
    
    local pkg_mq_server_name=$comvar_install_pkg_name;
    # instal rabbitmq pkg
    check_dependency $1 $2 $3 $4;


    if [ ! -d $4/rabbitmq_server* ]; then
        {
            sh $2/show_progress.sh $5 4534546 "install_rabbit_ser..."
        }&
        cmd_uncompress=""
        cmd_uncompress_dir=""
        get_uncompress_cmd `basename $pkg_mq_server_name`
        $cmd_uncompress $pkg_mq_server_name $cmd_uncompress_dir $4>/dev/null 2>&1;
    fi 

    if [ ! -d $5 ]; then
       mkdir -p $5;
    fi 

    cd $4/rabbitmq_server*/;
    local mq_path=`pwd`
    cp -r $mq_path/* $5/
    chmod -R 777 $5;

    wait;
    env_ret=`echo $PATH | grep "$5/sbin" | wc -l`
    if [ $env_ret -eq 0 ]; then
    	echo "export PATH=$5/sbin:$PATH">>/etc/profile;
    fi

    echo "[`date "+%Y-%m-%d %H:%M:%S"`]install rabbitmq_server suc. [path=$5]">>$1/process.log;
    echo "1">$1/ret;
}
check_install_rabbitmq_server $1 $2 $3 $4 $5;
