
enum argument_error {
ok,						//аргумент имеет корректное значение
invalid,				//недопустимый аргумент   
out_of_range, 			//аргумент выходит за пределы корректных значений
empty					//аргумент пустой
};
typedef enum argument_error TARGUMENT_ERROR;

void command_0_slot(void);
void command_1_slot(void);
void command_2_slot(void);
void command_3_slot(void);
void command_4_slot(void);
void command_5_slot(void);
void command_6_slot(void);
void command_7_slot(void);
void command_8_slot(void);
void command_9_slot(void);
void command_10_slot(void);
void command_11_slot(void);
void command_12_slot(void);
void command_13_slot(void);
void command_14_slot(void);
void command_15_slot(void);
void command_16_slot(void);
void command_17_slot(void);
void command_18_slot(void);
void command_19_slot(void);
void command_20_slot(void);
void command_21_slot(void);
void command_22_slot(void);
void command_23_slot(void);
void command_24_slot(void);
void command_25_slot(void);
void command_26_slot(void);
void command_27_slot(void);
void command_28_slot(void);
void command_29_slot(void);
void command_30_slot(void);
void command_31_slot(void);
void command_32_slot(void);
void command_33_slot(void);
void command_34_slot(void);
void command_35_slot(void);
void command_36_slot(void);
void command_37_slot(void);
void command_38_slot(void);
void command_39_slot(void);
void command_40_slot(void);
void command_41_slot(void);
void command_42_slot(void);
void command_43_slot(void);
void command_44_slot(void);
void command_45_slot(void);
void command_46_slot(void);
void command_47_slot(void);
void command_48_slot(void);
void command_49_slot(void);
void command_50_slot(void);
void command_51_slot(void);
void command_52_slot(void);
void command_53_slot(void);
void command_54_slot(void);
void command_55_slot(void);
void command_56_slot(void);
void command_57_slot(void);
void command_58_slot(void);
void command_59_slot(void);
void command_60_slot(void);
void command_61_slot(void);
void command_62_slot(void);
void command_63_slot(void);
void command_64_slot(void);
void command_65_slot(void);
void command_66_slot(void);
void command_67_slot(void);
void command_68_slot(void);
void command_69_slot(void);
void command_70_slot(void);
void command_71_slot(void);
void command_72_slot(void);
void command_73_slot(void);
void command_74_slot(void);
void command_75_slot(void);
void command_76_slot(void);
void command_77_slot(void);
void command_78_slot(void);
void command_79_slot(void);
void command_80_slot(void);
void command_81_slot(void);
void command_82_slot(void);
void command_83_slot(void);
void command_84_slot(void);
void command_85_slot(void);
void command_86_slot(void);
void command_87_slot(void);
void command_88_slot(void);
void command_89_slot(void);

/****ключи для nvs***/
const char player_id_name[] = "player_id";
const char team_id_name[] = "team_id";
const char damage_name[] = "damage";
const char bullets_clip_name[] = "bullets_clip";
const char clips_name[] = "clips";
const char reload_time_name[] = "reload_time";
const char ir_power_name[] = "ir_power";
const char second_weapon_name[] = "second_weapon";
const char friendly_fire_name[] = "friendly_fire";
const char statistic_name[] = "statistic";
const char safe_duration_name[] = "safe_duration";
const char shock_time_name[] = "shock_time";
const char life_start_name[] = "life_start";
const char batt_full_name[] = "batt_full";
const char batt_low_name[] = "batt_low";
const char cyclic_rate_name[] = "cyclic_rate";
const char bt_name[] = "bt_name";
const char bt_pin_name[] = "bt_pin";
const char bt_connect_name[] = "bt_con_n_1";
const char bt_connect_adr_name[] = "bt_con_a_1";
const char time_off_name[] = "tim_off";
const char set1_name[] = "set1";
const char set2_name[] = "set2";
const char set3_name[] = "set3";
const char set4_name[] = "set4";
const char setting_name[] ="setting";


