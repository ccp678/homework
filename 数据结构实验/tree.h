#ifndef _TREE_H_
#define _TREE_H_
#include <iostream>
#include <queue>
using namespace std;

//树（森林）的孩子兄弟链表表示

typedef char elementType;

typedef struct csNode
{

	elementType data;

	struct csNode *firstChild, *nextSibling;

}csNode,*csTree;



//先序遍历森林

void perOrderTraverse(csNode *T)

{

    if(T)

    {

        cout<<T->data<<" ";           //访问根节点

        perOrderTraverse(T->firstChild);  //递归调用先序遍历左子树

        perOrderTraverse(T->nextSibling);  //递归调用先序遍历右子树

    }

}

//后序遍历森林

void postOrderTraverse(csNode *T)

{

    if(T)

    {

        postOrderTraverse(T->firstChild);  //递归调用先序遍历左子树

        postOrderTraverse(T->nextSibling);  //递归调用先序遍历右子树

        cout<<T->data<<" ";            //访问根节点

    }

}

//层次遍历森林

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

//销毁森林

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
