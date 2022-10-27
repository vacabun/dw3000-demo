#ifndef DECA_PORT_H_
#define DECA_PORT_H_
#include <stdint.h>
#include <string.h>
#include "sys/types.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include "spi.h"

extern SPI_HandleTypeDef    *hcurrent_active_spi;/*clocked from 72MHz*/
extern GPIO_TypeDef* 		pin_port_active_spi;
extern uint16_t             pin_io_active_spi;
extern GPIO_PinState        SPI_CS_state;

typedef enum
{
    SPI_1=0,
    SPI_2
}host_using_spi_e;

typedef enum
{
    LED_PC6, // LED5
    LED_PC7, // LED6
    LED_PC8, // LED7
    LED_PC9, // LED8
    LED_ALL,
    LEDn
} led_t;

typedef void (*port_dwic_isr_t)(void);

#define WAIT_500uSEC Sleep(1) /*This is should be a delay of 500uSec at least. In our example it is more than that*/
#define WAIT_200uSEC Sleep(1) /*This is should be a delay of 200uSec at least. In our example it is more than that*/

uint32_t portGetTickCnt(void);
int usleep(useconds_t usec);
void Sleep(uint32_t x);
int peripherals_init(void);
void spi_peripheral_init();
ITStatus EXTI_GetITEnStatus(IRQn_Type IRQn);
void reset_DWIC(void);
void setup_DWICRSTnIRQ(int enable);
void wakeup_device_with_io(void);
void make_very_short_wakeup_io(void);
int port_is_boot1_low(void);
int port_is_boot1_on(uint16_t x);
int port_is_switch_on(uint16_t GPIOpin);
void led_off(led_t led);
void led_on(led_t led);
void change_SPI(host_using_spi_e spi);
void port_set_dw_ic_spi_slowrate(void);
void port_set_dw_ic_spi_fastrate(void);
void port_LCD_RS_set(void);
void port_LCD_RS_clear(void);
void port_LCD_RW_set(void);
void port_LCD_RW_clear(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void process_deca_irq(void);
void port_DisableEXT_IRQ(void);
void port_EnableEXT_IRQ(void);
uint32_t port_GetEXT_IRQStatus(void);
uint32_t port_CheckEXT_IRQ(void);



#endif
