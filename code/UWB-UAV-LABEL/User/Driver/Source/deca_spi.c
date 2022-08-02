/*! ----------------------------------------------------------------------------
 * @file    deca_spi.c
 * @brief   SPI access functions
 *
 * @attention
 *
 * Copyright 2015-2020 (c) DecaWave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 * @author DecaWave
 */

#include <deca_spi.h>
#include <deca_device_api.h>
#include "spi.h"


/* @fn      port_DisableEXT_IRQ
 * @brief   wrapper to disable DW_IRQ pin IRQ
 *          in current implementation it disables all IRQ from lines 5:9
 * */
__INLINE void port_DisableEXT_IRQ(void)
{
    NVIC_DisableIRQ(EXTI0_IRQn);
}

/* @fn      port_EnableEXT_IRQ
 * @brief   wrapper to enable DW_IRQ pin IRQ
 *          in current implementation it enables all IRQ from lines 5:9
 * */
__INLINE void port_EnableEXT_IRQ(void)
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
    return ((NVIC->ISER[(((uint32_t)(int32_t)IRQn) >> 5UL)] &\
            (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL)) ) == (uint32_t)RESET)?(RESET):(SET);

}

/* @fn      port_GetEXT_IRQStatus
 * @brief   wrapper to read a DW_IRQ pin IRQ status
 * */
__INLINE uint32_t port_GetEXT_IRQStatus(void)
{
    return EXTI_GetITEnStatus(EXTI0_IRQn);
}


/*! ------------------------------------------------------------------------------------------------------------------
 * Function: decamutexon()
 *
 * Description: This function should disable interrupts. This is called at the start of a critical section
 * It returns the irq state before disable, this value is used to re-enable in decamutexoff call
 *
 * Note: The body of this function is defined in deca_mutex.c and is platform specific
 *
 * input parameters:
 *
 * output parameters
 *
 * returns the state of the DW1000 interrupt
 */
decaIrqStatus_t decamutexon(void)
{
    decaIrqStatus_t s = port_GetEXT_IRQStatus();

    if(s) {
        port_DisableEXT_IRQ(); //disable the external interrupt line
    }
    return s ;   // return state before disable, value is used to re-enable in decamutexoff call
}

/*! ------------------------------------------------------------------------------------------------------------------
 * Function: decamutexoff()
 *
 * Description: This function should re-enable interrupts, or at least restore their state as returned(&saved) by decamutexon
 * This is called at the end of a critical section
 *
 * Note: The body of this function is defined in deca_mutex.c and is platform specific
 *
 * input parameters:
 * @param s - the state of the DW1000 interrupt as returned by decamutexon
 *
 * output parameters
 *
 * returns the state of the DW1000 interrupt
 */
void decamutexoff(decaIrqStatus_t s)        // put a function here that re-enables the interrupt at the end of the critical section
{
    if(s) { //need to check the port state as we can't use level sensitive interrupt on the STM ARM
        port_EnableEXT_IRQ();
    }
}


/*! ------------------------------------------------------------------------------------------------------------------
 * Function: writetospiwithcrc()
 *
 * Low level abstract function to write to the SPI when SPI CRC mode is used
 * Takes two separate byte buffers for write header and write data, and a CRC8 byte which is written last
 * returns 0 for success, or -1 for error
 */
int writetospiwithcrc(
                uint16_t      headerLength,
                const uint8_t *headerBuffer,
                uint16_t      bodyLength,
                const uint8_t *bodyBuffer,
                uint8_t       crc8)
{
    decaIrqStatus_t  stat ;
    stat = decamutexon() ;
    while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);

    HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET); /**< Put chip select line low */

    HAL_SPI_Transmit(&hspi1, (uint8_t *)headerBuffer, headerLength, 10);    /* Send header in polling mode */
    HAL_SPI_Transmit(&hspi1, (uint8_t *)bodyBuffer, bodyLength, 10);        /* Send data in polling mode */
    HAL_SPI_Transmit(&hspi1, (uint8_t *)&crc8, 1, 10);      /* Send data in polling mode */

    HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET); /**< Put chip select line high */
    decamutexoff(stat);
    return 0;
} // end writetospiwithcrc()


/*! ------------------------------------------------------------------------------------------------------------------
 * Function: writetospi()
 *
 * Low level abstract function to write to the SPI
 * Takes two separate byte buffers for write header and write data
 * returns 0 for success, or -1 for error
 */
int writetospi(uint16_t       headerLength,
               const uint8_t  *headerBuffer,
               uint16_t       bodyLength,
               const uint8_t  *bodyBuffer)
{
    decaIrqStatus_t  stat ;
    stat = decamutexon() ;

    while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);

    HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET); /**< Put chip select line low */

    HAL_SPI_Transmit(&hspi1, (uint8_t *)headerBuffer, headerLength, HAL_MAX_DELAY); /* Send header in polling mode */

    if(bodyLength != 0)
        HAL_SPI_Transmit(&hspi1, (uint8_t *)bodyBuffer,   bodyLength, HAL_MAX_DELAY);     /* Send data in polling mode */

    HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET); /**< Put chip select line high */
    decamutexoff(stat);
    return 0;
} // end writetospi()



/*! ------------------------------------------------------------------------------------------------------------------
* @fn spi_cs_low_delay()
*
* @brief This function sets the CS to '0' for ms delay and than raises it up
*
* input parameters:
* @param ms_delay - The delay for CS to be in '0' state
*
* no return value
*/
uint16_t spi_cs_low_delay(uint16_t delay_ms)
{
	/* Blocking: Check whether previous transfer has been finished */
	while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	/* Process Locked */
	__HAL_LOCK(&hspi1);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET); /**< Put chip select line low */
    deca_sleep(delay_ms);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET); /**< Put chip select line high */
	/* Process Unlocked */
	__HAL_UNLOCK(&hspi1);

	return 0;
}

/*! ------------------------------------------------------------------------------------------------------------------
 * Function: readfromspi()
 *
 * Low level abstract function to read from the SPI
 * Takes two separate byte buffers for write header and read data
 * returns the offset into read buffer where first byte of read data may be found,
 * or returns -1 if there was an error
 */
//#pragma GCC optimize ("O3")
int readfromspi(uint16_t  headerLength,
                uint8_t   *headerBuffer,
                uint16_t  readlength,
                uint8_t   *readBuffer)
{
    int i;

    decaIrqStatus_t  stat ;
    stat = decamutexon() ;

    /* Blocking: Check whether previous transfer has been finished */
    while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);

    HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET); /**< Put chip select line low */

    /* Send header */
    for(i=0; i<headerLength; i++)
    {
        HAL_SPI_Transmit(&hspi1, (uint8_t*)&headerBuffer[i], 1, HAL_MAX_DELAY); //No timeout
    }

    /* for the data buffer use LL functions directly as the HAL SPI read function
     * has issue reading single bytes */
    while(readlength-- > 0)
    {
        /* Wait until TXE flag is set to send data */
        while(__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_TXE) == RESET)
        {
        }

        hspi1.Instance->DR = 0; /* set output to 0 (MOSI), this is necessary for
        e.g. when waking up DW3000 from DEEPSLEEP via dwt_spicswakeup() function.
        */

        /* Wait until RXNE flag is set to read data */
        while(__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_RXNE) == RESET)
        {
        }

        (*readBuffer++) = hspi1.Instance->DR;  //copy data read form (MISO)
    }

    HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET); /**< Put chip select line high */

    decamutexoff(stat);

    return 0;
} // end readfromspi()

/****************************************************************************//**
 *
 *                              END OF DW1000 SPI section
 *
 *******************************************************************************/


