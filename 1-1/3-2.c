#include<stdio.h>
#include<stdlib.h>


int main()
{
    int M,N,K;
    int i,j;
    char s[100];
    int a,b,flag;
    int sum = 0;
    printf("请输入M,N,K\n");
    scanf("%d%d%d",&M,&N,&K);

    for(i = M;i <= N;++i)
    {
        a = i;
        flag = 0;
        do
        {
            b = a%10;
            if(K == b)
            {
                flag = 1;
                break;
            }
            a /= 10;
        } while (a != 0);
        
        if(flag) continue;
        sum += i;
        sum = sum%1000000007;
    }

    printf("%d",sum);
    return 0;
}