const unsigned char command_0[]  = "bullets_in_clip=";  // узнать размер (sizeof(command_0)-1)
const unsigned char command_1[]  = "bullets_in_clip?";  // 
const unsigned char command_2[]  = "protocol?";
const unsigned char command_3[]  = "clips=";  // 
const unsigned char command_4[]  = "clips?";  // 
const unsigned char command_5[]  = "time_off=";
const unsigned char command_6[]  = "time_off?";
const unsigned char command_7[]  = "com1";
const unsigned char command_8[]  = "com2";
const unsigned char command_9[]  = "com3";
const unsigned char command_10[]  = "com4";
const unsigned char command_11[]  = "com5";
const unsigned char command_12[]  = "com6";
const unsigned char command_13[]  = "com7";
const unsigned char command_14[]  = "play_sound";
const unsigned char command_15[]  = "statistic";
const unsigned char command_16[]  = "com8";
const unsigned char command_17[]  = "com9";
const unsigned char command_18[]  = "com18";
const unsigned char command_19[]  = "com17";
const unsigned char command_20[]  = "com16";
const unsigned char command_21[]  = "com15";
const unsigned char command_22[]  = "com14";
const unsigned char command_23[]  = "com13";
const unsigned char command_24[]  = "com12?";
const unsigned char command_25[]  = "com11";
const unsigned char command_26[]  = "sound_5_size?";
const unsigned char command_27[]  = "sound_6_adress=";
const unsigned char command_28[]  = "sound_6_adress?";
const unsigned char command_29[]  = "sound_6_size=";
const unsigned char command_30[]  = "sound_6_size?";
const unsigned char command_31[]  = "play_sound";
const unsigned char command_32[]  = "com10";
const unsigned char command_33[]  = "player_id=";
const unsigned char command_34[]  = "player_id?";
const unsigned char command_35[]  = "damage_index=";
const unsigned char command_36[]  = "damage_index?";
const unsigned char command_37[]  = "ir_power=";
const unsigned char command_38[]  = "ir_power?";
const unsigned char command_39[]  = "friendly_fire=";
const unsigned char command_40[]  = "friendly_fire?";
const unsigned char command_41[]  = "team_id=";
const unsigned char command_42[]  = "team_id?";
const unsigned char command_43[]  = "batt_full_voltage=";
const unsigned char command_44[]  = "batt_full_voltage?";
const unsigned char command_45[]  = "batt_low_voltage=";
const unsigned char command_46[]  = "batt_low_voltage?";
const unsigned char command_47[]  = "sound_7_adress=";
const unsigned char command_48[]  = "sound_7_adress?";
const unsigned char command_49[]  = "sound_7_size=";
const unsigned char command_50[]  = "sound_7_size?";
const unsigned char command_51[]  = "sound_8_adress=";
const unsigned char command_52[]  = "sound_8_adress?";
const unsigned char command_53[]  = "sound_8_size=";
const unsigned char command_54[]  = "sound_8_size?";
const unsigned char command_55[]  = "sound_9_adress=";
const unsigned char command_56[]  = "sound_9_adress?";
const unsigned char command_57[]  = "sound_9_size=";
const unsigned char command_58[]  = "sound_9_size?";
const unsigned char command_59[]  = "sound_10_adress=";
const unsigned char command_60[]  = "sound_10_adress?";
const unsigned char command_61[]  = "sound_10_size=";
const unsigned char command_62[]  = "sound_10_size?";
const unsigned char command_63[]  = "ir_carrier_frequency=";
const unsigned char command_64[]  = "ir_carrier_frequency?";
const unsigned char command_65[]  = "ver";
const unsigned char command_66[]  = "reload_duration=";
const unsigned char command_67[]  = "reload_duration?";
const unsigned char command_68[]  = "life_after_start=";
const unsigned char command_69[]  = "life_after_start?";
const unsigned char command_70[]  = "cyclic_rate=";
const unsigned char command_71[]  = "cyclic_rate?";
const unsigned char command_72[]  = "safe_duration=";
const unsigned char command_73[]  = "safe_duration?";
const unsigned char command_74[]  = "shock_time?";
const unsigned char command_75[]  = "shock_time=";
const unsigned char command_76[]  = "second_weapon?";
const unsigned char command_77[]  = "second_weapon=";
const unsigned char command_78[]  = "boot";
const unsigned char command_79[]  = "statistic_tager?";
const unsigned char command_80[]  = "statistic?";
const unsigned char command_81[]  = "statistic=";
const unsigned char command_82[]  =  "device_name?";
const unsigned char command_83[]  =  "device_name=";
const unsigned char command_84[]  = "connect_name?";
const unsigned char command_85[]  = "connect_name=";
const unsigned char command_86[]  = "connect_adr?";
const unsigned char command_87[]  = "connect_adr=";
const unsigned char command_88[]  = "pin_set?";
const unsigned char command_89[]  = "pin_set=";



