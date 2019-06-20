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


#ifndef _LORAGW_SX1302_H
#define _LORAGW_SX1302_H

/* -------------------------------------------------------------------------- */
/* --- DEPENDANCIES --------------------------------------------------------- */

#include <stdint.h>     /* C99 types*/

#include "config.h"     /* library configuration options (dynamically generated) */

/* -------------------------------------------------------------------------- */
/* --- PUBLIC CONSTANTS ----------------------------------------------------- */

/* Default values */
#define SX1302_AGC_RADIO_GAIN_AUTO  0xFF
#define TX_START_DELAY_DEFAULT      1500 /* Calibrated value for 500KHz BW */ /* TODO */

/* RX buffer packet structure */
#define SX1302_PKT_SYNCWORD_BYTE_0  0xA5
#define SX1302_PKT_SYNCWORD_BYTE_1  0xC0
#define SX1302_PKT_HEAD_METADATA    9
#define SX1302_PKT_TAIL_METADATA    14

/* modem IDs */
#if FPGA_BOARD_16_CH
#define SX1302_LORA_MODEM_ID_MAX    15
#define SX1302_LORA_STD_MODEM_ID    16
#define SX1302_FSK_MODEM_ID         17
#else
#define SX1302_LORA_MODEM_ID_MAX    11
#define SX1302_LORA_STD_MODEM_ID    12
#define SX1302_FSK_MODEM_ID         13
#endif

/* type of if_chain + modem */
#define IF_UNDEFINED                0
#define IF_LORA_STD                 0x10    /* if + standard single-SF LoRa modem */
#define IF_LORA_MULTI               0x11    /* if + LoRa receiver with multi-SF capability */
#define IF_FSK_STD                  0x20    /* if + standard FSK modem */

/* -------------------------------------------------------------------------- */
/* --- PUBLIC MACROS -------------------------------------------------------- */

#define REG_SELECT(rf_chain, a, b) ((rf_chain == 0) ? a : b)

