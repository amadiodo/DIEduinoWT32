#ifndef global_H
#define global_H

#include <Arduino.h>

// #define AC
// #define GREENCUBE_OBC
// #define PROPAGATOR
// #define FRIDGE
#define POWER_BOARD
// #define CAMERA
// #define COLLARE_USA

// #define DEBOLMAN_PSTN
#define LABICO
// #define DEBOLMAN_LAN
// #define S5LAB_ARUBA
// #define S5LAB_LAN

#define TCP_SOCKET

#define DEBUG_USART Serial
#define GREENCUBE_USART Serial2

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define picture_buffer_lenght  496 //508
#define HK_TLM 0x30
#define GLOBAL_TLM 0x50
#define MOS_EXT_PIN 13
#define MOS_A1_PIN 14
#define MOS_BIG_PIN 27
#define DS18_PIN 32
#define UDP_INTERFACE 0xA1
#define TCP_INTERFACE 0xA2
#define UART_INTERFACE 0xA3
#define FEND 0xC0
#define FESC 0xDB
#define TFEND 0xDC
#define TFESC 0xDD
#define PIN_EN_3V 33
#define PIN_EN_5V 4
#define PIN_LED 26
#define BREATHE_PIN 26
// #define 

extern uint8_t TCP_attempt;
extern uint32_t HK_TLM_receipt_time;
extern bool verbose;
extern bool TO_TCP;
extern bool TO_UART;
extern bool payload_semaphore;
extern bool propagator_available;
extern bool TCP_available;
extern bool DS18_available;
extern bool WiFi_available;
extern bool INA3221_available;
extern bool INA260_available;
extern bool send_logg;
extern uint32_t time_margin;
extern uint32_t power_board_old_time;
extern uint32_t DS18_old_time;
extern char stri[64];
extern char satname[24];
extern char tle_line1[69];
extern char tle_line2[69];
extern bool FS_available;
extern uint32_t PIC_old_time;
extern char debolman_host[16];
extern bool UDP_available;

// IPAddress aruba(80,211,188,79);
// extern IPAddress S5Lab_LAN_IP;
// extern IPAddress serverbit_LAN_IP;
// extern IPAddress labico_IP;

void UART_KISS_RX();
void send_UDP_IP(uint8_t buffer[], uint8_t lenght, IPAddress host, uint16_t port);
bool UDP_begin();
void NTP_loop();
void debug_prefix();
void SGP_loop();
void sgp_initialization();
uint32_t unix_seconds();
void RX_decoder(uint8_t buf[], uint16_t size, uint8_t KISS_port);
void TCP_send(uint8_t TCP_TX_uffer[], uint16_t size);
void KISS_encode(uint8_t buffer[], uint16_t size, uint8_t kissport, uint8_t interface);
// void KISS_translate(uint8_t buffer[], uint16_t size, uint8_t kissport);
void TCP_RX();
bool FS_initialization();
void filee();
void filee_de();
bool connectivity_check(bool force);
void H2O();
void apollo();
bool DS18B20_initialization();
void save_grenencube_parameters();
void GET_greencube_parameters_EEPROM();
void EXT_heat_control(uint8_t heat_PWM);
bool payload_live();
uint8_t day_hour();
void payload_send(uint8_t payload_TX_buffer[], uint8_t size );
void picture_request();
bool INA3221_initialization();
bool INA260_initialization();
void greencube_payload_task();
float DS18_read();
void power_board_read();
void pins_initialization();
void decode_payload_TLM_GLOBAL(uint8_t payload_TLM_buffer[], uint8_t size);
void greencube_power_cycle();
void send_UDP(uint8_t UDP_TX_buffer[], uint8_t lenght);
void WiFi_RSSI();
void decode_payload_picture(uint8_t payload_picture_buffer[]);
void recvMsg(uint8_t *data, size_t len);
void print_ESP_data();
void print_ESP_dataa();
void print_ESP_datab();
void print_ESP_datac();
void propagator_initialization();
void evaluate_prapagator();
void propagator_request_TLE(bool force);
void UDP_RX();
bool wifi_initialization();
uint8_t TCP_connection();
uint8_t TCP_check();
void read_AC_single_phase_power();
// void open_log_file();
// void print2log(char *text);
// void send_log();
// void send_log2();
void print_debug(char *text, bool log);
void GC_save_parameters(uint8_t buff[], uint8_t size);
void pins_initialization();
void blink_LED();
bool INA3221_initialization();
bool INA260_initialization();
void GC_print_parameters();
void save_grenencube_parameters();
void send_UDP_text(char *buffer);
void memory_setup();
uint8_t open_pic_file();
void write_pic_file(uint8_t buffer[], uint16_t size);
void colse_pic_file();
uint16_t pic_file_size();
void close_pic_file();
void breathe();
void eth_setup();
void eth_loop();

