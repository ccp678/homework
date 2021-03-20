#include <iostream>
#include"experiment.h"
#include <iostream>
#include "createGrpAdjMatrix.h"
#include "tree.h"
using namespace std;

int main()
{
    int i,x;

    Graph G;

    csTree T;

    int path[MaxVerNum];

    int dist[MaxVerNum];

    int topoList[MaxVerNum];        //拓扑序列

    int antiTopoList[MaxVerNum];    //逆拓扑序列

    cellType Dist[MaxVerNum][MaxVerNum];

    int Path[MaxVerNum][MaxVerNum];

    int vet[MaxVerNum]={0};         //事件的最早发生时间

    int vlt[MaxVerNum]={0};         //事件的最晚发生时间

    char fileName[100];         //保存文件名

    //menu();

    cout<<"请输入执行序号：";

    cin>>i;

    while(i)

    {

        switch(i)

        {

            case 1:

                cout<<"请输入打开的文件名：";

                cin>>fileName;

                if(CreateGrpFromFile(fileName,G))

                {

                        cout<<"数据处理完毕！"<<endl;

                }

            break;

            case 2:

                cout<<"请输入访问图的起始顶点编号：";

                cin>>x;

                cout<<"深度优先遍历序为:";

                DFSTraverse(G,x);

                cout<<endl;

                cout<<"广度优先遍历序为:";

                BFSTraverse(G,x);

                cout<<endl;

            break;

            case 3:

                cout<<"边或弧的数目为："<<G.ArcNum;

                cout<<endl;

            break;

            case 4:

                T=NULL;

                cout<<"请输入访问图的起始顶点编号：";

                cin>>x;

                T=DFSForest(G,T,x);

                cout<<"树或森林的先序遍历序为：";

                perOrderTraverse(T);

                cout<<endl;

                destroy(T);

            break;

            case 5:

                T=NULL;

                cout<<"请输入访问图的起始顶点编号：";

                cin>>x;

                T=BFSForest(G,T,x);

                cout<<"树或森林的先序遍历序为：";

                perOrderTraverse(T);

                cout<<endl;

                destroy(T);

            break;

            case 6:

                cout<<"请输入访问图的起始顶点编号：";

                cin>>x;

                prim(G,x);

                cout<<endl;

            break;

            case 7:

                cout<<"Kruskal最小生成树为：";

                Kruskal(G);

                cout<<endl;

            break;

            case 8:

                cout<<"请输入访问图的起始顶点编号：";

                cin>>x;

                Dijkstra(G,path,dist,x);

                printDijkstra(G,path,dist,x);

            break;

            case 9:

                floyd(G,Dist,Path);

                printFloyd(G,Dist,Path);

            break;

            case 10:

                printTopoList(G,topoList,vet,vlt);

                cout<<endl;



                cout<<endl;

            break;

            case 11:

                TopoSort(G,topoList,vet,vlt);

                //antiTopologicalSort(G,vlt,vet);

                printCriticalPath(G,topoList,vlt,vet);

                cout<<endl;

            break;

        }

        system("PAUSE");

        system("CLS");

//        menu();

        cout<<"请输入执行序号：";

        cin>>i;

    }

    return 0;
}
