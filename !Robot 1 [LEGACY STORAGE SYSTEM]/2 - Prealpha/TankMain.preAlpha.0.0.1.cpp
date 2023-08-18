#include "main.h"

using namespace pros;

// Setting up controllers
Controller Controller1(E_CONTROLLER_MASTER);
Controller Controller2(E_CONTROLLER_PARTNER);

// For motors, the order is (port assignment, cartridge type, forwards backwards w/ 0 being forwards and 1 being backwards)
Motor FL(1, E_MOTOR_GEARSET_06, 0);
Motor FR(4, E_MOTOR_GEARSET_06, 1);
Motor BL(2, E_MOTOR_GEARSET_06, 1);
Motor BR(5, E_MOTOR_GEARSET_06, 0);
Motor ML(3, E_MOTOR_GEARSET_06, 1);
Motor MR(6, E_MOTOR_GEARSET_06, 1);

// Add other motors, sensors and pistons here

// Variables
float drive_speed;
float turn_speed;
int RPM = 600;

// Chassis constructor
Drive chassis(
	// Left Chassis Ports (negative port will reverse it!)
	//   the first port is the sensored port (when trackers are not used!)
	{2, 5},

	// Right Chassis Ports (negative port will reverse it!)
	//   the first port is the sensored port (when trackers are not used!)
	{-3, -4},

	// IMU Port
	21,

	// Wheel Diameter (Remember, 4" wheels are actually 4.125!)
	//    (or tracking wheel diameter)
	4.125,

	// Cartridge RPM
	//   (or tick per rotation if using tracking wheels)
	RPM,

	// External Gear Ratio (MUST BE DECIMAL)
	//    (or gear ratio of tracking wheel)
	1

	// Uncomment if using tracking wheels
	/*
	// Left Tracking Wheel Ports (negative port will reverse it!)
	// ,{1, 2} // 3 wire encoder
	// ,8 // Rotation sensor

	// Right Tracking Wheel Ports (negative port will reverse it!)
	// ,{-3, -4} // 3 wire encoder
	// ,-9 // Rotation sensor
	*/

	// Uncomment if tracking wheels are plugged into a 3 wire expander
	// 3 Wire Port Expander Smart Port
	// ,1
);

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

	// Brain.Timer.clear();
	FL.move_velocity(0);
	FR.move_velocity(0);
	BL.move_velocity(0);
	BR.move_velocity(0);
	ML.move_velocity(0);
	MR.move_velocity(0);

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

		double left = (((drive * drive_speed + turn * turn_speed)) / 127 * RPM);

		double right = (((drive * drive_speed - turn * turn_speed)) / 127 * RPM);

		FL.move_velocity(left);
		ML.move_velocity(left);
		BL.move_velocity(left);
		FR.move_velocity(right);
		MR.move_velocity(right);
		BR.move_velocity(right);

		// Speed boost
		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_L1))
		{
			drive_speed = 0.9;
		}
		else
		{
			drive_speed = 0.6;
		}

		pros::delay(20);
	}

	pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
}
