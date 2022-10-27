#ifndef DECA_PORT_H_
#define DECA_PORT_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include "spi.h"

void disable_DW_EXT_IRQ(void);
void enable_DW_EXT_IRQ(void);
ITStatus EXTI_GetITEnStatus(IRQn_Type IRQn);
uint32_t get_DW_EXT_IRQStatus(void);
void usleep(uint32_t usec);
void Sleep(uint32_t x);
void reset_DWIC(void);
void set_dw_ic_spi_slowrate(void);
void set_dw_ic_spi_fastrate(void);
void wakeup_device_with_io(void);
#endif
