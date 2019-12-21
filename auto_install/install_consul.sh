# $1 -- shell path
# $2 -- install path
# $3 -- app_user
# $4 -- consul path

source $(dirname $0)/common.sh

function check_install_consul(){
    local scp_base_path=`dirname $1`
    local third_path=$scp_base_path/3rd
    local install_path=$2;
    local log_path=$scp_base_path/log
    local log_file=$log_path/process.log
    local log_ret=$log_path/ret

    local ret=`su - $3 -c "consul -v 2>&1 | grep Consul | wc -l"`
    if [ 0 -eq $ret ]; then
        local find_str="find $third_path -name consul*.*"
        comvar_install_pkg_name=""
        get_install_package_name "$find_str";
        if [ -z $comvar_install_pkg_name ]; then
            loge    "no consul package found."  $log_file
            logc    "0"                         $log_ret
            exit 0;
        fi
        local install_pkg_consul_name=$comvar_install_pkg_name;

        cmd_uncompress=""
        cmd_uncompress_dir=""
        get_uncompress_cmd `basename $install_pkg_consul_name`
        #$cmd_uncompress $install_pkg_consul_name $cmd_uncompress_dir $install_path; 

        if [ ! -d $4 ]; then 
            mkdir -p $4;
        fi
        $cmd_uncompress $install_pkg_consul_name $cmd_uncompress_dir $4; 

        #cp $install_path/consul $4/;

        env_ret=`echo $PATH | grep "$4" | wc -l`
        if [ $env_ret -eq 0 ]; then
            echo "export PATH=\$PATH:$4/">>/etc/profile
        fi

        ret=`su - $3 -c "consul -v 2>&1|grep Consul | wc -l"`
        if [ 0 -eq $ret ]; then
            loge    "install consul failed .please check it."   $log_file
            logc    "0"                                         $log_ret
            exit 0;
        fi
    fi

    logi    "consul install suc. [path=$PATH]"  $log_file
    logc    "1"                                 $log_ret
}

check_install_consul $1 $2 $3 $4;
