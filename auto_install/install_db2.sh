# $1 -- pkg_path
# $2 -- install_path
# $3 -- shell_path
# $4 -- db location
# $5 -- root_pwd
# $6 -- db version

db_default_path="/opt/ibm/db2/"

source $3/common.sh
function install_db2(){
    local scp_base_path=`dirname $3`
    local log_path=$scp_base_path/log
    local log_file=$log_path/process.log
    local log_ret=$log_path/ret
    local log_db=$log_path/install_db.log
    
    # set show progress size
    if [ $6 -eq 10 ]; then
        install_db2c_size=663365886
        install_db2s_size=1337545651
        uncompress_db2_size=2145302520
    else
        # v11
        install_db2c_size=712926603
        install_db2s_size=1739250405
        uncompress_db2_size=2342419226
    fi

    cd $pkg_path;            

    local find_str="find $1 -name v$6*linuxx64_server*.tar.gz"
    comvar_install_pkg_name=""
    get_install_package_name "$find_str";
    if [ -z $comvar_install_pkg_name ]; then
        loge    "no db2 package found." $log_file
        logc    "0" $log_ret
        exit 0;
    fi
    local install_pkg_full_name=$comvar_install_pkg_name;

    if [ ! -d $2/server_t ]; then
        cmd_uncompress=""
        cmd_uncompress_dir=""
        get_uncompress_cmd `basename $install_pkg_full_name`
        {   #v11 2342419226    v10 2145302520
            sh $3/show_progress.sh $2/server_t $uncompress_db2_size "uncompress_db2..."
        }&
       $cmd_uncompress $install_pkg_full_name $cmd_uncompress_dir $2 >>$log_db 2>&1;
       wait
    fi
    echo ""

    cd $2/server_t;
    count=`ls | grep db2_install | wc -l`
    # check it for using large space
    if [ $count -ne 1 ]; then
        loge    "db2 uncompress error, no db2_install found, please check it ." $log_file
        logc    "0"  $log_ret
        exit 0;
    fi

    if [ $4 -eq 1 ]; then 
        # LOCAL
        # 1742269544 v11
        {
	        sh $3/show_progress.sh $db_default_path $install_db2s_size "install_db2s"
        }&
        expect $3/exp/su_cmd.exp "root" $5 "sh $3/install_db2s.sh $2 $3">>$log_db
        wait
    else
        {
	        sh $3/show_progress.sh $db_default_path $install_db2c_size "install_db2c"
	    }&
        # REMOTE
        # total size is 712926603
        expect $3/exp/su_cmd.exp "root" $5 "sh $3/install_db2c.sh $2 $3 $6" >>$log_db
        wait
    fi

    local check_flag=`find / -name db2icrt 2>/dev/null | wc -l`
    if [ $check_flag -eq 0 ]; then
        logc    "0" $log_ret
        loge    "install db2 failed. please check it."  $log_file
        exit 0;
    fi

    if [ $4 -eq 1 ]; then 
        db2_lincese=`find $1 -name db2_*_lincese.zip`
        count=`find $1 -name db2_*_lincese.zip | wc -l`
        if [ $count -ne 1 ]; then 
            echo "please manual injection lincese"
            exit 0;
        fi

        mkdir -p $2/lincese

        cmd_uncompress=""
        cmd_uncompress_dir=""
        get_uncompress_cmd `basename $db2_lincese`
        $cmd_uncompress $db2_lincese $cmd_uncompress_dir $2/lincese

        lincese_cmd=`find $db_default_path -name db2licm`
        $lincese_cmd -a $2/lincese/*/db2ese_c.lic>>$log_path/install_db.log 2>&1
    fi

    logi    "install db2 suc."  $log_file
    logc    "1"                 $log_ret
}

install_db2 $1 $2 $3 $4 $5 $6;