#define SX1302_PKT_PAYLOAD_LENGTH(buffer, start_index)          TAKE_N_BITS_FROM(buffer[start_index +  2], 0, 8)
#define SX1302_PKT_CHANNEL(buffer, start_index)                 TAKE_N_BITS_FROM(buffer[start_index +  3], 0, 8)
#define SX1302_PKT_CRC_EN(buffer, start_index)                  TAKE_N_BITS_FROM(buffer[start_index +  4], 0, 1)
#define SX1302_PKT_CODING_RATE(buffer, start_index)             TAKE_N_BITS_FROM(buffer[start_index +  4], 1, 3)
#define SX1302_PKT_DATARATE(buffer, start_index)                TAKE_N_BITS_FROM(buffer[start_index +  4], 4, 4)
#define SX1302_PKT_MODEM_ID(buffer, start_index)                TAKE_N_BITS_FROM(buffer[start_index +  5], 0, 8)
#define SX1302_PKT_FREQ_OFFSET_7_0(buffer, start_index)         TAKE_N_BITS_FROM(buffer[start_index +  6], 0, 8)
#define SX1302_PKT_FREQ_OFFSET_15_8(buffer, start_index)        TAKE_N_BITS_FROM(buffer[start_index +  7], 0, 8)
#define SX1302_PKT_FREQ_OFFSET_19_16(buffer, start_index)       TAKE_N_BITS_FROM(buffer[start_index +  8], 0, 4)
#define SX1302_PKT_CRC_ERROR(buffer, start_index)               TAKE_N_BITS_FROM(buffer[start_index +  9], 0, 1)
#define SX1302_PKT_SYNC_ERROR(buffer, start_index)              TAKE_N_BITS_FROM(buffer[start_index +  9], 2, 1)
#define SX1302_PKT_HEADER_ERROR(buffer, start_index)            TAKE_N_BITS_FROM(buffer[start_index +  9], 3, 1)
#define SX1302_PKT_TIMING_SET(buffer, start_index)              TAKE_N_BITS_FROM(buffer[start_index +  9], 4, 1)
#define SX1302_PKT_SNR_AVG(buffer, start_index)                 TAKE_N_BITS_FROM(buffer[start_index + 10], 0, 8)
#define SX1302_PKT_RSSI_CHAN(buffer, start_index)               TAKE_N_BITS_FROM(buffer[start_index + 11], 0, 8)
#define SX1302_PKT_RSSI_SIG(buffer, start_index)                TAKE_N_BITS_FROM(buffer[start_index + 12], 0, 8)
#define SX1302_PKT_RSSI_CHAN_MAX_NEG_DELTA(buffer, start_index) TAKE_N_BITS_FROM(buffer[start_index + 13], 0, 4)
#define SX1302_PKT_RSSI_CHAN_MAX_POS_DELTA(buffer, start_index) TAKE_N_BITS_FROM(buffer[start_index + 13], 4, 4)
#define SX1302_PKT_RSSI_SIG_MAX_NEG_DELTA(buffer, start_index)  TAKE_N_BITS_FROM(buffer[start_index + 14], 0, 4)
#define SX1302_PKT_RSSI_SIG_MAX_POS_DELTA(buffer, start_index)  TAKE_N_BITS_FROM(buffer[start_index + 14], 4, 4)
#define SX1302_PKT_TIMESTAMP_7_0(buffer, start_index)           TAKE_N_BITS_FROM(buffer[start_index + 15], 0, 8)
#define SX1302_PKT_TIMESTAMP_15_8(buffer, start_index)          TAKE_N_BITS_FROM(buffer[start_index + 16], 0, 8)
#define SX1302_PKT_TIMESTAMP_23_16(buffer, start_index)         TAKE_N_BITS_FROM(buffer[start_index + 17], 0, 8)
#define SX1302_PKT_TIMESTAMP_31_24(buffer, start_index)         TAKE_N_BITS_FROM(buffer[start_index + 18], 0, 8)
#define SX1302_PKT_CRC_PAYLOAD_7_0(buffer, start_index)         TAKE_N_BITS_FROM(buffer[start_index + 19], 0, 8)
#define SX1302_PKT_CRC_PAYLOAD_15_8(buffer, start_index)        TAKE_N_BITS_FROM(buffer[start_index + 20], 0, 8)
#define SX1302_PKT_NUM_TS_METRICS(buffer, start_index)          TAKE_N_BITS_FROM(buffer[start_index + 21], 0, 8)

#define SET_PPM_ON(bw,dr)   (((bw == BW_125KHZ) && ((dr == DR_LORA_SF11) || (dr == DR_LORA_SF12))) || ((bw == BW_250KHZ) && (dr == DR_LORA_SF12)))

/* -------------------------------------------------------------------------- */
/* --- PUBLIC TYPES --------------------------------------------------------- */

/**
@struct sx1302_if_cfg_t
@brief TODO
*/
typedef struct {
    bool        if_enable;
    bool        if_rf_chain; /* for each IF, 0 -> radio A, 1 -> radio B */
    int32_t     if_freq; /* relative to radio frequency, +/- in Hz */
} sx1302_if_cfg_t;

/**
@struct sx1302_lora_service_cfg_t
@brief TODO
*/
typedef struct {
    uint8_t     lora_rx_bw; /* bandwidth setting for LoRa standalone modem */
    uint8_t     lora_rx_sf; /* spreading factor setting for LoRa standalone modem */
    bool        lora_rx_implicit_hdr; /* implicit header setting for LoRa standalone modem */
    uint8_t     lora_rx_implicit_length; /* implicit header payload length setting for LoRa standalone modem */
    bool        lora_rx_implicit_crc_en; /* implicit header payload crc enable setting for LoRa standalone modem */
    uint8_t     lora_rx_implicit_coderate; /* implicit header payload coderate setting for LoRa standalone modem */
} sx1302_lora_service_cfg_t;

