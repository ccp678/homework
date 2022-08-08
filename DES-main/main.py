import matplotlib.pyplot as plt # plt 用于显示图片
import matplotlib.image as mpimg # mpimg 用于读取图片
import numpy as np
from DES import text_en_de
from DES import image_en_de

def get_imag(name):
    lena = mpimg.imread(name) # 读取和代码处于同一目录下的 lena.png
    # 此时 lena 就已经是一个 np.array 了，可以对它进行任意处理
    print('图片信息：',lena.shape) #(512, 512, 3)

    #plt.imshow(lena) # 显示图片
    #plt.axis('off') # 不显示坐标轴
    #plt.show()



    with open('des.txt','w',encoding='utf-8') as f:
        
        for i in lena:
            for j in i:
                
                s = '['+str(j[0])+','+str(j[1])+','+str(j[2])+']'
                f.write(s+'\n')
                

    f.close()
    return lena

def arrayToImg(lena):
    l =  lena.shape
    s = []
    s2 =  []
    print(l[0],l[1])
    with open('des.txt','r') as f2:
        for i in range(l[0]):
            s = []
            for j in range(l[1]):
                r = f2.readline().replace('\n','')
                r2 = r
                #s2+=r.shape
                r = eval(r)
                #print(r)
                s.append(r)
            s2.append(s)
    #s = eval(s)           
    #print(type(s2))
    #print(r2+'\n')
    #print('r')
    n = np.array(s2,dtype='uint8')
    import matplotlib
    
    matplotlib.image.imsave('out.png', n)
    #lena2 = mpimg.imread('out.png') # 读取和代码处于同一目录下的 lena.png
    # 此时 lena 就已经是一个 np.array 了，可以对它进行任意处理
    #print(lena.shape) #(512, 512, 3)

    plt.imshow(lena) # 显示图片

if  __name__ == '__main__':
    while True:
        print("请输入加密的类型（0：图片，1:文本和字符串）2：退出")
        print("注意：图片加密的时间需要的会久一些")
        get = input()
        if get == '0':
            print("图片名称：")
            name = input()
            print('密钥:')
            key = input()
            lena = get_imag(name)
            #加密和解密
            image_en_de(key)
            arrayToImg(lena)
        elif get == '1':
            print("注意：此时的输入的文本应该填入在des.txt中")
            print('密钥:')
            key = input()
            text_en_de(key)
        else:
            print('error')
            break
