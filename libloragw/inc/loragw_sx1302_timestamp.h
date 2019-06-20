/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
  (C)2018 Semtech

Description:
    TODO

License: Revised BSD License, see LICENSE.TXT file include in the project
*/


#ifndef _LORAGW_SX1302_TIMESTAMP_H
#define _LORAGW_SX1302_TIMESTAMP_H

/* -------------------------------------------------------------------------- */
/* --- DEPENDANCIES --------------------------------------------------------- */

#include <stdint.h>     /* C99 types*/
#include <stdbool.h>       /* boolean type */


#include "config.h"     /* library configuration options (dynamically generated) */

/* -------------------------------------------------------------------------- */
/* --- PUBLIC CONSTANTS ----------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* --- PUBLIC MACROS -------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* --- PUBLIC TYPES --------------------------------------------------------- */

/**
@struct timestamp_counter_s
@brief context to maintain the internal counters (inst and pps trig) wrapping
*/
typedef struct timestamp_counter_s {
    uint32_t counter_us_raw_27bits_inst_prev;
    uint32_t counter_us_raw_27bits_pps_prev;
    uint8_t  counter_us_raw_27bits_inst_wrap;
    uint8_t  counter_us_raw_27bits_pps_wrap;
} timestamp_counter_t;

/* -------------------------------------------------------------------------- */
/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/**
@brief TODO
@param TODO
@return TODO
*/
void timestamp_counter_new(timestamp_counter_t * self);

/**
@brief TODO
@param TODO
@return TODO
*/
void timestamp_counter_delete(timestamp_counter_t * self);

/**
@brief Update the counter wrapping status based on given current counter
@param self     Pointer to the counter handler
@param pps      Set to true to update the PPS trig counter status
@param cnt      Current value of the counter to be used for the update
@return N/A
*/
void timestamp_counter_update(timestamp_counter_t * self, bool pps, uint32_t cnt);

/**
@brief Convert the 27-bits counter given by the SX1302 to a 32-bits counter which wraps on a uint32_t.
@param self     Pointer to the counter handler
@param pps      Set to true to expand the counter based on the PPS trig wrapping status
@param cnt_us   The 27-bits counter to be expanded
@return the 32-bits counter
*/
uint32_t timestamp_counter_expand(timestamp_counter_t * self, bool pps, uint32_t cnt_us);

/**
@brief Reads the SX1302 internal counter register, and return the 32-bits 1 MHz counter
@param self     Pointer to the counter handler
@param pps      Set to true to expand the counter based on the PPS trig wrapping status
@return the current 32-bits counter
*/
uint32_t timestamp_counter_get(timestamp_counter_t * self, bool pps);

/**
@brief Get the timestamp correction to applied to the packet timestamp
@param ifmod            modem type
@param bandwidth        modulation bandwidth
@param datarate         modulation datarate
@param coderate         modulation coding rate
@param crc_en           indicates if CRC is enabled or disabled
@param payload_length   payload length
@return The correction to be applied to the packet timestamp, in microseconds
*/
uint32_t timestamp_counter_correction(int ifmod, uint8_t bandwidth, uint8_t datarate, uint8_t coderate, uint32_t crc_en, uint16_t payload_length);

/**
@brief TODO
@param TODO
@return TODO
*/
int timestamp_counter_mode(bool enable_precision_ts, uint8_t max_ts_metrics, uint8_t nb_symbols);

#endif

/* --- EOF ------------------------------------------------------------------ */
