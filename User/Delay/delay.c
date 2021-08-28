#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////   

//********************************************************************************
//V1.2�޸�˵��
//�������ж��е��ó�����ѭ���Ĵ���
//��ֹ��ʱ��׼ȷ,����do while�ṹ!
//////////////////////////////////////////////////////////////////////////////////   
static u8  fac_us=0;//us��ʱ������
static u16 fac_ms=0;//ms��ʱ������

int sys_num=0;
/**********************************************************
** ������: delay_init	��ʼ���ӳٺ���
** ��������: ��ʼ���ӳٺ���,SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
** �������: SYSCLK����λMHz)
** �������: ��
** ���÷��������ϵͳʱ�ӱ���Ϊ72MHz,�����delay_init(72)
***********************************************************/
void delay_init(u8 SYSCLK)
{
    SysTick->CTRL&=0xfffffffb;//bit2���,ѡ���ⲿʱ��  HCLK/8
    fac_us=SYSCLK/8;    	    
    fac_ms=(u16)fac_us*1000;
}               				    
/**********************************************************
** ������: delay_ms
** ��������: ��ʱnms
** �������: nms
** �������: ��
** ˵����SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
		nms<=0xffffff*8*1000/SYSCLK
		SYSCLK��λΪHz,nms��λΪms
		��72M������,nms<=1864 
***********************************************************/	
void delay_ms(u16 nms)
{             	  
    u32 temp;   	   
    SysTick->LOAD=(u32)nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
    SysTick->VAL =0x00;           //��ռ�����
    SysTick->CTRL=0x01 ;          //��ʼ����  
    do
    {
        temp=SysTick->CTRL;
    }
    while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
    SysTick->CTRL=0x00;       //�رռ�����
    SysTick->VAL =0X00;       //��ռ�����          
}   
                  						   
/**********************************************************
** ������: delay_us
** ��������: ��ʱnus��nusΪҪ��ʱ��us��.
** �������: nus
** �������: ��
***********************************************************/  
void delay_us(u32 nus)
{   	
    u32 temp;       	 
    SysTick->LOAD=nus*fac_us; //ʱ�����      		 
    SysTick->VAL=0x00;        //��ռ�����
    SysTick->CTRL=0x01 ;      //��ʼ���� 	 
    do
    {
        temp=SysTick->CTRL;
    }
    while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
    SysTick->CTRL=0x00;       //�رռ�����
    SysTick->VAL =0X00;       //��ռ�����	 
}


void Systick_Init(void)
{
 if( SysTick_Config(SystemCoreClock / 10000))
 {

 }
}
void SysTick_Handler(void)
{
	sys_num++;
	if(sys_num>89)
	{
		sys_num=0;
		IWDG_ReloadCounter();	
	}
}

