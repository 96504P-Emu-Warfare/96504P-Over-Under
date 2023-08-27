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

drivetrain::drivetrain(int portML, int portMR) {
}

double drivetrain::getCenterPosition() {
  return convertToInches((ML.get_position() + MR.get_position() / 2));
}

void drivetrain::updatePos() {
  while (true) {
      heading += Inr.get_heading();
      newDistance =  chassis.getCenterPosition();
      xPos += (-newDistance * sin(heading));
      yPos += (newDistance * cos(heading));
      posArray[0] = xPos;
      posArray[1] = yPos;
    }
    
  delay (30);
}

void updatePosTask() {
    chassis.updatePos();
}

double drivetrain::getXPos() {
    return xPos;
}

double drivetrain::getYPos() {
    return yPos;
}

double drivetrain::getAngle() {
    return heading;
}

void drivetrain::motorsStop() {
    FL.move_velocity(0);
    FR.move_velocity(0);
	BL.move_velocity(0);
	BR.move_velocity(0);
	ML.move_velocity(0);
	MR.move_velocity(0);
}

void drivetrain::setDriveSpeed(double power) {
    FL.move_velocity(power);
    FR.move_velocity(power);
	BL.move_velocity(power);
	BR.move_velocity(power);
	ML.move_velocity(power);
	MR.move_velocity(power);
}

void drivetrain::setDriveSpeed(double power, std::string leftOrRight) {
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