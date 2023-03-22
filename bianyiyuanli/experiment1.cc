#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<map>
#include<iomanip>

using namespace std;
bool judgeK(string s);          
bool judgeS(string S);
bool judgeAcc(string words);
bool judgeB(string words);
bool judgeR(string words);
bool judgeC(string words );
bool judgeStr(string words);


struct hl
{
    /* data */
    int h;
    int l;
};


//keyword表
vector <string> k={"do","end","for","if","printf","scanf","then","while"};
//Demarcation mark表
vector<string> s={",",";","(",")","[","]"};
//算术运算符表
vector<string> acc = {"+","-","*","/"};
//Relational operators表
vector<string> Relation = {"<","<=","=",">",">=","<>"};

vector<string> vs;

int main()
{
    //读入字符

    fstream f("yuan.txt");
    int n = 1;  //表示第几行
    string gs;
    cout.fill(' ');
    cout<<left<<setw(20)<<"words";
    cout<<left<<setw(20)<<"Binary sequence";
    cout<<left<<setw(20)<<"type";
    cout<<left<<setw(20)<<"position"<<endl;
    while(getline(f,gs))
    {
        //gs = s;
        int k = 0;
        if(gs.size() == 0) break;
        for (int i = 0;i <= gs.size();++i)
        {
            //当检测到单词时
            //cout<<left<<setw(20)<<gs[i]<<endl;
            if(gs[i] == ' '||gs[i] == '\t'||gs[i]=='\n'||gs[i] == '\0')
            {
                vs.push_back(gs.substr(k,i-k));
                k = i + 1;
            }
            
        }
        k = 0;  //表示第几列
        //需要将分解好的一些字符串再分解一遍,将一些运算符和Demarcation mark提取出来
        for (int i = 0;i < vs.size();++i)
        {
            k++;
            if(judgeK(vs[i]))  //判断是不是keyword
            {
                cout<<left<<setw(20)<<vs[i]+"";
                cout<<left<<setw(20)<<"(1," + vs[i]+")";
                cout<<left<<setw(20)<<"keyword";
                cout<<left<<setw(20)<<"("+to_string(n)+","+to_string(k)+")"<<endl; 
            }
            else if(judgeS(vs[i]))   //是Demarcation mark
            {
                cout<<left<<setw(20)<<vs[i]+"";
                cout<<left<<setw(20)<<"(2,"+vs[i]+")";
                cout<<left<<setw(20)<<"Demarcation mark";
                cout<<left<<setw(20)<<"("+to_string(n)+","+to_string(k)+")"<<endl; 
                
            }
            else if(judgeAcc(vs[i])) //判断算数运算符
            {

                cout<<left<<setw(20)<<vs[i]+"";
                cout<<left<<setw(20)<<"(3,"+vs[i]+")";
                cout<<left<<setw(20)<<"算数运算符";
                cout<<left<<setw(20)<<"("+to_string(n)+","+to_string(k)+")"<<endl; 
                
            }
            else if(judgeR(vs[i]))  //判断是不是Relational operators
            {
                
                cout<<left<<setw(20)<<vs[i]+"";
                cout<<left<<setw(20)<<"(4,"+vs[i]+")";
                cout<<left<<setw(20)<<"Relational operators";
                cout<<left<<setw(20)<<"("+to_string(n)+","+to_string(k)+")"<<endl; 
                
            }
            else if(judgeB(vs[i]))  //判断是否是identifier
            {
                
                cout<<left<<setw(20)<<vs[i]+"";
                cout<<left<<setw(20)<<"(6,"+vs[i]+")";
                cout<<left<<setw(20)<<"identifier";
                cout<<left<<setw(20)<<"("+to_string(n)+","+to_string(k)+")"<<endl; 
                
                
            }
            else if(judgeC(vs[i]))   //判断是否是constant
            {
                
                cout<<left<<setw(20)<<vs[i]+"";
                cout<<left<<setw(20)<<"(5,"+vs[i]+")";
                cout<<left<<setw(20)<<"constant";
                cout<<left<<setw(20)<<"("+to_string(n)+","+to_string(k)+")"<<endl; 
                
            }
             
            else if(judgeStr(vs[i]))
            {
                for (int j = 0;j < vs[i].size();++j )
                {
                    
                    string s(1,vs[i][j]);  //char类型转换成string  
                    if(judgeS(s))          //是Demarcation mark
                    {
                        cout<<left<<setw(20)<<s+"";
                        cout<<left<<setw(20)<<"(2,"+s+")";
                        cout<<left<<setw(20)<<"Demarcation mark";
                        cout<<left<<setw(20)<<"("+to_string(n)+","+to_string(k)+")"<<endl; 
                
                    }
                    else if(judgeAcc(s))     //算数是运算符
                    {
                        string s1(1,vs[i][j+1]);
                        if(judgeAcc(s1))
                        {
                            //运算符两个字符
                            cout<<left<<setw(20)<<s+s1+"";
                            cout<<left<<setw(20)<<"error";
                            cout<<left<<setw(20)<<"error";
                            cout<<left<<setw(20)<<"("+to_string(n)+","+to_string(k)+")"<<endl; 
                                ++j;
                                ++k;
                        }
                        else
                        {
                            //运算符只有一个
                            cout<<left<<setw(20)<<s+"";
                            cout<<left<<setw(20)<<"(3,"+s+")";
                            cout<<left<<setw(20)<<"算数运算符";
                            cout<<left<<setw(20)<<"("+to_string(n)+","+to_string(k)+")"<<endl; 
                
                        }
                    }
                    else if(judgeB(s))     
                    {
                        cout<<left<<setw(20)<<s+"";
                        cout<<left<<setw(20)<<"(6,"+s+")";
                        cout<<left<<setw(20)<<"identifier";
                        cout<<left<<setw(20)<<"("+to_string(n)+","+to_string(k)+")"<<endl; 
                
                    }
                    else if(judgeC(s))                //constant
                    {
                        int end = j;
                        for(;vs[i][j]<='9'&&vs[i][j] >= '0';++j)
                        {
                            k++;
                        }

                        k--;
                        string s1 = vs[i].substr(end,j-end);
                        cout<<left<<setw(20)<<s1+"";
                        cout<<left<<setw(20)<<"(5,"+s1+")";
                        cout<<left<<setw(20)<<"constant";
                        cout<<left<<setw(20)<<"("+to_string(n)+","+to_string(k)+")"<<endl; 
                
                        j--;
                    }
                    else if(judgeR(s))         //是Relational operators
                    {
                        string s1(1,vs[i][j+1]);
                        if(judgeR(s1))
                        {
                            //运算符两个字符
                            cout<<left<<setw(20)<<s+s1+"";
                            cout<<left<<setw(20)<<"(4,"+s+s1+")";
                            cout<<left<<setw(20)<<"Relational operators";
                            cout<<left<<setw(20)<<"("+to_string(n)+","+to_string(k)+")"<<endl; 
                
                            ++j;
                            ++k;
                        }
                        else
                        {
                            //运算符只有一个
                            cout<<left<<setw(20)<<s+"";
                            cout<<left<<setw(20)<<"(4,"+s+")";
                            cout<<left<<setw(20)<<"Relational operators";
                            cout<<left<<setw(20)<<"("+to_string(n)+","+to_string(k)+")"<<endl; 
                
                        }
                        
                    }
                    else
                    {
                        cout<<left<<setw(20)<<s+"";
                        cout<<left<<setw(20)<<"error";
                        cout<<left<<setw(20)<<"error";
                        cout<<left<<setw(20)<<"("+to_string(n)+","+to_string(k)+")"<<endl; 
                    }
                    k++;
                }
            }
            else
            {
                cout<<left<<setw(20)<<vs[i]+"";
                cout<<left<<setw(20)<<"error";
                cout<<left<<setw(20)<<"error";
                cout<<left<<setw(20)<<"("+to_string(n)+","+to_string(k)+")"<<endl;
                //continue;
            }
        }
        
        vs.clear();
        n++;
    }
    

    return 0;

}


