#include "nu32dip.h"
#include "ws2812b.h"

#define LEDMAX 8    // Maximum number of LEDs possible

void clear_LED(wsColor color[]);

int main(void) {
    // initialize PIC and NeoPixel strip
    NU32DIP_Startup();
    ws2812b_setup();
    
    // number of LEDs being used
    int numLED = 8;
    
    // define variables for LED coloring
    wsColor LED_color[numLED];  // struct for LED coloring
    float sat = 1.0;            // sat is the saturation level, from 0 to 1, where 1 is full color and 0 is gray
    float bright = 0.5;         // bright sets the maximum brightness, from 0 to 1
    
    clear_LED(LED_color);   // clears the LEDs so that if the number used is less than before,
                            // the extra LEDs do not stay on
    
    // hue: array to hold hue(color) values for each LED from 0-360
    // initialized to start each LED at an evenly spaced color
    int hue[numLED];
    for(int j=0; j<numLED; j++){
        hue[j] = j*(360/numLED);
    }
    
    
    while(1){
        
        // this loop checks to see in any hue values are at the max and resets them if they are
        for(int x=0; x<numLED; x++){
            if(hue[x] >= 360){
                hue[x] = 0;
            }
        }
        
        // sets the color for each LED
        for(int y=0; y<numLED; y++){
            LED_color[y] = HSBtoRGB(hue[y],sat,bright);
        }
        
        ws2812b_setColor(LED_color,numLED);     // sends the color values to the LEDs
        
        // increments the hues of each LED by 1
        for(int z=0; z<numLED; z++){
            hue[z] = hue[z] + 1;
        }
        
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT()<120000){}     // delay for visual effects
    }
    
}

/* clear_LED function turns off all the LEDs
 * 
 * wsColor color[]: struct that holds the values for each LED color
 */
void clear_LED(wsColor color[]){
    for(int k=0; k<LEDMAX; k++){
        color[k] = HSBtoRGB(0,0.0,0.0);     // set hue, sat, and bright to 0 for each LED
    }
    ws2812b_setColor(color,LEDMAX);     // send the 0 values to the LEDs
}