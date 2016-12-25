//
//  car.h
//  IntelliCar
//
//  Created by Shi Yu on 2016/12/20.
//  Copyright ? 2016Äê Shi Yu. All rights reserved.
//

#ifndef car_h
#define car_h

#define LEFT_LED P3_7
#define RIGHT_LED P3_4

#define TRIG P2_5
#define ECHO P2_4

#define LEFT_FRONT_PWM P1_1
#define LEFT_BACK_PWM P1_3
#define RIGHT_FRONT_PWM P1_5
#define RIGHT_BACK_PWM P1_7

#define LEFT_FRONT_MOTOR_FORWARD P1_4
#define LEFT_BACK_MOTOR_FORWARD P1_6
#define RIGHT_FRONT_MOTOR_FORWARD P1_0
#define RIGHT_BACK_MOTOR_FORWARD P1_2

#define LEFT_FRONT_MOTOR_BACKWARD P0_5
#define LEFT_BACK_MOTOR_BACKWARD P0_7
#define RIGHT_FRONT_MOTOR_BACKWARD P0_1
#define RIGHT_BACK_MOTOR_BACKWARD P0_3

unsigned int leftSpeed, rightSpeed;
extern unsigned int leftPWM, rightPWM;

void turnLeft(unsigned int ls, unsigned int rs);
void turnRight(unsigned int ls, unsigned int rs);
void leftMotorBackward(void);
void rightMotorBackward(void);
void turnLeft(unsigned int ls, unsigned int rs);
void turnRight(unsigned int ls, unsigned int rs);
void goForward(unsigned int s);
void goBackward(unsigned int s);
void pwmOutput(void);

void leftMotorBackward(void) {
    LEFT_FRONT_MOTOR_FORWARD = 0;
    LEFT_BACK_MOTOR_FORWARD = 0;
    LEFT_FRONT_MOTOR_BACKWARD = 1;
    LEFT_BACK_MOTOR_BACKWARD = 1;
}

void rightMotorBackward(void) {
    RIGHT_FRONT_MOTOR_FORWARD = 0;
    RIGHT_BACK_MOTOR_FORWARD = 0;
    RIGHT_FRONT_MOTOR_BACKWARD = 1;
    RIGHT_BACK_MOTOR_BACKWARD = 1;
}

void leftMotorForward(void) {
    LEFT_FRONT_MOTOR_FORWARD = 1;
    LEFT_BACK_MOTOR_FORWARD = 1;
    LEFT_FRONT_MOTOR_BACKWARD = 0;
    LEFT_BACK_MOTOR_BACKWARD = 0;
}

void rightMotorForward(void) {
    RIGHT_FRONT_MOTOR_FORWARD = 1;
    RIGHT_BACK_MOTOR_FORWARD = 1;
    RIGHT_FRONT_MOTOR_BACKWARD = 0;
    RIGHT_BACK_MOTOR_BACKWARD = 0;
}

void leftMotorStop(void) {
    LEFT_FRONT_MOTOR_FORWARD = 0;
    LEFT_BACK_MOTOR_FORWARD = 0;
	LEFT_FRONT_MOTOR_BACKWARD = 0;
	LEFT_BACK_MOTOR_BACKWARD = 0;
}

void rightMotorStop(void) {
    RIGHT_FRONT_MOTOR_FORWARD = 0;
    RIGHT_BACK_MOTOR_FORWARD = 0;
    RIGHT_FRONT_MOTOR_BACKWARD = 0;
    RIGHT_BACK_MOTOR_BACKWARD = 0;
}

void turnLeft(unsigned int ls, unsigned int rs) {
    leftSpeed = ls;
    rightSpeed = rs;
    rightMotorForward();
    leftMotorBackward();
}

void turnRight(unsigned int ls, unsigned int rs) {
    leftSpeed = ls;
    rightSpeed = rs;
    rightMotorBackward();
    leftMotorForward();
}

void goRight(unsigned int s) {
	leftSpeed = s;
	leftMotorForward();
	rightMotorStop();
}

void goLeft(unsigned int s) {
	rightSpeed = s;
	leftMotorStop();
	rightMotorForward();
}

void goForward(unsigned int s) {
    leftSpeed = s;
    rightSpeed = s;
    leftMotorForward();
    rightMotorForward();
}

void goBackward(unsigned int s) {
    leftSpeed = s;
    rightSpeed = s;
    leftMotorBackward();
    rightMotorBackward();
}

void pwmOutput(void) {
    if(leftPWM <= leftSpeed) {
        LEFT_FRONT_PWM = 1;
        LEFT_BACK_PWM = 1;
    }
    else {
        LEFT_FRONT_PWM = 0;
        LEFT_BACK_PWM = 0;
    }
    
    if(rightPWM <= rightSpeed) {
        RIGHT_FRONT_PWM = 1;
        RIGHT_BACK_PWM = 1;
    }
    else {
        RIGHT_FRONT_PWM = 0;
        RIGHT_BACK_PWM = 0;
    }
}

#endif /* car_h */
