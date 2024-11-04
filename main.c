#include "kernel.h"

#define BASEADDRESS2 0x8008000
#define BASEADDRESS1 0x8010000
#define BASEADDRESS3 0x8018000
#define QUANTA			 100

static void (*program1)(void) = (void (*) (void))0x8008000;
static void (*program2)(void) = (void (*) (void))0x8010000;
static void (*program3)(void) = (void (*) (void))0x8018000;

int main(){
	osKernelInit();
	osKernelAddProcess(program1);
	osKernelAddProcess(program2);
	osKernelAddProcess(program3);
	osKernelLaunch(QUANTA);
	while(1){
	
	}
}