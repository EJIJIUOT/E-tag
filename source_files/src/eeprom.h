#include <stdint.h>
#include <stdbool.h>
#include "nvs.h"
#include "nvs_flash.h"
#include <string.h>
#include "driver/timer.h"
#include "commands.h"
#define NAME_NVS "nvs"


void check_eeprom(void);
void eeprom_read_val(uint8_t value);

bool set_eeprom_bt_name(uint32_t num,char* name);
bool get_eeprom_bt_name(uint32_t num,char* name);
uint8_t check_name(char* name,size_t size);//проверка имени ВТ


uint8_t check_name(char* name,size_t size)
{
size_t required_size =strlen(name);
int pos=0;
uint8_t error=0;//0 нет ошибки
if(required_size ==size-1)
{
while(pos<required_size)
{
if(name[pos]=='\0')
{
//printf("NULL data\n");
error=1;
return error; 
break;
}
if(!((name[pos]<='!')||(name[pos]>'{')))
{    
////printf("name_tmp :%c\n",name[pos]);
pos++;
}
else
{
 //printf("invalid  value\n");
 error=2;
 return error; 
break; 
}  
}
return error;
}
else
{
 error=3; 
return error;  
}
}

bool set_eeprom_bt_name(uint32_t num,char* name)
{  
nvs_flash_init();
nvs_handle_t eeprom_nvs_handle;
nvs_open(NAME_NVS, NVS_READWRITE, &eeprom_nvs_handle);
int pos=0;
bool write=false;
size_t required_size=0;
switch (num)
{
case 0:
required_size =NAME_LEN;
break;
case 1:
required_size =NAME_LEN;
break;
case 2:
required_size =PIN_LEN;
break;
default:
break;
}  

char * name_tmp = (char*) calloc(required_size, sizeof(char));
if(name[pos]=='\0')
{ 
free(name_tmp); 
nvs_close(eeprom_nvs_handle);
nvs_flash_deinit();  
return write;
}
if(required_size<=0)
{ 
free(name_tmp); 
nvs_close(eeprom_nvs_handle);
nvs_flash_deinit();  
return write;
}
//printf("required_size:%d\n",required_size);
while(pos<required_size)
{

if(!((name[pos]<'!')||(name[pos]>'{')))
{    
name_tmp[pos]=name[pos];
//printf("name_tmp :%c\n",name_tmp[pos]);
pos++;
}
else
{
 ////printf("exit\n");  
break;
}
}
switch(num){
 
case 0:
nvs_set_str(eeprom_nvs_handle, bt_name, name_tmp);  
write=true;
break;
case 1:  
nvs_set_str(eeprom_nvs_handle, bt_connect_name, name_tmp);
write=true;
break;
case 2:
nvs_set_str(eeprom_nvs_handle, bt_pin_name, name_tmp);
write=true;
break;

default:
write=false;
break;
}
if (write==true)
{
nvs_commit(eeprom_nvs_handle);
}
nvs_close(eeprom_nvs_handle);
nvs_flash_deinit(); 
free(name_tmp);
return write;  
}

bool get_eeprom_bt_name(uint32_t num,char* name)
{ 
bool ok=false;  
size_t required_size =0;
switch (num)
{
case 0:
required_size =NAME_LEN;
break;
case 1:
required_size =NAME_LEN;
break;
case 2:
required_size =PIN_LEN;
break;
default:
break;
} 

if(required_size<=0)
{
return ok;
}
nvs_flash_init();
nvs_handle_t eeprom_nvs_handle;
nvs_open(NAME_NVS, NVS_READONLY, &eeprom_nvs_handle);
switch(num){
case 0:
nvs_get_str(eeprom_nvs_handle,bt_name,NULL,&required_size);
//printf("required_size :%d\n",required_size);
nvs_get_str(eeprom_nvs_handle,bt_name,name,&required_size);
ok=true;
break;  
case 1:    
nvs_get_str(eeprom_nvs_handle,bt_connect_name,name,&required_size);
ok=true;
break;
case 2:
nvs_get_str(eeprom_nvs_handle, bt_pin_name,name,&required_size);
ok=true;
break;
default:
break;
}
nvs_close(eeprom_nvs_handle);
nvs_flash_deinit();
return ok;
}

