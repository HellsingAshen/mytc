# $1 -- pkg_path
# $2 -- install_path
# $3 -- shell_path
# $4 -- db location
# $5 -- root_pwd

db_default_path="/opt/ibm/db2/"

source $3/common.sh
function install_db2(){
    cd $pkg_path;            

    local find_str="find $1 -name v*linuxx64_server*.tar.gz"
    comvar_install_pkg_name=""
    get_install_package_name "$find_str";
    if [ -z $comvar_install_pkg_name ]; then
        echo "[`date "+%Y-%m-%d %H:%M:%S"`]no db2 package found.">>$1/process.log
        echo "0">$1/ret
        exit 0;
    fi
    local install_pkg_full_name=$comvar_install_pkg_name;

    if [ ! -d $2/server_t ]; then
        cmd_uncompress=""
        cmd_uncompress_dir=""
        get_uncompress_cmd `basename $install_pkg_full_name`
        {
            sh $3/show_progress.sh $2/server_t 2342419226 "uncompress_db2..."
        }&
       $cmd_uncompress $install_pkg_full_name $cmd_uncompress_dir $2>/dev/null 2>&1;
       wait
    fi
    echo ""

    cd $2/server_t;
    count=`ls | grep db2_install | wc -l`
    # check it for using large space
    if [ $count -ne 1 ]; then
        echo "db2 package error. please check it."
        echo "[`date "+%Y-%m-%d %H:%M:%S"`]db2 uncompress error, no db2_install found, please check it .">>$1/process.log
        echo "0">$1/ret
        exit 0;
    fi

    if [ $4 -eq 1 ]; then 
        # LOCAL
        # 1742269544
        {
	     sh $3/show_progress.sh $db_default_path 1739250405 "install_db2s"
	}&
        expect $3/exp/su_cmd.exp "root" $5 "sh $3/install_db2s.sh $2 $3">/dev/null
        wait
    else
        {
	     sh $3/show_progress.sh $db_default_path 712926603 "install_db2c"
	}&
        # REMOTE
        # total size is 712926603
        expect $3/exp/su_cmd.exp "root" $5 "sh $3/install_db2c.sh $2 $3">/dev/null
        wait
    fi

    local check_flag=`find / -name db2icrt | grep -v "Permission denied" | wc -l`
    if [ $check_flag -eq 0 ]; then
        echo "0">$1/ret
        echo "[`date "+%Y-%m-%d %H:%M:%S"`]install db2 failed. please check it.">$1/process.log
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
        $lincese_cmd -a $2/lincese/*/db2ese_c.lic>/dev/null 2>&1
    fi

    echo "[`date "+%Y-%m-%d %H:%M:%S"`]install db2 suc.">$1/process.log
    echo "1">$1/ret
}

install_db2 $1 $2 $3 $4 $5;
