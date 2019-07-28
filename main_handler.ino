#include"user_def.h"
#include "motor_control.h"
#include "main_handler.h"

 
void clean_panel(uint8_t clean_hour,uint8_t clean_minute,uint8_t *clean_counter,uint8_t*clean_flag,uint8_t current_hour,uint8_t current_minute){
 if(current_hour==clean_hour){
   if(current_minute>=clean_minute){
      if(*clean_flag==0&&*clean_counter<3){
        Serial.println(clean_hour);
        Serial.println(clean_minute);
        Serial.println("cleaning");
        run_brush();
        *clean_flag=1;
        (*clean_counter)++;
       }
    }
 }
}


bool get_project_state(uint8_t current_hour,uint8_t current_minute){
 uint8_t start_time_pass_flag=0;
 uint8_t end_time_pass_flag=0;
 if(current_hour>start_hour){
    start_time_pass_flag=1;
 }
 if(current_hour<start_hour){
    start_time_pass_flag=0;
 }
 if(current_hour==start_hour){
    if(current_minute>=start_minute){
        start_time_pass_flag=1;
    }
    else{
        start_time_pass_flag=0;
    }
 }


if(current_hour>end_hour){
    end_time_pass_flag=0;
 }
 if(current_hour<end_hour){
    end_time_pass_flag=1;
 }
 if(current_hour==end_hour){
    if(current_minute>end_minute){
    end_time_pass_flag=0;
    }
    else{
        end_time_pass_flag=1;
    }
 }


 if(start_time_pass_flag==1&& end_time_pass_flag==1){
    return 1;
 }
 else{
    return 0;
 }
}
