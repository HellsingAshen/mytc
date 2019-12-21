# $1 db2instance 
# $2 db2user
# $3 db2pwd 
# $4 db sql path

mkdir -p ~/install_log
db2 connect to $1 user $2 using $3 > /dev/null 2>&1
for i in `ls $4/*.sql| sort`
do
    db2 -tf  $i >> ~/install_log/initdb.log
done 
