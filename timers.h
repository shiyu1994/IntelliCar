//
//  timers.h
//  IntelliCar
//
//  Created by Shi Yu on 2016/12/20.
//  Copyright ? 2016Äê Shi Yu. All rights reserved.
//

#ifndef timers_h
#define timers_h

#include "at89x52.h"
#include "display.h"
#include <intrins.h>

extern void setupTimers(void);
extern void trigger(void);
void setupTimers(void);

unsigned int countDisplay = 0;
unsigned int countEcho = 0;
unsigned int countPWM = 0;

unsigned int leftPWM = 0, rightPWM = 0;

void setupTimers(void) {
    TMOD = 0x11;
    
    TH1 = (65536 - 100) / 256;
    TL1 = (65536 - 100) % 256;
    
    TH0 = 0;
    TL0 = 0;
    
    TR1 = 1;

	ET0 = 1;
    ET1 = 1;
	EA = 1;
}

void timer1Handler() interrupt 3 using 2 { 
    TH1 = (65536 - 100) / 256;
    TL1 = (65536 - 100) % 256;

	++countEcho;
	++countDisplay;
	++countPWM;
    
    if(countDisplay >= 20) {
		countDisplay = 0;
        //display();
    }						

    if(countPWM >= 10) {
		countPWM = 0;
		pwmOutput();
        leftPWM = (leftPWM + 1) % 10;
        rightPWM = (rightPWM + 1) % 10;
    }

	/*if(countEcho >= 1000) {
		countEcho = 0;
		trigger();
		calcDistance();		
	}*/
    
}

void timer0Handler() interrupt 1 using 0 {
    
} 

#endif /* timers_h */
