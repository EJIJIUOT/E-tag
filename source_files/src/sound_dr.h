#include <stdio.h>
#include <string.h>
#include "driver/i2s.h"
#include "driver/timer.h"
#include "sound_sample.h"//массив своих звуков
#include "laserwar_sound.h"//массив звуков лазервар

#define SOUND_OUT   DAC_CHANNEL_2//gpio26
#define SAMPLE_RATE 11025//для звуков лазервар 11025 для своих 8000
#define TIM_GRUP_SOUND TIMER_GROUP_0 
#define TIM_NUM_SOUND TIMER_0

typedef struct _audio_info//общая структура для таймера
{	
	uint32_t dataLength;
	const uint8_t *data;	
} audio_info_t;

enum sound_role{//перечесление своих звуков
	nothing_to_play,
	shot_sound,
	hit_sound,
	clip_in_sound,
	clip_out_sound,
	misfire_sound,
	flying_bullet_sound,
	start_game_sound,
	game_over_sound,
	sonar_sound
};

typedef enum sound_laserwar{//структура для звуков лазервар
nothing_to_play_lw,  
NewGame,
StartGame,
TimeOver,
SpecialForces,
Blood,
Fire,
SilentFire,
HotFire,
Misfire,
Miss,
FiringMode,
StartReload,
EndReload,
LastClip,
Stuned,
Bleeding,
Hited,
Sniper,
NeadHelp,
Killed,
KilledByZombi,
Bandage,
Medic,
Reheneration,
Support,
Ammo,
Disarmed,
DoubleHealth,
ArmyDoctor,
Anomal,
Radiation,
BombDeact,
Point,
Terminator,
LastHero,
Zombi,
Clowl,
AkumGood,
AkumBad,
Ticker,
Error,
StartRecovery,
HilRPower,
LowlRPower,
Pause,
Red_s,
Blue_s,
Yellow_s,
Green_s,
GrenadeFire,
GrenadeLoaded,
GredageExplosion,
Scout,
AdminMode,
SettingWrited,
StatisticReaded,
StatisticCleared,
RoundTimerON,
min10Left,
min5Left,
min1Left,
HaveFlag,
FlagStand
}TSOUND_ROLE_LW;

volatile uint32_t wav_pos ;
typedef enum sound_role TSOUND_ROLE;
volatile audio_info_t waw_samle;
void play_sound_from_flash(TSOUND_ROLE sound_role);//функция воспроизведения своих звуков
void timer_sound_Init(void);//инициализация звукового таймера
void IRAM_ATTR timer_sound_ISR(void *arg);//тело прерывания таймера
void sound_stop_now(void);
void play_sound_from_flash_LW(TSOUND_ROLE_LW sound_role_lw);//функция воспроизведения звуков лазервар
void play_sound_num(uint8_t num);//функция воспроизведения LW звуков через номер

void play_sound_from_flash(TSOUND_ROLE sound_role)
{
 switch (sound_role)
	{
	  case 	nothing_to_play:
	  sound_stop_now();
	  break;
		//звук выстрела
		case shot_sound:
		sound_stop_now(); 
 waw_samle.dataLength=sizeof(wav_shoot);//4685;
 waw_samle.data= wav_shoot;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);

    break;
    	case hit_sound: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(wav_hit_sound);//4262;
   waw_samle.data= wav_hit_sound ;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
     	case clip_in_sound: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(wav_clip_in_sound);//1399;
   waw_samle.data= wav_clip_in_sound;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case clip_out_sound:
     sound_stop_now();  
   waw_samle.dataLength =sizeof(wav_clip_out_sound); //1520;
  waw_samle.data= wav_clip_out_sound;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break; 
    	case misfire_sound: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(wav_misfire_sound);//2453;
   waw_samle.data= wav_misfire_sound;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    	case flying_bullet_sound: 
     sound_stop_now(); 
  waw_samle.dataLength =sizeof(wav_flying_bullet_sound); //4885;
   waw_samle.data= wav_flying_bullet_sound;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case start_game_sound:
    sound_stop_now();  
  waw_samle.dataLength =sizeof(wav_start_game_sound); //9474;
   waw_samle.data= wav_start_game_sound;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break;   

	case game_over_sound:
   sound_stop_now();
   waw_samle.dataLength = sizeof(wav_game_over_sound);//26433;
  waw_samle.data= wav_game_over_sound;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    case sonar_sound:
	sound_stop_now();
   waw_samle.dataLength = sizeof(wav_sonar_sound);//11782;
   waw_samle.data= wav_sonar_sound;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;

    default:
   sound_stop_now();
	break;
}
}

