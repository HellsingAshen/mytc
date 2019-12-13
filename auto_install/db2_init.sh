# $1 -- db_name 
# $2 -- shell_path
# $3 -- pkg_path
# $4 -- db2user
# $5 -- db2pwd 
# $6 -- test_tables 
# $7 -- db instance 
# $8 -- db is init flag 

# check db exist 
count=`su - $4 -c "db2 list db directory | grep -i \"Database name\" | grep -i $1 | wc -l"`
if [ $count -eq 0 ]; then
    # created if not exist
    su - $4 -c "mkdir -p  ~/shell_path"
    cp $2/db2_crt_db.sh /home/$4/shell_path;
    chmod 777 /home/$4/shell_path/*.sh;

    # show progress
    {
        sh $2/show_continue.sh "crt_db"
    } 2>/dev/null &

    su - $4 -c "~/shell_path/db2_crt_db.sh" > /dev/null 2>&1;
    
    sh $2/stop_show_continue.sh > /dev/null 2>&1;

    count=`su - $4 -c "db2 list db directory | grep -i \"Database name\" | grep -i $1 | wc -l"`
    if [ $count -eq 0 ]; then
        echo "[`date "+%Y-%m-%d %H:%M:%S"`]create db $1 failed.">>$3/process.log
        echo "0">$3/ret
        exit 0;
    fi
fi

echo "[`date "+%Y-%m-%d %H:%M:%S"`]db2 check exist suc.">>$3/process.log

test=1
if [ $test -eq 1 ]; then
    su - $4 -c "mkdir -p  ~/shell_path"
    cp $2/db2_init_sql.sh /home/$4/shell_path;
    cp -r $2/init_sql /home/$4/shell_path/
    chmod 777 /home/$4/shell_path/*.sh;

    # show progress
    {
        sh $2/show_continue.sh "init_db"
    } 2>/dev/null &

    su - $4 -c "sh /home/$4/shell_path/db2_init_sql.sh $1 $4 $5 ~/shell_path"

    sh $2/stop_show_continue.sh;
else 
    # check before init
    ret=`su - $4 -c "db2 connect to $7 user $4 using $5>/dev/null 2>&1; db2 list tables | grep  $6 | wc -l"`
    cnt=`echo $ret| awk '{print $19}'`
    if [ $cnt -eq 0 ]; then
        # excute init sql
        su - $4 -c "mkdir -p  ~/shell_path"
        cp $2/db2_init_sql.sh /home/$4/shell_path;
        cp -r $2/init_sql /home/$4/shell_path/
        chmod 777 /home/$4/shell_path/*.sh;

        # show progress
        {
            sh $2/show_continue.sh "crt_db"
        }&

        su - $4 -c "sh /home/$4/shell_path/db2_init_sql.sh $1 $4 $5 ~/shell_path"

        kill_pid=`ps -ef | grep show_continue.sh | grep -v grep | awk '{print $2}'`
        for i in $kill_pid
        do
            echo " kill process " $i
            kill -9 $i >/dev/null 2>&1
        done 

        ret=`su - $4 -c "db2 connect to $7 user $4 using $5; db2 list tables | grep  $6 | wc -l"`
        cnt=`echo $ret| awk '{print $19}'`
        if [ $cnt -eq 0 ]; then
            echo "[`date "+%Y-%m-%d %H:%M:%S"`]init db $1 failed.">>$3/process.log
            echo "0">$3/ret
            exit 0;
        fi
    fi
fi

echo "[`date "+%Y-%m-%d %H:%M:%S"`]db2 init sql suc.">>$3/process.log
echo "1">$3/ret

