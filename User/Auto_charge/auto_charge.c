#include "auto_charge.h"
#include "stdio.h"

extern bool Red_Left,Red_Front_Middle,Red_Front_Right,Red_Front_Left,Red_Right;   //�洢�������ź�
int check[3]={100,100,100};  //�������泬�������ݼ��
int checkup[3]={100,100,100};
int i=2;  //���������ݼ��������
int Flag_Ultra_charge=1;  //��繦���Ƿ�ֹͣ��־λ
int Ultra_charge=100; //�洢���泬�����������
int Red_flag_rr=1,Red_flag_ll=1,Red_flag_r=0,Red_flag_l=0,Red_flag_stop=1;  //�Զ��������еĸ�����־λ

int ultrasound_data_back(void);  //���泬�������ݺ����������ַ���ֵ�ú�����Ҫ����ǰ��������


void auto_charge(void)
{
	  if(Flag_Ultra_charge)  //����������ֹͣ����
		{
    	//	Ultra_charge=	ultrasound_data_back();
			
// 	    printf("%d\r\n",ultrasound_data_back());
			
			check[i]=Ultra_charge;
			i--;
			if(i==-1)
			{	
				i=2;
				checkup[1]=check[1];
				checkup[2]=check[2];
				checkup[0]=check[0];
 //       Flag_Ultra_charge=0;				
			}
			
		}
		
		if((checkup[0]<7)&&(checkup[1]<7)&&(checkup[2]<7)) //�����������ݾ�С��9mmʱ��������ֹͣ
		{
//			printf("tingzhi\r\n");
			Set_carStop();
			Red_flag_stop=0;       //������ֹͣ��־λ  
			Flag_Ultra_charge=0;
		}
		else
		{
			Red_flag_stop=1;
			Flag_Ultra_charge=1;			
		}
		
	  if(Red_flag_stop)  
		{

			if(Red_Right&&Red_flag_rr)    //���Ҳഫ�������յ��ź�ʱ����1��Ӧ��־λ
			{	
				Red_flag_r=1;
			}
			
			if(Red_Left&&Red_flag_ll)   //����ഫ�������յ��ź�ʱ����1��Ӧ��־λ
			{
				Red_flag_l=1;
			}
		
			if(Red_flag_r||Red_flag_l)   //��������źŽ���ʱ
			{
				 if(Red_flag_r&&Red_flag_l)     //�������������������źŽ��յ����
				 {
					  if(Red_Right) 
					  {
						   Red_flag_l=0;
					  }
					  else 
						Red_flag_r=0;		
				 }
			
				 if(Red_flag_r)    //�Ҳ���յ��źź���ת�����������������������ź�ʱִ��
				 {		
					  Set_carRight(1000);
					  if(Red_flag_r&&Red_Front_Middle&&Red_Front_Right&&Red_Front_Left)
					  {	
						   Red_flag_r=0;
						   Red_flag_rr=0;
						   Red_flag_ll=0;
						   Set_carBack(1000);
					  }
											
				 }
				 else	          //������ת���������������źŽ���ʱֱ��
				 {		
					  Set_carLeft(1000);
					  if(Red_flag_l&&Red_Front_Middle&&Red_Front_Left&&Red_Front_Right)
					  {
						   Red_flag_l=0;
						   Red_flag_rr=0;
						   Red_flag_ll=0;                         
						   Set_carBack(1000);
					  }		
				 }
			 }	
			 else if((!Red_flag_rr)&&(!Red_flag_ll))
			 {
					if(Red_Front_Left&&Red_Front_Middle&&Red_Front_Right)
					{
							Set_carBack(1000);
					}
					if((!Red_Front_Left)&&Red_Front_Middle&&(!Red_Front_Right))
					{
							Set_carBack(1000);
					}
					if((!Red_Front_Left)&&Red_Front_Middle&&Red_Front_Right)
					{						
							Set_carRight(1000);
					}
					if(Red_Front_Left&&Red_Front_Middle&&(!Red_Front_Right))
					{
							Set_carLeft(1000);
					}
			 }
			 else
			 {
				  Set_carFoward(1000);
				 
			 }

		 }		
		 else   
				 Set_carStop();		
}
