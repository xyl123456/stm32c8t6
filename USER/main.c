#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "user_app.h"

 
/************************************************
 ALIENTEKս��STM32������ʵ��4
 ����ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


 int main(void)
 {		
	SystemInit();
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	myuart_init(1,9600);//��ʼ������1,������wifiģ��ͨ��
	myuart_init(2,115200);//��ʼ������2
	//myuart_init(3,115200);//��ʼ������3
	TIM3_Int_Init(SECOND_1S_TIME,TIME3_10KHZ_PRE);//10Khz�ļ���Ƶ�ʣ�������9999Ϊ1s  
 	LED_Init();			     //LED�˿ڳ�ʼ��
	//KEY_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�
	hal_board_init();//�ϵ��������
 	while(1)
	{
		//KEY=keyscan();
		uart_receve_handle();
		event_task_handle();
		delay_ms(20);
	}	 
 }

