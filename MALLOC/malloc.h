#ifndef __MALLOC_H
#define __MALLOC_H
#include "stm32f10x.h"
#include "string.h"


void mymemset(void *s,u8 c,u32 count);	//�����ڴ�
void mymemcpy(void *des,void *src,u32 n);//�����ڴ�     
extern int mymemcmp(void *str1,void *str2,int len);//�Ƚ��ڴ�

#endif



