#include <iostream>
#include <cstdlib>//��׼��
#include <windows.h>//��ʱ����
#include <stdio.h>//���getchar()
#include <ctime>//ʱ�亯��
#include<conio.h> //�ն�����

#define MAX_X 7                /*���������Թ��ĳ��Ϳ������Ҫ�޸ģ�*/
#define MAX_Y 8

/*���õĳ�������ҲҪ��*/
/*
���ж���ջʱ���������Ҿͱ����U,D,L,R
�ж����ʱΪ3��4��5��6
�ж���������ʱΪ w,s,a,d
*/
using namespace std;

bool flag = false;      //��ʾ������ͼ���ɹ���true
bool slow = false;       //������Ϸ�ٶȣ�true��ʾ���ٶ�
bool autogame = false;   //��ʾ������Ϸģʽ,true��ʾ�Զ�


int maze[MAX_X][MAX_Y];  //�����Թ�������ڲ����

struct node
{
    int x;
    int y;
    char direction;
    struct node * next;   //��һ��·������ô�����ģ�
};

class stack_of_maze{    //·��ջ����¼������·����Ϣ
private:
    struct node *head;
public:
    stack_of_maze():head(NULL){}
    ~stack_of_maze()   //ɾ������
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
����һ���µĽڵ����ڲ��룬�����Ƚ���Ϣ��¼���µĽڵ��У�
�ٰ��µĽڵ���뵽��������������Ĺ�������������µ��ƶ���Ϣ
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
    else cout<<"ջ�գ���ӡʧ��"<<endl;
}
//������ͼ(��Ҫ��)
void creatMzae()
{
    int maxway = MAX_X*MAX_Y;
    int x,y;
    //����Թ�
    for(x = 0;x < MAX_X;x++)
    {
        for(y = 0;y < MAX_Y;y++)
        {
            maze[x][y] = 1;
        }
    }
    //��������ӣ���ʱ��Ϊ����
    srand((unsigned)(time(NULL)));
    //�漴�����Թ�ͨ·
    for(int i = 0;i < maxway;++i)
    {
        x = rand()%(MAX_X-2) + 1;
        y = rand()%(MAX_Y-2) + 1;
        maze[x][y] = 0;               //����ͨ·
    }
    maze[1][1] = 0;
    maze[MAX_X-2][MAX_Y-2] = 0;
    maze[0][1] = 3;
    maze[MAX_X-1][MAX_Y-2] = 0;
}
//��ӡ��ͼ
void printMaze()
{
    int x,y;
    system("cls");
    for(x = 0;x < MAX_X;x++)
    {
        for(y = 0;y < MAX_Y;y++)
        {

            if(maze[x][y]==0){cout<<" ";continue;}        //ͨ·
            if(maze[x][y]==1){cout<<"#";continue;}        //ǽ
            if(maze[x][y]==2){cout<<"*";continue;}        //����ͬ
            if(maze[x][y]==3){cout<<"@";continue;}        //������
            if(maze[x][y]==4){cout<<"@";continue;}
            if(maze[x][y]==5){cout<<"@";continue;}
            if(maze[x][y]==6){cout<<"@";continue;}
            if(maze[x][y]==7){cout<<"@";continue;}   //��ǰվ��λ��
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

    int x = 1,y = 1;  //������
    while(true)
    {
        temp[x][y] = 2;

        //����
        if(temp[x+1][y] == 0)
        {
            s.push(x,y,'D');
            //�ڵ�ǰλ����һ�����µı�־
            temp[x][y] = 3;
            x = x+1;
            temp[x][y] = 7;  //��ǰվ����ͼ��

        }

        //����
        if(temp[x][y+1]==0)
        {
            s.push(x,y,'R');

            //�ڵ���λ����һ�����ҵı�־
            temp[x][y+1] = 4;
            ++y;
            temp[x][y] = 7;

        }

        //����
        if(temp[x-1][y]==0)
        {
            s.push(x,y,'U');
            //��һ�����ϵı�־

            temp[x][y] = 6;
            x--;
            temp[x][y] = 7;
        }

        //����
        if(temp[x][y-1]==0)
        {
            s.push(x,y,'L');
            //��һ������ı�־
            temp[x][y] = 5;
            --y;
            temp[x][y] = 7;
        }

        //�ж��Ƿ�ﵽ���ڣ�����ﵽ������flag���Ϊtrue
            if((x==MAX_X-1)&&(y==MAX_Y-2)){
                flag = true;
                return ;
            }
            else continue;

            //�������Ҷ���ͨ���˻����
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

//����ʶ��

void move()
{
    int x = 1,y = 1;
    while(1)
    {
        //�ж���������
        switch(getch()){
        case 's':
            if(maze[x+1][y]==0){
                maze[x][y] = 0;
                x++;
                maze[x][y] = 7;
                printMaze();
                if(x==MAX_X-1&&y==MAX_Y-2)
                {
                    cout<<"\n\n         �ɹ��߳��Թ�      "<<endl;
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
                    cout<<"\n\n         �ɹ��߳��Թ�      "<<endl;
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
                    cout<<"\n\n         �ɹ��߳��Թ�      "<<endl;
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
                    cout<<"\n\n         �ɹ��߳��Թ�      "<<endl;
                    return;
                }
            }
            break;
        }
    }
}

//�Զ�Ѱ·
void autoMove(stack_of_maze &s)
{
    int x = 1,y = 1;
    while(true)
    {
        maze[x][y] = 2;

        //����Ѱ·
        if(maze[x+1][y]==0)
        {
            s.push(x,y,'D');   //��������ջ����¼·��
            maze[x][y] = 3;
            x++;
            maze[x][y] = 7;
            if(slow) printMaze();
            if(x==MAX_X-1&&y==MAX_Y-2)
            {
                s.push(x,y,'*');   //��־�Ѿ�����
                cout<<"\n\n         �ɹ��߳��Թ�      "<<endl;
                return;
            }
            else continue;


        }

        //����Ѱ·
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
                cout<<"\n\n         �ɹ��߳��Թ�      "<<endl;
                return;
            } else continue;
        }

        //����
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
                cout<<"\n\n         �ɹ��߳��Թ�      "<<endl;
                return;
            } else continue;
        }

        //����
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
                cout<<"\n\n         �ɹ��߳��Թ�      "<<endl;
                return;
            } else continue;
        }

        //�������Ҳ�ͨ���˻�
        if(s.pop(x,y)==NULL && maze[x-1][y]!=0 && maze[x][y-1]!=0 && maze[x][y+1]!=0 && maze[x+1][y]!=0)
        {
            cout<<"\n\n         û�гɹ��߳��Թ�      "<<endl;
            maze[0][1] = 7;
            if(maze[1][1] != 1)
            {
                maze[1][1]=2;   //���Ϊ����ͬ
            }
            return;
        }

    }
}

