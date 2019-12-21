# $1 pkg path
# $2 app user
# $3 main port
# $4 gateway port
# $5 shell_path

function run_jar(){
    home_path=`cat /etc/passwd | grep $2 | awk -F: '{print $6}'`;
    if [ ! -d $home_path/jar ]; then
        mkdir -p $home_path/jar;
        if [ ! -d $home_path/jar ]; then
            echo " create dir failed when running jar.please check it .">$1/process.log
            echo "0"/ret
            exit 0;
        fi
    fi
    
    cp $1/jar/*.jar $home_path/jar;

    for i in `ls $home_path/jar/*.jar`
    do
        local base_pro=`basename $i`

        if [ $base_pro = scp-main* ];then
            num=`echo $3 | tr -cd ":" | wc -c`
            for ((j=1; j<=$num; j++))
            do
                name=`echo $3 |awk '{print $"'$j'"}' | awk -F ":" '{print $1}'`
                port=`echo $3 |awk '{print $"'$j'"}' | awk -F ":" '{print $2}'`
                su - $2 -c "nohup java -jar $i --node.name=$name --server.port=$port > /dev/null 2>&1 &"
                echo "JAVA_$i_START_PARA:" "java -jar $i --node.name=$name --server.port=$port" >>boot_info
            done
        elif  [ $base_pro = scp-gateway* ];then
            num=`echo $4 | tr -cd ":" | wc -c`
            for ((j=1; j<=$num; j++))
            do
                name=`echo $4 |awk '{print $"'$j'"}' | awk -F ":" '{print $1}'`
                port=`echo $4 |awk '{print $"'$j'"}' | awk -F ":" '{print $2}'`
                su - $2 -c "nohup java -jar $i --node.name=$name --server.port=$port > /dev/null 2>&1 &"
                echo "JAVA_$i_START_PARA:" "java -jar $i --node.name=$name --server.port=$port">>boot_info
            done
        else
            su - $2 -c "nohup java -jar $i >/dev/null 2>&1 &"
            echo "JAVA_$i_START_PARA:" "java -jar $i" >>boot_info
        fi

    done
}

run_jar $1 $2
