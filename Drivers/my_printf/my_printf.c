#include "my_printf.h"

void vprint(const char *fmt, va_list argp, UART_HandleTypeDef *uart2)
{
    char string[200];
	
    if(0 < vsprintf(string,fmt,argp)) // build string
    {
  
      HAL_UART_Transmit(uart2, (uint8_t*)string, strlen(string), HAL_MAX_DELAY); // send message via UART

    }
}

void my_printf(UART_HandleTypeDef *uart2, const char *fmt, ...) // custom printf() function
{
    va_list argp;
	
    va_start(argp, fmt);
	
    vprint(fmt, argp, uart2);
	
    va_end(argp);
}
