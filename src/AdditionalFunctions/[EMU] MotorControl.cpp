/**************************************************************
                       MOTOR CONTROL

Simple methods used to change motor speeds and behaviors.

Created 8/18/23
Last update 8/18/23

****************************************************************/
#include "main.h"

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

void setDriveSpeed(double power, string leftOrRight) {
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