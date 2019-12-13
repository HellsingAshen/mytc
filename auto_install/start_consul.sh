# $1 -- app_user
# $2 -- process
su - $1 -c "nohup $2>/dev/null 2>&1 &">/dev/null
