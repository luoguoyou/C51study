#include <STC8H.h>
#include <intrins.h>
void Delay500ms()		//@11.0592MHz延时函数
{
	unsigned char i, j, k;

	_nop_();//用到它就要用到这个头文件<intrins.h>
	_nop_();
	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void setup()
{
	//P5M0 &= ~0x10; P5M1 &= ~0x10; 
    P0M0 &= 0xf8; P0M1 &= 0xf8; 

}

void loop()
{
    P00 = 0;
    Delay500ms();
    P00 = 1;
    Delay500ms();

    P01 = 0;
    Delay500ms();
    
    P01 = 1;
    Delay500ms();
    P02 = 0;
    Delay500ms();
    P02 = 1;
    Delay500ms();
}
void main()
{
    setup();
    while(1)
    {
        loop();
    }
}