void timer_sound_Init()
{


	timer_config_t config = {
		.divider = 2340, // Предделитель 3600 для (TTGO)
		.counter_dir = TIMER_COUNT_UP, // Считать вверх
		.counter_en = TIMER_PAUSE, // Состояние - пауза
		.alarm_en = TIMER_ALARM_EN, // Включить прерывание Alarm
		.intr_type = TIMER_INTR_LEVEL, // Прерывание по уровню
		.auto_reload = TIMER_AUTORELOAD_EN , // Автоматически перезапускать счет
	};

	// Применить конфиг
	timer_init(TIM_GRUP_SOUND , TIM_NUM_SOUND, &config);
	// Установить начальное значение счетчика
	timer_set_counter_value(TIM_GRUP_SOUND , TIM_NUM_SOUND, 0x00000000ULL);
	// Установить значение счетчика для срабатывания прерывания Alarm
	timer_set_alarm_value(TIM_GRUP_SOUND, TIM_NUM_SOUND, TIMER_BASE_CLK / config.divider / SAMPLE_RATE);
	// Разрешить прерывания
	timer_enable_intr(TIM_GRUP_SOUND , TIM_NUM_SOUND);
	// Зарегистрировать обработчик прерывания
   timer_isr_register(TIM_GRUP_SOUND , TIM_NUM_SOUND, timer_sound_ISR, (void *)&waw_samle, ESP_INTR_FLAG_IRAM, NULL);
   //printf("sound timer init 0k\n");
	// Запустить таймер
	//timer_start(TIMER_GROUP_0, TIM_NUM_SOUND);
  //dac_output_enable(SOUND_OUT_1);
  dac_output_enable(SOUND_OUT);
  //printf("dac sound eneble 0k\n");
}

