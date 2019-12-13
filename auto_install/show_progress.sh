# $1 percent 
# $2 info 
print_rate()
{
    if [ $1 -gt 100 ]; then
        $1=100;
    fi

    left=`expr 100 - $1`
    printf "\r$2:[%.$1d" | tr '0' '#'
    printf "%.${left}d]" | tr '0' ' '
    printf "$1%%"
}
 
# $1 dir target
# $2 total_size <byte>
# $3 info
# $4 tar.gz
show_rate()
{
    #if [ -z $2 ]; then 
    #    for file_size in $(tar tvvf $3 | awk '{print $3}'); do
    #        total_size=`expr $total_size + $file_size`
    #    done
    #else
    #    total_size=$2
    #fi

    total_size=$2

    while true
    do
        if [ ! -d $1 ]; then
            current_size=0; 
        else 
            # current_size=$(du -bs $1 | awk '{printf $1}')
            current_size=`du -bs $1 2>/dev/null | awk '{printf $1}'`
        fi

        percent=$((${current_size}/(${total_size}/100)))

        print_rate $percent $3
        sleep 1

        if [ $percent -ge 99 ]; then
           print_rate 100 $3
           exit 0; 
        fi
    done
}

show_rate $1 $2 $3
