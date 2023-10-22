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
Last update 9/7/23

****************************************************************/
#include "main.h"

using namespace pros;

// ------------- ALLIANCE ----------- //
std::string alliance("red"); // Red by default

// ------------- AUTONOMOUS ----------- //

// ------------- MOTORS ----------- //
bool lukeBot = false;
//**
   // Motor FL(8, E_MOTOR_GEARSET_06, 0);
    //Motor FR(11, E_MOTOR_GEARSET_06, 1);
    //Motor BL(9, E_MOTOR_GEARSET_06, 1);
    //Motor BR(12, E_MOTOR_GEARSET_06, 0);
    //otor ML(10, E_MOTOR_GEARSET_06, 1);
    //Motor MR(13, E_MOTOR_GEARSET_06, 0);
    //drivetrain chassis(3, 6);

// For motors, the order is (port assignment, cartridge type, forwards backwards w/ 0 being forwards and 1 being backwards) 1/4 forwards

Motor FL(3, E_MOTOR_GEARSET_06, 1);
Motor FR(6, E_MOTOR_GEARSET_06, 0);
Motor BL(10, E_MOTOR_GEARSET_06, 1);
Motor BR(5, E_MOTOR_GEARSET_06, 0);
Motor ML(8, E_MOTOR_GEARSET_06, 0);
Motor MR(4, E_MOTOR_GEARSET_06, 1);
Motor CL(17, E_MOTOR_GEARSET_18, 1);
Motor CR(18, E_MOTOR_GEARSET_18, 1);

// ------------- CONTROLLERS ----------- //
Controller Controller1(E_CONTROLLER_MASTER);
Controller Controller2(E_CONTROLLER_PARTNER);

//------------- RADIO -----------//
//pros::Link radio(20, "Robot1", pros::E_LINK_TRANSMITTER);

// ------------- PNEUMATICS ----------- //
ADIDigitalOut rightWing('A');
ADIDigitalOut leftWing('B');

// ------------- SENSORS ----------- //
//Rotation RotationL(7);
//Rotation RotationR(8);
//Rotation RotationB(9);
IMU Inr(16);
ADIAnalogIn cataSwitch(12);
Optical Opt(13);
bool inertialSensor = true;

// ------------- SIZING SPECS ----------- //
// In inches
double widthBetweenMiddleWheels = 8;
double driveWheelRadius = 3.25/2;
double cataGearing = 6/10;

// Should be able to multiply wheel speed and gearRatio to get motor speed
double gearRatio = (double)54/30;

    void robotSetup(){
    // Set up encoder units for motors 
    FL.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
    FR.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
    BL.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
    BR.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
    ML.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
    MR.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
    CL.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
    CR.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
}
