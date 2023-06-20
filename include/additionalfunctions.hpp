#pragma once

//Autons.cpp
void drive_example();
void turn_example();
void drive_and_turn();
void wait_until_change_speed();
void swing_example();
void combining_movements();
void interfered_example();

//AutonSelector.cpp
void autonSelector();

//Constants&ExitConditons.cpp
void default_constants();
void one_mogo_constants();
void two_mogo_constants();
void exit_condition_defaults();
void modified_exit_condition();

//ControllerScreen.cpp
void controllerSetup();
void overheatWarning();

//DriveControl.cpp
void driverControl();
void motorsStop();
extern double left;
extern double right;

//Odometry.cpp
double getEncoderValue();
void odometryTracker();
void odometryMove();
void odometryTurn();
double odometryGetPosition();

//InitializeBranding.cpp
void branding();
void controllerBranding();
void brainBranding();


