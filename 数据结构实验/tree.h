#ifndef _TREE_H_
#define _TREE_H_
#include <iostream>
#include <queue>
using namespace std;

//����ɭ�֣��ĺ����ֵ������ʾ

typedef char elementType;

typedef struct csNode
{

	elementType data;

	struct csNode *firstChild, *nextSibling;

}csNode,*csTree;



//�������ɭ��

void perOrderTraverse(csNode *T)

{

    if(T)

    {

        cout<<T->data<<" ";           //���ʸ��ڵ�

        perOrderTraverse(T->firstChild);  //�ݹ�����������������

        perOrderTraverse(T->nextSibling);  //�ݹ�����������������

    }

}

//�������ɭ��

void postOrderTraverse(csNode *T)

{

    if(T)

    {

        postOrderTraverse(T->firstChild);  //�ݹ�����������������

        postOrderTraverse(T->nextSibling);  //�ݹ�����������������

        cout<<T->data<<" ";            //���ʸ��ڵ�

    }

}

//��α���ɭ��

void levelOrderTraverse(csNode *T)

{

    queue<csNode *> q;

    csNode * u,*n,*p;

    if(T==NULL)

    {

        return;

    }

    n=T;

    while(n)

    {

        p=n;

        q.push(p);

        while(!q.empty())

        {

            p=q.front();

            cout<<p->data<<" ";

            u=p->firstChild;

            while(u)

            {

                p=u;

                q.push(p);

                u=u->nextSibling;

            }

            q.pop();

        }

        n=n->nextSibling;

    }

}

//����ɭ��

void destroy(csNode *&T)

{

    if(T)

    {

        destroy(T->firstChild);

        destroy(T->nextSibling);

        delete T;

    }

}

#endif // _TREE_H_
