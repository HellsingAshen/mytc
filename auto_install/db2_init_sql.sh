# $1 db2instance 
# $2 db2user
# $3 db2pwd 
# $4 shell_path

db2 connect to $1 user $2 using $3 > /dev/null 2>&1
db2 -tf  $4/init_sql/scp.sql > /dev/null 2>&1
db2 -tf  $4/init_sql/db2_sequence.sql > /dev/null 2>&1

# check it
