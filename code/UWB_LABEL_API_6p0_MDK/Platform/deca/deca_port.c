#include <deca_port.h>

SPI_HandleTypeDef   *hcurrent_active_spi=&hspi1;//Is the current active SPI pointer - 1 or 2
GPIO_TypeDef* 			pin_port_active_spi = SPI1_CS_GPIO_Port;
uint16_t            pin_io_active_spi=SPI1_CS_Pin;//CS IO for SPI. Default SPI1
GPIO_PinState       SPI_CS_state=GPIO_PIN_RESET;//Determine the CS for the IO

/* @fn      disable_DW_EXT_IRQ
 * @brief   wrapper to disable DW_IRQ pin IRQ
 * */
__INLINE void disable_DW_EXT_IRQ(void)
{
    NVIC_DisableIRQ(EXTI0_IRQn);
}

/* @fn      port_EnableEXT_IRQ
 * @brief   wrapper to enable DW_IRQ pin IRQ
 *          in current implementation it enables all IRQ from lines 5:9
 * */
__INLINE void enable_DW_EXT_IRQ(void)
{

	NVIC_EnableIRQ(EXTI0_IRQn);
}

/**
 * @brief  Checks whether the specified IRQn line is enabled or not.
 * @param  IRQn: specifies the IRQn line to check.
 * @return "0" when IRQn is "not enabled" and !0 otherwise
 */
ITStatus EXTI_GetITEnStatus(IRQn_Type IRQn)
{
    return ((NVIC->ISER[(((uint32_t)(int32_t)IRQn) >> 5UL)] & (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL))) == (uint32_t)RESET) ? (RESET) : (SET);
}

/* @fn      port_GetEXT_IRQStatus
 * @brief   wrapper to read a DW_IRQ pin IRQ status
 * */
__INLINE uint32_t get_DW_EXT_IRQStatus(void)
{

   return EXTI_GetITEnStatus(EXTI0_IRQn);
}

/* @fn    usleep
 * @brief precise usleep() delay
 * */
#pragma GCC optimize("O0")
void usleep(uint32_t usec)
{
    uint32_t i;

    usec *= 12;
    for (i = 0; i < usec; i++)
    {
        __NOP();
    }
}

/* @fn    Sleep
 * @brief Sleep delay in ms using SysTick timer
 * */
__INLINE void Sleep(uint32_t x)
{
    HAL_Delay(x);
}

/* @fn      port_set_dw_ic_spi_slowrate
 * @brief   set 4.5MHz
 *          note: hspi1 is clocked from 72MHz
 * */
void set_dw_ic_spi_slowrate(void)
{
    hcurrent_active_spi->Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_16;
    HAL_SPI_Init(hcurrent_active_spi);
}

/* @fn      port_set_dw_ic_spi_fastrate
 * @brief   set 18MHz
 *          note: hspi1 is clocked from 72MHz
 * */
void set_dw_ic_spi_fastrate(void)
{
    hcurrent_active_spi->Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_2;
    HAL_SPI_Init(hcurrent_active_spi);
}


/* @fn      reset_DW IC
 * @brief   DW_RESET pin on DW IC has 2 functions
 *          In general it is output, but it also can be used to reset the digital
 *          part of DW IC by driving this pin low.
 *          Note, the DW_RESET pin should not be driven high externally.
 * */
void reset_DWIC(void)
{
    // drive the RSTn pin low
    HAL_GPIO_WritePin(DW_RSTn_GPIO_Port, DW_RSTn_Pin, GPIO_PIN_RESET);

    usleep(1);

    // drive the RSTn pin high
    HAL_GPIO_WritePin(DW_RSTn_GPIO_Port, DW_RSTn_Pin, GPIO_PIN_SET);
	
    Sleep(2);
}

/*! ------------------------------------------------------------------------------------------------------------------
 * @fn wakeup_device_with_io()
 *
 * @brief This function wakes up the device by toggling io with a delay.
 *
 * input None
 *
 * output -None
 *
 */
#define WAIT_200uSEC Sleep(1) /*This is should be a delay of 200uSec at least. In our example it is more than that*/
void wakeup_device_with_io(void)
{
	  HAL_GPIO_WritePin(UWB_WAKEUP_GPIO_Port, UWB_WAKEUP_Pin, GPIO_PIN_SET);
    WAIT_200uSEC;
	  HAL_GPIO_WritePin(UWB_WAKEUP_GPIO_Port, UWB_WAKEUP_Pin, GPIO_PIN_RESET);
}