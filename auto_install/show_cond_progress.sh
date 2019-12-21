# $1 cond str
# show progress while running 
# $1 info string
# $2 cond cmd str
show_cond_continue()
{
    local cur=1;
    local count=0;
    left=`expr 100 - $cur`
    while true
    do
        printf "\r[$1 %.${cur}d" | tr '0' '.'
        printf "%.${left}d]" | tr '0' ' '
        sleep 1;
        count=`eval $2`
        if [ $count -ne 0 ] ;then
            echo "" > /dev/null 2>&1
            return 0;
        fi
        cur=`expr $cur + 1`
        if [ $cur -gt 99 ];then
            cur=0
        fi 
        left=`expr 100 - $cur`
    done
}

show_cond_continue "$1" "$2"
