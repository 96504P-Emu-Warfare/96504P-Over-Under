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
	bool leftWingOut = false;
	bool rightWingOut = false;
	bool cataMotorOn = false;

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

		// ******************************************
		// CONTROLLER 1							   //
		// ******************************************

		if (Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_A)){
			if (cataMotorOn == false) {
				CL.move_velocity(70);
				cataMotorOn = true;
			}
			else {
				CL.move_velocity(0);
				cataMotorOn = false;
			}
		}

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_B)){
			
		}

		// change this later, only for testing enable/disable
		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_X)){
			callAuton();
		}

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_Y)){
			primeCata();
			shootCata();
		}

		//SHIFT BUTTON
		if (Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)){
			if (leftWingOut == false) {
				leftWing.set_value(1);
				leftWingOut = true;
			}
			else {
				leftWing.set_value(0);
				leftWingOut = false;
			}
		}

		if (Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)){
			if (rightWingOut == false) {
				rightWing.set_value(1);
				rightWingOut = true;
			}
			else {
				rightWing.set_value(0);
				rightWingOut = false;
			}
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

		if (Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT)) {
			forwardOne();
		}
		if (Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT)) {
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

		getAuton();

        overheatWarningEMU(FR.get_temperature(), Controller1);
        overheatWarningEMU(MR.get_temperature(), Controller1);
        overheatWarningEMU(BR.get_temperature(), Controller1);
        overheatWarningEMU(FL.get_temperature(), Controller1);
        overheatWarningEMU(ML.get_temperature(), Controller1);
        overheatWarningEMU(BL.get_temperature(), Controller1);
		overheatWarningEMU(CL.get_temperature(), Controller1);
		overheatWarningEMU(CR.get_temperature(), Controller1);

		pros::delay(20);

	}
}