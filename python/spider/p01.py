import urllib2

url = "https://news.163.com"
content = urllib2.urlopen(url);
resp = urllib2.urlopen(url).read();

print resp.decode("gbk") 
