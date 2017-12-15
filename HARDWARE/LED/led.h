#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

#define LED0    PBout(1)// PB1
#define LED1    PEout(5)// PE5	

#define LED_FLASH_TIME 100 //��λ��10ms

#define LED0_FLASH    0x00
#define LED1_FLASH    0x01
#define LED2_FLASH    0x02
#define LED3_FLASH    0x03


extern void LED_Init(void);//��ʼ��

extern void LED_Flash(int led_n);
		 				    
#endif