void eeprom_read_val(uint8_t value)
{
 // portENTER_CRITICAL(&mutex);
//timer_pause(TIMER_GROUP_0 , TIMER_1 ); 
if(start_sound==true)
{
timer_pause(TIMER_GROUP_0  , TIMER_0 );
}
//timer_pause(TIMER_GROUP_1  , TIMER_1 );
  nvs_flash_init ();
  nvs_handle_t eeprom_nvs_handle;
  nvs_open(NAME_NVS, NVS_READONLY, &eeprom_nvs_handle);
  switch(value)
  {
  case 0:
  nvs_get_u8(eeprom_nvs_handle, player_id_name, &eeprom.player_id);
  break;
  case 1:
  nvs_get_u8(eeprom_nvs_handle, team_id_name, &eeprom.team_id);
  break;
   case 2:
  nvs_get_u8(eeprom_nvs_handle, damage_name, &eeprom.damage);
  break;
   case 3:
  nvs_get_u8(eeprom_nvs_handle, ir_power_name, &eeprom.ir_power);
  break;
   case 4:
  nvs_get_u16(eeprom_nvs_handle, bullets_clip_name, &eeprom.bullets_in_clip);
  break;
   case 5:
  nvs_get_u16(eeprom_nvs_handle, clips_name, &eeprom.clips);
  break;
 case 6:
  nvs_get_u8(eeprom_nvs_handle, reload_time_name, &eeprom.reload_duration);
  break;
   case 7:
  nvs_get_u16(eeprom_nvs_handle, safe_duration_name, &eeprom.safe_duration);
  break;
   case 8:
  nvs_get_u16(eeprom_nvs_handle, shock_time_name, &eeprom.shock_time);
  break;
   case 9:
 nvs_get_u16(eeprom_nvs_handle, life_start_name, &eeprom.life_after_start);
  break;
   case 10:
  nvs_get_u16(eeprom_nvs_handle, cyclic_rate_name, &eeprom.cyclic_rate);
  break;
  case 11:
 nvs_get_u8(eeprom_nvs_handle, time_off_name, &eeprom_time_off);
  break;
 case 12:
 nvs_get_u8(eeprom_nvs_handle, friendly_fire_name, &eeprom.friendly_fire_enable);
  break;
case 13:
 nvs_get_u16(eeprom_nvs_handle, batt_full_name, &eeprom.batt_full_voltage);
  break;
case 14:
 nvs_get_u16(eeprom_nvs_handle, batt_low_name, &eeprom.batt_low_voltage);
  break;
  default:
  break;
  }
  nvs_close(eeprom_nvs_handle);
  nvs_flash_deinit();
//timer_start(TIMER_GROUP_0, TIMER_1 );
if(start_sound==true)
{
timer_start(TIMER_GROUP_0  , TIMER_0 );
}
 // portEXIT_CRITICAL(&mutex);
}

