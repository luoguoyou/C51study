#include <STC8H.h>
#include <intrins.h>
bit key_flag=0;
#define KEY1 P32
#define KEY2 P33
void Delay20ms()  //@11.0592MHz
{
 unsigned char i, j, k;

 _nop_();
 _nop_();
 i = 1;
 j = 216;
 k = 35;
 do
 {
  do
  {
   while (--k);
  } while (--j);
 } while (--i);
}
unsigned char i;
void setup()
{
    EA = 1;
    EX0 =1;
    EX1 =1;
    IE0 =0;
    IE1 =0;
    IT0 =1;
    IT1 =1;
    P0M0 &= 0xf8; 
    P0M1 &= 0xf8; 
    P0 &=0XFF;
}
void key_see_about()//按键查询，看按键1或二是否按下
{
 	if(KEY1==0)//如果按键1按下
 	{
  		Delay20ms();//延时20ms按键1消抖环节
  		if(KEY1==0)//按键1还是低电平则标志为置1，以上为按键1消抖环节
  		{
  	 		key_flag=1;//按键标志位置1
  		}
 	} 
 	if(KEY2==0)//如果按键2按下
 	{
  		Delay20ms();//延时20ms
  		if(KEY2==0)//以上为按键2消抖环节
  		{
   			key_flag=1;//标志位置1
  		}
 	}
}
// void Timer0_ISR(void) interrupt 1
// {
//     key_flag =1;
//     while(!KEY1);
// }

void LED_turn()//led流转函数
{
	if(key_flag)//确认按键按下才进入亮灯
	{
		key_flag=0;//自定义按键一标志位清零
		P0=~(1<<i);//按键按下一次亮一种灯
		i++;//移位量比前一次多一
		if(i>2)//灯循环一次后i清零
			i=0;
	}
}
void loop()
{
    LED_turn();
}
void main()
{
    setup();
    while(1)
    {
        loop();
    }
}