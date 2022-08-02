//
// Created by maguo on 2022/7/28.
//

#include "deca_conf.h"
#include <deca_device_api.h>
#include "gpio.h"
#include "cmsis_os2.h"
#include "deca_config_options.h"
#include "deca_sleep.h"
#include "shared_functions.h"
#include "deca_regs.h"

extern dwt_config_t config_options;
extern dwt_txconfig_t txconfig_options;
extern dwt_txconfig_t txconfig_options_ch9;


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
    while(dwt_configure(&config_options)) /* if the dwt_configure returns DWT_ERROR either the PLL or RX calibration has failed the host should reset the device */
    {
        usb_printf((char *)"CONFIG FAILED     ");
    }

    /* Configure the TX spectrum parameters (power, PG delay and PG count) */
    if(config_options.chan == 5)
    {
        dwt_configuretxrf(&txconfig_options);
    }
    else
    {
        dwt_configuretxrf(&txconfig_options_ch9);
    }

    /* Apply default antenna delay value. See NOTE 2 below. */
    dwt_setrxantennadelay(RX_ANT_DLY);
    dwt_settxantennadelay(TX_ANT_DLY);

    /* Set expected response's delay and timeout. See NOTE 14, 17 and 18 below.
     * As this example only handles one incoming frame with always the same delay and timeout, those values can be set here once for all. */
    dwt_setrxaftertxdelay(POLL_TX_TO_RESP_RX_DLY_UUS);
    dwt_setrxtimeout(RESP_RX_TIMEOUT_UUS);

    /* Set expected response's timeout. See NOTE 1 and 5 below.
     * As this example only handles one incoming frame with always the same delay, this value can be set here once for all. */
    set_resp_rx_timeout(RESP_RX_TIMEOUT_UUS, &config_options);

    /* Next can enable TX/RX states output on GPIOs 5 and 6 to help diagnostics, and also TX/RX LEDs */
    dwt_setlnapamode(DWT_LNA_ENABLE | DWT_PA_ENABLE);

//    /* Enable wanted interrupts (TX confirmation, RX good frames, RX timeouts and RX errors). */
//    dwt_setinterrupt(SYS_ENABLE_LO_TXFRS_ENABLE_BIT_MASK | SYS_ENABLE_LO_RXFCG_ENABLE_BIT_MASK | SYS_ENABLE_LO_RXFTO_ENABLE_BIT_MASK |
//                     SYS_ENABLE_LO_RXPTO_ENABLE_BIT_MASK | SYS_ENABLE_LO_RXPHE_ENABLE_BIT_MASK | SYS_ENABLE_LO_RXFCE_ENABLE_BIT_MASK |
//                     SYS_ENABLE_LO_RXFSL_ENABLE_BIT_MASK | SYS_ENABLE_LO_RXSTO_ENABLE_BIT_MASK, 0, DWT_ENABLE_INT);
//
//    //dwt_rxenable(DWT_START_RX_IMMEDIATE);
//    dwt_setrxaftertxdelay(RESP_TX_TO_FINAL_RX_DLY_UUS);


}