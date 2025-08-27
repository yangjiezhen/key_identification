#include <REGX52.H>
#include "Key.h"
#define 	KEY_PRESSED 		1
#define 	KEY_UNPRESSED 	0

#define   KEY_TIME_DOUBLE 200		//双击阈值
#define   KEY_TIME_LONG		2000	//长按阈值
#define   KEY_TIME_REPEAT	100	//重复阈值

uint8_t Key_Flag[KEY_COUNT];

uint8_t Key_GetState(uint8_t n)//检测按键实际状态，在Tick函数里执行进行消抖
{
	if(n==KEY_1)
	{
		if(P3_1==0)
		{
			return KEY_PRESSED;
		}
		return KEY_UNPRESSED;	
	}
	if(n==KEY_2)
	{
		if(P3_0==0)
		{
			return KEY_PRESSED;
		}
		return KEY_UNPRESSED;	
	}
	if(n==KEY_3)
	{
		if(P3_2==0)
		{
			return KEY_PRESSED;
		}
		return KEY_UNPRESSED;	
	}
	if(n==KEY_4)
	{
		if(P3_3==0)
		{
			return KEY_PRESSED;
		}
		return KEY_UNPRESSED;	
	}
}


void key_tick()
{	
	static unsigned char count1,i;//遍历四个按键检测;
	static unsigned char CurrState[KEY_COUNT]; 
	static unsigned char PrevState[KEY_COUNT],S[KEY_COUNT],Time[KEY_COUNT];
		
	//函数每次都从头开始执行，用静态变量保存上一次的状态，让函数下一次从上一次结束的地方开始执行
	//通过静态变量跟踪状态 (s变量)，实现了类似 "断点续传" 的效果。
	for(i=0;i<KEY_COUNT;i++)
	{	
		
		if(Time[i]>0)
		{
			Time[i]--;
		}
	}
		count1++;
	if (count1 >= 20)
	{
		
		count1 = 0;
		P2_3=~P2_3;
		for (i = 0; i < KEY_COUNT; i ++)
		{
			PrevState[i] = CurrState[i];
			CurrState[i] = Key_GetState(i);
			
			if (CurrState[i] == KEY_PRESSED)
			{
				Key_Flag[i] |= KEY_HOLD;
			}
			else
			{
				Key_Flag[i] &= ~KEY_HOLD;
			}
			
			if (CurrState[i] == KEY_PRESSED && PrevState[i] == KEY_UNPRESSED)
			{
				Key_Flag[i] |= KEY_DOWN;
			}
			
			if (CurrState[i] == KEY_UNPRESSED && PrevState[i] == KEY_PRESSED)
			{
				Key_Flag[i] |= KEY_UP;
			}
			
			if (S[i] == 0)
			{
				if (CurrState[i] == KEY_PRESSED)
				{
					Time[i] = KEY_TIME_LONG;
					S[i] = 1;
				}
			}
			else if (S[i] == 1)
			{
				if (CurrState[i] == KEY_UNPRESSED)
				{
					Time[i] = KEY_TIME_DOUBLE;
					S[i] = 2;
				}
				else if (Time[i] == 0)
				{
					Time[i] = KEY_TIME_REPEAT;
					Key_Flag[i] |= KEY_LONG;
					S[i] = 4;
				}
			}
			else if (S[i] == 2)
			{
				if (CurrState[i] == KEY_PRESSED)
				{
					Key_Flag[i] |= KEY_DOUBLE;
					S[i] = 3;
				}
				else if (Time[i] == 0)
				{
					Key_Flag[i] |= KEY_SINGLE;
					S[i] = 0;
				}
			}
			else if (S[i] == 3)
			{
				if (CurrState[i] == KEY_UNPRESSED)
				{
					S[i] = 0;
				}
			}
			else if (S[i] == 4)
			{
				if (CurrState[i] == KEY_UNPRESSED)
				{
					S[i] = 0;
				}
				else if (Time[i] == 0)
				{
					Time[i] = KEY_TIME_REPEAT;
					Key_Flag[i] |= KEY_REPEAT;
					S[i] = 4;
				}
			}
		}
	}
}
//  a  |= 位掩码，将对应位置1  ： a &=~位掩码，将对应位置0
uint8_t Key_Check(uint8_t n ,uint8_t	Flag) //Flag是位掩码，检测KeyFlag某一位的值，用于检测对应动作是否实现
{                                
	if(Key_Flag[n]	&	Flag) //变量与上位掩码，标志位为1时，计算结果为位掩码本身,非0即进入if语句
	{
		if(Flag!=KEY_HOLD)
			{	                          //如果不是keyhold，则读后把对应某一位清零
			Key_Flag[n] &=	~Flag;
			}   
		return 1;
	}
	return 0;
}






























