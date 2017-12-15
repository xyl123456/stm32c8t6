#ifndef __USER_APP_H
#define __USER_APP_H	 

#include "sys.h"


#define HAL_REJEST_LENGTH  22
#define HAL_HEART_LENGTH   13
//身份登记
typedef union Rejest_up
{
   unsigned char data_buf[22];
   struct rejest_data_t
   {
       unsigned char Head_byte[2];//0xEB 0x90
       unsigned char Data_length[2];//0x00 0x14
       unsigned char Data_type; //数据的类型0x02
       unsigned char MAC_addr[4];   //设备地址，硬件ID 
       unsigned char Version[3];//协议版本号，1.0.0位0x01,0x00,0x00
       unsigned char HardVersion[3];//硬件协议版本号，1.0.0位0x01,0x00,0x00
       unsigned char Heart_time[3];//心跳时间间隔,默认30秒
       unsigned char Check_code[2];//校验码，除去包头和包尾所有字节的累加和
       unsigned char Tial[2];//0x0D 0x0A
   }data_core;
}Rejest_up_t;


//身份登记返回
typedef union Rejest_down
{
   unsigned char data_buf[14];
   struct rejestdown_data_t
   {
       unsigned char Head_byte[2];//0xEB 0x90
       unsigned char Data_length[2];//0x00 0x0C
       unsigned char Data_type; //数据的类型0x03
       unsigned char MAC_addr[4];   //设备地址，硬件ID 
       unsigned char CMD_code; //命令字段，解释是否登记成功，重复登记等
       unsigned char Check_code[2];//校验码，除去包头和包尾所有字节的累加和
       unsigned char Tial[2];//0x0D 0x0A
   }data_core;
}Rejest_down_t;


//心跳命令
typedef union Heart_up
{
   unsigned char data_buf[13];
   struct head_data_t
   {
       unsigned char Head_byte[2];//0xEB 0x90
       unsigned char Data_length[2];//0x00 0x0B
       unsigned char Data_type; //数据的类型0x01
       unsigned char MAC_addr[4];   //设备地址 
       unsigned char Check_code[2];//校验码，除去包头和包尾所有字节的累加和
       unsigned char Tial[2];//0x0D 0x0A
   }data_core;
}Heart_up_t;


//设备数据
typedef union Data_up
{
   unsigned char data_buf[31];
   struct data_up_t
   {
       unsigned char Head_byte[2];//0xEB 0x90
       unsigned char Data_length[2];//0x00 0x17
       unsigned char Data_type; //数据的类型0x04
       unsigned char MAC_addr[4];   //设备地址 
       unsigned char PM25[3];//第一个字节0x01,后两个是数据，数据为整数
       unsigned char PM03[3];//第一个字节0x0E,后两个是数据，数据为整数
       unsigned char TEM[3];//第一个字节0x03,后两个是数据,数据为1000+数据准换16
       unsigned char HUM[3];//第一个字节0x04,后两个是数据,数据为1000+数据准换16
       unsigned char POW[3];//第一个字节0x0A,后两个是数据，数据为百分比
       unsigned char POW_STA[3];//如果充电则为0X01，不充电为0x00
       unsigned char Check_code[2];//校验码，除去包头和包尾所有字节的累加和
       unsigned char Tial[2];//0x0D 0x0A
   }data_core;
}Data_up_t;


//控制命令
typedef union Dev_control
{
   unsigned char data_buf[24];
   struct dec_ctl_t
   {
       unsigned char Head_byte[2];//0xEB 0x90
       unsigned char Data_length[2];//0x00 0x18
       unsigned char Data_type; //数据的类型0x05
       unsigned char MAC_addr[4];   //设备地址 
       unsigned char Serial_code[8];//命令流水号
       unsigned char Cmd_code[3];//命令字，开机 81 00 0A ，关机81 00 0B
       unsigned char Check_code[2];//校验码，除去包头和包尾所有字节的累加和
       unsigned char Tial[2];//0x0D 0x0A
   }data_core;
}Dev_control_t;

//写入设备ID
typedef union Dev_dp
{
   unsigned char data_buf[13];
   struct dev_dp_t
   {
       unsigned char Head_byte[2];//0xEB 0x90
       unsigned char Data_length[2];//0x00 0x0B
       unsigned char Data_type; //数据的类型0xFD
       unsigned char MAC_addr[4];   //设备地址,高位在前地位在后
       unsigned char Check_code[2];//校验码，除去包头和包尾所有字节的累加和
       unsigned char Tial[2];//0x0D 0x0A
   }data_core;
}Dev_dp_t;

//写入设备ID返回
typedef union Dev_up
{
   unsigned char data_buf[13];
   struct dec_up_t
   {
       unsigned char Head_byte[2];//0xEB 0x90
       unsigned char Data_length[2];//0x00 0x0D
       unsigned char Data_type; //数据的类型0xFE
       unsigned char MAC_addr[4];   //设备地址 
       unsigned char Check_code[2];//校验码，除去包头和包尾所有字节的累加和
       unsigned char Tial[2];//0x0D 0x0A
   }data_core;
}Dev_up_t;


//激光PM2.5数据
typedef union PM25_up
{
   unsigned char data_buf[32];
   struct pm25_up_t
   {
       unsigned char Head_byte[2];//0x42 0x4D
       unsigned char Data_length[2];//0x00 0x1c
       unsigned char pm1_bz[2]; //pm1.0标准颗粒物ug/m3
       unsigned char pm25_bz[2];   //pm2.5标准颗粒物ug/m3
       unsigned char pm10_bz[2];   //pm10标准颗粒物ug/m3
       unsigned char pm1_dq[2]; //pm1.0大气环境ug/m3
       unsigned char pm25_dq[2];   //pm2.5大气环境ug/m3
       unsigned char pm10_dq[2];   //pm10大气环境ug/m3
       unsigned char pm03_kq[2]; //pm0.3 0.1升空气颗粒数
       unsigned char pm05_kq[2]; //pm0.5 0.1升空气颗粒数
       unsigned char pm1_kq[2]; //pm1.0 0.1升空气颗粒数
       unsigned char pm25_kq[2];//pm2.5 0.1升空气颗粒数
       unsigned char pm5_kq[2];//pm5 0.1升空气颗粒数
       unsigned char pm10_kq[2];//pm10 0.1升空气颗粒数
       unsigned char bb_code;  //版本号0x91
       unsigned char error_code;  //错误码0x00
       unsigned char Check_code[2];//校验码，除去包头和包尾所有字节的累加和
   }data_core;
}PM25_up_t;

void send_rejest_data(void);
uint16_t  Sum_data(unsigned char buf[],int start,int stop);
void send_serial_data(void);
extern void hal_board_init(void);
extern void event_task_handle(void);		    
#endif
