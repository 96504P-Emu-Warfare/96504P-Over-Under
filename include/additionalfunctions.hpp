#pragma once

using namespace std;

//Autons.cpp
void moveTest();
void turnTest();
void nonGoal1();
void goal1();
void lukeAuton();
void skills1();
void skills2();

// AutonSelector.cpp
extern int auton_number;
extern int queue_length;
extern string auton_name;
void setAutonNumber(int number);
void forwardOne();
void backwardOne();
void callAuton();
void getAuton();

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
void primeP(double rotationInDegrees);

//RobotSetup.cpp
void robotSetup();

//Cata.cpp
void primeCata();
void shootCata();
void enableCata();
void disableCata();
bool getCataStatus();
void calibrateCata();

//Drivetrain.cpp
extern double heading;
extern double newDistance;
extern double xPos;
extern double yPos;
extern double posArray;
double getCenterPosition();
void updatePos();
double getXPos();
double getYPos();
double getAngle();
void motorsStop();
void setDriveSpeed(double power);
void setDriveSpeed(double power, std::string leftOrRight);
void triggerWings();



