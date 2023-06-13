#include "main.h"
#include "okapi/api/chassis/controller/chassisControllerIntegrated.hpp"
#include "okapi/api/chassis/controller/chassisControllerPid.hpp"
#include "okapi/api/chassis/controller/chassisScales.hpp"
#include "okapi/api/chassis/controller/defaultOdomChassisController.hpp"
#include "okapi/api/chassis/controller/odomChassisController.hpp"
#include "okapi/api/chassis/model/hDriveModel.hpp"
#include "okapi/api/chassis/model/readOnlyChassisModel.hpp"
#include "okapi/api/chassis/model/skidSteerModel.hpp"
#include "okapi/api/chassis/model/threeEncoderSkidSteerModel.hpp"
#include "okapi/api/chassis/model/threeEncoderXDriveModel.hpp"
#include "okapi/api/chassis/model/xDriveModel.hpp"
#include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"

#include "okapi/api/control/async/asyncLinearMotionProfileController.hpp"
#include "okapi/api/control/async/asyncMotionProfileController.hpp"
#include "okapi/api/control/async/asyncPosIntegratedController.hpp"
#include "okapi/api/control/async/asyncPosPidController.hpp"
#include "okapi/api/control/async/asyncVelIntegratedController.hpp"
#include "okapi/api/control/async/asyncVelPidController.hpp"
#include "okapi/api/control/async/asyncWrapper.hpp"
#include "okapi/api/control/controllerInput.hpp"
#include "okapi/api/control/controllerOutput.hpp"
#include "okapi/api/control/iterative/iterativeMotorVelocityController.hpp"
#include "okapi/api/control/iterative/iterativePosPidController.hpp"
#include "okapi/api/control/iterative/iterativeVelPidController.hpp"
#include "okapi/api/control/util/controllerRunner.hpp"
#include "okapi/api/control/util/flywheelSimulator.hpp"
#include "okapi/api/control/util/pidTuner.hpp"
#include "okapi/api/control/util/settledUtil.hpp"
#include "okapi/impl/control/async/asyncMotionProfileControllerBuilder.hpp"
#include "okapi/impl/control/async/asyncPosControllerBuilder.hpp"
#include "okapi/impl/control/async/asyncVelControllerBuilder.hpp"
#include "okapi/impl/control/iterative/iterativeControllerFactory.hpp"
#include "okapi/impl/control/util/controllerRunnerFactory.hpp"
#include "okapi/impl/control/util/pidTunerFactory.hpp"

#include "okapi/api/odometry/odomMath.hpp"
#include "okapi/api/odometry/odometry.hpp"
#include "okapi/api/odometry/threeEncoderOdometry.hpp"

#include "okapi/api/device/rotarysensor/continuousRotarySensor.hpp"
#include "okapi/api/device/rotarysensor/rotarySensor.hpp"
#include "okapi/impl/device/adiUltrasonic.hpp"
#include "okapi/impl/device/button/adiButton.hpp"
#include "okapi/impl/device/button/controllerButton.hpp"
#include "okapi/impl/device/controller.hpp"
#include "okapi/impl/device/distanceSensor.hpp"
#include "okapi/impl/device/motor/adiMotor.hpp"
#include "okapi/impl/device/motor/motor.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"
#include "okapi/impl/device/opticalSensor.hpp"
#include "okapi/impl/device/rotarysensor/IMU.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"
#include "okapi/impl/device/rotarysensor/adiGyro.hpp"
#include "okapi/impl/device/rotarysensor/integratedEncoder.hpp"
#include "okapi/impl/device/rotarysensor/potentiometer.hpp"
#include "okapi/impl/device/rotarysensor/rotationSensor.hpp"

#include "okapi/api/filter/averageFilter.hpp"
#include "okapi/api/filter/composableFilter.hpp"
#include "okapi/api/filter/demaFilter.hpp"
#include "okapi/api/filter/ekfFilter.hpp"
#include "okapi/api/filter/emaFilter.hpp"
#include "okapi/api/filter/filter.hpp"
#include "okapi/api/filter/filteredControllerInput.hpp"
#include "okapi/api/filter/medianFilter.hpp"
#include "okapi/api/filter/passthroughFilter.hpp"
#include "okapi/api/filter/velMath.hpp"
#include "okapi/impl/filter/velMathFactory.hpp"

#include "okapi/api/units/QAcceleration.hpp"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QAngularAcceleration.hpp"
#include "okapi/api/units/QAngularJerk.hpp"
#include "okapi/api/units/QAngularSpeed.hpp"
#include "okapi/api/units/QArea.hpp"
#include "okapi/api/units/QForce.hpp"
#include "okapi/api/units/QFrequency.hpp"
#include "okapi/api/units/QJerk.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QMass.hpp"
#include "okapi/api/units/QPressure.hpp"
#include "okapi/api/units/QSpeed.hpp"
#include "okapi/api/units/QTime.hpp"
#include "okapi/api/units/QTorque.hpp"
#include "okapi/api/units/QVolume.hpp"
#include "okapi/api/units/RQuantityName.hpp"

#include "okapi/api/util/abstractRate.hpp"
#include "okapi/api/util/abstractTimer.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include "okapi/api/util/supplier.hpp"
#include "okapi/api/util/timeUtil.hpp"
#include "okapi/impl/util/configurableTimeUtilFactory.hpp"
#include "okapi/impl/util/rate.hpp"
#include "okapi/impl/util/timeUtilFactory.hpp"
#include "okapi/impl/util/timer.hpp"


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

	double drive_speed  = 0.6;
	double turn_speed = 0.5;
	double heat_speed =  1;
	double turbo_speed = 1;
	double F_speed = 1800;
	double IN_speed = 500;
	double R_speed = 60;
	bool F_toggle = false;
	bool IN_toggle = false;