void IRAM_ATTR timer_sound_ISR(void *arg)
{
    timer_group_clr_intr_status_in_isr(TIM_GRUP_SOUND, TIM_NUM_SOUND);
	// Перезапустить прерывание Alarm
	timer_group_enable_alarm_in_isr(TIM_GRUP_SOUND, TIM_NUM_SOUND);

    audio_info_t *audio = (audio_info_t *)arg;
	if (wav_pos >= audio->dataLength) 
  {wav_pos = 44;
	timer_pause(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    start_sound = false; 
	}
  
	dac_output_voltage(SOUND_OUT, *(audio->data + wav_pos));
	wav_pos ++;   
}

void sound_stop_now(void)
{
  wav_pos = 44;//при воспроизведение своих звуков обнуляем до 0 при LW до 44
	timer_pause(TIM_GRUP_SOUND, TIM_NUM_SOUND);
  start_sound = false; 
}

void play_sound_from_flash_LW(TSOUND_ROLE_LW sound_role_lw)
{
 switch (sound_role_lw)
	{
	  case 	nothing_to_play_lw:
	  sound_stop_now();
	  break;
    //sound_stop_now();
		//звук выстрела
		case NewGame:
		sound_stop_now(); 
 waw_samle.dataLength=sizeof(NewGame_01);//4685;
 waw_samle.data= NewGame_01;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);

    break;
    	case StartGame: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(StartGame_02);//4262;
   waw_samle.data= StartGame_02 ;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
     	case TimeOver: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(TimeOver_03);//1399;
   waw_samle.data= TimeOver_03;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case SpecialForces:
     sound_stop_now();  
   waw_samle.dataLength =sizeof(SpecialForces_04); //1520;
  waw_samle.data= SpecialForces_04;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break; 
    	case Blood: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(Blood_05);//2453;
   waw_samle.data=Blood_05;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    	case Fire: 
     sound_stop_now(); 
  waw_samle.dataLength =sizeof(Fire_06); //4885;
   waw_samle.data= Fire_06;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case SilentFire:
    sound_stop_now();  
  waw_samle.dataLength =sizeof(SilentFire_07); //9474;
   waw_samle.data= SilentFire_07;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break;   

	case HotFire:
   sound_stop_now();
   waw_samle.dataLength = sizeof(HotFire_08);//26433;
  waw_samle.data= HotFire_08;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    case Misfire:
	sound_stop_now();
   waw_samle.dataLength = sizeof(Misfire_09);//11782;
   waw_samle.data= Misfire_09;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
		case Miss:
		sound_stop_now(); 
 waw_samle.dataLength=sizeof(Miss_10);//4685;
 waw_samle.data= Miss_10;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);

    break;
    	case FiringMode: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(FiringMode_11);//4262;
   waw_samle.data= FiringMode_11 ;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
     	case StartReload: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(StartReload_12);//1399;
   waw_samle.data= StartReload_12;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case EndReload:
     sound_stop_now();  
   waw_samle.dataLength =sizeof(EndReload_13); //1520;
  waw_samle.data= EndReload_13;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break; 
    	case LastClip: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(LastClip_14);//2453;
   waw_samle.data=LastClip_14;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    	case Stuned: 
     sound_stop_now(); 
  waw_samle.dataLength =sizeof(Stuned_15); //4885;
   waw_samle.data= Stuned_15;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case Bleeding:
    sound_stop_now();  
  waw_samle.dataLength =sizeof(Bleeding_16); //9474;
   waw_samle.data= Bleeding_16;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break;   

	case Hited:
   sound_stop_now();
   waw_samle.dataLength = sizeof(Hited_17);//26433;
  waw_samle.data= Hited_17;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    case Sniper:
	sound_stop_now();
   waw_samle.dataLength = sizeof(Sniper_18);//11782;
   waw_samle.data= Sniper_18;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;    
		case NeadHelp:
		sound_stop_now(); 
 waw_samle.dataLength=sizeof(NeadHelp_19);//4685;
 waw_samle.data= NeadHelp_19;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);

    break;
    	case Killed: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(Killed_20);//4262;
   waw_samle.data= Killed_20 ;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
     	case KilledByZombi: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(KilledByZombi_21);//1399;
   waw_samle.data= KilledByZombi_21;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case Bandage:
     sound_stop_now();  
   waw_samle.dataLength =sizeof(Bandage_22); //1520;
  waw_samle.data= Bandage_22;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break; 
    	case Medic: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(Medic_23);//2453;
   waw_samle.data=Medic_23;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    	case Reheneration: 
     sound_stop_now(); 
  waw_samle.dataLength =sizeof(Reheneration_24); //4885;
   waw_samle.data= Reheneration_24;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case Support:
    sound_stop_now();  
  waw_samle.dataLength =sizeof(Support_25); //9474;
   waw_samle.data= Support_25;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break;   

	case Ammo:
   sound_stop_now();
   waw_samle.dataLength = sizeof(Ammo_26);//26433;
  waw_samle.data= Ammo_26;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    case Disarmed:
	sound_stop_now();
   waw_samle.dataLength = sizeof(Disarmed_27);//11782;
   waw_samle.data= Disarmed_27;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
		case DoubleHealth:
		sound_stop_now(); 
 waw_samle.dataLength=sizeof(DoubleHealth_28);//4685;
 waw_samle.data= DoubleHealth_28;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);

    break;
    	case ArmyDoctor: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(ArmyDoctor_29);//4262;
   waw_samle.data= ArmyDoctor_29 ;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
     	case Anomal: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(Anomal_30);//1399;
   waw_samle.data= Anomal_30;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case Radiation:
     sound_stop_now();  
   waw_samle.dataLength =sizeof(Radiation_31); //1520;
  waw_samle.data= Radiation_31;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break; 
    	case BombDeact: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(BombDeact_32);//2453;
   waw_samle.data=BombDeact_32;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    	case Point: 
     sound_stop_now(); 
  waw_samle.dataLength =sizeof(Point_33); //4885;
   waw_samle.data= Point_33;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case Terminator:
    sound_stop_now();  
  waw_samle.dataLength =sizeof(Terminator_34); //9474;
   waw_samle.data= Terminator_34;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break;   

	case LastHero:
   sound_stop_now();
   waw_samle.dataLength = sizeof(LastHero_35);//26433;
  waw_samle.data= LastHero_35;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    case Zombi:
	sound_stop_now();
   waw_samle.dataLength = sizeof(Zombi_36);//11782;
   waw_samle.data= Zombi_36;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
		case Clowl:
		sound_stop_now(); 
 waw_samle.dataLength=sizeof(Clowl_37);//4685;
 waw_samle.data= Clowl_37;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);

    break;
    	case AkumGood: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(AkumGood_38);//4262;
   waw_samle.data= AkumGood_38 ;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
     	case AkumBad: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(AkumBad_39);//1399;
   waw_samle.data= AkumBad_39;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case Ticker:
     sound_stop_now();  
   waw_samle.dataLength =sizeof(Ticker_40); //1520;
  waw_samle.data= Ticker_40;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break; 
    	case Error: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(Error_41);//2453;
   waw_samle.data=Error_41;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    	case StartRecovery: 
     sound_stop_now(); 
  waw_samle.dataLength =sizeof(StartRecovery_42); //4885;
   waw_samle.data= StartRecovery_42;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case HilRPower:
    sound_stop_now();  
  waw_samle.dataLength =sizeof(HilRPower_43); //9474;
   waw_samle.data= HilRPower_43;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break;   

	case LowlRPower:
   sound_stop_now();
   waw_samle.dataLength = sizeof(LowlRPower_44);//26433;
  waw_samle.data= LowlRPower_44;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    case Pause:
	sound_stop_now();
   waw_samle.dataLength = sizeof(Pause_45);//11782;
   waw_samle.data= Pause_45;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
		case Red_s:
		sound_stop_now(); 
 waw_samle.dataLength=sizeof(Red_46);//4685;
 waw_samle.data= Red_46;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);

    break;
    	case Blue_s: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(Blue_47);//4262;
   waw_samle.data= Blue_47 ;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
     	case Yellow_s: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(Yellow_48);//1399;
   waw_samle.data= Yellow_48;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case Green_s:
     sound_stop_now();  
   waw_samle.dataLength =sizeof(Green_49); //1520;
  waw_samle.data= Green_49;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break; 
    	case GrenadeFire: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(GrenadeFire_50);//2453;
   waw_samle.data=GrenadeFire_50;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    	case GrenadeLoaded: 
     sound_stop_now(); 
  waw_samle.dataLength =sizeof(GrenadeLoaded_51); //4885;
   waw_samle.data= GrenadeLoaded_51;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case GredageExplosion:
    sound_stop_now();  
  waw_samle.dataLength =sizeof(GredageExplosion_52); //9474;
   waw_samle.data= GredageExplosion_52;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break;   

	case Scout:
   sound_stop_now();
   waw_samle.dataLength = sizeof(Scout_53);//26433;
  waw_samle.data= Scout_53;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    case AdminMode:
	sound_stop_now();
   waw_samle.dataLength = sizeof(AdminMode_54);//11782;
   waw_samle.data= AdminMode_54;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
		case SettingWrited:
		sound_stop_now(); 
 waw_samle.dataLength=sizeof(SettingWrited_55);//4685;
 waw_samle.data= SettingWrited_55;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);

    break;
    	case StatisticReaded: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(StatisticReaded_56);//4262;
   waw_samle.data= StatisticReaded_56 ;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
     	case StatisticCleared: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(StatisticCleared_57);//1399;
   waw_samle.data= StatisticCleared_57;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case RoundTimerON:
     sound_stop_now();  
   waw_samle.dataLength =sizeof(RoundTimerON_58); //1520;
  waw_samle.data= RoundTimerON_58;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break; 
    	case min10Left: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(min10Left_59);//2453;
   waw_samle.data=min10Left_59;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    	case min5Left: 
     sound_stop_now(); 
  waw_samle.dataLength =sizeof(min5Left_60); //4885;
   waw_samle.data= min5Left_60;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case min1Left:
    sound_stop_now();  
  waw_samle.dataLength =sizeof(min1Left_61); //9474;
   waw_samle.data= min1Left_61;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break;   

	case HaveFlag:
   sound_stop_now();
   waw_samle.dataLength = sizeof(HaveFlag_62);//26433;
  waw_samle.data= HaveFlag_62;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    case FlagStand:
	sound_stop_now();
   waw_samle.dataLength = sizeof(FlagStand_63);//11782;
   waw_samle.data= FlagStand_63;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    default:
   sound_stop_now();
	break;
}
}