// struct LoRa_param_sct {
//   uint8_t id;
//   uint8_t interval;
//   uint8_t SF;
//   uint8_t BW;

//   uint8_t TX_power;
//   uint8_t CR;
//   uint8_t CRC;
//   uint8_t frequency;

//   uint8_t gain;
//   int8_t  RX_freq_corr;
//   uint8_t FLDRO;
//   uint8_t RFO;

//   uint8_t sync_word;
//   uint8_t EX_header;
//   uint8_t ACT_TX;
//   uint8_t I_limit;

//   uint8_t LNA;
//   uint8_t P_length;
//   uint8_t len;
//   uint8_t EXT_PA;

//   uint16_t temp;
//   uint8_t temp2;
//   uint8_t temp3;
// } ;

// extern LoRa_param_sct LoRa_parameters;

// struct LoRa_RX_packet_sct {
//   uint32_t time;
//   uint8_t RSSI;
//   uint8_t SNR;
//   uint8_t length;
//   uint8_t temp;

//   int8_t state;
//   uint8_t id;
//   uint16_t TSL;

//   int16_t freq_error;
//   uint8_t temp5;
//   uint8_t temp6;

// } ;

// extern LoRa_RX_packet_sct LoRa_RX_packet;

struct fridge_packet_sct {
  float PLUS_X;
  float MINUS_X;
  float PLUS_Y;
  float MINUS_Y;
  float PLUS_Z;
  float MINUS_Z;
  float EXT;
  float EXTb;
  float AUX;
} ;

extern fridge_packet_sct fridge_packet;

struct TLM_PWR_board_sct {
  uint8_t boot_count;
  uint8_t RSSI;
  uint8_t boot_cause;;
  uint8_t ETH_error;
  float seconds;

  float V5V_voltage;
  float V5V_current;
  
  float V3V3_voltage;
  float V3V3_current;
  
  float EXT_voltage;
  float EXT_current;
  
  float VIN_voltage;
  float VIN_current;
  
  float VIN_power;
  float temperature;
};

extern TLM_PWR_board_sct power_board;

struct greencube_parameters_sct {
  uint8_t TLM_interval;
  uint8_t heat_PWM;
  uint8_t LED_PWM ;
  uint8_t picture_interval;
  
  uint8_t H2O_dose;
  uint8_t PIC_resolution;
  uint8_t BIO_active;
  uint8_t H2O_interval;

  uint8_t time_margin;
  uint8_t EXT_heater_PWM;
  uint8_t WiFi_delay;
  uint8_t UART_delay;
} ;

extern greencube_parameters_sct greencube_parameters;

struct pay_tlm_sct {  
  uint64_t unixtime;    

  uint16_t BMP_T;
  uint8_t tank_press;
  uint8_t H2O_dose;
  uint8_t SCD_M;
  uint8_t BME_M;
  uint8_t SHT_M;
  uint8_t illumination;

  int16_t LPS35HW_T;
  uint16_t LPS35HW_P;
  uint16_t SCD_CO2;
  int16_t SCD_T;

  int16_t BME_T;
  uint16_t BME_P;
  uint16_t BME_G;
  int16_t SHT_T;

  uint16_t BMP_P;
  uint8_t O2;
  uint8_t ranging;
  uint32_t seconds;
  
  uint16_t TVOC;       
  uint16_t eCO2;

  uint8_t camera_status;
  uint8_t sensors_init;
  uint8_t boot_count;
  uint8_t heat_PWM;

  uint8_t accessories;
  uint8_t valve_counter;
  uint16_t rang_light;
               
  uint8_t V_12V;
  uint8_t boot_cause;
  uint8_t LED_PWM;
  uint8_t error;
} ;

extern pay_tlm_sct payload_TLM ;

struct pay_tlm_HK_sct {    
  uint8_t LED_PWM;
  uint8_t H2O_dose;
  uint16_t RAM;

  uint8_t heat_PWM;
  uint8_t accessories;
  uint8_t boot_cause;
  uint8_t valve_counter;
  
  uint32_t millis;
  uint8_t boot_count;
  uint8_t sensors_init;
  uint8_t illumination;
  uint8_t V_12V;
} ;

extern pay_tlm_HK_sct tlm_HK;

struct pic_struct {
  uint8_t id;
  uint8_t lenght;
  uint16_t pkt_num;
  uint8_t pic[picture_buffer_lenght];  
} ;

extern pic_struct photo;

#endif