											   //
//  echo.h
//  IntelliCar
//
//  Created by Shi Yu on 2016/12/20.
//  Copyright ? 2016Äê Shi Yu. All rights reserved.
//

#ifndef echo_h
#define echo_h

#include "intrins.h"
#include "at89x52.h"
#include "display.h"

#define TRIG P2_5
#define ECHO P2_4

unsigned long echoDistance = 333;
unsigned int time;
extern unsigned char displayBuffer[];

void trigger(void);
void calcDistance(void);

void trigger(void) {
    TRIG = 1;
    _nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_();
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_();
    TRIG = 0;
}

void calcDistance(void) {
    while(!ECHO);
    TR0 = 1;	   
    while(ECHO);
    TR0 = 0;
    
    time = TH0 * 256 + TL0;

	TH0 = 0;
    TL0 = 0;
    
    echoDistance = time * 1.7 / 100;

	displayBuffer[0] = echoDistance % 1000 / 100;
    displayBuffer[1] = echoDistance % 1000 % 100 / 10;
    displayBuffer[2] = echoDistance % 1000 % 100 % 10;
}

#endif /* echo_h */
