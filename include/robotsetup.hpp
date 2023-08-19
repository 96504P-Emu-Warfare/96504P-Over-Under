#pragma once

#include "EZ-Template/drive/drive.hpp"

extern std::string alliance;

using namespace pros;

extern Drive chassis;

extern Motor FL;
extern Motor FR;
extern Motor BL;
extern Motor BR;
extern Motor ML;
extern Motor MR;

extern Controller Controller1;
extern Controller Controller2;

extern Rotation RotationL;
extern Rotation RotationR;
extern Rotation RotationB;

extern double mathPI;
extern double widthBetweenMiddleWheels;
extern double trackingWheelWidth;
extern double driveWheelRadius;
