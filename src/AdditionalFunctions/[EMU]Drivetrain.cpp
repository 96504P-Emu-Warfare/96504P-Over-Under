#include "main.h"

/**
 * DECLARED IN chassis.hpp *
double heading;
double newDistance;
double xPos;
double yPos;
double posArray[];
*/

// Default Constructor

double getCenterPosition() {
  return convertToInches((ML.get_position() + MR.get_position() / 2));
}

void updatePos() {
  while (true) {
      heading += Inr.get_heading();
      newDistance =  chassis.getCenterPosition();
      xPos += (-newDistance * sin(heading));
      yPos += (newDistance * cos(heading));
    }
    
  delay (30);
}

void updatePosTask() {
    //chassis.updatePos();
}

double getXPos() {
    return xPos;
}

double getYPos() {
    return yPos;
}

double getAngle() {
    return heading;
}

void motorsStop() {
    FL.move_velocity(0);
    FR.move_velocity(0);
	BL.move_velocity(0);
	BR.move_velocity(0);
	ML.move_velocity(0);
	MR.move_velocity(0);
}

void setDriveSpeed(double power) {
    FL.move_velocity(power);
    FR.move_velocity(power);
	BL.move_velocity(power);
	BR.move_velocity(power);
	ML.move_velocity(power);
	MR.move_velocity(power);
}

void setDriveSpeed(double power, std::string leftOrRight) {
	if (leftOrRight == "Left") {
		FL.move_velocity(power);
		BL.move_velocity(power);
		ML.move_velocity(power);
	}
	if (leftOrRight == "Right") {
		FR.move_velocity(power);
		BR.move_velocity(power);
		MR.move_velocity(power);
	}
}