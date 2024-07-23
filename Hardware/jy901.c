#include	"jy901.h"

uint8_t g_RxState=0;

Jy901_Struct jy901_data = {0};


void Jy901_Process(Jy901_Struct* Jy901_Data_Str)
{
	static uint8_t 	rx_count=0;
	static uint16_t data_sum=0;
	switch(g_RxState)
	{
		case	RECEV_FH:
			if(g_RxData==0x55)
			{
				g_RxState=RECEV_FUNC;
			}
		break;
		case RECEV_FUNC:
		{
			switch(g_RxData)
			{
				case 0x51:g_RxState=RECEV_ACC;break;
				case 0x52:g_RxState=RECEV_ANG;break;
				case 0x53:g_RxState=RECEV_EUR;break;
				default:g_RxState = RECEV_FH;break;
			}break;
		}
		case RECEV_ACC:
		{
			data_sum+=g_RxData;
			Jy901_Data_Str->Acc_data.Acc_buf[rx_count++]=g_RxData;
			if(rx_count==9)
			{
				rx_count=0;
				g_RxState = DECODE_ACC;
			}
		}break;
		case RECEV_ANG:
		{
			data_sum+=g_RxData;
			Jy901_Data_Str->Ang_data.Ang_buf[rx_count++]=g_RxData;
			if(rx_count==9)
			{
				rx_count=0;
				g_RxState = DECODE_ANG;
			}
		}break;
		case RECEV_EUR:
		{
			data_sum+=g_RxData;
			Jy901_Data_Str->Eul_data.Eul_buf[rx_count++]=g_RxData;
			if(rx_count==9)
			{
				rx_count=0;
				g_RxState = DECODE_EUL;
			}
		}break;
		case DECODE_ACC:
		{
			Jy901_Data_Str->Acc_data.AccX= ((short)((short)Jy901_Data_Str->Acc_data.Acc_buf[1] << 8 | Jy901_Data_Str->Acc_data.Acc_buf[0])) / 32768.0f* 16.0f;
			Jy901_Data_Str->Acc_data.AccX= ((short)((short)Jy901_Data_Str->Acc_data.Acc_buf[3] << 8 | Jy901_Data_Str->Acc_data.Acc_buf[2])) / 32768.0f* 16.0f;
			Jy901_Data_Str->Acc_data.AccX= ((short)((short)Jy901_Data_Str->Acc_data.Acc_buf[5] << 8 | Jy901_Data_Str->Acc_data.Acc_buf[4])) / 32768.0f* 16.0f;
			g_RxState=RECEV_FH;
		}
		case DECODE_ANG:
		{
			Jy901_Data_Str->Ang_data.AngX= ((short)((short)Jy901_Data_Str->Ang_data.Ang_buf[1] << 8 | Jy901_Data_Str->Ang_data.Ang_buf[0])) / 32768.0f* 2000.0f;
			Jy901_Data_Str->Ang_data.AngY= ((short)((short)Jy901_Data_Str->Ang_data.Ang_buf[3] << 8 | Jy901_Data_Str->Ang_data.Ang_buf[2])) / 32768.0f* 2000.0f;
			Jy901_Data_Str->Ang_data.AngZ= ((short)((short)Jy901_Data_Str->Ang_data.Ang_buf[5] << 8 | Jy901_Data_Str->Ang_data.Ang_buf[4])) / 32768.0f* 2000.0f;
			g_RxState=RECEV_FH;
		}		
		case DECODE_EUL:
		{

			Jy901_Data_Str->Eul_data.Roll= ((short)((short)Jy901_Data_Str->Eul_data.Eul_buf[1] << 8 | Jy901_Data_Str->Eul_data.Eul_buf[0])) / 32768.0f* 180.0f;
			Jy901_Data_Str->Eul_data.Pitch= ((short)((short)Jy901_Data_Str->Eul_data.Eul_buf[3] << 8 | Jy901_Data_Str->Eul_data.Eul_buf[2])) / 32768.0f* 180.0f;
			Jy901_Data_Str->Eul_data.Yaw= ((short)((short)Jy901_Data_Str->Eul_data.Eul_buf[5] << 8 | Jy901_Data_Str->Eul_data.Eul_buf[4])) / 32768.0f* 180.0f;
			g_RxState=RECEV_FH;
		}		
		default :g_RxState = RECEV_FH;break;
	}
}