void on_center_button() {
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
void increase_F_speed()
{
  F_speed += 100;
  if (F_speed > 3000)
  {
    F_speed = 3000;
  }
}

void decrease_F_speed()
{
  F_speed = F_speed - 100;
  if (F_speed < 0)
  {
    F_speed = 0;
  }
}


void F_toggleButton()
{
  if(F_toggle)
  {
	//FLY.set_brake_mode(MOTOR_BRAKE_COAST);
	FLY.move_velocity(0);
  }
  else
  {
    F_speed = 1800;
	FLY.move_velocity(F_speed);
  }
    F_toggle = !F_toggle;

}

void IN_toggleButton()
{
  if(Controller1.get_digital(E_CONTROLLER_DIGITAL_L1))
  {
	IN_toggle = !IN_toggle;
    if(IN_toggle == true)
    {
        INTR.move_velocity(IN_speed);
    }
    else
    {
      INTR.move_velocity(0);
    }

  }
  else
  {
	IN_toggle = !IN_toggle;
    if(IN_toggle == true)
    {
        INTR.move_velocity(-R_speed*3);
    }
    else
    {
      INTR.move_velocity(0);
    }
  }
}



void Indexer_activate()
{
  if(Controller1.get_digital(E_CONTROLLER_DIGITAL_L1))
  {
    Indexer.set_value(HIGH);
	delay(150);
    //wait(0.15,seconds);
    Indexer.set_value(LOW);
  }
  else
  {	
    for(int i = 0; i < 3; i++)
    {
        Indexer.set_value(HIGH);
        delay(150);
        Indexer.set_value(LOW);
        delay(200);
    }
  }
}

void rotate()
{
	
}

void Expand()
{
  if(Controller1.get_digital(E_CONTROLLER_DIGITAL_Y) || Controller2.get_digital(E_CONTROLLER_DIGITAL_Y))
  {
    Expansion.set_value(HIGH);
    Expansion2.set_value(HIGH);
    FLY.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  }
}

void opcontrol() 
{
	pros::lcd::set_text(1, "zesty");

	//Brain.Timer.clear();
	frontLeft.move_velocity(0);
	frontRight.move_velocity(0);
	backLeft.move_velocity(0);
	backRight.move_velocity(0);
	FLY.move_velocity(0);
	INTR.move_velocity(0);

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


	while (true) 
	{
		if(Controller1.get_digital(E_CONTROLLER_DIGITAL_R2))
		{
			//FLY.move_velocity(300);

			F_toggleButton();

				//F_toggle = true;
			//pros::lcd::set_text(1, "haha56");
		}


	if(Controller1.get_digital(E_CONTROLLER_DIGITAL_R2))
	{
		F_toggleButton();
		screen::print(TEXT_MEDIUM, 3, "DaBaby");
	}
	
	if(Controller1.get_digital(E_CONTROLLER_DIGITAL_R1))
	{
		IN_toggleButton();
	}

	if(Controller1.get_digital(E_CONTROLLER_DIGITAL_L2))
	{
		Indexer_activate();
	}

	if(Controller1.get_digital(E_CONTROLLER_DIGITAL_UP))
	{
		increase_F_speed();
	}

	if(Controller1.get_digital(E_CONTROLLER_DIGITAL_DOWN))
	{
		decrease_F_speed();
	}

	if(Controller1.get_digital(E_CONTROLLER_DIGITAL_X))
	{
		Expand();
	}

	if(Controller2.get_digital(E_CONTROLLER_DIGITAL_R2))
	{
		F_toggleButton();
	}
	
	if(Controller2.get_digital(E_CONTROLLER_DIGITAL_R1))
	{
		IN_toggleButton();
	}

	if(Controller2.get_digital(E_CONTROLLER_DIGITAL_L2))
	{
		Indexer_activate();
	}

	if(Controller2.get_digital(E_CONTROLLER_DIGITAL_UP))
	{
		increase_F_speed();
	}

	if(Controller2.get_digital(E_CONTROLLER_DIGITAL_DOWN))
	{
		decrease_F_speed();
	}

	if(Controller2.get_digital(E_CONTROLLER_DIGITAL_X))
	{
		Expand();
	}

		/*
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int left = Controller1.get_analog(ANALOG_LEFT_Y);
		int right = Controller1.get_analog(ANALOG_RIGHT_Y);
		*/


		//left_mtr = left;
		//right_mtr = right;

		//

		
		double Drive = Controller1.get_analog(ANALOG_LEFT_Y);

		double Turn = Controller1.get_analog(ANALOG_RIGHT_X);

		double left = (((Drive*drive_speed + Turn*turn_speed))/127 * 600);



		double right = (((Drive*drive_speed - Turn*turn_speed))/127 * 600);
		

		
	   frontLeft.move_velocity(left);
       topLeft.move_velocity(left );
       backLeft.move_velocity(left);
       frontRight.move_velocity(right);
       topRight.move_velocity(right);
       backRight.move_velocity(right);  
		

	/*
	   frontLeft.move((left*600)/215);
       topLeft.move((left*600)/215);
       backLeft.move((left*600)/215);
       frontRight.move((right*600)/215);
       topRight.move((right*600)/215);
       backRight.move((right*600)/215);  
*/
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

