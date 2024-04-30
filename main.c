#include "sys.h"

int main(){
	UARTInit(115200);
	ledInit();
	delayInit();
	ledon;
	while(1){
		ledoff;
		user_main_info("test1\n");
		user_main_info("test2\n");
		delay_ms(1000);
		ledon;
		delay_ms(1000);
	}
}

