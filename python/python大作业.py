import re
import time
import requests
from urllib import error
from bs4 import BeautifulSoup
import os


numPicture = 0 #存储需要图片的数量
fileName = ''  #得到创建文件的名字
l = []         #存放图片的url
num = 0        #表示正在下载图片的张数

#找出图片的网址信息
def Search(url,r):
    global l
    print("正在搜索图片，请稍等")
    t = 0
    i = 1
    s = 0
    while t < 1000:
        Url = url + str(t)
        try:
            Result = r.get(Url,timeout = 7, allow_redirects = False)
        except BaseException:
            t +=  60
            continue
        else:
            result = Result.text
        pictureUrl = re.findall('"objURL":"(.*?)",', result, re.S)   #利用正则表达式找到图片的url
        le = len(pictureUrl) 
        s += le
        if le == 0:
            break
        else :
            l.append(pictureUrl)
            t+=60
    return s    

def recommend(url):
    R = []
    Url = url + str(0)
    try:
        Result = r.get(Url,timeout = 7, allow_redirects = False)
    except BaseException:
        return 
    else:
        result = Result.text
        soup =BeautifulSoup(result,'html.parser')
        a = soup.find(id = 'topRS')
        la = a.find_all('a')
        for i in la:
            if i is not None:
                R.append(i.get_text())
    return R
    
def download(html,keyword):
    global num
    pictureUrl = re.findall('"objURL":"(.*?)",', html, re.S)  #先用正则表达式找到图片的url
    print("找到关键词："+keyword+'的图片，即将开始下载...')
    for i in pictureUrl:
        print("正在下载第"+str(num+1)+'张图片')
        try:
            if i is not None:
                pic = requests.get(i,timeout = 7)
            else:
                continue
        except BaseException:
            print("出现错误，当前图片无法下载")
            continue
        else :
            Str = fileName + r'\\'+keyword + '_' + str(num) + '.jpg'
            fp = open(Str,'wb')
            fp.write(pic.content)   #
            fp.close()
            num += 1
        if num >= numPicture:
            return

#主函数
if __name__ == '__main__':
    headers = {
        'Accept-Language': 'zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2',
        'Connection': 'keep-alive',
        'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/60.0',
        'Upgrade-Insecure-Requests': '1'
    }
    r = requests.Session()
    r.headers = headers

    name = input("请输入关键词")

    url = 'https://image.baidu.com/search/flip?tn=baiduimage&ie=utf-8&word=' + name + '&pn='
    a=url
    Sum = Search(url,r)
    print('检测出{}类图片，有{}张'.format(name,Sum))
    numPicture = int(input("请输入想要下载的数量"))
    fileName = input("请输入将要建立的专门存储图片的文件夹名称")
    x = os.path.exists(fileName)
    if x==1:
        print("该文件已经存在，请重新输入")
        file = input("请输入将要建立的专门存储图片的文件夹名称")
        os.mkdir(fileName)
    else:
        os.mkdir(fileName)
    t = 0
    tmp = url
    while t < numPicture:
        try:
            url = tmp + str(t)
            result = r.get(url,timeout = 10,allow_redirects = False)
        except error.HTTPError :
            print("网络错误，稍后重试")
            t += 60
        else:
            download(result.text,name)
            t+=60
    print("下载结束，感谢使用")
    R = recommend(a)  #记录推荐
    print("你可能喜欢")
    for i in R:
        print(i,end = ' ')
