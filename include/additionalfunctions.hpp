#pragma once

using namespace std;

//Autons.cpp
void moveTest();
void turnTest();
void nonGoal1();
void goal1();
void scrim1();

// AutonSelector.cpp
extern int auton_number;
extern int queue_length;
void setAutonNumber(int number);
void forwardOne();
void backwardOne();
void callAuton();
void getAutonNumber();

//ControllerScreen.cpp
void controllerScreenSetupEMU();
void overheatWarningEMU(int motorHeat, pros::Controller controller);

//DriveControl.cpp
void driverControl();
extern double left;
extern double right;

//Odometry.cpp
double getSensorEncoderValue(pros::Rotation rotSensor);
double convertToInches(double encoderValue);

//InitializeBranding.cpp
void branding();
void controllerBranding(pros::Controller controller);
void brainBranding();

//PIDs.cpp
void setConstants(string mode);
void moveP(double distance);
void turnP(double angle);

//RobotSetup.cpp
void robotSetup();


