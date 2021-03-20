#include<iostream>
using namespace std;

bool homework012(Graph G,int vi,int vj)
{
    if(G.AdjMatrix[vi][vj]>=1&&G.AdjMatrix[vi][vj]<= INF)
        return true;
    else return false;
}
bool homework016(Graph G,int v0)
{
    for(int i = 1;i <= MaxVerNum;++i)
    {
        if(i==v0)
            continue;
        else
        {
            if(G.AdjMatrix[i][v0]>=1&&G.AdjMatrix[i][v0]<=INF)
            {
                return false;
            }
        }
    }
    return true;
}


void homework018(Graph &A,Graph &B,int verID)
{
    //visited
    visited[verID] = true;

    EdgeNode *p;
    p = A.VerList[verID].firstEdge;
    while(p)
    {

        //��Ϊ�ӽڵ���Ҫ����û�б����ʣ����Ҹýڵ����һ���ڵ�Ӧ������������ͼ����ͨ·��
        //ת�Ƶ��ڽӱ��Ͼ���˵�ڴ���ĳһ����ȵ�һ���ϼ��иýڵ㣬�ýڵ�Ҳδ�����ʡ�
        if(!visited[p->adjVer])//�����ҵ�������Ϊ�ӽڵ�Ľڵ�
        {
            EdgeNode u;
            u.adjVer = p->adjVer;           //��������
            u.eInfo = p->eInfo;
            u.next = NULL;
            if(B.VerList[verID].firstEdge==NULL)
            {
                B.VerList[verID].firstEdge = &u;
            }
            else
            {
                 EdgeNode *q = B.VerList[verID].firstEdge   //�����ýڵ����ӵĽڵ㣬�����ͷ�����������ǵ�
                do
                {
                 q = q->next;
                }while(q->next!=NULL);
                q->next = &u;
            }
            homework018(A,B,p->adjVer);
        }

        p = p->next;
    }
}

void homework018(Graph &A,Graph &B)
{
    homework018(A,B,1);
}
