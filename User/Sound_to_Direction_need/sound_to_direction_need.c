#include "sound_to_direction_need.h"

int sequence[]={0,0,0,0};             //�洢����������˳�������
int number=0;                         //�������еı�Ų���
int caculate_direction=0;             //�Ƿ���нǶȼ����־λ
int time1,time2,time3;                //��һ�����������źŽ��ܵ��ڶ����������������ĸ�֮���ʱ����
int time_s,time1_1,time2_1,time3_1;   //��ʼ����ʱ��������ֵ����һ�Ρ��ڶ��Ρ��������ⲿ�жϴ���ʱ��������ֵ
int flag_update=0;                    //ǰ�������������������źŽ���֮��������Ƿ������־λ
int caculate_once;                    //�Ƿ����һ�ο���λ
extern int angle_decision;  

int jishu=0;   //���Բ���

void TIM8_Init(int pre_scalar)
{
	 TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	 NVIC_InitTypeDef  NVIC_InitStructure;
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8 , ENABLE);
   TIM_DeInit(TIM8);
	
	 //ʹ��arr��ֵ�����Ĵ�
   TIM_TimeBaseStructure.TIM_Period=65535;		 								/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
   TIM_TimeBaseStructure.TIM_Prescaler=pre_scalar;				    /* ʱ��Ԥ��Ƶ�� 72M/360 ,����5us*/ 
   TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		  /* ������Ƶ */
   TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;  /* ���ϼ���ģʽ */
   TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
	
	 TIM_ITConfig(TIM8, TIM_IT_Update ,ENABLE  );               //ʹ�ܻ���ʧ��ָ����TIM�ж�
   TIM_ClearFlag(TIM8, TIM_FLAG_Update);
	 TIM_ARRPreloadConfig(TIM8, ENABLE);                        //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���

	 TIM_Cmd(TIM8, ENABLE);                                     //ʹ��TIMx����
	
	 NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;         //TIM8�ж�
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //��ռ���ȼ�0��
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         //�����ȼ�3��
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQͨ����ʹ��
	 NVIC_Init(&NVIC_InitStructure);                            //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}

void TIM8_UP_IRQHandler(void)                                 //ITM8������жϷ����� 
{
	 if (TIM_GetITStatus(TIM8, TIM_IT_Update) != RESET)         //���ָ����TIM�жϷ������:TIM �ж�Դ 
	 {
	 TIM_ClearITPendingBit(TIM8, TIM_IT_Update);                //���TIMx���жϴ�����λ:TIM �ж�Դ 
	 flag_update=1;
	 }
}

//void IWDG_Init(u8 prer,u16 rlr)   //���Ź���λ����ϵͳ���������¿����÷����Ȳ�ʹ��
//{
//	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //ʹ�ܶԼĴ���IWDG_PR��IWDG_RLR��д����
//	
//	IWDG_SetPrescaler(prer);  //����IWDGԤ��Ƶֵ:����IWDGԤ��ƵֵΪ64
//	
//	IWDG_SetReload(rlr);  //����IWDG��װ��ֵ
//	
//	IWDG_ReloadCounter();  //����IWDG��װ�ؼĴ�����ֵ��װ��IWDG������
//	
//	IWDG_Enable();  //ʹ��IWDG
//}

//void IWDG_Feed(void)
//{   
// 	IWDG_ReloadCounter();										   
//}


EXTI_InitTypeDef EXTI_InitStructure;

void EXTIX_Init(void)
{
 	  NVIC_InitTypeDef NVIC_InitStructure;
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);          //�ⲿ�жϣ���Ҫʹ��AFIOʱ��
	
    //GPIOE.1 �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource1);


  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;      //�½��ش���
		EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	                           //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	  EXTI_ClearITPendingBit(EXTI_Line1); 

    //GPIOE.2	  �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	                         //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		
		EXTI_ClearITPendingBit(EXTI_Line2); 

    //GPIOE.3	  �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);

   	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		                          //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		
		EXTI_ClearITPendingBit(EXTI_Line3); 

  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);

   	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		                          //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		
	  EXTI_ClearITPendingBit(EXTI_Line4); 
		
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3); 
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			        //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x04;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	                            //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			        //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x04;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
 
 
   	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			        //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x04;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
		
		
   	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			        //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x04;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
}
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1)!=RESET)
	{
		if(number==0)
		{
//			time_s=TIM_GetCounter(TIM8);	
//			flag_update=0;		
			sequence[number]=number_f;
		}
		if(number==1)
		{
//			time1_1=TIM_GetCounter(TIM8);
//			if(flag_update)
//			{
//				time1=time1_1+65535-time_s;
//				flag_update=0;
//			}
//			else
//				time1=time1_1-time_s;
			//time1=time1/need_derivation;
			sequence[number]=number_f;
		}
		if(number==2)
		{
//			time2_1=TIM_GetCounter(TIM8);
//			if(flag_update)
//			{
//				time2=time2_1+65535-time1_1+time1;
//				flag_update=0;
//			}
//			else
//			time2=time2_1-time1_1+time1;
			//time2=time2/need_derivation;
			sequence[number]=number_f;
		}
		if(number==3)
		{
//			time3_1=TIM_GetCounter(TIM8);
//			if(flag_update)
//			{
//				time3=time3_1+65535-time2_1+time2;
//				flag_update=0;
//			}
//			else
//			time3=time3_1-time2_1+time2;			
			//time3=time3/need_derivation;
			
			sequence[number]=number_f;
			caculate_direction=1;
			caculate_once=1;
		}
		number++;
		EXTI_ClearFlag(EXTI_Line1);
		EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  	EXTI_Init(&EXTI_InitStructure);
		//jishu++;
	}
}

