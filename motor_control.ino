#include "relay.h"
#include "motor_control.h"

static void pin_init(){
  pinMode(relay_channel_1,OUTPUT);
  pinMode(relay_channel_2,OUTPUT);
  pinMode(relay_channel_3,OUTPUT);
}

static void left_to_right(){
  digitalWrite(linear_motion_motor_left_to_right_switch,on);
  digitalWrite(linear_motion_motor_right_to_left_switch,off);
  digitalWrite(circular_motion_motor_switch,off);
}
static right_to_left(){
  digitalWrite(linear_motion_motor_left_to_right_switch,off);
  digitalWrite(linear_motion_motor_right_to_left_switch,on);
  digitalWrite(circular_motion_motor_switch,off);
}

static void rotate(){
  digitalWrite(linear_motion_motor_left_to_right_switch,off);
  digitalWrite(linear_motion_motor_right_to_left_switch,off);
  digitalWrite(circular_motion_motor_switch,on);
}

static void all_switch_off(){
  digitalWrite(linear_motion_motor_left_to_right_switch,off);
  digitalWrite(linear_motion_motor_right_to_left_switch,off);
  digitalWrite(circular_motion_motor_switch,off);
}

void run_brush(){
for(int i=0;i<left_to_right_step_count;i++){
left_to_right();
delay(linear_motion_motor_left_to_right_runtime);
rotate();
delay(circular_motion_motor_runtime);
}
all_switch_off();
delay(motor_cooling_delay);
for(int i=0;i<right_to_left_step_count;i++){
left_to_right();
delay(linear_motion_motor_right_to_left_runtime);
rotate();
delay(circular_motion_motor_runtime );
}
all_switch_off();
delay(motor_cooling_delay);
}
