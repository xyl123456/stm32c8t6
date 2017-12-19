#include "user_app.h"
#include "usart.h"
#include "timer.h"
#include "malloc.h"	
#include "led.h"
#include "delay.h"
#include "key.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "stmflash.h"



//注册信息数据
unsigned char HEARD_DATA[2]={0xEB,0x90};
unsigned char HEARD_LENGTH[2]={0x00,0x14};
unsigned char DEV_MAC_ADDR[4]={0x00,0x00,0x00,0x00};
unsigned char VERSION[3]={0x20,0x00,0x00};
unsigned char HARD_VERSION[3]={0x10,0x00,0x00};
unsigned char HEART_TIME[3]={0x00,0x00,0x1E};
unsigned char TAIL_DATA[2]={0x0D,0x0A};

//心跳数据
unsigned char HEART_LENGTH[2]={0x00,0x0B};
//数据上报
unsigned char UPDATA_LENGTH[2]={0x00,0x17};
unsigned char PM25_DATA[3]={0x01,0x00,0x2F};
unsigned char PM03_DATA[3]={0x0E,0x00,0x14};
unsigned char TEM_DATA[3]={0x03,0x03,0xFB};
unsigned char HUM_DATA[3]={0x04,0x00,0x35};

unsigned char datatemp[4];


uint16_t  Sum_data(unsigned char buf[],int start,int stop){
	uint16_t sum_data=0;
	int i;
	for(i=start;i<=stop;i++){
		sum_data=sum_data+buf[i];
	}
	return sum_data;

}
//注册数据上报
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

	check_data=Sum_data(rejest_up_t.data_buf,2,HAL_REJEST_LENGTH-5);
	check_buf[0]=check_data>>8;
  check_buf[1]=check_data;
	
	mymemcpy(rejest_up_t.data_core.Check_code,check_buf,2);
	mymemcpy(rejest_up_t.data_core.Tial,TAIL_DATA,2);
   
	myuart_send(HAL_UART2,rejest_up_t.data_buf,HAL_REJEST_LENGTH);
}

void hal_board_init(void) {
	USART_GetFlagStatus(USART1, USART_FLAG_TC);
	USART_GetFlagStatus(USART2, USART_FLAG_TC);
	//读取flash中设备地址 4 byte
	STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)DEV_MAC_ADDR,4);
	
	//STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)DEV_MAC_ADDR,4);
	send_rejest_data();
	
}
//心跳数据上报
void send_heart_data(void){
	uint16_t check_data;
	unsigned char check_buf[2];
	Heart_up_t heart_up_t;
	mymemcpy(heart_up_t.data_core.Head_byte,HEARD_DATA,2);
	mymemcpy(heart_up_t.data_core.Data_length,HEART_LENGTH,2);
	heart_up_t.data_core.Data_type=0x01;
	mymemcpy(heart_up_t.data_core.MAC_addr,DEV_MAC_ADDR,4);
	
	check_data=Sum_data(heart_up_t.data_buf,2,HAL_HEART_LENGTH-5);
	check_buf[0]=check_data>>8;
  check_buf[1]=check_data;
	mymemcpy(heart_up_t.data_core.Check_code,check_buf,2);
	mymemcpy(heart_up_t.data_core.Tial,TAIL_DATA,2);
	
	myuart_send(HAL_UART1,heart_up_t.data_buf,HAL_HEART_LENGTH);
	
}

