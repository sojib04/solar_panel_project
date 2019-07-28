#include <Wire.h>
#include "rtc.h"
#include "RTClib.h"

RTC_DS1307 _rtc;
Time SystemTime;

void rtc_init(LiquidCrystal lcd){
    if (! _rtc.begin()) {
    while (1);
  }
 uint8_t byte1=read_rtc_ram(rtc_check_byte1_address);
 uint8_t byte2=read_rtc_ram(rtc_check_byte2_address);
 uint8_t byte3=read_rtc_ram(rtc_check_byte3_address);
 
 if(byte1!=rtc_check_byte1||byte2!=rtc_check_byte2||byte3!=rtc_check_byte3){
  lcd.print("set up time");
  setup_rtc();
  write_rtc_ram(rtc_check_byte1_address,rtc_check_byte1);
  write_rtc_ram(rtc_check_byte2_address,rtc_check_byte2);
  write_rtc_ram(rtc_check_byte3_address,rtc_check_byte3);
 }  
}

/*
 this function checks whether a year is a leap year or not
 @input year
 @output true if leap yaar false if not leap year
 */
static bool leap_year(uint16_t Year){
  if((Year%4)==0){
    if((Year%100)==0){
      if((Year%400)==4000){
        return true;
      }
      else 
      return false;
    }
    else 
    return true;
  }
  else
  return false;
}

/*this function converts 12-hr clock to 14-hr clock
 @input pointer to panel_user_seetings structure
 @output none.set 24hr value in the panel_user_seetings structure
 */
static clock_converter(panel_user_settings *prtc){
  if(prtc->Meridian==1){
    prtc->Hour=prtc->Hour+12;
  }
}

/*this function finds out the maximum day in a month
 @input month and year
 @output maximum day in the month
 */
static uint8_t get_max_day(uint8_t month,uint16_t year){
  enum month_name{January=1,February,March,April,May,June,July,August,September,October,November,December};
  uint8_t max_day=0;
  switch(month)
{
  case January:
  max_day=31;
  break;
  
  case February:
  {
    if(leap_year(year))
    max_day=29;
    else
    max_day=28;
  }
  break;
  
  case March:
  max_day=31;
  break;
  
  case April:
  max_day=30;
  break;
  
  case May:
  max_day=31;
  break;
  
  case June:
  max_day=30;
  break;
  
  case July:
  max_day=31;
  break;

  case August:
  max_day=31;
  break;

  case September:
  max_day=30;
  break;

  case October:
  max_day=31;
  break;

  case November:
  max_day=30;
  break;

  case December:
  max_day=31;
  break;

  default:
  max_day=30;
  
}
return max_day;
}

/*this function takes time and date input from user and validates it
 *@ pointer to input panel_setup_time struct and panel_user_settings struct
 *@output none.store time and date value in panel_user_settings struct
 */
