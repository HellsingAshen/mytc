# $1 install path
# $2 shell path
# $3 db2 version
if [ $3 -eq 11 ]; then
    expect $2/exp/install_db2s.exp "$1/server_t/db2_install" "yes" "yes" "SERVER" "no"
else
    expect $2/exp/install_db2s_v10.exp "$1/server_t/db2_install" "yes" "SERVER" "no"
fi
