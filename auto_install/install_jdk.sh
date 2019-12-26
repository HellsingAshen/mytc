# $1 -- pkg_path
# $2 -- install_path
# $3 -- shell_path
# $4 -- app_user

source $(dirname $0)/common.sh
java_base_version=1.8

function check_install_jdk(){
    local scp_base_path=`dirname $1`
    local log_path=$scp_base_path/log
    local log_file=$log_path/process.log
    local log_ret=$log_path/ret

    # 1 -- install     2 -- update
    local op_flag=0;

    ret=`su - $4 -c "java -version 2>&1 |grep \"java version\" |wc -l"`
    if [ 0 -eq $ret ]; then
        op_flag=1;
    else
        ver=`java -version 2>&1 |grep java | awk -F "\"" '{print $2}' | awk -F "." '{print $1"."$2}'`
        java_base_version=1.8
        if [ $(echo "$java_base_version > $ver"|bc) -eq 1 ];then
            op_flag=2;
        fi
    fi

    if [ $op_flag -eq 1 ] || [ $op_flag -eq 2 ]; then
        local find_str="find $1 -name jdk*.rpm";
        get_install_package_name "$find_str";
        if [ -z $comvar_install_pkg_name ]; then
            loge    "no package find $find_str" $log_file
            logc    "0"                         $log_ret
            exit 0;
        fi 

        local install_pkg_name=$comvar_install_pkg_name;
        if [ $op_flag -eq 1 ]; then
            rpm -ivh $install_pkg_name;
            logd    "jdk package [$install_pkg_name] has been installed."  $log_file
        else
            # rpm -U $install_pkg_name;
            rpm -i --force --nodeps $install_pkg_name
            logd    "jdk package [$install_pkg_name] has been updated."    $log_file
        fi

        ret=`su - $4 -c "java -version 2>&1 |grep \"java version\" |wc -l"`
        if [ 0 -eq $ret ]; then
            loge    "package install failed.please check it"    $log_file
            logc    "0"                                         $log_ret
            exit 0;
        fi
    fi

    logi    "package jdk install suc."  $log_file
    logc    "1"                         $log_ret
}

check_install_jdk $1 $2 $3 $4;
