//
// Created by maguo on 2022/7/28.
//

#ifndef UWB_UAV_LABEL_PRINTF_H
#define UWB_UAV_LABEL_PRINTF_H

#include "stdio.h"


#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */



void usb_printf(const char *format, ...);

#endif //UWB_UAV_LABEL_PRINTF_H
