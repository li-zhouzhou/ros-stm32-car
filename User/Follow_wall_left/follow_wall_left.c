#include "follow_wall_left.h"

int distance_left=0,distance_front=0;  //����ǰ�����������������Ծ���ֵ

int ultrasound_data_front(int);        //�з���ֵ�ĺ���ʹ��ǰ��Ҫ�ٴ�������

void follow_wall_left(void)
{
	distance_left=ultrasound_data_front(0);
	distance_front=ultrasound_data_front(2);
	if((distance_left<distance_max)&&distance_left>distance_min)
	{
		if(distance_front<distance_max)
			Set_carRight(1000);
		else
			Set_carFoward(1000);
	}
	else if(distance_left>=distance_max)
	{
		if(distance_front<distance_max)
			Set_carRight(1000);
		else
			Set_carFoward(1000);
	}
	else 
	{
		if(distance_front<distance_max)
			Set_carRight(1000);
		else
			Set_carFoward(1000);
	}
}
