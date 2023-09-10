/**************************************************************
                        PIDs

PID Methods for autonomous movement

Created 8/18/23
Last update 9/7/23

****************************************************************/
#include "main.h"

using namespace pros;

double mathPI = 3.141519;
sensorTL PIDlayer(void);
PIDlayer.updateTL();

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
double prevMotorPower;

double slew(double curr, double prev) {
    // Slew rate should be 1 / the amt of cycles of the loop you want it to take to reach full speed from 0
    double slewRate = 0.05;
    if (curr > prev + slewRate ) {
        curr = prev + slewRate;
    }
    if (curr < prev - slewRate) {
        curr = prev - slewRate;
    }
    return curr;
}

double overvoltProtection(double curr) {
    if (curr > 1) {
        curr = 1;
    }
    if (curr < 0) {
        curr = 0;
    }
    return curr;
}

void moveP(double distance) {
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
        //chassis.setDriveSpeed(motorPower + motorPower * leftCorrection(), "Left");
        //chassis.setDriveSpeed(motorPower + motorPower * rightCorrection(), "Right");

        chassis.setDriveSpeed(motorPower , "Left");
        chassis.setDriveSpeed(motorPower , "Right");
        
        // Don't clog CPU
        pros::delay(30);
        
        // Exit conditions (NEED TO BE TUNED)
        if (error <= 0.1 && derivative <= 0.1) {
            m = 0;
        }
    }
    currentPosition = 0;
}

void turnP(double angle) {
    //Set PID constants to turn mode
    setConstants("turn");
    t = 1;
    
    setpointAngle = angle;
    prevError = 0;

    double getCurrentAngle();
        if (inertialSensor) {
            currentAngle = (Inr.get_rotation());
        }
        else {
            currentAngle += ((ML.get_position() - MR.get_position()) / widthBetweenMiddleWheels);
        }

        
    currentAngle = 0;
    
    if (inertialSensor) {
        Inr.set_rotation(0);
    }

    while (t == 1) {
        // Find currentAngle
        currentAngle = getCurrentAngle();
        
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
        if (inertialSensor == false) {
            ML.tare_position();
            MR.tare_position();
        }
        else Inr.set_rotation(0);

        // Slewing
        motorPower = slew(motorPower, prevMotorPower);

        // Overvolt protection
        motorPower = overvoltProtection(motorPower);

        // Apply motorPower
        chassis.setDriveSpeed(-motorPower, "Left");
        chassis.setDriveSpeed(motorPower, "Right");
        
        // Don't clog CPU
        pros::delay(30);
        
        // Exit conditions (NEED TUNING)
        if (error <= 0.1 && derivative <= 0.1) {
            t = 0;
        }
    }
    // Set up for next call
    prevMotorPower = motorPower;
}