/**
@struct sx1302_fsk_cfg_t
@brief TODO
*/
typedef struct {
    uint8_t     fsk_rx_bw; /* bandwidth setting of FSK modem */
    uint32_t    fsk_rx_dr; /* FSK modem datarate in bauds */
    uint8_t     fsk_sync_word_size; /* default number of bytes for FSK sync word */
    uint64_t    fsk_sync_word; /* default FSK sync word (ALIGNED RIGHT, MSbit first) */
} sx1302_fsk_cfg_t;

/* -------------------------------------------------------------------------- */
/* --- PUBLIC FUNCTIONS PROTOTYPES ------------------------------------------ */

/**
@brief TODO
@param TODO
@return TODO
*/
void sx1302_init(struct lgw_conf_timestamp_s *conf);

/**
@brief Get the SX1302 unique identifier
@param eui  pointerto the memory holding the concentrator EUI
@return LGW_REG_SUCCESS if no error, LGW_REG_ERROR otherwise
*/
int sx1302_get_eui(uint64_t * eui);

/**
@brief Check AGC & ARB MCUs parity error, and update timestamp counter wraping status
@brief This function needs to be called regularly (every few seconds) by the upper layer
@param N/A
@return LGW_REG_SUCCESS if no error, LGW_REG_ERROR otherwise
*/
int sx1302_update(void);

/**
@brief Select the clock source radio
@param rf_chain The RF chain index from which to get the clock source
@return LGW_REG_SUCCESS if success, LGW_REG_ERROR otherwise
*/
int sx1302_radio_clock_select(uint8_t rf_chain);

/**
@brief Apply the radio reset sequence to the required RF chain index
@param rf_chain The RF chain index of the radio to be reset
@param type     The type of radio to be reset
@return LGW_REG_SUCCESS if success, LGW_REG_ERROR otherwise
*/
int sx1302_radio_reset(uint8_t rf_chain, lgw_radio_type_t type);

/**
@brief Configure the radio type for the given RF chain
@param rf_chain The RF chain index to be configured
@param type     The type of radio to be set for the given RF chain
@return LGW_REG_SUCCESS if success, LGW_REG_ERROR otherwise
*/
int sx1302_radio_set_mode(uint8_t rf_chain, lgw_radio_type_t type);

/**
@brief Give/Release control over the radios to/from the Host
@param host_ctrl    Set to true to give control to the host, false otherwise
@return LGW_REG_SUCCESS if success, LGW_REG_ERROR otherwise
*/
int sx1302_radio_host_ctrl(bool host_ctrl);

/**
@brief Perform the radio calibration sequence and fill the TX gain LUT with calibration offsets
@param context_rf_chain The RF chains array from which to get RF chains current configuration
@param clksrc           The RF chain index which provides the clock source
@param txgain_lut       A pointer to the TX gain LUT to be filled
@return LGW_REG_SUCCESS if success, LGW_REG_ERROR otherwise
*/
int sx1302_radio_calibrate(struct lgw_conf_rxrf_s * context_rf_chain, uint8_t clksrc, struct lgw_tx_gain_lut_s * txgain_lut);

/**
@brief Configure the PA and LNA LUTs
@param N/A
@return LGW_REG_SUCCESS if success, LGW_REG_ERROR otherwise
*/
int sx1302_pa_lna_lut_configure(void);

/**
@brief Configure the Radio Front-End stage of the SX1302
@param N/A
@return LGW_REG_SUCCESS if success, LGW_REG_ERROR otherwise
*/
int sx1302_radio_fe_configure(void);

/**
@brief TODO
@param TODO
@return TODO
*/
uint8_t sx1302_get_ifmod_config(uint8_t if_chain);

/**
@brief Configure the channelizer stage of the SX1302
@param if_cfg   A pointer to the channels configuration
@param fix_gain Set to true to force the channelizer to a fixed gain, false to let the AGC controlling it
@return LGW_REG_SUCCESS if success, LGW_REG_ERROR otherwise
*/
int sx1302_channelizer_configure(struct lgw_conf_rxif_s * if_cfg, bool fix_gain);

