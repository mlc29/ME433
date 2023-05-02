#include <stdio.h>
#include "nu32dip.h"
#include "i2c_master_noint.h"

unsigned char addy = 0b01000000;
unsigned char IODIR = 0x00;
unsigned char GPIO = 0x09;
unsigned char OLAT = 0x0A;

void delay();
void gen_i2c_write(unsigned char address, unsigned char SFR, unsigned char value);
int gen_i2c_read(unsigned char address, unsigned char SFR);

int main(void) {
    int r;
    
    NU32DIP_Startup();
    
    // Init I2C pins B8(SCL) and B9(SDA)
    i2c_master_setup();
    
    // Init the chip, GP0 as input, GP7 as output
    gen_i2c_write(addy, IODIR, 0b00000001);
    
    while(1){
        // Blink the yellow LED for heartbeat
        NU32DIP_YELLOW = 0;
        delay();
        NU32DIP_YELLOW = 1;
        delay();
        NU32DIP_YELLOW = 0;
        
        // read the value of GP0
        r = gen_i2c_read(addy, GPIO);
        if(!r){
            gen_i2c_write(addy, OLAT, 0b10000000);
        } else{
            gen_i2c_write(addy, OLAT, 0b00000000);
        }
    }
}


// delay function for blinking LEDs
void delay(void){
    _CP0_SET_COUNT(0);
    while(_CP0_GET_COUNT()<4800000){}
}


/* Generic I2C write function that writes to any I2C chip
 * 
 * address: the address of the desired I2C chip
 * SFR: the register which you want to write to
 * value: the 8-bit value you want to send to the SFR
 */
void gen_i2c_write(unsigned char address, unsigned char SFR, unsigned char value){
    i2c_master_start();
    i2c_master_send(address);
    i2c_master_send(SFR);
    i2c_master_send(value);
    i2c_master_stop();
}


/* Generic I2C read function that reads from the specified I2c chip
 * 
 * Currently the function is reading from GP0 only
 * 
 * address: the address of the desired I2C chip
 * SFR: the register you want to read from
 */
int gen_i2c_read(unsigned char address, unsigned char SFR){
    i2c_master_start();
    i2c_master_send(address);
    i2c_master_send(SFR);
    i2c_master_restart();
    
    i2c_master_send(address|0b1);       // address|0b1 sends the read byte instead of the write byte
    unsigned char r = i2c_master_recv();
    i2c_master_ack(1);
    i2c_master_stop();
    
    return (r&0b00000001);  // r&0b00000001 sends a 1 if GP0 is high and 0 if GP0 is low
}