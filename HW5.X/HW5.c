#include "nu32dip.h"
#include "spi.h"
#include <math.h>

int set_voltage(unsigned int x, unsigned char a_or_b, unsigned short z);

int main(void) {
    unsigned int t = 0;     // counter variable
    unsigned short s = 0;   // variable to hold SPI communication bits
    unsigned char a = 0b0;  // char for channel a
    unsigned char b = 0b1;  // char for channel b
    
    NU32DIP_Startup();      // call NU32 startup function
    initSPI();              // call SPI startup function
    while(1) {
        
        set_voltage(t,a,s);         // send sine wave voltage
        t = set_voltage(t,b,s);     // send triangle wave voltage
        t++;                        // increment the counter
        
        _CP0_SET_COUNT(0);                  // delay 5 ms
        while(_CP0_GET_COUNT()<120000){}
    }
}

/* FUNCTOIN TO CALCULATE AND SEND 10-BIT VOLTAGE TO SPI DAC
 * 
 * unsigned int x relates to the counter variable
 * unsigned char a_or_b is which channel the function will speak to
 * unsigned short z is the holder for the SPI communication bits
*/
int set_voltage(unsigned int x, unsigned char a_or_b, unsigned short z) {
    
    float y = 0;            // holds the float value of the calculated voltage
    unsigned int v = 0;     // holds the int value of the calculated voltage to send via SPI
    int dy = 1;             // controls the slope of the triangle wave
    
    if(a_or_b == 0b0) {                     // Statement that calculates sine wave voltage for channel a
      y = 511.0*sin(2.0*M_PI*x/100)+512.0;  // calculates the 2Hz sine wave value as a float
    }
    
    if(a_or_b == 0b1) {         // Statement that calculates tri wave voltage for channel b
        
        if (x >= 101){          // if the counter is at or above halfway, make the slope negative
            dy = -1;
        } 
        
        if (dy == 1){           // calculate the tri wave voltage for a positive slope
            y = y + (1023/100)*x;
        }
        
        if (dy == -1){          // calculate the tri wave voltage for a negative slope
            y = 1023 - (1023/100)*(x-99);
            
            if (x == 199){      // if the counter reaches the end of the period,set the counter to 0
                x = 0;
            }
        }
    }
    
    v = y;              // change the voltage value from float to int
    z = 0b111<<12;      // initialization bits
    z = z|(a_or_b<<15); // speak to channel a or b
    z = z|(v<<2);       // add the 10 bit voltage
    
    LATAbits.LATA3 = 0; // set chip select low to send bits
    spi_io(z>>8);       // send first 8 bits, then second 8 bits
    spi_io(z);
    LATAbits.LATA3 = 1; // set chip select high to stop  
    
    return x;   // return value of x to counter
}