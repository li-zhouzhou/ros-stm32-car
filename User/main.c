/***********************************************  ˵��  *****************************************************************
*
*   1.���ڽ���
*    ��1�����ݣ�С���������ٶ�,��λ:mm/s���������ݶ�Ϊfloat�ͣ�float��ռ4�ֽڣ�
*    ��2����ʽ��10�ֽ� [�����ٶ�4�ֽ�][�����ٶ�4�ֽ�][������"\r\n"2�ֽ�]
*
*   2.���ڷ���
*    ��1�����ݣ���̼ƣ�x,y���ꡢ���ٶȡ����ٶȺͷ���ǣ���λ����Ϊ��mm,mm,mm/s,rad/s,rad���������ݶ�Ϊfloat�ͣ�float��ռ4�ֽڣ�
*    ��2����ʽ��21�ֽ� [x����4�ֽ�][y����4�ֽ�][�����4�ֽ�][���ٶ�4�ֽ�][���ٶ�4�ֽ�][������"\n"1�ֽ�]
*
************************************************************************************************************************/
#include "stm32f10x.h"
#include "stm32f10x_it.h"

#include "delay.h"
#include "nvic_conf.h"
#include "rcc_conf.h"

#include "usart.h"
#include "encoder.h"
#include "contact.h"
#include "gpio_conf.h"
#include "tim2_5_6.h"
#include "odometry.h"
#include "tim2_5_6.h"

#include "stdbool.h"
#include <stdio.h>
#include "string.h"
#include "math.h"
/***********************************************  ���  *****************************************************************/

char odometry_data[21]={0};   //���͸����ڵ���̼���������

float odometry_right=0,odometry_left=0;//���ڵõ����������ٶ�

/***********************************************  ����  *****************************************************************/

extern float position_x,position_y,oriention,velocity_linear,velocity_angular;         //����õ�����̼���ֵ

extern u8 USART_RX_BUF[USART_REC_LEN];     //���ڽ��ջ���,���USART_REC_LEN���ֽ�.
extern u16 USART_RX_STA;                   //���ڽ���״̬���	

extern float Milemeter_L_Motor,Milemeter_R_Motor;     //dtʱ���ڵ��������ٶ�,������̼Ƽ���

/***********************************************  ����  *****************************************************************/

u8 main_sta=0; //������������������if��ȥ�������flag��1��ӡ��̼ƣ���2���ü�����̼����ݺ�������3���ڽ��ճɹ�����4���ڽ���ʧ�ܣ�

union recieveData  //���յ�������
{
	float d;    //�������ٶ�
	unsigned char data[4];
}leftdata,rightdata;       //���յ�����������

union odometry  //��̼����ݹ�����
{
	float odoemtry_float;
	unsigned char odometry_char[4];
}x_data,y_data,theta_data,vel_linear,vel_angular;     //Ҫ��������̼����ݣ��ֱ�Ϊ��X��Y�����ƶ��ľ��룬��ǰ�Ƕȣ����ٶȣ����ٶ�

/****************************************************************************************************************/	
int main(void)
{		
	u8 t=0;
	u8 i=0,j=0,m=0;

    RCC_Configuration();      //ϵͳʱ������		
	NVIC_Configuration();     //�ж����ȼ�����
	GPIO_Configuration(); 	  //������������������
	USART1_Config();	      //����1����
    
    TIM2_PWM_Init();	      //PWM�����ʼ��
	ENC_Init();               //��������ʼ��
	TIM5_Configuration();     //�ٶȼ��㶨ʱ����ʼ��
	TIM1_Configuration();     //��̼Ʒ�����ʱ����ʼ��

	while (1)
	{		
		if(main_sta&0x01)//ִ�з�����̼����ݲ���
		{
            //��̼����ݻ�ȡ
			x_data.odoemtry_float=position_x;//��λmm
			y_data.odoemtry_float=position_y;//��λmm
			theta_data.odoemtry_float=oriention;//��λrad
			vel_linear.odoemtry_float=velocity_linear;//��λmm/s
			vel_angular.odoemtry_float=velocity_angular;//��λrad/s
            
            //��������̼����ݴ浽Ҫ���͵�����
			for(j=0;j<4;j++)
			{
				odometry_data[j]=x_data.odometry_char[j];
				odometry_data[j+4]=y_data.odometry_char[j];
				odometry_data[j+8]=theta_data.odometry_char[j];
				odometry_data[j+12]=vel_linear.odometry_char[j];
				odometry_data[j+16]=vel_angular.odometry_char[j];
			}
            
			odometry_data[20]='\n';//��ӽ�����
            
			//��������Ҫ����
			for(i=0;i<21;i++)
			{
				USART_ClearFlag(USART1,USART_FLAG_TC);  //�ڷ��͵�һ������ǰ�Ӵ˾䣬�����һ�����ݲ����������͵�����				
				USART_SendData(USART1,odometry_data[i]);//����һ���ֽڵ�����	
				while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);	//�ȴ����ͽ���			
			}
            
			main_sta&=0xFE;//ִ�м�����̼����ݲ���
		}
		if(main_sta&0x02)//ִ�м�����̼����ݲ���
		{
			odometry(Milemeter_R_Motor,Milemeter_L_Motor);//������̼�
        
			main_sta&=0xFD;//ִ�з�����̼����ݲ���
		} 
		if(main_sta&0x08)        //������ָ��û����ȷ����ʱ
		{
			USART_ClearFlag(USART1,USART_FLAG_TC);  //�ڷ��͵�һ������ǰ�Ӵ˾䣬�����һ�����ݲ����������͵�����
            for(m=0;m<3;m++)
            {
                USART_SendData(USART1,0x00);	
                while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
            }		
            USART_SendData(USART1,'\n');	
            while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);	
            main_sta&=0xF7;
		}
		if(USART_RX_STA&0x8000)  // ����1���պ���
		{			
            //�����������ٶ�
            for(t=0;t<4;t++)
            {
                rightdata.data[t]=USART_RX_BUF[t];
                leftdata.data[t]=USART_RX_BUF[t+4];
            }
            
            //�����������ٶ�
            odometry_right=rightdata.d;//��λmm/s
            odometry_left=leftdata.d;//��λmm/s
            
			USART_RX_STA=0;//������ձ�־λ
		}
       
        car_control(rightdata.d,leftdata.d);	 //�����յ����������ٶȸ���С��	
	}//end_while
}//end main
/*********************************************END OF FILE**************************************************/
