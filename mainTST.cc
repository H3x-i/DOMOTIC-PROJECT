#include "uart.h"
#include <stdio.h>


int main(void) {

	uart_init();

	FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL,         _FDEV_SETUP_WRITE);
	FILE uart_input  = FDEV_SETUP_STREAM(NULL,         uart_getchar, _FDEV_SETUP_READ);
	FILE uart_io     = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

	stdout = &uart_output;
	stdin  = &uart_input;

	char input[32];

	while(1) {
		puts("Hello world!");
		//input = getchar();
		scanf("%31s", input);
		printf("You wrote %s\n", input);
	}

    return 0;
}
