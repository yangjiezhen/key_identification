#ifndef __KEY_H__
#define __KEY_H__

#define   KEY_HOLD				0x01	//位掩码
#define   KEY_DOWN				0x02	//位掩码
#define   KEY_UP					0x04	//位掩码
#define   KEY_SINGLE			0X08	//位掩码
#define   KEY_DOUBLE			0X10	//位掩码
#define   KEY_LONG				0x20	//位掩码
#define   KEY_REPEAT			0x40	//位掩码

#define   KEY_1   				0
#define   KEY_2   				1
#define   KEY_3   				2
#define   KEY_4   				3

#define 	KEY_COUNT				4

typedef unsigned char uint8_t;
extern uint8_t Key_Flag[KEY_COUNT];//REPEAT LONG DOUBLE SINGLE UP DOWN HOLD
															//0     1       1     1      1    1   1    1      
void key_tick(void);
uint8_t Key_Check(uint8_t n ,uint8_t	Flag);

#endif
