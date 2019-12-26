# $1 -- jar path
# $2 -- app_user
# $3 -- log path

source $(dirname $0)/common.sh
function run_java_exe(){

    local log_path=$3
    local log_file=$3/process.log
    local log_boot=$3/boot_info
    local log_ret=$3/ret
    
    local i=0;
    local choice=();
    declare -A map_pkg=()
    local gateway_name_port=""
    local main_name_port=""

    if [ ! -d $1 ]; then
        loge "no jar directory found."  $log_file
        logc "0"                        $log_ret
        exit 0;
    fi

    # check java is installed
    ret=`su - $2 -c "java -version 2>&1 |grep \"java version\" |wc -l"`
    if [ $ret -eq 0 ]; then
        loge "no jdk found, please install jdk first."  $log_file
        exit 0;
    fi

    local home_path=`cat /etc/passwd | grep $2 | awk -F: '{print $6}'`;

    cp -r $1 $home_path/;
    local log_app=$home_path/install_log
    if [ ! -d $log_app ]; then
        su - $2 -c "mkdir -p $log_app"
    fi
    chmod -R 777 $home_path/jar

    for ch in `ls $home_path/jar`
    do
        i=`expr $i + 1`;
        echo "$i) " $ch;
        map_pkg["$i"]=$ch;
    done

    while true;
    do
        read -p "input your choice: " -a choice;
        if [ ${#choice[@]} -ne 0 ]; then
            break;
        fi
    done

    for i in ${choice[@]}
    do
        name=${map_pkg["$i"]}
        if [[ "$name" == scp-main* ]];then
            if [ -z $main_name_port ]; then
                read -p "
            input name and port of scp-main application which format is {<NAME:PORT>}
                example: name1:8000 name2:8001
            input your name:port " -a main_name_port;
            fi

            num=`echo $main_name_port | tr -cd ":" | wc -c`
            if [ $num -eq 0 ];then
                su - $2 -c "nohup java -jar  $home_path/jar/${map_pkg["$i"]}/*.jar >> $log_app/process.log 2>&1 &"
                echo "JAVA_$i_START_PARA:" "java -jar ${map_pkg["$i"]}" >> $log_boot
            else
                for ((j=1; j<=$num; j++))
                do
                    name=`echo $main_name_port | awk '{print $"'$j'"}' | awk -F ":" '{print $1}'`
                    port=`echo $main_name_port | awk '{print $"'$j'"}' | awk -F ":" '{print $2}'`
                    su - $2 -c "nohup java -jar  $home_path/jar/${map_pkg["$i"]}/*.jar --node.name=$name --server.port=$port >> $log_app/process.log 2>&1 &"
                    echo "JAVA_$i_START_PARA:" "java -jar  $home_path/jar/${map_pkg["$i"]} --node.name=$name --server.port=$port" >> $log_boot
                done
            fi
	elif [[ "$name" == scp-gat* ]]; then
            if [ -z $gateway_name_port ]; then
                read -p "
            input name and port of scp-gateway application which format is {<NAME:PORT>}
                example: name1:8000 name2:8001
            input your name:port " -a  gateway_name_port;

            fi

            num=`echo $gateway_name_port | tr -cd ":" | wc -c`
            if [ $num -eq 0 ];then
                su - $2 -c "nohup java -jar  $home_path/jar/${map_pkg["$i"]}/*.jar >> $log_app/process.log 2>&1 &"
                echo "JAVA_$i_START_PARA:" "java -jar  $home_path/jar/${map_pkg["$i"]}" >> $log_boot
            else
                for ((j=1; j<=$num; j++))
                do
                    name=`echo $gateway_name_port |awk '{print $"'$j'"}' | awk -F ":" '{print $1}'`
                    port=`echo $gateway_name_port |awk '{print $"'$j'"}' | awk -F ":" '{print $2}'`
                    su - $2 -c "nohup java -jar  $home_path/jar/${map_pkg["$i"]}/*.jar --node.name=$name --server.port=$port >> $log_app/process.log 2>&1 &"
                    echo "JAVA_$i_START_PARA:" "java -jar  $home_path/jar/${map_pkg["$i"]} --node.name=$name --server.port=$port" >> $log_boot
                done
            fi
        else
	    su - $2 -c "nohup java -jar  $home_path/jar/${map_pkg["$i"]}/*.jar >>$log_app/process.log 2>&1 &"
	    echo "JAVA_$i_START_PARA:" "java -jar  $home_path/jar/${map_pkg["$i"]}" >> $log_boot
        fi
    done
}

run_java_exe $1 $2 $3
