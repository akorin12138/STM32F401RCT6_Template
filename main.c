#include "sys.h"
int main(){
	UARTInit(115200);
	ledInit();
	delayInit();
	rtos_init();

while(1){}
}

