#ifndef __MAIN_HANDLER_H
#define __MAIN_HANDLER_H
void clean_panel(uint8_t clean_hour,uint8_t clean_minute,uint8_t *clean_counter,uint8_t*clean_flag,uint8_t current_hour,uint8_t current_minute);
bool get_project_state(uint8_t current_hour,uint8_t current_minute);
#endif
