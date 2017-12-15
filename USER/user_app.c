#include "user_app.h"
#include "usart.h"
#include "timer.h"
#include "malloc.h"	
#include "led.h"
#include "delay.h"
#include "key.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"

//注册信息数据
unsigned char HEARD_DATA[2]={0xEB,0x90};
unsigned char HEARD_LENGTH[2]={0x00,0x14};
unsigned char DEV_MAC_ADDR[4]={0x00,0x00,0x00,0x00};
unsigned char VERSION[3]={0x01,0x00,0x00};
unsigned char HARD_VERSION[3]={0x01,0x00,0x00};
unsigned char HEART_TIME[3]={0x00,0x00,0x1E};
unsigned char TAIL_DATA[2]={0x0D,0x0A};

//心跳数据
unsigned char HEART_LENGTH[2]={0x00,0x0E};



uint16_t  Sum_data(unsigned char buf[],int start,int stop){
	uint16_t sum_data=0;
	int i;
	for(i=start;i<stop;i++){
		sum_data=sum_data+buf[i];
	}
	return sum_data;

}

void send_rejest_data(void){
	uint16_t check_data;
	unsigned char check_buf[2];
	Rejest_up_t rejest_up_t;
	mymemcpy(rejest_up_t.data_core.Head_byte,HEARD_DATA,2);
	mymemcpy(rejest_up_t.data_core.Data_length,HEARD_LENGTH,2);
	rejest_up_t.data_core.Data_type=0x02;
	mymemcpy(rejest_up_t.data_core.MAC_addr,DEV_MAC_ADDR,4);
	mymemcpy(rejest_up_t.data_core.Version,VERSION,3);
	mymemcpy(rejest_up_t.data_core.HardVersion,HARD_VERSION,3);
	mymemcpy(rejest_up_t.data_core.Heart_time,HEART_TIME,3);

	check_data=Sum_data(rejest_up_t.data_buf,2,16);
	check_buf[0]=check_data>>8;
  check_buf[1]=check_data;
	
	mymemcpy(rejest_up_t.data_core.Check_code,check_buf,2);
	mymemcpy(rejest_up_t.data_core.Tial,TAIL_DATA,2);
   
	myuart_send(HAL_UART2,rejest_up_t.data_buf,HAL_REJEST_LENGTH);
}

void hal_board_init(void) {
	unsigned char start_buf[1]={0xFF};
	myuart_send(HAL_UART2,start_buf,1);
	send_rejest_data();
}

void send_heart_data(void){
	uint16_t check_data;
	unsigned char check_buf[2];
	Heart_up_t heart_up_t;
	mymemcpy(heart_up_t.data_core.Head_byte,HEARD_DATA,2);
	mymemcpy(heart_up_t.data_core.Data_length,HEART_LENGTH,2);
	heart_up_t.data_core.Data_type=0x01;
	mymemcpy(heart_up_t.data_core.MAC_addr,DEV_MAC_ADDR,4);
	
	check_data=Sum_data(heart_up_t.data_buf,2,7);
	check_buf[0]=check_data>>8;
  check_buf[1]=check_data;
	mymemcpy(heart_up_t.data_core.Check_code,check_buf,2);
	mymemcpy(heart_up_t.data_core.Tial,TAIL_DATA,2);
	
	myuart_send(HAL_UART2,heart_up_t.data_buf,HAL_HEART_LENGTH);
	
}
void send_serial_data(void) {
	
	
}

void event_task_handle(void) {
	if(sys_event_flag&SEND_SERIAL_EVENT){
		//处理数据上报信息
		send_serial_data();
		sys_event_flag ^=SEND_SERIAL_EVENT;
	}
	if(sys_event_flag&HEART_SERIAL_EVENT){
		//心跳事件
		send_heart_data();
		sys_event_flag ^=HEART_SERIAL_EVENT;
	}
}

