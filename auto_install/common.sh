comvar_install_pkg_name=""
# $1 -- find str
function choose_pkg(){
    local i=0;
    local choice=0;
    declare -A map_pkg=()
    for ch in `$1`
    do
            i=`expr $i + 1`;
            echo "$i) " $ch;

            map_pkg["$i"]=$ch;
    done

    while true;
    do
            read -p "input your choice: " choice;
echo "get choice " $choice
            if [ $choice -gt 0 ] && [ $choice -lt `expr $i + 1` ]; then
                echo "INSTALL IS " ${map_pkg["$choice"]};
                comvar_install_pkg_name=${map_pkg["$choice"]};
                return;
            else
                echo "invalid node_number number, please input a node_number ranges from [1 - $i]";
            fi
    done

}

# $1 -- find str
function get_install_package_name(){
    local find_str=$1;

    # for unixODBC
    local pkg_count=`$1 | wc -l`;

    if [ 0 -eq $pkg_count ]; then
        echo "no package found. find str is [$1], please check it."
        exit 0;
    elif  [ 1 -eq $pkg_count ]; then
        comvar_install_pkg_name=`$find_str`;
    else
        choose_pkg "$find_str";
        #comvar_install_pkg_name=$comvar_install_pkg_name;
    fi
}

cmd_uncompress=""
cmd_uncompress_dir=""
# $1 basename
function get_uncompress_cmd()
{
    local filename=$1
    local suffix=${filename#*.}
    local support=('tar','tar.gz','tar.bz2','zip');
    while true;
    do
        case $suffix in
            'tar')
                cmd_uncompress="tar -xvf ";
                cmd_uncompress_dir="-C ";
                break;;
            'tar.gz')
                cmd_uncompress="tar -zxvf ";
                cmd_uncompress_dir="-C ";
                break;;
            'tar.bz2')
                cmd_uncompress="tar -zxvf ";
                cmd_uncompress_dir="-C ";
                break;;
            'zip')
                cmd_uncompress="unzip ";
                cmd_uncompress_dir="-d ";
                break;;
            '')
                echo "not support type";
                break;;
            *)
                suffix=${suffix#*.};
                continue;;
        esac
    done
}
