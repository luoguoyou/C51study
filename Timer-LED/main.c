#include <STC8H.h>
#include "intrins.h"


#define key2 P33    //key2 bit address


void Timer0_Init(void)		//1毫秒@11.0592MHz
{
	AUXR |= 0x80;			//set timer clock 1T mode
	TMOD &= 0xF0;			//set timer mode
	TL0 = 0xCD;				//set timer lower initial value
	TH0 = 0xD4;				//set timer high initial value
	TF0 = 0;				//clear TF0 flag
	TR0 = 1;				//start timer0 counting
    EA = 1;                 //open global interrupt
    ET0 = 1;              //open timer0 interrupt
}

void setup()//
{
    P0M0 = 0x00; P0M1 = 0x00; //set P0 as quasi-bidirectional mode

}
#define key1 P32  //key1 bit address
bit key1_last = 1, key1_now;
unsigned int key1_time = 0;
unsigned char key1_flag = 0; //0: no key action, 1: short press, 2: long press
void key_scan()
{
    key1_now = key1;
    if(key1_now == 0 && key1_last ==1)//key1 is starting to bepressed
    {
        key1_time = 0;
    }
    if(key1_now == 0)//key1 is pressing
    {
        key1_time ++;
        if(key1_time >= 1000)
        {
            if(key1_flag != 2) //if not already long pressed
            {
                key1_flag = 2;
            }
        }
    }
    if(key1_now == 1 && key1_last == 0)
    {
        if(key1_time < 1000)
        {
            key1_flag = 1;
        }
    }
    key1_last = key1_now;
}
void loop()
{

}

void timer0_isr(void) interrupt 1  //timer0 interrupt service routine
{

    

}

void main()
{
    setup();
    Timer0_Init();
    while(1)
    {
        loop();
    }
}