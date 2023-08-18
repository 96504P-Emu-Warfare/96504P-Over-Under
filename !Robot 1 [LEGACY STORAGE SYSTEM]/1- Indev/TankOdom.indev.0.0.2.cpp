/**************************************************************
                        ODOMETRY

Odometry program using tracking wheels to track the location of
the robot and allow for more accurate movement.

Created 6/17/23
Last update 6/20/23

****************************************************************/

#include "main.h"
#include <math.h>

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
int getEncoderValue(pros::Rotation rotSensor) {
  return rotSensor.get_position();
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

// Movement using simple odometry and PID loop
void odometryMove(double inches, int RPM){
  double intialPosition = getEncoderValue();
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
