#include "main.h"
#include "paired AUTON document"
#include "IncludeDocument.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
using namespace pros;

Controller Controller1(E_CONTROLLER_MASTER);
Controller Controller2(E_CONTROLLER_PARTNER);
Motor frontLeft(11, E_MOTOR_GEARSET_06, 1);
Motor frontRight(19, E_MOTOR_GEARSET_06, 0);
Motor backLeft(12, E_MOTOR_GEARSET_06, 1);
Motor backRight(20, E_MOTOR_GEARSET_06, 0);
Motor topLeft(1, E_MOTOR_GEARSET_06, 0);
Motor topRight(10, E_MOTOR_GEARSET_06, 0);

ADIDigitalOut Indexer('A', LOW);
ADIDigitalOut Expansion('B', LOW);
ADIDigitalOut Expansion2('C', LOW);
Motor FLY(5, E_MOTOR_GEARSET_06, 0);
Motor INTR(6, E_MOTOR_GEARSET_06, 1);

double drive_speed = 0.6;
double turn_speed = 0.5;
double heat_speed = 1;
double turbo_speed = 1;
double F_speed = 1800;
double IN_speed = 500;
double R_speed = 60;
bool F_toggle = false;
bool IN_toggle = false;

void on_center_button()
{
	static bool pressed = false;
	pressed = !pressed;
	if (pressed)
	{
		pros::lcd::set_text(2, "I was pressed!");
	}
	else
	{
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::lcd::initialize();
	pros::lcd::register_btn1_cb(on_center_button);
	opcontrol();
	/*
	frontLeft.move_velocity(400);
	topLeft.move_velocity(400);
	backLeft.move_velocity(400);
	frontRight.move_velocity(-400);
	topRight.move_velocity(-400);
	backRight.move_velocity(-400);
	*/
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

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
	pros::lcd::set_text(1, "zesty");

	// Brain.Timer.clear();
	frontLeft.move_velocity(0);
	frontRight.move_velocity(0);
	backLeft.move_velocity(0);
	backRight.move_velocity(0);

	frontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	frontRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	backLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	backRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	FLY.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	INTR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	topLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	topRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	// Button pressing here:
	/*
	Controller1.ButtonR2.pressed(F_toggleButton);
   Controller1.ButtonR1.pressed(IN_toggleButton);
   Controller1.ButtonL2.pressed(Indexer_activate);
   Controller1.ButtonUp.pressed(increase_F_speed);
   Controller1.ButtonDown.pressed(decrease_F_speed);
   Controller1.ButtonX.pressed(Expand);
   Controller2.ButtonR2.pressed(F_toggleButton);
   Controller2.ButtonR1.pressed(IN_toggleButton);
   Controller2.ButtonL2.pressed(Indexer_activate);
   Controller2.ButtonUp.pressed(increase_F_speed);
   Controller2.ButtonDown.pressed(decrease_F_speed);
   Controller2.ButtonX.pressed(Expand);
	*/

	/**
	 * BUTTON INPUT SYSTEM HERE
	 */

	while (true)
	{
		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_R2))
		{
			// FLY.move_velocity(300);

			F_toggleButton();

			// F_toggle = true;
			// pros::lcd::set_text(1, "haha56");
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

		double Drive = Controller1.get_analog(ANALOG_LEFT_Y);

		double Turn = Controller1.get_analog(ANALOG_RIGHT_X);

		double left = (((Drive * drive_speed + Turn * turn_speed)) / 127 * 600);

		double right = (((Drive * drive_speed - Turn * turn_speed)) / 127 * 600);

		frontLeft.move_velocity(left);
		topLeft.move_velocity(left);
		backLeft.move_velocity(left);
		frontRight.move_velocity(right);
		topRight.move_velocity(right);
		backRight.move_velocity(right);

		if (Controller1.get_digital(E_CONTROLLER_DIGITAL_L1))
		{
			drive_speed = 1;
		}
		else
		{
			drive_speed = 0.6;
		}

		pros::delay(20);
	}
}
