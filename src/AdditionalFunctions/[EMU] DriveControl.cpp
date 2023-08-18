/**************************************************************
                 DRIVE CONTROL 

This is the drive code for the robot during OpControl

Created 6/18/23
Last update 6/18/23

****************************************************************/

#include "main.h"

void driverControl() {

    // Variables
    float driveSpeed;
    float turnSpeed;
    int maxDriveRPM = 600;

    // Brain.Timer.clear();
	motorsStop();

	FL.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	FR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	BL.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	BR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	ML.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	MR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	/**
	 * BUTTON INPUT SYSTEM
	 */

	while (true)
	{
		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_R2))
		{
		}

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_R2))
		{
		}

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_R1))
		{
		}

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_L2))
		{
		}

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_UP))
		{
		}

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_DOWN))
		{
		}

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_X))
		{
		}

		if (Controller2.get_digital(E_CONTROLLER_DIGITAL_R2))
		{
		}

		if (Controller2.get_digital(E_CONTROLLER_DIGITAL_R1))
		{
		}

		if (Controller2.get_digital(E_CONTROLLER_DIGITAL_L2))
		{
		}

		if (Controller2.get_digital(E_CONTROLLER_DIGITAL_UP))
		{
		}

		if (Controller2.get_digital(E_CONTROLLER_DIGITAL_DOWN))
		{
		}

		if (Controller2.get_digital(E_CONTROLLER_DIGITAL_X))
		{
		}

		// Simple linear drive controls, based on the left and right sides and based on the analog system out of 127 multiplied by the RPM of the drives
		double drive = Controller1.get_analog(ANALOG_LEFT_Y);

		double turn = Controller1.get_analog(ANALOG_RIGHT_X);

		double left = (((drive * driveSpeed + turn * turnSpeed)) / 127 * maxDriveRPM);

		double right = (((drive * driveSpeed - turn * turnSpeed)) / 127 * maxDriveRPM);

		FL.move_velocity(left);
		ML.move_velocity(left);
		BL.move_velocity(left);
		FR.move_velocity(right);
		MR.move_velocity(right);
		BR.move_velocity(right);

		// Speed boost
		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_L1))
		{
			driveSpeed = 0.9;
		}
		else
		{
			driveSpeed = 0.6;
		}

		pros::delay(20);
	}
}