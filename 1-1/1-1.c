#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    char s[10000];
    int i;
    printf("请输入字符串\n");
    gets(s);
    for (i = 0;i < strlen(s);++i)
    {
        s[i] = 187 - s[i];
    }
    printf("结果为%s\n",s);
    return 0;
}