/**********************************************************************************
 * �ļ���  : UltrasonicWave.c
 * ����    �����������ģ�飬UltrasonicWave_Configuration��������
             ��ʼ������ģ�飬UltrasonicWave_StartMeasure��������
			 ������࣬������õ�����ͨ������1��ӡ����         
 * ʵ��ƽ̨��Ұ��STM32������
 * Ӳ�����ӣ�------------------
 *          |      - TRIG      |
 *          |      - ECHO      |
 *           ------------------
 * ��汾  ��ST3.5.0
 *
*********************************************************************************/
#include "UltrasonicWave.h"
#include "stm32f10x.h"
#include "stdio.h"
#include "delay.h"


u16 time6_aa = 0,length=1300;
u8 flag_0 = 0,flag_1 = 0,flag_2 = 0,flag_3 = 0,flag_4=0,flag_5=0,flag_back_ultra=0;


unsigned short int UltrasonicWave_Distance;      //������ľ���    

/*
 * ��������DelayTime_us
 * ����  ��1us��ʱ����
 * ����  ��Time   	��ʱ��ʱ�� US
 * ���  ����	
 */
void DelayTime_us(int Time)    
{
   unsigned char i;
   for ( ; Time>0; Time--)
     for ( i = 0; i < 72; i++ );
}

/*
 * ��������UltrasonicWave_Configuration
 * ����  ��������ģ��ĳ�ʼ��
 * ����  ����
 * ���  ����	
 */

void UltrasonicWave_Configuration(void) //��Ҫ7���շ����ţ�����һ����ǰ������ҹ�6��
{
  GPIO_InitTypeDef GPIO_InitStructure;	
       
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	
	//�����Զ����ֹͣ�ĳ��� ,Ҳ��������ʹ��
	/************************************************************************/  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;					       //PD0��TRIG    
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //��Ϊ�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(GPIOD, &GPIO_InitStructure);	        

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				         //PD1��ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		 //��Ϊ����
  GPIO_Init(GPIOD,&GPIO_InitStructure);			
	
	
	//����Ϊ���̴����ҵĳ���	
	/************************************************************************/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;					 //PD2��TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //��Ϊ�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(GPIOD, &GPIO_InitStructure);	                 //��ʼ������GPIO 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				     //PD3��ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		 //��Ϊ����
  GPIO_Init(GPIOD,&GPIO_InitStructure);						 //��ʼ��GPIOD
	
	
  /************************************************************************/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;					 //PD8��TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //��Ϊ�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(GPIOD, &GPIO_InitStructure);	                 //��ʼ������GPIO 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				     //PD9��ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		 //��Ϊ����
  GPIO_Init(GPIOD,&GPIO_InitStructure);						 //��ʼ��GPIOD
	
	/************************************************************************/  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;					 //PD10��TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //��Ϊ�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(GPIOD, &GPIO_InitStructure);	                 //��ʼ������GPIO D

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				     //PD11��ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		 //��Ϊ����
  GPIO_Init(GPIOD,&GPIO_InitStructure);						 //��ʼ��GPIOD
	
	/************************************************************************/  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;					 //PD12��TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //��Ϊ�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(GPIOD, &GPIO_InitStructure);	                 //��ʼ������GPIO 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				     //PD13��ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		 //��Ϊ����
  GPIO_Init(GPIOD,&GPIO_InitStructure);						 //��ʼ��GPIOD
	
	/************************************************************************/  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;					 //PD14��TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //��Ϊ�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(GPIOD, &GPIO_InitStructure);	                 //��ʼ������GPIO 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				     //PD15��ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		 //��Ϊ����
  GPIO_Init(GPIOD,&GPIO_InitStructure);						 //��ʼ��GPIOC

	/************************************************************************/  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;					 //PD4��TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //��Ϊ�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(GPIOD, &GPIO_InitStructure);	                 //��ʼ������GPIO 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				     //PD7��ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		 //��Ϊ����
  GPIO_Init(GPIOD,&GPIO_InitStructure);						 //��ʼ��GPIOC
	
}

int UltrasonicWave_CalculateTime(void)  //��õ�λ��mm
{
  UltrasonicWave_Distance=(int)(TIM_GetCounter(TIM6)*5*34/2000);
	return UltrasonicWave_Distance;
}

