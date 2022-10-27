//
// Created by maguo on 2022/8/2.
//
#include "deca_process.h"
#include "deca_device_api.h"
#include "deca_regs.h"
#include "printf.h"

static uint8_t tx_msg[] = {0xC5, 0, 'D', 'E', 'C', 'A', 'W', 'A', 'V', 'E', 0x43, 0x02, 0, 0};



void Rx_Callback() {
    usb_printf("It\r\n");
    uint32_t status_reg = dwt_read32bitreg(SYS_STATUS_ID);
    if (status_reg & (SYS_STATUS_RXFCG_BIT_MASK | SYS_STATUS_ALL_RX_TO | SYS_STATUS_ALL_RX_ERR))
    {

    }

}

void process(){

//    /* Write frame data to DW IC and prepare transmission. See NOTE 7 below. */
//    dwt_writetxdata(sizeof(tx_msg), tx_msg, 0); /* Zero offset in TX buffer. */
//    dwt_writetxfctrl(sizeof(tx_msg), 0, 0); /* Zero offset in TX buffer, no ranging. */
//
//    /* Start transmission, indicating that a response is expected so that reception is enabled immediately after the frame is sent. */
//    dwt_starttx(DWT_START_TX_IMMEDIATE );
}