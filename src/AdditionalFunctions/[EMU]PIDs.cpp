/**************************************************************
                        PIDs

PID Methods for autonomous movement

Created 8/18/23
Last update 9/7/23

****************************************************************/
#include "main.h"

using namespace pros;

double mathPI = 3.141519;
sensorTL PIDlayer;

double kP;
double kI;
double kD;

void setConstants(string mode) {
    if (mode == "move") {
        kP = .4;
        kI = .0;
        kD = .0;
    }
    if  (mode == "turn") {
        kP = .4;
        kI = .0;
        kD = .0;
    }
    else {
        std::cout << "Error: Constants are not set properly";
    }
}

int m;
int t;

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
    
    setpointDistance = distance / 100 ;
    currentPosition = 0;
    prevError = 0;
    m = 1;
    Controller1.clear();
    ML.tare_position();
    MR.tare_position();
    
    while (m == 1) {
        // Find currentPosition
        currentPosition = ( ((ML.get_position() + MR.get_position()) / 2) * (mathPI / 180 ) * driveWheelRadius);
        
        // Find error
        error = setpointDistance - currentPosition;
        
        // Find P,I and D
        proportional = ( error / setpointDistance );
        integral += error;
        derivative =  error - prevError;
        
        // Motor power output
        motorPower =  kP*proportional + kI*integral + kD*derivative;
        
        // Set up for next loop
        prevError = error;

        // Apply motorPower
        //chassis.setDriveSpeed(motorPower + motorPower * leftCorrection(), "Left");
        //chassis.setDriveSpeed(motorPower + motorPower * rightCorrection(), "Right");

        FL.move_velocity(motorPower * 600);
		BL.move_velocity(motorPower * 600);
		ML.move_velocity(motorPower * 600);
		FR.move_velocity(motorPower * 600);
		BR.move_velocity(motorPower * 600);
		MR.move_velocity(motorPower * 600);
        
        // Don't clog CPU
        pros::delay(30);
         
        Controller1.set_text(0, 1, to_string(motorPower));
        Controller1.set_text(1, 1, to_string(proportional));
        Controller1.set_text(2, 1, to_string(currentPosition));
        
        // Exit conditions (NEED TO BE TUNED)
        if (error <= 0.1) {
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
        
    currentAngle = 0;
    
    if (inertialSensor) {
        Inr.set_heading(0);
    }

    while (t == 1) {
        // Find currentAngle
        currentAngle = (Inr.get_heading());
        
        // Find error
        error = setpointAngle - currentAngle;
        
        // Find P,I and D
        proportional = ( error / setpointAngle );
        integral += error;
        derivative =  error - prevError;
        
        // Motor power output
        motorPower =  kP*proportional + kI*integral + kD*derivative;
        
        // Set up for next loop
        prevError = error;

        // Slewing
        motorPower = slew(motorPower, prevMotorPower);

        // Overvolt protection
        motorPower = overvoltProtection(motorPower);

        // Apply motorPower
        //chassis.setDriveSpeed(-motorPower, "Left");
        //chassis.setDriveSpeed(motorPower, "Right");
        FL.move_velocity(motorPower * 600);
		BL.move_velocity(motorPower * 600);
		ML.move_velocity(motorPower * 600);
		FR.move_velocity(-motorPower * 600);
		BR.move_velocity(-motorPower * 600);
		MR.move_velocity(-motorPower * 600);

        //set up for next loop
        prevMotorPower = motorPower;
        
        // Don't clog CPU
        pros::delay(30);
        
        Controller1.set_text(0, 1, to_string(motorPower));
        Controller1.set_text(1, 1, to_string(proportional));
        Controller1.set_text(2, 1, to_string(currentPosition));

        // Exit conditions (NEED TUNING)
        if (error <= 0.1 && derivative <= 0.1) {
            t = 0;
        }
    }
    
}