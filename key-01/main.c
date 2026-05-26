#include <STC8H.h>
#include <intrins.h>
bit key_flag=0;
#define KEY1 P32
#define KEY2 P33

unsigned char i;//控制灯移位变量
void setup()//外部中断0和io口初始化变量
{
	EA=1;//打开总中断
	EX0=1;//外部中断0中断允许位，它打开等会才能进入中断服务子函数
	EX1=1;//外部中断1中断允许位，它打开等会才能进入中断服务子函数
	IE0=0;//外部中断0中断请求标志位，它等于1进入中断服务子函数
	IE1=0;//外部中断1中断请求标志位，它等于1进入中断服务子函数
	IT0=1;//外部中断0下降沿触发，就是按键按下才触发，抬起不触发
	IT1=1;//外部中断1下降沿触发，就是按键按下才触发，抬起不触发
	P0M1 &=0xf8;//设置P0口低三位为准双向口模式
	P0M0 &=0xf8;//设置P0口低三位为准双向口模式
	P0 &=0xff;//先把灯都灭了；
}
void INT0_IE0() interrupt 0//外部中断0的中断服务子函数
{
	key_flag=1;//自定义按键一标志位，按键按下置1
	while(!KEY1);//等待按键抬起
}
void INT0_IE1() interrupt 2//外部中断1的中断服务子函数
{
	key_flag=1;//自定义按键一标志位，按键按下置1
	while(!KEY2);//等待按键抬起
}
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