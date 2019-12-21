mkdir -p ~/dbdata/scp
mkdir -p ~/dbdata/db2/scp
mkdir -p ~/tablespace/

db2 "create db scp on /home/scp/dbdata/scp dbpath on /home/scp/dbdata/db2/scp using codeset UTF-8 territory CN"
db2 "connect to scp"
db2 "create schema scp"
db2 "grant dbadm on database to user scp"
db2 "create bufferpool buffer1 immediate size 250 pagesize 32768"
db2 "create regular tablespace tablespace1 pagesize 32k managed by DATABASE using (file '/home/scp/tablespace/tablespace1.dbf' 1g) bufferpool buffer1"
db2 "grant use of tablespace tablespace1 to user scp"

