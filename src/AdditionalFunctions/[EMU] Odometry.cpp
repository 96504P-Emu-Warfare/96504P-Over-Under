/**************************************************************
                        ODOMETRY

Odometry program using tracking wheels to track the location of
the robot and allow for more accurate movement.

Created 6/17/23
Last update 6/20/23

****************************************************************/

#include "main.h"
#include <math.h>

using namespace pros;

// Constants
const double WHEEL_RADIUS = 2.0; // inches

// Global variables
double prevLeftEncoder;
double prevRightEncoder;
double prevOrientation;
double prevPositionX;
double prevPositionY;
double totalLeftEncoderChange;
double totalRightEncoderChange;

// Used to get the enocdear value of the rotational sensor of a port
double getEncoderValue(Rotation rotSensor) {
  return rotSensor.get_position();
}

// Used to convert encoder value to distance in inches - THIS MATH IS LIKELY WRONG
double convertToInches(double encoderValue) {
  return encoderValue * M_PI / 180 * WHEEL_RADIUS;
}

// From the notes of PIlons
// Tracker code that gives position based on original position and last position

void odometryTracker() {

  while (true) {

  // Store the current encoder values in local variables
  double currentLeftEncoder = getEncoderValue(RotationL);
  double currentRightEncoder = getEncoderValue(RotationR);

  // Calculate the change in each encoder's value since the last cycle
  double leftEncoderChange = currentLeftEncoder - prevLeftEncoder;
  double rightEncoderChange = currentRightEncoder - prevRightEncoder;

  // Update stored previous values of encoders
  prevLeftEncoder = currentLeftEncoder;
  prevRightEncoder = currentRightEncoder;

  // Calculate the total change in the left and right encoder values since the last reset
  totalLeftEncoderChange = totalLeftEncoderChange + currentLeftEncoder; 
  totalRightEncoderChange = totalRightEncoderChange + currentRightEncoder; 

  // New absolute orientation

  // Change in angle

  // Local offset
  
  // Average orientation

  // Global offset as rotated by avgOrientation

  // New absolute position

  // Update stored "previous values" of orientation and position
  //prevOrientation = orientation;
  //prevPositionX = positionX;
  //prevPositionY = positionY;
  }
}

// Movement using simple odometry and PID loop (NO HEADING CORRECTION YET)
void odometryMove(double inches, int RPM, bool hardstop){

  // These are the local starting points for the movement
  double initialPositionL = getEncoderValue(RotationL);
  double initialPositionR = getEncoderValue(RotationR);

  // These are the values which will be continually updated throughout the movement, initialized based on initial position
  double currentPositionL = initialPositionL;
  double currentPositionR = initialPositionR;

  // These will be changed within each while statement and will be added to the currentPosition values
  double changeInPositionL;
  double changeInPositionR;

  // This sets up the braking mode, so the programmer can decide whether to coast or not after movement ends, set on brake by default
  if (hardstop == false) {
    FL.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	  FR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	  BL.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	  BR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	  ML.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	  MR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  }
  else {
    FL.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	  FR.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	  BL.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	  BR.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	  ML.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	  MR.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  }

  while (convertToInches(currentPositionL) < inches || convertToInches(currentPositionR) < inches) {

    // Initial tracking math
    double whileStartingPositionL = getEncoderValue(RotationL);
    double whileStartingPositionR = getEncoderValue(RotationR);

    //PID LOOP HERE

    // Describe the distance each side is from the destination
    double distanceFromDestinationL = inches - convertToInches(currentPositionL);
    double distanceFromDestinationR = inches - convertToInches(currentPositionR);

    // Final tracking math
    double whileEndingPositionL = getEncoderValue(RotationL);
    double whileEndingPositionR = getEncoderValue(RotationR);

    changeInPositionL = whileEndingPositionL - whileStartingPositionL;
    changeInPositionR = whileEndingPositionR - whileEndingPositionR;

    currentPositionL = currentPositionL + changeInPositionL;
    currentPositionR = currentPositionR + changeInPositionR;

    // Heading correction math
  }

  motorsStop();

  return;
}

// Turn using simple odometry and PID loop
void odometryTurn(){
  return;
}

// Uses odometryTracker() to find current location
double odometryGetPosition(){
  //return absolutePosition;
  //return absoluteOrientation;
  return 0.0;
}
