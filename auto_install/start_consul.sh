# $1 app_user
# $2 cmd
function runcmd(){
    if [ ! -z "$2" ]; then
        su - $1 -c "nohup $2>/dev/null 2>&1 &">/dev/null
    fi
}

runcmd $1 "$2";
runcmd $1 "$3";
runcmd $1 "$4";
runcmd $1 "$5";
runcmd $1 "$6";
runcmd $1 "$7";
runcmd $1 "$8";
