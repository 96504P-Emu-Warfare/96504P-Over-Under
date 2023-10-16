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
double slewRate;

void setConstants(string mode) {
    if (mode == "move") {
        kP = 1.2;
        kI = 0;
        kD = .01;
        slewRate = 0.05;
    }
    if  (mode == "turnShort") {
        kP = .8;
        kI = .0;
        kD = .02;
        slewRate = 0.04;
    }
    if  (mode == "turnLong") {
        kP = 1.6;
        kI = .0;
        kD = .03;
        slewRate = 0.03;
    }
    if (mode == "cata") {
        kP = 1.2;
        kI = 0;
        kD = .01;
        slewRate = 0.1;
    }
    else {
        std::cout << "Error: Constants are not set properly";
    }
}

int m;
int t;
int s;

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

double correctionError;

double slew(double curr, double prev) {
    // Slew rate should be 1 / the amt of cycles of the loop you want it to take to reach full speed from 0
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

void resetValues() {
    currentPosition = 0;
    setpointDistance = 0;
    currentAngle = 0;
    setpointAngle = 0;
    error = 0;
    proportional = 0;
    integral = 0;
    derivative = 0;
    prevError = 0;
    motorPower = 0;
    prevMotorPower = 0;
    correctionError = 0;
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
    prevMotorPower = 0;
    m = 1;
    Controller1.clear();
    ML.set_zero_position(0);
    MR.set_zero_position(0);
    
    while (m == 1) {


        // Find currentPosition 
        currentPosition = ( ((ML.get_position() + MR.get_position()) / 2) * (mathPI / 180) * 0.6 * driveWheelRadius);
        correctionError = Inr.get_rotation();
        
        // Find error
        error = setpointDistance - currentPosition;
        
        // Find P,I and D
        proportional = ( abs(error) / setpointDistance );
        integral += error;
        derivative =  error - prevError;
        
        // Motor power output
        motorPower =  kP*proportional + kI*integral + kD*derivative;
        
        // Slewing
        motorPower = slew(motorPower, prevMotorPower);

        // Overvolt protection
        motorPower = overvoltProtection(motorPower);

        // Apply power
        FL.move_velocity(motorPower * 400);
		BL.move_velocity(motorPower * 400);
		ML.move_velocity(motorPower * 400);
		FR.move_velocity(motorPower * 400);
		BR.move_velocity(motorPower * 400);
		MR.move_velocity(motorPower * 400);
        
        // Exit conditions (NEED TO BE TUNED)
        if (abs(error) <= 0.2) {
            m = 0;
            FL.move_velocity(motorPower * 0);
            BL.move_velocity(motorPower * 0);
            ML.move_velocity(motorPower * 0);
            FR.move_velocity(motorPower * 0);
            BR.move_velocity(motorPower * 0);
            MR.move_velocity(motorPower * 0);
        }

        //set up for next loop
        prevError = error;
        prevMotorPower = motorPower;

        // Don't clog CPU
        // Replace all this with some type of event viewer on controller 2
        // Controller2.update(update values within a task to send to controller 2)
        Controller1.set_text(1, 1, "e/p: " + to_string(currentPosition) + " " + to_string(error));
        Controller1.set_text(2, 1, "powerM" + to_string(motorPower));
        Controller1.set_text(3, 1, to_string(currentPosition));
        
        pros::delay(30);
        
    } 
    resetValues();
}

void turnP(double angle) {

    FL.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	FR.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	BL.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	BR.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	ML.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	MR.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

    //Set PID constants to turn mode
    if (angle > 120) {setConstants("turnLong");}
    else {setConstants("turnShort");}

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
        proportional = ( abs(error) / setpointAngle );
        integral += error;
        derivative =  error - prevError;
        
        // Motor power output
        motorPower =  kP*proportional + kI*integral + kD*derivative;
        
        // Slewing
        motorPower = slew(motorPower, prevMotorPower);

        // Overvolt protection
        motorPower = overvoltProtection(motorPower);

        // Apply motorPower
        //chassis.setDriveSpeed(-motorPower, "Left");
        //chassis.setDriveSpeed(motorPower, "Right");
        FL.move_velocity(motorPower * 400);
		BL.move_velocity(motorPower * 400);
		ML.move_velocity(motorPower * 400);
		FR.move_velocity(motorPower * -400);
		BR.move_velocity(motorPower * -400);
		MR.move_velocity(motorPower * -400);

        //set up for next loop
        prevError = error;
        prevMotorPower = motorPower;
        
        Controller1.set_text(0, 0, " turning:" + to_string(error));
        Controller1.set_text(1, 0, to_string(proportional));
        Controller1.set_text(2, 0, to_string(currentPosition));

        // Exit conditions (NEED TUNING)
        if (abs(error) <= 0.5) {
            t = 0;
            FL.move_velocity(0);
            BL.move_velocity(0);
            ML.move_velocity(0);
            FR.move_velocity(0);
            BR.move_velocity(0);
            MR.move_velocity(0);
        }

        // Don't clog CPU
        pros::delay(30);
    }
    
    resetValues();
    
}

void primeP(double rotationInDegrees) {

    FL.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	FR.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	BL.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	BR.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	ML.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	MR.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

    //Set PID constant
    setConstants("cata");

    s = 1;
    
    setpointAngle = rotationInDegrees;
    prevError = 0;
        
    currentAngle = 0;
    
    Inr.set_rotation(0);

    delay(20);

    while (s == 1) {

        // Find currentAngle
        currentAngle = (CL.get_position() * cataGearing);
        
        // Find error
        error = setpointAngle - currentAngle;
        
        // Find P,I and D
        proportional = ( abs(error) / setpointAngle );
        integral += error;
        derivative =  error - prevError;
        
        // Motor power output
        motorPower =  kP*proportional + kI*integral + kD*derivative;
        
        // Slewing
        motorPower = slew(motorPower, prevMotorPower);

        // Overvolt protection
        motorPower = overvoltProtection(motorPower);

        // Apply motorPower
        CL.move_velocity(motorPower * 200);

        //set up for next loop
        prevError = error;
        prevMotorPower = motorPower;
        
        Controller1.set_text(0, 0, " priming:" + to_string(error));
        Controller1.set_text(1, 0, to_string(proportional));
        Controller1.set_text(2, 0, to_string(currentPosition));

        // Limit switch
        if (cataSwitch.get_value() == 1) {
            s = 0;
        }
        
        // Exit conditions (NEED TUNING)
        if (abs(error) <= 0.5) {
            s = 0;
            CL.move_velocity(0);
        }

        // Don't clog CPU
        pros::delay(30);
    }
    
    resetValues();
    
}