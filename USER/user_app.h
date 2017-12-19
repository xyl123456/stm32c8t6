#ifndef __USER_APP_H
#define __USER_APP_H	 

#include "sys.h"


#define HAL_REJEST_LENGTH  					22
#define HAL_HEART_LENGTH   					13
#define HAL_DATAUP_LENGTH           25
#define HAL_MODIFY_LENGTH           13


//��ݵǼ�
typedef union Rejest_up
{
   unsigned char data_buf[22];
   struct rejest_data_t
   {
       unsigned char Head_byte[2];//0xEB 0x90
       unsigned char Data_length[2];//0x00 0x14
       unsigned char Data_type; //���ݵ�����0x02
       unsigned char MAC_addr[4];   //�豸��ַ��Ӳ��ID 
       unsigned char Version[3];//Э��汾�ţ�1.0.0λ0x01,0x00,0x00
       unsigned char HardVersion[3];//Ӳ��Э��汾�ţ�1.0.0λ0x01,0x00,0x00
       unsigned char Heart_time[3];//����ʱ����,Ĭ��30��
       unsigned char Check_code[2];//У���룬��ȥ��ͷ�Ͱ�β�����ֽڵ��ۼӺ�
       unsigned char Tial[2];//0x0D 0x0A
   }data_core;
}Rejest_up_t;


//��ݵǼǷ���
typedef union Rejest_down
{
   unsigned char data_buf[14];
   struct rejestdown_data_t
   {
       unsigned char Head_byte[2];//0xEB 0x90
       unsigned char Data_length[2];//0x00 0x0C
       unsigned char Data_type; //���ݵ�����0x03
       unsigned char MAC_addr[4];   //�豸��ַ��Ӳ��ID 
       unsigned char CMD_code; //�����ֶΣ������Ƿ�Ǽǳɹ����ظ��Ǽǵ�
       unsigned char Check_code[2];//У���룬��ȥ��ͷ�Ͱ�β�����ֽڵ��ۼӺ�
       unsigned char Tial[2];//0x0D 0x0A
   }data_core;
}Rejest_down_t;


//��������
typedef union Heart_up
{
   unsigned char data_buf[13];
   struct head_data_t
   {
       unsigned char Head_byte[2];//0xEB 0x90
       unsigned char Data_length[2];//0x00 0x0B
       unsigned char Data_type; //���ݵ�����0x01
       unsigned char MAC_addr[4];   //�豸��ַ 
       unsigned char Check_code[2];//У���룬��ȥ��ͷ�Ͱ�β�����ֽڵ��ۼӺ�
       unsigned char Tial[2];//0x0D 0x0A
   }data_core;
}Heart_up_t;


//�豸����
typedef union Data_up
{
   unsigned char data_buf[25];
   struct data_up_t
   {
       unsigned char Head_byte[2];//0xEB 0x90
       unsigned char Data_length[2];//0x00 0x17
       unsigned char Data_type; //���ݵ�����0x04
       unsigned char MAC_addr[4];   //�豸��ַ 
       unsigned char PM25[3];//��һ���ֽ�0x01,�����������ݣ�����Ϊ����
       unsigned char PM03[3];//��һ���ֽ�0x0E,�����������ݣ�����Ϊ����
       unsigned char TEM[3];//��һ���ֽ�0x03,������������,����Ϊ1000+����׼��16
       unsigned char HUM[3];//��һ���ֽ�0x04,������������,����Ϊ1000+����׼��16
       unsigned char Check_code[2];//У���룬��ȥ��ͷ�Ͱ�β�����ֽڵ��ۼӺ�
       unsigned char Tial[2];//0x0D 0x0A
   }data_core;
}Data_up_t;


//��������
typedef union Dev_control
{
   unsigned char data_buf[24];
   struct dec_ctl_t
   {
       unsigned char Head_byte[2];//0xEB 0x90
       unsigned char Data_length[2];//0x00 0x16
       unsigned char Data_type; //���ݵ�����0x05
       unsigned char MAC_addr[4];   //�豸��ַ 
       unsigned char Serial_code[8];//������ˮ��
       unsigned char Cmd_code[3];//�����֣����� 81 00 0A ���ػ�81 00 0B
       unsigned char Check_code[2];//У���룬��ȥ��ͷ�Ͱ�β�����ֽڵ��ۼӺ�
       unsigned char Tial[2];//0x0D 0x0A
   }data_core;
}Dev_control_t;

//д���豸ID
typedef union Dev_dp
{
   unsigned char data_buf[13];
   struct dev_dp_t
   {
       unsigned char Head_byte[2];//0xEB 0x90
       unsigned char Data_length[2];//0x00 0x0B
       unsigned char Data_type; //���ݵ�����0xFD
       unsigned char MAC_addr[4];   //�豸��ַ,��λ��ǰ��λ�ں�
       unsigned char Check_code[2];//У���룬��ȥ��ͷ�Ͱ�β�����ֽڵ��ۼӺ�
       unsigned char Tial[2];//0x0D 0x0A
   }data_core;
}Dev_dp_t;

//д���豸ID����
typedef union Dev_up
{
   unsigned char data_buf[13];
   struct dec_up_t
   {
       unsigned char Head_byte[2];//0xEB 0x90
       unsigned char Data_length[2];//0x00 0x0B
       unsigned char Data_type; //���ݵ�����0xFE
       unsigned char MAC_addr[4];   //�豸��ַ 
       unsigned char Check_code[2];//У���룬��ȥ��ͷ�Ͱ�β�����ֽڵ��ۼӺ�
       unsigned char Tial[2];//0x0D 0x0A
   }data_core;
}Dev_up_t;


//����PM2.5����
typedef union PM25_up
{
   unsigned char data_buf[32];
   struct pm25_up_t
   {
       unsigned char Head_byte[2];//0x42 0x4D
       unsigned char Data_length[2];//0x00 0x1c
       unsigned char pm1_bz[2]; //pm1.0��׼������ug/m3
       unsigned char pm25_bz[2];   //pm2.5��׼������ug/m3
       unsigned char pm10_bz[2];   //pm10��׼������ug/m3
       unsigned char pm1_dq[2]; //pm1.0��������ug/m3
       unsigned char pm25_dq[2];   //pm2.5��������ug/m3
       unsigned char pm10_dq[2];   //pm10��������ug/m3
       unsigned char pm03_kq[2]; //pm0.3 0.1������������
       unsigned char pm05_kq[2]; //pm0.5 0.1������������
       unsigned char pm1_kq[2]; //pm1.0 0.1������������
       unsigned char pm25_kq[2];//pm2.5 0.1������������
       unsigned char pm5_kq[2];//pm5 0.1������������
       unsigned char pm10_kq[2];//pm10 0.1������������
       unsigned char bb_code;  //�汾��0x91
       unsigned char error_code;  //������0x00
       unsigned char Check_code[2];//У���룬��ȥ��ͷ�Ͱ�β�����ֽڵ��ۼӺ�
   }data_core;
}PM25_up_t;

void send_rejest_data(void);
uint16_t  Sum_data(unsigned char buf[],int start,int stop);
void send_serial_data(void);
void send_heart_data(void);

void App_process_uart(u8 port,u8 buf[],u8 len);


extern void myuart_init(u8 port,u32 bound);
extern void uart_receve_handle(void);

extern void hal_board_init(void);
extern void event_task_handle(void);		    
#endif
