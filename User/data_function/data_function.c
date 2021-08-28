#include "data_function.h"
#include "stm32f10x.h"
#include "UltrasonicWave.h"
#include "stdbool.h"

//�������ݺ����ڱ���
extern float Sum_L_Motor,Sum_R_Motor,Milemeter_L_Motor,Milemeter_R_Motor;
extern int Flag_milemeter;

//�������ݺ������������������룺10-110CM ��5v����
int Ultra_dis[6]={0};  //�洢ǰ��6�������ľ���
int Ulta_number=0;
int ultra_distance=0;  //�洢���泬����������õľ���ֵ

float encoder_data_left(void)
{
	if(Flag_milemeter==1)
	{
		Flag_milemeter=0;			
		Sum_L_Motor+=Milemeter_L_Motor;   //��������Ҫ��һ�����Ǵ���
  }
	return Sum_L_Motor;
}

float encoder_data_right(void)
{
	if(Flag_milemeter==1)
	{
		Flag_milemeter=0;
		Sum_R_Motor+=Milemeter_R_Motor;		
  }
	return Sum_R_Motor;
}

// void ultrasound_data_front(isOnoff)
//{
//	if(isOnoff==true)
//	{
//		int k=0;
//		for(k=0;k<6;k++)
//		{
//			Ultra_dis[k]=	UltrasonicWave_StartMeasure(Ulta_number);
//			Ulta_number++;
//		}
//		k=0;
//		Ulta_number=0;
//		//return Ultra_dis;
//		//return Ultra_dis[re_number];
//	}

//}

int ultrasound_data_back()
{

	ultra_distance=UltrasonicWave_Measure_back();
	return ultra_distance;
}



