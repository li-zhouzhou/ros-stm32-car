#include "stm32f10x.h"
#include "nvic_conf.h"

void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;	
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);//���ж�ʸ���ŵ�Flash��0��ַ
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//�������ȼ����õ�ģʽ,��1��:��ռ���ȼ�0(0:7),��ռ���ȼ�1(0:7),

    /****************************ʹ�ܴ���1�жϣ����������ȼ�***********************/
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;					   //USART1ȫ���ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	   //��ռ���ȼ� 1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	           //��ռ���ȼ� 2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  		 			   //ʹ���ж�
    NVIC_Init(&NVIC_InitStructure);	     	
		  	
	
	NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn;                //B(��)�����жϺ�������encoder.c�ж���ʹ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel =TIM4_IRQn;                //A(��)�����жϺ�������encoder.c�ж���ʹ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
                                                        
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	 
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}	
