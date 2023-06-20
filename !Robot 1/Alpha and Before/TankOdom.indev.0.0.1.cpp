/**************************************************************
                  ODOMETRY 

The main file for the code, where everything is called and 
executed. Broken down into intialize, disabled, competition_initialize, 
autonomous and opcontrol.

Created 6/16/23
Last update 6/20/23

****************************************************************/

#include <iostream>
#include "main.h"
#include <math.h>


// Constants
const double WHEEL_RADIUS = 2.0; // inches

// Global variables
double prevLeftEncoder = 0.0;
double prevRightEncoder = 0.0;
double prevOrientation = 0.0;
double prevPositionX = 0.0;
double prevPositionY = 0.0;
double totalLeftEncoderChange;
double totalRightEncoderChange;

// Used to get the enocdear value of the rotational sensor of a port
float getEncoderValue(int port) {
  return 1;
}

// From the notes of PIlons
// Tracker code that gives position based on original position and last position

void odometryTracker() {

  while (true) {
  // Store the current encoder values in local variables
  double currentLeftEncoder = getEncoderValue(1);
  double currentRightEncoder = getEncoderValue(1);

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
void odometryMove(){
  return;
}

// Turn using simple odometry and PID loop
void odometryTurn(){
  return;
}

// Uses odometryTracker() to find current location
void odometryGetPosition(){
  //return absolutePosition;
  //return absoluteOrientation;
}
