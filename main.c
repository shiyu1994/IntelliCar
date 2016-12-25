//
//  main.c
//  IntelliCar
//
//  Created by Shi Yu on 2016/12/20.
//  Copyright ? 2016ƒÍ Shi Yu. All rights reserved.
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
extern void trigger2(void);
extern void calcDistance(void);

extern unsigned long echoDistance;
extern unsigned int countEcho;
extern unsigned long echoDistance2;
extern unsigned int countEcho2;

#define TURN_TIME  25000
#define RIGHT_TURN_DELAY 18 //右转时间
#define LEFT_TURN_DELAY 20 //左转时间
#define LEFT_TURN_LEFT_SPEED 5  //左转时左轮后退速度
#define LEFT_TURN_RIGHT_SPEED 5 //左转时右轮前进速度
#define RIGHT_TURN_LEFT_SPEED 5 //右转时左轮前进速度
#define RIGHT_TURN_RIGHT_SPEED 5 //右转时右轮后退速度

void delay(unsigned int t) {
	int i = 0, j = 0;
	for(i = 0; i < t; ++i)
		for(j = 0; j < 2000; ++j);
}


void main(void) {
    
	unsigned char state = 0;
	unsigned long lastDistance = 0;
	unsigned char lastTurnLeft = 0;
	unsigned int defaultCount = 0;
	unsigned int stuckDetectionCounter = 0;
	unsigned char trigRight = 0;
   	
    setupTimers();
    
    while(1) {	
				if(countEcho2 >= 100) {
					trigger2();
					calcDistance2();
				}
				if(countEcho >= 200) {
					++stuckDetectionCounter;

					//if(trigRight == 1) {
						trigger();
			        	calcDistance();
					//	trigRight = 0;
					//}
					//else {
				
					//	trigRight = 1;
					//}
					
					countEcho = 0;
					countEcho2 = 0;
						 
			        if(echoDistance2 <= 9) {
			            if(LEFT_LED == 1 && echoDistance >= 15) {
							//if(defaultCount % 2 == 1) {
			                	turnRight(RIGHT_TURN_LEFT_SPEED, RIGHT_TURN_RIGHT_SPEED);
								delay(RIGHT_TURN_DELAY);
							//}
							//else {
								//turnLeft(LEFT_TURN_LEFT_SPEED, LEFT_TURN_RIGHT_SPEED);
								//delay(LEFT_TURN_DELAY);
							//}
							//++defaultCount; 
			            }
			            else if(LEFT_LED == 1 && echoDistance < 15) {
			                turnLeft(LEFT_TURN_LEFT_SPEED, LEFT_TURN_RIGHT_SPEED);
							delay(LEFT_TURN_DELAY);
			            }
			            else if(LEFT_LED == 0 && echoDistance >= 15) {
			                turnRight(RIGHT_TURN_LEFT_SPEED, RIGHT_TURN_RIGHT_SPEED);
							delay(RIGHT_TURN_DELAY);
			            }
			            else {
							while(LEFT_LED == 0 && echoDistance < 15) {
			                	goBackward(2);
							}
							if(LEFT_LED == 1 && echoDistance < 15) {
								turnLeft(LEFT_TURN_LEFT_SPEED, LEFT_TURN_RIGHT_SPEED);
								delay(LEFT_TURN_DELAY);
							}
							else if(LEFT_LED == 0 && echoDistance >= 15) {
								turnRight(RIGHT_TURN_LEFT_SPEED, RIGHT_TURN_RIGHT_SPEED);
								delay(RIGHT_TURN_DELAY);
							}
							else if(LEFT_LED == 1 && echoDistance >= 15) {
								if(defaultCount % 2 == 0) {
				                	turnRight(RIGHT_TURN_LEFT_SPEED, RIGHT_TURN_RIGHT_SPEED);
									delay(RIGHT_TURN_DELAY);
								}
								else {
									turnLeft(LEFT_TURN_LEFT_SPEED, LEFT_TURN_RIGHT_SPEED);
									delay(LEFT_TURN_DELAY);
								}
								++defaultCount;
							}
			            }
			        }
					else {
						if(echoDistance < 5) {
							goLeft(5);
						}
						else if(echoDistance >= 10 && echoDistance <= 15) { 
							goRight(5); 
						}
						else {
			            	goForward(2);
						}
					}
					/*if(stuckDetectionCounter == 50) {
						if(lastDistance == echoDistance) {
							if(!lastTurnLeft) {
								turnLeft(LEFT_TURN_LEFT_SPEED, LEFT_TURN_RIGHT_SPEED);
								delay(10);
								lastTurnLeft = 1;
							}			
							else {
								turnRight(RIGHT_TURN_LEFT_SPEED, RIGHT_TURN_RIGHT_SPEED);
								delay(10);
								lastTurnLeft = 0;
							}
						}
						lastDistance = echoDistance;	
						stuckDetectionCounter = 0;	
					}*/
			    }
			}
		
    
}