/**
@brief Configure the correlator stage of the SX1302 LoRa multi-SF modems
@param N/A
@return LGW_REG_SUCCESS if success, LGW_REG_ERROR otherwise
*/
int sx1302_lora_correlator_configure(void);

/**
@brief Configure the correlator stage of the SX1302 LoRa single-SF modem
@param cfg  A pointer to the channel configuration
@return LGW_REG_SUCCESS if success, LGW_REG_ERROR otherwise
*/
int sx1302_lora_service_correlator_configure(struct lgw_conf_rxif_s * cfg);

/**
@brief Configure the syncword to be used by LoRa modems (public:0x34, private:0x12)
@param public           Set to true to use the "public" syncword, false to use the private one
@param lora_service_sf  The spreading factor configured for the single-SF LoRa modem
@return LGW_REG_SUCCESS if success, LGW_REG_ERROR otherwise
*/
int sx1302_lora_syncword(bool public, uint8_t lora_service_sf);

/**
@brief Configure the LoRa multi-SF modems
@param radio_freq_hz    The center frequency of the RF chain (0 or 1)
@return LGW_REG_SUCCESS if success, LGW_REG_ERROR otherwise
*/
int sx1302_lora_modem_configure(uint32_t radio_freq_hz);

/**
@brief Configure the LoRa single-SF modem
@param cfg              A pointer to the channel configuration
@param radio_freq_hz    The center frequency of the RF chain (0 or 1)
@return LGW_REG_SUCCESS if success, LGW_REG_ERROR otherwise
*/
int sx1302_lora_service_modem_configure(struct lgw_conf_rxif_s * cfg, uint32_t radio_freq_hz);

/**
@brief Configure the FSK modem
@param cfg  A pointer to the channel configuration
@return LGW_REG_SUCCESS if success, LGW_REG_ERROR otherwise
*/
int sx1302_fsk_configure(struct lgw_conf_rxif_s * cfg);

/**
@brief Enable the modems
@param N/A
@return LGW_REG_SUCCESS if success, LGW_REG_ERROR otherwise
*/
int sx1302_modem_enable(void);

/**
@brief Enable/Disable the GPS to allow PPS trigger and counter sampling
@param enbale   Set to true to enable, false otherwise
@return LGW_REG_SUCCESS if success, LGW_REG_ERROR otherwise
*/
int sx1302_gps_enable(bool enable);

/**
@brief Get the current SX1302 internal counter value
@param pps      True for getting the counter value at last PPS
@return the counter value in mciroseconds (32-bits)
*/
uint32_t sx1302_timestamp_counter(bool pps);

/**
@brief TODO
@param TODO
@return TODO
*/
int sx1302_agc_load_firmware(const uint8_t *firmware);

/**
@brief TODO
@param TODO
@return TODO
*/
int sx1302_agc_status(uint8_t* status);

/**
@brief TODO
@param TODO
@return TODO
*/
int sx1302_agc_wait_status(uint8_t status);

/**
@brief TODO
@param TODO
@return TODO
*/
int sx1302_agc_mailbox_read(uint8_t mailbox, uint8_t* value);

/**
@brief TODO
@param TODO
@return TODO
*/
int sx1302_agc_mailbox_write(uint8_t mailbox, uint8_t value);

/**
@brief TODO
@param TODO
@return TODO
*/
int sx1302_agc_start(uint8_t version, lgw_radio_type_t radio_type, uint8_t ana_gain, uint8_t dec_gain, uint8_t fdd_mode);

/**
@brief TODO
@param TODO
@return TODO
*/
int sx1302_arb_load_firmware(const uint8_t *firmware);

/**
@brief TODO
@param TODO
@return TODO
*/
int sx1302_arb_status(uint8_t* status);

/**
@brief TODO
@param TODO
@return TODO
*/
int sx1302_arb_wait_status(uint8_t status);

