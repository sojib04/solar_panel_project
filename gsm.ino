#include "gsm.h"
#include "user_def.h"
#include "relay.h"
void send_sms(){

digitalWrite(modem_switch,HIGH);
delay(8000);
delay(8000);
delay(8000);
delay(8000);
delay(8000);
delay(8000);
Serial3.print("ATE0\r");
delay(2000);
Serial3.print("AT+CMGF=1\r");
delay(2000);
Serial3.print("AT+CMGS=\"+8801923291312\"\r");
delay(2000);
Serial3.print(sms);
delay(2000);
Serial3.write(0x1A);
delay(2000);
delay(8000);
delay(8000);
delay(8000);
delay(8000);
delay(8000);
delay(8000);
digitalWrite(modem_switch,HIGH);
}
