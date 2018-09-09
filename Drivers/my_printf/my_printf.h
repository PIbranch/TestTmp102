 #ifndef __MY_PRINTF_H
 #define __MY_PRINTF_H

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "main.h"

void vprint(const char *fmt, va_list argp, UART_HandleTypeDef *uart2);

 // custom printf() function
void my_printf(UART_HandleTypeDef *uart2, const char *fmt, ...);


#endif

