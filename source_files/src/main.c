//Стандартные библиотеки ESP_IDF//
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/rmt.h"
#include "driver/timer.h"
#include "esp_err.h"
#include "driver/dac.h"
#include "driver/adc.h"
//пользовательские библиотеки//
#include "global_variables.h"//глобальные переменные
#include "eeprom.h"//енергонезависимая память
#include "ssd1306.h"//драйвер экрана
#include "sound_dr.h"//драйвер звука
#include "image.h"//картинки для экрана
#include "pgmspase.h"//для работы с данными записаными на флешь (пережиток переделывать не стал)
#include "btm_driver.h"//БТ драйвер
#include "ws2812.h"//RGB драйвер
//декларация функций//

//тело прерываний//
void IRAM_ATTR global_timer_IRS(void *arg);
void IRAM_ATTR tsop_isr_handler(void* arg);
void IRAM_ATTR off_on_handler(void* arg);
void IRAM_ATTR display_handler(void* arg);
void IRAM_ATTR timer_ir_tx_rx_ISR(void *arg);
//инициализация таймеров//
void  global_timer_Init(void);
void timer_ir_tx_rx_Init(void);
//звуковой таймер инициализируется в библиотеке драйвера

//инициализация потров ввода вывода//
void ports_init_rx_tx(void);
void ports_init(void);

//функции дисплея//
void display_status(void);
void display_bullets_update(void);
void display_clips_update(void);
void display_life_update(void);
void display_voltage_update(void);
void bt_display(void);
void display_off(void);

//инициализация переменных//
void init_var_global(void);
void init_var_rx_tx(void);

//функции команд//
void new_game(void);
void recovery_clips(void);
void recovery_life(void);
void set_color_team_now(void);
void set_damage_now(void);
void set_damage_temp(void);
void game_over(void);
void invite(void);
void print_statistic_page(uint32_t page);
//функции блютуз//

void bt_data(void);
trx_event parsing_bt_data(void);
bool get_bt_buffer_bit(uint8_t);
trx_packet get_bt_packet_value();
void USART_FlushRxBuf(void);
void set_bt_buffer_bit(uint8_t index, bool value);
uint32_t parsing_uint32_argument_value(void);
trx_event parsing_bt_data(void);
void parsing_command(void);
uint8_t get_command_index(void);//проверим, что за команда пришла по UART
void finde_message_in_bt_buffer(void);
void get_int_argument_value(uint8_t var_adress,const char* key, uint8_t min_val, uint8_t max_val);
void get_word_argument_value(uint16_t var_adress,const char* key, uint16_t min_val, uint16_t max_val);
void get_str_argument(char *var_adress,const char* key, uint8_t length);
void get_u32_argument_value(uint32_t var_adress,const char* key, uint32_t min_val, uint32_t max_val);
//функции ИК//
void send_ir_package(void);
void ir_tx_cursor_home(void);//устанавливаем курсор в начало буфера
void get_ir_protocol(void); //погрешности интервалов
void led_invert(void);
void set_buffer_bit(uint8_t, bool);	////Задаем значение биту в буфере ИК-приемника
tir_message get_ir_message_from_buffer(void);
tir_message get_ir_message_from_bt_buffer(void); 
bool get_buffer_bit(uint8_t);
//функции установки параметров//
void set_player_id(uint8_t ID);
void set_cyclic_deley_counter(void);
trx_packet get_packet_value(void);
tgun_damage gun_damage(void);//Определяем текущий урон, наносимый нашим тагом
tteam_color team_id(void); 
tget_ir_currect_modet gun_power_ir(void);
void set_team_color(tteam_color);
void set_gun_damage(tgun_damage );
void set_gun_ir_power(tget_ir_currect_modet);
//функции статистики/
void statistic_count(trx_packet hit_packet);
void death_shoots(void);
void print_statistic_page(uint32_t page);
//функция обработки попадания//
void hit_processing(trx_packet hit_packet);
uint8_t get_light_color_hit(trx_packet hit_packet);
//общие функции //
uint8_t char_to_int(char c);
char* int_to_str(uint8_t x, uint8_t digits);
char* long_int_to_str(uint16_t x, uint8_t digits);
//задача контроля батареи//
void adc_Task(void* arg);
//функция выключения//
void off_device(void);
//функии для кнопок//
TKEYBOARD_STATUS get_keyboard_status(void);
TKEYBOARD_STATUS get_reload_key_status(void);
TKEYBOARD_EVENT test_keyboard(void);
TKEYBOARD_EVENT test_reload_key(void);
TFIRE_MODE_STATUS fire_mode(void);
/*******************/
void app_main(void)
{ 
	


#if (HARDWARE_MODE==1)
      ports_init_rx_tx();
	 init_var_global();
      timer_ir_tx_rx_Init();
	 check_key_bt=false;
     setPin(eeprom_bt_pin);
	 BluetoothSerial_begin(eeprom_devise_name,true);
     connect_to_name(eeprom_con_name);   
	xTaskCreate(ws2812_Task, "ws2812_tack", 2048, NULL, 5, NULL);
	 xTaskCreate(adc_Task, "adc_read",2048, NULL, 3,NULL);	
get_light_color(bat_lvl,4,0,1000);
vTaskDelay(2000 / portTICK_PERIOD_MS);
if(BluetoothSerial_hasClient()==false)
{
for	(int i=0;i<5;i++)
{		 
get_light_color(bat_lvl,4,0,1000);
vTaskDelay(2000 / portTICK_PERIOD_MS);
while(BluetoothSerial_hasClient()==true)
{
	

	if(BluetoothSerial_available())
{

switch(BluetoothSerial_read())
{
case'\r':
break;	
case 'v':
//printf("vibro\n");
break;	
case 'r':
get_light_color(0,16,0,300);
break;
case 'b':
get_light_color(1,16,0,300);
break;
case 'y':
get_light_color(2,16,0,300);
break;
case 'g':
get_light_color(3,16,0,300);
break;
case 'c':
get_light_color(255,16,0,300);
break;
default:
break;
}
}
}
}
}
while(BluetoothSerial_hasClient()==true)
{	

	if(BluetoothSerial_available())
{
switch(BluetoothSerial_read())
{
case'\r':
break;
case 'v':
//printf("vibro\n");
break;	
case 'r':
get_light_color(0,16,0,300);
break;
case 'b':
get_light_color(1,16,0,300);
break;
case 'y':
get_light_color(2,16,0,300);
break;
case 'g':
get_light_color(3,16,0,300);
break;
case 'c':
get_light_color(255,16,0,300);
break;
default:
break;
}
}
}
//vTaskDelay(50 / portTICK_PERIOD_MS);
    printf("Restarting now.\n");
   fflush(stdout);
    esp_restart();	
#endif



#if (HARDWARE_MODE==0)

       first_on=true;  
      ports_init();
      ports_init_rx_tx();
	  gpio_set_level(OFF_ON_OUT,1);
	 init_var_global();
     global_timer_Init();
     timer_sound_Init();
     timer_ir_tx_rx_Init();
     ssd1306_init(NUM_OLED,SCL_OLED, SDA_OLED,RES_OLED);
	 //printf("ssd1306 init ok\n");
	 ssd1306_clear(NUM_OLED);
	 //printf("ssd1306 clear ok\n");
	 ssd1306_refresh(NUM_OLED, true);
	 //printf("ssd1306 refresh ok\n");
	 ssd1306_select_font(NUM_OLED, FONT_TEXT);
	 //printf("ssd1306 font ok\n");
     setPin(eeprom_bt_pin);
	 BluetoothSerial_begin(eeprom_devise_name,false);
    ws2812_parametrs = xQueueCreate(10, sizeof(tparametrs));
	// bool set_flag=true;
     //printf("init ok\n");
death_col = 0;
shoots_tmp_col = 0;
statistic_upload_f=false;

ssd1306_draw_string(NUM_OLED, 45, 0, "LTASCET", 1, 0);
ssd1306_draw_string(NUM_OLED, 45, 16, "ESP32", 1, 0);
ssd1306_refresh(NUM_OLED, true);
//printf("oled ok\n");
get_light_color(eeprom.team_id,LED_NUMBER,0,300);   //функция цвета
//printf("ws2812 ok\n");
vTaskDelay(500 / portTICK_PERIOD_MS);
set_cyclic_deley_counter();
display_status();
timer_start(TIM_GRUP_GLOBAL, TIM_NUM_GLOBAL );
//printf("global timer start 0k\n");
first_on=false; 
 xTaskCreate(ws2812_Task, "ws2812_tack", 2048, NULL, 5, NULL);
xTaskCreate(adc_Task, "adc_read",2048, NULL, 4,NULL);
if (gpio_get_level(OUT_POWER_OLED)==0)
{
ssd1306_clear(NUM_OLED);
ssd1306_refresh(NUM_OLED, true);
}
while(1){
if(set_or_game==false)
{
set_or_game=true;	
}
mode_device=0;					
if(off_on_flag==true)
{
off_device();
}
if(display_mode_status==true)
{
display_off();	
}	

if (chit_detected)
	{ 
  display_status();
   
		while (chit_detected)
		{
         if(off_on_flag==true)
{
off_device();
}
if(display_mode_status==true)
{
display_off();	
}

			if(start_sound==false)
		{
		display_voltage_update();			
		//play_sound_from_flash(sonar_sound);
		play_sound_from_flash_LW(Pause);
		vTaskDelay(2000 / portTICK_PERIOD_MS);	
		}
		};
		keyboard_event=no_key_pressing;
		reload_key_event=no_key_pressing;
  display_status(); 	
	}    

		switch(rx_event)//выясним, какое именно событие произошло
					{
						//printf("rx switch begin\n");

						case RX_COMPLETE: 	//получен пакет
						{
							 //printf("RX_COMPLETE\n");
							rx_event = NOT_EVENT;	
							if(!get_buffer_bit(0)) //если этот бит равен 0, то это пакет с данными (выстрел)
							{
								rx_packet = get_packet_value();
								hit_processing(rx_packet);
								rx_event = NOT_EVENT;
                            
							}
						
							break;
						}
						
						case RX_MESSAGE_COMPLITE://принято сообщение
						{
							rx_event = NOT_EVENT;							
							if(get_buffer_bit(0)) //если этот бит равен 1, то это пакет с командой
                        	{
                           		ir_message = get_ir_message_from_buffer();//выдергиваем значения команды из буфера ИК приемника
                        
                           	 if (ir_message.control_byte ==Valid_value)//сообщение принято корректно (контрольный байт принят без ошибок)
							 {
								switch(ir_message.ID)//если имя команды
                           		{
                              		case Add_Health: //добавить "жизни"
                              		
										//код для добавления жизни
                                 		break;
                              	
                              		case Add_Rounds://добавить "патронов"
                                 
								 		//код для добавления патронов
                                 		break;
										
										
                              		
//case Set_life:// установить хх жизней
									
 
  //                           life_in_percent = ir_message.param;
 //              status_need_update = true;
//			   eeprom_write_byte((uint8_t *)&life_after_start,ir_message.param);
//			   beep(1000, 2, 128);
  //                           break;
                                  
									case Set_damage://установить хх урон
                                    set_damage_now();
                                    break;
									

								   case Set_damage_tmp://установить хх урон
                                   set_damage_temp();
                                   break;


                            		case Change_color:
									set_color_team_now();		
									break;
  
									case Command://какая то дополнительноя команда	
										switch(ir_message.param)//выясним, какая это командв
										{
										   // case 0x05://начать новую игру немедленно
										   case New_Game_Now:
											
									new_game();                                       
                                        break;
                               //   #if CONFIGURATION_PIO ==5
								//   case 0xFC://slave chit_detect true
                                //    chit_detect_slave=true;
                                 //       break;
                                //   case 0xFD://slave chit_detect false
                                 //   chit_detect_slave=false;
                                //        break;
								//	#endif
								//	#if CONFIGURATION_PIO ==6
								//   case 0xFC://slave chit_detect true
                                //    chit_detect_slave=true;
                                //        break;
                                //   case 0xFD://slave chit_detect false
                                //    chit_detect_slave=false;
                                //        break;
								//	#endif		
                                         //   case 0x0D://(заполнить магазин)добавить Х магазинов
									case Rec_Ammo:											
                                    recovery_clips();
                                        break;
	                                
                                            // case 0xFE://режим настроек
                                    case Setting_Mode:
                                           invite();
                                        break;
								    case Tager_off:
                                           BluetoothSerial_str_write("Restarting\n",11);
                                           printf("Restarting now.\n");
                                           vTaskDelay(500 / portTICK_PERIOD_MS);
                                           fflush(stdout);
										   gpio_set_level(OFF_ON_OUT,0);
                                           esp_restart();
                                        break;
									
                                          //  case 0x06://востановить здоровье до 100% (аптечка)
										  case Rec_Life:
                                    recovery_life();  
	                                    break;
										//	case 0x00://"выключить" игрока 
                                    case Admin_Kill:
									game_over();
										break;
									default: 
									    break;
										}
										break;
                              	}//switch(ir_message.ID)
                                    }//if (ir_message.control_byte ==Valid_value)	
							}	
                           			else//неправильный контрольный байт ошибка приема
							{
								rx_event = RX_ERROR;
							}
                        	 
							rx_event = NOT_EVENT;
							break;

						
						}
						
						case RX_ERROR:		//ошибка приема
						{
                            if(!(ir_error_ignore))//если не надо игнорировать ошибку и звук не воспроизводиться уже
                            {
						    play_sound_from_flash(flying_bullet_sound);
							//play_sound_from_flash_LW(Miss);
                            
                            }
                            rx_event = NOT_EVENT;
						
							break;
						}
						
						case NOT_EVENT:		//ошибка приема
						{
					
							break;
						}



					}// switch (rx_event)



//BluetoothSerial_available

if (rxCount>0)//если буфер BT приемника не пустой
	{
       bt_data();
	}
	
switch(keyboard_event)
	{
	 	     case no_key_pressing:
             display_voltage_update();
			 //display_bullets_update();
		break;
		     case key_pressing:
		//printf("key_pressing\n");

		  if(!(shock_counter==0))
	{
		//printf("shock_counter!=0\n");
	keyboard_event=no_key_pressing;
	//printf("shock time %d\n",shock_counter);		
		break;
	}
		  if(!(reload_countdown==0) )
	{
		//printf("shock_counter!=0\n");
	keyboard_event=no_key_pressing;
	if(start_sound==false)
	{
	//play_sound_from_flash(misfire_sound);
	play_sound_from_flash_LW(Misfire);
	}
	//printf("reload_countdown  %d\n",reload_countdown );		
		break;
	}
    if (!eeprom.life_after_start)
	{	
		//	play_sound_from_flash(misfire_sound);
		//printf("!eeprom.life_after_start\n");
keyboard_event=no_key_pressing;
			break;
	}


	if (eeprom.bullets_in_clip==0)
	{
		//printf("eeprom.bullets_in_clip==0\n");			
keyboard_event=no_key_pressing;
//play_sound_from_flash(misfire_sound);
play_sound_from_flash_LW(Misfire);
			break;
	}
	   switch(fire_mode())
	   {
	   case queues:
     //  printf("queues\n");
	 //  printf("%d\n",cyclic_deley_counter);
if((eeprom.bullets_in_clip>0)&&(cyclic_deley_counter==0))	
        {
		eeprom.bullets_in_clip--;//уменьшаем на 1 количество патронов
		display_bullets_update();	            
	    send_ir_package();
        //play_sound_from_flash(shot_sound);
		play_sound_from_flash_LW(Fire);
	//	printf("shoot\n");
		}
		if ((fire_mode()==queues)&&(cyclic_deley_counter==0)&&(get_keyboard_status()==key_pressed))
{
set_cyclic_deley_counter();
//printf("set_cnt\n");
//sound_stop_now();	
}

	   break;
       case single:
	eeprom.bullets_in_clip--;   
	display_bullets_update();	            
	send_ir_package();
    //play_sound_from_flash(shot_sound);
	play_sound_from_flash_LW(Fire);
	//printf("single\n");
    keyboard_event=no_key_pressing;
	   break;
	   default:
	  // printf("default\n");
	   break;
	   }
	   default:
	   break;
	   keyboard_event=no_key_pressing;	   
   
	}						
switch(reload_key_event)
	{
		//printf("reload_key_event begin\n");
	 	case no_key_pressing: 
		 //printf("no_key_pressing begin\n");
		break;
		case key_pressing:
		//printf("key_pressing begin\n");

			if (reload_state==nothing_to_do)
			{		
	if (eeprom.clips > 0)
				{	
					reload_countdown =  eeprom.reload_duration*10000;
					//printf("reload_countdown1 %d\n",reload_countdown );
					reload_state=waiting_countdown;
                    //play_sound_from_flash(clip_out_sound);
					play_sound_from_flash_LW(StartReload);
					eeprom.clips--;//уменьшаем на 1 количество обойм
			        eeprom.bullets_in_clip=bullets;
					reload_key_event=no_key_pressing; 
				
				}
			}
			break;
  
		default:
		reload_key_event=no_key_pressing;
		//printf("reload_key_event\n");
		break;
		}



switch (reload_state)
	{
		     case nothing_to_do:
		break;
		     case waiting_countdown:
			 //printf("reload_countdown2 %d\n",reload_countdown );
		break;
		     case reload_now:
		//printf("reload_countdown3 %d\n",reload_countdown );
			//eeprom.clips--;//уменьшаем на 1 количество обойм
			//eeprom.bullets_in_clip=bullets;
			//nvs_get_u8(eeprom_nvs_handle, "bullets_clip", &eeprom.bullets_in_clip);
			display_clips_update();
			display_bullets_update();
			if(!((waw_samle.data==wav_hit_sound)&&(start_sound==true)))
			{ 
		    //play_sound_from_flash(clip_in_sound);
			play_sound_from_flash_LW(EndReload);
			reload_state = nothing_to_do;
			reload_key_event=no_key_pressing;
			}
		break;
	}

if (status_need_update) 
	{
		if (!((waw_samle.data==wav_hit_sound)&&(start_sound==true)))//если не играет звук ранения
		{
        display_status(); 
		status_need_update = false;
		}
		
	}
	//	if (display_bullets_update_now>0) 
	//	{
	//		display_bullets_update();
	//		display_bullets_update_now--;
	//	}

if((gpio_get_level(FIRE_KEY)==0)&&(fire_mode()==queues)&&(eeprom.bullets_in_clip>0))
	   {		   
		keyboard_event=key_pressing;   
	   }
	vTaskDelay(10/ portTICK_PERIOD_MS);   
	}
printf("error departure from the while");
#endif

}

