/**************************************************************
                         MAIN

The main file for the code, where everything is called and 
executed. Broken down into intialize, disabled, competition_initialize, 
autonomous and opcontrol.

Created 6/16/23
Last update 6/18/23

****************************************************************/

#include "main.h"

using namespace pros;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize()
{
	/** Create default settings for motors
	Controller1.print(0, 0, "                  ");
	delay(50);
	Controller1.print(1, 0, "                  ");
	delay(50);
	Controller1.print(2, 0, "Setting up");
	delay(50);
	robotSetup();*/

	// Opening branding on controller and brain
	//branding();

	// Initialize the inertial sensor
	Inr.reset();

	while(Inr.is_calibrating()) {
		pros::delay(20);
	}

	Controller1.set_text(2, 0, "Done setting up");
 	
	//Add autonomous implementation

	// Create the controller screen task
	//std::thread controller(controllerScreenSetupEMU);
	//auto controllerScreen = lv_task_create(controllerScreenSetupEMU, 1000, LV_TASK_PRIO_MID);
	//lv_task_enable(controllerScreen);

	// Create the odometry tracking task
	//std::thread odometry(updatePosTask);

	// Tasks for updating TLs
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
	pros::lcd::set_text(1, "Disabled mode is now running");
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize()
{
	pros::lcd::set_text(1, "Competition_initialize mode is now running");
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
	callAuton();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
	pros::lcd::set_text(0, "OpControl is Now Running");
	Controller1.set_text(2, 0, "Running");

	driverControl();

	pros::delay(10); 
}
