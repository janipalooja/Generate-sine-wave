// Generates 1kHz sine wave for 1 period (Time delay 1ms)

#include "mbed.h"
#define DEBUG // Comment out to disable debugging
#define SAMPLES 128
#define FREQUENCY 1000 //Hz -> 1kHz Frequency
#define RADIANS 6.28318530717959 //  Phase difference φ in radians

AnalogOut dac(PA_4);

volatile int i = 0;
float sine_wave_data[SAMPLES];
 
void Sample_timer_interrupt(void) {
    dac = sine_wave_data[i];
    #ifdef DEBUG
    printf("sample %i: %.4f\r\n", i, sine_wave_data[i]);
    #endif
    // Increment i from 0 to 127 and drop back to 0 at 128
    i = (i+1) & 0x07F; // 0 - 127
}

void generate_sine_wave() {
    for(int k=0; k < SAMPLES; k++) {
        sine_wave_data[k]=((1.0 + sin((float(k)/SAMPLES*RADIANS)))/2.0);
    }
}
 
int main()
{
    Ticker Sample_Period;

    generate_sine_wave();

    Sample_Period.attach(&Sample_timer_interrupt, 1.0/(FREQUENCY*SAMPLES));

    while(1) {}
}
