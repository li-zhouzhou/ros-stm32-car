#include "stm32f10x_it.h"

/***************************************************************************************************/

extern s32 hSpeed_Buffer1[],hSpeed_Buffer2[];//�������ٶȻ�������
extern u8 main_sta;//����������ִ�б�־λ

//extern u8 bSpeed_Buffer_Index;
u8 bSpeed_Buffer_Index = 0;//���������ֱ��������������

//extern float Milemeter_L_Motor,Milemeter_R_Motor;      //�ۼƵ��һ�����е���� cm		
float  Milemeter_L_Motor=0,Milemeter_R_Motor=0;//dtʱ���ڵ��������ٶ�,������̼Ƽ���

u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u16 USART_RX_STA=0;   //����״̬���	
u8 serial_rec=0x31;   //���մ������ݱ���

extern float pulse;//���A PID���ں��PWMֵ����
extern float pulse1;//���B PID���ں��PWMֵ����

/***************************************************************************************************/

void USART1_IRQHandler(void)//�����жϺ���
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //�Ƿ���ܵ�����
    {
		serial_rec =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
					
		if((USART_RX_STA&0x8000)==0)//����δ���
        {
            if(USART_RX_STA&0x4000)//���յ���0x0d
            {
                if(serial_rec==0x0a)
                {
                    if((USART_RX_STA&0x3f)==8)
                    {							
                        USART_RX_STA|=0x8000;	//��������� 
                        main_sta|=0x04;
                        main_sta&=0xF7;
                    }
                    else
                    {
                        main_sta|=0x08;
                        main_sta&=0xFB;
                        USART_RX_STA=0;//���մ���,���¿�ʼ
                    }
                }
                else 
                {
                    main_sta|=0x08;
                    USART_RX_STA=0;//���մ���,���¿�ʼ
                }
            }
            else //��û�յ�0X0D
            {	
                if(serial_rec==0x0d)USART_RX_STA|=0x4000;
                else
                {
                    USART_RX_BUF[USART_RX_STA&0X3FFF]=serial_rec ;
                    USART_RX_STA++;
                    if(USART_RX_STA>(USART_REC_LEN-1))
                    {
                        main_sta|=0x08;
                        USART_RX_STA=0;//�������ݴ���,���¿�ʼ����
                    }							
                }		 
            }
        }   		 
    }
}

void TIM5_IRQHandler(void)//С���ٶȼ��㶨ʱ���жϺ���
{
	if ( TIM_GetITStatus(TIM5 , TIM_IT_Update) != RESET ) 
	{						      
        if (hSpeedMeas_Timebase_500us !=0)//����������ɼ�ʱ����δ��
        {
            hSpeedMeas_Timebase_500us--;//��ʼ����	
        }
        else    //����������ɼ�ʱ��������
        {
            s32 wtemp2,wtemp1;
            
            hSpeedMeas_Timebase_500us = SPEED_SAMPLING_TIME;//�ָ�����������ɼ�ʱ����
            
            /************************ 1 ***************************/
            
            wtemp2 = ENC_Calc_Rot_Speed2(); //A ��ȡ�ı�����
            wtemp1 = ENC_Calc_Rot_Speed1(); //B ��ȡ�ı�����
            
//            //���Ϊָֹͣ����������ٶ�Ϊ�㣬������ٶȴ洢����ֹǰ���ٶȲ�̫�����С����ת
//            if((wtemp2 == 0) && (wtemp1 == 0))
//            {
//                pulse=pulse1=0;
//            }
             
            /************************ 2 ***************************/
            
            //���������������������������̼Ƽ���
            Milemeter_L_Motor= (float)wtemp1; //����������
            Milemeter_R_Motor= (float)wtemp2;
            
            main_sta|=0x02;//ִ�м�����̼����ݲ���

            /************************ 3 ***************************/
            
            //��ʼ���������ֱ�����������
            hSpeed_Buffer2[bSpeed_Buffer_Index] = wtemp2;
            hSpeed_Buffer1[bSpeed_Buffer_Index] = wtemp1;
            bSpeed_Buffer_Index++;//������λ
            
            //���������ֱ���������������ж�
            if(bSpeed_Buffer_Index >=SPEED_BUFFER_SIZE)
            {
                bSpeed_Buffer_Index=0;//���������ֱ������������������
            }
            
            /************************ 4 ***************************/
            
            ENC_Calc_Average_Speed();//�������ε����ƽ��������
            Gain2(); //���Aת��PID���ڿ��� ��
            Gain1(); //���Bת��PID���ڿ��� ��
        }
        
		TIM_ClearITPendingBit(TIM5 , TIM_FLAG_Update);//����жϱ�־λ    		 
	}		 
}


void TIM1_UP_IRQHandler(void)//��̼Ʒ�����ʱ���жϺ���
{
	if( TIM_GetITStatus(TIM1 , TIM_IT_Update) != RESET ) 
	{	
		main_sta|=0x01;//ִ�з�����̼����ݲ���
		
		TIM_ClearITPendingBit(TIM1 , TIM_FLAG_Update);//����жϱ�־λ  		 
	}		 
}

/***************************************************************************************************/




