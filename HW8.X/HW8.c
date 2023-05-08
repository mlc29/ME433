#include <stdio.h>
#include "nu32dip.h"
#include "font.h"
#include "i2c_master_noint.h"
#include "mpu6050.h"
#include "ssd1306.h"

void blink(int iterations, int time_ms);
void drawChar(unsigned char character, unsigned char x, unsigned char y);
void drawMessage(unsigned char *m, unsigned char x, unsigned char y);

int main(void){
    
    // Setup the PIC, MPU, and OLED screen
    NU32DIP_Startup();
    i2c_master_setup();
    ssd1306_setup();
    init_mpu6050();
    
    // message holder
    unsigned char s[62];
    unsigned char message[100];
    
    // variables for acceleration data
    unsigned char d[14];
    float ax, ay, az, gx, gy, gz, T;
    
    // variables for fps calculation
    int t;
    unsigned char fps;
    
    while(1){
        /*
        burst_read_mpu6050(d);  // Read and convert z acceleration from mpu
        az = conv_zXL(d);
        
        _CP0_SET_COUNT(0);      // start timer to find fps
        sprintf(s,"%f",az);
        drawMessage(s,0,0);
        ssd1306_update();
        
        t = _CP0_GET_COUNT();   // get time passed to calculate fps
        t = 24000000/t;
        sprintf(s,"%d FPS",t);
        drawMessage(s,0,20);
        ssd1306_update();
        */
        
        NU32DIP_WriteUART1("Write your message here:\r\n");
        NU32DIP_ReadUART1(s,62);
        NU32DIP_WriteUART1(s);
        NU32DIP_WriteUART1("\r\n");
        
        ssd1306_clear();
        drawMessage(s,0,0);
        ssd1306_update();
        while(_CP0_GET_COUNT()<12000000){}
    }
}


// function to blink the LEDs
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


/* drawChar function draws desired character at specified position
 * 
 * character: the character that should be drawn on screen
 * x: x position on screen
 * y: y position on screen
 */
void drawChar(unsigned char character, unsigned char x, unsigned char y){
    int i,j;
    unsigned char col;
    for (i=0; i<5; i++){
        col = ASCII[character-0x20][i];     // get the ith column of the desired character from ASCII table
        for (j=0; j<8; j++){
            ssd1306_drawPixel(x+i, y+j, (col>>j)&0b1);  // draw individual pixels as on or off based on ASCII table
        }
    }
}


/* drawMessage function writes a full string to the screen starting at the specified position
 * 
 * *m: pointer to a string m
 * x: starting x position
 * y: starting y position
 */
void drawMessage(unsigned char *m, unsigned char x, unsigned char y){
    int k=0;
    while(m[k] != 0){
        if(k<=20){
            drawChar(m[k], x+6*k, y);   // add 6 to x to get a space in between characters
        }
        else if(k>=21 && k<=41){
            drawChar(m[k], x+6*(k-21), y+9);   // move to a new line (y+9) and go back to x=0
        }
        else if(k>=42 && k<=62) {
            drawChar(m[k], x+6*(k-42), y+18);   // move to a new line (y+18) and go back to x=0
        }
        k++;
    }
}