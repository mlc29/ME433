#include "nu32dip.h"
#include <stdio.h>
#include <math.h>

int main(void) {
    char message[100];
    int buttonPressed = 0; // flag to indicate if button is pressed
    NU32DIP_Startup();
    while (1) {
        if (!NU32DIP_USER && !buttonPressed) { // check if button is pressed and flag is not set
            buttonPressed = 1; // set buttonPressed flag
            int i;
            for(i = 0; i < 100; i++) {
                float angle = (2.0 * M_PI * i) / 100; // angle in radians
                float value = 1.65 + 1.65 * sin(angle); // generate sine wave from 0 to 3.3 volts
                sprintf(message, "%f\r\n", value);
                NU32DIP_WriteUART1(message);
                _CP0_SET_COUNT(0);
                while(_CP0_GET_COUNT() < 240000) {}
            }
        }
        else if (NU32DIP_USER) { // check if button is released
            buttonPressed = 0; // clear buttonPressed flag
        }
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT() < 2400000) {}
    }
}