void ports_init(void)
{   
	/*ИНИЦИАЛИЗАЦИЯ ВХОДНЫХ ПОРТОВ БЕЗ ПРЕРЫВАНИЙ*/
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = KEY_INPUT_PIN_SEL;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);
/*ИНИЦИАЛИЗАЦИЯ ВЫХОДНЫХ ПОРТОВ*/
	io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT_OUTPUT;
    io_conf.pin_bit_mask = GPIO_OUTPUT_INPUT_PIN_SEL;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);
/*ИНИЦИАЛИЗАЦИЯ ВХОДНЫХ ПОРТОВ С ПРЕРЫВАНИЯМИ*/
    io_conf.intr_type =  GPIO_INTR_NEGEDGE;
    io_conf.pin_bit_mask =  OFF_ON_PIN_SEL ;  
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);

    gpio_set_intr_type(BUTTON_OFF_ON_KEY ,GPIO_INTR_NEGEDGE);
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);   
    gpio_isr_handler_add(BUTTON_OFF_ON_KEY, off_on_handler, (void*) BUTTON_OFF_ON_KEY);//

    gpio_set_intr_type(BUTTION_OLED ,GPIO_INTR_NEGEDGE);
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    gpio_isr_handler_add(BUTTION_OLED, display_handler, (void*) BUTTION_OLED);
	

	//printf("ports init ok\n");
}

TKEYBOARD_STATUS get_keyboard_status(void) {
volatile	TKEYBOARD_STATUS s_ret;	
	switch (gpio_get_level(FIRE_KEY)) //проверяем, нажат ли курок
		{ 
			case 1: s_ret=no_key_pressed  ; 
			break;
			default: s_ret=key_pressed ;			
		}
		return s_ret;
}

TKEYBOARD_STATUS get_reload_key_status(void) {
volatile	TKEYBOARD_STATUS s_ret;
	switch (gpio_get_level(RELOAD_KEY)) //проверяем, нажат ли кнопка "перезарядить"
		{
			case 1: s_ret=no_key_pressed  ; 
      break;
			default: s_ret=key_pressed ;	
		}
		return s_ret;
}

 TKEYBOARD_EVENT test_keyboard(void){
	TKEYBOARD_STATUS key_status;
	TKEYBOARD_EVENT ret_ev;
	key_status=get_keyboard_status();
	switch(key_status)  //проверяем, что нажато
	{
		case no_key_pressed: 
		{
			if (key_pressing_duration.key_1>= SHORT_DURATION)
			{
				ret_ev=key_pressing;
                key_pressing_duration.key_1    =0;
                key_pressing_duration.key_1_inc=0;
				return ret_ev;
			}
			else 
			{
				ret_ev=no_key_pressing;
                key_pressing_duration.key_1    =0;
                key_pressing_duration.key_1_inc=1;			
			}
		
		} 
		break;
	 	case key_pressed  : //нажата кнопка 1
		{ 
			if(key_pressing_duration.key_1>= SHORT_DURATION)
			{
				ret_ev=key_pressing;
             	key_pressing_duration.key_1    =0;
              key_pressing_duration.key_1_inc=0;
			} 
			else 
			{
				key_pressing_duration.key_1 += key_pressing_duration.key_1_inc; 
        ret_ev=keyboard_event;
			}
		}
		break;
		default: ret_ev=keyboard_event;	
	}
return   ret_ev;
}

TKEYBOARD_EVENT test_reload_key(void){
	TKEYBOARD_STATUS key_status;
	TKEYBOARD_EVENT ret_ev;
	key_status=get_reload_key_status();
	switch(key_status)  //проверяем, что нажато
	{
		case no_key_pressed: 
		{
			if (key_pressing_duration.key_2>= SHORT_DURATION)
			{
				ret_ev=key_pressing;
                key_pressing_duration.key_2    =0;
                key_pressing_duration.key_2_inc=0;
				return ret_ev;
			}
			else 
			{
				ret_ev=no_key_pressing;
                key_pressing_duration.key_2    =0;
                key_pressing_duration.key_2_inc=1;
			}
		} 
		break;
	 	case key_pressed  : //нажата кнопка "Перезарядить"
		{ 
			if(key_pressing_duration.key_2>= SHORT_DURATION)
			{
				ret_ev=key_pressing;
             	key_pressing_duration.key_2    =0;
                key_pressing_duration.key_2_inc=0;
			} 
			else 
			{
				key_pressing_duration.key_2 += key_pressing_duration.key_2_inc; 
                ret_ev=reload_key_event;
			}
		}
		break;
		default: ret_ev=reload_key_event;
	}
return   ret_ev;
}

 TFIRE_MODE_STATUS fire_mode(void)//Определяем текущий режим огня (одиночный/очередями)
{
TFIRE_MODE_STATUS result;
if (gpio_get_level(FIRE_MODE_KEY)==1)
 {
result =queues;
 }
else
{  
result = single;
}
return result;
}

char* int_to_str(uint8_t x, uint8_t digits){

static volatile char str[6];

volatile uint8_t celoe, ostatok;
celoe=x;
int digits_tmp;
digits_tmp=digits;
if (digits == 0) digits_tmp=3;
      for (int i=(digits_tmp-1); i>=0; i--)
      {        
      ostatok= celoe%10;
	  celoe  = celoe/10;
	  str[i]= pgm_read_byte(&numbers[ostatok]);
      }
      str[digits_tmp]='\0';	  
if (digits == 0)	
{
        while ((str[0]=='0')&&(str[1] !='\0'))
		{ 
		for (int i=0; i < (6-1); i++) str[i]=str[i+1];
		}
}
      return (char*)&str;      

}

char* long_int_to_str(uint16_t x, uint8_t digits)
{
static volatile char str[6];
volatile uint16_t celoe, ostatok;
celoe=x;
int digits_tmp;
digits_tmp=digits;
if (digits == 0) digits_tmp=5;
      for (int i=(digits_tmp-1); i>=0; i--)
      {   
      ostatok= celoe%10;
	  celoe  = celoe/10;
	  str[i]= numbers[ostatok];
      }
      str[digits_tmp]='\0';	  
if (digits == 0)	
{
        while ((str[0]=='0')&&(str[1] !='\0')) for (int i=0; i < (6-1); i++) str[i]=str[i+1];
}
      return (char*)&str;      
}

void display_off(void)
{

vTaskDelay(300 / portTICK_PERIOD_MS);
		
if(gpio_get_level(OUT_POWER_OLED)==0)
{
gpio_set_level(OUT_POWER_OLED,1);
switch(mode_device)
		 {
		 case 0:
	     display_status();
		 break;
		 case 1:
	     display_status();
		 break;
		 case 2:
	      ssd1306_clear(NUM_OLED);
          ssd1306_draw_string(NUM_OLED, 45, 12,"SETTINGS", 1, 0);
          ssd1306_refresh(NUM_OLED, true);
		 break;
		 case 3:
	      ssd1306_clear(NUM_OLED);
          ssd1306_draw_string(NUM_OLED, 45, 12,"NO KEY", 1, 0);
          ssd1306_refresh(NUM_OLED, true);
		 break;
		 }
		 		 
}
else
{
gpio_set_level(OUT_POWER_OLED,0);
ssd1306_clear(NUM_OLED);
ssd1306_refresh(NUM_OLED, true);
}
display_mode_status=false;
gpio_set_intr_type(BUTTION_OLED ,GPIO_INTR_NEGEDGE);
gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
gpio_isr_handler_add(BUTTION_OLED, display_handler, (void*) BUTTION_OLED);
}

void off_device(void)
{
 bool off=false;
 uint8_t cnt=eeprom_time_off;
        ssd1306_clear(NUM_OLED);
		ssd1306_refresh(NUM_OLED, true);
		vTaskDelay(100 / portTICK_PERIOD_MS);
		ssd1306_draw_string(NUM_OLED, 25, 8, "DEVICE OFF", 1, 0);
		ssd1306_refresh(NUM_OLED, true);
		vTaskDelay(100 / portTICK_PERIOD_MS);
while(off_on_flag==true)
{

	   if(gpio_get_level(BUTTON_OFF_ON_KEY)==0)
		{
		if(cnt>0)
		{
         //for(uint8_t cnt=eeprom_time_off;cnt>0;cnt--)
         		
         ssd1306_draw_string(NUM_OLED, 45, 18, int_to_str(cnt,2), 1, 0);
		 ssd1306_refresh(NUM_OLED, true);
		 cnt--;
		 //printf("cnt :%d\n",cnt);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
		}
		else
		{
		off_on_flag=false;	
		}
		if(cnt==0)
		{				
		off=true;
		}
		}		
		else
		{	
		ssd1306_clear(NUM_OLED);	
		vTaskDelay(100 / portTICK_PERIOD_MS);
		ssd1306_draw_string(NUM_OLED, 5, 10, "DEVICE OFF STOP", 1, 0);	
        ssd1306_refresh(NUM_OLED, true);
		vTaskDelay(500 / portTICK_PERIOD_MS);
		if(gpio_get_level(OUT_POWER_OLED)==0)
		 {
		 ssd1306_clear(NUM_OLED);	 
         ssd1306_refresh(NUM_OLED, true);  
		 }	 
		 switch(mode_device)
		 {
		 case 0:
	     display_status();
		 break;
		 case 1:
	     display_status();
		 break;
		 case 2:
	      ssd1306_clear(NUM_OLED);
 if(gpio_get_level(OUT_POWER_OLED)==1)
		 {
  ssd1306_draw_string(NUM_OLED, 45, 12,"SETTINGS", 1, 0);
  ssd1306_refresh(NUM_OLED, true);
		 }
		 break;
		 case 3:
	      ssd1306_clear(NUM_OLED);
          ssd1306_draw_string(NUM_OLED, 45, 12,"NO KEY", 1, 0);
          ssd1306_refresh(NUM_OLED, true);
		 break;
		 }
		 off_on_flag=false;
		}		
		}
		 if(off==true)
		 {
		 gpio_set_level(OFF_ON_OUT,0);
		 vTaskDelay(500 / portTICK_PERIOD_MS);
		 fflush(stdout);
         esp_restart();
		 } 
		 switch(mode_device)
		 {
		 case 0:
	     display_status();
		 break;
		 case 1:
	     display_status();
		 break;
		 case 2:
		 if(gpio_get_level(OUT_POWER_OLED)==1)
		 {
	      ssd1306_clear(NUM_OLED);
          ssd1306_draw_string(NUM_OLED, 45, 12,"SETTINGS", 1, 0);
          ssd1306_refresh(NUM_OLED, true);
		 }
		 break;
		 case 3:
	      ssd1306_clear(NUM_OLED);
          ssd1306_draw_string(NUM_OLED, 45, 12,"NO KEY", 1, 0);
          ssd1306_refresh(NUM_OLED, true);
		 break;
		 } 	
    gpio_set_intr_type(BUTTON_OFF_ON_KEY ,GPIO_INTR_NEGEDGE);
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    gpio_isr_handler_add(BUTTON_OFF_ON_KEY, off_on_handler, (void*) BUTTON_OFF_ON_KEY);
	timer_start(TIM_GRUP_GLOBAL, TIM_NUM_GLOBAL );
	
}

