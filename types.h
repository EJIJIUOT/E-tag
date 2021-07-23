#include <stdint.h>
#include <stdbool.h>





///структура для записи звуков во flash
typedef struct READ_sample {
uint32_t cnt_block;	//блоки
uint32_t cnt_page;	//страницы
uint32_t null_page;
uint32_t null_block;
uint32_t offset;
uint8_t spiffs_patrition;//какой раздел стереть
bool ehd_flag;//конец процедуры
} tread_sample;

enum typkeyboard_status {
			no_key_pressed,
			key_pressed
			};

enum typkeyboard_event  {
			no_key_pressing,
			key_pressing
	        };

enum tfire_mode_status {
single,
queues
};

enum reload_status{
	nothing_to_do,
	waiting_countdown,
	reload_now
};

struct pressing_duration
		{ uint16_t key_1      ; //длительность непрерывного 
					    //нажатия кнопки 1 ("Клавиша огня")
		  uint16_t key_1_inc:1; //бит, разрешающий 
					    //или запрещающий отсчет
					    //длительности нажатия кнопки 1  
		  uint16_t key_2      ; //длительность непрерывного 
					    //нажатия кнопки 2 ("Перезарядить")
		  uint16_t key_2_inc:1; //бит, разрешающий 
					    //или запрещающий отсчет
					    //длительности нажатия кнопки 2  		  
		  uint16_t no_key   ;
		};

enum Rx_Event {	
				NOT_EVENT, 		//нет событий
				RX_COMPLETE, 	//принят пакет
				RX_MESSAGE_COMPLITE,//принято сообщение
				RX_ERROR		//ошибка приема пакета
				}; 

typedef struct IR_Message {
uint8_t ID; //наименование сообщения
uint8_t param;//параметр сообщения
uint8_t control_byte;//контрольный байт
} tir_message;

typedef struct IR_Command {
uint8_t ID; //наименование сообщения
uint8_t param;//1параметр сообщения
uint8_t param1;//2параметр сообщения
} tir_command;

typedef struct IR_Tx_Buffer_Cursor {
uint8_t byte_pos; //номен байта в буфере передатчика
uint8_t bit_mask;//битовая маска для получения текущего бита
uint16_t bits_for_tx;//сколько бит нужно ещё передать 
} tir_tx_buffer_cursor;

typedef struct PlayerID {
uint16_t bit_7;//последний бит (всегда должен быть равен IR_ZERO)
uint16_t bit_6; 
uint16_t bit_5; 
uint16_t bit_4;
uint16_t bit_3;
uint16_t bit_2;
uint16_t bit_1;
uint16_t bit_0;//Первый бит
} tplayer_id;

typedef struct TeamID{
uint16_t bit_1;
uint16_t bit_0;
} tteam_id;

typedef struct Damage{
uint16_t bit_3; 
uint16_t bit_2; 
uint16_t bit_1; 
uint16_t bit_0;
} tdamage;

typedef struct DataPacket {
uint16_t header; //заголовок, всегда должен быть равен IR_START (1 Байт)
tplayer_id player_id; //после заголовка идет идентификатор игрока (8 Байт)
tteam_id team_id;	  //Затем идентификатор команды (2 Байта)
tdamage damage;		  //Ну и последним стоит "урон" (4 Байта)
uint16_t end_of_data;  //Метка, указывающая передатчику, что данных для отправки больше нет (всегда должна быть равна 0) (1 Байт)
} tdata_packet;

union data_packet_union{
tdata_packet packet;
uint16_t data[16];
};

typedef struct miles_protocol{
uint16_t carrier_frequency;
uint16_t err_tolerance;
uint16_t ir_zero;
uint16_t ir_one;
uint16_t ir_start;
uint16_t ir_space;
} tmiles_protocol;

enum Team_Color {	//Определим перечисляемый тип для работы с цветом команды
	Red, 	//00 = Red 0
	Blue, 	//01 = Blue	1	
	Yellow, //10 = Yellow 2
	Green}; //11 = Green 3
			
enum GunDamage {	
	
	Damage_1,  //0000 = 1
	Damage_2,  //0001 = 2
	Damage_4,  //0010 = 4
	Damage_5,  //0011 = 5
	Damage_7,  //0100 = 7
	Damage_10, //0101 = 10
	Damage_15, //0110 = 15
	Damage_17, //0111 = 17
	Damage_20, //1000 = 20
	Damage_25, //1001 = 25
	Damage_30, //1010 = 30
	Damage_35, //1011 = 35
	Damage_40, //1100 = 40
	Damage_50, //1101 = 50
	Damage_75, //1110 = 75
	Damage_100 //1111 = 100
	};
	
enum Get_ir_currect_modet {	
	
/*	7%,      //0
	17%,     //1
	35%,     //2
	57%,     //3
	78%,     //4
	85%,     //5
	92%,     //6
    100%     //7*/
	Pow_7,
	Pow_17,
	Pow_35,
	Pow_57,
	Pow_78,
	Pow_85,
	Pow_92,
	Pow_100
	};

uint8_t damage_value []  = {
	1,   // 0000 = 1   (Damage_1)
	2,   // 0001 = 2   (Damage_2)
	4,   // 0010 = 4   (Damage_4)
	5,   // 0011 = 5   (Damage_5)
	7,   // 0100 = 7   (Damage_7)
	10,  // 0101 = 10  (Damage_10)
	15,  // 0110 = 15  (Damage_15)
	17,  // 0111 = 17  (Damage_17)
	20,  // 1000 = 20  (Damage_20)
	25,  // 1001 = 25  (Damage_25)
	30,  // 1010 = 30  (Damage_30)
	35,  // 1011 = 35  (Damage_35)
	40,  // 1100 = 40  (Damage_40)
	50,  // 1101 = 50  (Damage_50)
	75,  // 1110 = 75  (Damage_75)
	100, // 1111 = 100 (Damage_100)

};

uint8_t ir_power_value [] = {
	50,   // 100ma
	75,   // 250ma
	100,   // 500ma
	125,   // 800ma
	150,   // 1100ma
	175,   // 1200ma
	200,   // 1300ma
	225   // 1300-1500ma max	

};	
	    								
enum Staictic_mode {		
	No,           //0
	Yes_block,    //1
	Yes_no_block  //2	
	};
		    								
enum Second_weapon_modet {		
	Not,           //0
	Master,    //1
	Slave  //2
	};

typedef struct RX_Packet {
uint8_t player_id;	//идентификатор попавшего в нас игрока
uint8_t team_id;	//идентификатор (цвет) его команды
uint8_t damage;		//приченённый нам урон
} trx_packet;

typedef struct E_eeprom_struct {
uint8_t team_id;	//идентификатор  игрока
uint8_t player_id;	//идентификатор команды
uint8_t damage;		// урон
uint8_t ir_power;	//мощность излучения
uint16_t bullets_in_clip;	//
uint16_t clips;
uint8_t reload_duration;	//
uint8_t friendly_fire_enable;	//
uint8_t statistic_enable;
uint16_t safe_duration;	//
uint16_t shock_time;	//
uint8_t second_weapon_enable;
uint16_t batt_full_voltage;	//
uint16_t batt_low_voltage;	//
uint16_t life_after_start;
uint16_t cyclic_rate;
} te_eeprom_struct;

struct st_col{
uint8_t sh_team; //номер цвета
uint16_t damage_rec;//полученный урон
uint8_t fatal_shoot;//фатальный выстрел
uint8_t death;//количество смертей
uint16_t shoots_tmp;//количество выстрелов
uint8_t damage_tager;//урон тагера
};





 