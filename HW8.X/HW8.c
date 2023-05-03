#include <stdio.h>
#include "nu32dip.h"
#include "font.h"
#include "i2c_master_noint.h"
#include "mpu6050.h"
#include "ssd1306.h"

void blink(int iterations, int time_ms);


int main(void){
    
    // Setup the PIC and OLED screen
    NU32DIP_Startup();
    ssd1306_setup();
    
    while(1){
        _CP0_SET_COUNT(0);
        blink(1,50);         // Blink LEDs for heartbeat
        ssd1306_drawPixel(1,1,1);
        ssd1306_update();
        
        while(_CP0_GET_COUNT()<48000000){}
    }
}


// blink the LEDs
void blink(int iterations, int time_ms) {
    int i;
    unsigned int t;
    for (i = 0; i < iterations; i++) {
        NU32DIP_GREEN = 0; // on
        NU32DIP_YELLOW = 1; // off
        t = _CP0_GET_COUNT(); // should really check for overflow here
        // the core timer ticks at half the SYSCLK, so 24000000 times per second
        // so each millisecond is 24000 ticks
        // wait half in each delay
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }

        NU32DIP_GREEN = 1; // off
        NU32DIP_YELLOW = 0; // on
        t = _CP0_GET_COUNT(); // should really check for overflow here
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }
    }
}