/*
 * ��������UltrasonicWave_StartMeasure
 * ����  ����ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
 * ����  ����
 * ���  ����	
 */
int UltrasonicWave_StartMeasure(int number)
{
	int Distance=0;
	switch(number)
	{
		 case 0:
				GPIO_SetBits(GPIOD,GPIO_Pin_2); 		  //��>10us�ĸߵ�ƽ
				DelayTime_us(10);		                      //��ʱ10us
				GPIO_ResetBits(GPIOD,GPIO_Pin_2);
							
				while(!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3));	             //�ȴ��ߵ�ƽ
				TIM_Cmd(TIM6, ENABLE);                                             //����ʱ��
				while(flag_0==0)
				{
					 if(TIM_GetCounter(TIM6)>length)
					 {
							TIM_Cmd(TIM6, DISABLE);
							Distance=UltrasonicWave_CalculateTime();
							TIM_SetCounter(TIM6,0);	
							flag_0=1;
						}
						else
						{
							 if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3) == RESET)	                 //�ȴ��͵�ƽ
							 {
									TIM_Cmd(TIM6, DISABLE);	//��ʱ��2ʧ��
									Distance=UltrasonicWave_CalculateTime();	//�������
									TIM_SetCounter(TIM6,0);
									flag_0=1;
								}
						}		 	
				 }
				 flag_0=0;
				 break;
			
			case 1:
				 GPIO_SetBits(GPIOD,GPIO_Pin_8); 		  //��>10US�ĸߵ�ƽ
				 DelayTime_us(10);		                      //��ʱ20US
				 GPIO_ResetBits(GPIOD,GPIO_Pin_8);
							
				 while(!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9));	             //�ȴ��ߵ�ƽ
				 TIM_Cmd(TIM6, ENABLE);                                             //����ʱ��
							
				 while(flag_1==0)
				 {
						if(TIM_GetCounter(TIM6)>length)
						{
								TIM_Cmd(TIM6, DISABLE);
								Distance=UltrasonicWave_CalculateTime();
								TIM_SetCounter(TIM6,0);	
								flag_1=1;
						 }
						 else
						 {
								if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9) == RESET)	                 //�ȴ��͵�ƽ
								{
									 TIM_Cmd(TIM6, DISABLE);	//��ʱ��2ʧ��
									 Distance=UltrasonicWave_CalculateTime();	//�������
									 TIM_SetCounter(TIM6,0);
									 flag_1=1;
								 }
							}		 	
					}
					flag_1=0;
					break;
			case 2:
					GPIO_SetBits(GPIOD,GPIO_Pin_10); 		  //��>10US�ĸߵ�ƽ
					DelayTime_us(10);		                      //��ʱ20US
					GPIO_ResetBits(GPIOD,GPIO_Pin_10);
							
					while(!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_11));	             //�ȴ��ߵ�ƽ
					TIM_Cmd(TIM6, ENABLE);                                             //����ʱ��
							
					while(flag_2==0)
					{
							if(TIM_GetCounter(TIM6)>length)
							{
							   TIM_Cmd(TIM6, DISABLE);
							   Distance=UltrasonicWave_CalculateTime();
							   TIM_SetCounter(TIM6,0);	
								 flag_2=1;
							}
						  else
							{
							    if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_11) == RESET)	                 //�ȴ��͵�ƽ
									{
									   TIM_Cmd(TIM6, DISABLE);	//��ʱ��2ʧ��
									   Distance=UltrasonicWave_CalculateTime();	//�������
										 TIM_SetCounter(TIM6,0);
										 flag_2=1;
									}
							}		 	
					}
					flag_2=0;
					break;
			case 3:
					GPIO_SetBits(GPIOD,GPIO_Pin_12); 		  //��>10US�ĸߵ�ƽ
					DelayTime_us(10);		                      //��ʱ20US
					GPIO_ResetBits(GPIOD,GPIO_Pin_12);
							
					while(!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13));	             //�ȴ��ߵ�ƽ
					TIM_Cmd(TIM6, ENABLE);                                             //����ʱ��
							
					while(flag_3==0)
					{
						  if(TIM_GetCounter(TIM6)>length)
							{
								  TIM_Cmd(TIM6, DISABLE);
									Distance=UltrasonicWave_CalculateTime();
									TIM_SetCounter(TIM6,0);	
									flag_3=1;
							}
							else
							{
								 if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13) == RESET)	                 //�ȴ��͵�ƽ
								 {
										TIM_Cmd(TIM6, DISABLE);	//��ʱ��2ʧ��
										Distance=UltrasonicWave_CalculateTime();	//�������
										TIM_SetCounter(TIM6,0);
										flag_3=1;
								 }
							}		 	
				    }
					  flag_3=0;
					  break;
			 	case 4:
						GPIO_SetBits(GPIOD,GPIO_Pin_14); 		  //��>10US�ĸߵ�ƽ
						DelayTime_us(10);		                      //��ʱ20US
						GPIO_ResetBits(GPIOD,GPIO_Pin_14);
							
						while(!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15));	             //�ȴ��ߵ�ƽ
						TIM_Cmd(TIM6, ENABLE);                                             //����ʱ��
							
						while(flag_4==0)
						{
							if(TIM_GetCounter(TIM6)>length)
							{
								TIM_Cmd(TIM6, DISABLE);
								Distance=UltrasonicWave_CalculateTime();
								TIM_SetCounter(TIM6,0);	
								flag_4=1;
							}
							else
							{
								if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15) == RESET)	                 //�ȴ��͵�ƽ
								{
									TIM_Cmd(TIM6, DISABLE);	//��ʱ��2ʧ��
									Distance=UltrasonicWave_CalculateTime();	//�������
									TIM_SetCounter(TIM6,0);
									flag_4=1;
								}
							}		 	
						}
						flag_4=0;
						break;
			 case 5:
						GPIO_SetBits(GPIOD,GPIO_Pin_4); 		  //��>10US�ĸߵ�ƽ
						DelayTime_us(10);		                      //��ʱ20US
						GPIO_ResetBits(GPIOD,GPIO_Pin_4);
							
						while(!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7));	             //�ȴ��ߵ�ƽ
						TIM_Cmd(TIM6, ENABLE);                                             //����ʱ��
							
						while(flag_5==0)
						{
							if(TIM_GetCounter(TIM6)>length)
							{
								TIM_Cmd(TIM6, DISABLE);
								Distance=UltrasonicWave_CalculateTime();
								TIM_SetCounter(TIM6,0);	
								flag_5=1;
							}
							else
							{
								if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7) == RESET)	                 //�ȴ��͵�ƽ
								{
									TIM_Cmd(TIM6, DISABLE);	//��ʱ��2ʧ��
									Distance=UltrasonicWave_CalculateTime();	//�������
									TIM_SetCounter(TIM6,0);
									flag_5=1;
								}
							}		 	
						}
						flag_5=0;
						break;
		}	
		return Distance;	
}

int UltrasonicWave_Measure_back(void)
{
	int Distance=0;
  GPIO_SetBits(GPIOD,GPIO_Pin_0); 		  //��>10US�ĸߵ�ƽ
	DelayTime_us(15);		                      //��ʱ20US
	GPIO_ResetBits(GPIOD,GPIO_Pin_0);
							
	while(!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1));	             //�ȴ��ߵ�ƽ
	TIM_Cmd(TIM6, ENABLE);                                             //����ʱ��
							
	while(flag_back_ultra==0)
	{
	  if(TIM_GetCounter(TIM6)>length)
	  {
	    TIM_Cmd(TIM6, DISABLE);
	  	Distance=UltrasonicWave_CalculateTime();
	  	TIM_SetCounter(TIM6,0);	
			flag_back_ultra=1;
		}
		else
		{
			if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1) == RESET)	                 //�ȴ��͵�ƽ
			{
				TIM_Cmd(TIM6, DISABLE);	//��ʱ��2ʧ��
				Distance=UltrasonicWave_CalculateTime();	//�������
				TIM_SetCounter(TIM6,0);
				flag_back_ultra=1;
			}
		}		 	
	}
	flag_back_ultra=0;	
	return Distance;
}

/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
