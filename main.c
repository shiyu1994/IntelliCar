//
//  main.c
//  IntelliCar
//
//  Created by Shi Yu on 2016/12/20.
//  Copyright ? 2016Äê Shi Yu. All rights reserved.
//

#include <at89x52.h>
#include "car.h"
#include "timers.h"
#include "echo.h"

extern void turnLeft(unsigned int ls, unsigned int rs);
extern void turnRight(unsigned int ls, unsigned int rs);
extern void goForward(unsigned int s);
extern void goBackward(unsigned int s);

extern void setupTimers(void);
extern void trigger(void);
extern void calcDistance(void);

extern unsigned long echoDistance;
extern unsigned int countEcho;

#define TURN_TIME  25000

void delay(unsigned int t) {
	int i = 0, j = 0;
	for(i = 0; i < t; ++i)
		for(j = 0; j < 2000; ++j);
}

void main(void) {
    
	unsigned char state = 0;
	unsigned int turnCounter = TURN_TIME;
	unsigned long lastDistance = 0;
	unsigned int defaultCount = 0;
   	
    setupTimers();
    
    while(1) {
			
			//if(state == 0) {	
				if(countEcho >= 1000) {
					//countEcho = 0;
					trigger();
			        calcDistance();		 
			        if(echoDistance <= 6) {
			            if(LEFT_LED == 1 && RIGHT_LED == 1) {
							if(defaultCount % 2 == 0) {
			                	turnRight(5, 5);
								delay(28);
							}
							else {
								turnLeft(5, 5);
								delay(30);
							} 
							++defaultCount;
			            }
			            else if(LEFT_LED == 1 && RIGHT_LED == 0) {
							//turnCounter = TURN_TIME;
							//state = 1;
			                turnLeft(5, 5);
							delay(30);
			            }
			            else if(LEFT_LED == 0 && RIGHT_LED == 1) {
							//turnCounter = TURN_TIME;
							//state = 1;
			                turnRight(5, 5);
							delay(28);
							/*if(rightCount > 0) {
								++rightCount;
							}*/
			            }
			            else {
							//turnCounter = TURN_TIME;
							//state = 1;
							while(LEFT_LED == 0 && RIGHT_LED == 0) {
			                	goBackward(2);
							}
			            }
			        }
					else {
						/*if(LEFT_LED == 1 && RIGHT_LED == 0) {
							turnLeft(5, 5);
							delay(2);
						}
						else if(LEFT_LED == 0 && RIGHT_LED == 1) {
							turnRight(5, 5);
							delay(2);
						}
						else {*/
			            	goForward(2);
						//}
					}
			        //else {
					/*	if(lastDistance == echoDistance)	{
							if(LEFT_LED == 1 && RIGHT_LED == 0) {
								turnLeft(5, 5);
							}
							else if(LEFT_LED == 0 && RIGHT_LED == 1) {
								turnRight(5, 5);
							}	
							else if(LEFT_LED == 0 && RIGHT_LED == 0) {
								goBackward(2);
							}
							else {
								goForward(2);
							}
						}
						else {
							goForward(2);
						}*/
			        }
					lastDistance = echoDistance;
				}
			/*}
			else if(state == 1) {
				if(LEFT_LED == 0 && RIGHT_LED == 0) {
					goBackward(3);
				}
				else if(LEFT_LED == 1 && RIGHT_LED == 0) {
			        turnLeft(5, 5);
			    }
			    else if(LEFT_LED == 0 && RIGHT_LED == 1) {
			        turnRight(5, 5);
			    }
				--turnCounter;
				if(turnCounter == 0) {
					state = 0;
				}
			}*/
		
    
}
