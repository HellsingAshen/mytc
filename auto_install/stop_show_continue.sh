kill_pid=`ps -ef | grep show_continue.sh | grep -v grep | awk '{print $2}' | xargs kill -9`
for i in $kill_pid
do
    echo " kill process " $i
    kill -9 $i >/dev/null 2>&1
done
