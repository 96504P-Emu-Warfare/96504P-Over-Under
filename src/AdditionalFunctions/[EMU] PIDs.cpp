/**************************************************************
                        PIDs

PID Methods for autonomous movement

Created 8/18/23
Last update 8/18/23

****************************************************************/
#include "main.h"

double M_PI = 3.14159265358979323846;

double kP;
double kI;
double kD;

int setConstants(string mode) {
    if (mode == "move") {
        kP = 1;
        kI = 1;
        kD = 1;
    }
    if  (mode == "turn") {
        kP = 1;
        kI = 1;
        kD = 1;
    }
    else {
        std::cout << "Error: Constants are not set properly";
    }
}

double pPowerThreshold = 0.85;

double currentPosition;
double setpointDistance;
double currentAngle;
double setpointAngle;

double error;
double proportional;
double integral;
double derivative;
double prevError;
double motorPower;

int m;
int t;

void movePID(double distance) {
    //Set PID constants to move mode
    setConstants("move");
    
    setpointDistance = distance;
    
    while (m == 1) {
        // Find currentPosition
        currentPosition += ( ((RotationL.get_position() + RotationL.get_position()) / 2) * (M_PI / 180 ) / trackingWheelRadius);
        
        // Find error
        error = setpointDistance - currentPosition;
        
        // Find P,I and D
        proportional = ( error / setpointDistance ) * pPowerThreshold;
        integral += error;
        derivative =  error - prevError;
        
        // Motor power output
        motorPower =  kP*proportional + kI*integral + kD*derivative;
        
        // Set up for next loop
        prevError = error;
        RotationL.reset_position();
        RotationR.reset_position();

        // Apply motorPower
        setDriveSpeed(motorPower);
        
        // Don't clog CPU
        delay(50);
        
        // Exit conditions
        if (error <= 0.1 && derivative <= 0.1) {
            m = 1;
        }
    }
    currentPosition = 0;
    return;
}

void turnPID(double angle) {
    //Set PID constants to turn mode
    setConstants("turn");
    
    setpointAngle = angle;
    while (t == 1) {
        // Find currentAngle
        currentAngle += ((RotationL.get_position() - RotationL.get_position()) / trackingWheelWidth);
        
        // Find error
        error = setpointAngle - currentAngle;
        
        // Find P,I and D
        proportional = ( error / setpointAngle ) * pPowerThreshold;
        integral += error;
        derivative =  error - prevError;
        
        // Motor power output
        motorPower =  kP*proportional + kI*integral + kD*derivative;
        
        // Set up for next loop
        prevError = error;
        RotationL.reset_position();
        RotationR.reset_position();
        
        // Apply motorPower
        setDriveSpeed(motorPower);
        
        // Don't clog CPU
        delay(50);
        
        // Exit conditions
        if (error <= 0.1 && derivative <= 0.1) {
            m = 1;
        }
    }
    currentAngle = 0;
    return;
}
