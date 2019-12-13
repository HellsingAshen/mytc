# $1 -- pkg_path
# $2 -- install_path
# $3 -- shell_path
# $4 -- root_pwd
# $5 -- app_user
# $6 -- consul_path

source $3/common.sh
function check_install_consul(){
    
    local install_path=$2;
    local ret=`su - $5 -c "consul -v 2>&1 | grep Consul | wc -l"`
    if [ 0 -eq $ret ]; then
        local find_str="find $1 -name consul*.zip"
        comvar_install_pkg_name=""
        get_install_package_name "$find_str";
        if [ -z $comvar_install_pkg_name ]; then
            echo "[`date "+%Y-%m-%d %H:%M:%S"`]no consul package found.">>$1/process.log
            echo "0">$1/ret
            exit 0;
        fi
        local install_pkg_consul_name=$comvar_install_pkg_name;

        #unzip $install_pkg_consul_name -d  $install_path;
        cmd_uncompress=""
        cmd_uncompress_dir=""
        get_uncompress_cmd `basename $install_pkg_consul_name`
        $cmd_uncompress $install_pkg_consul_name $cmd_uncompress_dir $install_path; 

        if [ ! -d $6 ]; then 
            mkdir -p $6;
        fi
        cp $install_path/consul $6/;

        env_ret=`echo $PATH | grep "$6" | wc -l`
        if [ $env_ret -eq 0 ]; then
            echo "export PATH=\$PATH:$6/">>/etc/profile
        fi

        ret=`su - $5 -c "consul -v 2>&1|grep Consul | wc -l"`
        if [ 0 -eq $ret ]; then
            echo "[`date "+%Y-%m-%d %H:%M:%S"`]install consul failed .please check it.">>$1/process.log
            echo "0">$1/ret
            exit 0;
        fi
    fi
}

check_install_consul $1 $2 $3 $4 $5 $6;
echo "[`date "+%Y-%m-%d %H:%M:%S"`]consul install suc. [path=$PATH]">>$1/process.log
echo "1">$1/ret