void play_sound_num(uint8_t num)
{
switch (num)
	{
	  case 	0:
	  sound_stop_now();
	  break;
    //sound_stop_now();
		//звук выстрела
		case 1:
		sound_stop_now(); 
 waw_samle.dataLength=sizeof(NewGame_01);//4685;
 waw_samle.data= NewGame_01;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);

    break;
    	case 2: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(StartGame_02);//4262;
   waw_samle.data= StartGame_02 ;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
     	case 3: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(TimeOver_03);//1399;
   waw_samle.data= TimeOver_03;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case 4:
     sound_stop_now();  
   waw_samle.dataLength =sizeof(SpecialForces_04); //1520;
  waw_samle.data= SpecialForces_04;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break; 
    	case 5: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(Blood_05);//2453;
   waw_samle.data=Blood_05;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    	case 6: 
     sound_stop_now(); 
  waw_samle.dataLength =sizeof(Fire_06); //4885;
   waw_samle.data= Fire_06;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case 7:
    sound_stop_now();  
  waw_samle.dataLength =sizeof(SilentFire_07); //9474;
   waw_samle.data= SilentFire_07;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break;   

	case 8:
   sound_stop_now();
   waw_samle.dataLength = sizeof(HotFire_08);//26433;
  waw_samle.data= HotFire_08;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    case 9:
	sound_stop_now();
   waw_samle.dataLength = sizeof(Misfire_09);//11782;
   waw_samle.data= Misfire_09;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
		case 10:
		sound_stop_now(); 
 waw_samle.dataLength=sizeof(Miss_10);//4685;
 waw_samle.data= Miss_10;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);

    break;
    	case 11: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(FiringMode_11);//4262;
   waw_samle.data= FiringMode_11 ;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
     	case 12: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(StartReload_12);//1399;
   waw_samle.data= StartReload_12;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case 13:
     sound_stop_now();  
   waw_samle.dataLength =sizeof(EndReload_13); //1520;
  waw_samle.data= EndReload_13;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break; 
    	case 14: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(LastClip_14);//2453;
   waw_samle.data=LastClip_14;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    	case 15: 
     sound_stop_now(); 
  waw_samle.dataLength =sizeof(Stuned_15); //4885;
   waw_samle.data= Stuned_15;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case 16:
    sound_stop_now();  
  waw_samle.dataLength =sizeof(Bleeding_16); //9474;
   waw_samle.data= Bleeding_16;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break;   

	case 17:
   sound_stop_now();
   waw_samle.dataLength = sizeof(Hited_17);//26433;
  waw_samle.data= Hited_17;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    case 18:
	sound_stop_now();
   waw_samle.dataLength = sizeof(Sniper_18);//11782;
   waw_samle.data= Sniper_18;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;    
		case 19:
		sound_stop_now(); 
 waw_samle.dataLength=sizeof(NeadHelp_19);//4685;
 waw_samle.data= NeadHelp_19;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);

    break;
    	case 20: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(Killed_20);//4262;
   waw_samle.data= Killed_20 ;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
     	case 21: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(KilledByZombi_21);//1399;
   waw_samle.data= KilledByZombi_21;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case 22:
     sound_stop_now();  
   waw_samle.dataLength =sizeof(Bandage_22); //1520;
  waw_samle.data= Bandage_22;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break; 
    	case 23: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(Medic_23);//2453;
   waw_samle.data=Medic_23;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    	case 24: 
     sound_stop_now(); 
  waw_samle.dataLength =sizeof(Reheneration_24); //4885;
   waw_samle.data= Reheneration_24;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case 25:
    sound_stop_now();  
  waw_samle.dataLength =sizeof(Support_25); //9474;
   waw_samle.data= Support_25;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break;   

	case 26:
   sound_stop_now();
   waw_samle.dataLength = sizeof(Ammo_26);//26433;
  waw_samle.data= Ammo_26;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    case 27:
	sound_stop_now();
   waw_samle.dataLength = sizeof(Disarmed_27);//11782;
   waw_samle.data= Disarmed_27;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
		case 28:
		sound_stop_now(); 
 waw_samle.dataLength=sizeof(DoubleHealth_28);//4685;
 waw_samle.data= DoubleHealth_28;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);

    break;
    	case 29: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(ArmyDoctor_29);//4262;
   waw_samle.data= ArmyDoctor_29 ;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
     	case 30: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(Anomal_30);//1399;
   waw_samle.data= Anomal_30;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case 31:
     sound_stop_now();  
   waw_samle.dataLength =sizeof(Radiation_31); //1520;
  waw_samle.data= Radiation_31;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break; 
    	case 32: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(BombDeact_32);//2453;
   waw_samle.data=BombDeact_32;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    	case 33: 
     sound_stop_now(); 
  waw_samle.dataLength =sizeof(Point_33); //4885;
   waw_samle.data= Point_33;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case 34:
    sound_stop_now();  
  waw_samle.dataLength =sizeof(Terminator_34); //9474;
   waw_samle.data= Terminator_34;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break;   

	case 35:
   sound_stop_now();
   waw_samle.dataLength = sizeof(LastHero_35);//26433;
  waw_samle.data= LastHero_35;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    case 36:
	sound_stop_now();
   waw_samle.dataLength = sizeof(Zombi_36);//11782;
   waw_samle.data= Zombi_36;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
		case 37:
		sound_stop_now(); 
 waw_samle.dataLength=sizeof(Clowl_37);//4685;
 waw_samle.data= Clowl_37;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);

    break;
    	case 38: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(AkumGood_38);//4262;
   waw_samle.data= AkumGood_38 ;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
     	case 39: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(AkumBad_39);//1399;
   waw_samle.data= AkumBad_39;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case 40:
     sound_stop_now();  
   waw_samle.dataLength =sizeof(Ticker_40); //1520;
  waw_samle.data= Ticker_40;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break; 
    	case 41: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(Error_41);//2453;
   waw_samle.data=Error_41;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    	case 42: 
     sound_stop_now(); 
  waw_samle.dataLength =sizeof(StartRecovery_42); //4885;
   waw_samle.data= StartRecovery_42;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case 43:
    sound_stop_now();  
  waw_samle.dataLength =sizeof(HilRPower_43); //9474;
   waw_samle.data= HilRPower_43;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break;   

	case 44:
   sound_stop_now();
   waw_samle.dataLength = sizeof(LowlRPower_44);//26433;
  waw_samle.data= LowlRPower_44;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    case 45:
	sound_stop_now();
   waw_samle.dataLength = sizeof(Pause_45);//11782;
   waw_samle.data= Pause_45;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
		case 46:
		sound_stop_now(); 
 waw_samle.dataLength=sizeof(Red_46);//4685;
 waw_samle.data= Red_46;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);

    break;
    	case 47: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(Blue_47);//4262;
   waw_samle.data= Blue_47 ;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
     	case 48: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(Yellow_48);//1399;
   waw_samle.data= Yellow_48;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case 49:
     sound_stop_now();  
   waw_samle.dataLength =sizeof(Green_49); //1520;
  waw_samle.data= Green_49;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break; 
    	case 50: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(GrenadeFire_50);//2453;
   waw_samle.data=GrenadeFire_50;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    	case 51: 
     sound_stop_now(); 
  waw_samle.dataLength =sizeof(GrenadeLoaded_51); //4885;
   waw_samle.data= GrenadeLoaded_51;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case 52:
    sound_stop_now();  
  waw_samle.dataLength =sizeof(GredageExplosion_52); //9474;
   waw_samle.data= GredageExplosion_52;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break;   

	case 53:
   sound_stop_now();
   waw_samle.dataLength = sizeof(Scout_53);//26433;
  waw_samle.data= Scout_53;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    case 54:
	sound_stop_now();
   waw_samle.dataLength = sizeof(AdminMode_54);//11782;
   waw_samle.data= AdminMode_54;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
		case 55:
		sound_stop_now(); 
 waw_samle.dataLength=sizeof(SettingWrited_55);//4685;
 waw_samle.data= SettingWrited_55;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);

    break;
    	case 56: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(StatisticReaded_56);//4262;
   waw_samle.data= StatisticReaded_56 ;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
     	case 57: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(StatisticCleared_57);//1399;
   waw_samle.data= StatisticCleared_57;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case 58:
     sound_stop_now();  
   waw_samle.dataLength =sizeof(RoundTimerON_58); //1520;
  waw_samle.data= RoundTimerON_58;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break; 
    	case 59: 
		sound_stop_now();
   waw_samle.dataLength = sizeof(min10Left_59);//2453;
   waw_samle.data=min10Left_59;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    	case 60: 
     sound_stop_now(); 
  waw_samle.dataLength =sizeof(min5Left_60); //4885;
   waw_samle.data= min5Left_60;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break; 
    	case 61:
    sound_stop_now();  
  waw_samle.dataLength =sizeof(min1Left_61); //9474;
   waw_samle.data= min1Left_61;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND);
    break;   

	case 62:
   sound_stop_now();
   waw_samle.dataLength = sizeof(HaveFlag_62);//26433;
  waw_samle.data= HaveFlag_62;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    case 63:
	sound_stop_now();
   waw_samle.dataLength = sizeof(FlagStand_63);//11782;
   waw_samle.data= FlagStand_63;
     start_sound = true;
     timer_start(TIM_GRUP_SOUND, TIM_NUM_SOUND); 
    break;
    default:
   sound_stop_now();
	break;
}

}