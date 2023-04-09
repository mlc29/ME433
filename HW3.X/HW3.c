#include "nu32dip.h"

int main(void) {
    char message[100];
    
    NU32DIP_Startup();
    while (1) {
        int i = 0;
        for(i=0; i<100; i++) {
            sprintf(message, "%f\r\n", i*3.3/100.0);
            NU32DIP_WriteUART1(message);
            _CP0_SET_COUNT(0);
            while(_CP0_GET_COUNT() < 24000){}
        }
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT() < 24000000*5) {}
    }
}
