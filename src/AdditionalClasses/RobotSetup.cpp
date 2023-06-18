#include "main.h"
/**************************************************************
ROBOT SETUP 

Sets up the devices used throughout the program, this includes:
 - Motors
 - Controllers
 - Pneumatics
 - Sensors

Created 6/17/23
Last update 6/17/23

****************************************************************/

using namespace pros;

// ------------- ALLIANCE ----------- //
string alliance = {"blue"}; // Blue by default

// ------------ CHASSIS -------- //
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
	600,

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

// ------------- MOTORS ----------- //

// ------------- CONTROLLERS ----------- //
Controller Controller1(E_CONTROLLER_MASTER);
Controller Controller2(E_CONTROLLER_PARTNER);


// ------------- PNEUMATICS ----------- //

// ------------- SENSORS ----------- //