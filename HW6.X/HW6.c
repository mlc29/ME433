#include <stdio.h>
#include "nu32dip.h"
#include "i2c_master_noint.h"

unsigned char addy = 0b01000000;
void delay();
void set_GP7(unsigned int x);

int main(void) {
    
    NU32DIP_Startup();
    
    // Init I2C pins B8(SCL) and B9(SDA)
    i2c_master_setup();
    
    // Init the chip, GP0 as input, GP7 as output
    i2c_master_start();
    i2c_master_send(addy);
    i2c_master_send(0x00);
    i2c_master_send(0b00000001);
    i2c_master_stop();
    
    while(1){
        // Blink the yellow LED for heartbeat
        NU32DIP_YELLOW = 0;
        delay();
        NU32DIP_YELLOW = 1;
        delay();
        
        // Blink GP7 to check for function
        set_GP7(1);
        delay();
        set_GP7(0);
        delay();
        
    }
}

// delay function for blinking LEDs
void delay(void){
    _CP0_SET_COUNT(0);
    while(_CP0_GET_COUNT()<12000000){}
}

// function for blinking GP7
void set_GP7(unsigned int x){
    unsigned short i;
    i = x<<7;
    i2c_master_start();
    i2c_master_send(addy);
    i2c_master_send(0x0A);
    i2c_master_send(i);
    i2c_master_stop();
}