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
		Auton("Testing\n\nDrive forward 12 in and come back.", moveTest),
		
	});
}
    