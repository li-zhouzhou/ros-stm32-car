#ifndef __STM32F10x_IT_H
#define __STM32F10x_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f10x.h"
#include <stdio.h>
#include "encoder.h"
#include "contact.h"
#include "string.h"
#include "delay.h"
	 
#define USART_REC_LEN  			200  	//�����������ֽ��� 200

void USART1_IRQHandler(void);//�����жϺ���
void TIM5_IRQHandler(void);//�ٶȼ��㶨ʱ���жϺ���
void TIM1_UP_IRQHandler(void);//��̼Ʒ�����ʱ���жϺ���
    
#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_IT_H */