/*void main(void) {
    
	unsigned char state = 0;
	unsigned long lastDistance = 0;
	unsigned char lastTurnLeft = 0;
	unsigned int defaultCount = 0;
	unsigned int stuckDetectionCounter = 0;
   	
    setupTimers();
    
    while(1) {	
				if(countEcho >= 1000) {
					++countEcho;
					++stuckDetectionCounter;
					trigger();
			        calcDistance();		 
			        if(echoDistance <= 6) {
			            if(LEFT_LED == 1 && RIGHT_LED == 1) {
							if(defaultCount % 2 == 0) {
			                	turnRight(RIGHT_TURN_LEFT_SPEED, RIGHT_TURN_RIGHT_SPEED);
								delay(RIGHT_TURN_DELAY);
							}
							else {
								turnLeft(LEFT_TURN_LEFT_SPEED, LEFT_TURN_RIGHT_SPEED);
								delay(LEFT_TURN_DELAY);
							}
							++defaultCount; 
			            }
			            else if(LEFT_LED == 1 && RIGHT_LED == 0) {
			                turnLeft(LEFT_TURN_LEFT_SPEED, LEFT_TURN_RIGHT_SPEED);
							delay(LEFT_TURN_DELAY);
			            }
			            else if(LEFT_LED == 0 && RIGHT_LED == 1) {
			                turnRight(RIGHT_TURN_LEFT_SPEED, RIGHT_TURN_RIGHT_SPEED);
							delay(RIGHT_TURN_DELAY);
			            }
			            else {
							while(LEFT_LED == 0 && RIGHT_LED == 0) {
			                	goBackward(2);
							}
							if(LEFT_LED == 1 && RIGHT_LED == 0) {
								turnLeft(LEFT_TURN_LEFT_SPEED, LEFT_TURN_RIGHT_SPEED);
								delay(LEFT_TURN_DELAY);
							}
							else if(LEFT_LED == 0 && RIGHT_LED == 1) {
								turnRight(RIGHT_TURN_LEFT_SPEED, RIGHT_TURN_RIGHT_SPEED);
								delay(RIGHT_TURN_DELAY);
							}
							else if(LEFT_LED == 1 && RIGHT_LED == 1) {
								if(defaultCount % 2 == 0) {
				                	turnRight(RIGHT_TURN_LEFT_SPEED, RIGHT_TURN_RIGHT_SPEED);
									delay(RIGHT_TURN_DELAY);
								}
								else {
									turnLeft(LEFT_TURN_LEFT_SPEED, LEFT_TURN_RIGHT_SPEED);
									delay(LEFT_TURN_DELAY);
								}
								++defaultCount;
							}
			            }
			        }
					else {
			            goForward(2);
					}
					if(stuckDetectionCounter == 50) {
						if(lastDistance == echoDistance) {
							if(!lastTurnLeft) {
								turnLeft(LEFT_TURN_LEFT_SPEED, LEFT_TURN_RIGHT_SPEED);
								delay(10);
								lastTurnLeft = 1;
							}			
							else {
								turnRight(RIGHT_TURN_LEFT_SPEED, RIGHT_TURN_RIGHT_SPEED);
								delay(10);
								lastTurnLeft = 0;
							}
						}
						lastDistance = echoDistance;	
						stuckDetectionCounter = 0;	
					}
			    }
			}
		
    
}*/
