#include <stdio.h>
#include "nu32dip.h"
#include "i2c_master_noint.h"

unsigned char addy_write = 0b01000000;
unsigned char addy_read = 0b01000001;
unsigned char IODIR = 0x00;
unsigned char GPIO = 0x09;
unsigned char OLAT = 0x0A;

void delay();
void generic_i2c_write(unsigned char address, unsigned char SFR, unsigned char value);

int main(void) {
    
    NU32DIP_Startup();
    
    // Init I2C pins B8(SCL) and B9(SDA)
    i2c_master_setup();
    
    // Init the chip, GP0 as input, GP7 as output
    generic_i2c_write(addy_write, IODIR, 0b00000001);
    
    while(1){
        // Blink the yellow LED for heartbeat
        NU32DIP_YELLOW = 0;
        delay();
        NU32DIP_YELLOW = 1;
        delay();
        NU32DIP_YELLOW = 0;
        
        // Blink GP7 to check for function
        generic_i2c_write(addy_write, OLAT, 0b10000000);
        delay();
        generic_i2c_write(addy_write, OLAT, 0b00000000);
        delay();
        
    }
}


// delay function for blinking LEDs
void delay(void){
    _CP0_SET_COUNT(0);
    while(_CP0_GET_COUNT()<12000000){}
}


// generic i2c write function that writes to any i2c chip
void generic_i2c_write(unsigned char address, unsigned char SFR, unsigned char value){
    i2c_master_start();
    i2c_master_send(address);
    i2c_master_send(SFR);
    i2c_master_send(value);
    i2c_master_stop();
}