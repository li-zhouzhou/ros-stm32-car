#include "sample_function.h"
#include "stm32f10x.h"
#include "stdbool.h"
#include "UltrasonicWave.h"
#include <stdio.h>
//���⴫���������źŽ��ձ���,�����ø�
extern bool Red_Left,Red_Front_Middle,Red_Front_Right,Red_Front_Left,Red_Right;

//��ײ�����������źŽ��ձ���,����ֵ��
int seq_bumper[3]={0};                    //�洢������ײ���������ź�ֵ


void red_sample(void)
{
	Red_Left=GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_15);
	Red_Front_Left=GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14);
	Red_Front_Middle=GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_13);
	Red_Front_Right=GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12);
	Red_Right=GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11);
}

void bumper_sample(void)
{
	seq_bumper[0]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8);     //��
	seq_bumper[1]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11);    //ǰ
	seq_bumper[2]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12);    //��
	
	//printf(" %d %d %d\r\n",seq_bumper[0],seq_bumper[1],seq_bumper[2]);
}

