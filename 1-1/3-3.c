#include<stdio.h>
#include<math.h>

int isPrime(int src)
{
    double sq = sqrt(src);
        if (src < 2) {
            return 0;
        }
        if (src == 2 || src == 3) {
            return 1;
        }
        if (src % 2 == 0) {// 先判断是否为偶数，若偶数就直接结束程序
            return 0;
        }
        for (int i = 3; i <= sq; i+=2) {
            if (src % i == 0) {
                return 0;
            }
        }
        return 1;
}

int main()
{
    
    int a,b;
    int s,n,i;
    printf("请输入一个数\n");
    scanf("%d",&n);
    for (i = 0;i < n;++i){
        scanf("%d",&a);
        if (isPrime(a)) {
        printf("N\n");
        } 
        else
        {
            for (int i = 2; i < a; i++) {
                if (a%i == 0) {
                    b = a % i;
                    if(b != 0) continue;
                    s = a / i;
                    //判断两个乘数是否素数
                    if (isPrime(i) && isPrime(s)&& i != s) {
                        printf("Y\n",i,s);
                        break;
                    }else {
                        printf("N\n",i,s);
                        break;
                    }
                }
            }
        }
    }
    
    
    return 0;
}