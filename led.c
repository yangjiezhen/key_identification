#include <REGX52.H>
#include "Key.h"
unsigned int i;unsigned int count,led_mode;
unsigned char flag=0;
void led_on()
{
	P2=0x00;
}
void led_off()
{
  P2=0xFF;
}
void led_flash()
{

	P2=~P2;
}

void led_tick()
{
//	unsigned char keynum;
//	keynum=key_getnum();
	if(led_mode==0)
	{
		led_off();
	}

	else if(led_mode==1)
	{
		i++;
		i%=1000;
		if(i<500)
		{
			led_on();
		}
		else
		{
			led_off();
	  }

	}	
	else if(led_mode==2)
	{
				i++;
		i%=100;
		if(i<50)
		{
			led_on();
		}
		else
		{
			led_off();
		}

}
}
void led_setmode(unsigned int mode)
{
	led_mode=mode;
}