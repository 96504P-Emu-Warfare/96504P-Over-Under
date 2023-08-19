/**************************************************************
                    ROBOT SETUP 

Sets up the devices and robot variables used throughout the program, this includes:
 - Alliance Color
 - Motors
 - Controllers
 - Pneumatics
 - Sensors
 - Robot Sizing Specs

Created 6/17/23
Last update 8/18/23

****************************************************************/
#include "main.h"

using namespace pros;

// ------------- ALLIANCE ----------- //
std::string alliance("red"); // Red by default

// ------------- MOTORS ----------- //
// For motors, the order is (port assignment, cartridge type, forwards backwards w/ 0 being forwards and 1 being backwards)
Motor FL(1, E_MOTOR_GEARSET_06, 1);
Motor FR(4, E_MOTOR_GEARSET_06, 1);
Motor BL(2, E_MOTOR_GEARSET_06, 1);
Motor BR(5, E_MOTOR_GEARSET_06, 1);
Motor ML(3, E_MOTOR_GEARSET_06, 1);
Motor MR(6, E_MOTOR_GEARSET_06, 1);

// ------------- CONTROLLERS ----------- //
Controller Controller1(E_CONTROLLER_MASTER);
Controller Controller2(E_CONTROLLER_PARTNER);

// ------------- PNEUMATICS ----------- //

// ------------- SENSORS ----------- //
Rotation RotationL(7);
Rotation RotationR(8);
Rotation RotationB(9);

// ------------- SIZING SPECS ----------- //
// In inches
double trackingWheelRadius = 2;
double trackingWheelWidth = 10;
double driveWheelRadius = 3;