void menu();

void gamestart()
{
    //��ʼ����ͼ
    flag = false;
    while(!flag)
    {
        //������
        system("cls");
        cout<<"\t*                loading.              *"<<endl;
        Sleep(1);
        system("cls");
        cout<<"\t*                loading..             *"<<endl;
        Sleep(1);
        system("cls");
        cout<<"\t*                loading...            *"<<endl;
        stack_of_maze s;
        //������ͼ
        creatMzae();
        //����ͼ�Ƿ񴴽��ɹ�
        check(s);
    }

    //�Թ��������,����Թ�
    printMaze();
    cout<<"\n\n              ����enter������"<<endl;
    //������Ϸ
    if(!autogame)
    {
        move();
        cout<<"\n\n              ����enter������"<<endl;
        getchar();
        menu();
    }else{
        stack_of_maze s1;
        autoMove(s1);
    }
    printMaze();
    cout<<"\n\n              ����enter������"<<endl;
    getchar();
    menu();
}

void menu()
{
    system("cls");
    //int num;
    cout<<"\t****************************************"<<endl;
    cout<<"\t*                                      *"<<endl;
    cout<<"\t*               1.�鿴·��             *"<<endl;
    cout<<"\t*                                      *"<<endl;
    cout<<"\t*               2.�Զ�����             *"<<endl;
    cout<<"\t*                                      *"<<endl;
    cout<<"\t*               3.������Ϸ             *"<<endl;
    cout<<"\t*                                      *"<<endl;
    cout<<"\t*               4.�˳���Ϸ             *"<<endl;
    cout<<"\t*                                      *"<<endl;
    cout<<"\t****************************************"<<endl;
    slow = false;
    //ѡ��ģʽ
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
        cout<<"\n\n              �������������enter���أ�"<<endl;
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