void check_eeprom(){//проверка значений еепром
//nvs_flash_init ();-иниацилизация nvs
//nvs_flash_erase ();-стререть nvs
//nvs_open("List", NVS_READWRITE, &my_handle);-открыть nvs
//nvs_handle my_handle;-дескриптор
//nvs_get_i8(my_handle, "nvs_i8", &nvs_i8);-прочитать nvs
//nvs_set_i8(my_handle, "nvs_i8", nvs_i8);-записать nvs
//nvs_get_i16, nvs_get_u32 разные типы данных
//nvs_commit(my_handle);-обновить запись
//nvs_close(my_handle);-заркыть

timer_pause(TIMER_GROUP_0, TIMER_1 );
if(start_sound==true)
{
timer_pause(TIMER_GROUP_0  , TIMER_0 );
}
//timer_pause(TIMER_GROUP_1  , TIMER_1 );
//portENTER_CRITICAL(&mutex);
bool write_val_nvs=false;
nvs_flash_init ();
nvs_handle_t eeprom_nvs_handle;
nvs_open(NAME_NVS, NVS_READWRITE, &eeprom_nvs_handle);

nvs_get_u8(eeprom_nvs_handle, player_id_name, &eeprom.player_id);
nvs_get_u8(eeprom_nvs_handle, team_id_name, &eeprom.team_id);
nvs_get_u8(eeprom_nvs_handle, damage_name, &eeprom.damage);
nvs_get_u8(eeprom_nvs_handle, reload_time_name, &eeprom.reload_duration);
//printf("reload_duration :%d\n",eeprom.reload_duration);
nvs_get_u8(eeprom_nvs_handle, ir_power_name, &eeprom.ir_power);
////printf("eeprom_ir_power :%d\n",eeprom_ir_power);
nvs_get_u8(eeprom_nvs_handle, second_weapon_name, &eeprom.second_weapon_enable);
////printf("eeprom_second_weapon_enable :%d\n",eeprom_second_weapon_enable);
nvs_get_u8(eeprom_nvs_handle, friendly_fire_name, &eeprom.friendly_fire_enable);
////printf("eeprom_friendly_fire_enable :%d\n",eeprom_friendly_fire_enable);
nvs_get_u8(eeprom_nvs_handle, statistic_name, &eeprom.statistic_enable);
////printf("eeprom_statistic_enable :%d\n",eeprom_statistic_enable);
nvs_get_u16(eeprom_nvs_handle, safe_duration_name, &eeprom.safe_duration);
//printf("safe_duration:%d\n",eeprom.safe_duration);
nvs_get_u16(eeprom_nvs_handle, shock_time_name, &eeprom.shock_time);
//printf("shock_time :%d\n",eeprom.shock_time);
nvs_get_u8(eeprom_nvs_handle, time_off_name, &eeprom_time_off);
////printf("eeprom_time_off:%d\n",eeprom_time_off);

nvs_get_u16(eeprom_nvs_handle, bullets_clip_name, &eeprom.bullets_in_clip);
bullets=eeprom.bullets_in_clip;
//printf("bullets_in_clip:%d\n",eeprom.bullets_in_clip);
nvs_get_u16(eeprom_nvs_handle, clips_name, &eeprom.clips);
clips=eeprom.clips;
//printf("clips:%d\n",eeprom.clips);
nvs_get_u16(eeprom_nvs_handle, life_start_name, &eeprom.life_after_start);
life_in_percent=eeprom.life_after_start;
////printf("eeprom_life_after_start :%d\n",eeprom_life_after_start);
nvs_get_u16(eeprom_nvs_handle, batt_full_name, &eeprom.batt_full_voltage);
////printf("eeprom_batt_full_voltage :%d\n",eeprom_batt_full_voltage);
nvs_get_u16(eeprom_nvs_handle, batt_low_name, &eeprom.batt_low_voltage);
////printf("eeprom_batt_low_voltage :%d\n",eeprom_batt_low_voltage);
nvs_get_u16(eeprom_nvs_handle, cyclic_rate_name, &eeprom.cyclic_rate);
//printf("cyclic_rate :%d\n",eeprom.cyclic_rate);

////////uint8//////////
if (eeprom.player_id>127)
{
eeprom.player_id=127;
nvs_set_u8(eeprom_nvs_handle, player_id_name, eeprom.player_id);
////printf("set eeprom_player_id :%d\n",eeprom_player_id);
write_val_nvs=true;	
} 
if (eeprom.team_id>3)
{
eeprom.team_id=3;
nvs_set_u8(eeprom_nvs_handle, team_id_name, eeprom.team_id);
////printf("set eeprom_team_id :%d\n",eeprom_team_id);
write_val_nvs=true;	
} 
if (eeprom.damage>15)
{
eeprom.damage=15;
nvs_set_u8(eeprom_nvs_handle, damage_name, eeprom.damage);
////printf("set eeprom_damage :%d\n",eeprom_damage);
write_val_nvs=true;
}
if (eeprom.bullets_in_clip>999)
{
eeprom.bullets_in_clip=999;
nvs_set_u16(eeprom_nvs_handle, bullets_clip_name, eeprom.bullets_in_clip);
////printf("set eeprom_bullets_in_clip :%d\n",eeprom_bullets_in_clip);
write_val_nvs=true;
}
if (eeprom.clips>999)
{
eeprom.clips=999;
nvs_set_u16(eeprom_nvs_handle, clips_name, eeprom.clips);
////printf("set eeprom_clips :%d\n",eeprom_clips);
write_val_nvs=true;
}
if (eeprom.reload_duration>99)
{
eeprom.reload_duration=99;
nvs_set_u8(eeprom_nvs_handle, reload_time_name, eeprom.reload_duration);
////printf("set eeprom_reload_duration :%d\n",eeprom_reload_duration);
write_val_nvs=true;
}
if (eeprom.friendly_fire_enable>1)
{
eeprom.friendly_fire_enable=1;
nvs_set_u8(eeprom_nvs_handle, friendly_fire_name, eeprom.friendly_fire_enable);
////printf("set eeprom_friendly_fire_enable :%d\n",eeprom_friendly_fire_enable);
write_val_nvs=true;
}
if (eeprom.statistic_enable>2)
{
eeprom.statistic_enable=2;
nvs_set_u8(eeprom_nvs_handle, statistic_name, eeprom.statistic_enable);
////printf("set eeprom_statistic_enable :%d\n",eeprom_statistic_enable);
write_val_nvs=true;
}
if (eeprom.safe_duration>30000)
{
eeprom.safe_duration=30000;
nvs_set_u8(eeprom_nvs_handle, safe_duration_name, eeprom.safe_duration);
////printf("set eeprom_safe_duration :%d\n",eeprom_safe_duration);
write_val_nvs=true;
}
if (eeprom.shock_time>30000)
{
eeprom.shock_time=30000;
nvs_set_u8(eeprom_nvs_handle, shock_time_name, eeprom.shock_time);
////printf("set eeprom_safe_duration :%d\n",eeprom_safe_duration);
write_val_nvs=true;
}
if (eeprom.ir_power>7)
{
eeprom.ir_power=7;
nvs_set_u8(eeprom_nvs_handle, ir_power_name, eeprom.ir_power);
////printf("set eeprom_ir_power :%d\n",eeprom_ir_power);
write_val_nvs=true;
}
if (eeprom_time_off>99)
{
eeprom_time_off=99;
nvs_set_u8(eeprom_nvs_handle, time_off_name, eeprom_time_off);
////printf("set eeprom_ir_power :%d\n",eeprom_ir_power);
write_val_nvs=true;
}
if (eeprom.second_weapon_enable>2)
{
eeprom.second_weapon_enable=2;
nvs_set_u8(eeprom_nvs_handle, second_weapon_name, eeprom.second_weapon_enable);
////printf("set eeprom_second_weapon_enable :%d\n",eeprom_second_weapon_enable);
write_val_nvs=true;
}
//////////uint16//////////
if (eeprom.life_after_start>999)
{
eeprom.life_after_start=999;
nvs_set_u16(eeprom_nvs_handle, life_start_name, eeprom.life_after_start);
////printf("set eeprom_life_after_start :%d\n",eeprom_life_after_start);
write_val_nvs=true;
}
if ((eeprom.batt_full_voltage==0xFFFF)||(eeprom.batt_full_voltage<3000))
{
eeprom.batt_full_voltage=4200;
nvs_set_u16(eeprom_nvs_handle, batt_full_name, eeprom.batt_full_voltage);
////printf("set eeprom_batt_full_voltage :%d\n",eeprom_batt_full_voltage);
write_val_nvs=true;
}
if ((eeprom.batt_low_voltage==0xFFFF)||(eeprom.batt_low_voltage<2100))
{
eeprom.batt_low_voltage=2100;
nvs_set_u16(eeprom_nvs_handle, batt_low_name, eeprom.batt_low_voltage);
////printf("set eeprom_batt_low_voltage :%d\n",eeprom_batt_low_voltage);
write_val_nvs=true;
}
if ((eeprom.cyclic_rate>800)||(eeprom.cyclic_rate<30))
{
eeprom.cyclic_rate=30;
nvs_set_u16(eeprom_nvs_handle, cyclic_rate_name, eeprom.cyclic_rate);
////printf("set eeprom_cyclic_rate :%d\n",eeprom_cyclic_rate);
write_val_nvs=true;
}
if(write_val_nvs==true)
{
//printf("nvs_commit\n");	
nvs_commit(eeprom_nvs_handle);
}
nvs_close(eeprom_nvs_handle);
nvs_flash_deinit();
//printf("check 0k\n");
//portEXIT_CRITICAL(&mutex);
//#if (HARDWARE_MODE==0)
timer_start(TIMER_GROUP_0, TIMER_1 );
if(start_sound==true)
{
timer_start(TIMER_GROUP_0  , TIMER_0 );
}
//timer_start(TIMER_GROUP_1  , TIMER_1 );
//#endif
}