void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2)!=RESET)
	{
		if(number==0)
		{
			
//			time_s=TIM_GetCounter(TIM8);	
//			flag_update=0;		
			sequence[number]=number_b;
		}
		if(number==1)
		{
//			time1_1=TIM_GetCounter(TIM8);
//			if(flag_update)
//			{
//				time1=time1_1+65535-time_s;
//				flag_update=0;
//			}
//			else
//				time1=time1_1-time_s;
			//time1=time1/need_derivation;
			sequence[number]=number_b;
		}
		if(number==2)
		{
//			time2_1=TIM_GetCounter(TIM8);
//			if(flag_update)
//			{
//				time2=time2_1+65535-time1_1+time1;
//				flag_update=0;
//			}
//			else
//				time2=time2_1-time1_1+time1;
//			//time2=time2/need_derivation;
			sequence[number]=number_b;
		}
		if(number==3)
		{
//			time3_1=TIM_GetCounter(TIM8);
//			if(flag_update)
//			{
//				time3=time3_1+65535-time2_1+time2;
//				flag_update=0;
//			}
//			else
//			time3=time3_1-time2_1+time2;
			
			sequence[number]=number_b;
			caculate_direction=1;
			caculate_once=1;
		}
		number++;
		EXTI_ClearFlag(EXTI_Line2);
		EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  	EXTI_Init(&EXTI_InitStructure);

	}	
}

void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3)!=RESET)
	{
		if(number==0)
		{
//			time_s=TIM_GetCounter(TIM8);	
//			flag_update=0;		
			sequence[number]=number_l;
		}
		if(number==1)
		{
//			time1_1=TIM_GetCounter(TIM8);
//			if(flag_update)
//			{
//				time1=time1_1+65535-time_s;
//				flag_update=0;
//			}
//			else
//				time1=time1_1-time_s;
			//time1=time1/need_derivation;
			sequence[number]=number_l;
		}
		if(number==2)
		{
//			time2_1=TIM_GetCounter(TIM8);
//			if(flag_update)
//			{
//				time2=time2_1+65535-time1_1+time1;
//				flag_update=0;
//			}
//			else
//				time2=time2_1-time1_1+time1;
			//time2=time2/need_derivation;
			sequence[number]=number_l;
		}
		if(number==3)
		{
//			time3_1=TIM_GetCounter(TIM8);
//			if(flag_update)
//			{
//				time3=time3_1+65535-time2_1+time2;
//				flag_update=0;
//			}
//			else
//			time3=time3_1-time2_1+time2;
			
			sequence[number]=number_l;
			caculate_direction=1;
			caculate_once=1;
		}
		number++;
		EXTI_ClearFlag(EXTI_Line3);
		
		EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  	EXTI_Init(&EXTI_InitStructure);

	}	
}

void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4)!=RESET)
	{
		if(number==0)
		{
		
//			time_s=TIM_GetCounter(TIM8);
//			flag_update=0;		
			sequence[number]=number_r;
		}
		if(number==1)
		{
//			time1_1=TIM_GetCounter(TIM8);
//			if(flag_update)
//			{
//				time1=time1_1+65535-time_s;
//				flag_update=0;
//			}
//			else
//				time1=time1_1-time_s;
			//time1=time1/need_derivation;
			sequence[number]=number_r;
		}
		if(number==2)
		{
//			time2_1=TIM_GetCounter(TIM8);
//			if(flag_update)
//			{
//				time2=time2_1+65535-time1_1+time1;
//				flag_update=0;
//			}
//			else
//				time2=time2_1-time1_1+time1;
		//	time2=time2/need_derivation;
			sequence[number]=number_r;
		}
		if(number==3)
		{
//			time3_1=TIM_GetCounter(TIM8);
//			if(flag_update)
//			{
//				time3=time3_1+65535-time2_1+time2;
//				flag_update=0;
//			}
//			else
//			time3=time3_1-time2_1+time2;
			
			sequence[number]=number_r;
			caculate_direction=1;
			caculate_once=1;

		}
		number++;
		EXTI_ClearFlag(EXTI_Line4);
		EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  	EXTI_Init(&EXTI_InitStructure);
		jishu++;
	}	
}

void All_init(void)                 //�����������ת������ʱʹ��
{
		EXTI_InitTypeDef EXTI_InitStructure;
		//delay_us(20000);
	  EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);
		
   	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);
		
   	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);
		
   	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);
		
		caculate_direction=0;
		angle_decision=0;
		printf("go\r\n");
		number=0;
		memset(sequence,0,5*sizeof(int));                      //����sequence[]ȫ������
		jishu=0;
}	
