
#from experiment002 import Stack,splitG
from collections import defaultdict
import pandas as pd
import functools 
def error():
    print('出错')

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

fileName = 'text.txt'

with open(fileName) as file:
    g = file.readlines()
file.close()
VT = ['i','(',')','@','+','-','/','#','*']
VN = ['E','T','F']

begin = 'E' #表示开始符号

productions = splitG(g)

First = defaultdict(set)

def getFirst(v):
        if First[v] != set():
            return First[v]
        
        for curPro in productions:
            if curPro[0] == v:
                #判断右边首个字母是不是终结符
                if curPro[1] in VT:
                    First[v].add(curPro[1])
                else:   #非终结符
                    #判断推导式右边的第一个字母First是不是已经出现
                    if curPro[1] == curPro[0]:  #直接左递归的情况
                        continue
                    if(First[curPro[1]] == set()):
                        First[v] = set(getFirst(curPro[1]))
                    else:
                        First[v] = set(First[curPro[1]])
        return First[v]

#得到一条语句的First集
def getLastFirst(cur):
        f = []
        l = len(cur)
        
        if cur[0] in VN:
            f.append(list(First[cur[0]]))
        elif cur[0] in VT:
            f.append(cur[0])
        ff = []
        for i in f:
            if i not in ff:
                ff.append(i)
        return f

for curVn in VN:
        getFirst(curVn)
#print(list(First['E']))


###开始构建DFA表
#用列表作为队列,构建每一个状态


#判断两个list是否有重合
def judgeAandB(v1,v2):
    if(len(v1) > len(v2)):
        v = v1
        v1 = v2
        v2 = v
    l = len(v1)
    for i in range(l):
        if v1[i] != v2[i]:
            return False;
    return True

#判断语句是否在闭包中，返回位置
#判断的是生成式是不是在闭包中
def judgeAinB(v1,v2):
    num = -1
    #print(v1,v2)
    for i in v2:
        num += 1
        d = [False for c in v1 if c not in i]
        if not d :           #表示是子集关系
            v1_l = len(v1)
            for j in range(v1_l):    #判断顺序
                
                if v1[j] != i[j]:
                    #print( False,-1)
                    return False,-1
                #print(v1[j],i[j])
            return True,num     #返回位置
    return False,-1
        
#求两个list的并集,对于二维及以上不适用
def getSet(v1,v2):
    s1 = set(v1)
    s2 = set(v2)
    return list(s1 | s2)

pro = productions   #用来记录加过点之后的式子


for i in pro:
    l = len(i)
    i.insert(1,'.')
#print(pro)

 
##求闭包  参数是每个状态的第一条语句
#没一条语句的样子是[语句字符，[展望]]
def getCLOSURE(b):
    v = []
    v.append(b)
    l = len(b)
    last = len(v)
    
    v1 = [_ for _ in v]
    v2 = [_ for _ in v]
    for i in v:   #遍历每一个元素
        i_l = len(i)
        for j in range(i_l):  #找到每一条语句点的位置
            if i[j] == '.': #找到点的位置
                if i[j+1] in VN:        #表示有产生式
                    c = i[j+1]
                    ##产生下一个产生式
                    for cur in pro:
                        if cur[0] == c:     #表示找到产生式
                            ##计算First集
                            #print(i)
                            fir = getLastFirst(i[j+2:-1]+i[-1])  #fir为一个list
                            #print(cur,i[j+2:-1]+i[-1],fir)
                            newchars = [k for k in cur]
                            a,b = judgeAinB(newchars,v)   #判断是否已经在闭包内
                            #print(cur,i[j+2:-1]+i[-1],fir)
                            fir = getSet(fir,i[-1])
                            if(a):     #已经有语句了
                                #print('hhhhhhhhhhhhhhhhhhhhh')
                                v_last = v[b][-1]
                                fir = getSet(fir,v_last)
                                newchars.append(fir)
                                v.pop(b)
                                v.append(newchars)
                            else:
                                #print(newchars)
                                newchars.append(fir)
                                v.append(newchars)
                    break
                elif i[j+1] in VT:        #表示是终结符,洗衣歌字符没有产生式
                    break
                elif j == i_l-2:          #点的位置在生成式最后
                    break
                else:
                    error()
                break
    
    #v.clear()
    #v = [_ for _ in v1]
        #print(v)
        
    

    return v


