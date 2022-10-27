/*! ----------------------------------------------------------------------------
 *  @file    read_dev_id.c
 *  @brief   This example just read DW IC's device ID. It can be used to verify
 *           the SPI comms are working correctly.
 *
 * @attention
 *
 * Copyright 2018-2020 (c) Decawave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 * @author Decawave
 */


#include <deca_device_api.h>
#include <port.h>
#include <example_selection.h>


#if defined(TEST_READING_DEV_ID)

extern void test_run_info(unsigned char *data);

/* Example application name and version to display on LCD screen/VCOM port. */
#define APP_NAME "READ DEV ID\r\n"

/**
 * Application entry point.
 */
int read_dev_id(void)
{
    int err = 0;
    /* Display application name on LCD. */
    usb_printf(APP_NAME);

    /* Configure SPI rate, DW3000 supports up to 38 MHz */
    port_set_dw_ic_spi_fastrate();

    /* Reset DW IC */
    reset_DWIC(); /* Target specific drive of RSTn line into DW IC low for a period. */

    Sleep(2); // Time needed for DW3000 to start up (transition from INIT_RC to IDLE_RC, or could wait for SPIRDY event)
    /* Reads and validate device ID returns DWT_ERROR if it does not match expected else DWT_SUCCESS */
    if ((err=dwt_check_dev_id())==DWT_SUCCESS)
    {
			  usb_printf("DEV ID : %#x\r\n",dwt_readdevid());
    }
    else
    {
				usb_printf("DEV ID FAILED\r\n");
    }

    return err;
}

#endif
/*****************************************************************************************************************************************************
 * NOTES:
 ****************************************************************************************************************************************************/
