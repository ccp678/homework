#include<stdio.h>
#include<stdlib.h>


int main()
{
    int N,K;
    char c;
    int I,J,m;
    int i,j;
    int s[10001];
    printf("输入操作\n");
    scanf("%d",&N);
    for(int i = 1; i <= N;++i)
    {
        scanf("%d",&s[i]);
    }
    scanf("%d",&K);
    getchar();         //吞掉输入的回车字符，为下边接受其他字符做准备
    for (int i = 0;i < K;++i)
    {
        scanf("%c%d%d%d",&c,&I,&J,&m);
        getchar();
        //printf("\n");
        for (j = I; j <= J;++j)
        {
            if(c == '-') s[j] -= m;
            else if (c == '+') s[j] += m;
            else if(c == '=' ) s[j] = m;
        }
            
    }
    for (i = 1;i <= N;++i)
    {
        printf("%d ",s[i]);
    }
    return 0;
}