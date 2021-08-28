#include "gpio_conf.h"

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;   /*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOB, ENABLE); 	/*����GPIOA��GPIOC��GPIOE������ʱ��*/
                                                    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_10|GPIO_Pin_11;  // �������																
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   /*��������ģʽΪͨ���������*/
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 	/*������������Ϊ50MHz */   
    GPIO_Init(GPIOC, &GPIO_InitStructure);	        /*���ÿ⺯������ʼ��GPIOC*/	
    
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12;	//��ײ��� Left  Middle Right
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   /*��������ģʽΪͨ���������*/
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 	/*������������Ϊ50MHz */   
//    GPIO_Init(GPIOA, &GPIO_InitStructure);	        /*���ÿ⺯������ʼ��GPIOC*/
//        
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_15|GPIO_Pin_12|GPIO_Pin_14;	//������
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   /*��������ģʽΪͨ���������*/
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 	/*������������Ϊ50MHz */   
//    GPIO_Init(GPIOE, &GPIO_InitStructure);	        /*���ÿ⺯������ʼ��GPIOC*/	
//    
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 �˿�����
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
//    GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
//    GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 �����
    
}
	