void adc_Task(void* arg)
{
    adc1_config_width ( ADC_WIDTH_12Bit ); 
    adc1_config_channel_atten ( ADC_IN  , ADC_ATTEN_0db ); 
     //R1 = 27000; // resistance of R1 (27K)
    // R2 = 10000;  // resistance of R2 (10K)

	for(;;)
	{
        uint32_t voltage = 0;
		uint32_t sum=0;
        for (int i = 0; i < NO_OF_SAMPLES; i++) 
		{

          sum += adc1_get_raw(ADC_IN); 
		}
		voltage =sum /NO_OF_SAMPLES;
        voltage = ((voltage * 1100) / 4096.0)+3000;

       bat_lvl = ((6*(voltage - eeprom.batt_low_voltage)) / (eeprom.batt_full_voltage- eeprom.batt_low_voltage));
		//printf("voltage:%d\n",voltage );
		//printf("bat lvl:%d\n",bat_lvl);
        vTaskDelay(pdMS_TO_TICKS(10000));

    }

//vTaskDelete(NULL);

}


void init_var_global(void)
{
off_on_flag=false;
display_mode_status=false;
gpio_set_level(OUT_POWER_OLED,1);	
check_eeprom();
init_var_rx_tx();
eeprom.bullets_in_clip=0;
key_pressing_duration.key_1    =0;//обнуляем счетчики 
						  //длительности
						  //непрерывного нажатия кнопок
key_pressing_duration.key_1_inc=1;//разрешаем отсчет длительности
key_pressing_duration.key_2    =0;//обнуляем счетчики 
						  //длительности
						  //непрерывного нажатия кнопок
key_pressing_duration.key_2_inc=1;//разрешаем отсчет длительности
chit_detected_counter=0;
chit_detected = true;
display_bullets_update_now = 0;
shock_counter=0;
receiver_on = false;
ir_error_ignore = 0; //не игнорируем ошибочные пакеты
reload_countdown=0;
status_need_update = true;
bit_in_bt_rx_buff = 0;
cr_received = false; 
bt_header_received = false;
safe_counter = 0;//обратный счетчик времени неуязвимости после ранения
cyclic_deley_counter =(600000/eeprom.cyclic_rate)/*10*/;//задержка между выстрелами при автоматической стрельбе в тиках таймера
statistic_tmp=eeprom.statistic_enable;
}


void display_status()//выводим на дисплей текущее значение жизни, патронов, магазинов 
{

   #if (SSD1306 == 0)
   if (gpio_get_level(OUT_POWER_OLED)==1)
  {	
     ssd1306_clear(NUM_OLED);
  ssd1306_refresh(NUM_OLED, true);
  ssd1306_select_font(NUM_OLED, FONT_TEXT);
  ssd1306_draw_string(NUM_OLED, 21, 3,long_int_to_str(eeprom.life_after_start,3), 1, 0);
  ssd1306_draw_string(NUM_OLED, 21, 18,int_to_str(eeprom.bullets_in_clip,3), 1, 0);
  ssd1306_draw_string(NUM_OLED, 65, 18,int_to_str(eeprom.clips,3), 1, 0);
  ssd1306_drawBitmap(NUM_OLED,0, 0, image_data_life14, 14, 14, 0); 
  ssd1306_drawBitmap(NUM_OLED,0, 16, image_data_ammo14, 14, 14, 0);
  ssd1306_drawBitmap(NUM_OLED,45, 16, image_data_clips14, 14, 14, 0);
  ssd1306_refresh(NUM_OLED, true);
  }
  else
  {
	vTaskDelay(50 / portTICK_PERIOD_MS); 
  }  
  #elif (SSD1306 == 1)
  if (gpio_get_level(OUT_POWER_OLED)==1)
  {	
     ssd1306_clear(NUM_OLED);
  ssd1306_refresh(NUM_OLED, true);
  ssd1306_select_font(NUM_OLED, FONT_TEXT);
  ssd1306_draw_string(NUM_OLED, 21, 3,long_int_to_str(eeprom.life_after_start,3), 1, 0);
  ssd1306_draw_string(NUM_OLED, 21, 18,int_to_str(eeprom.bullets_in_clip,3), 1, 0);
  ssd1306_draw_string(NUM_OLED, 65, 18,int_to_str(eeprom.clips,3), 1, 0);
  ssd1306_drawBitmap(NUM_OLED,0, 0, image_data_life14, 14, 14, 0); 
  ssd1306_drawBitmap(NUM_OLED,0, 16, image_data_ammo14, 14, 14, 0);
  ssd1306_drawBitmap(NUM_OLED,45, 16, image_data_clips14, 14, 14, 0);
  ssd1306_refresh(NUM_OLED, true);
  }
  else
  {
	vTaskDelay(50 / portTICK_PERIOD_MS); 
  }  

    #elif (SSD1306 == 2)	
  if (gpio_get_level(OUT_POWER_OLED)==1)
  {
  ssd1306_clear(NUM_OLED);
  ssd1306_refresh(NUM_OLED, true);
  ssd1306_select_font(NUM_OLED, FONT_TEXT);  
  ssd1306_draw_string(NUM_OLED, 16, 3,long_int_to_str(eeprom.life_after_start,3), 1, 0);
  ssd1306_draw_string(NUM_OLED, 16, 21,int_to_str(eeprom.bullets_in_clip,3), 1, 0);
  ssd1306_draw_string(NUM_OLED, 52, 21,int_to_str(eeprom.clips,3), 1, 0);
  ssd1306_drawBitmap(NUM_OLED,0, 0, image_data_life14, 14, 14, 0); 
  ssd1306_drawBitmap(NUM_OLED,0, 16, image_data_ammo14, 14, 14, 0);
  ssd1306_drawBitmap(NUM_OLED,36, 16, image_data_clips14, 14, 14, 0);  
  ssd1306_refresh(NUM_OLED, true);
  }
  else
  {
	vTaskDelay(50 / portTICK_PERIOD_MS); 
  }
 #endif 
}

void bt_display(void)
{
 
#if (SSD1306 == 0)
if (gpio_get_level(OUT_POWER_OLED)==1)
  {		
if(BluetoothSerial_hasClient()==true){
ssd1306_drawBitmap(NUM_OLED,78, 0, image_data_bt, 7, 7, 0);
ssd1306_refresh(NUM_OLED, true);
}
else
{
ssd1306_drawBitmap(NUM_OLED,78, 0, image_data_bt_no, 7, 7, 1);
ssd1306_refresh(NUM_OLED, true);	
	
}
  }
  else
  {
	vTaskDelay(50 / portTICK_PERIOD_MS); 
  }	
 #elif (SSD1306 == 1)
 if (gpio_get_level(OUT_POWER_OLED)==1)
  {		
if(BluetoothSerial_hasClient()==true){
ssd1306_drawBitmap(NUM_OLED,78, 0, image_data_bt, 7, 7, 0);
ssd1306_refresh(NUM_OLED, true);
}
else
{
ssd1306_drawBitmap(NUM_OLED,78, 0, image_data_bt_no, 7, 7, 1);
ssd1306_refresh(NUM_OLED, true);	
	
}
  }
  else
  {
	vTaskDelay(50 / portTICK_PERIOD_MS); 
  }	
 #elif (SSD1306 == 2)
  
 if (gpio_get_level(OUT_POWER_OLED)==1)
  {		
if(BluetoothSerial_hasClient()==true){
ssd1306_drawBitmap(NUM_OLED,50, 0, image_data_bt, 7, 7, 0);
ssd1306_refresh(NUM_OLED, true);
}
else
{
ssd1306_drawBitmap(NUM_OLED,50, 0, image_data_bt_no, 7, 7, 1);
ssd1306_refresh(NUM_OLED, true);	
	
}
  }
  else
  {
	vTaskDelay(50 / portTICK_PERIOD_MS); 
  }	
#endif
}

void display_bullets_update(void)
{
#if (SSD1306 == 0)	

if (gpio_get_level(OUT_POWER_OLED)==1)
  {				
ssd1306_draw_string(NUM_OLED, 21, 18,int_to_str(eeprom.bullets_in_clip,3), 1, 0);	
ssd1306_refresh(NUM_OLED, true);
}
else
  {
	vTaskDelay(50 / portTICK_PERIOD_MS); 
  }
 #elif (SSD1306 == 1)
 if (gpio_get_level(OUT_POWER_OLED)==1)
  {				
ssd1306_draw_string(NUM_OLED, 21, 18,int_to_str(eeprom.bullets_in_clip,3), 1, 0);	
ssd1306_refresh(NUM_OLED, true);
}
else
  {
	vTaskDelay(50 / portTICK_PERIOD_MS); 
  }
 #elif (SSD1306 == 2)
 if (gpio_get_level(OUT_POWER_OLED)==1)
  {				
ssd1306_draw_string(NUM_OLED, 16, 21,int_to_str(eeprom.bullets_in_clip,3), 1, 0);	
ssd1306_refresh(NUM_OLED, true);
}
else
  {
	vTaskDelay(50 / portTICK_PERIOD_MS); 
  }
#endif
}

void display_clips_update(void)
{
#if (SSD1306 == 0)

if (gpio_get_level(OUT_POWER_OLED)==1)
  {		
  ssd1306_draw_string(NUM_OLED, 65, 18,int_to_str(eeprom.clips,3), 1, 0);
  ssd1306_refresh(NUM_OLED, true);	
  }
  else
  {
	vTaskDelay(50 / portTICK_PERIOD_MS); 
  }
#elif (SSD1306 == 1)
if (gpio_get_level(OUT_POWER_OLED)==1)
  {		
  ssd1306_draw_string(NUM_OLED, 65, 18,int_to_str(eeprom.clips,3), 1, 0);
  ssd1306_refresh(NUM_OLED, true);	
  }
  else
  {
	vTaskDelay(50 / portTICK_PERIOD_MS); 
  }
#elif (SSD1306 == 2)
if (gpio_get_level(OUT_POWER_OLED)==1)
  {		
  ssd1306_draw_string(NUM_OLED, 52, 21,int_to_str(eeprom.clips,3), 1, 0);
  ssd1306_refresh(NUM_OLED, true);	
  }
  else
  {
	vTaskDelay(50 / portTICK_PERIOD_MS); 
  }
#endif
}

 void display_life_update(void)
 {
	#if (SSD1306 == 0) 
	if (gpio_get_level(OUT_POWER_OLED)==1)
  {	 
   	ssd1306_draw_string(NUM_OLED, 21, 3,long_int_to_str(eeprom.life_after_start,3), 1, 0);
	ssd1306_refresh(NUM_OLED, true); 
  }
   else
  {
	vTaskDelay(50 / portTICK_PERIOD_MS); 
  }	
  #elif (SSD1306 == 1)
  	if (gpio_get_level(OUT_POWER_OLED)==1)
  {	 
   	ssd1306_draw_string(NUM_OLED, 21, 3,long_int_to_str(eeprom.life_after_start,3), 1, 0);
	ssd1306_refresh(NUM_OLED, true); 
  }
   else
  {
	vTaskDelay(50 / portTICK_PERIOD_MS); 
  }	
  #elif (SSD1306 == 2)
  	if (gpio_get_level(OUT_POWER_OLED)==1)
  {	 
   	ssd1306_draw_string(NUM_OLED, 16, 3,long_int_to_str(eeprom.life_after_start,3), 1, 0);
	ssd1306_refresh(NUM_OLED, true); 
  }
   else
  {
	vTaskDelay(50 / portTICK_PERIOD_MS); 
  }	
#endif
 }

