#include "nu32dip.h"
#include "ws2812b.h"

int main(void) {
    // initialize PIC and NeoPixel strip
    NU32DIP_Startup();
    ws2812b_setup();
    
    
    // define char to hold 24 bit message that goes to LED
    int numLED = 5;
    wsColor LED_color[numLED];
    int i[] = {0, 60, 120, 180, 240};
    int sat = 1;
    int bright = 0.5;
    
    while(1){
        for(int x=0; x<numLED; x++){
            if(i[x] >= 360){
                i[x] = 0;
            }
        }
        
        for(int y=0; y<numLED; y++){
            LED_color[y] = HSBtoRGB(i[y], sat, bright);
        }
        
        ws2812b_setColor(LED_color,numLED);
        
        for(int z=0; z<numLED; z++){
            i[z] = i[z] + 1;
        }

        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT()<48000){}
    }
    
}