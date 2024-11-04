#include "kernel.h"
//Khai bao kich co Stack cho moi thread 

static uint32_t MILLIS_PRESCALER;
static tcbType tcbs[MAX_NUM_OF_PROCESS];
tcbType *currentPt;
static int Current_Process_Num = 0;
static uint32_t TCB_STACK[MAX_NUM_OF_PROCESS][STACK_SIZE];

void osKernelInit(void){
	//1ms
	MILLIS_PRESCALER = (BUS_FREQ/1000);
}
void osKernelLaunch(uint32_t quanta){
    SysTick->CTRL = SYSTICK_RST;
    SysTick->VAL = 0;
    SysTick->LOAD = (quanta * MILLIS_PRESCALER - 1);
    NVIC_SetPriority(SysTick_IRQn, 15);
    SysTick->CTRL |= CTRL_CLCKSRC | CTRL_ENABLE;
    SysTick->CTRL |= CTRL_TICKINT;
    osStart();
}
uint8_t osKernelAddProcess(void (*task)(void)){
    __disable_irq();  
    tcbs[Current_Process_Num].BaseAddress = (uint32_t)(task);
    osKernelStackInit(Current_Process_Num);
    if (!Current_Process_Num) {
        tcbs[Current_Process_Num].nextPt = &tcbs[Current_Process_Num];
    } else {
        tcbs[Current_Process_Num - 1].nextPt = &tcbs[Current_Process_Num];
        tcbs[Current_Process_Num].nextPt = &tcbs[0];
    }
    currentPt = &tcbs[0];
    Current_Process_Num++;
    __enable_irq();  

    return 1;  
}
void osKernelStackInit(int i){
    tcbs[i].stackPt = &TCB_STACK[i][STACK_SIZE - 16];  /* StackPointer points to base of stack frame */

    TCB_STACK[i][STACK_SIZE-1] = 1 << 24;  
    TCB_STACK[i][STACK_SIZE - 2] = *(volatile uint32_t *)(tcbs[i].BaseAddress + 4);
	
    TCB_STACK[i][STACK_SIZE-3] = 0x14141414;   /* Register R14 (Link Register, LR) */
    TCB_STACK[i][STACK_SIZE-4] = 0x12121212;   /* Register R12 */
    TCB_STACK[i][STACK_SIZE-5] = 0x03030303;   /* Register R3 */
    TCB_STACK[i][STACK_SIZE-6] = 0x02020202;   /* Register R2 */
    TCB_STACK[i][STACK_SIZE-7] = 0x01010101;   /* Register R1 */
    TCB_STACK[i][STACK_SIZE-8] = 0x00000000;   /* Register R0 */

    /* Initialize remaining registers R4-R11 */
    TCB_STACK[i][STACK_SIZE-9] = 0x11111111;   /* Register R11 */
    TCB_STACK[i][STACK_SIZE-10] = 0x10101010;  /* Register R10 */
    TCB_STACK[i][STACK_SIZE-11] = 0x09090909;  /* Register R9 */
    TCB_STACK[i][STACK_SIZE-12] = 0x08080808;  /* Register R8 */
    TCB_STACK[i][STACK_SIZE-13] = 0x07070707;  /* Register R7 */
    TCB_STACK[i][STACK_SIZE-14] = 0x06060606;  /* Register R6 */
    TCB_STACK[i][STACK_SIZE-15] = 0x05050505;  /* Register R5 */
    TCB_STACK[i][STACK_SIZE-16] = 0x04040404;  /* Register R4 */
}


