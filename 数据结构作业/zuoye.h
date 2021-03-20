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

        //作为子节点需要满足没有被访问，而且该节点和上一个节点应该相连，记在图中有通路。
        //转移到邻接表上就是说在代表某一点出度的一行上既有该节点，该节点也未被访问。
        if(!visited[p->adjVer])//遍历找到可以作为子节点的节点
        {
            EdgeNode u;
            u.adjVer = p->adjVer;           //复制数据
            u.eInfo = p->eInfo;
            u.next = NULL;
            if(B.VerList[verID].firstEdge==NULL)
            {
                B.VerList[verID].firstEdge = &u;
            }
            else
            {
                 EdgeNode *q = B.VerList[verID].firstEdge   //遍历该节点连接的节点，如果与头结点相连，泽盖垫
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
