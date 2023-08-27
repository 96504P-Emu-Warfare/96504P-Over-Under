#pragma once

using namespace std;

//Autons.cpp
void moveTest();

//AutonSelector.cpp
void autonSelector();

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
void movePID(double distance);
void turnPID(double angle);

//RobotSetup.cpp
void robotSetup();