/**
@brief TODO
@param TODO
@return TODO
*/
int sx1302_arb_debug_read(uint8_t reg_id, uint8_t* value);

/**
@brief TODO
@param TODO
@return TODO
*/
int sx1302_arb_debug_write(uint8_t reg_id, uint8_t value);

/**
@brief TODO
@param TODO
@return TODO
*/
int sx1302_arb_start(uint8_t version);

/**
@brief TODO
@param TODO
@return TODO
*/
uint8_t sx1302_arb_get_debug_stats_detect(uint8_t channel);

/**
@brief TODO
@param TODO
@return TODO
*/
uint8_t sx1302_arb_get_debug_stats_alloc(uint8_t channel);

/**
@brief TODO
@param TODO
@return TODO
*/
void sx1302_arb_print_debug_stats(void);

/**
@brief TODO
@param TODO
@return TODO
*/
uint16_t sx1302_lora_payload_crc(const uint8_t * data, uint8_t size);

/**
@brief TODO
@param TODO
@return TODO
*/
uint16_t sx1302_rx_buffer_read_ptr_addr(void);

/**
@brief TODO
@param TODO
@return TODO
*/
uint16_t sx1302_rx_buffer_write_ptr_addr(void);

/**
@brief Check if any data to be fetched from the SX1302 RX buffer and fetch it if any.
@param nb_bytes A pointer to allocated memory to hold the number of bytes fetched
@return LGW_REG_SUCCESS if success, LGW_REG_ERROR otherwise
*/
int sx1302_fetch(uint16_t * nb_bytes);

/**
@brief Parse and return the next packet available in the fetched RX buffer.
@param context      Gateway configuration context
@param p            The structure to get the packet parsed
@return LGW_REG_SUCCESS if a packet could be parsed, LGW_REG_ERROR otherwise
*/
int sx1302_parse(lgw_context_t * context, struct lgw_pkt_rx_s * p);

/**
@brief Configure the delay to be applied by the SX1302 for TX to start
@param rf_chain     The RF chain index to be configured
@param radio_type   The type of radio for this RF chain
@param modulation   The modulation used for the TX
@param bandwidth    The bandwidth used for the TX
@return LGW_REG_SUCCESS if success, LGW_REG_ERROR otherwise
*/
int sx1302_tx_set_start_delay(uint8_t rf_chain, lgw_radio_type_t radio_type, uint8_t modulation, uint8_t bandwidth);

/**
@brief Compute the offset to be applied on RSSI for temperature compensation
@param context  a pointer to the memory that holds the current temp comp context
@param temperature  the temperature for which to compute the offset to be applied
@return the offset to be applied to RSSI
*/
float sx1302_rssi_get_temperature_offset(struct lgw_rssi_tcomp_s * context, float temperature);

/**
@brief Get current TX status of the SX1302
@param rf_chain the TX chain we want to get the status from
@return current status
*/
uint8_t sx1302_tx_status(uint8_t rf_chain);

/**
@brief Get current RX status of the SX1302
@param rf_chain the RX chain we want to get the status from
@return current status
@note NOT IMPLEMENTED
*/
uint8_t sx1302_rx_status(uint8_t rf_chain);

/**
@brief Abort current transmit
@param rf_chain the TX chain on which we want to abort transmit
@return LGW_REG_SUCCESS if success, LGW_REG_ERROR otherwise
*/
int sx1302_tx_abort(uint8_t rf_chain);

/**
@brief TODO
@param TODO
@return TODO
*/
int sx1302_tx_configure(lgw_radio_type_t radio_type);

/**
@brief TODO
@param TODO
@return TODO
*/
int sx1302_send(lgw_radio_type_t radio_type, struct lgw_tx_gain_lut_s * tx_lut, bool lwan_public, struct lgw_conf_rxif_s * context_fsk, struct lgw_pkt_tx_s * pkt_data);

#endif

/* --- EOF ------------------------------------------------------------------ */