const unsigned char* commandsPointers[]  = 
{
command_0,
command_1,
command_2,
command_3,
command_4,
command_5,
command_6,
command_7,
command_8,
command_9,
command_10,
command_11,
command_12,
command_13,
command_14,
command_15,
command_16,
command_17,
command_18,
command_19,
command_20,
command_21,
command_22,
command_23,
command_24,
command_25,
command_26,
command_27,
command_28,
command_29,
command_30,
command_31,
command_32,
command_33,
command_34,
command_35,
command_36,
command_37,
command_38,
command_39,
command_40,
command_41,
command_42,
command_43,
command_44,
command_45,
command_46,
command_47,
command_48,
command_49,
command_50,
command_51,
command_52,
command_53,
command_54,
command_55,
command_56,
command_57,
command_58,
command_59,
command_60,
command_61,
command_62,
command_63,
command_64,
command_65,
command_66,
command_67,
command_68,
command_69,
command_70,
command_71,
command_72,
command_73,
command_74,
command_75,
command_76,
command_77,
command_78,
command_79,
command_80,
command_81,
command_82,
command_83,
command_84,
command_85,
command_86,
command_87,
command_88,
command_89
};



const unsigned char unknown_command_error[]  = "ERROR:unknown command\r\n";
const unsigned char command_error[]  = "ERROR\r\n";
const unsigned char parameter_empty_error[]  = "ERROR:parameter is not specified\r\n";
const unsigned char parameter_out_of_range_error[]  = "ERROR:parameter out of range\r\n";
const unsigned char parameter_invalid_error[]  = "ERROR:invalid parameter\r\n";
const unsigned char spase[]  = " ";
const unsigned char ok_string[]  = "\r\nOK\r\n";
const unsigned char ok_strm[]  = "OK\r\n";
const unsigned char red_vibro[]  = "rv\r\n";
const unsigned char blue_vibro[]  = "bv\r\n";
const unsigned char yellou_vibro[]  = "yv\r\n";
const unsigned char green_vibro[]  = "gv\r\n";
const unsigned char key_correct[] = "\r\nLIC KEY GOOD!\r\n"	;
const unsigned char key_no_correct[] = "\r\nLIC KEY INCORRECT!\r\n";
const unsigned char key_error[]="ERROR:INVALID KEY\r\n";
const unsigned char cr_lf[]  = "\r\n";
const unsigned char comma[]  = ",";


const unsigned char protocol[]  = 	
											"Rounds in clip;int(0,999);bullets_in_clip?;bullets_in_clip=\r\n"

											"Clips;int(0,999);clips?;clips=\r\n"

											"Quickfirer (rounds/min);int(30,800);cyclic_rate?;cyclic_rate=\r\n"

											"Player ID;int(0,127);player_id?;player_id=\r\n"

											"Team color;enum(Red,Blue,Yellow,Green);team_id?;team_id=\r\n"

											"Damage;enum(1%,2%,4%,5%,7%,10%,15%,17%,20%,25%,30%,35%,40%,50%,75%,100%);damage_index?;damage_index=\r\n"

											"Friendly fire;enum(No,Yes);friendly_fire?;friendly_fire=\r\n"

											"Health;int(0,999);life_after_start?;life_after_start=\r\n"

											"Invincibility after being wounded (in tenths of ms.);int(0,30000);safe_duration?;safe_duration=\r\n"

											"Shock time (in tenths of ms.);int(0,30000);shock_time?;shock_time=\r\n"

											"IR radiation power;enum(7%,17%,35%,57%,78%,85%,92%,100%);ir_power?;ir_power=\r\n"

											"Reload cycle duration (sec.);int(0,99);reload_duration?;reload_duration=\r\n"

											"Charged battery voltage (mV);int(3000,45000);batt_full_voltage?;batt_full_voltage=\r\n"

											"Low battery voltage (mV);int(2700,45000);batt_low_voltage?;batt_low_voltage=\r\n" 
											
                                            "Time OFF;int(0,255);time_off?;time_off=\r\n"
											//"Statistic;enum(No,Yes_block,Yes_no_block);statistic?;statistic=\r\n"
											;


