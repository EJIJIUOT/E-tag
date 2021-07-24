#include <stdint.h>
#include <stdbool.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/rmt.h"
#include "led_strip.h"

#define WS2812_OUT   GPIO_NUM_21
#define RMT_TX_CHANNEL RMT_CHANNEL_0
#define LED_NUMBER 16

typedef struct parametrs
 {
    uint8_t color_leds;
	uint8_t num_leds;
	uint8_t num_leds_non;
	uint32_t tim_ms;
 }tparametrs;

void ws2812_Task(void* arg);
void get_light_color(uint8_t color,uint8_t num,uint8_t num_non,uint32_t ms); 
xQueueHandle ws2812_parametrs = NULL;

void get_light_color(uint8_t color,uint8_t num,uint8_t num_non,uint32_t ms)
{
	tparametrs par_tmp;
	par_tmp.color_leds= color;
	par_tmp.num_leds=num;
	par_tmp.num_leds_non=num_non;
	par_tmp.tim_ms=ms;
		#if (HARDWARE_MODE==0)
	if(BluetoothSerial_hasClient()==true)
    { 
	//printf("get_ligth\n"); 	
		switch(color)
	 {
		 case 0:
		
		 BluetoothSerial_write(red_vibro,4);
		 break;
         case 1:
		 
		 BluetoothSerial_write(blue_vibro,4);
		 break; 
		 case 2:
		 
		 BluetoothSerial_write(yellou_vibro,4);
		 break;
		 case 3:
		
		 BluetoothSerial_write(green_vibro,4);
		 break;
		 default:
		 break;
	 }
	}
#endif
    xQueueSend(ws2812_parametrs, &par_tmp, 1);
}	

 void ws2812_Task(void* arg)
{
    rmt_config_t config = RMT_DEFAULT_CONFIG_TX(WS2812_OUT, RMT_TX_CHANNEL);
    // set counter clock to 40MHz
    config.clk_div = 2;
    rmt_config(&config);
    rmt_driver_install(config.channel, 0, 0);
    // install ws2812 driver
    led_strip_config_t strip_config = LED_STRIP_DEFAULT_CONFIG(LED_NUMBER, (led_strip_dev_t)config.channel);
   led_strip_t *strip = led_strip_new_rmt_ws2812(&strip_config);

    tparametrs param_tmp;
    uint8_t color_leds;
	uint8_t num_leds;
	uint8_t num_leds_non;
	uint32_t tim_ms;
	uint32_t tim_update;
	
    for(;;) {
     
	if(xQueueReceive(ws2812_parametrs, &param_tmp, portMAX_DELAY))
	{ 
	color_leds=param_tmp.color_leds;
	num_leds=param_tmp.num_leds;
	num_leds_non=param_tmp.num_leds_non;
    tim_ms=param_tmp.tim_ms;
    if(LED_NUMBER<=20)
	{
	tim_update=1;
	}
	else if ((LED_NUMBER>20)&&(LED_NUMBER<=40))
	{
    tim_update=2;
	}
	else if ((LED_NUMBER>40)&&(LED_NUMBER<=80))
	{
    tim_update=3;
	}
	else if ((LED_NUMBER>80)&&(LED_NUMBER<=100))
	{
    tim_update=5;
	}
  //  if(xQueueReceive(ws2812_num_leds, &num_leds, portMAX_DELAY))
//	{
//	if(xQueueReceive(timer_ms, &tim_ms, portMAX_DELAY))
//	{	
     if((num_leds<=LED_NUMBER)&&(num_leds_non<=LED_NUMBER))
	 { 
	if(tim_ms==0)
	{
	//printf("delay==0\n");	 
	switch(color_leds)
	{
	case 0://red
    for(int i=0;i<num_leds;i++)
	{
    strip->set_pixel(strip, i, 128, 0, 0);
    }
	for(int i=0;i<num_leds_non;i++)
	{
    strip->set_pixel(strip, i, 0, 0, 0);
    }
    strip->refresh(strip, tim_update);
	//gpio_set_level(RELAY,1);
	break;
    case 1://blue
    for(int i=0;i<num_leds;i++)
	{
   strip->set_pixel(strip, i, 0, 0, 128);
    }
	for(int i=0;i<num_leds_non;i++)
	{
    strip->set_pixel(strip, i, 0, 0, 0);
    }
    strip->refresh(strip, tim_update);
	//gpio_set_level(RELAY,1);
	break;
	case 2://yelou
    for(int i=0;i<num_leds;i++)
	{
   strip->set_pixel(strip, i, 128, 128, 0);
    }
	for(int i=0;i<num_leds_non;i++)
	{
    strip->set_pixel(strip, i, 0, 0, 0);
    }
    strip->refresh(strip, tim_update);
	//gpio_set_level(RELAY,1);
	break; 
    case 3://green
    for(int i=0;i<num_leds;i++)
	{
   strip->set_pixel(strip, i, 0, 128, 0);
    }
	for(int i=0;i<num_leds_non;i++)
	{
    strip->set_pixel(strip, i, 0, 0, 0);
    }
    strip->refresh(strip, tim_update);
	//gpio_set_level(RELAY,1);
	break;
	case 4:
    for(int i=0;i<num_leds;i++)
	{
   strip->set_pixel(strip, i, 96, 128, 96);
    }
	for(int i=0;i<num_leds_non;i++)
	{
    strip->set_pixel(strip, i, 0, 0, 0);
    }
    strip->refresh(strip, tim_update);
	//gpio_set_level(RELAY,1);
	break;
	case 5:
    for(int i=0;i<num_leds;i++)
	{
   strip->set_pixel(strip, i, 96, 128, 96);
    }
	for(int i=0;i<num_leds_non;i++)
	{
    strip->set_pixel(strip, i, 0, 0, 0);
    }
    strip->refresh(strip, tim_update);
	//gpio_set_level(RELAY,1);
	break;
	case 6:
    for(int i=0;i<num_leds;i++)
	{
   strip->set_pixel(strip, i, 96, 128, 96);
    }
   for(int i=0;i<num_leds_non;i++)
	{
    strip->set_pixel(strip, i, 0, 0, 0);
    }
    strip->refresh(strip, tim_update);
	//gpio_set_level(RELAY,1);
	break;
	 case 255:	 
    strip->clear(strip, tim_update);
    strip->refresh(strip, tim_update);
	//gpio_set_level(RELAY,0);
	break;	
	default:
	break;
   //printf("delay==0 end\n");
	}
	}//delay_ms>0
	else//delay==0 или <0
	{
	//printf("delay!=0\n");	
	switch(color_leds)
	{
	case 0://red
    for(int i=0;i<num_leds;i++)
	{
    strip->set_pixel(strip, i, 128, 0, 0);
    }
	for(int i=0;i<num_leds_non;i++)
	{
    strip->set_pixel(strip, i, 0, 0, 0);
    }
    strip->refresh(strip, tim_update);
	//gpio_set_level(RELAY,1);
	break;
    case 1://blue
    for(int i=0;i<num_leds;i++)
	{
   strip->set_pixel(strip, i, 0, 0, 128);
    }
    for(int i=0;i<num_leds_non;i++)
	{
    strip->set_pixel(strip, i, 0, 0, 0);
    }
    strip->refresh(strip, tim_update);
	//gpio_set_level(RELAY,1);
	break;
	case 2://yelou
    for(int i=0;i<num_leds;i++)
	{
   strip->set_pixel(strip, i, 128, 128, 0);
    }
    for(int i=0;i<num_leds_non;i++)
	{
    strip->set_pixel(strip, i, 0, 0, 0);
    }
    strip->refresh(strip, tim_update);
	//gpio_set_level(RELAY,1);
	break; 
    case 3://green
    for(int i=0;i<num_leds;i++)
	{
   strip->set_pixel(strip, i, 0, 128, 0);
    }
    for(int i=0;i<num_leds_non;i++)
	{
    strip->set_pixel(strip, i, 0, 0, 0);
    }
    strip->refresh(strip, tim_update);
	//gpio_set_level(RELAY,1);
	break;
	case 4:
    for(int i=0;i<num_leds;i++)
	{
   strip->set_pixel(strip, i, 96, 128, 96);
    }
   for(int i=0;i<num_leds_non;i++)
	{
    strip->set_pixel(strip, i, 0, 0, 0);
    }
    strip->refresh(strip, tim_update);
	//gpio_set_level(RELAY,1);
	break;
	case 5:
    for(int i=0;i<num_leds;i++)
	{
   strip->set_pixel(strip, i, 96, 128, 96);
    }
    for(int i=0;i<num_leds_non;i++)
	{
    strip->set_pixel(strip, i, 0, 0, 0);
    }
    strip->refresh(strip, tim_update);
	//gpio_set_level(RELAY,1);
	break;
	case 6:
    for(int i=0;i<num_leds;i++)
	{
   strip->set_pixel(strip, i, 96, 128, 96);
    }
    for(int i=0;i<num_leds_non;i++)
	{
    strip->set_pixel(strip, i, 0, 0, 0);
    }
    strip->refresh(strip, tim_update);
	//gpio_set_level(RELAY,1);
	break;	
	case 255:
    strip->clear(strip, tim_update);
    strip->refresh(strip, tim_update);
	//gpio_set_level(RELAY,0);
	break;
	default:
	break;
	}
	vTaskDelay(tim_ms/ portTICK_PERIOD_MS);
	strip->clear(strip, tim_update);
    strip->refresh(strip, tim_update);
	//gpio_set_level(RELAY,0);
	//printf("delay!=0 end\n");	
	}//else
	



     }//((num_leds<=LED_NUMBER)&&(num_leds_non<=LED_NUMBER))
	// }//xQueueReceive
//	}
	}//xQueueReceive
 }//for
}