#print(pro)
#print(judgeAinB(['E', '.', 'E', '+', 'T'],[['S', '.', 'E', ['#']],[],['E', '.', 'E', '+', 'T',['#']]]))
##移动并消除点
def deletePoin(V):
    v = [_ for _ in V]
    v_l = len(v)
    pos = 0
    for i in range(v_l):
        if v[i] == '.':
            pos = i
    if pos == v_l -2:
        return v,pos
    v.insert(pos+2,'.')
    v.pop(pos)
    return v,pos+1   #也要但会点的位置

#判断生成式是否在闭包内，包括展望
def judgeAandB_B(A,B):
    v1 = [_ for _ in A]
    v2 = [_ for _ in B]
    c1 = str(v1[0:-1])
    for i in v2:
        #d = [False for c in v1[-1] if c not in ]
        c2 = str(i[0:-1])
        if c1 == c2:    #生成式在
            if len(v1[-1]) == len(i[-1]):
                d = [False for c in v1[-1] if c not in i[-1]]
                if not d:
                    return True
    return False   


###闭包程序成功
#开始求DFA

class obj():
    def __init__(self):
        super().__init__()
        self.num = 0       #表示几号  
        self.queue = []   #表示内部的表达式
        self.superNum = 0 #表示上一状态标号
        self.super = []     #用来记录上一状态标号
        self.type = 'S'
    def __iter__(self):
        return self
    def __list__():
        return [self.num,self.type,self.queue,self.super]
    def __next__(self):   #变成可迭代对象
        return self.num,self.type,self.queue,self.super
    def __show__():
        print('状态号:',self.num)
        print('这个闭包的状态',type)
        print('闭包内容',self.queue)
        print('指向这个闭包的点',self.super)

#求闭包是否在项目中
def judgeAinB_DFA(A,B):
    B_l = len(B)
    num = 0
    for i in B:
        if functools.reduce(lambda x, y : x and y, map(lambda p, q: p == q,i.queue,A), True):   #缺陷：严格要求位置，可能对展望的判断有错误
            return True,num
        num+=1
    return False,-1      

#存储DFA的信息
def judgeCinCh(c,ch):
    i_l = len(ch)
    for i in range(i_l):
        if c[0] == ch[i][0]:
            return True,ch[i][1]
    return False,-1
#求二维数组的并集
def getSet2(A,B):
    #return list(set(A).union(set(B)))
   # for i in B:
    #    if i in A:
    tmp = [j for j in A if j in B]
    tmp += [j for j in A if j not in tmp]
    tmp += [j for j in B if j not in tmp]  
    return tmp
    #union = set(tuple(t) for t in A+B)
    #union = list(list(t) for t in union)

DFA = []

beginS = ['S','.','E',['#']]
#print(beginS[2:-1]+beginS[-1])

#print(getCLOSURE(beginS))
def getDFA():
    #getCLOSURE()
    #设置开始节点
    
    b = getCLOSURE(beginS)  #求出状态0
    
    beg = obj()
    beg.queue = [_ for _ in b]
    beg.super.append([-1,'#']) #默认
    beg.num = 0       #标号为状态0
    #print('yyyyyyyyyyyyyy')
    DFA.append(beg)
    #按照队列的思想生成其他的状态
    Snum = 0   #状态数
    
    ch = []   #表示下一个语句的首字符
    v_g = []   #表示每一个状态能产生的其他状态
    #print('jjjjjjjjjj')
    for i in DFA:
        #if len(DFA)>22:
           # break
       # print('hhhhhhhhh')
        v = i.queue   #v = [['S', '.', 'E', ['#']], ['E', '.', 'E', '+', 'T', ['#', '+']], ['E', '.', 'T', ['#', '+']], ['T', '.', 'T', '*', 'F', ['#', '+', '*']], ['T', '.', 'F', ['#', '+', '*']], ['F', '.', '(', 'E', ')', ['#', '+', '*']], ['F', '.', 'i', ['#', '+', '*']]]
        v_l = len(v)
        
        for j in range(v_l):  #遍历状态内的语句
            
            j_l = len(v[j])  #生成式的大小
            v_j = [_ for _ in v[j]]  #当前生成式
            for k in range(j_l):   
                #print(v_j[k])
                if v_j[k] == '.':
                    if k == j_l -2:
                        break
                    c = v_j[k+1]   #记录下一个要生成的语句的产生式左部,也是生成下一状态的字符
                    
                    #####开始生成下一个状态
                    new_chars,p = deletePoin(v_j) #得到下一个状态的生成式
                    new_c =  getCLOSURE(new_chars)  
                    new_obj = obj()
                    #对每一个闭包的属性赋值
                    new_obj.queue = new_c   #待改
                    
                    if p == len(new_chars) - 2:   #点已经在最后一个位置,规约
                        new_obj.type = 'R'
                    else:
                        new_obj.type = 'S'
                    
                    Snum += 1    #状态数
                    new_obj.num = Snum

                    C = [c,new_obj.num] 
                    #print(C,ch)
                    
                    d,b = judgeCinCh(C,ch)
                        #print(a,b,len(DFA))

                    if d:
                        Snum -= 1
                        DFA[b].queue = getSet2(DFA[b].queue,new_c)
                        print(DFA[b].num)
                    else:
                        
                
                        a,b = judgeAinB_DFA(new_c,DFA)
                        if a:      #判断是不是在DFA闭包中,在
                            Snum -= 1
                            new_obj.num = DFA[b].num
                            ch.append([c,new_obj.num]) 
                            new_obj.super = DFA[b].super
                            DFA[b].super.append([i.num,c])
                            print(DFA[b].num)
                            #DFA[b].super.append([DFA[b].num,c])
                            
                        else:
                            
                            #print(a,b,len(DFA))
                            ch.append([c,new_obj.num]) 
                                #if new_obj.type == 'S':
                            new_obj.super.append([i.num,c]) 
                            DFA.append(new_obj)
                         
                   
                    
                    break
        ch.clear()
       
    return DFA

