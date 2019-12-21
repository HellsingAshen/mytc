# $1 -- app_user
# $3 -- cmd 1
# $4 -- cmd 2
# $5 -- cmd 3
# $6 -- cmd 4
# $7 -- cmd 5
# $8 -- cmd 6

# $1 app_user
# $2 cmd
function runcmd(){
    if [ ! -z "$2" ]; then
        su - $1 -c "nohup $2 >/dev/null 2>&1 &"
    fi
}

runcmd $1 "$2";
runcmd $1 "$3";
runcmd $1 "$4";
runcmd $1 "$5";
runcmd $1 "$6";
runcmd $1 "$7";
runcmd $1 "$8";
runcmd $1 "$9";
