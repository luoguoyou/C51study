#include <STC8H.h>
#include "intrins.h"

unsigned char i;//控制灯移位变量
unsigned char count = 0;
void Timer0_Init(void)		//50毫秒@11.0592MHz
{
	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0x00;				//设置定时初始值
	TH0 = 0x4C;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
    EA = 1;                 //打开总中断
    ET0 = 1;              //打开定时器0中断 
}



void initialize()
{
    P0M1 &= 0xf8;
    P0M0 &= 0xf8;
}

// void LED()
// {
//     if(TF0)
//     {
//    TF0 = 0;
//    P0=~(1<<i);//按键按下一次亮一种灯
// 		i++;//移位量比前一次多一
// 		if(i>2)//灯循环一次后i清零
// 			i=0;
//     }

// }

void Timer0_isr() interrupt 1
{
    TH0 = 0x4C;
    TL0 = 0x00;
    count++;
    if(count == 10)
    {
    count = 0;
    P0=~(1<<i);//按键按下一次亮一种灯
		i++;//移位量比前一次多一
		if(i>2)//灯循环一次后i清零
		i=0;
    }
    
}

void main()
{
    initialize();
    Timer0_Init();
    while(1)
    {
        // LED();
    }
}