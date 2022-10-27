//
// Created by maguo on 2022/7/28.
//

#include "deca_conf.h"
#include <deca_device_api.h>
#include "gpio.h"
#include "cmsis_os2.h"
#include "deca_config_options.h"
#include "deca_sleep.h"

#include "deca_regs.h"

extern dwt_config_t config_options;
extern dwt_txconfig_t txconfig_options;
extern dwt_txconfig_t txconfig_options_ch9;

/* Default communication configuration. We use default non-STS DW mode. */
static dwt_config_t config = {
        5,               /* Channel number. */
        DWT_PLEN_128,    /* Preamble length. Used in TX only. */
        DWT_PAC8,        /* Preamble acquisition chunk size. Used in RX only. */
        9,               /* TX preamble code. Used in TX only. */
        9,               /* RX preamble code. Used in RX only. */
        1,               /* 0 to use standard 8 symbol SFD, 1 to use non-standard 8 symbol, 2 for non-standard 16 symbol SFD and 3 for 4z 8 symbol SDF type */
        DWT_BR_6M8,      /* Data rate. */
        DWT_PHRMODE_STD, /* PHY header mode. */
        DWT_PHRRATE_STD, /* PHY header rate. */
        (129 + 8 - 8),   /* SFD timeout (preamble length + 1 + SFD length - PAC size). Used in RX only. */
        DWT_STS_MODE_OFF, /* STS disabled */
        DWT_STS_LEN_64,  /* STS length see allowed values in Enum dwt_sts_lengths_e */
        DWT_PDOA_M0      /* PDOA mode off */
};

void reset_DWIC(void)
{
    HAL_GPIO_WritePin(DW1000_RSTn_GPIO_Port, DW1000_RSTn_Pin, GPIO_PIN_RESET);
    deca_usleep(20);
    HAL_GPIO_WritePin(DW1000_RSTn_GPIO_Port, DW1000_RSTn_Pin, GPIO_PIN_SET);
}

void init_DWIC(){

    reset_DWIC();

    deca_sleep(2); // Time needed for DW3000 to start up (transition from INIT_RC to IDLE_RC)

    while (!dwt_checkidlerc()) /* Need to make sure DW IC is in IDLE_RC before proceeding */
    {
        usb_printf((char *)"INIT FAILED     ");
    }

    while (dwt_initialise(DWT_DW_IDLE) == DWT_ERROR)
    {
        usb_printf((char *)"INIT FAILED     ");

    }

    /* Configure DW IC. See NOTE 15 below. */
    while(dwt_configure(&config)) /* if the dwt_configure returns DWT_ERROR either the PLL or RX calibration has failed the host should reset the device */
    {
        usb_printf((char *)"CONFIG FAILED     ");
    }

    /* Configure the TX spectrum parameters (power, PG delay and PG count) */
    if(config.chan == 5)
    {
        dwt_configuretxrf(&txconfig_options);
    }
    else
    {
        dwt_configuretxrf(&txconfig_options_ch9);
    }


    dwt_setpanid(0xF0F0);
    dwt_setaddress16(0x0001);

    dwt_setrxantennadelay(RX_ANT_DLY);
    dwt_settxantennadelay(TX_ANT_DLY);

    dwt_setinterrupt(DWT_INT_TFRS, 0, DWT_ENABLE_INT);

//    dwt_rxenable(DWT_START_RX_IMMEDIATE);
//
//    dwt_setrxtimeout(0);
}