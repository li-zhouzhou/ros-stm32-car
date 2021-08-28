#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f10x.h"
#include "stdio.h"
#include "stdbool.h"
#include "PID.h"
#include "delay.h"

#define U16_MAX    ((u16)65535u)
#define U32_MAX    ((u32)4294967295uL)


#define SPEED_SAMPLING_TIME  9    // (9+1)*500usec = 5MS   ,200hz
#define SPEED_BUFFER_SIZE 3       //�������ٶȻ��������С

#define ENCODER1_TIMER TIM3   // ���B���̲ɼ���ʱ�� TIM3
#define ENCODER2_TIMER TIM4   // ���A���̲ɼ���ʱ�� TIM4
#define ENCODER2_PPR           (u16)(4096)  // ���2��������
#define ENCODER1_PPR           (u16)(4096)  // ���2��������

#define ICx_FILTER      (u8) 6 // 6<-> 670nsec   ������ģʽ���ò���

#define SPEED_SAMPLING_FREQ (u16)(2000/(SPEED_SAMPLING_TIME+1))  //200hz��С���ٶȲ���Ƶ��
//#define SPEED_SAMPLING_FREQ (u16)(10000/(SPEED_SAMPLING_TIME+1)) //1000hz

static unsigned short int hSpeedMeas_Timebase_500us = SPEED_SAMPLING_TIME;//����������ɼ�ʱ����

void ENC_Init(void);//��������ʼ��

void ENC_Init1(void);//���õ��B TIM3������ģʽPA6 PA7 ����
void ENC_Init2(void);//���õ��A TIM4������ģʽPB6 PB7 �ҵ��

s16 ENC_Calc_Rot_Speed1(void);//������B�ı�����
s16 ENC_Calc_Rot_Speed2(void);//������A�ı�����

void ENC_Clear_Speed_Buffer(void);//�ٶȴ洢������
void ENC_Calc_Average_Speed(void);//�������ε����ƽ��������

void Gain1(void);//���õ��B PID���� PA1
void Gain2(void);//���õ��A PID���� PA2

#endif 
