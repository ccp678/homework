#include<stdio.h>
#include<stdlib.h>
int main()
{
    char dbyte[] = {0x12,0x34,0x56,0x78,0x9a};
    int i;
    __asm
    {
        mov ecx,5
        mov esi,0
        again:
        mov bl,dbyte[esi]
        rol bl,1
        rol bl,1
        rol bl,1
        rol bl,1
        mov dbyte[esi],bl
        add si,1
        loop again
    }
    for (i = 0;i < 5;++i)
    {
        printf("%x ",dbyte[i])
    }
    return 0;
}