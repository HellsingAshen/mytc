# $1 -- pkg_path
# $2 -- install_path
# $3 -- shell_path
# $4 -- app_user


source $3/common.sh

function check_install_jdk(){
    ret=`su - $4 -c "java -version 2>&1 |grep \"java version\" |wc -l"`
    if [ 0 -eq $ret ]; then
        local find_str="find $1 -name jdk*.rpm";
        get_install_package_name "$find_str";
        if [ -z $comvar_install_pkg_name ]; then
            echo "no package find $find_str">>$1/process.log
            echo "0">$1/ret
            exit 0;
        fi 

        local install_pkg_consul_name=$comvar_install_pkg_name;
        rpm -ivh $install_pkg_consul_name;
        ret=`su - $4 -c "java -version 2>&1 |grep \"java version\" |wc -l"`
        if [ 0 -eq $ret ]; then
            echo "package install failed.please check it">>$1/process.log
            echo "0">$1/ret
            exit 0;
        fi
    fi

    echo "package jdk install suc.">>$1/process.log
    echo "1">$1/ret
}

check_install_jdk $1 $2;
