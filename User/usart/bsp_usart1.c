/**
  ******************************************************************************
  * @file    bsp_usart1.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����c��printf������usart�˿�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "bsp_usart1.h"

 /**
  * @brief  USART1 GPIO ����,����ģʽ���á�115200 8-N-1
  * @param  ��
  * @retval ��
  */
void USART1_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		
		/* config USART1 clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
		
		/* USART1 GPIO config */
		/* Configure USART1 Tx (PA.09) as alternate function push-pull */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		/* Configure USART1 Rx (PA.10) as input floating */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
			
		/* USART1 mode config */
		USART_InitStructure.USART_BaudRate = 115200;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No ;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART1, &USART_InitStructure); 
		
			/* ʹ�ܴ���1�����ж� */
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	  //USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		USART_Cmd(USART1, ENABLE);
		
/********************************************************************************************/		
		//�Խ������Ĵ���2���� 
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO, ENABLE);
	 //����remap_gpio����2
	 GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);
	 
   //����PA2��USART2_TX_
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
   GPIO_Init(GPIOD,&GPIO_InitStructure);
   //����PA3��USART2_RX
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
   GPIO_Init(GPIOD,&GPIO_InitStructure);
   //����USART2���ж�����
//   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//   NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
//   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //���ȼ�Ϊ��0��
//   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//   NVIC_Init(&NVIC_InitStructure);
   //����USART2
/******************************************************
     ������Ϊ115200,�ֳ�Ϊ8������żУ��λ����ֹλΪ1.
******************************************************/
   USART_InitStructure.USART_BaudRate=115200;
   USART_InitStructure.USART_WordLength=USART_WordLength_8b;
   USART_InitStructure.USART_StopBits=USART_StopBits_1;
   USART_InitStructure.USART_Parity=USART_Parity_No;
   USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
   USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
   USART_Init(USART2,&USART_InitStructure);
   //��USART2�жϴ�����ʽΪ�����ж�
   USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//���ܿ�IT-TXE�ж�ʹ�ܣ���Ϊ��ʼ��ʱҲ����TXE��λ����Ϊ��ʱ�������ݼĴ���Ϊ��
   //ʹ��USART2��ʱ��
   USART_Cmd(USART2,ENABLE);
   //���USART2�ķ��ͽ�����־λ�������һ���ַ����Ͳ���ȥ
   USART_ClearFlag(USART2,USART_FLAG_TC);
   //����2������� 
}

///�ض���c�⺯��printf��USART1
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ�USART1 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///�ض���c�⺯��scanf��USART1 ��ʱû�õ�
int fgetc(FILE *f)
{
		/* �ȴ�����1�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}
/*********************************************END OF FILE**********************/
