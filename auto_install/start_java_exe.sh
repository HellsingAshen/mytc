# $1 pkg path
# $2 app user

function run_jar(){
    home_path=`cat /etc/passwd | grep $2 | awk -F: '{print $6}'`;
    if [ ! -d $home_path/jar ]; then
        mkdir -p $home_path/jar;
        if [ ! -d $home_path/jar ]; then
            echo " create dir failed when running jar.please check it .">$1/process.log
            echo "0"/ret
            exit 0;
        fi
    fi
    
    cp $1/jar/*.jar $home_path/jar;

    for i in `ls $home_path/jar/*.jar`
    do
        local base_pro=`basename $i`
        local count=`ps -ef | grep -v grep | grep $2 | grep $base_pro | wc -l`;
        if [ $count -eq 0 ]; then
            su - $2 -c "nohup java -jar $i >/dev/null 2>&1 &"
            count=`ps -ef | grep -v grep | grep $2 | grep $base_pro | wc -l`;
            if [ $count -eq 0 ]; then
                echo "[`date "+%Y-%m-%d %H:%M:%S"`]start $base_pro failed .">>$1/process.log
                echo "0">>$pkg_path/ret
            else
                echo "[`date "+%Y-%m-%d %H:%M:%S"`]start $base_pro suc.">>$1/process.log
            fi
        fi
    done
}

run_jar $1 $2
