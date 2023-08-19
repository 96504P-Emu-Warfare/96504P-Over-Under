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
void odometryTracker();
void odometryMove();
void odometryTurn();
double odometryGetPosition();

//InitializeBranding.cpp
void branding();
void controllerBranding(pros::Controller controller);
void brainBranding();

//MotorControl.cpp
void setDriveSpeed(double motorpower);
void motorsStop();

//PIDs.cpp
void setConstants(string mode);
void movePID(double distance);
void turnPID(double angle);