void display_voltage_update(void)
{   

#if (SSD1306 == 0)	
	  if (gpio_get_level(OUT_POWER_OLED)==1)
  {	 
	    switch (bat_lvl)
		{
		case 0:
        ssd1306_drawBitmap(NUM_OLED,94, 0, image_data_bat0, 7, 7, 1);
        ssd1306_refresh(NUM_OLED, true);
		break;
        case 1:
        ssd1306_drawBitmap(NUM_OLED,94, 0, image_data_bat1, 7, 7, 1);
        ssd1306_refresh(NUM_OLED, true);
		break;
        case 2:
        ssd1306_drawBitmap(NUM_OLED,94, 0, image_data_bat2, 7, 7, 1);
        ssd1306_refresh(NUM_OLED, true);
		break;
        case 3:
        ssd1306_drawBitmap(NUM_OLED,94, 0, image_data_bat3, 7, 7, 1);
       ssd1306_refresh(NUM_OLED, true);
		break;
        case 4:
        ssd1306_drawBitmap(NUM_OLED,94, 0, image_data_bat4, 7, 7, 1);
       ssd1306_refresh(NUM_OLED, true);
		break;
        case 5:
        ssd1306_drawBitmap(NUM_OLED,94, 0, image_data_bat5, 7, 7, 1);
        ssd1306_refresh(NUM_OLED, true);
		break;
		default:
		ssd1306_drawBitmap(NUM_OLED,94, 0, image_data_bat5, 7, 7, 1);
        ssd1306_refresh(NUM_OLED, true);
		break;
		}
	 bt_display();
  }
  else
  {
	vTaskDelay(50 / portTICK_PERIOD_MS); 
  }
  #elif (SSD1306 == 1) 
  	  if (gpio_get_level(OUT_POWER_OLED)==1)
  {	 
	    switch (bat_lvl)
		{
		case 0:
        ssd1306_drawBitmap(NUM_OLED,94, 0, image_data_bat0, 7, 7, 1);
        ssd1306_refresh(NUM_OLED, true);
		break;
        case 1:
        ssd1306_drawBitmap(NUM_OLED,94, 0, image_data_bat1, 7, 7, 1);
        ssd1306_refresh(NUM_OLED, true);
		break;
        case 2:
        ssd1306_drawBitmap(NUM_OLED,94, 0, image_data_bat2, 7, 7, 1);
        ssd1306_refresh(NUM_OLED, true);
		break;
        case 3:
        ssd1306_drawBitmap(NUM_OLED,94, 0, image_data_bat3, 7, 7, 1);
       ssd1306_refresh(NUM_OLED, true);
		break;
        case 4:
        ssd1306_drawBitmap(NUM_OLED,94, 0, image_data_bat4, 7, 7, 1);
       ssd1306_refresh(NUM_OLED, true);
		break;
        case 5:
        ssd1306_drawBitmap(NUM_OLED,94, 0, image_data_bat5, 7, 7, 1);
        ssd1306_refresh(NUM_OLED, true);
		break;
		default:
		ssd1306_drawBitmap(NUM_OLED,94, 0, image_data_bat5, 7, 7, 1);
        ssd1306_refresh(NUM_OLED, true);
		break;
		}
	 bt_display();
  }
  else
  {
	vTaskDelay(50 / portTICK_PERIOD_MS); 
  }
 #elif (SSD1306 == 2) 
	  if (gpio_get_level(OUT_POWER_OLED)==1)
  {	 
	    switch (bat_lvl)
		{
		case 0:
        ssd1306_drawBitmap(NUM_OLED,60, 0, image_data_bat0, 7, 7, 1);
        ssd1306_refresh(NUM_OLED, true);
		break;
        case 1:
        ssd1306_drawBitmap(NUM_OLED,60, 0, image_data_bat1, 7, 7, 1);
        ssd1306_refresh(NUM_OLED, true);
		break;
        case 2:
        ssd1306_drawBitmap(NUM_OLED,60, 0, image_data_bat2, 7, 7, 1);
        ssd1306_refresh(NUM_OLED, true);
		break;
        case 3:
        ssd1306_drawBitmap(NUM_OLED,60, 0, image_data_bat3, 7, 7, 1);
       ssd1306_refresh(NUM_OLED, true);
		break;
        case 4:
        ssd1306_drawBitmap(NUM_OLED,60, 0, image_data_bat4, 7, 7, 1);
       ssd1306_refresh(NUM_OLED, true);
		break;
        case 5:
        ssd1306_drawBitmap(NUM_OLED,60, 0, image_data_bat5, 7, 7, 1);
        ssd1306_refresh(NUM_OLED, true);
		break;
		default:
		ssd1306_drawBitmap(NUM_OLED,60, 0, image_data_bat5, 7, 7, 1);
        ssd1306_refresh(NUM_OLED, true);
		break;
		}
	 bt_display();
  }
  else
  {
	vTaskDelay(50 / portTICK_PERIOD_MS); 
  }
#endif
}

void new_game(void)
{
timer_pause(TIMER_GROUP_0 , TIMER_1 );  
eeprom_read_val(4);
eeprom_read_val(9);
timer_start(TIMER_GROUP_0 , TIMER_1 ); 
eeprom.bullets_in_clip=0;//Устанавливаем количество патронов											
keyboard_event=no_key_pressing;//очищаем события триггера
reload_key_event=no_key_pressing;//очищаем события перезарядки
rx_event = NOT_EVENT;   //очищаем события ИК приемника												
display_status(); 
get_light_color(eeprom.team_id,LED_NUMBER,0,1000 );
play_sound_from_flash_LW(StartGame);
set_or_game=true;
}

void recovery_clips(void)
{
eeprom.bullets_in_clip=0;
display_bullets_update();
eeprom.clips=clips;
display_clips_update();
get_light_color(eeprom.team_id,LED_NUMBER,0,300);
}

void invite(void)  //приглашение  в меню настроек
{
  timer_pause(TIM_GRUP_GLOBAL, TIM_NUM_GLOBAL );
set_or_game=false;
play_sound_from_flash_LW(AdminMode);
  ssd1306_clear(NUM_OLED);
  ssd1306_select_font(NUM_OLED, FONT_TEXT);
  ssd1306_refresh(NUM_OLED, true);
  ssd1306_draw_string(NUM_OLED, 10, 12,"SETTINGS", 1, 0);
  ssd1306_refresh(NUM_OLED, true);
  
		while(gpio_get_level(RELOAD_KEY)==1) //(gpio_get_level(RELOAD_KEY)==0) //пока не нажата перезарядка
		{//[while]
		//display_off();
         mode_device=2;
		if(off_on_flag==true)
{
off_device();
}
if(display_mode_status==true)
{
display_off();	
}
              			display_voltage_update();			
                         bt_display();
					             					                  
			if (cr_received)//если появилось что то в УАРТ
				{	
					
					parsing_command();
                   
                  
				}	
				if (gpio_get_level(FIRE_KEY)==0)//если нажат спуск
				{

                 if (BluetoothSerial_hasClient())//если блютус соединение установлено
					{
						while(gpio_get_level(FIRE_KEY)==0)//пока нажат курок
						{        
			get_light_color(eeprom.team_id,LED_NUMBER,0,300 );
				vTaskDelay(2000 / portTICK_PERIOD_MS);			

						}
					}
					
					
					keyboard_event=no_key_pressing;
				}	
 
	vTaskDelay(30 / portTICK_PERIOD_MS);		
	}//[/while]

	timer_start(TIM_GRUP_GLOBAL, TIM_NUM_GLOBAL );
	keyboard_event=no_key_pressing;
	play_sound_from_flash_LW(SettingWrited);
	vTaskDelay(2500 / portTICK_PERIOD_MS);
    new_game();
	}

void recovery_life(void)
{
eeprom.life_after_start=life_in_percent;
display_life_update();
get_light_color(eeprom.team_id,LED_NUMBER,0,300);	
}

void set_color_team_now(void)
{
timer_pause(TIM_GRUP_GLOBAL, TIM_NUM_GLOBAL );	
uint8_t result=ir_message.param;
eeprom.team_id=result;
nvs_flash_init ();
nvs_handle_t eeprom_nvs_handle;
nvs_open(NAME_NVS, NVS_READWRITE, &eeprom_nvs_handle);
nvs_set_u8(eeprom_nvs_handle, team_id_name, eeprom.team_id);
nvs_commit(eeprom_nvs_handle);
nvs_close(eeprom_nvs_handle);
nvs_flash_deinit();	
set_team_color(team_id());	//Устанавливаем идентификатор (цвет) команды
get_light_color(eeprom.team_id,LED_NUMBER,0,300);
timer_start(TIM_GRUP_GLOBAL, TIM_NUM_GLOBAL );	
}

 uint8_t char_to_int(char c)
     {
       switch(c)
       {
         case '0': return 0;
         case '1': return 1;
         case '2': return 2;
         case '3': return 3;
         case '4': return 4;
         case '5': return 5;
         case '6': return 6;
         case '7': return 7;
         case '8': return 8;
         case '9': return 9;
         default : return 0x55;
         
       }
     }

void set_damage_now(void)
{
timer_pause(TIM_GRUP_GLOBAL, TIM_NUM_GLOBAL );	
uint8_t result=ir_message.param;
eeprom.damage=result;
nvs_flash_init ();
nvs_handle_t eeprom_nvs_handle;
nvs_open(NAME_NVS, NVS_READWRITE, &eeprom_nvs_handle);
nvs_set_u8(eeprom_nvs_handle, damage_name, eeprom.damage);
nvs_commit(eeprom_nvs_handle);
nvs_close(eeprom_nvs_handle);
nvs_flash_deinit();	
set_gun_damage(gun_damage());
get_light_color(eeprom.team_id,LED_NUMBER,0,300);
timer_start(TIM_GRUP_GLOBAL, TIM_NUM_GLOBAL );
}

void set_damage_temp(void)
{	
set_gun_damage(ir_message.param);
get_light_color(eeprom.team_id,LED_NUMBER,0,300);	
}

void game_over(void)
{
	eeprom.life_after_start=0;
    get_light_color(eeprom.team_id,LED_NUMBER,0,0 );
	
	display_life_update();//отобразим уровень жизни на ЖКИ

uint16_t cl=0;
uint16_t cl_in=0;
			//статистика//
			switch(eeprom.statistic_enable){
		case 0:
		break;
        case 1:
        
            death_col++;
			cl=clips;
		    cl_in=bullets;
            shoots_tmp_col =((cl-clips)*cl_in)-bullets;
            death_shoots();
			 
		break;
        case 2:
         death_col++;
		cl=clips;
		cl_in=bullets;
            shoots_tmp_col =((cl-clips)*cl_in)-bullets;
            death_shoots();
		break;
        
		}			
play_sound_from_flash_LW(Killed);
			rx_event = NOT_EVENT;
			ir_message.control_byte = 0;
			timer_pause(TIM_GRUP_GLOBAL, TIM_NUM_GLOBAL );
while(!((ir_message.control_byte ==Valid_value)&&(ir_message.ID==Command)&&((ir_message.param==New_Game_Now)||(ir_message.param==Setting_Mode))))//пока не получим команду "старт" или выключить тагер

				{//[while]
				//display_off();
                 mode_device=1;
				if(off_on_flag==true)
{
off_device();
}
if(display_mode_status==true)
{
display_off();	
}
	              //printf("while\n");
                   if(BluetoothSerial_hasClient()==false)
					   {

                         

						 // printf("bt disconnect\n");  
						if(start_sound==false)
						{  
						play_sound_from_flash_LW(Pause);
						} 
						 display_voltage_update();
                         bt_display();
						 vTaskDelay(pdMS_TO_TICKS(500));
					   }
					  
					   else
					   { 

                       get_light_color(eeprom.team_id,LED_NUMBER,0,300);

					   display_voltage_update();
					   bt_display();                 
                       display_life_update();
					   bt_display();
					   vTaskDelay(pdMS_TO_TICKS(1000));
					   



				rx_event = NOT_EVENT;				
					
					if (rx_event == RX_MESSAGE_COMPLITE){ ir_message = get_ir_message_from_buffer();}//пришла команда пульта, выдергиваем значения команды из буфера ИК приемника	
					else //[else]
					{							
						if (rxCount>0) finde_message_in_bt_buffer();							
					}//[else]
				}//else BluetoothSerial_hasClient											
				}//[while]
			if(ir_message.param==New_Game_Now){
			timer_start(TIM_GRUP_GLOBAL, TIM_NUM_GLOBAL );	
			new_game();
			}
            if(ir_message.param==Setting_Mode){	
invite();
}

}

void hit_processing(trx_packet hit_packet)//обрабатываем попадание
{	
if (!(safe_counter==0)) 
{
	return; //если время неуязвимости ещё не кончилось, то выходим
}
if ( (hit_packet.team_id != team_id() )||((eeprom.friendly_fire_enable==1)&&(hit_packet.player_id != eeprom.player_id)))//"пуля" прилетела от игрока другой, не нашей, команды
	{
		cyclic_deley_counter = 0; //останавливаем счетчик задержки до следующего выстрела



switch(eeprom.statistic_enable)
{
		case 0:
		break;
        case 1:
        statistic_count(hit_packet);
		break;
        case 2:
        statistic_count(hit_packet);
		break;
		default:
		break;
} 


		get_light_color(get_light_color_hit(hit_packet),LED_NUMBER,0,300 );
		gpio_set_level(RELAY,1 );
		if (eeprom.life_after_start > hit_packet.damage) 
		{
			safe_counter = eeprom.safe_duration*10; //время неуязвимости
			shock_counter=eeprom.shock_time*10;
			eeprom.life_after_start = eeprom.life_after_start-(hit_packet.damage);
            display_life_update();
			play_sound_from_flash_LW(Hited);
            
			keyboard_event=no_key_pressing;
			gpio_set_level(RELAY,0 );
			
		}
		else //[else]
		{	
  display_status(); 
  game_over();		
}//[else]
}
}

void global_timer_Init(void)
{

        timer_config_t config = {
		.alarm_en = TIMER_ALARM_EN, // Включить прерывание Alarm
		.counter_en = TIMER_PAUSE, // Состояние - пауза
		.intr_type = TIMER_INTR_LEVEL, // Прерывание по уровню
		.counter_dir = TIMER_COUNT_UP, // Считать вверх
		.auto_reload = TIMER_AUTORELOAD_EN , // Автоматически перезапускать счет
		.divider = 80, // Предделитель 1MHz 1uS (для TTGO =52)
		
		};

	// Применить конфиг
	timer_init(TIM_GRUP_GLOBAL, TIM_NUM_GLOBAL , &config);
	// Установить начальное значение счетчика
	timer_set_counter_value(TIM_GRUP_GLOBAL, TIM_NUM_GLOBAL , 0x00000000ULL);
	// Установить значение счетчика для срабатывания прерывания Alarm
	timer_set_alarm_value(TIM_GRUP_GLOBAL, TIM_NUM_GLOBAL ,CAR_FREQ_GLOBAL);//для 56кгц fq_clk=9
	// Разрешить прерывания
	timer_enable_intr(TIM_GRUP_GLOBAL, TIM_NUM_GLOBAL );
	// Зарегистрировать обработчик прерывания
	//timer_isr_register(grup, num, timer0_ISR, (void *)&ir_packet_info, ESP_INTR_FLAG_IRAM, NULL);
    timer_isr_register(TIM_GRUP_GLOBAL, TIM_NUM_GLOBAL , global_timer_IRS, NULL, ESP_INTR_FLAG_IRAM, NULL);
	// Запустить таймер
	//printf("global timer init 0k\n");
	//timer_start(TIM_GRUP_GLOBAL, TIM_NUM_GLOBAL );
	////printf("global timer start 0k\n");
    //timer_pause(TIM_GRUP_GLOBAL, TIM_NUM_GLOBAL ); 

}

