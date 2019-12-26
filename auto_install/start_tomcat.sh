# $1 app_user
# $2 log path
# $3 startup.sh full path
su - $1 -c "nohup sh $3 > /dev/null 2>&1 &"
