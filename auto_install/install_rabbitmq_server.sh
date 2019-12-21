source $(dirname $0)/common.sh
erlang_path=/usr/local/erlang
log_path=""
log_file=""
log_ret=""
log_showpgr=""
log_makeerl=""

# $1 pkg_path
# $2 pkg_version like this 4.4.7-23 TODO:
# simple implementation
function check_install_gcc_cpp_dep(){
    local gcc_cpp_path=`find $1 -name gcc_cpp`
    if [ ! -d $gcc_cpp_path ]; then
        logi "install gcc-c++, dir found, please check it. "    $log_file
        logc "0"                                                $log_ret
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
    logi "prepare to install $1" $log_file
    case "$1" in
        openssl-devel)
            openssldev_path=`find $2 -name openssl-dev`
            if [ ! -d $openssldev_path ];then
                loge    "install no openssl-dev dir found, please check it. "   $log_file
                logc "0"                                                        $log_ret
                exit 0;
            fi
            cd $openssldev_path;
            openssldev_path=`pwd`; 
            rpm -i --force --nodeps $openssldev_path/ins/* >> $log_file;
            rpm -U $openssldev_path/upd/* >> $log_file;;
        gcc-c++|ncurses-devel|openssl|unixODBC-devel|unixODBC)
            if [ "$1" == "unixODBC" ] || [ "$1" == "openssl" ]; then
                find_str="eval find $2 -name $1* | grep -v $1-devel";
            else
                find_str="find $2 -name $1*"
            fi

            comvar_install_pkg_name=""
            get_install_package_name "$find_str";
            if [ -z $comvar_install_pkg_name ]; then 
                loge "no package find [$find_str]"  $log_file
                logc "0"                            $log_ret
                exit 0;
            fi

            local install_pkg_full_name=$comvar_install_pkg_name;

            if [ $1 == "gcc-c++" ];then
                local version=`echo $1 | awk -F\- '{print $2 "-" $3} '| awk -F. '{print $1 "." $2 "." $3}'`
                check_install_gcc_cpp_dep $2 "$version";
            fi

            rpm -ivh $install_pkg_full_name >> $log_file;

            if [ "$1" == "unixODBC" ] || [ "$1" == "openssl" ]; then
                ret=`rpm -qa | grep $1 | grep -v $1-devel | grep x86_64 | wc -l`
            else
                ret=`rpm -qa | grep $1 | grep x86_64 | wc -l`
            fi
            if [ 0 -eq $ret ];then
                loge "install $1 failed.please check it."   $log_file;
                log  "0"                                    $log_ret
                exit 0;
            fi
            logi    "install " $1 "end" $log_file;;

        erlang)
            local find_str="find $2 -name otp_src*.tar.gz"
            comvar_install_pkg_name=""
            get_install_package_name "$find_str";
            if [ -z $comvar_install_pkg_name ]; then
                loge    "no package find [$find_str]"   $log_file
                logc     "0"                            $log_ret
                exit 0;
            fi

            local install_pkg_full_name=$comvar_install_pkg_name;
            if [ ! -d $5/erlang ]; then
                mkdir -p $5/erlang/
                cmd_uncompress=""
                cmd_uncompress_dir=""
                get_uncompress_cmd `basename $install_pkg_full_name`

                $cmd_uncompress $install_pkg_full_name $cmd_uncompress_dir $5/erlang/>/dev/null 2>/dev/null;
            fi

            # add progress 
            {
                sh $3/show_progress.sh $5/erlang/ 307963545 "make_erlang...">>$log_file
            }&

            cd $5/erlang/otp_src_*
            ./configure --prefix=$erlang_path --enable-hipe --enable-threads --enable-smp-support --enable-kernel-poll  --without-javac >> $log_makeerl  2>&1
            make >>$log_makeerl 2>&1
            make install >>$log_makeerl  2>&1

            wait;

            env_ret=`echo $PATH | grep $erlang_path/bin | wc -l`
            if [ $env_ret -eq 0 ]; then
                echo "export PATH=$erlang_path/bin:$PATH">>/etc/profile
             fi

            source /etc/profile
            export PATH=$erlang_path/bin:$PATH;
            ret=`erl 2>/dev/null <<!
halt().
!`;
            local erl_ret=`echo $ret | grep Eshell | wc -l`
            if [ 0 -eq $erl_ret ];then
                logi "install erlang failed .please check log $install_cpx_log" $log_file
                logc "0"                                                        $log_ret
                exit 0;
            fi

            logi    "install " $1 "end" $log_file;;
        *)
            loge "not support package ."    $log_file
            logc "0"                        $log_ret;;
    esac
    logc    "1" $log_ret
}


# $1 pkg_path
# $2 shell_path
# $3 root_pwd
# $4 install path
function check_dependency(){
    # check ncurses-devel
    has_ncurses_devel=`rpm -qa | grep ncurses-devel | grep x86_64 | wc -l`
    if [ 0 -eq $has_ncurses_devel ];then
        logi    "start to install ncurses-devel."   $log_file
        do_install_dep "ncurses-devel" $1 $2 $3 $4;
    fi
    logi    "chech ncurses-devel end. version is [`rpm -qa | grep ncurses-devel | grep x86_64`]"    $log_file

    # check openssl
    has_openssl=`rpm -qa | grep openssl | grep -v "openssl-devel"| grep x86_64 | wc -l`
    if [ 0 -eq $has_openssl ];then
        logi    "start to install openssl." $log_file
        do_install_dep "openssl" $1 $2 $3 $4;
    fi
    logi "chech openssl end. version is [`rpm -qa | grep openssl | grep -v openssl-devel | grep x86_64`]"  $log_file

    # check openssl-devel
    has_openssl_dev=`rpm -qa | grep -w openssl-devel | grep x86_64 | wc -l`
    if [ 0 -eq $has_openssl_dev ];then
        logi "start to install openssl-devel." $log_file
        do_install_dep "openssl-devel" $1 $2 $3 $4;
    fi
    logi "chech openssl-devel end. version is [`rpm -qa | grep -w openssl-devel | grep x86_64`]"    $log_file

    # check unixODBC
    has_odbc=`rpm -qa | grep -w unixODBC | grep x86_64 | grep -v devel | wc -l`;
    if [ 0 -eq $has_odbc ];then
        logi "start to install unixODBC."   $log_file
        do_install_dep "unixODBC" $1 $2 $3 $4;
    fi
    logi "chech unixODBC end. version is [`rpm -qa | grep -w unixODBC | grep x86_64 | grep -v devel`]"   $log_file

    has_odbc_devel=`rpm -qa | grep unixODBC-devel|grep x86_64|wc -l`
    if [ 0 -eq $has_odbc_devel ];then
        logi "start to install unixODBC-devel." $log_file
        do_install_dep "unixODBC-devel" $1 $2 $3 $4;
    fi
    logi "chech unixODBC-devel end. version is [`rpm -qa | grep unixODBC-devel|grep x86_64`]"    $log_file

    # check gcc-c++
    has_gcc=`rpm -qa | grep -w gcc-c++ | grep x86_64| wc -l`
    if [ 0 -eq $has_gcc ];then
        logi "start to install gcc-c++."    $log_file
        do_install_dep "gcc-c++" $1 $2 $3 $4;
    fi
    logi "chech gcc-c++ end. version is [`rpm -qa | grep -w gcc-c++ | grep x86_64`]"    $log_file

    # check erlang
    has_erlang_str=`erl 2>/dev/null <<!
halt().
!`;
    has_erlang=`echo $has_erlang_str | grep Eshell | wc -l`
    if [ 0 -eq $has_erlang ];then
        logi    "start to install erlang."  $log_file
        do_install_dep "erlang" $1 $2 $3 $4;
    fi
    logi "chech erlang end" $log_file
}

# $1 -- pkg_path
# $2 -- shell_path
# $3 -- root_pwd
# $4 -- install_path
# $5 -- rabbit mq path
# $6 -- 
#
function check_install_rabbitmq_server(){
    local scp_base_path=`dirname $2`
    log_path=$scp_base_path/log
    log_file=$log_path/process.log
    log_ret=$log_path/ret
    log_showpgr=$log_path/show_progress_ret
    log_makeerl=$log_path/makeerl.log


    logd    "check_install_rabbitmq_server start."  $log_file
    #cd $4;

    local find_str="find $1 -name rabbitmq-server*"

    comvar_install_pkg_name=""
    get_install_package_name "$find_str";
    if [ -z $comvar_install_pkg_name ]; then
        loge    "no rabbitmq-server package found." $log_file
        logc    "0"                                 $log_ret
        exit 0;
    fi
    
    local pkg_mq_server_name=$comvar_install_pkg_name;
    # instal rabbitmq pkg
    check_dependency $1 $2 $3 $4;

    if [ ! -d $4/rabbitmq_server* ]; then
        {
            sh $2/show_progress.sh $5 4534546 "install_rabbit_ser..." >>$log_path/process.log
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

    wait;

    chmod -R 777 $5;

    env_ret=`echo $PATH | grep "$5/sbin" | wc -l`
    if [ $env_ret -eq 0 ]; then
    	echo "export PATH=$5/sbin:$PATH">>/etc/profile;
    fi

    logi    "install rabbitmq_server suc. [path=$5]"    $log_file
    logc    "1"                                         $log_ret
}
check_install_rabbitmq_server $1 $2 $3 $4 $5;
