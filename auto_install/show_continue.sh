# show progress while running 
# $1 info string
show_continue()
{
    local cur=1;
    left=`expr 100 - $cur`
    while true
    do
        printf "\r[$1 %.${cur}d" | tr '0' '#'
        printf "%.${left}d]" | tr '0' ' '
        #printf "%.${left}d" | tr '0' ' '
        sleep 1;
        cur=`expr $cur + 1`
        if [ $cur -gt 99 ];then
            cur=0
        fi 
        left=`expr 100 - $cur`
    done
}

show_continue "$1"
