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
        kP = .001;
        kI = .0002;
        kD = .0002;
    }
    if  (mode == "turn") {
        kP = .2;
        kI = .0001;
        kD = .0008;
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
    if (curr < -1) {
        curr = -1;
    }
    return curr;
}

void moveP(double distance) {

    FL.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	FR.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	BL.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	BR.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	ML.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	MR.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

    //Set PID constants to move mode
    setConstants("move");
    
    setpointDistance = distance;
    currentPosition = 0;
    prevError = 0;
    m = 1;
    Controller1.clear();
    ML.tare_position();
    MR.tare_position();
    
    while (m == 1) {
        // Find currentPosition
        currentPosition = ( ((ML.get_position() + MR.get_position()) / 2) * (mathPI / 180) * 0.6 * driveWheelRadius);
        
        // Find error
        error = setpointDistance - currentPosition;
        
        // Find P,I and D
        proportional = ( error / setpointDistance );
        integral += error;
        derivative = error - prevError;
        
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

        // Slewing
        motorPower = slew(motorPower, prevMotorPower);

        // Overvolt protection
        motorPower = overvoltProtection(motorPower);
        
        // Don't clog CPU

        Controller1.set_text(0, 1, "e/p: " + to_string(currentPosition) + " " + to_string(error));
        Controller1.set_text(1, 1, "powerM" + to_string(motorPower));
        Controller1.set_text(2, 1, to_string(currentPosition));
        
        pros::delay(30);
        
        // Exit conditions (NEED TO BE TUNED)
        if (abs(error) <= 1) {
            m = 0;
        }
    } 
    currentPosition = 0;
    proportional = 0;
    integral = 0;
    derivative = 0;
}

void turnP(double angle) {

    FL.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	FR.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	BL.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	BR.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	ML.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	MR.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

    //Set PID constants to turn mode
    setConstants("turn");
    t = 1;
    
    setpointAngle = angle;
    prevError = 0;
        
    currentAngle = 0;
    
    Inr.set_rotation(0);

    delay(20);

    while (t == 1) {

        // Find currentAngle
        currentAngle = (Inr.get_rotation());
        
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
        
        Controller1.set_text(0, 0, "turning:" + to_string(error));
        Controller1.set_text(1, 0, to_string(proportional));
        Controller1.set_text(2, 0, to_string(currentPosition));

        // Exit conditions (NEED TUNING)
        if (error <= 2) {
            t = 0;
            FL.move_velocity(0);
            BL.move_velocity(0);
            ML.move_velocity(0);
            FR.move_velocity(0);
            BR.move_velocity(0);
            MR.move_velocity(0);
        }
    }
    
    proportional = 0;
    integral = 0;
    derivative =  0;
    
}