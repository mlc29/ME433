#include "nu32dip.h"
#include "ws2812b.h"

int main(void) {
    // initialize PIC and NeoPixel strip
    NU32DIP_Startup();
    ws2812b_setup();
    
    int numLED = 5;
    // define char to hold 24 bit message that goes to LED
    wsColor LED_color[numLED];
    
    for(int i = 0; i < numLED; i++){
        LED_color[i].r = 0x0F;
        LED_color[i].g = 0x00;
        LED_color[i].b = 0x00;
    }
    LED_color[0].r = 0x00;
    LED_color[0].g = 0x00;
    LED_color[0].b = 0x00;
    ws2812b_setColor(LED_color,numLED);
    
}