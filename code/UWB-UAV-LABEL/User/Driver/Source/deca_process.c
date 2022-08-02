//
// Created by maguo on 2022/8/2.
//
#include "deca_process.h"
#include "deca_device_api.h"
#include "deca_regs.h"
#include "printf.h"

/* Frames used in the ranging process. See NOTE 3 below. */
static uint8_t tx_poll_msg[] = {0x41, 0x88, 0, 0xCA, 0xDE, 'W', 'A', 'V', 'E', 0xE0, 0, 0};
static uint8_t rx_resp_msg[] = {0x41, 0x88, 0, 0xCA, 0xDE, 'V', 'E', 'W', 'A', 0xE1, 0, 0};
static uint8_t tx_final_msg[] = {0x41, 0x88, 0, 0xCA, 0xDE, 'D', 'E', 'C', 'A', 0xE2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
/* Length of the common part of the message (up to and including the function code, see NOTE 3 below). */
#define ALL_MSG_COMMON_LEN 10
/* Indexes to access some of the fields in the frames defined above. */
#define ALL_MSG_SN_IDX 2
#define RESP_MSG_POLL_RX_TS_IDX 10
#define RESP_MSG_RESP_TX_TS_IDX 14
#define RESP_MSG_TS_LEN 4
#define FINAL_MSG_POLL_TX_TS_IDX 10
#define FINAL_MSG_RESP_RX_TS_IDX 14
#define FINAL_MSG_FINAL_TX_TS_IDX 18

/*
 * 128-bit STS key to be programmed into CP_KEY register.
 *
 * This key needs to be known and programmed the same at both units performing the SS-TWR.
 * In a real application for security this would be private and unique to the two communicating units
 * and chosen/assigned in a secure manner lasting just for the period of their association.
 *
 * Here we use a default KEY as specified in the IEEE 802.15.4z annex
 */
static dwt_sts_cp_key_t cp_key =
        {
                0x14EB220F,0xF86050A8,0xD1D336AA,0x14148674
        };

/*
 * 128-bit initial value for the nonce to be programmed into the CP_IV register.
 *
 * The IV, like the key, needs to be known and programmed the same at both units performing the SS-TWR.
 * It can be considered as an extension of the KEY. The low 32 bits of the IV is the counter.
 * In a real application for any particular key the value of the IV including the count should not be reused,
 * i.e. if the counter value wraps the upper 96-bits of the IV should be changed, e.g. incremented.
 *
 * Here we use a default IV as specified in the IEEE 802.15.4z annex
 */
static dwt_sts_cp_iv_t cp_iv =
        {
                0x1F9A3DE4,0xD37EC3CA,0xC44FA8FB,0x362EEB34
        };

static uint8_t frame_seq_nb = 0;
/*
 * The 'poll' message initiating the ranging exchange includes a 32-bit counter which is part
 * of the IV used to generate the scrambled timestamp sequence (STS) in the transmitted packet.
 */
static void send_tx_poll_msg(void)
{
    /* Write frame data to DW IC and prepare transmission. See NOTE 7 below. */
    tx_poll_msg[ALL_MSG_SN_IDX] = frame_seq_nb;

    dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_TXFRS_BIT_MASK);
    dwt_writetxdata(sizeof(tx_poll_msg), tx_poll_msg, 0); /* Zero offset in TX buffer. */
    dwt_writetxfctrl(sizeof(tx_poll_msg), 0, 1); /* Zero offset in TX buffer, ranging. */

    /* Start transmission. */
    dwt_starttx(DWT_START_TX_IMMEDIATE | DWT_RESPONSE_EXPECTED);

    /* Poll DW IC until TX frame sent event set. See NOTE 8 below. */
    while (!(dwt_read32bitreg(SYS_STATUS_ID) & SYS_STATUS_TXFRS_BIT_MASK))
    { };

    /* Clear TXFRS event. */
    dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_TXFRS_BIT_MASK);

}

void Rx_Callback() {
    usb_printf("It\r\n");
    uint32_t status_reg = dwt_read32bitreg(SYS_STATUS_ID);
    if (status_reg & (SYS_STATUS_RXFCG_BIT_MASK | SYS_STATUS_ALL_RX_TO | SYS_STATUS_ALL_RX_ERR))
    {
        usb_printf("It\r\n");
    }


}

uint8_t firstLoopFlag = 0;
void process(){

    /*
        * Set STS encryption key and IV (nonce).
        * See NOTE 16 below.
        */
    if (!firstLoopFlag)
    {
        /*
         * On first loop, configure the STS key & IV, then load them.
         */
        dwt_configurestskey(&cp_key);
        dwt_configurestsiv(&cp_iv);
        dwt_configurestsloadiv();
        firstLoopFlag = 1;
    }
    else
    {
        /*
         * On subsequent loops, we only need to reload the lower 32 bits of STS IV.
         */
        dwt_writetodevice(STS_IV0_ID, 0, 4, (uint8_t *)&cp_iv);
        dwt_configurestsloadiv();
    }

    /*
     * Send the poll message to the responder.
     */
    send_tx_poll_msg();
    usb_printf("send pol\r\n");
}