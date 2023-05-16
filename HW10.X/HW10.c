#include "nu32dip.h"
#include "ws2812b.h"

#define LEDMAX 8    // Maximum number of LEDs possible

void clear_LEDs(wsColor color[]);

int main(void) {
    // initialize PIC and NeoPixel strip
    NU32DIP_Startup();
    ws2812b_setup();
    
    // number of LEDs being used
    int numLED = 5;
    
    // define variables for LED coloring
    wsColor LED_color[numLED];  // struct for LED coloring
    float sat = 1.0;            // sat is the saturation level, from 0 to 1, where 1 is full color and 0 is gray
    float bright = 0.5;         // bright sets the maximum brightness, from 0 to 1
    
    clear_LEDs(LED_color);   // clears the LEDs so that if the number used is less than before,
                            // the extra LEDs do not stay on
    
    // hue: array to hold hue(color) values for each LED from 0-360
    // initialized to start each LED at an evenly spaced color
    int hueMIN = 0;
    int hueMAX = 360;
    int hue[numLED];
    for(int i=0; i<numLED; i++){
        hue[i] = hueMIN + i*(hueMAX/(4*numLED));
    }
    
    int change[numLED];
    for(int j=0; j<numLED; j++){
        change[j] = 1;
    }
    
    while(1){
        
        // sets the color for each LED
        for(int x=0; x<numLED; x++){
            LED_color[x] = HSBtoRGB(hue[x],sat,bright);
        }
        
        ws2812b_setColor(LED_color,numLED);     // sends the color values to the LEDs
        
        // increments the hues of each LED by 1 or resets the hue if it reaches the max value
        for(int z=0; z<numLED; z++){
            if(hue[z] < hueMAX){
                hue[z] = hue[z] + 1;
            }
            else{
                hue[z] = hueMIN;
            }
        }
        
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT()<480000){}     // delay for visual effects
    }
    
}

/* clear_LED function turns off all the LEDs
 * 
 * wsColor color[]: struct that holds the values for each LED color
 */
void clear_LEDs(wsColor color[]){
    for(int k=0; k<LEDMAX; k++){
        color[k] = HSBtoRGB(0,0.0,0.0);     // set hue, sat, and bright to 0 for each LED
    }
    ws2812b_setColor(color,LEDMAX);     // send the 0 values to the LEDs
}