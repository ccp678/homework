from collections import defaultdict

#设置优先级
operand = defaultdict(int)
operand['=']=0
operand['+']=1
operand['-']=1
operand['*']=2
operand['/']=2

op = ['+','-','*','/','=']
#栈

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
            print(self.__list)
            return self.__list
            # return ''.join(self.__list)
            #print('栈',self.__list)
        def is_empty(self):
            if self.__list == []:
                return True
            else: return False

##识别字符串中的内容将数字和符号区分开来
def get_sentence(s):
    s_s = list(s)
    l_s = ''
    l_l = len(l_s)
    bool_l = False
    v_s = []
    for i in range(len(s_s)):
        if s_s[i] in op:
            l_s += ' ' + s_s[i] + ' '
        elif s_s[i] == '(':
            l_s += s_s[i] + ' '
        elif s_s[i] == ')':
            l_s += ' ' + s_s[i]
        else:
            l_s += s_s[i]
    return l_s


#将中缀式改为后缀式
def get_Suffixform(str_in):
    sym_stack = Stack()   #符号栈
    operand_sta = Stack() #生成后缀式的栈
    l = str_in
    for i in l:
        
        #print(operand[sym_stack.top()])
        if i in op or i == '(' or i == ')':   #当遇到符号的时候判断入符号栈
            #当前符号栈为空或者遇到括号，
            if sym_stack.is_empty() or i == '(' or sym_stack.top() == '(':  #当遇到(时，不管前边是什么运算，先计算括号内的，(入栈
                sym_stack.push(i)
            elif i == ')':           #遇到)将最近的(之间的内容调出来，将括号的内容送入生成式栈
                c = sym_stack.pop()
                while (c != '('):
                    operand_sta.push(c)
                    c = sym_stack.pop()
            elif  operand[sym_stack.top()] < operand[i]:   #遇到大的优先级符号，需要将符号入栈
                sym_stack.push(i)
                #print(True)
            else:    #将优先级<=的，先将符号栈的内容放入后缀式栈，然后再将现在的符号放入符号栈
                operand_sta.push(sym_stack.pop())
                sym_stack.push(i)
        else:   #是数字，直接放入后缀式栈中
            operand_sta.push(i) 
            #sym_stack.push(i)
        #operand_sta.show()
        #sym_stack.show()
    while(not sym_stack.is_empty()):  #将符号栈中的内容弹出并压入操作数中
    
        operand_sta.push(sym_stack.pop())
    
    return operand_sta.show()



def get_result(str_in):
    result = []
    s = Stack()   #最后的
    num = 0
    for c in str_in:
        if c not in op:  #表示是数字，直接入栈
            s.push(c)
        else:
            num += 1     #遇到符号后，就要生成四元式
            t_str = 'T' + str(num)
            if c != '=':
                ss = s.pop()
                result.append('('+c+','+s.pop()+','+ss+','+t_str+')')
                s.push(t_str)
            else:
                result.append('('+c+','+s.pop()+','+'-'+','+t_str+')')
        
    #print(result)
    return result


def main(s):
    #s = '52-((((7-2)*5/(4-2)-3)/5-2)*6-2)'
    #s = 'x=1+2+3*5-(7-2)*2'
    s = get_sentence(s)
    #print(s)
    l_s = s.split(' ')
    sta = get_Suffixform(l_s)
    r = get_result(sta)
    #print(list(s))

    print(r)
    return  r

#main()

from tkinter import *
def on_click():
    en = entry.get()
    r = main(en)
    sta = [_+'\n' for _ in r]
    s = ''.join(sta)
    t.insert(END,s)
    #t.insert(LEFT,mysta)
    #t.insert(END,m)
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

