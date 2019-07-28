#include <LiquidCrystal.h>
#include "sample.h"
#include "lcd.h"
#include "rtc.h"
#include "gsm.h"
#include "user_def.h"
#include "main_handler.h"

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SolarPanel panel;

void setup() {
  lcd.begin(LcdColumnNum,LcdRowNum);
  delay(100);
  analogWrite(led_brightness,3.5);
  lcd.print("Initializing....");
  Serial.begin(9600);
  Serial2.begin(9600);
  rtc_init(lcd);
  lcd.clear();
}

void loop() { 
 uint8_t current_hour;
 uint8_t current_minute;
 bool    project_state_flag=0;
 uint8_t panel_clean_count=0;
 uint8_t panel_clean_time_flag[3]={0,0,0};
 uint32_t modem_next_flag_set_time=0;
 uint8_t modem_flag=1;
 while(1){
  current_hour=get_time()->_hour;
  current_minute=get_time()->_minute;
  project_state_flag=get_project_state(current_hour,current_minute);
  if(project_state_flag==0){
    panel_clean_time_flag[0]=0;
    panel_clean_time_flag[1]=0;
    panel_clean_time_flag[2]=0;
    modem_next_flag_set_time=0;
    lcd.clear();
  }
  if(project_state_flag==1){
   get_parameters(&panel);                          
   print_lcd(&panel,lcd);
   clean_panel( clean_hour1,clean_minute1,&panel_clean_count,&panel_clean_time_flag[0],current_hour,current_minute);
   clean_panel(clean_hour2, clean_minute2,&panel_clean_count,&panel_clean_time_flag[1],current_hour,current_minute);
   clean_panel( clean_hour3, clean_minute3,&panel_clean_count,&panel_clean_time_flag[2],current_hour,current_minute);
   if((get_time()->unix_time)>modem_next_flag_set_time&&modem_flag==0){
   modem_flag=1;
   }
  if((uint8_t)panel.average_voltage<=low_voltage_threshold&&modem_flag==1){
   send_sms();
   modem_flag=0;
   modem_next_flag_set_time=get_time()->unix_time+message_interval;
       
  }
 }

 } 
}
