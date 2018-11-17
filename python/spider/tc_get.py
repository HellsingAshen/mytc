import  urllib
import  urllib2
url = "https://www.baidu.com/s"
data ={
    'wd':'for 宁哥的小站',
}
print (data)
data = urllib.urlencode(data)
full_url = url + '?' + data

print full_url
response  = urllib2.urlopen(full_url)

print response.read();
