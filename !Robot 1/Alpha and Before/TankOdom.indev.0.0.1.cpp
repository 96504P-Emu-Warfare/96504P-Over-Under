#include <iostream>
#include "main.h"
#include <math.h>


// Constants
const double WHEEL_RADIUS = 2.0; // inches

// Global variables
double prevLeftEncoder = 0.0;
double prevRightEncoder = 0.0;
double prevBackEncoder = 0.0;
double prevOrientation = 0.0;
double prevPositionX = 0.0;
double prevPositionY = 0.0;
double totalLeftEncoderChange;
double totalRightEncoderChange;

void odometryTracker() {

  while (true) {
  // Store the current encoder values in local variables
  double currentLeftEncoder = getLeftEncoderValue();
  double currentRightEncoder = getRightEncoderValue();
  double currentBackEncoder = getBackEncoderValue();

  // Calculate the change in each encoder's value since the last cycle
  double leftEncoderChange = currentLeftEncoder - prevLeftEncoder;
  double rightEncoderChange = currentRightEncoder - prevRightEncoder;
  double backEncoderChange = currentBackEncoder = prevBackEncoder;

  // Update stored previous values of encoders
  prevLeftEncoder = currentLeftEncoder;
  prevRightEncoder = currentRightEncoder;

  // Calculate the total change in the left and right encoder values since the last reset
  totalLeftEncoderChange = totalLeftEncoderChange + currentLeftEncoder; 
  totalRightEncoderChange = totalRightEncoderChange + currentRightEncoder; 

  // Calculate new absolute orientation

  // Calculate the change in angle

  // Calculate the local offset
  
  // Calculate the average orientation

  // Calculate global offset as rotated by avgOrientation

  // Calculate new absolute position

  // Update stored "previous values" of orientation and position
  prevOrientation = orientation;
  prevPositionX = positionX;
  prevPositionY = positionY;
  }
}
