//LCD declarations
#ifndef __LCD_H
#define __LCD_H
#define LcdColumnNum  16
#define LcdRowNum     2
#define rs            34
#define en            35
#define d4            30
#define d5            31
#define d6            32
#define d7            33
#define led_brightness A3
typedef struct{
  String param_name;
  String param_value;
  String param_unit;
}ParamPrint;
/*
this function prints avergae voltage,current,power in lcd
@input : SolarPanel structure pointer,LiquidCrystal instance
@output:
V=xx.yyV P=xx.yyW
I=xx.yymA 
*/
void print_lcd(SolarPanel *pPanel,LiquidCrystal lcd);
#endif
