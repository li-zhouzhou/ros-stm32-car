#include "usart.h"

 /**
  * @brief  USART1 GPIO ����,����ģʽ���á�115200 8-N-1
  * @param  ��
  * @retval ��
  */
	
void USART1_Config(void)
{
	GPIO_InitTypeDef     GPIO_InitStructure;   //���ڶ˿����ýṹ�����
	USART_InitTypeDef    USART_InitStructure;  //���ڲ������ýṹ�����

	//��1������GPIO��USART������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);	 //��GPIOAʱ�Ӻ�GPIOA����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//�򿪴��ڸ���ʱ��
	USART_DeInit(USART1);  //��λ����1

	//��2������USART1 Tx�����ͽţ���GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			   //����1���ͽ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		   //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   //����ٶ�50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);				   //��ʼ��GPIOA
														  
	//��3������USART Rx�����սţ���GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;			   //����1���ս�
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);				   //��ʼ��GPIOA

	//��4��������USART1����
	USART_InitStructure.USART_BaudRate             = 115200;							 //���������ã�115200
	USART_InitStructure.USART_WordLength           = USART_WordLength_8b;			 //����λ�����ã�8λ
	USART_InitStructure.USART_StopBits             = USART_StopBits_1;				 //ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity               = USART_Parity_No;				 //�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None; //Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;	 //�����뷢�Ͷ�ʹ��
	USART_Init(USART1, &USART_InitStructure);										 //��ʼ��USART1

    //�򿪷����жϺͽ����ж�(�����Ҫ�ж�)
	 // USART_ITConfig(USART1, USART_IT_TXE, ENABLE);  // ʹ��ָ����USART1�����ж� ��
  	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // ʹ��ָ����USART1�����ж� ��

	//��5����ʹ�� USART1�� �������
	USART_Cmd(USART1, ENABLE);							   //ʹ�� USART1

    //�����������1���ֽ��޷���ȷ���ͳ�ȥ������
    USART_ClearFlag(USART1, USART_FLAG_TC);                //�崮��1���ͱ�־
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
