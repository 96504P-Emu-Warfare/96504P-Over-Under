/**************************************************************
                 DRIVE CONTROL 

This is the drive code for the robot during OpControl

Created 6/18/23
Last update 6/18/23

****************************************************************/

#include "main.h"

void driverControl() {

    // Variables
    float driveSpeed = .8;
    float turnSpeed = .2;

    // Brain.Timer.clear();
	//chassis.motorsStop();

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
		void controllerScreenSetupEMU();
		
		// CONTROLLER 1

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_R2))
		{
			moveP(20);
		}

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_A))
		{
			turnP(90);
		}

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_R1))
		{
			moveTest();
		}

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_L2))
		{
			while (true) {
				Controller1.set_text(0,0, to_string(Inr.get_rotation()));
			}
		}

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_UP))
		{
		}

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_DOWN))
		{
		}

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_X))
		{
			scrim1();
		}

		// CONTROLLER 2

		if (Controller2.get_digital(E_CONTROLLER_DIGITAL_R2))
		{
			turnP(90);
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

		double left = (((drive * driveSpeed + turn * turnSpeed)) / 127 * 600);

		double right = (((drive * driveSpeed - turn * turnSpeed)) / 127 * 600);

		FL.move_velocity(left);
		ML.move_velocity(left);
		BL.move_velocity(left);
		FR.move_velocity(right);
		MR.move_velocity(right);
		BR.move_velocity(right);

		pros::delay(20);
	}
}