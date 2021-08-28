#ifndef __PID_H
#define __PID_H

#include "stdio.h"

struct PID
{
    float Kp;
    float Ki;
    float Kd;
    float error_0;//��������
    float error_1;//һ��г������
    float error_2;//����г������
    long  Sum_error;
    float OutputValue;//ʵ�������
    float OwenValue;//�����ʱ�ı�׼�����
};

float PID_calculate( struct PID *Control,float CurrentValue);      //λ��PID����

#endif 