void IRAM_ATTR global_timer_IRS(void *arg)
{
	
   // timer_pause(TIM_GRUP_GLOBAL, TIM_NUM_GLOBAL );
    // Очистить флаги прерываний
	timer_group_clr_intr_status_in_isr(TIM_GRUP_GLOBAL, TIM_NUM_GLOBAL );
	// Перезапустить прерывание Alarm
	timer_group_enable_alarm_in_isr(TIM_GRUP_GLOBAL,TIM_NUM_GLOBAL );
global_timer=true;	
portENTER_CRITICAL_ISR(&mutex);
if(cyclic_deley_counter>0)
{ 
cyclic_deley_counter--;//уменьшаем значение обратного счетчика задержки между выcтрелами
}
if(shock_counter>0)
{ 
shock_counter--;
}

                if(!(ir_error_ignore==0))
				{ 
				ir_error_ignore--;
				}
				if (!(safe_counter==0))
				{ 
				safe_counter--;
				}
		switch(keyboard_event) 
			{
		  	case no_key_pressing: 
		  		{
					keyboard_event=test_keyboard(); 
					break;
				}
		  	default:;         
			}	

		switch(reload_key_event)
			{
		  	case no_key_pressing: 
		  		{
					reload_key_event=test_reload_key(); 
					break;
				}
		  	default:
			break ;         
			}		
		if(reload_countdown > 0) //обратный отсчет длительности перезарядки не окончен
		{
			reload_countdown--;
		}
		else //пора закончить перезаряд 
		{
			if(reload_state==waiting_countdown)
			{
			reload_state=reload_now;
			}
		} 
		portEXIT_CRITICAL_ISR(&mutex);
	global_timer=false;	
}

void timer_ir_tx_rx_Init()
{
      
        timer_config_t config = {
		.alarm_en = TIMER_ALARM_EN, // Включить прерывание Alarm
		.counter_en = TIMER_PAUSE, // Состояние - пауза
		.intr_type = TIMER_INTR_LEVEL, // Прерывание по уровню
		.counter_dir = TIMER_COUNT_UP, // Считать вверх
		.auto_reload = TIMER_AUTORELOAD_EN , // Автоматически перезапускать счет
		//.divider = 80, // Предделитель 1MHz 1mS
		.divider = 80 // Предделитель 52 для TTGO (26Mhz) 80 для (40Mhz)
		};

	// Применить конфиг
	timer_init(TIM_GRUP_IR, TIM_NUM_IR, &config);
	// Установить начальное значение счетчика
	timer_set_counter_value(TIM_GRUP_IR, TIM_NUM_IR, 0x00000000ULL);
	// Установить значение счетчика для срабатывания прерывания Alarm
	timer_set_alarm_value(TIM_GRUP_IR, TIM_NUM_IR,CAR_FREQ);//для 56кгц fq_clk=9
	// Разрешить прерывания
	timer_enable_intr(TIM_GRUP_IR, TIM_NUM_IR);
	// Зарегистрировать обработчик прерывания
	//timer_isr_register(TIM_GRUP_IR, TIM_NUM_IR, timer0_ISR, (void *)&ir_packet_info, ESP_INTR_FLAG_IRAM, NULL);
    timer_isr_register(TIM_GRUP_IR, TIM_NUM_IR, timer_ir_tx_rx_ISR, NULL, ESP_INTR_FLAG_IRAM, NULL);
	//printf("rx tx timer init 0k\n");
	// Запустить таймер
	//timer_start(TIM_GRUP_IR, TIM_NUM_IR);
    //timer_pause(TIM_GRUP_IR, TIM_NUM_IR);   
}

void ports_init_rx_tx()
{
    gpio_config_t io_conf;
    io_conf.intr_type =  GPIO_INTR_NEGEDGE;
    io_conf.pin_bit_mask = (1ULL<<TSOP_IN );  
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);

    gpio_set_intr_type(TSOP_IN ,GPIO_INTR_NEGEDGE);

    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);

    gpio_isr_handler_add(TSOP_IN , tsop_isr_handler, (void*) TSOP_IN );

   dac_output_enable(IR_OUT );

}

void IRAM_ATTR off_on_handler(void* arg)
{
	if(first_on==false)
{
gpio_isr_handler_remove(BUTTON_OFF_ON_KEY);
off_on_flag=true;	
}	
}

void IRAM_ATTR display_handler(void* arg)
{

gpio_isr_handler_remove(BUTTION_OLED);
display_mode_status=true;

	
}

void IRAM_ATTR timer_ir_tx_rx_ISR(void *arg)
{
// Очистить флаги прерываний
	timer_group_clr_intr_status_in_isr(TIM_GRUP_IR, TIM_NUM_IR);
	// Перезапустить прерывание Alarm
	timer_group_enable_alarm_in_isr(TIM_GRUP_IR, TIM_NUM_IR);

static volatile uint8_t prt;
prt = gpio_get_level(TSOP_IN ); 
if (prt==0) //На ножке ИК-приемника низкий уровень сигнала (пойман сигнал несущей)
	{
		
		low_level_counter++;//Увеличиваем счетчик длительности низкоуровнего сигнала на ножке ИК-приемника


	}
else  //На ножке ИК-приемника высокий уровень сигнала (пойман сигнал несущей)
	{
		high_level_counter++;///Увеличиваем счетчик длительности высокоуровнего сигнала на ножке ИК-приемника
		if((start_bit_received)&&(high_level_counter > IR_ZERO*8)/*&&(bit_in_rx_buff>=13)*/)
		{//Фиксируем окончание приема по таймауту
			start_bit_received	= false; 	//отменяем прием
/************************/						
			switch(bit_in_rx_buff)//проверим, сколько бит принято
			{
				case 14:
				{
					rx_event = RX_COMPLETE;			//Генерим событие "принят пакет"
					#if (HARDWARE_MODE==1)
					BluetoothSerial_byte_write('t');
					#endif
					break;	
				}
				case 24:
				{
					rx_event = 	RX_MESSAGE_COMPLITE;//принято сообщение;
					#if (HARDWARE_MODE==1)
					BluetoothSerial_byte_write('t');
					#endif
					break;	
				}
				default:
				{
					rx_event = RX_ERROR;			//генерируем событие - "ошибка приёма"
					#if (HARDWARE_MODE==1)
                    BluetoothSerial_byte_write('e');
					#endif
				}
			}
			

			receiver_on = false;//выключаем приемник
			if (ir_transmitter_on==false){ 
			timer_pause(TIM_GRUP_IR, TIM_NUM_IR); }//если передача не ведётся - выключаем прерывания
			
		}
		if((high_level_counter > IR_ZERO*8)&&(ir_transmitter_on==false))
		{
			receiver_on = false;//выключаем приемник
			timer_pause(TIM_GRUP_IR, TIM_NUM_IR);
		}
	
	}



if (ir_transmitter_on==true)
	{//Если передача разрешена

		if (ir_pulse_counter > 0)		//необходимая длительность пачки импульсов 
		{								//ещё не достигнута, "мигаем" дальше
			//IR_LED_INVERT;  			//необходимая длительность пачки 
 led_hit ^= 1;
    	switch(led_hit){
case 0:
//gpio_set_level(HIT_LED_OUT,0);
dac_output_voltage(IR_OUT ,0);
break;
case 1:
//gpio_set_level(HIT_LED_OUT,1);
dac_output_voltage(IR_OUT ,ir_power_value_dac);
break;
        }

			ir_pulse_counter--;
		}
		else							//пачка импульсов была отправлена, 
		{
            //gpio_set_level(HIT_LED_OUT,0);
            dac_output_voltage(IR_OUT ,0);
			//IR_LED_OFF;			//тушим ИК-диод 
			if ( ir_space_counter > 0)	//проверим, выдержан ли промежуток между импульсами
			{							//нет, промежуток не выдержан
			//gpio_set_level(HIT_LED_OUT,0);
            dac_output_voltage(IR_OUT ,0);
					//IR_LED_OFF;	//тушим ИК-диод
					ir_space_counter--;	//уменьшаем обратный счетчик паузы на один "тик"		
			}
			else //Пакет импульсов и промежуток между битами переданы
			{	 //нужно формировать следующую пачку (передаваемый бит)
				
				
				if (ir_tx_buffer_cursor.bits_for_tx>0) //если указатель указывает не на пустую ячейку
				{
					if(ir_tx_buffer_cursor.bit_mask == 0)//все биты текущего байта уже переданы
					{
						ir_tx_buffer_cursor.byte_pos++;//переходим к следующему байту
						ir_tx_buffer_cursor.bit_mask = (1<<7); //старший бит уходит первым
						
					}
					if (tx_buffer[ir_tx_buffer_cursor.byte_pos]&ir_tx_buffer_cursor.bit_mask)//если текущий бит равен "1"
					{
						ir_pulse_counter = IR_ONE;//отправим "1" (помигаем 1200 микросекунд)
					}
					else //текущий бит равен "0"
					{
						ir_pulse_counter = IR_ZERO;//отправим "0" (помигаем 600 микросекунд)
					}
					ir_space_counter = IR_SPACE;      //и про паузу не забудем					
					ir_tx_buffer_cursor.bit_mask = (ir_tx_buffer_cursor.bit_mask >> 1); //следующий бит
					ir_tx_buffer_cursor.bits_for_tx--; //уменьшаем количество оставшихся бит
//					ir_pulse_counter =data_packet.data[cursor_position++] ; //передадим импульс указанной длительностью

				}
				else //Все данные переданы (элемент, на который ссылается указатель, равен 0)
				{
					ir_transmitter_on=false; //выключаем передатчик
                   // timer_pause(TIM_GRUP_IR, TIM_NUM_IR);
					//FIRE_LED_OFF;
					display_bullets_update_now++;
				// если 	
					//if (!receiver_on) //если нет приема пакета
					//{
					//	TIMSK &=~_BV(OCIE2);          // Запрещаем прерывания по захвату/сравнению
						
				//	}				 
				}										
			}				 
		}
	}	

}

void IRAM_ATTR tsop_isr_handler(void* arg)
{
 timer_start(TIM_GRUP_IR, TIM_NUM_IR);         // Разрешаем прерывания по захвату/сравнению
receiver_on = true;
if(!(gpio_get_level(TSOP_IN )))		 //если прерывание вызвано спадом 
	{
	gpio_set_intr_type(TSOP_IN ,GPIO_INTR_ANYEDGE);

	if (start_bit_received)//Если старт-бит принят, то идет прием пакета
		{
		if((high_level_counter < (IR_SPACE + ERROR_TOLERANCE))&&(high_level_counter > (IR_SPACE - ERROR_TOLERANCE)))//Проверим длительность паузы между битами
		{
					//длительность паузы между импульсами корректна
		}
		else //Длительность паузы между приемом битов не корректна
		{//Фиксируем ошибку приёма
		start_bit_received	= false; 	//отменяем прием
		bit_in_rx_buff = 0;				//очищаем буфер
		rx_event = RX_ERROR;			//генерируем событие - "ошибка приёма"
		//#if (HARDWARE_MODE==1)
		//BluetoothSerial_byte_write('e');
		//#endif
//						TIMSK &= ~_BV(OCIE2);          // Запрещаем прерывания по захвату/сравнению
		}
		}		
		low_level_counter = 0;//Обнуляем счетчик длительности низкоуровнего сигнала на ножке ИК-приёмника
		high_level_counter = 0;//Обнуляем счетчик длительности высокоуровнего сигнала на ножке ИК-приёмника
	}
if(gpio_get_level(TSOP_IN ))	//прерывание вызвано фронтом 
	{
		gpio_set_intr_type(TSOP_IN ,GPIO_INTR_NEGEDGE);
		
		if (start_bit_received)//Если старт-бит принят, то идет прием пакета
			{
				if((low_level_counter < (IR_ZERO + ERROR_TOLERANCE))&&(low_level_counter > (IR_ZERO - ERROR_TOLERANCE)))//Проверим, соответствует ли длительность пакета нулевому биту
				{
					set_buffer_bit(bit_in_rx_buff++, false);//Длительность пачки соответствует биту со значением 0, заносим ноль в буфер приема
					#if (HARDWARE_MODE==1)
					BluetoothSerial_byte_write('0');
					#endif
				}
				else //Нет, это не бит со значением 0
				{
					if((low_level_counter < (IR_ONE + ERROR_TOLERANCE))&&(low_level_counter > (IR_ONE - ERROR_TOLERANCE)))//, может это бит со значением 1?
					{
							set_buffer_bit(bit_in_rx_buff++, true);//Длительность пачки соответствует биту со значением 1, заносим еденицу в буфер приема
							#if (HARDWARE_MODE==1)
							BluetoothSerial_byte_write('1');
							#endif		
					}
					else //Это ни единица, ни ноль - это помеха 
					{
						start_bit_received	= false; 	//отменяем прием
						bit_in_rx_buff = 0;				//очищаем буфер
						rx_event = RX_ERROR;			//генерируем событие - "ошибка приёма"
					//	#if (HARDWARE_MODE==1)
					//	BluetoothSerial_byte_write('e');
					//	#endif
//						TIMSK &= ~_BV(OCIE2);          // Запрещаем прерывания по захвату/сравнению
					}
				}
			}
		else //Старт-бит ещё не принят
		{
			if ((low_level_counter < (IR_START + ERROR_TOLERANCE))&&(low_level_counter > (IR_START - ERROR_TOLERANCE))) //Может это старт-бит?	
			{//Это старт-бит
				bit_in_rx_buff = 0;				//очищаем буфер
				start_bit_received	= true; 	//разрешаем прием пакетов (бит)
				#if (HARDWARE_MODE==1)
				BluetoothSerial_byte_write('h');
				#endif
			}
			else //это не старт-бит, это помеха 
			{
				//Игнорируем
			}
		}
		low_level_counter = 0;//Обнуляем счетчик длительности низкоуровнего сигнала на ножке ИК-приёмника
		high_level_counter = 0;//Обнуляем счетчик длительности высокоуровнего сигнала на ножке ИК-приёмника
	}
}

