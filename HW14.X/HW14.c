#include "nu32dip.h"


int angle_to_duty(int angle);

int main(void){
    NU32DIP_Startup();  // Initialize PIC
    
    // Initialization of pins for RC servo motor
    T2CONbits.TCKPS = 4;     // Timer2 prescaler N=16 (1:16)
    PR2 = 59999;              // period = (PR2+1) * N * (1/48000000) = 50 Hz
    TMR2 = 0;                // initial TMR2 count is 0
    OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
    OC1CONbits.OCTSEL = 0;   // Use timer2
    //OC1RS = 4500;             // duty cycle = OC1RS/(PR2+1) = 25%
    OC1R = 1500;              // initialize before turning OC1 on; afterward it is read-only
    T2CONbits.ON = 1;        // turn on Timer2
    OC1CONbits.ON = 1;       // turn on OC1
    
    RPB15Rbits.RPB15R = 0b0101; // Set B15 to OC1
    
    while(1){
        _CP0_SET_COUNT(0);
        if(OC1RS == 3000){
            OC1RS = 6000;
        }
        else{
            OC1RS = 3000;
        }
        while(_CP0_GET_COUNT()<96000000){}
        
    }
}


/* NOTES
 Use Timer3 for RC servo at 50Hz
 N=16 so set TCKPS=4
 PR2 = 59999
 0C1R = 4500
 OC1RS = 1500 for 0.5ms pulse (0 degrees)
 OC1RS = 7500 for 2.5ms pulse (180 degrees)
 switch every 4 seconds
 */

