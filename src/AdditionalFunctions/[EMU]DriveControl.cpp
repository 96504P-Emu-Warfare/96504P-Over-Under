/**************************************************************
                 DRIVE CONTROL 

This is the drive code for the robot during OpControl

Created 6/18/23
Last update 6/18/23

****************************************************************/

#include "main.h"

void driverControl() {

    // Variables
    float driveSpeed = .9;
    float turnSpeed = .4;

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

		getAutonNumber();
		
		// ******************************************
		// CONTROLLER 1							   //
		// ******************************************

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_A)){
			//select screen
		}

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_B)){
			//back screen
		}

		// change this later, only for testing enable/disable
		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_X)){
			if (getCataStatus() == true) {
				disableCata();
			}
			if (getCataStatus() == false) {
				enableCata();
			}
		}

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_Y)){
			primeCata();
			shootCata();
		}

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_L2)){
			//expand both wings
		}

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_R2)){
			CR.move_velocity(-127);
		}
		else if (Controller1.get_digital(E_CONTROLLER_DIGITAL_R1)){
			CR.move(127);
		} 
		else {
			CR.move(0);
		}

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_LEFT)) {
			forwardOne();
		}
		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_RIGHT)) {
			backwardOne();
		}

		// ******************************************
		// CONTROLLER 2							   //
		// ******************************************

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

		if (left > 600) {left = 600;} else if (left < -600) {left = -600;}
		if (right > 600) {right = 600;} else if (right < -600) {right = -600;}
		
		FL.move_velocity(left);
		ML.move_velocity(left);
		BL.move_velocity(left);
		FR.move_velocity(right);
		MR.move_velocity(right);
		BR.move_velocity(right);

		Controller1.set_text(0,1, to_string(left) + " " + to_string(right));

		pros::delay(20);

	}
}