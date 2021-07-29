#define GPKCON0 (*(volatile unsigned long *)0x7F008800)
#define GPKDAT (*(volatile unsigned long *)0x7F008808)

#define GPNCON (*(volatile unsigned long *)0x7F008830)
#define GPNDAT (*(volatile unsigned long *)0x7F008834)


void main(void)
{
	int dat = 0;

	// 配置GPK4-7为输出功能
	GPKCON0 = 0x11110000;	
	
	// 所有LED熄灭
	GPKDAT = 0x000000f0;
	
	// 配置GPN为输入功能
	GPNCON = 0;
	
	// 轮询的方式查询按键事件
	while(1)
	{
		dat = GPNDAT;

		if(dat & (1<<0)){				// KEY1被按下，则LED1,2亮，否则LED1,2灭
			GPKDAT |= 1<<4;
			GPKDAT |= 1<<5;
		}
		else{
			GPKDAT &= ~(1<<4);
			GPKDAT &= ~(1<<5);
		}
		if(dat & (1<<1)){				// KEY2被按下，则LED3,4亮，否则LED3,4灭
			GPKDAT |= (1<<6);
			GPKDAT |= 1<<7;
		}
		else{
			GPKDAT &= ~(1<<6);
			GPKDAT &= ~(1<<7);
		}
		if(dat & (1<<2)){				// KEY3被按下，则LED1,3亮，否则LED1,3灭
			GPKDAT |= (1<<6);
			GPKDAT |= 1<<4;
		}
		else{
			GPKDAT &= ~(1<<6);
			GPKDAT &= ~(1<<4);
		}
		if(dat & (1<<3)){				// KEY4被按下，则LED2,4亮，否则LED2,4灭
			GPKDAT |= 1<<7;
			GPKDAT |= 1<<5;
		}
		else{
			GPKDAT &= ~(1<<7);
			GPKDAT &= ~(1<<5);
		}
	}
}

