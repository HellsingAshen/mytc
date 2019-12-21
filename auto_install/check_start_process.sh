# $1 -- appuser 
# $2 -- keywords 1
# $3 -- keywords 2
# $4 -- keywords 3
# $5 -- log path
count=`ps -ef | grep -v grep | grep $1 | grep $2 | grep $3 | grep $4 |grep -v pts| wc -l`
if [ $count -eq 0 ]; then
    echo "no process $2 found">>$5/process.log
    echo "0">$5/ret
else
    echo "process $2 found">>$5/process.log;
    echo "1">$5/ret;
fi
