#include "stdio.h"
#define GPNCON (*(volatile unsigned long *)0x7F008830)
#define GPNDAT (*(volatile unsigned long *)0x7F008834)

#define INTMSK (*(volatile unsigned long *)0X4A000008)

#define GPKCON0     		(*((volatile unsigned long *)0x7F008800))
#define GPKDATA     		(*((volatile unsigned long *)0x7F008808))

#define GPFCON (*(volatile unsigned int *)0x7F0080A0)
#define GPFDAT (*(volatile unsigned int *)0x7F0080A4)
#define		PWMTIMER_BASE			(0x7F006000)
#define		TINT_CSTAT 	( *((volatile unsigned long *)(PWMTIMER_BASE+0x44)) )
#define		TCON      	( *((volatile unsigned long *)(PWMTIMER_BASE+0x08)) )
void timer_init(unsigned long utimer,unsigned long uprescaler,unsigned long udivider,unsigned long utcntb,unsigned long utcmpb);
int t = 0;//t控制蜂鸣器是否响
int main()
{
	timer_init(0,65,4,31250,0);
	int dat;
	//unsigned long temp0;
	//unsigned long utimer=0;
	int num = 5;//设置需要达到的值
	int k = 0;//设置计数值
	GPNCON = 0;//按键使能
	//int flag = 0;
	TCON &= ~(1<<0);//关闭定时器0
	//int temp;
	int i; 
	//int j;
	while (1)
	{
		dat = GPNDAT;//获取按键寄存器的值
		if(!(dat & (1<<0)))//如果k1被按下
		{
			i = 0;
			while(i<20000000)
			{
				i++;
			}//延时一段时间
			if(!(dat & (1<<0)))//再次检测k1是否被按下,若按下k++
				k++;
			while(!(dat & (1<<0) ))  //get k++
			{
				dat = GPNDAT;
			}

			
		}
		else if(!(dat & (1<<1)))//检测k2是否被按下
		{
			num =5;

		}
		else if(!(dat & (1<<2)))//检测k3是否被按下
		{
			num =10;

		}
		else if(!(dat & (1<<3)))//检测k4是否被按下
		{
			k=0;//使k清0
			TCON &= ~(1<<0); //关闭定时器
			//TCON &= ~(1<<3); //zidong
			GPKDATA = 0xff;  //关闭灯
			//GPKDATA = 0xef;  //开灯1
			GPFDAT &= ~(1<<14); //关闭蜂鸣器
			
		}
		if(k >= num)//按键次数到达num后，将k置为0，t置为1
		{
			k = 0;
			t = 1;//代表此时蜂鸣器应该闪烁
			GPKDATA = 0;
			//GPKDATA |= (1<<14);
			GPFDAT |= (1<<14);
			timer_init(0,65,4,31250,0);//重新初始化定时器，并打开
		}
		else if(k == 1)
		{
			t = 0;//此时蜂鸣器停止
		}
	}
	
	return 0;
}
