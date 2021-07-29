#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include<set>
#include<iomanip>
using namespace std;
ifstream input("in1.txt");
map<char,set<char>>first; //first集合
map<char,set<char>>follow; //follo集合
map<char,set<char>>first_temp;
map<char,set<char>>follow_temp;
map<char,set<string>>string_temp;
set<char>table; //终结符号
set<char>no_end; //非终结符
string s[10][10]; //分析表
map<char,int>xlab;
map<char,int>ylab;
void First(){
    string temp;
    while(getline(input,temp)){
         int len = temp.length();
         if(first.find(temp[0])==first.end()){
            int l=5;
            while(temp[l]!='|'&&l<len) l++;
                 if(!(temp[5]>='A'&&temp[5]<='Z'))
                     first[temp[0]].insert(temp[5]);
                 else
                     first_temp[temp[0]].insert(temp[5]);
                 if(l<len&&temp[l]=='|'){
                    if(!(temp[l+2]>='A'&&temp[l+2]<='Z'))
                         first[temp[0]].insert(temp[l+2]);
                    else first_temp[temp[0]].insert(temp[l+2]);
               }
         }
    }
    map<char,set<char>>::iterator it=first_temp.begin();
    while(first_temp.size()!=0){
        set<char>::iterator ij=it->second.begin();
        while(ij!=it->second.end()){
             if(first.find(*ij)!=first.end()){
                set<char>::iterator ik=first[*ij].begin();
                while(ik!=first[*ij].end())
                      first[it->first].insert(*ik),ik++;
                it->second.erase(ij++);
             }
             else ij++;
        }
        if(it->second.size()==0)
           first_temp.erase(it++);
        else
           it++;
        if(it==first_temp.end())
           it=first_temp.begin();
    }
    input.close();
}

void Follow(){
     input.open("in.txt");
     string temp;
     table.insert('$');
     while(getline(input,temp)){
           int l=5,len=temp.length();
           no_end.insert(temp[0]);
           while(l<len-1&&temp[l+1]!=' '){
                 if(!(temp[l]>='A'&&temp[l]<='Z')&&temp[l]!='e')
                     table.insert(temp[l]);
                 if(temp[l]>='A'&&temp[l]<='Z') {
                    follow[temp[l]].insert('$');
                    if(!(temp[l+1]>='A'&&temp[l+1]<='Z'))
                         follow[temp[l]].insert(temp[l+1]);
                    else{
                         int ok=1;
                         set<char>::iterator it=first[temp[l+1]].begin();
                         while(it!=first[temp[l+1]].end()){
                               if(*it!='e')
                               follow[temp[l]].insert(*it);
                               else ok=0;
                               it++;
                         if(!ok)
                            follow_temp[temp[l]].insert(temp[0]);
                        }
                    }

                }
            l++;
          }
          int k=0;
          while(temp[k+5]!='\0'&&temp[k+5]!='|')
                k++;
          if(temp[k+5]=='\0')
              string_temp[temp[0]].insert(temp.substr(5,k));
          else
              string_temp[temp[0]].insert(temp.substr(5,k-1));
          if(temp[k+5]=='|'){
             int y=0;
             while(temp[k+5+y]!='\0')
                   y++;
             string_temp[temp[0]].insert(temp.substr(k+7,y));
          }
          if(l<len&&temp[l]>='A'&&temp[l]<='Z')
             follow_temp[temp[l]].insert(temp[0]);
         while(l<len) {
              if(!(temp[l]>='A'&&temp[l]<='Z')&&temp[l]!=' '&&temp[l]!='|'&&temp[l]!='e')
                   table.insert(temp[l]);
              l++;
         }
     }
    map<char,set<char>>::iterator it=follow_temp.begin();
    while(follow_temp.size()!=0){
        set<char>::iterator ij=it->second.begin();
        while(ij!=it->second.end()){
             if(follow.find(*ij)!=follow.end()){
                set<char>::iterator ik=follow[*ij].begin();
                while(ik!=follow[*ij].end())
                      follow[it->first].insert(*ik),ik++;
                it->second.erase(ij++);
             }
             else
                ij++;
        }
        if(it->second.size()==0)
           follow_temp.erase(it++);
        else
           it++;
        if(it==follow_temp.end())
           it=follow_temp.begin();
    }
    input.close();
}


void show_first(){ //打印FIRST集合
     cout<<"FIRST集合为："<<endl;
     map<char,set<char>>::iterator it=first.begin();
     while(it!=first.end()){
           cout<<"FIRST"<<"("<<it->first<<")"<<"={ ";
           set<char>::iterator ij=it->second.begin();
           int l=0,len=it->second.size();
           while(ij!=it->second.end()){
            cout<<*ij;ij++;
            if(l<=len-2)
               cout<<" , ";
            l++;
        }
        it++;
        cout<<" }"<<endl;
    }
}

void show_follow(){ //打印FOLLOW集合
     cout<<"FOLLOW集合为："<<endl;
     map<char,set<char>>::iterator it=follow.begin();
     while(it!=follow.end()){
          cout<<"FOLLOW"<<"("<<it->first<<")"<<"={ ";
          set<char>::iterator ij=it->second.begin();
          int l=0,len=it->second.size();
          while(ij!=it->second.end()){
                cout<<*ij;ij++;
                if(l<=len-2)
                   cout<<" , ";
                l++;
          }
        it++;
        cout<<" }"<<endl;
    }
}

void show_table(){  //打印并存储LL1分析表
    cout<<"LL1分析表为："<<endl;
    cout<<"---------------------------------------------------"<<endl;
    cout<<"        ";
    set<char>::iterator it=table.begin();
    int k=0;
    while(it!=table.end()){
        ylab[*it]=k++;
        cout<<*it<<"         ";it++;
    }
    cout<<endl;
    it = no_end.begin();
    int l=0;
    while(it!=no_end.end()){
         cout<<*it<<"       ";
         set<char>::iterator ij=table.begin();
         int j=0;
         while(ij!=table.end()){
               set<string>::iterator ik=string_temp[*it].begin();
               int ok=0;
               while(ik!=string_temp[*it].end()){
                    string temp=*ik;
                    if(first[temp[0]].count(*ij)!=0||temp[0]==*ij){
                       ok=1;cout<<*it<<"->"<<temp; s[l][j]=temp;
                       for(int x=temp.length()+3;x<10;x++) cout<<" ";
                     }
                    if(ok==0 &&(first[temp[0]].count('e')!=0||(*ik)[0]=='e')){
                          if(follow[*it].count(*ij)!=0){
                             ok=1;cout<<*it<<"->"<<temp; s[l][j]=temp;
                             for(int x=temp.length()+3;x<10;x++)
                                 cout<<" ";
                          }
                    }
                    ik++;
                }
               if(!ok)
                  cout<<"          ",s[l][j]=" ";
               ij++;
               j++;
          }
         cout<<endl;
         xlab[*it]=l;
         it++;
         l++;
    }

}

int main(){
    First(); //求first集合
    show_first(); //打印first集合
    Follow(); //求follow集合
    show_follow(); //打印follo集合
    show_table(); //打印LL1分析表
}
