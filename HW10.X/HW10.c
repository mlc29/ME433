#include "nu32dip.h"
#include "ws2812b.h"

int main(void) {
    // initialize PIC and NeoPixel strip
    NU32DIP_Startup();
    ws2812b_setup();
    
    //int numLED = 1;
    // define char to hold 24 bit message that goes to LED
    wsColor LED_color[5];
    
    for(int i = 0; i < 5; i++){
        LED_color[i].r = 0xFF;
        LED_color[i].g = 0x00;
        LED_color[i].b = 0x00;
    }
    while(1){
        ws2812b_setColor(LED_color,5);
    }
}