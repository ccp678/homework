#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
int main()
{
    int N, n, A;
    int i, j;
    char s[100];
    int b, sum = 0;
    printf("请输入正整数\n");
    scanf("%d",&N);
    printf("输出\n");
    for (i  = 0;i <= N;++i)
    {
        sprintf(s, "%d", i);//转换成字符串号计算数字的长度
        n = strlen(s);
        A = i;
        sum = 0;
        do 
        {
          b = A%10;
          A /= 10;
         sum += pow((double)b,(double)n);
         n--;
        } while (A != 0);
        if(sum == i)
        {
            printf("%d\t",i);
        }
    }
    printf("\n");
    return 0;
}