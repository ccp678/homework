#include <iostream>
#include <cstdlib>//标准库
#include <windows.h>//延时函数
#include <stdio.h>//获得getchar()
#include <ctime>//时间函数
#include<conio.h> //终端设置

#define MAX_X 7                /*这是设置迷宫的长和宽，最后需要修改，*/
#define MAX_Y 8

/*设置的出口条件也要改*/
/*
在判断入栈时，上线左右就变成了U,D,L,R
判断输出时为3，4，5，6
判断输入命令时为 w,s,a,d
*/
using namespace std;

bool flag = false;      //表示创建地图，成功用true
bool slow = false;       //更换游戏速度，true表示慢速度
bool autogame = false;   //表示更换游戏模式,true表示自动


int maze[MAX_X][MAX_Y];  //设置迷宫问题的内部情况

struct node
{
    int x;
    int y;
    char direction;
    struct node * next;   //上一步路径（怎么过来的）
};

class stack_of_maze{    //路线栈，记录做过的路线信息
private:
    struct node *head;
public:
    stack_of_maze():head(NULL){}
    ~stack_of_maze()   //删除链表
    {
        node *p = head;
        while(head!=NULL)
        {
            head = head->next;
            delete p;
            p = head;
        }
    }
    void push(int xx,int yy,char ddirection);
    node * pop(int &xx,int &yy);
    void print();
};

/*
设置一个新的节点用于插入，首先先将信息记录到新的节点中，
再把新的节点插入到扎顶。这个函数的功能是用于添加新的移动信息
*/


void stack_of_maze::push(int xx,int yy,char ddirection)
{
    struct node * new_node = new node;
    if(new_node!=NULL)
    {
        new_node->x = xx;
        new_node->y = yy;
        new_node->direction = ddirection;
        new_node->next =  NULL;
        if(head==NULL)
        {
            head = new_node;
        }
        else
        {
            new_node->next = head;
            head = new_node;
        }
    }
}

node * stack_of_maze:: pop(int &xx,int &yy)
{
    if(head!=NULL)
    {
        node *p = head;
        head = head->next;
        xx = p->x;
        yy = p->y;
        delete p;
    }
    return head;
}

void stack_of_maze::print()
{
    if(head!=NULL)
    {
        node *p = head;
        while(p!=NULL)
        {
            cout<<" "<<p->x<<" "<<p->y<<p->direction<<endl;
        }
    }
    else cout<<"栈空，打印失败"<<endl;
}
//创建地图(需要改)
void creatMzae()
{
    int maxway = MAX_X*MAX_Y;
    int x,y;
    //填充迷宫
    for(x = 0;x < MAX_X;x++)
    {
        for(y = 0;y < MAX_Y;y++)
        {
            maze[x][y] = 1;
        }
    }
    //随机数种子，以时间为参数
    srand((unsigned)(time(NULL)));
    //随即构建迷宫通路
    for(int i = 0;i < maxway;++i)
    {
        x = rand()%(MAX_X-2) + 1;
        y = rand()%(MAX_Y-2) + 1;
        maze[x][y] = 0;               //设置通路
    }
    maze[1][1] = 0;
    maze[MAX_X-2][MAX_Y-2] = 0;
    maze[0][1] = 3;
    maze[MAX_X-1][MAX_Y-2] = 0;
}
//打印地图
void printMaze()
{
    int x,y;
    system("cls");
    for(x = 0;x < MAX_X;x++)
    {
        for(y = 0;y < MAX_Y;y++)
        {

            if(maze[x][y]==0){cout<<" ";continue;}        //通路
            if(maze[x][y]==1){cout<<"#";continue;}        //墙
            if(maze[x][y]==2){cout<<"*";continue;}        //死胡同
            if(maze[x][y]==3){cout<<"@";continue;}        //向下走
            if(maze[x][y]==4){cout<<"@";continue;}
            if(maze[x][y]==5){cout<<"@";continue;}
            if(maze[x][y]==6){cout<<"@";continue;}
            if(maze[x][y]==7){cout<<"@";continue;}   //当前站立位置
        }
        cout<<endl;
    }
    if(slow)
    {
        Sleep(1);
    }
}
void check(stack_of_maze &s)
{
    int temp[MAX_X][MAX_Y];
    for(int x = 0;x < MAX_X;x++)
    {
        for(int y = 0;y < MAX_Y;y++)
        {
            temp[x][y] = maze[x][y];
        }
    }

    int x = 1,y = 1;  //出发点
    while(true)
    {
        temp[x][y] = 2;

        //向下
        if(temp[x+1][y] == 0)
        {
            s.push(x,y,'D');
            //在当前位置做一个向下的标志
            temp[x][y] = 3;
            x = x+1;
            temp[x][y] = 7;  //当前站立的图标

        }

        //向右
        if(temp[x][y+1]==0)
        {
            s.push(x,y,'R');

            //在当抢位置做一个向右的标志
            temp[x][y+1] = 4;
            ++y;
            temp[x][y] = 7;

        }

        //向上
        if(temp[x-1][y]==0)
        {
            s.push(x,y,'U');
            //做一个向上的标志

            temp[x][y] = 6;
            x--;
            temp[x][y] = 7;
        }

        //向左
        if(temp[x][y-1]==0)
        {
            s.push(x,y,'L');
            //做一个向左的标志
            temp[x][y] = 5;
            --y;
            temp[x][y] = 7;
        }

        //判断是否达到出口，如果达到出口则flag标记为true
            if((x==MAX_X-1)&&(y==MAX_Y-2)){
                flag = true;
                return ;
            }
            else continue;

            //上下左右都不通，退回起点
            if(s.pop(x,y)==NULL&&temp[x-1][y]!=0&&temp[x][y-1]!=0&&temp[x][y+1]&&temp[x+1][y]!=0)
            {
                temp[0][1] = 7;
                if(temp[1][1]!=1)
                {
                    temp[1][1] = 2;
                }
                return;
            }

    }
}

