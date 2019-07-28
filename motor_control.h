#ifndef __MOTOR_CONTROL_H
#define __MOTOR_CONTROL_H
#define circular_motion_motor_runtime             3000
#define linear_motion_motor_left_to_right_runtime 3000
#define linear_motion_motor_right_to_left_runtime 4000
#define motor_cooling_delay                       6000 
#define right_to_left_step_count                  4
#define left_to_right_step_count                  3 
#define  on                                       0x1
#define  off                                      0x0
/*@function : This function cleans the panel two times.from right to left
and left to right.
@input      : none
@output     : none
 */
void run_brush(void);
#endif
