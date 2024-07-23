#ifndef		__JY901_H_
#define		__JY901_H_

#include	"main.h"
#include	"usart.h"



typedef	enum
{
	RECEV_FH=0x00,
	RECEV_FUNC,
	RECEV_ACC,
	RECEV_ANG,
	RECEV_EUR,
	DECODE_ACC,
	DECODE_ANG,
	DECODE_EUL
}Receive_State;

typedef	struct
{
	float	AccX;
	float	AccY;
	float	AccZ;
	uint8_t	Acc_buf[9];
}AccVel_Struct;

typedef	struct
{
	float	AngX;
	float	AngY;
	float	AngZ;
	uint8_t	Ang_buf[9];
}AngVel_Struct;

typedef	struct
{
	float	Roll;
	float	Pitch;
	float	Yaw;
	uint8_t	Eul_buf[9];
}EulAng_Struct;

typedef	struct
{
	AccVel_Struct Acc_data;
	AngVel_Struct Ang_data;
	EulAng_Struct	Eul_data;	
}Jy901_Struct;

extern 	Jy901_Struct jy901_data;


void Jy901_Process(Jy901_Struct* Jy901_Data_Str);

#endif