//命令识别

void move()
{
    int x = 1,y = 1;
    while(1)
    {
        //判断输入命令
        switch(getch()){
        case 's':
            if(maze[x+1][y]==0){
                maze[x][y] = 0;
                x++;
                maze[x][y] = 7;
                printMaze();
                if(x==MAX_X-1&&y==MAX_Y-2)
                {
                    cout<<"\n\n         成功走出迷宫      "<<endl;
                    return;
                }
            }
            break;
        case 'd':
            if(maze[x][y+1]==0){
                maze[x][y] = 0;
                y++;
                maze[x][y] = 7;
                printMaze();
                if(x==MAX_X-1&&MAX_Y-2)
                {
                    cout<<"\n\n         成功走出迷宫      "<<endl;
                    return;
                }
            }
            break;
        case 'w':
            if(maze[x-1][y]==0)
            {
                maze[x][y] = 0;
                x=x-1;
                maze[x][y] = 7;
                printMaze();
                if(x==MAX_X-1&&y==MAX_Y-2)
                {
                    cout<<"\n\n         成功走出迷宫      "<<endl;
                    return;
                }
            }
            break;
        case 'a':
            if(maze[x][y-1]==0)
            {
                maze[x][y] = 0;
                y=y-1;
                maze[x][y] = 7;
                printMaze();
                if(x==MAX_X-1&&y==MAX_Y-2)
                {
                    cout<<"\n\n         成功走出迷宫      "<<endl;
                    return;
                }
            }
            break;
        }
    }
}

