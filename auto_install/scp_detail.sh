# show detail
name=""


# run cmd as root transitorily
# we need chmod +s /bin/netstat 

pids=()
ports=()
status="S" # S -- stopped R -- running a -- abnormal
users=()
show_rcds=""

# head flag
head_flag=0;
# local or remote.  local -- 0; remote -- other-values
is_remote_consul=0
is_remote_rabbitmq=0
is_remote_scp_main=0
is_remote_scp_config=0
is_remote_scp_web=0
is_remote_scp_gateway=0
is_remote_tomcat=0

function get_jar_path(){
    echo "1";    
}

function show_head(){
    if [ $head_flag -eq 0 ]; then
        printf "\n           NAME        USER         PID        PORT       SATUS        MORE\n"  ;
        head_flag=1;
    fi
}
# $1 name
function init_status(){
    name="$1"
    users=()
    pids=()
    ports=()
    status="S" # S -- stopped R -- running a -- abnormal
}

function get_consul_status(){
    init_status "CONSUL";
    
    local idx=0;
    show_rcds=""
    if [ $is_remote_consul -eq 0 ];then
        pids=`ps -ef | grep -w $1 | grep -v grep | awk '{print $2}' 2>/dev/null`
        users=`ps -ef | grep $1 | grep -v grep | awk '{print $1}' 2>/dev/null`
        count=`ps -ef | grep -w $1 | grep -v grep | awk '{print $2}' | wc -l `

        [ $count -eq 0 ] && pids="--" && users="--" && ports="--" && status="S" && return 0;
        
        for ((i=0; i<$count; i ++))
        do
            pid=${pids["$i"]}
            user=${users["$i"]}
            ports=$(netstat -nptl | grep "$pid" | grep  ::: | awk '{print $4}' | tr ::: " " | awk '{print $1}')
            show_head;
            for j in ${ports[@]}
            do 
                printf "%15s%12s%12s%12s%12s%12s\n" "$name" "$user" "$pid" "$j" "R" "--"
            done
        done
        

    else
        echo "not support "
        # remote
    fi
}

function get_rabbitmq_status(){
    init_status "RABBITMQ";

    local idx=0;
    show_rcds=""
    if [ $is_remote_rabbitmq -eq 0 ];then
        pids=`ps -ef | grep -w $1 | grep -v grep | awk '{print $2}'`
        users=`ps -ef | grep $1 | grep -v grep | awk '{print $1}'`
        count=`ps -ef | grep -w $1 | grep -v grep | awk '{print $2}' | wc -l `

        [ $count -eq 0 ] && pids="--" && users="--" && ports="--" && status="S" && return 0;

        for ((i=0; i<$count; i ++))
        do
            pid=${pids["$i"]}
            user=${users["$i"]}
            ports=$(netstat -nptl | grep "$pid" | grep  ::: | awk '{print $4}' | tr ::: " " | awk '{print $1}')
            show_head;
            for j in ${ports[@]}
            do
                printf "%15s%12s%12s%12s%12s%12s\n" "$name" "$user" "$pid" "$j" "R" "--"
            done
        done


    else
        echo "not support "
        # remote
    fi

}

function get_tomcat_status(){
    init_status "TOMCAT";

    local idx=0;
    show_rcds=""
    if [ $is_remote_tomcat -eq 0 ];then
        pids=`ps -ef | grep -w $1 | grep -v grep | awk '{print $2}'`
        users=`ps -ef | grep $1 | grep -v grep | awk '{print $1}'`
        count=`ps -ef | grep -w $1 | grep -v grep | awk '{print $2}' | wc -l `

        [ $count -eq 0 ] && pids="--" && users="--" && ports="--" && status="S" && return 0;

        for ((i=0; i<$count; i ++))
        do
            pid=${pids["$i"]}
            user=${users["$i"]}
            ports=$(netstat -nptl | grep "$pid" | grep  ::: | awk '{print $4}' | tr ::: " " | awk '{print $1}' | grep -v ffff)
            show_head;
            for j in ${ports[@]}
            do
                printf "%15s%12s%12s%12s%12s%12s\n" "$name" "$user" "$pid" "$j" "R" "--"
            done
        done


    else
        echo "not support "
        # remote
    fi

}

function get_scp_config_status(){
    init_status "scp-config";

    local idx=0;
    show_rcds=""
    if [ $is_remote_scp_config -eq 0 ];then
        pids=`ps -ef | grep $1 | grep -v grep | awk '{print $2}'`
        users=`ps -ef | grep $1 | grep -v grep | awk '{print $1}'`
        count=`ps -ef | grep $1 | grep -v grep | awk '{print $2}' | wc -l `

        [ $count -eq 0 ] && pids="--" && users="--" && ports="--" && status="S" && return 0;

        for ((i=0; i<$count; i ++))
        do
            pid=${pids["$i"]}
            user=${users["$i"]}
            ports=$(netstat -nptl | grep "$pid" | grep  ::: | awk '{print $4}' | tr ::: " " | awk '{print $1}')
            port_count=$(netstat -nptl | grep "$pid" | grep  ::: | awk '{print $4}' | tr ::: " " | awk '{print $1}' | wc -l)
            show_head;
            if [ $port_count -ne 0 ];then
                for j in ${ports[@]}
                do
                    printf "%15s%12s%12s%12s%12s%12s\n" "$name" "$user" "$pid" "$j" "R" "--"
                done
            else
                printf "%15s%12s%12s%12s%12s%12s\n" "$name" "$user" "$pid" "--" "R" "--"
            fi
        done


    else
        echo "not support "
        # remote
    fi


}
function get_user_arr(){
    str=$1
    local j=0;
    for i in ${str[@]}
    do
        ausers["$j"]="$i";
        j=`expr $j + 1`
    done
}

