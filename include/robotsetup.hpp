#pragma once

extern std::string alliance;

using namespace pros;

extern autonSystem autonSelectorP;

extern Motor FL;
extern Motor FR;
extern Motor BL;
extern Motor BR;
extern Motor ML;
extern Motor MR;
extern Motor CL;
extern Motor CR;
extern drivetrain chassis;

extern Controller Controller1;
extern Controller Controller2;

extern Rotation RotationL;
extern Rotation RotationR;
extern Rotation RotationB;
extern IMU Inr;
extern bool inertialSensor;

extern double mathPI;
extern double widthBetweenMiddleWheels;
extern double trackingWheelWidth;
extern double driveWheelRadius;
extern double gearRatio;

// While Loop conditions, 'm' for move, 't' for turn pids
extern int m;
extern int t;
