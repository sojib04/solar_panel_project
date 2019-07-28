#ifndef __RTC_H_
#define __RTC_H_

#define clean_counter_address     0x11
#define clean_flag_value0_address 0x12
#define clean_flag_value1_address 0x13
#define clean_flag_value2_address 0x14

#define rtc_check_byte1_address   0x15
#define rtc_check_byte2_address   0x16
#define rtc_check_byte3_address   0x17

#define rtc_check_byte1           0x06
#define rtc_check_byte2           0x07
#define rtc_check_byte3           0x08


typedef struct _rtc{
    uint8_t _hour;
    uint8_t _minute;
    uint32_t unix_time;
}Time;



//this structure contains the user input about time and date
typedef struct{
  uint8_t Date;
  uint8_t Month;
  uint8_t Hour;
  uint8_t Minute;
  uint8_t Meridian;
  uint16_t Year;
}panel_user_settings;

//this structure helps to get time and date input form user
 typedef struct{
  uint8_t digit_count;
  bool invalid_flag;
  uint8_t user_input_buffer[4];
  String parameter_name;
  String message_to_user;         
}panel_setup_time;

/*this function takes date and time input from user and set up the system rtc
 @input RTC_DS1307 type object
 @output none.sets the rtc up according to user
 */
void setup_rtc();

void rtc_init(LiquidCrystal lcd);
Time* get_time();
void write_rtc_ram(uint8_t address,uint8_t data);
uint8_t read_rtc_ram(uint8_t address);

#endif
