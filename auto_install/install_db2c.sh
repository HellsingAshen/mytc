# $1 install_path
# $2 shell path
# $3 db2 version
if [ $3 -eq 11 ]; then 
    expect $2/exp/install_db2c.exp "$1/server_t/db2_install" "yes" "yes" "CLIENT"
else
    expect $2/exp/install_db2c_v10.exp "$1/server_t/db2_install" "yes" "CLIENT"
fi