void send_serial_data(void) {
	uint16_t check_data;
	unsigned char check_buf[2];
	Data_up_t data_up_t;
	mymemcpy(data_up_t.data_core.Head_byte,HEARD_DATA,2);
	mymemcpy(data_up_t.data_core.Data_length,UPDATA_LENGTH,2);
	data_up_t.data_core.Data_type=0x04;
	mymemcpy(data_up_t.data_core.MAC_addr,DEV_MAC_ADDR,4);
	mymemcpy(data_up_t.data_core.PM25,PM25_DATA,3);
	mymemcpy(data_up_t.data_core.PM03,PM03_DATA,3);
	mymemcpy(data_up_t.data_core.TEM,TEM_DATA,3);
	mymemcpy(data_up_t.data_core.HUM,HUM_DATA,3);
	
	check_data=Sum_data(data_up_t.data_buf,2,HAL_DATAUP_LENGTH-5);
	check_buf[0]=check_data>>8;
  check_buf[1]=check_data;
	
	mymemcpy(data_up_t.data_core.Check_code,check_buf,2);
	mymemcpy(data_up_t.data_core.Tial,TAIL_DATA,2);
	
	myuart_send(HAL_UART1,data_up_t.data_buf,HAL_DATAUP_LENGTH);
	
	//STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,4);
	
	//myuart_send(HAL_UART2,datatemp,4);
	
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


void App_process_uart(u8 port,u8 buf[],u8 len){
	uint16_t check_data;
	unsigned char check_buf[2];
	check_data=Sum_data(buf,2,len-5);
	check_buf[0]=check_data>>8;
	check_buf[1]=check_data;
	if(mymemcmp(buf+(len-4),check_buf,2)==0){
		
	if(port==HAL_UART1){
		//串口1用于通信，处理下发的控制命令
		if((len==HAL_MODIFY_LENGTH)&(buf[4]==0xFD)){
			//修改设备ID
		Dev_dp_t dev_dp_t;//接收的数据
		Dev_up_t dev_up_t;//串口返回上报的数据
		mymemcpy(dev_dp_t.data_buf,buf,len);
		mymemcpy(dev_up_t.data_buf,buf,len);	
			
		mymemcpy(DEV_MAC_ADDR,dev_dp_t.data_core.MAC_addr,4);	
		STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)DEV_MAC_ADDR,4);	
		//返回设置地址数据
		dev_up_t.data_core.Data_type=0xFE;
		check_data=Sum_data(dev_up_t.data_buf,2,len-5);
		check_buf[0]=check_data>>8;
		check_buf[1]=check_data;
		mymemcpy(dev_up_t.data_core.Check_code,check_buf,2);
			
		myuart_send(HAL_UART1,dev_up_t.data_buf,HAL_MODIFY_LENGTH);
		}
	}else if(port==HAL_UART2){
		//处理串口2接收的数据---串口类型的设备：PM2.5等
		
	}
}else {
	len =0;
	mymemset(buf,0,sizeof((u8*)buf));
}	
}

//串口处理回调函数
void uart_receve_handle(void)
{
	if(USART_RX_STA&0x8000)
		{	
			u8 uart_len;
			u8 uart_commandbuf[USART_REC_LEN];
			uart_len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			mymemcpy(uart_commandbuf,USART_RX_BUF,uart_len);
			
			App_process_uart(HAL_UART1,uart_commandbuf,uart_len);
			
			//myuart_send(HAL_UART1,uart_commandbuf,uart_len);
			
			USART_RX_STA=0;
			mymemset(uart_commandbuf,0,USART_REC_LEN);
		}
		if(USART2_RX_STA&0x8000)
		{	
			u8 uart2_len;
			u8 uart2_commandbuf[USART_REC_LEN];
			uart2_len=USART2_RX_STA&0x3fff;//得到此次接收到的数据长度
			mymemcpy(uart2_commandbuf,USART2_RX_BUF,uart2_len);
			myuart_send(HAL_UART2,uart2_commandbuf,uart2_len);
			USART2_RX_STA=0;
			mymemset(uart2_commandbuf,0,USART_REC_LEN);
		}	
		if(USART3_RX_STA&0x8000)
		{	
			u8 uart3_len;
			u8 uart3_commandbuf[USART_REC_LEN];
			uart3_len=USART3_RX_STA&0x3fff;//得到此次接收到的数据长度

			mymemcpy(uart3_commandbuf,USART3_RX_BUF,uart3_len);
			myuart_send(3,uart3_commandbuf,uart3_len);

			USART3_RX_STA=0;
			mymemset(uart3_commandbuf,0,USART_REC_LEN);
		}	
		
}
