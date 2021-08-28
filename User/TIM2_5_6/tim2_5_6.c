#include "tim2_5_6.h"

void TIM2_PWM_Init(void)//PWM�����ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;      
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2|GPIO_Pin_1;      // ֻ�õ��˶�ʱ���ĵ�2��1·���
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		         // �����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /****************�ź�����0.5ms=(3599+1)/72Mhz*****************/    	
    TIM_TimeBaseStructure.TIM_Period = 3599;                   //����ʱ����0������3599����Ϊ3600�Σ�Ϊһ����ʱ����
    TIM_TimeBaseStructure.TIM_Prescaler = 0;	                 //����Ԥ��Ƶ7����Ϊ9MHz����Ԥ0��Ƶ����Ϊ72MHz��
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	 //����ʱ�ӷ�Ƶϵ��������Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	         //����ΪPWMģʽ1
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 100;	                     //����ͨ��1�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM  ���500
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);	                 //ʹ��ͨ��1 PA0
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	         //����ΪPWMģʽ1
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 100;	                     //����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM  ���500
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);	 
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM2, ENABLE);			                   // ʹ��TIM2���ؼĴ���ARR
    TIM_Cmd(TIM2, ENABLE);                                     //ʹ�ܶ�ʱ��2
}
/*
 * ��ʱ��5 TIM_Period / Auto Reload Register(ARR) = 1000   TIM_Prescaler--71 
 * �ж�����Ϊ = 1/(72MHZ /9) * 1000 = 125us
   �ж�����Ϊ = 1/(72MHZ /9) * 2000 = 250us
 *
 * TIMxCLK/CK_PSC --> TIMxCNT --> TIM_Period(ARR) --> �ж� ��TIMxCNT����Ϊ0���¼��� 
 */
void TIM5_Configuration(void)//�ٶȼ��㶨ʱ����ʼ��        
{
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5 , ENABLE); 
	
   /* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
   TIM_TimeBaseStructure.TIM_Period=4000;  //2000hz
    // TIM_TimeBaseStructure.TIM_Period=1000;  //8000hz
    // TIM_TimeBaseStructure.TIM_Period=2000;  //4000hz

    //TIM_TimeBaseStructure.TIM_Period=800;  //10000hz�Ĳ���Ƶ��
	
   /* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
   TIM_TimeBaseStructure.TIM_Prescaler= 8;
	
   /* ���ⲿʱ�ӽ��в�����ʱ�ӷ�Ƶ,����û���õ� */
   TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;	
   TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
   TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	
   TIM_ClearFlag(TIM5, TIM_FLAG_Update);
   TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);		
   TIM_Cmd(TIM5, ENABLE);																		    
}

void TIM1_Configuration(void)//��̼Ʒ�����ʱ����ʼ��
{
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
   TIM_DeInit(TIM1);
	

   /* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
   TIM_TimeBaseStructure.TIM_Period=500;  //  500*100us=50ms  5000*100us=500ms 
   TIM_TimeBaseStructure.TIM_Prescaler=(7200-1); //����7200/72=100us
	
	 /* ���ⲿʱ�ӽ��в�����ʱ�ӷ�Ƶ,����û���õ� */
   TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;	
   TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
   TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
   TIM_ClearFlag(TIM1, TIM_FLAG_Update);
   TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);		
   TIM_Cmd(TIM1, ENABLE);	
}
