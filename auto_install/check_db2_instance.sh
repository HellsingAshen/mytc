# para 1 -- root_pwd
# para 2 -- instance name
# para 3 -- shell path
# para 4 -- pkg path
# para 5 -- instance user
ret=`su - $5 -c "db2ilist 2>/dev/null | grep scp | wc -l"`
if [ $ret -eq 0 ]; then 
    count=`find / -name db2icrt | wc -l`;
    if [ $count -ne 1 ]; then
        echo " find db2icrt count is $count, please check it ."
        echo "[`date "+%Y-%m-%d %H:%M:%S"`]can't find db2icrt.">>$4/process.log
        echo "0">$4/ret
        exit 0;
    fi
    db2_cmd_db2icrt=`find / -name db2icrt`;

    home_path=`cat /etc/passwd | grep $5 | awk -F: '{print $6}'`;
    {
	# 9149173 client origin 33448697
        sh $3/show_progress.sh $home_path/sqllib 9149173 "crt_db2instance"
    }&
    $db2_cmd_db2icrt -u $5 $2>/dev/null
    wait;

    ret=`su - $5 -c "db2ilist 2>/dev/null | grep $2 | wc -l"`
    if [ $ret -ne 1 ]; then
         echo "error while do [db2icrt -u scp scp]"
         echo "[`date "+%Y-%m-%d %H:%M:%S"`] db2icrt. failed. please check it.">>$4/process.log
         echo "0">$4/ret
         exit 0;
    fi
fi

echo "[`date "+%Y-%m-%d %H:%M:%S"`] db2 instance check $2 suc.">>$4/process.log
echo "1">$4/ret
