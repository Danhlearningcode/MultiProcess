#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "stm32f10x.h"                  // Device header
#include <stdint.h>
#include <stdio.h>
/* SysTick Resgister Define */
//Clock freq for SysTick
#define BUS_FREQ 			72000000 
//Cho phep bo dem sysTick Hoat Dong
#define CTRL_ENABLE 			(1<<0)
//Cho Phep Ngat Systick
#define CTRL_TICKINT 			(1<<1)
//Chon nguon cap xung clock cho Systick
#define CTRL_CLCKSRC 			(1<<2)
//Set co ngat Systick
#define CTRL_COUNTFLAG 		(1<<16)
//Gia tri Reset cho systick
#define SYSTICK_RST 			0

#define STACK_SIZE 			100 
//Khai bao so luong thread 
#define MAX_NUM_OF_PROCESS		3

struct tcb{
	uint32_t *stackPt;
	struct tcb* nextPt;
	uint32_t BaseAddress;
};

typedef struct tcb tcbType;

void osKernelInit(void);
void osKernelLaunch(uint32_t quanta);
uint8_t osKernelAddProcess(void (*task)(void));
void osKernelStackInit(int i);
void osStart(void);


#endif
