#include <stdio.h>
#include "nu32dip.h"
#include "font.h"
#include "i2c_master_noint.h"
#include "mpu6050.h"
#include "ssd1306.h"

void blink(int iterations, int time_ms);
void drawChar(char character, char x, char y);


int main(void){
    
    // Setup the PIC and OLED screen
    NU32DIP_Startup();
    i2c_master_setup();
    ssd1306_setup();
    char m[100];
    
    while(1){
        _CP0_SET_COUNT(0);
        blink(1,50);         // Blink LEDs for heartbeat
        
        sprintf(m,"Hello World!");
        drawChar(m[0],0,0);
        drawChar(m[1],6,0);
        drawChar(m[2],12,0);
        drawChar(m[3],18,0);
        drawChar(m[4],24,0);
        drawChar(m[5],30,0);
        drawChar(m[6],36,0);
        drawChar(m[7],42,0);
        drawChar(m[8],48,0);
        drawChar(m[9],54,0);
        drawChar(m[10],60,0);
        drawChar(m[11],66,0);
        ssd1306_update();
        
        
        
        
        while(_CP0_GET_COUNT()<48000000){}
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
void drawChar(char character, char x, char y){
    int i,j;
    unsigned char col;
    for (i=0; i<5; i++){
        col = ASCII[character-0x20][i];
        for (j=0; j<8; j++){
            ssd1306_drawPixel(x+i, y+j, (col>>j)&0b1);
        }
    }
}