//自动寻路
void autoMove(stack_of_maze &s)
{
    int x = 1,y = 1;
    while(true)
    {
        maze[x][y] = 2;

        //向下寻路
        if(maze[x+1][y]==0)
        {
            s.push(x,y,'D');   //将操作入栈，记录路线
            maze[x][y] = 3;
            x++;
            maze[x][y] = 7;
            if(slow) printMaze();
            if(x==MAX_X-1&&y==MAX_Y-2)
            {
                s.push(x,y,'*');   //标志已经结束
                cout<<"\n\n         成功走出迷宫      "<<endl;
                return;
            }
            else continue;


        }

        //向右寻路
        if(maze[x][y+1]==0)
        {
            s.push(x,y,'R');
            maze[x][y] = 4;
            y++;
            maze[x][y] = 7;
            printMaze();
            if(slow) printMaze();
            if(x==MAX_X-1&&y==MAX_Y-2)
            {
                s.push(x,y,'*');
                cout<<"\n\n         成功走出迷宫      "<<endl;
                return;
            } else continue;
        }

        //向上
        if(maze[x-1][y]==0)
        {
            s.push(x,y,'U');
            maze[x][y] == 6;
            x--;
            maze[x][y] = 7;
            printMaze();
            if(slow) printMaze();
            if(x==MAX_X-1&&y==MAX_Y-2)
            {
                s.push(x,y,'*');
                cout<<"\n\n         成功走出迷宫      "<<endl;
                return;
            } else continue;
        }

        //向左
        if(maze[x][y-1]==0)
        {
            s.push(x,y,'L');
            maze[x][y] == 5;
            y--;
            maze[x][y] = 7;
            printMaze();
            if(slow) printMaze();
            if(x==MAX_X-1&&y==MAX_Y-2)
            {
                s.push(x,y,'*');
                cout<<"\n\n         成功走出迷宫      "<<endl;
                return;
            } else continue;
        }

        //上下左右不通则退回
        if(s.pop(x,y)==NULL && maze[x-1][y]!=0 && maze[x][y-1]!=0 && maze[x][y+1]!=0 && maze[x+1][y]!=0)
        {
            cout<<"\n\n         没有成功走出迷宫      "<<endl;
            maze[0][1] = 7;
            if(maze[1][1] != 1)
            {
                maze[1][1]=2;   //标记为死胡同
            }
            return;
        }

    }
}

void menu();

void gamestart()
{
    //初始化地图
    flag = false;
    while(!flag)
    {
        //进度条
        system("cls");
        cout<<"\t*                loading.              *"<<endl;
        Sleep(1);
        system("cls");
        cout<<"\t*                loading..             *"<<endl;
        Sleep(1);
        system("cls");
        cout<<"\t*                loading...            *"<<endl;
        stack_of_maze s;
        //创建地图
        creatMzae();
        //检查地图是否创建成功
        check(s);
    }

    //迷宫创建完毕,输出迷宫
    printMaze();
    cout<<"\n\n              输入enter键继续"<<endl;
    //自行游戏
    if(!autogame)
    {
        move();
        cout<<"\n\n              输入enter键继续"<<endl;
        getchar();
        menu();
    }else{
        stack_of_maze s1;
        autoMove(s1);
    }
    printMaze();
    cout<<"\n\n              输入enter键继续"<<endl;
    getchar();
    menu();
}

void menu()
{
    system("cls");
    //int num;
    cout<<"\t****************************************"<<endl;
    cout<<"\t*                                      *"<<endl;
    cout<<"\t*               1.查看路径             *"<<endl;
    cout<<"\t*                                      *"<<endl;
    cout<<"\t*               2.自动进行             *"<<endl;
    cout<<"\t*                                      *"<<endl;
    cout<<"\t*               3.自行游戏             *"<<endl;
    cout<<"\t*                                      *"<<endl;
    cout<<"\t*               4.退出游戏             *"<<endl;
    cout<<"\t*                                      *"<<endl;
    cout<<"\t****************************************"<<endl;
    slow = false;
    //选择模式
    switch(getch())
    {
    case '1':
        autogame = true;
        gamestart();
        break;
    case'2':
        autogame = true;
        gamestart();
        break;
    case'3':
        autogame = false;
        gamestart();
        break;
    case'4':
        exit(1);
    default:
        cout<<"\n\n              错误操作，输入enter返回！"<<endl;
        getchar();
        menu();
    }
    getchar();
}

void creat()
{
    while(true)
    {
        switch(getch())
        {
        case 'w':
        }
    }
}

int main()
{
    /*autogame = true;
    //gamestart();
    stack_of_maze s;
    creatMzae();

    //check(s);
    autoMove(s);
    printMaze();
    /*stack_of_maze s1;
    autoMove(s1);
    printMaze();*/
    menu();
    return 0;
}
