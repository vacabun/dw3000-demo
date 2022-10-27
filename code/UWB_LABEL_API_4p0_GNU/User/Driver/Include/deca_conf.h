//
// Created by maguo on 2022/7/28.
//

#ifndef UWB_UAV_LABEL_DECA_CONF_H
#define UWB_UAV_LABEL_DECA_CONF_H



void init_DWIC();


/* Inter-ranging delay period, in milliseconds. */
#define RNG_DELAY_MS 1000

/* Default antenna delay values for 64 MHz PRF. See NOTE 2 below. */
#define TX_ANT_DLY 16385
#define RX_ANT_DLY 16385

/* Delay between frames, in UWB microseconds. See NOTE 1 below. */
#define POLL_TX_TO_RESP_RX_DLY_UUS (290 + CPU_COMP)
/* Delay between frames, in UWB microseconds. See NOTE 1 below. */
#define POLL_RX_TO_RESP_TX_DLY_UUS (500 + CPU_COMP)
/*Delay between the response frame and final frame. */
#define RESP_TX_TO_FINAL_RX_DLY_UUS (100 + CPU_COMP)
/* This is the delay from Frame RX timestamp to TX reply timestamp used for calculating/setting the DW IC's delayed TX function. This includes the
 * frame length of approximately 550 us with above configuration. */
#define RESP_RX_TO_FINAL_TX_DLY_UUS (480 + CPU_COMP)

/* Receive response timeout. See NOTE 5 below. */
#define RESP_RX_TIMEOUT_UUS 300


#endif //UWB_UAV_LABEL_DECA_CONF_H
