#include <REGX52.H>
#include "led.h"
#include "Timer0.h"
#include "Key.h"
#include <INTRINS.H>
#include "LCD1602.h"

uint8_t num1;
uint8_t num2;

void main()
{
	Timer0_Init();
	LCD_Init();
	LCD_ShowString(1,1,"num1:");
	LCD_ShowString(2,1,"num2:");		
	
	while(1)
	{	
//		示例1
//		if(Key_Check(KEY_HOLD))
//		{
//				num1=1;
//		}
//		else
//		{ 
//				num1=0;
//		}
//		示例2
//		if(Key_Check(KEY_1,KEY_REPEAT))
//		{
//			P2_0=~P2_0;
//		}
//		if(Key_Check(KEY_2,KEY_SINGLE))
//		{
//			num2++;
//		}

	
		
		LCD_ShowNum(1,6,num1,5);
		LCD_ShowNum(2,6,num2,5);
	}
}		
void Timer0_Routine() interrupt 1
{
		TL0 = 0x18;		//设置定时初值
		TH0 = 0xFC;		//设置定时初值
		key_tick();
	  
}



















