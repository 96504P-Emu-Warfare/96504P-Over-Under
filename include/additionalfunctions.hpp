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

//DriveControl.cpp
void driverControl();

//Odometry.cpp
float getEncoderValue();
void odometryTracker();
void odometryMove();
void odometryTurn();
void odometryGetPosition();


