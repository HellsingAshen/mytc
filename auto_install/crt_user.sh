# user   -- $1
# passwd -- $2
# pkg_path -- $3
function check_user_exist(){
    if id $1 &> /dev/null; then
        echo "user has been exist.">$3/process.log
    else
        useradd $1
        echo $2 | passwd $1 --stdin  &>/dev/null
        if [ $? -eq 0 ]; then
            echo "add user $username suc.">$3/process.log
        else
            echo "can not add $username."
            echo "[`date "+%Y-%m-%d %H:%M:%S"`]create user $1 failed.">>$3/process.log;
            echo "0">$3/ret;
            exit 0;
        fi
    fi

    echo "[`date "+%Y-%m-%d %H:%M:%S"`]check_user_exist suc.">>$3/process.log
    echo "1">$3/ret
}
check_user_exist $1 $2 $3;
