/**************************************************************
                        PIDs

PID Methods for autonomous movement

Created 8/18/23
Last update 8/18/23

****************************************************************/
#include "main.h"

using namespace pros;

double mathPI = 3.141519;

double kP;
double kI;
double kD;

void setConstants(string mode) {
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

int m;
int t;

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


void movePID(double distance) 
{
    //Set PID constants to move mode
    setConstants("move");
    
    setpointDistance = distance;
    prevError = 0;
    m = 1;
    while (m == 1) {
        // Find currentPosition
        currentPosition += ( ((ML.get_position() + MR.get_position()) / 2) * (mathPI / 180 ) / driveWheelRadius);
        
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
        ML.tare_position();
        MR.tare_position();

        // Apply motorPower
        setDriveSpeed(motorPower);
        
        // Don't clog CPU
        pros::delay(30);
        
        // Exit conditions
        if (error <= 0.1 && derivative <= 0.1) {
            m = 0;
        }
    }
    currentPosition = 0;
}

void turnPID(double angle) 
{
    //Set PID constants to turn mode
    setConstants("turn");
    t = 1;
    
    setpointAngle = angle;
    prevError = 0;

    while (t == 1) {
        // Find currentAngle
        currentAngle += ((ML.get_position() - MR.get_position()) / widthBetweenMiddleWheels);
        
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
        ML.tare_position();
        MR.tare_position();
        
        // Apply motorPower
        setDriveSpeed(-motorPower, "Left");
        setDriveSpeed(motorPower, "Right");
        
        // Don't clog CPU
        pros::delay(30);
        
        // Exit conditions
        if (error <= 0.1 && derivative <= 0.1) {
            t = 0;
        }
    }
    currentAngle = 0;
}
