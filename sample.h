#ifndef __SAMPLE_H
#define __SAMPLE_H
//this structure holds solar panel parameters voltage,current,power
typedef struct{
    float average_voltage;
    float average_current;
    float average_power;
}SolarPanel;

//calculation constants

//adc related definations
#define adc_conversion_factor 0.00488
#define adc_constant          0.83
//sample related definations
#define sample_number 10
#define sampling_intervel 500  //in milisecondss

//voltage constant
#define voltage_multiply_factor 5.00
#define voltage_constant (voltage_multiply_factor*average_factor*adc_constant)

//average defination
#define average_factor 0.10










//connection pin description
#define voltage_sense_pin A0
#define current_sense_pin A1

/*
this function collects voltage sample
process samples and deteremine average voltage current and power
and put them in in solarpanel structure
@input  : SolarPanel structure pointer
@output : stroes average voltage current and power in solarpanel structure
*/
void get_parameters(SolarPanel *pPanel);
#endif
