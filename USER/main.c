#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "user_app.h"

 
/************************************************
 ALIENTEK战舰STM32开发板实验4
 串口实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


 int main(void)
 {		
	SystemInit();
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	myuart_init(1,9600);//初始化串口1,用于与wifi模块通信
	myuart_init(2,115200);//初始化串口2
	//myuart_init(3,115200);//初始化串口3
	TIM3_Int_Init(SECOND_1S_TIME,TIME3_10KHZ_PRE);//10Khz的计数频率，计数到9999为1s  
 	LED_Init();			     //LED端口初始化
	//KEY_Init();          //初始化与按键连接的硬件接口
	hal_board_init();//上电输出数据
 	while(1)
	{
		//KEY=keyscan();
		uart_receve_handle();
		event_task_handle();
		delay_ms(20);
	}	 
 }

