#include<stdio.h>
#include<stdlib.h>
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))
//如果有一个区间和其他区间交叉，那么选择区间左边较小的，右边较大的。
//将所有的区间从小到大按照第一个排列，之后再一个一个判断区间是否包含另一个区间
void sort(int a[][2],int N)
{
    int i, j;
    int v0,v1;
    //排序主体
    for(i = 1; i <= N - 1; i ++)
    {
        for(j = i+1; j <= N; j ++)
        {
            if(a[i][0] > a[j][0])//如前面的比后面的大，则交换。
            {
                v0 = a[i][0];
                v1 = a[i][1];

                a[i][0] = a[j][0];
                a[i][1] = a[j][1];


                a[j][0] = v0;
                a[j][1] = v1;
            }
        }
    }   

}

int main()
{
    int N,K;
    int a[10001];
    int q[101][2];//={0},J[100]={0},J_[10001]={0};
    int i,j;
    printf("输入\n");
    scanf("%d",&N);
    for(i = 1;i <= N;++i)
    {
        scanf("%d",&a[i]);
    }
    //读入q,J
    scanf("%d",&K);
    for (i = 1;i <= K;++i)
    {
        scanf("%d%d",&q[i][0],&q[i][1]);
    }
    sort(q,K); //对数组从1~K的数据进行排序
    //for(i = 0;i <= K;++i)
    //printf("%d ",q[i]);
    //将对应的区间的右边界选择出来
    //开始合并区间
    int m[101][2]; //存储新区间
    int n = 1;
    m[1][0] = q[1][0];
    m[1][1] = q[1][1];

    for (i = 2;i < K;++i )
    {
        if(q[i][0] > m[n][1]) //新的左区间比上一个区间的右边界大，说明是一个新的范围
        {
            n++;
            m[n][0] = q[i][0];
            m[n][1] = q[i][1];
        }
        else
        {
            //m[n][0] = min(m[n][0],q[i][0]);
            m[n][1] = max(m[n][1],q[i][1]);
        }
    }

    printf("结果\n");
    for ( i = 1; i < m[1][0]; i++)
    {
        printf("%d ",a[i]);
    }
    
    for(i = 1;i < n;++i)
    {
        //printf("合并结果\n");
        //printf("%d %d\n",m[i][0],m[i][1]);
        for(j = m[i][1];j <= m[i+1][0];++j)
        {
            printf("%d ",a[j]);
        }
    }
    for(i = m[n][1]+1;i <= N;++i )
    {
        printf("%d ",a[i]);
    }
printf("\nm的结果\n");
    for ( i = 1; i <= n; i++)
    {
        printf("\n%d %d",m[i][0],m[i][1]);
    }
    
    return 0;
}