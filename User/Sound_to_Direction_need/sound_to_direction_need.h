#ifndef __SOUND_TO_DIRECTION_NEED_H
#define __SOUND_TO_DIRECTION_NEED_H

#include "stm32f10x.h"
#include "math.h"
#include "stdio.h"
#include "cstring"

//ÿ�����������������
#define number_f 1
#define number_b 2
#define number_l 3
#define number_r 4

#define need_derivation 36    //����ʱ��36MHz��������Ϊ�˽�ʱ�䵥λת����΢��

void TIM8_Init(int pre_scalar);  //���ټ���ʱ�ӣ�����ΪԤ��Ƶϵ��
void IWDG_Init(u8 prer,u16 rlr);
void EXTIX_Init(void);     //�������������������źŽ��յ��ⲿ�ж�
void All_init(void);

#endif
