/**************************************************************
                AUTONOMOUS SELECTOR

Where autonomous routines are selected, called in main during initialize.

Created 6/16/23
Last update 6/20/23

****************************************************************/

#include "main.h"

using namespace pros;

// Autonomous Selector using LLEMU
void autonSelector() {

	ez::as::auton_selector.add_autons({
		Auton("Example Drive\n\nDrive forward and come back.", drive_example),
		Auton("Example Turn\n\nTurn 3 times.", turn_example),
		Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
		Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
		Auton("Swing Example\n\nSwing, drive, swing.", swing_example),
		Auton("Combine all 3 movements", combining_movements),
		Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
	});
}
    