dfa = getDFA()

#print(getCLOSURE(['E','E','*','F','.',['#']]))



##构造ACTION和GOTO表
def getM(p):
    with open(fileName) as file:
        g = file.readlines()
    file.close()
    G = splitG(g)
    #print(g)
    Data = [[[] for i in range(len(VT+VN))] for i in range(len(p)+1)]
    M = pd.DataFrame(data = Data,index = range(-1,len(dfa)),columns = VT+VN)
    for i in p:
        if i.type == 'R':
            for j in i.queue[0][-1]:
                a = i.queue[0][0:-2]
                #print(a)
                n  = 0
                for k in G:
                    if functools.reduce(lambda x, y : x and y, map(lambda p, q: p == q,k,a), True):   #缺陷：严格要求位置，可能对展望的判断有错误
                        break
                    n+=1
                M.loc[i.num][j].append('R'+str(n+1))

        
        for j in i.super:
            # print(i.num)
        #print(j)
            M.loc[j[0]][j[1]].append('S'+str(i.num))
    
    #M.loc[1]['#'].append('acc')
    return M
M = getM(dfa)


####最后将所有式子进行一斤规约

def main(s_get):
    
    v_sta = []
    v_mysta = []
    v_s = []
    result = ''
    beg_sta = 0
    sta = '#'
    mystate = Stack()
    mystate.push('S0')
    result += '{:>30}\t{:>30}\t{:>30}\t\n'.format(sta,mystate.show(),s_get)
    while True:
        print(beg_sta,s_get[0],'hh')
        #print(M)
        ch = M.loc[beg_sta,s_get[0]]  #查找M
        print(ch)
        if len(ch) == 0:#表示内部没有元素
            error()
            break
        if ch[0] == 'R7':
            print('分析成功')
            result += '分析成功'
            break
        if ch[0][0] == 'S':
            beg_sta = int(ch[0][1:])
            mystate.push(ch[0])  #移进状态
            sta += s_get[0]     #活前缀，入栈
            s_get = s_get[1:]   #
        if ch[0][0] == 'R':  #规约
            #查找
            n = int(ch[0][1])
            l = productions[n-1]   #规约串一条语句
            print(l)
            l1 = l[2:] #规约的字符
            l2 = l[0]   #新生成的字符
            l_l = len(l1)  
            sta += s_get[0]
            d_s = len(sta)-l_l
            sta = sta[0:d_s]  #出栈
            print('状态栈',mystate.show())
            #print(l_l)
            for i in range(l_l):  #状态出栈
                mystate.pop()
            #new_s = M.loc[str(mystate.top()[1])][l2][0]
            #sta.replace(len(sta)-l_l,len(sta),'')
            
            s_get = l2 + s_get    #更新字符串
            beg_sta = int(mystate.top()[1:])
        v_sta.append(sta+'\n')
        v_mysta.append(mystate.show())
        v_s.append(s_get+'\n')
        result += '{:>30}\t{:>30}\t{:>30}\t\n'.format(sta,mystate.show(),s_get)
        #print('内容栈',sta)
    pd.set_option('display.max_rows', None)  # 可以填数字，填None表示'行'无限制
    pd.set_option('display.max_columns', None)
    return result,M
        
#main('i+i*i#')

from tkinter import *
def on_click():
    en = entry.get()
    sta,m = main(en)
    t.insert(END,sta+'\n\n\n')
    #t.insert(LEFT,mysta)
    t.insert(END,m)
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