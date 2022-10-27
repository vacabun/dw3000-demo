//
// Created by maguo on 2022/7/28.
//

#include "printf.h"
#include <stdarg.h>
#include "usart.h"
#include "usbd_cdc_if.h"
extern uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];

PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART2 and Loop until the end of transmission */
    HAL_UART_Transmit(&huart1,(uint8_t *)&ch,1,0xFFFF);
    return ch;
}

void usb_printf(const char *format, ...)
{
    va_list args;
    uint32_t length;

    va_start(args, format);
    length = vsnprintf((char *)UserTxBufferFS, APP_TX_DATA_SIZE, (char *)format, args);
    va_end(args);
    CDC_Transmit_FS(UserTxBufferFS, length);

}
