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

	pros::delay(500); // Stop the user from doing anything while legacy ports configure.

	// Configure your chassis controls
	chassis.set_active_brake(0.1); // Sets the active brake kP
	default_constants();
	exit_condition_defaults();

	// Autonomous Selector using LLEMU
	ez::as::auton_selector.add_autons({
		Auton("Example Drive\n\nDrive forward and come back.", drive_example),
		Auton("Example Turn\n\nTurn 3 times.", turn_example),
		Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
		Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
		Auton("Swing Example\n\nSwing, drive, swing.", swing_example),
		Auton("Combine all 3 movements", combining_movements),
		Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
	});

	// Initialize chassis and auton selector
	chassis.initialize();
	ez::as::initialize();
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
	chassis.reset_pid_targets();				  // Resets PID targets to 0
	chassis.reset_gyro();						  // Reset gyro position to 0
	chassis.reset_drive_sensor();				  // Reset drive sensors to 0
	chassis.set_drive_brake(MOTOR_BRAKE_HOLD);	  // Set motors to hold.  This helps autonomous consistency.
	ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
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

	driverControl();

	pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
}