void ir_tx_cursor_home(void){//устанавливаем курсор в начало буфера
ir_tx_buffer_cursor.byte_pos = 0;
ir_tx_buffer_cursor.bit_mask = (1<<7);
ir_pulse_counter = IR_START; //передадим заголовоке
ir_space_counter = IR_SPACE;// и заголовок
}

void set_buffer_bit(uint8_t index, bool value)//Задаем значение биту в буфере ИК-приемника
{
uint8_t byte_index;
uint8_t bit_index;
byte_index = index/8; //Определяем, в каком байте нахадится нужный бит
bit_index = index - (byte_index*8);//Определяем номер бита в байте
if(value) 
		{
			rx_buffer[byte_index] |= (1<<(7-bit_index));
		}
else	{
			rx_buffer[byte_index] &= ~(1<<(7-bit_index));
		}
}

tgun_damage gun_damage()
{
return eeprom.damage;
}

tteam_color team_id() 
{
return eeprom.team_id;
}
 
tget_ir_currect_modet gun_power_ir() 
{
return eeprom.ir_power;
}

void set_player_id(uint8_t ID){
tx_buffer[0]= ID;
tx_buffer[0] &=~(1<<7);//седьмой бит в выстреле всегда равен "0"
}

void set_team_color(tteam_color color){
tx_buffer[1] &=~((1<<7)|(1<<6));//обнуляем два старших бита 
tx_buffer[1] |=(color <<6);//устанавливаем 6 и 7 биты в соответствии с цветом команды
}

void set_gun_damage(tgun_damage damage){
tx_buffer[1] &=~((1<<5)|(1<<4)|(1<<3)|(1<<2));//обнуляем биты урона 
tx_buffer[1] |=(damage << 2);
}

void set_gun_ir_power(tget_ir_currect_modet ir_power_value_set){
uint8_t ir_index=eeprom.ir_power;
ir_power_value_dac=(ir_power_value[ir_index]);
}

trx_packet get_packet_value() //считываем данные их полученного пакета
{ 
trx_packet result;
uint8_t byte_tmp;
result.player_id = rx_buffer[0];
byte_tmp = rx_buffer[1];
byte_tmp = byte_tmp << 2; //избавляемся от бит цвета команды
byte_tmp = byte_tmp >> 4;
result.damage = (damage_value[byte_tmp]);
result.team_id = rx_buffer[1]>>6;
return result;
}

tir_message get_ir_message_from_buffer(void) //извлекаем из буфера полученное сообщение 
{
	tir_message msg_tmp;
	msg_tmp.ID = rx_buffer[0];
	msg_tmp.param = rx_buffer[1];
	msg_tmp.control_byte = rx_buffer[2];
	return msg_tmp;
}

bool get_buffer_bit(uint8_t index){		//считываем значение бита
uint8_t byte_index;
uint8_t bit_index;
byte_index = index/8; 
bit_index = index - (byte_index*8);
if(rx_buffer[byte_index]&(1<<(7-bit_index))) return true;
else return false;
}

void send_ir_package(void){ //Отправляем пакет ("стреляем")
ir_error_ignore = DEFAULT_IR_ERROR_IGNORE;
set_cyclic_deley_counter();
ir_tx_cursor_home();//Курсор - на начало буфера
ir_tx_buffer_cursor.bits_for_tx=14;//"выстрел" состоит из 14 бит
ir_transmitter_on = true;	//Разрешаем передачу
timer_start(TIM_GRUP_IR, TIM_NUM_IR);
}

void init_var_rx_tx(void)
{

set_gun_ir_power(gun_power_ir());
 ir_transmitter_on=false; 	//Запретим пока передачу данных (поскольку данные ещё не сформированны)
set_player_id(eeprom.player_id);	//Устанавливаем идентификатор игрока
set_team_color(team_id());	
set_gun_damage(gun_damage());
start_bit_received = false;
bit_in_rx_buff = 0;
rx_event = NOT_EVENT;
receiver_on = false;
flag=false;
}

void set_cyclic_deley_counter() //настраиваем время задержки до следующего выстрела
{								// при автоматической стрельбк и время отсечки звука
cyclic_deley_counter =(600000/eeprom.cyclic_rate)/*10*/;
}

uint8_t get_light_color_hit(trx_packet hit_packet)
{
uint8_t color_tmp=255;
switch(hit_packet.team_id )
{
case 0:
color_tmp=0;
break;

case 1:
color_tmp=1;
break;

case 2:
color_tmp=2;
break;

case 3:
color_tmp=3;
break;

default:
break;
}
return color_tmp;
}

void bt_data(void)
{
 switch(parsing_bt_data())//проверим ПРИЕМНЫЙ буфер
		{
			case RX_COMPLETE: 	//получен пакет
			{
				if(!get_bt_buffer_bit(0)) //если этот бит равен 0, то это пакет с данными (выстрел)
				{
					bt_rx_packet = get_bt_packet_value();
					hit_processing(bt_rx_packet);
					USART_FlushRxBuf();
					bt_header_received=false;
				}

			}
			break;
			case RX_ERROR:		//ошибка приема
			{
				    if(!(ir_error_ignore))	
					{
                    //play_sound_from_flash(flying_bullet_sound);
					play_sound_from_flash_LW(Miss);
					keyboard_event=no_key_pressing; 
					}
			}
			break;
			case RX_MESSAGE_COMPLITE://принято сообщение
						{
							rx_event = NOT_EVENT;							
							if(get_bt_buffer_bit(0)) //если этот бит равен 1, то это пакет с командой
                        	{
                           		ir_message = get_ir_message_from_bt_buffer();//выдергиваем значения команды из буфера ИК приемника
                        
                           	 if (ir_message.control_byte ==Valid_value )//сообщение принято корректно (контрольный байт принят без ошибок)
							 {
								switch(ir_message.ID)//если имя команды
                           		{
                              		case Add_Health: //добавить "жизни"
                              		{
										//код для добавления жизни
                                 		break;
                              		}
                              		case Add_Rounds://добавить "патронов"
                              		{
                                 
								 		//код для добавления патронов
                                 		break;
                              		}
									case Change_color:
									set_color_team_now();
									break;

                                    case Set_damage://установить хх урон
									set_damage_now();
                                    break;

								    case Set_damage_tmp://установить хх урон временный  
									set_damage_temp();
                                    break;

                              		case Command://какая то дополнительноя команда
                              		{
                                    	
										switch(ir_message.param)//выясним, какая это командв
										{
												//case 0x05://начать новую игру немедленно
											case New_Game_Now:
                                    if(reload_state!=nothing_to_do) 
									break;
                                    new_game();  
                                    break;
											

//case 0x0d://полный боезапас
case Rec_Ammo :											
recovery_clips();
break;
/*case Set_OK:
if(jdy_cs_tmp== 2){
USART_SendStr("h1000 0011 1111 1000 1110 1000t");
}
set_ok_detect=false;
break;*/											
//case 0xFE://режим настроек
case Setting_Mode:
invite();
break;

case Tager_off:
                                           BluetoothSerial_str_write("Restarting\n",11);
                                           printf("Restarting now.\n");
                                           vTaskDelay(500 / portTICK_PERIOD_MS);
                                           fflush(stdout);
										   gpio_set_level(OFF_ON_OUT,0);
                                           esp_restart();
                                        break;
//case 0xFC://slave chit_detect true 
/*case Chitfetect_Jdy_True:
chit_detect_slave=true;
break;*/
//case 0xFD://slave chit_detect false
/*case Chitfetect_Jdy_False:
chit_detect_slave=false;
break;*/

									//	case 0x06://востановить здоровье до 100% (аптечка)
                                     case Rec_Life:		
                                     recovery_life();
	                                 break;
													
											//	case 0x00://"выключить" игрока 
									 case Admin_Kill:
								     game_over();
									 break;

											default: 
											break;
										
										}
										
									
										break;
                              		}
                           		}
                        	 }

                        	}
							else//контрольный байт сообщения не корректный - ошибка приема
							{
							}
							rx_event = NOT_EVENT;
							break;

						}
			break;
			case NOT_EVENT:		//нет ничего интересного ;-)
			{
			}
			break;
		}


}

trx_event parsing_bt_data(void) //анализируем пакет, полученный по блютус, извекаем из него данные
{
	volatile uint8_t tmp_char;
	trx_event result;

	result = NOT_EVENT;
	if(cr_received)
	{

	while (rxCount)//пока не считаем все символы из буфера
	{
		tmp_char = blue_GetChar();
		switch(tmp_char)
		{
			case 'h'://нашли заголовок пакета 104 'h'
			
				bt_header_received = true; //фиксируем получение заголовка
				bit_in_bt_rx_buff=0;//ставим курсор в начало буфера пакета
			
			break;
			case '0'://получен бит "0"
			
				if(bt_header_received){ 
				set_bt_buffer_bit(bit_in_bt_rx_buff++, false);//если заголовок получен, заносим значение бита в буфер пакета
				}
			break;
			case '1'://получен бит "1"
			
				if(bt_header_received) 
				{
					set_bt_buffer_bit(bit_in_bt_rx_buff++, true);//если заголовок получен, заносим значение бита в буфер пакета
				}
			break;
			case 'e'://пакет битый 101 'e'
			
				bt_header_received = false;//нужно искать следующий заголовок
				return RX_ERROR;//выходим с ошибкой
			
			break;
			case 't'://таймаут приема бита 116 't'
			
				
				if((bt_header_received)&&(bit_in_bt_rx_buff>0))//если заголовок получен и буфер пакета не пустой
				{				
						
						
						
					switch(bit_in_bt_rx_buff)//проверим, сколько бит принято
					{
                       case 24:
						
							result	= RX_MESSAGE_COMPLITE;//принято сообщение;
							cr_received=false;
							break;


						case 14:
						
							result = RX_COMPLETE;			//Генерим событие "принят пакет"
							cr_received=false;
							break;	
						
							
						
						default:
						{
							result = RX_ERROR;			//генерируем событие - "ошибка приёма"
							cr_received=false;
						}
					}						

						bt_header_received = false;//заголовок обработали
						return result;
				//		return RX_COMPLETE;//выходим с сообщением о получении пакета
				}
				else 	
				{
					bt_header_received = false;//заголовок обработали
				}
			
			break;

		}

    
	}
	}//while (rxCount)

//всё считали, собйтий нет
return result;

}

bool get_bt_buffer_bit(uint8_t index){		//Считываем значение бита в буфере ИК-приемника
uint8_t byte_index;
uint8_t bit_index;
byte_index = index/8; //Определяем, в каком байте нахадится нужный бит
bit_index = index - (byte_index*8);//Определяем номер бита в байте
if(bt_rx_buffer[byte_index]&(1<<(7-bit_index))) return true;
else return false;
}

trx_packet get_bt_packet_value(){ //Считываем данные из полученного пакета
trx_packet result;
uint8_t byte_tmp;

result.player_id = bt_rx_buffer[0];
byte_tmp = bt_rx_buffer[1];
byte_tmp = byte_tmp << 2; //избавляемся от бит цвета команды
byte_tmp = byte_tmp >> 4;
result.damage = damage_value[byte_tmp];
result.team_id = bt_rx_buffer[1]>>6;

return result;
}

void USART_FlushRxBuf(void)
{

  rxBufTail = 0;
  rxBufHead = 0;
  rxCount = 0;

}

tir_message get_ir_message_from_bt_buffer(void) 
{
	tir_message msg_tmp;
	msg_tmp.ID = bt_rx_buffer[0];
	msg_tmp.param = bt_rx_buffer[1];
	msg_tmp.control_byte = bt_rx_buffer[2];
	return msg_tmp;

}

void set_bt_buffer_bit(uint8_t index, bool value)
{	
uint8_t byte_index;
uint8_t bit_index;
byte_index = index/8; 
bit_index = index - (byte_index*8);
if(value) 
		{
			bt_rx_buffer[byte_index] |= (1<<(7-bit_index));
		}
else	{
			bt_rx_buffer[byte_index] &= ~(1<<(7-bit_index));
		}
}

