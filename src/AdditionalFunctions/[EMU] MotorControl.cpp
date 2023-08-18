#include "main.h"

void motorsStop() {
    FL.move_velocity(0);
    FR.move_velocity(0);
	BL.move_velocity(0);
	BR.move_velocity(0);
	ML.move_velocity(0);
	MR.move_velocity(0);
}

void setDriveSpeed(double motorpower){
    FL.move_velocity(motorpower);
    FR.move_velocity(motorpower);
	BL.move_velocity(motorpower);
	BR.move_velocity(motorpower);
	ML.move_velocity(motorpower);
	MR.move_velocity(motorpower);
}