static void get_time_parameter(panel_setup_time *psetup,panel_user_settings *rtc){
  uint8_t loop_count=0;
  Serial.println(psetup->message_to_user);
  do{
    while(loop_count!=psetup->digit_count){
      if(Serial.available()>0){
        psetup->user_input_buffer[loop_count]=Serial.read()-48;
        loop_count++;
      }
    }
    if(psetup->parameter_name.equals("year")){
      rtc->Year=psetup->user_input_buffer[0]*1000+psetup->user_input_buffer[1]*100+psetup->user_input_buffer[2]*10+psetup->user_input_buffer[3];
    }
    else if(psetup->parameter_name.equals("month")){
    
      rtc->Month=psetup->user_input_buffer[0]*10+psetup->user_input_buffer[1];
    }
    else if(psetup->parameter_name.equals("date")){
       rtc->Date=psetup->user_input_buffer[0]*10+psetup->user_input_buffer[1];
    }
    else if(psetup->parameter_name.equals("hour")){
       rtc->Hour=psetup->user_input_buffer[0]*10+psetup->user_input_buffer[1];
    }
    else if(psetup->parameter_name.equals("minute")){
       rtc->Minute=psetup->user_input_buffer[0]*10+psetup->user_input_buffer[1];
    }
    else{
      rtc->Meridian=psetup->user_input_buffer[0];
    }

    //validating year
    if(psetup->parameter_name.equals("year")){
      if(rtc->Year<2019){
        Serial.println("invalid "+psetup->parameter_name+"!!");
        Serial.println(psetup->message_to_user);
        psetup->invalid_flag=true;
        loop_count=0;
      }
      else{
        psetup->invalid_flag=false;
      }

    }
    //end of validating year

    //validating month
    else if(psetup->parameter_name.equals("month")){
      if((rtc->Month<1)||(rtc->Month>12)){
          Serial.println("invalid "+psetup->parameter_name+"!!");
          Serial.println(psetup->message_to_user);
          psetup->invalid_flag=true;
          loop_count=0;
        }
      else{
          psetup->invalid_flag=false;
      }

    }
    //end of validating month

    //validating date
    else if(psetup->parameter_name.equals("date")){
      if((rtc->Date<1)||((rtc->Date)>get_max_day(rtc->Month,rtc->Year))){
          Serial.println("invalid "+psetup->parameter_name+"!!");
          Serial.println(psetup->message_to_user);
          psetup->invalid_flag=true;
          loop_count=0;
        }
      else{
          psetup->invalid_flag=false;
      }

    }
    //end of validating date


    //validating hour
    else if(psetup->parameter_name.equals("hour")){
      if((rtc->Hour<1)||(rtc->Hour>12)){
          Serial.println("invalid "+psetup->parameter_name+"!!");
          Serial.println(psetup->message_to_user);
          psetup->invalid_flag=true;
          loop_count=0;
        }
      else{
          psetup->invalid_flag=false;
      }
    }
    //end of validating hour

    //validating minute
    else if(psetup->parameter_name.equals("minute")){
      if((rtc->Minute<1)||(rtc->Minute>60)){
          Serial.println("invalid "+psetup->parameter_name+"!!");
          Serial.println(psetup->message_to_user);
          psetup->invalid_flag=true;
          loop_count=0;
        }
      else{
          psetup->invalid_flag=false;
      }

    }
    //end of validating minute

    //validating meridian
    else{
      if((rtc->Meridian>1)||(rtc->Meridian<0)){
          Serial.println("invalid "+psetup->parameter_name+"!!");
          Serial.println(psetup->message_to_user);
          psetup->invalid_flag=true;
          loop_count=0;
        }
      else{
          psetup->invalid_flag=false;
      }

    }
    //end of meridian


  }
  while(psetup->invalid_flag);

}

void setup_rtc(){
  panel_user_settings rtc;
  panel_setup_time user_setup;
  //year
  user_setup.digit_count=4;
  user_setup.invalid_flag=false;
  user_setup.parameter_name="year";
  user_setup.message_to_user="set year : 2019 and there after";
  get_time_parameter(&user_setup,&rtc);
  //end of year

  //month 
  user_setup.digit_count=2;
  user_setup.invalid_flag=false;
  user_setup.parameter_name="month";
  user_setup.message_to_user="set month : type the number of month. like for January type 01;for December type 12";
  get_time_parameter(&user_setup,&rtc);
  //end of month

  //date
  user_setup.digit_count=2;
  user_setup.invalid_flag=false;
  user_setup.parameter_name="date";
  user_setup.message_to_user="set day of the month like 01,02,03...30,31";
  get_time_parameter(&user_setup,&rtc);
  //end of date

//hour
  user_setup.digit_count=2;
  user_setup.invalid_flag=false;
  user_setup.parameter_name="hour";
  user_setup.message_to_user="set hour : type hour in two digit in 12 hour clock system";
  get_time_parameter(&user_setup,&rtc);
//end of hour

//minute
  user_setup.digit_count=2;
  user_setup.invalid_flag=false;
  user_setup.parameter_name="minute";
  user_setup.message_to_user="set minute : type minute in two digit";
  get_time_parameter(&user_setup,&rtc);
//end of minute

//meridian
  user_setup.digit_count=1;
  user_setup.invalid_flag=false;
  user_setup.parameter_name="meridian";
  user_setup.message_to_user="set am/pm : for am type 0 for pm type 1";
  get_time_parameter(&user_setup,&rtc);
//end of meridaina
  clock_converter(&rtc);
 if (! _rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
     _rtc.adjust(DateTime(rtc.Year,rtc.Month,rtc.Date, rtc.Hour,rtc.Minute, 0));
  }
}


Time* get_time(){
    DateTime now = _rtc.now();
    SystemTime._hour=now.hour();
    SystemTime._minute=now.minute();
    SystemTime.unix_time=now.unixtime();
    return &SystemTime;
}

void write_rtc_ram(uint8_t address,uint8_t data)
{
   _rtc.writenvram(address,data);
}
uint8_t read_rtc_ram(uint8_t address){
  return _rtc.readnvram(address);
}
