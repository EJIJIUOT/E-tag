//static const char* TAG = "E-tag";
//#define SHIPPS_NAME        "sample"
//#define NAME_NVS "nvs"

//массивы блютуз имен//
#define NAME_LEN 11
#define PIN_LEN 5
#define ADR_LEN 7
#define CON_NAME_LEN 11

#define TAGER 0
#define HEADBAND 1
#define HARDWARE_MODE TAGER //TAGER -реэим тагера,HEADBAND -режим повязка
 
/**входные порты*/
#define ADC_IN    ADC_CHANNEL_5    ///         GPIO_NUM_33
#define DEFAULT_VREF    1100 
#define NO_OF_SAMPLES   64 

#define BUTTON_OFF_ON_KEY  GPIO_NUM_2
#define FIRE_MODE_KEY   GPIO_NUM_36
#define FIRE_KEY     GPIO_NUM_34
#define RELOAD_KEY   GPIO_NUM_39
#define TSOP_IN     GPIO_NUM_32
#define BUTTION_OLED   GPIO_NUM_4


/*ВЫХОДНЫЕ ПОРТЫ*/
#define IR_OUT    DAC_CHANNEL_1//gpio25
//#define SOUND_OUT   DAC_CHANNEL_2//gpio26
//#define WS2812_OUT   GPIO_NUM_21
#define OFF_ON_OUT   GPIO_NUM_18
#define SCL_OLED   GPIO_NUM_23
#define SDA_OLED   GPIO_NUM_22
#define RES_OLED   GPIO_NUM_35
#define OUT_POWER_OLED   GPIO_NUM_5
#define RELAY   GPIO_NUM_19

#define KEY_INPUT_PIN_SEL   ((1ULL<<FIRE_MODE_KEY) | (1ULL<<RELOAD_KEY ) | (1ULL<<FIRE_KEY ))
#define IR_INPUT_PIN_SEL    (1ULL<<TSOP_IN )
#define OFF_ON_PIN_SEL    ((1ULL<<BUTTON_OFF_ON_KEY ) |(1ULL<<BUTTION_OLED))
#define GPIO_OUTPUT_INPUT_PIN_SEL  ((1ULL<<WS2812_OUT ) | (1ULL<<OUT_POWER_OLED)| (1ULL<<RELAY )| (1ULL<<OFF_ON_OUT))  
#define DURATION_KEYBOAR 5

//звук//
//#define SAMPLE_RATE 8000
//#define TIM_GRUP_SOUND TIMER_GROUP_0 
//#define TIM_NUM_SOUND TIMER_0
//ик таймер//
#define TIM_GRUP_IR TIMER_GROUP_1 
#define TIM_NUM_IR TIMER_1
#define CAR_FREQ 9 //ДЛЯ 56КГЦ =9
//дисплей//
#define NUM_OLED 0 //0 ИЛИ 1
#define FONT_TEXT 1
#define SSD1306 2//0 -128x64 , 1 -128x32  ,2 -74x40 
//ws2812//
//#define RMT_TX_CHANNEL RMT_CHANNEL_0
//#define LED_NUMBER 16
//глобальный таймер//
#define TIM_GRUP_GLOBAL TIMER_GROUP_0 
#define TIM_NUM_GLOBAL  TIMER_1
#define CAR_FREQ_GLOBAL 50 //10khz при 50

#define SHORT_DURATION 50


#define Add_Health 0x80 //сообщение добавить жизни
#define Add_Rounds 0x81 //сообщение добавить патронов
#define Change_color 0xA9//сообщение сменить цвет команды 
#define Command 0x83 //сообщение-команда
#define Valid_value 0xE8 //корректное значение контрольного байта сообщения
#define Set_life 0xA3 //установить хх жизней
#define Set_damage 0xA8 //установить хх урон
#define Set_damage_tmp 0xA7 //установить хх урон временный
#define Setting_Mode 0xFE //переход в режим настроек
#define Chitfetect_Jdy_True 0xFC//чит детект для радиомодуля включен
//#define Chitfetect_Jdy_False 0xFD//чит детект для радиомодуля выключен
#define Tager_off 0xFD//чит детект для радиомодуля выключен
//#define Set_OK 0xF8//команда подтверждения
#define New_Game_Now 0x05//новая игра немедленно
#define Admin_Kill 0x00//админ килл
#define Rec_Ammo 0x0D//полное здоровье
#define Rec_Life 0x06//полный боезапас
//#define Set_OK 0xA8
//#define Set_damage 0xFE //
#define ESP_INTR_FLAG_DEFAULT 0
#define DEFAULT_IR_ERROR_IGNORE 80

#define IR_START 264//264 
#define IR_SPACE  52
#define IR_ONE 132
#define IR_ZERO 66
#define ERROR_TOLERANCE 20

#define RX_BUFFER_SIZE   8 //Размер буффера приемника
#define TX_BUFFER_SIZE   8 //Размер буффера приемника

#define max_round 127

/*#define  PLAYER_ID 0
#define  TEAM_ID 1
#define  DAMAGE 2
#define  IR_POWER 3
#define  BULLETS 4
#define  CLIPS 5
#define  RELOAD_DUR 6
#define  SAFE_DUR 7
#define  SHOCK_TIM 8
#define LIFE 9
#define CICLIC 10
#define FRIENDLY 11
#define STATISTIC 12
#define S_WEAPON 13
#define BATT_FUUL 14
#define BATT_LOW 15
#define TIMER_OFF 16*/