function get_pid_arr(){
    str=$1
    local j=0;
    for i in ${str[@]}
    do
        apids["$j"]="$i";
        j=`expr $j + 1`
    done
}

function get_scp_main_status(){
    init_status "scp-main";

    local idx=0;
    show_rcds=""
    if [ $is_remote_scp_main -eq 0 ];then
        pids=`ps -ef | grep $1 | grep -v grep | awk '{print $2}'`
        users=`ps -ef | grep $1 | grep -v grep | awk '{print $1}'`
        count=`ps -ef | grep -w $1 | grep -v grep | awk '{print $2}' | wc -l `

        [ $count -eq 0 ] && pids="--" && users="--" && ports="--" && status="S" && return 0;
        apids=()
        get_pid_arr "$pids"
        get_user_arr "$users"

        for ((i=0; i<$count; i ++))
        do
            pid=${apids["$i"]}
            user=${ausers["$i"]}
            port_count=$(netstat -nptl | grep "$pid" | grep  ::: | awk '{print $4}' | tr ::: " " | awk '{print $1}' | wc -l)
            if [ $port_count -ne 0 ]; then
                ports=$(netstat -nptl | grep "$pid" | grep  ::: | awk '{print $4}' | tr ::: " " | awk '{print $1}')
                show_head;
                for j in ${ports[@]}
                do
                    printf "%15s%12s%12s%12s%12s%12s\n" "$name" "$user" "$pid" "$j" "R" "--"
                done
            else
                show_head;
                printf "%15s%12s%12s%12s%12s%12s\n" "$name" "$user" "$pid" "--" "R" "--"
            fi
        done


    else
        echo "not support "
        # remote
    fi

}

function get_scp_gateway_status(){
    init_status "scp-gateway";

    local idx=0;
    show_rcds=""
    if [ $is_remote_scp_gateway -eq 0 ];then
        pids=`ps -ef | grep $1 | grep -v grep | awk '{print $2}'`
        users=`ps -ef | grep $1 | grep -v grep | awk '{print $1}'`
        count=`ps -ef | grep -w $1 | grep -v grep | awk '{print $2}' | wc -l `

        [ $count -eq 0 ] && pids="--" && users="--" && ports="--" && status="S" && return 0;
        apids=()
        get_pid_arr "$pids"
        get_user_arr "$users"

        for ((i=0; i<$count; i ++))
        do
            pid=${apids["$i"]}
            user=${ausers["$i"]}
            port_count=$(netstat -nptl | grep "$pid" | grep  ::: | awk '{print $4}' | tr ::: " " | awk '{print $1}' | wc -l)
            if [ $port_count -ne 0 ]; then
                ports=$(netstat -nptl | grep "$pid" | grep  ::: | awk '{print $4}' | tr ::: " " | awk '{print $1}')
                show_head;
                for j in ${ports[@]}
                do
                    printf "%15s%12s%12s%12s%12s%12s\n" "$name" "$user" "$pid" "$j" "R" "--"
                done
            else
                show_head;
                printf "%15s%12s%12s%12s%12s%12s\n" "$name" "$user" "$pid" "--" "R" "--"
            fi
        done


    else
        echo "not support "
        # remote
    fi
}

function get_scp_web_status(){
    init_status "scp-web";

    local idx=0;
    show_rcds=""
    if [ $is_remote_scp_web -eq 0 ];then
        pids=`ps -ef | grep $1 | grep -v grep | awk '{print $2}'`
        users=`ps -ef | grep $1 | grep -v grep | awk '{print $1}'`
        count=`ps -ef | grep -w $1 | grep -v grep | awk '{print $2}' | wc -l `

        [ $count -eq 0 ] && pids="--" && users="--" && ports="--" && status="S" && return 0;

        for ((i=0; i<$count; i ++))
        do
            pid=${pids["$i"]}
            user=${users["$i"]}
            ports=$(netstat -nptl | grep "$pid" | grep  ::: | awk '{print $4}' | tr ::: " " | awk '{print $1}')
            port_count=$(netstat -nptl | grep "$pid" | grep  ::: | awk '{print $4}' | tr ::: " " | awk '{print $1}' | wc -l)
            show_head;
            if [ $port_count -ne 0 ];then
                for j in ${ports[@]}
                do
                    printf "%15s%12s%12s%12s%12s%12s\n" "$name" "$user" "$pid" "$j" "R" "--"
                done
            else
                printf "%15s%12s%12s%12s%12s%12s\n" "$name" "$user" "$pid" "--" "R" "--"
            fi
        done


    else
        echo "not support "
        # remote
    fi

}

# rcd-count + rcds
function show_status(){
    echo "1"
}

# $1 name
function get_status(){
    case "$1" in
        CONSUL)
            get_consul_status "consul";;
        RABBITMQ)
            get_rabbitmq_status "rabbit";;
        TOMCAT)
            get_tomcat_status "tomcat";;
        SCP_CONFIG)
            get_scp_config_status "scp-config";;
        SCP_MAIN)
            get_scp_main_status "scp-main";;
        SCP_GATEWAY)
            get_scp_gateway_status "scp-gateway";;
        SCP_WEB)
            get_scp_web_status "scp-web";;

    esac
    # show_status();

    
}

function show_scp_detail(){
    get_status "CONSUL"
    get_status "RABBITMQ"
    get_status "TOMCAT"
    get_status "SCP_CONFIG"
    get_status "SCP_MAIN"
    get_status "SCP_GATEWAY"
    get_status "SCP_WEB"
}

show_scp_detail;
