#include "sound_to_direction.h"
#include "sound_to_direction_need.h"
#include "contact.h"

double thlta=0;                                //�����õ���Դ����ڻ�������ǰ���ĽǶ�
int angle_decision=0;                          //�����Ƿ��ڽǶ�ģʽ�»�������ת
double time0_1=0,time0_2=0,time0_3=0;          //ת��Ϊ�������¼�
extern int time1,time2,time3;  
extern int time_s,time1_1,time2_1,time3_1;  
extern int sequence[],caculate_once;

void area_decision(void)
{
	 if(sequence[0]==number_f)               //ǰ���������Ƚ��յ��ź�
	 {
			if(sequence[1]==number_l)
			{
				 angle_decision=1;
			}
			if(sequence[1]==number_r)
			{
				 angle_decision=2;
			}
	  }
		if(sequence[0]==number_l)              //�󷽴������Ƚ��յ��ź�
		{
			 if(sequence[1]==number_f)
			 {
					angle_decision=3; 
			 }
			 if(sequence[1]==number_b)
			 {
					angle_decision=4;
			 }
		}
		if(sequence[0]==number_r)              //�ҷ��������Ƚ��յ��ź�
		{
			 if(sequence[1]==number_f)
			 {
				  angle_decision=5;
			 }
			 if(sequence[1]==number_b)
			 {
					angle_decision=6;
			 }
		}
		if(sequence[0]==number_b)              //�󷽴������Ƚ��յ��ź�
		{
			 if(sequence[1]==number_l)
			 {
					angle_decision=7;	  
			 }			
			 if(sequence[1]==number_r)
			 {
					angle_decision=8;	
			 }
		}
}

void area_decision_angle(void)
{
	 if(caculate_once)
	 {
      int thlta=angle_caculate();
			caculate_once=1;   
	 }
	 if(sequence[0]==number_f)                  //ǰ���������Ƚ��յ��ź�
	 {
			if(sequence[1]==number_l)
			{
				if(thlta>15)                          //�������ڻ�������תʱ����������ǰ��ʮ���ʱ�����˲�������ת
			  {
					 angle_decision=1;
				}
				else
				{
					 angle_decision=0;
				}
			}
			if(sequence[1]==number_r)
			{
				 if(thlta>15)
				 {
						angle_decision=2;
				 }
				 else
				 {
						angle_decision=0;
				 }
			}
		}
		if(sequence[0]==number_l)                //�󷽴������Ƚ��յ��ź�
		{
			 if(sequence[1]==number_f)
			 {
					angle_decision=3; 
			 }
			 if(sequence[1]==number_b)
			 {
					angle_decision=4;
			 }
		}
		if(sequence[0]==number_r)                //�ҷ��������Ƚ��յ��ź�
		{
			 if(sequence[1]==number_f)
			 {
					angle_decision=5;
			 }
			 if(sequence[1]==number_b)
			 {
					angle_decision=6;
			 }
		}
		if(sequence[0]==number_b)                //�󷽴������Ƚ��յ��ź�
		{
			 if(sequence[1]==number_l)
			 {
					angle_decision=7;	  
			 }
			 if(sequence[1]==number_r)
			 {
					angle_decision=8;	
			 }
		}
}

int angle_caculate(void)                      //�Ƕȼ��㺯��
{
	double angle=0;
	time0_1=time1/need_derivation;              //������ʱ��ת������
	time0_2=time2/need_derivation;
	time0_3=time3/need_derivation;
	
	angle=atan(fabs(time0_1-time0_2)/time0_3);  //�ǶȽ��Ƽ��㹫ʽ
	angle=(int)(angle*180/pi);                  //���Ƕ��Ի�����ʽת��Ϊ�Ƕ���ʽ
	
	return angle;
}

void sound_to_direction_area(void)         //������������ת���������ܽ������ж�����Ȼ�������ת
{
	 area_decision();
	 switch(angle_decision)                   //���Խ׶�û�����̷������ݣ���Ҫ���õı�־λ���������ã�����ǶȻ���Ҫ����һ��
	 {
			case 1:set_stop();break;   
			case 2:set_stop();break;
			case 3:Set_CarTurn(8500,11500,67);break;
			case 4:Set_CarTurn(8500,11500,112);break;
			case 5:Set_CarTurn(11500,8500,67);break;
			case 6:Set_CarTurn(11500,8500,112);break;
			case 7:Set_CarTurn(8500,11500,157);break;
			case 8:Set_CarTurn(11500,8500,157);break;
			case 0:set_stop();break;
	 }

}

void sound_to_direction_angle(void)           //�������ܽ����ǰ��ռ���ǶȽ�����ת
{
	  area_decision_angle();
		switch(angle_decision)                   //���Խ׶�û�����̷������ݣ���Ҫ���õı�־λ����������
		{
			 case 1:Set_CarTurn(8500,11500,(int)thlta);break;
			 case 2:Set_CarTurn(11500,8500,(int)thlta);break;
			 case 3:Set_CarTurn(8500,11500,(90-(int)thlta));break;
			 case 4:Set_CarTurn(8500,11500,(90+(int)thlta));break;
			 case 5:Set_CarTurn(11500,8500,(90-(int)thlta));break;
			 case 6:Set_CarTurn(11500,8500,(90+(int)thlta));break;
			 case 7:Set_CarTurn(8500,11500,(180-(int)thlta));break;
			 case 8:Set_CarTurn(11500,8500,(180-(int)thlta));break;
			 case 0:Set_carStop();break;
		}
	} 