void parsing_command(void)
{

uint8_t cmd_index;
					
					cmd_index = get_command_index();
					switch(cmd_index)
					{
						case 0: command_0_slot();
						break;
						case 1: command_1_slot();
						break;
						case 2: command_2_slot();
						break;
						case 3: command_3_slot();
						break;
						case 4: command_4_slot();
						break;
						case 5: command_5_slot();
						break;
						case 6: command_6_slot();
						break;
						case 7: command_7_slot();
						break;
						case 8: command_8_slot();
						break;
						case 9: command_9_slot();
						break;
						case 10: command_10_slot();
						break;
						case 11: command_11_slot();
						break;
						case 12: command_12_slot();
						break;
						case 13: command_13_slot();
						break;
						case 14: command_14_slot();
						break;
						case 15: command_15_slot();
						break;
						case 16: command_16_slot();
						break;
						case 17: command_17_slot();
						break;
						case 18: command_18_slot();
						break;
						case 19: command_19_slot();
						break;
						case 20: command_20_slot();
						break;
						case 21: command_21_slot();
						break;
						case 22: command_22_slot();
						break;
						case 23: command_23_slot();
						break;
						case 24: command_24_slot();
						break;
						case 25: command_25_slot();
						break;
						case 26: command_26_slot();
						break;
						case 27: command_27_slot();
						break;
						case 28: command_28_slot();
						break;
						case 29: command_29_slot();
						break;
						case 30: command_30_slot();
						break;
						case 31: command_31_slot();
						break;		
						case 32: command_32_slot();
						break;		
						case 33: command_33_slot();
						break;
						case 34: command_34_slot();
						break;
						case 35: command_35_slot();
						break;
						case 36: command_36_slot();
						break;
						case 37: command_37_slot();
						break;
						case 38: command_38_slot();
						break;
						case 39: command_39_slot();
						break;
						case 40: command_40_slot();
						break;
						case 41: command_41_slot();
						break;
						case 42: command_42_slot();
						break;
						case 43: command_43_slot();
						break;
						case 44: command_44_slot();
						break;	
						case 45: command_45_slot();
						break;
						case 46: command_46_slot();
						break;	
						case 47: command_47_slot();
						break;
						case 48: command_48_slot();
						break;
						case 49: command_49_slot();
						break;
						case 50: command_50_slot();
						break;
						case 51: command_51_slot();
						break;
						case 52: command_52_slot();
						break;
						case 53: command_53_slot();
						break;
						case 54: command_54_slot();
						break;
						case 55: command_55_slot();
						break;
						case 56: command_56_slot();
						break;
						case 57: command_57_slot();
						break;
						case 58: command_58_slot();
						break;
						case 59: command_59_slot();
						break;
						case 60: command_60_slot();
						break;
						case 61: command_61_slot();
						break;
						case 62: command_62_slot();
						break;
						case 63: command_63_slot();
						break;
						case 64: command_64_slot();
						break;
						case 65: command_65_slot();
						break;
						case 66: command_66_slot();
						break;
						case 67: command_67_slot();
						break;
						case 68: command_68_slot();
						break;
						case 69: command_69_slot();
						break;
						case 70: command_70_slot();
						break;
						case 71: command_71_slot();
						break;
						case 72: command_72_slot();
						break;
						case 73: command_73_slot();
						break;
						case 74: command_74_slot();
						break;
						case 75: command_75_slot();
						break;
						case 76: command_76_slot();
						break;
                        case 77: command_77_slot();
						break;
                        case 78: command_78_slot();
						break;
                        case 79: command_79_slot();
						break;
                        case 80: command_80_slot();
					    break;
	                    case 81: command_81_slot();
						break;
						case 82: command_82_slot();
						break;
						case 83: command_83_slot();
						break;
						case 84: command_84_slot();
						break;
						case 85: command_85_slot();
						break;
						case 86: command_86_slot();
						break;
						case 87: command_87_slot();
						break;
						case 88: command_88_slot();
						break;
                        case 89: command_89_slot();
						break;
                        /*case 90: command_90_slot();
						break;
                        case 91: command_91_slot();
						break;
                        case 92: command_92_slot();
						break;
                        case 93: command_93_slot();
						break;
                        case 94: command_94_slot();
						break;
                        case 95: command_95_slot();
						break;
                        case 96: command_96_slot();
						break;
                        case 97: command_97_slot();
						break;
                        case 98: command_98_slot();
						break;
                        case 99: command_99_slot();
						break;*/
                        //case 100: command_100_slot();
						//break;
						default:
						{
						BluetoothSerial_write(unknown_command_error,(sizeof(unknown_command_error)-1));	
						
						}

					}
				
					cr_received = false;
					USART_FlushRxBuf();

}

uint8_t get_command_index(void)//проверим, что за команда пришла по UART
{

volatile uint16_t delta;
volatile char* cursor_pos;
volatile char* buff_pos;

volatile char cmd_buff[32];
uint8_t comand_len;

	for (int index=0; index <(sizeof(commandsPointers)/sizeof(char*)); index++)
	{
		
		unsigned char sym;
		uint8_t sym_index = 0;
		char* psym; //указатель на первый символ команды в памяти программ
		psym = (char*)commandsPointers[index];
		comand_len = 0;
		while((pgm_read_byte(psym)!=0))
		{
			sym = pgm_read_byte(psym);
			cmd_buff[sym_index++] = sym; //копируем команду в буфер
			comand_len++;
			psym++;
		}
		
		cursor_pos = memmem((uint8_t *)&(usartRxBuf[rxBufHead]),rxCount,(char*)cmd_buff,comand_len);
		buff_pos = (char*)&usartRxBuf[0];
		if (memmem((uint8_t *)&(usartRxBuf[rxBufHead]),rxCount,(char*)cmd_buff,comand_len)!=NULL) 
		{
			delta = (uint16_t*)(cursor_pos) - (uint16_t*)(buff_pos);
			
			rxBufHead = rxBufHead+comand_len+(unsigned char)(delta);
			rxCount = rxCount-comand_len-(unsigned char)(delta);
			return index;	
		}
	
	}

	return 255; //не найдена такая команда в списке команд

}

void finde_message_in_bt_buffer(void)//ищем сообщение в приемном буфере блютус
{
		
		switch(parsing_bt_data())//проверим роиемный буфер
		{
			case RX_COMPLETE: 	//получен пакет
			{
			}
			break;
			case RX_ERROR:		//ошибка приема
			{
			}
			
			case RX_MESSAGE_COMPLITE://принято сообщение
			{
					//		rx_event = NOT_EVENT;							
							if(get_bt_buffer_bit(0)) //если этот бит равен 1, то это пакет с командой
                        	{
                           		ir_message = get_ir_message_from_bt_buffer();//выдергиваем значения команды из буфера ИК приемника	
								rx_event = NOT_EVENT;
								break;

							}
						
			}
			
			
			
			break;
			case NOT_EVENT:		//нет ничего интересного ;-)
			{
			}
			break;
		}
}

void get_int_argument_value(uint8_t var_adress,const char* key, uint8_t min_val, uint8_t max_val)//запись параметра uint8 через уарт
{

bool param_not_empty = false;
volatile char ch_tmp;
volatile uint8_t result = 0;

while(usartRxBuf[rxBufHead] !='\r')

	{

		ch_tmp = usartRxBuf[rxBufHead++];
		if (ch_tmp==' ') continue; //игнорируем пробелы
		if ((ch_tmp >= '0')&&(ch_tmp<= '9'))
		{
			result = result*10+char_to_int(ch_tmp);
			param_not_empty = true;
		}		
		else 
		{
			BluetoothSerial_write(parameter_invalid_error,(sizeof(parameter_invalid_error)-1));
			return;
			


		}
	}
if (!param_not_empty) 
	{
		BluetoothSerial_write(parameter_empty_error,(sizeof(parameter_empty_error)-1));
		return;//пустой аргумент
	}

if ((result>max_val)||(result<min_val))
	{
		BluetoothSerial_write(parameter_out_of_range_error,(sizeof(parameter_out_of_range_error)-1));
		return;//аргумент больше максимально допустимого значения
	} 
nvs_flash_init ();
nvs_handle_t eeprom_nvs_handle;
nvs_open(NAME_NVS, NVS_READWRITE, &eeprom_nvs_handle);
var_adress=result;
nvs_set_u8(eeprom_nvs_handle, key, var_adress);
nvs_commit(eeprom_nvs_handle);
nvs_close(eeprom_nvs_handle);
nvs_flash_deinit();
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));

}

void get_u32_argument_value(uint32_t var_adress,const char* key, uint32_t min_val, uint32_t max_val)//запись параметра uint32 через уарт
{

bool param_not_empty = false;
volatile char ch_tmp;
volatile uint32_t result = 0;

while(usartRxBuf[rxBufHead] !='\r')

	{

		ch_tmp = usartRxBuf[rxBufHead++];
		if (ch_tmp==' ') continue; //игнорируем пробелы
		if ((ch_tmp >= '0')&&(ch_tmp<= '9'))
		{
			result = result*10+char_to_int(ch_tmp);
			param_not_empty = true;
		}		
		else 
		{
			BluetoothSerial_write(parameter_invalid_error,(sizeof(parameter_invalid_error)-1));
			return;
			

		}
	}
if (!param_not_empty) 
	{
		BluetoothSerial_write(parameter_empty_error,(sizeof(parameter_empty_error)-1));
		return;//пустой аргумент
	}

if ((result>max_val)||(result<min_val))
	{
		BluetoothSerial_write(parameter_out_of_range_error,(sizeof(parameter_out_of_range_error)-1));
		return;//аргумент больше максимально допустимого значения
	} 
nvs_flash_init ();
nvs_handle_t eeprom_nvs_handle;
nvs_open(setting_name, NVS_READWRITE, &eeprom_nvs_handle);
var_adress=result;
nvs_set_u32(eeprom_nvs_handle, key, var_adress);
nvs_commit(eeprom_nvs_handle);
nvs_close(eeprom_nvs_handle);
nvs_flash_deinit();

BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));
}

void get_word_argument_value(uint16_t var_adress,const char* key, uint16_t min_val, uint16_t max_val)//запись параметра uint16 через уарт
{

bool param_not_empty = false;
volatile char ch_tmp;
volatile uint16_t result = 0;

while(usartRxBuf[rxBufHead] !='\r')

	{

		ch_tmp = usartRxBuf[rxBufHead++];
		if (ch_tmp==' ') continue; //игнорируем пробелы
		if ((ch_tmp >= '0')&&(ch_tmp<= '9'))
		{
			result = result*10+char_to_int(ch_tmp);
			param_not_empty = true;
		}		
		else 
		{
			BluetoothSerial_write(parameter_invalid_error,(sizeof(parameter_invalid_error)-1));
			return;
		}
	}
if (!param_not_empty) 
	{
		BluetoothSerial_write(parameter_empty_error,(sizeof(parameter_empty_error)-1));
		return;//пустой аргумент
	}

if ((result>max_val)||(result<min_val))
	{
		BluetoothSerial_write(parameter_out_of_range_error,(sizeof(parameter_out_of_range_error)-1));
		return;//аргумент больше максимально допустимого значения
	} 
nvs_flash_init ();
nvs_handle_t eeprom_nvs_handle;
nvs_open(NAME_NVS, NVS_READWRITE, &eeprom_nvs_handle);
var_adress=result;
nvs_set_u16(eeprom_nvs_handle, key, var_adress);
nvs_commit(eeprom_nvs_handle);
nvs_close(eeprom_nvs_handle);
nvs_flash_deinit();
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));

}

void get_str_argument(char *var_adress,const char* key, uint8_t length)//запись параметра str через уарт
{

char ch_tmp;
int count=0;
char result[length];
while(usartRxBuf[rxBufHead] !='\r')
//for(usartRxBuf[rxBufHead] !='\r')

	{

		ch_tmp = usartRxBuf[rxBufHead++];
		//if (ch_tmp==' ') continue; //игнорируем пробелы		
		if((ch_tmp==' ')||(ch_tmp==0x00)||(ch_tmp=='\r'))
		{
		BluetoothSerial_write(parameter_empty_error,(sizeof(parameter_empty_error)-1));
		return;//пустой аргумент
		}	
			if(count<length)
		{	
         result[count]=ch_tmp;
		 //printf("%d\n",count);
		 count++;
		 
		}
		else
		{
         BluetoothSerial_write(parameter_invalid_error,(sizeof(parameter_invalid_error)-1));
		 return;
		}				
}

		if(!(count==(length-1)))
{
 //printf("count range :%d\n",count);	
BluetoothSerial_write(parameter_out_of_range_error,(sizeof(parameter_out_of_range_error)-1));
//return;//аргумент больше максимально допустимого значения
}


if(count==(length-1))	
{
 //printf("count write:%d\n",count);		 
 //printf("result :%s\n",result);
 //BluetoothSerial_str_write(result,count);	
nvs_flash_init ();
nvs_handle_t eeprom_nvs_handle;
nvs_open(NAME_NVS, NVS_READWRITE, &eeprom_nvs_handle);
//printf("result :%s\n",result);
//strcpy(var_adress, result);	
snprintf(var_adress,length,"%s",result);
//sprintf(var_adress,"%s",result);
nvs_set_str(eeprom_nvs_handle, key, var_adress);
nvs_commit(eeprom_nvs_handle);
nvs_close(eeprom_nvs_handle);
nvs_flash_deinit();	
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));
}	
}

uint32_t parsing_uint32_argument_value(void)//запись uint32_t
{
bool param_not_empty = false;
unsigned char  ch_tmp;
int count=0;
char  result[32];
bool end_while=true;
uint32_t value;
uint32_t error =0xffffffff;
if(rxCount<=32)
{
while(end_while) 
 
{

		ch_tmp = usartRxBuf[rxBufHead++];
		if ((ch_tmp=='\r')||(ch_tmp=='\n'))
		{
		end_while=false;	
		}        	
		if  ( (!((ch_tmp >= '0')&&(ch_tmp<= '9')))||(ch_tmp==' ') ) continue; //игнорируем пробелы и другие символы кроме цифр
		if ((ch_tmp >= '0')&&(ch_tmp<= '9'))
		{

			result[count] =ch_tmp ;
			param_not_empty = true;
			count++;
		}
		else
		{	
		
			BluetoothSerial_write(parameter_invalid_error,(sizeof(parameter_invalid_error)-1));
			
			return error;						

		}
	}
if (!param_not_empty) 
	{
					
		BluetoothSerial_write( parameter_empty_error,(sizeof( parameter_empty_error)-1));
			
		return error;//пустой аргумент
	}
}
else
{				
BluetoothSerial_write(parameter_out_of_range_error,(sizeof(parameter_out_of_range_error)-1));		
return error;
}
value=atoi(result);
//printf("value : %d  \n",value);
USART_FlushRxBuf();
return value;
}


