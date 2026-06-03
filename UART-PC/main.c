#include <STC8H.h>
#include "intrins.h"
char s_data ='x';
bit uart_flag = 0; // 串口接收完成标志
// LED 引脚定义 
sbit LED_R = P0^0; // 红灯
sbit LED_G = P0^1; // 绿灯
sbit LED_B = P0^2; // 蓝灯
unsigned char i;//控制灯移位变量
void Uart1_Init(void)	//9600bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器时钟1T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xE0;			//设置定时初始值
	TH1 = 0xFE;			//设置定时初始值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
    ES=1;//打开串口1中断允许控制位
	EA=1; //打开总中断
}
void setup()
 {
  	P0M1 &=0xF8;//（P0M1=0x00）//P0低三位设置为准双向口模式
    P0M0 &=0XF8;//（P0M0=0x00）//P0低三位设置为准双向口模式

    LED_R = 1;
    LED_G = 1;
    LED_B = 1;
 }
 void Uart1_SendByte(unsigned char dat)
{
    SBUF = dat;
    while (!TI);        // 等待发送完成
    TI = 0;             // 清除发送中断标志
}

void Uart1_ISR(void) interrupt 4
{
    if (RI)
    {
        s_data = SBUF;  // 读取接收缓冲区
        RI = 0;         // 清除接收中断标志
        uart_flag = 1;  // 置位接收标志，通知主循环处理
    }
}
void Process_Command(char cmd)
{
    switch (cmd)
    {
        case 'B':       
            LED_R = 0;  
            LED_G = 1;
            LED_B = 1;
            Uart1_SendByte('B'); // 反馈
            break;
        case 'b':
            LED_R = 1;  
            LED_G = 1;
            LED_B = 1;
            Uart1_SendByte('b'); // 反馈
            break;
            
        case 'R':       
            LED_R = 1;
            LED_G = 0;
            LED_B = 1;
            Uart1_SendByte('R');
            break;
        case 'r':
            LED_R = 1;
            LED_G = 1;
            LED_B = 1;
            Uart1_SendByte('r');
            break;
            
        case 'G':       
            LED_R = 1;
            LED_G = 1;
            LED_B = 0;
            Uart1_SendByte('G');
            break;
        
        case 'g':
            LED_R = 1;
            LED_G = 1;
            LED_B = 1;
            Uart1_SendByte('g');
            break;
            
        case 'A':       // 所有灯亮
            LED_R = 0;
            LED_G = 0;
            LED_B = 0;
            Uart1_SendByte('A');
            break;
        case 'a':
            LED_R = 1;
            LED_G = 1;
            LED_B = 1;
            Uart1_SendByte('a');
            break;
            
        case 'L':       
            P0=~(1<<i);//按键按下一次亮一种灯
            i++;//移位量比前一次多一
            if(i>2)//灯循环一次后i清零
			i=0;
            Uart1_SendByte('L');
            break;

            
        default:        // 未知指令，原样返回
            Uart1_SendByte(cmd);
            break;
    }
}

void main(void)
{
    setup();    // 初始化
    Uart1_Init();   // 初始化串口
    
    while (1)
    {
        if (uart_flag)      // 如果收到数据
        {
            uart_flag = 0;  // 清除标志
            Process_Command(s_data); // 处理指令
        }
    }
}