#pragma once

//Autons.cpp
void moveTest();

//AutonSelector.cpp
void autonSelector();

//Constants&ExitConditons.cpp
void default_constants();
void one_mogo_constants();
void two_mogo_constants();
void exit_condition_defaults();
void modified_exit_condition();

//ControllerScreen.cpp
void controllerScreenSetup();
void overheatWarning(int motorHeat, Controller Controller);

//DriveControl.cpp
void driverControl();
extern double left;
extern double right;

//Odometry.cpp
double getEncoderValue(Rotation rotSensor);
double convertToInches(double encoderValue);
void odometryTracker();
void odometryMove();
void odometryTurn();
double odometryGetPosition();

//InitializeBranding.cpp
void branding();
void controllerBranding(Controller controller);
void brainBranding();

//MotorControl.cpp
void setDriveSpeed(double motorpower);
void motorsStop();

//PIDs.cpp
int setConstants(string mode);
void movePID(double distance);
void turnPID(double angle);


