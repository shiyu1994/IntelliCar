														 //
//  display.h
//  IntelliCar
//
//  Created by Shi Yu on 2016/12/20.
//  Copyright ? 2016Äê Shi Yu. All rights reserved.
//

#ifndef display_h
#define display_h

#include "at89x52.h"
#include "echo.h"

unsigned char displayBuffer[4];
unsigned char const displayCode[12] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xBF, 0xff};
int displayPosition = 0;
extern unsigned long echoDistance;

void display(void);

void display(void) {
    
	/*displayBuffer[0] = echoDistance % 1000 / 100;
    displayBuffer[1] = echoDistance % 1000 % 100 / 10;
    displayBuffer[2] = echoDistance % 1000 % 100 % 10;*/

    if(displayPosition == 0) {
        P0 = displayCode[displayBuffer[0]] & 0x7f;
    }
    else {
        P0 = displayCode[displayBuffer[displayPosition]]; 
    }
    
    if(displayPosition == 2) {
        P2_1 = 1;
        P2_2 = 1;
        P2_3 = 0;
    }
    else if(displayPosition == 1) {
        P2_1 = 1;
        P2_2 = 0;
        P2_3 = 1;
    }
    else if(displayPosition == 0) {
        P2_1 = 0;
        P2_2 = 1;
        P2_3 = 1;
    }
    
    displayPosition = (displayPosition + 1) % 3;
}

#endif /* display_h */
