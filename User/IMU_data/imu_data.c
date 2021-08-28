#include "imu_data.h"

int once_delay=1;
float acc[3],w[3],angle[3],T;    //���ٶȣ����ٶȣ��Ƕȣ��¶�
extern unsigned char Re_buf[11],temp_buf[11],counter;
extern unsigned char sign;       //���ڽ������ݺ���������̵ı�־λ
static unsigned char Temp[11];   //���ݻ���

void imu_data(void)              //�����ǵ����ȼ�Ҫ���ڼ�����������ȼ�����ֹ��ʱ�������ǵ�׼ȷ�ȴ����˶�ʱ������Ϊ����
{
//	 if(once_delay)
//	 {
//		 delay_ms(200);
//		 once_delay=0;
//	 }
	
	 if(sign)
   {  
      memcpy(Temp,Re_buf,11);
      sign=0;
      if(Re_buf[0]==0x55)       //���֡ͷ
      {  
        switch(Re_buf[1])
        {
           case 0x51: //��ʶ������Ǽ��ٶȰ�
              acc[0] = ((short)(Temp[3]<<8 | Temp[2]))/32768.0*16*9.8;      //X����ٶ�
              acc[1] = ((short)(Temp[5]<<8 | Temp[4]))/32768.0*16*9.8;      //Y����ٶ�
              acc[2] = ((short)(Temp[7]<<8 | Temp[6]))/32768.0*16*9.8;      //Z����ٶ�
              T    = ((short)(Temp[9]<<8 | Temp[8]))/340.0+36.25;      //�¶�
              break;
           case 0x52: //��ʶ������ǽ��ٶȰ�
              w[0] = ((short)(Temp[3]<<8| Temp[2]))/32768.0*2000;      //X����ٶ�
              w[1] = ((short)(Temp[5]<<8| Temp[4]))/32768.0*2000;      //Y����ٶ�
              w[2] = ((short)(Temp[7]<<8| Temp[6]))/32768.0*2000;      //Z����ٶ�
              T    = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;      //�¶�
              break;
           case 0x53: //��ʶ������ǽǶȰ�
              angle[0] = ((short)(Temp[3]<<8| Temp[2]))/32768.0*180;   //X���ת�ǣ�x �ᣩ
              angle[1] = ((short)(Temp[5]<<8| Temp[4]))/32768.0*180;   //Y�ḩ���ǣ�y �ᣩ
              angle[2] = ((short)(Temp[7]<<8| Temp[6]))/32768.0*180;   //Z��ƫ���ǣ�z �ᣩ
              T        = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;   //�¶�

              //printf("X��Ƕȣ�%.2f   Y��Ƕȣ�%.2f   Z��Ƕȣ�%.2f\r\n",angle[0],angle[1],angle[2]);
              break;
              default:  break;
        }
			//printf("X�Ƕȣ�%.2f  Y�Ƕȣ�%.2f  Z�Ƕȣ�%.2f  X�ٶȣ�%.2f  Y�ٶȣ�%.2f  Z�ٶȣ�%.2f\r\n",angle[0],angle[1],angle[2],w[0],w[1],w[2]);
			 //printf("%.2f %.2f %.2f\r\n",acc[0],acc[1],acc[2]);
     }        
  }
//  delay_ms(50);
			
}
