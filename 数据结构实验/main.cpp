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

    int topoList[MaxVerNum];        //��������

    int antiTopoList[MaxVerNum];    //����������

    cellType Dist[MaxVerNum][MaxVerNum];

    int Path[MaxVerNum][MaxVerNum];

    int vet[MaxVerNum]={0};         //�¼������緢��ʱ��

    int vlt[MaxVerNum]={0};         //�¼���������ʱ��

    char fileName[100];         //�����ļ���

    //menu();

    cout<<"������ִ����ţ�";

    cin>>i;

    while(i)

    {

        switch(i)

        {

            case 1:

                cout<<"������򿪵��ļ�����";

                cin>>fileName;

                if(CreateGrpFromFile(fileName,G))

                {

                        cout<<"���ݴ�����ϣ�"<<endl;

                }

            break;

            case 2:

                cout<<"���������ͼ����ʼ�����ţ�";

                cin>>x;

                cout<<"������ȱ�����Ϊ:";

                DFSTraverse(G,x);

                cout<<endl;

                cout<<"������ȱ�����Ϊ:";

                BFSTraverse(G,x);

                cout<<endl;

            break;

            case 3:

                cout<<"�߻򻡵���ĿΪ��"<<G.ArcNum;

                cout<<endl;

            break;

            case 4:

                T=NULL;

                cout<<"���������ͼ����ʼ�����ţ�";

                cin>>x;

                T=DFSForest(G,T,x);

                cout<<"����ɭ�ֵ����������Ϊ��";

                perOrderTraverse(T);

                cout<<endl;

                destroy(T);

            break;

            case 5:

                T=NULL;

                cout<<"���������ͼ����ʼ�����ţ�";

                cin>>x;

                T=BFSForest(G,T,x);

                cout<<"����ɭ�ֵ����������Ϊ��";

                perOrderTraverse(T);

                cout<<endl;

                destroy(T);

            break;

            case 6:

                cout<<"���������ͼ����ʼ�����ţ�";

                cin>>x;

                prim(G,x);

                cout<<endl;

            break;

            case 7:

                cout<<"Kruskal��С������Ϊ��";

                Kruskal(G);

                cout<<endl;

            break;

            case 8:

                cout<<"���������ͼ����ʼ�����ţ�";

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

        cout<<"������ִ����ţ�";

        cin>>i;

    }

    return 0;
}
