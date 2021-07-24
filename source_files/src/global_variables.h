#include <stdint.h>
#include <stdbool.h>
#include "types.h"

volatile bool start_sound = false;
//статистика//
volatile bool statistic_upload_f;
volatile uint8_t statistic_tmp;//статистика off/on
volatile uint16_t shoots_tmp_col;
volatile uint8_t death_col;
struct st_col My_st_col[max_round];

///общие//
 volatile uint16_t chit_detected_counter; // счётчик длительности отключения повязки
 volatile bool chit_detected; // флаг, имеющий значение true, если зафиксировано отключение повязки
 volatile bool detect_bt;
 volatile uint32_t timer2;
 volatile bool off_on_flag;
volatile bool display_mode_status;
volatile uint8_t mode_device;
const char numbers[] ={"0123456789"};
const char hex_numbers[]={"0123456789ABCDEF"};


//ик прием/передача
typedef enum Rx_Event trx_event;
volatile uint16_t low_level_counter; 			//Счетчик длительности сигнала низкого уровня на выводе ИК-приемника
volatile uint16_t high_level_counter; 			//Счетчик длительности сигнала высокого уровня на выводе ИК-приемника
volatile bool start_bit_received;
volatile bool receiver_on;
volatile uint16_t ir_error_ignore;
volatile bool ir_transmitter_on;
volatile uint16_t ir_pulse_counter; 	//Обратный счетчик "вспышек" ИК-диода
volatile tir_tx_buffer_cursor ir_tx_buffer_cursor; //курсор передающего ИК буфера
volatile tmiles_protocol miles_protocol;//структура для хранения данных протокола
volatile uint8_t tx_buffer[TX_BUFFER_SIZE]; 	//Буффер ИК-передатчика
volatile int ir_space_counter; //Обратный счетчик длительности выключенного состояния ИК-диода (пауза между битами) 
volatile uint8_t ir_power_value_dac;
volatile uint8_t led_hit=0;
volatile bool start_bit_received;
volatile bool receiver_on;
volatile uint16_t low_level_counter; 			//Счетчик длительности сигнала низкого уровня на выводе ИК-приемника
volatile uint16_t high_level_counter; 			//Счетчик длительности сигнала высокого уровня на выводе ИК-приемника
volatile uint16_t bit_in_rx_buff;
volatile trx_event rx_event; 					//события ИК-приемника
volatile trx_packet rx_packet;
volatile tir_message ir_message;
volatile uint8_t rx_buffer[RX_BUFFER_SIZE]; 	//Буффер ИК-приемника



///параметры тагера//
typedef enum Team_Color tteam_color;
typedef enum Get_ir_currect_modet tget_ir_currect_modet;
typedef enum GunDamage tgun_damage; 
typedef enum Second_weapon_modet tsecond_weapon_modet;
typedef enum Staictic_mode tstatistic_mode;
tgun_damage damage;
tget_ir_currect_modet ir_power_value_set;
volatile uint8_t max_bullets_game;
volatile uint32_t reload_countdown;
volatile bool status_need_update;
volatile uint32_t safe_counter;
volatile uint32_t cyclic_deley_counter;
volatile uint32_t shock_counter;
volatile uint8_t display_bullets_update_now;
volatile uint8_t max_bullets_game;
volatile uint16_t cut_off_sound;
volatile uint16_t life_in_percent;
volatile uint16_t clips;
volatile uint16_t bullets;
volatile uint32_t bat_lvl;
te_eeprom_struct eeprom;

///кнопки//
typedef enum typkeyboard_event TKEYBOARD_EVENT;
typedef enum typkeyboard_status TKEYBOARD_STATUS;
typedef enum tfire_mode_status TFIRE_MODE_STATUS;
typedef enum  reload_status TRELOAD_STATUS;
volatile TKEYBOARD_EVENT  keyboard_event; //события клавиатуры 
volatile TKEYBOARD_EVENT  reload_key_event; //события клавиши "Перезарядить"
volatile struct pressing_duration key_pressing_duration;//структура хранит счетчики длительности нажатия кнопок
volatile TRELOAD_STATUS reload_state;


//блютуз//
void BluetoothSerial_task_write_bufer(void * arg);//задача записи в буфер
#define  SIZE_BUF 256
char usartRxBuf[SIZE_BUF];
volatile uint16_t rxBufTail = 0;
volatile uint16_t rxBufHead = 0;
volatile uint16_t rxCount = 0;
volatile bool cr_received; 
volatile bool bt_header_received;
uint8_t set_mode_bt=0;
volatile bool check_key_bt=false;
volatile bool set_or_game=false;


volatile uint16_t bit_in_bt_rx_buff;
volatile trx_packet bt_rx_packet;
volatile uint8_t bt_rx_buffer[RX_BUFFER_SIZE];
char eeprom_bt_pin[PIN_LEN]={"1234"};//]="1234";
char eeprom_devise_name[NAME_LEN];//;//="ESP32T";
char eeprom_con_name[NAME_LEN];//="ESP32T";
char eeprom_con_adr[ADR_LEN];//="123456";

///выкл/вкл//
volatile bool flag;
uint8_t  eeprom_time_off;
volatile bool first_on;
volatile bool off_on_flag;
portMUX_TYPE mutex= portMUX_INITIALIZER_UNLOCKED;
volatile bool global_timer=false;
volatile bool sound_timer=false;
volatile bool ir_timer=false;


