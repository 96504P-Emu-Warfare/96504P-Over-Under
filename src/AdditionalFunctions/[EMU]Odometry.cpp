/**************************************************************
                        ODOMETRY

Odometry program using tracking wheels to track the location of
the robot and allow for more accurate movement.

Created 6/17/23
Last update 8/25/23

****************************************************************/

#include "main.h"
#include <math.h>

using namespace pros;


// Global variables
double xPos = 0;
double yPos = 0;
double posArray[2];
double heading;
double newDistance;


// Used to get the enocdear value of the rotational sensor of a port
double getSensorEncoderValue(Rotation rotSensor) {
  return rotSensor.get_position();
}

// Used to convert encoder value to distance in inches 
double convertToInches(double value) {
  return value * mathPI / 180 * driveWheelRadius * gearRatio;
}
 