//用于判断字符串是不是keyword
bool judgeK(string s)
{
    
    for (int i = 0;i < k.size();++i)
    {
        if(k[i] == s)
        {
            return true;
        }
    }

    return false;
}


bool judgeS(string S)
{
    for (int i = 0;i < s.size();++i)
    {
        if(S == s[i])
        {
            return true;
            
        }
    }
    return false;
}
//判断是否是运算符
bool judgeAcc(string words)
{
    for(int i = 0;i < acc.size();++i)
    {
        if(acc[i] == words)
        {
            return true;
        }
    }
    return false;
}

//判断是不是identifier
bool judgeB(string words)
{
    bool flag = true;
    int k = 0;
    for(int i=0;i < words.size();++i)
    {
        if(((words[i]>='A'&&words[i]<='Z')||(words[i]>='a'&&words[i]<='z')||words[i] == '_'))
        {
            k++;
        }
        if(i!=0&&words[i]>='0'&&words[i]<='9') k++;
    }
    if(k == words.size())
    {
        return true;
    }
    else
    {
        return false;
    }
}

//判断是否是Relational operators
bool judgeR(string words)
{
    for (int i=0;i < Relation.size() ;++i)
    {
        if(words == Relation[i])
        {
            return true;
        }
    }
    return false;
}
//判断是不是constant
bool judgeC(string words )
{
    int n = 0;  //点的个数

    for(int i = 0;i < words.size(); ++i)
    {
        if(n > 1)
        {
            return false;
        }
        if(words[i] == '.')
        {
            n++;
        }
        if(!(words[i] <= '9' && words[i] >= '0'))
        {
            return false;
        }

    }
    return true;
}
//判断是否是一条语句
bool judgeStr(string words)
{
    for(int i = 0;i < words.size();++i)
    {
        string s(1,words[i]);
        if(judgeR(s))
        {
            return true;
        }
        if(judgeAcc(s))
        {
            return true;
        }
        if(judgeS(s)) return true;
    }
    return false;
}