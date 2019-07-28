#include<LiquidCrystal.h>
#include "lcd.h"

static uint8_t print_to_lcd(ParamPrint *pParam,LiquidCrystal lcd,uint8_t current_column,uint8_t current_line){
  uint8_t string_length=0;
  lcd.setCursor(current_column,current_line);
  lcd.print(pParam->param_name);
  string_length=(pParam->param_name).length();
  current_column+=string_length;
  lcd.print(pParam->param_value);
  string_length=(pParam->param_value).length();
  current_column+=string_length;
  lcd.print(pParam->param_unit);
  string_length=(pParam->param_unit).length();
  current_column+=string_length;
  return current_column;
}



void print_lcd(SolarPanel *pPanel, LiquidCrystal lcd){
  ParamPrint param;
  uint8_t current_column=0;
  uint8_t current_line=0;
  lcd.clear();
  
  //printing voltage
  param.param_name="V=";
  param.param_value=String(pPanel->average_voltage,2);
  param.param_unit="V";
  current_column=print_to_lcd(&param,lcd,current_column,current_line);
  
  //printing power
  current_column+=1;
  param.param_name="P=";
  param.param_value=String(pPanel->average_power,2);
  param.param_unit="W";
  current_column=print_to_lcd(&param,lcd,current_column,current_line);
  
  //printing current
  current_line=1;
  current_column=0;
  param.param_name="I=";
  param.param_value=String(pPanel->average_current,2);
  param.param_unit="mA";
  current_column=print_to_lcd(&param,lcd,current_column,current_line);
 }