void command_0_slot(void)//bullets_in_clip=
{
get_word_argument_value(eeprom.bullets_in_clip,bullets_clip_name, 0, 999);	
}
void command_1_slot(void)//bullets_in_clip?
{
eeprom_read_val(4);
BluetoothSerial_write_u16(eeprom.bullets_in_clip);
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));
}
void command_2_slot(void)//protocol?
{
BluetoothSerial_write(protocol,sizeof(protocol));
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));	

}
void command_3_slot(void)//clips=
{
get_word_argument_value(eeprom.clips,clips_name, 0, 999);

}
void command_4_slot(void)//clips?
{
eeprom_read_val(5);	
BluetoothSerial_write_u16(eeprom.clips);
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));	

}
void command_5_slot(void)//time_off=
{ 
get_int_argument_value(eeprom_time_off,time_off_name, 0, 255);
}
void command_6_slot(void)//time_off?
{
eeprom_read_val(11);		
BluetoothSerial_write_u8(eeprom_time_off);
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));
}
void command_7_slot(void)//com
{
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));
}
void command_8_slot(void)//com
{
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));
}
void command_9_slot(void)//com
{
}
void command_10_slot(void)//com
{
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));
}
void command_11_slot(void)//com
{
	
}
void command_12_slot(void)
{}
void command_13_slot(void)
{}
void command_14_slot(void)//play_sound
{
play_sound_num(parsing_uint32_argument_value());
}
void command_15_slot(void)//statistic
{
if(death_col==0){
		uint8_t	cl;
		uint8_t cl_in;
           	switch(statistic_tmp){
		case 0:
		break;
        case 1:
        
            death_col++;
			cl=eeprom.clips;
		    cl_in=eeprom.bullets_in_clip;
            shoots_tmp_col =((cl-clips)*cl_in)-bullets;
            death_shoots();
			 
		break;
        case 2:
         death_col++;
		cl=eeprom.clips;
		cl_in=eeprom.bullets_in_clip;
            shoots_tmp_col =((cl-clips)*cl_in)-bullets;
            death_shoots();
		break;
        
		}
}
//pl1
print_statistic_page(parsing_uint32_argument_value());
statistic_upload_f=true;

}
void command_16_slot(void)
{}
void command_17_slot(void)
{}
void command_18_slot(void)
{}
void command_19_slot(void)
{}
void command_20_slot(void)
{}
void command_21_slot(void)
{}
void command_22_slot(void)
{}
void command_23_slot(void)
{}
void command_24_slot(void)
{}
void command_25_slot(void)
{}
void command_26_slot(void)
{}
void command_27_slot(void)
{}
void command_28_slot(void)
{}
void command_29_slot(void)
{}
void command_30_slot(void)
{}
void command_31_slot(void)
{}
void command_32_slot(void)
{}
void command_33_slot(void)//player_id=
{
get_int_argument_value(eeprom.player_id,team_id_name, 0, 127);
}
void command_34_slot(void)//player_id?
{
eeprom_read_val(0);		
BluetoothSerial_write_u8(eeprom.player_id);
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));		
}
void command_35_slot(void)//damage=
{
get_int_argument_value(eeprom.damage,damage_name, 0, 15);
}
void command_36_slot(void)//damage?
{
eeprom_read_val(2);		
BluetoothSerial_write_u8(eeprom.damage);
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));		
}
void command_37_slot(void)//ir_power=
{
get_int_argument_value(eeprom.ir_power,ir_power_name, 0, 7);
}
void command_38_slot(void)//ir_power?
{
eeprom_read_val(3);		
BluetoothSerial_write_u8(eeprom.ir_power);
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));		
}
void command_39_slot(void)//friendly_fire=
{
get_int_argument_value(eeprom.friendly_fire_enable,friendly_fire_name, 0, 1);
}
void command_40_slot(void)//friendly_fire?
{
eeprom_read_val(12);	
BluetoothSerial_write_u8(eeprom.friendly_fire_enable);
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));		

}
void command_41_slot(void)//team_id=
{
get_int_argument_value(eeprom.team_id,team_id_name, 0, 3);
}
void command_42_slot(void)//team_id?
{
eeprom_read_val(1);	
BluetoothSerial_write_u8(eeprom.team_id);
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));		

}
void command_43_slot(void)//batt_full_voltage=
{
get_word_argument_value(eeprom.batt_full_voltage,batt_full_name, 3000, 45000);
}
void command_44_slot(void)//batt_full_voltage?
{
eeprom_read_val(13);	
BluetoothSerial_write_u16(eeprom.batt_full_voltage);
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));		

}
void command_45_slot(void)//batt_low_voltage=
{
get_word_argument_value(eeprom.batt_low_voltage,batt_low_name, 2100, 45000);
}
void command_46_slot(void)//batt_low_voltage?
{
eeprom_read_val(14);	
BluetoothSerial_write_u16(eeprom.batt_low_voltage);
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));	
}
void command_47_slot(void)
{}
void command_48_slot(void)
{}
void command_49_slot(void)
{}
void command_50_slot(void)
{}
void command_51_slot(void)
{}
void command_52_slot(void)
{}
void command_53_slot(void)
{}
void command_54_slot(void)
{}
void command_55_slot(void)
{}
void command_56_slot(void)
{}
void command_57_slot(void)
{}
void command_58_slot(void)
{}
void command_59_slot(void)
{}
void command_60_slot(void)
{}
void command_61_slot(void)
{}
void command_62_slot(void)
{}
void command_63_slot(void)
{}
void command_64_slot(void)
{}
void command_65_slot(void)
{}
void command_66_slot(void)//reload_time=
{
get_int_argument_value(eeprom.reload_duration,reload_time_name, 0, 99);
}
void command_67_slot(void)//reload_time?
{
eeprom_read_val(6);	
BluetoothSerial_write_u8(eeprom.reload_duration);
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));	
}
void command_68_slot(void)//life_after_start=
{
get_word_argument_value(eeprom.life_after_start,life_start_name, 0, 999);
}
void command_69_slot(void)//life_after_start?
{
eeprom_read_val(9);	
BluetoothSerial_write_u16(eeprom.life_after_start);
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));	
}
void command_70_slot(void)//cyclic_rate=
{
get_word_argument_value(eeprom.cyclic_rate,cyclic_rate_name, 30, 800);
}
void command_71_slot(void)//cyclic_rate?
{
eeprom_read_val(10);	
BluetoothSerial_write_u16(eeprom.cyclic_rate);
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));
}
void command_72_slot(void)//safe_duration=
{
get_word_argument_value(eeprom.safe_duration,safe_duration_name, 0, 30000);
}
void command_73_slot(void)//safe_duration?
{
eeprom_read_val(7);	
BluetoothSerial_write_u16(eeprom.safe_duration);
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));	
}
void command_74_slot(void)//shock_time?
{
eeprom_read_val(8);	
BluetoothSerial_write_u16(eeprom.shock_time);
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));
}
void command_75_slot(void)//shock_time=
{
get_word_argument_value(eeprom.shock_time,shock_time_name, 0, 30000);
}
void command_76_slot(void)
{}
void command_77_slot(void)
{}
void command_78_slot(void)//restart
{
 
 BluetoothSerial_str_write("Restarting\n",11);
 printf("Restarting now.\n");
 vTaskDelay(500 / portTICK_PERIOD_MS);
    fflush(stdout);
	gpio_set_level(OFF_ON_OUT,0);
    esp_restart();	

}
void command_79_slot(void)
{}
void command_80_slot(void)
{}
void command_81_slot(void)
{

}
void command_82_slot(void)//tag_name?
{
get_eeprom_bt_name(0,eeprom_devise_name);
size_t sz=strlen(eeprom_devise_name);
BluetoothSerial_str_write(eeprom_devise_name,sz);
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));
}
void command_83_slot(void)////tag_name=
{
size_t required_size =NAME_LEN;
char ch_tmp;
int pos=0;
char * name_tmp1 = (char*) calloc(required_size, sizeof(char));
while(usartRxBuf[rxBufHead] !='\r')
{	
ch_tmp = usartRxBuf[rxBufHead++]; 
if(ch_tmp==' ')
{	 
continue;
}
name_tmp1[pos]=ch_tmp;
pos++;
//printf("name_tmp1 : %s\n",name_tmp1);
}
switch (check_name(name_tmp1,NAME_LEN))
{
case 0:
set_eeprom_bt_name(0,name_tmp1);
USART_FlushRxBuf();	
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));	
break;
case 1:
USART_FlushRxBuf();	
BluetoothSerial_write(parameter_empty_error,(sizeof(parameter_empty_error)-1));	
break;
case 2:
USART_FlushRxBuf();	
BluetoothSerial_write(parameter_invalid_error,(sizeof(parameter_invalid_error)-1));
break;
case 3:
USART_FlushRxBuf();	
BluetoothSerial_write(parameter_out_of_range_error,(sizeof(parameter_out_of_range_error)-1));
BluetoothSerial_write(cr_lf,(sizeof(cr_lf)-1));
BluetoothSerial_str_write("name length=",12);
BluetoothSerial_write_u16(NAME_LEN-1);
BluetoothSerial_write(cr_lf,(sizeof(cr_lf)-1));
break;
default:
break;
}

free(name_tmp1);
}
void command_84_slot(void)//handband_name?
{
get_eeprom_bt_name(1,eeprom_con_name);
size_t sz=strlen(eeprom_con_name);
BluetoothSerial_str_write(eeprom_con_name,sz);
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));
}
void command_85_slot(void)//handband_name=
{
size_t required_size =NAME_LEN;
char ch_tmp;
int pos=0;
char * name_tmp1 = (char*) calloc(required_size, sizeof(char));
while(usartRxBuf[rxBufHead] !='\r')
{	
ch_tmp = usartRxBuf[rxBufHead++]; 
if(ch_tmp==' ')
{	 
continue;
}
name_tmp1[pos]=ch_tmp;
pos++;
//printf("name_tmp1 : %s\n",name_tmp1);
}
switch (check_name(name_tmp1,NAME_LEN))
{
case 0:
set_eeprom_bt_name(1,name_tmp1);
USART_FlushRxBuf();	
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));	
break;
case 1:
USART_FlushRxBuf();	
BluetoothSerial_write(parameter_empty_error,(sizeof(parameter_empty_error)-1));	
break;
case 2:
USART_FlushRxBuf();	
BluetoothSerial_write(parameter_invalid_error,(sizeof(parameter_invalid_error)-1));
break;
case 3:
USART_FlushRxBuf();	
BluetoothSerial_write(parameter_out_of_range_error,(sizeof(parameter_out_of_range_error)-1));
BluetoothSerial_write(cr_lf,(sizeof(cr_lf)-1));
BluetoothSerial_str_write("name length=",12);
BluetoothSerial_write_u16(NAME_LEN-1);
BluetoothSerial_write(cr_lf,(sizeof(cr_lf)-1));
break;
default:
break;
}

free(name_tmp1);
}
void command_86_slot(void)//handband_adr?
{
nvs_flash_init ();
nvs_handle_t eeprom_nvs_handle;
size_t required_size=sizeof(eeprom_con_adr);
nvs_open(NAME_NVS, NVS_READONLY, &eeprom_nvs_handle);	
nvs_get_str(eeprom_nvs_handle, bt_connect_adr_name, eeprom_con_adr,&required_size);
nvs_close(eeprom_nvs_handle);
nvs_flash_deinit();
BluetoothSerial_str_write(eeprom_con_adr,(sizeof(eeprom_con_adr)-1));
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));
//printf("eeprom_con_adr :%s\n",eeprom_con_adr);
}
void command_87_slot(void)//handband_adr=
{
get_str_argument(eeprom_con_adr,bt_connect_adr_name,ADR_LEN);
}
void command_88_slot(void)//pin_set?
{
get_eeprom_bt_name(2,eeprom_bt_pin);
size_t sz=strlen(eeprom_bt_pin);
BluetoothSerial_str_write(eeprom_bt_pin,sz);
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));
}
void command_89_slot(void)//pin_set=
{
size_t required_size =PIN_LEN ;
char ch_tmp;
int pos=0;
char * name_tmp1 = (char*) calloc(required_size, sizeof(char));
while(usartRxBuf[rxBufHead] !='\r')
{	
ch_tmp = usartRxBuf[rxBufHead++]; 
if(ch_tmp==' ')
{	 
continue;
}
name_tmp1[pos]=ch_tmp;
pos++;
//printf("name_tmp1 : %s\n",name_tmp1);
}
switch (check_name(name_tmp1,PIN_LEN))
{
case 0:
set_eeprom_bt_name(2,name_tmp1);
USART_FlushRxBuf();	
BluetoothSerial_write(ok_string,(sizeof(ok_string)-1));	
break;
case 1:
USART_FlushRxBuf();	
BluetoothSerial_write(parameter_empty_error,(sizeof(parameter_empty_error)-1));	
break;
case 2:
USART_FlushRxBuf();	
BluetoothSerial_write(parameter_invalid_error,(sizeof(parameter_invalid_error)-1));
break;
case 3:
USART_FlushRxBuf();	
BluetoothSerial_write(parameter_out_of_range_error,(sizeof(parameter_out_of_range_error)-1));
BluetoothSerial_write(cr_lf,(sizeof(cr_lf)-1));
BluetoothSerial_str_write("pin length=",11);
BluetoothSerial_write_u8(PIN_LEN-1);
BluetoothSerial_write(cr_lf,(sizeof(cr_lf)-1));
break;
default:
break;
}

free(name_tmp1);
}

void statistic_count(trx_packet hit_packet)
{
uint8_t pl_id;
if(hit_packet.player_id!=0)
{
pl_id=hit_packet.player_id-1;
My_st_col[pl_id].sh_team = hit_packet.team_id;
My_st_col[pl_id].damage_tager = hit_packet.damage;
if(life_in_percent > hit_packet.damage){
	
My_st_col[pl_id].damage_rec += hit_packet.damage;
}
else{
if(life_in_percent<=hit_packet.damage){
My_st_col[pl_id].damage_rec +=life_in_percent;
}
My_st_col[pl_id].fatal_shoot++;
}
}	
}

void death_shoots(void) 
{
uint8_t pl_id=0;
uint8_t damg = eeprom.damage;
	if(eeprom.player_id!=0)
{	
pl_id=eeprom.player_id-1;
}	
							
My_st_col[pl_id].sh_team = eeprom.team_id;
My_st_col[pl_id].death=death_col;
My_st_col[pl_id].shoots_tmp+=shoots_tmp_col;
My_st_col[pl_id].damage_tager=damage_value[damg];
}

void print_statistic_page(uint32_t page)
{	
if(page>0)
{	
uint32_t page_cnt=page-1;
if(My_st_col[page_cnt].damage_tager==0)
{
//printf("data NULL\n");
}
else{
BluetoothSerial_write_u32(page);
BluetoothSerial_write_u8(My_st_col[page_cnt].sh_team);
BluetoothSerial_write(comma,(sizeof(comma)-1));
BluetoothSerial_write_u16(My_st_col[page_cnt].damage_rec);
BluetoothSerial_write(comma,(sizeof(comma)-1));
BluetoothSerial_write_u8(My_st_col[page_cnt].fatal_shoot);
BluetoothSerial_write(comma,(sizeof(comma)-1));
BluetoothSerial_write_u8(My_st_col[page_cnt].death);
BluetoothSerial_write(comma,(sizeof(comma)-1));
BluetoothSerial_write_u16(My_st_col[page_cnt].shoots_tmp);
BluetoothSerial_write(comma,(sizeof(comma)-1));
BluetoothSerial_write_u8(My_st_col[page_cnt].damage_tager);
BluetoothSerial_write(cr_lf,(sizeof(cr_lf)-1));
}
}	
}