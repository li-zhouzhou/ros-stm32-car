#ifndef __UltrasonicWave_H
#define	__UltrasonicWave_H

void UltrasonicWave_Configuration(void);               //�Գ�����ģ���ʼ��
int UltrasonicWave_StartMeasure(int Ulta_number);                //��ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
int UltrasonicWave_Measure_back(void);

#endif
