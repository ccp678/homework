
from collections import defaultdict
import pandas as pd

def main(s):


    with open('yuan.txt') as f:
        g = f.readlines()
    f.close()   

    #将输入的语法字符串进行分割

    VT = ['i','(',')','@','+','-','/','#','*']
    VN = ['E','T','G','F','S']


    ###解析需要用到的栈
    class Stack(object):
        def __init__(self):
            self.__list = []
        #判断空
        def is_empty(self):
            return self.__list == []
        #入栈
        def push(self,item):    
            self.__list.append(item)
        #出栈
        def pop(self):
            return self.__list.pop()
        #取栈顶元素
        def top(self):
            return self.__list[-1]
        def show(self):
            return ''.join(self.__list)
            #print('栈',self.__list)


    def splitG(gramma):
        stack = []
        #清除最后的\n
        for i in range(len(gramma)-1):
            gramma[i] = gramma[i][0:-1]
        v = []
        
        for i in gramma:
            v1 = i.split("->")
            v2 = v1[1].split('|')
            for j in v2:
                l = []
                for k in j:
                    l.append(k)
                v.append([v1[0]]+l)
        return v

        
    #将式子解析出来
    productions = splitG(g)
    #构造First表
    
    First = defaultdict(set)
    Follow = defaultdict(set)

    #得到first集
    def getFirst(v):
        if First[v] != set():
            return First[v]
        
        for curPro in productions:
            if curPro[0] == v:
                #判断右边首个字母是不是终结符
                if curPro[1] in VT:
                    First[v].add(curPro[1])
                else:
                    #判断推导式右边的第一个字母是不是已经生成过FIRST集
                    if(First[curPro[1]] == set()):
                        First[v] = set(getFirst(curPro[1]))
                    else:
                        First[v] = set(First[curPro[1]])
        return First[v]
    #得到FELLOW集

    
    first = defaultdict(set)
    follow = defaultdict(set)
    vt = VT
    vn = VN
    def getFollow(curVn):
            # 同上
        if curVn != 'E' and follow[curVn] != set():
            return follow[curVn]
        # print(curVn)
        # 这两层循环是为了在产生式右侧找到正在求的非终结符
        for curPro in productions:
            l = len(curPro)
            for i in range(1,l):
                if curPro[i] != curVn:  #找求的字符
                    continue
                # print(curPro)
                # 如果当前非终结符是列表最后一个元素那么他的下一个元素一定是结束符#
                if i == l-1:
                    # print(2)
                    follow[curVn] = set(getFollow(curPro[0]))
                    follow[curVn].add('#')
                    continue
                # 判断后面的是终结符还是非终结符
                if curPro[i+1] in vt:   #终结符添加
                    follow[curVn].add(curPro[i+1])
                elif curPro[i+1] in vn:
                    #如果右边的字符的First集有空串的情况下,将
                    if '@' in first[curPro[i+1]]:
                        # print(4)
                        follow[curVn] = follow[curVn] | first[curPro[i+1]]
                        follow[curVn] = follow[curVn] | set(getFollow(curPro[0]))
                        follow[curVn].discard('@')      #按照原来的步骤求出的同时，也将空串去掉
                    else:
                        # print(5)
                        follow[curVn] = follow[curVn] | first[curPro[i+1]]   #求出右边字母的FIRST
        return follow[curVn]

    for curVn in VN:
        getFirst(curVn)
    first = First
    follow[VN[0]].add('#')

    for i in VN:
        getFollow(i)
    Follow = follow




    ####开始创建select表

    ##首先得到一个式子生成的First集

    def getLastFirst(cur):
        f = []
        l = len(cur)
        for i in range(1,l):
            if(cur[i] in VT):
                f.append(cur[i])
                break
            elif cur[i] in VN:
                if '@' in First[cur[i]]:   #有空串,继续往下遍历
                    f.extend(First[cur[i]])
                else:
                    f.extend(First[cur[i]])
                    break
        ff = []
        for i in f:
            if i not in ff:
                ff.append(i)
        return ff




    ##生成select表
    #生成一个二维列表来存放数据，存放的数据也是一个列表
    Data = [[[] for i in range(len(VT))] for i in range(len(VN))]

    M = pd.DataFrame(data = Data,index = VN,columns = VT)

    def getSelect():
        for i in productions:
            row = i[0]
            #对每一个式子求出对应的非终结符
            columns = getLastFirst(i)
            for j in columns:
                if j == '@':       #判断有空串的情况
                    continue
                M.loc[row][j].append(i)
        for i in productions:
            row = i[0]
            columns = getLastFirst(i)

            if '@' in columns:
                for j in Follow[row]:
                    M.loc[row][j].append(i)

    getSelect()

    ###进行分析
    def getResult(sentence):
        ##删除语句中的‘ ’
        sentence.replace(' ','')
        v = list(sentence)   #需要判断的字符串
        l = len(v)
        i = 0;

        S = Stack();
        S.push('#')
        S.push('E')
        x = S.top()

        cin =  ''  #表示输入
        cout = ''  #表示输出

        #result = S.show()+'\t'+sentence+'\t'+'初始化\n'
       # result = '{:>30}\t{:>30}\t{:>20}\t\n'.format('栈','输入','输出')
        result = '{:>30}\t{:>30}\t{:>20}\t\n'.format(S.show(),sentence,'初始化')
        v2 = v
        while x != '#':
            cin = ''.join(v2)
            a  = v[i]
            if x == a:   #栈顶元素和字符串首字母匹配
                S.pop()  
                v2 = v[i:-1]  #求匹配过后的输入字符串
                i = i + 1
            elif x in VT:
                raise Exception('ERROR：栈顶元素是非终结符')
            elif M[a][x] is []: #对应的分析表没有选项
                raise Exception('没有找到对应的生成式')
            elif M[a][x][0] in productions:     #查表找到对应的生成式
                prod = M[a][x][0]
                #记录输出
                cout = prod
                S.pop()
                l2 = len(prod)
                for j in range(l2 - 1):
                    if prod[l2 -j -1] != '@':  #不是空串才反过来把生成式放入栈中
                        S.push(prod[l2-j-1])
            x = S.top()
            cout2 = [_ for _ in cout]
            cout2.insert(1,'->')
            result = result + '{:>30}\t{:>30}\t{:>30}\t\n'.format(S.show(),str(cin),str(cout2))
            #print(result)
        return result
    pd.set_option('display.max_rows', None)  # 可以填数字，填None表示'行'无限制
    pd.set_option('display.max_columns', None)

    sentence = s
    return getResult(sentence),M



from tkinter import *
from tkinter import messagebox



###输出GUI
from tkinter import *
def on_click():
    en = entry.get()
    result,fir = main(en)
    t.insert(END,result+'\n\n')
    t.insert(END,fir)
    #t.insert(END,fol)

root = Tk(className='LL(1)')
root.geometry('1000x800')
label1 = Label(root,justify = LEFT)
label1['text'] = '输入式子'
label1.pack()

text = StringVar()

entry = Entry(root)
entry['textvariable'] = text
entry.pack()

button = Button(root)
button['text'] = '生成'
button['command'] = on_click
button.pack()
t = Text(root,width = 600,height = 800)
t.pack(side = RIGHT)

root.mainloop()
