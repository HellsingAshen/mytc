# $1 pkg_path
# $2 install_pkg_path
# $3 shell_path
# $4 app_user
# $5 tomcat_path

source $3/common.sh
#tomcat_path=""

function check_install_tomcat(){
    # check exist 
    if [ -d $5/bin ]; then
        echo "[`date "+%Y-%m-%d %H:%M:%S"`]Tomcat install suc.">>$1/process.log
        echo "1">$1/ret
        exit 0;
    fi

    tomcat_path=$5
    find_str="find $1 -name apache-tomcat*"

    comvar_install_pkg_name=""
    get_install_package_name "$find_str";
    if [ -z $comvar_install_pkg_name ]; then
        echo "[`date "+%Y-%m-%d %H:%M:%S"`]no tomcat package found.">>$1/process.log
        echo "0">$1/ret
        exit 0;
    fi

    local install_pkg_full_name=$comvar_install_pkg_name;
    local install_pkg_base_name=`basename $install_pkg_full_name`;

    if [ ! -d $5 ]; then
        mkdir -p $5 ;
        if [ ! -d $5 ]; then
            echo "[`date "+%Y-%m-%d %H:%M:%S"`]permission denied. please check current user.">>$1/process.log
            echo "0">$1/ret
            exit 0;
        fi
    fi

    {
         sh $3/show_progress.sh $tomcat_path 14995413 "install_tomcat..."
    }&

    if [ ! -d $5/bin ]; then
        cmd_uncompress=""
        cmd_uncompress_dir=""
	get_uncompress_cmd `basename  $install_pkg_full_name`
        #$cmd_uncompress $install_pkg_full_name $cmd_uncompress_dir $5  --strip-components "1" >/dev/null &;
        $cmd_uncompress $install_pkg_full_name $cmd_uncompress_dir $5  --strip-components "1" >/dev/null;
        chmod -R 777 $5;

        env_ret=`echo $PATH | grep "$5/bin" | wc -l`
        if [ $env_ret -eq 0 ]; then
            echo "export PATH=$5/bin:$PATH">>/etc/profile
        fi

        echo "[`date "+%Y-%m-%d %H:%M:%S"`]Tomcat install path is [ tomcat_path = $5 ]">>$1/process.log
        echo "1">$1/ret
    else 
        echo "[`date "+%Y-%m-%d %H:%M:%S"`]Tomcat install failed.">>$1/process.log
        echo "0">$1/ret
    fi
    wait;

    echo "[`date "+%Y-%m-%d %H:%M:%S"`]Tomcat install suc.">>$1/process.log
    echo "1">$1/ret
    
}

check_install_tomcat $1 $2 $3 $4 $5;

