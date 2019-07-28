#include "sample.h"

void get_parameters(SolarPanel *pPanel){
    uint16_t inst_voltage_value_digital=0;
    uint16_t inst_current_value_digital=0;
    float inst_power_value=0.00;
    float current_value_A=0.0;
    uint8_t loop_counter=0;

    //collection of samples
    for(loop_counter=0;loop_counter<sample_number;loop_counter++){
        inst_voltage_value_digital+=analogRead(voltage_sense_pin);
        inst_current_value_digital+=analogRead(current_sense_pin);
        delay(sampling_intervel);
    }

    //processing  instaneous voltage and storing avergae voltage current power in the structures
    pPanel->average_voltage= ((float)inst_voltage_value_digital)*voltage_constant;
    pPanel->average_current=((float)inst_current_value_digital-2.43)*10.0;
    if( pPanel->average_current<0){
      pPanel->average_current=0.0;
    }
    //current_value_A=(float)inst_current_value_digital*current_constant_A;
    pPanel->average_power=pPanel->average_voltage* pPanel->average_current;
    pPanel->average_current=pPanel->average_current*1000.0;
 }
