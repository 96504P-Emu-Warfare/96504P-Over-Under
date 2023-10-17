/**************************************************************
                CONTROLLER SCREEN

The controller screen data is stored here and will be run as
a task in main. The controller includes data such as
 - Battery life
 - Drive speed
 - Robot odometry position
 - Flywheel speed
etc....

Controller 1 will focus on the things useful while driving
Controller 2 will focus on diagnostics and maybe elevation

Created 6/17/23
Last update 6/19/23

****************************************************************/
#include "main.h"

using namespace pros;

// Motor overheat warning
void overheatWarningEMU(int motorHeat, Controller controller){
    if (motorHeat > 74) {
        controller.set_text(2,0, "DRIVE MOTOR OVERHEAT WARNING: " + motorHeat);
        screen::set_eraser(COLOR_RED);
        screen::erase();
        controller.rumble(". . .");
    }   
}

void controllerScreenSetupEMU() {

    // Data to be fed to controller
    int batteryCapacity = battery::get_capacity();
    int LdriveSpeed = (FL.get_actual_velocity() + ML.get_actual_velocity() + BL.get_actual_velocity()) / 3;
    int RdriveSpeed = (FR.get_actual_velocity() + MR.get_actual_velocity() + BR.get_actual_velocity()) / 3;
    int FRheat = FR.get_temperature();
    int FLheat = FL.get_temperature();
    int MRheat = MR.get_temperature();
    int MLheat = ML.get_temperature();
    int BRheat = BR.get_temperature();
    int BLheat = BL.get_temperature();

    // *************** CONTROLLER 1 - Focused on driving  ********************//

    // Setting text of controller
    //while (true) {
        Controller1.set_text(0,0, "Bat: " + std::to_string(batteryCapacity) + "%");
        Controller1.set_text(1,0, "LDS: " + std::to_string(LdriveSpeed) + "RPM");
        Controller1.set_text(1,8, "RDS: " + std::to_string(RdriveSpeed) + "RPM");
        

        // Overheat warnings for drive motors
        overheatWarningEMU(FRheat, Controller1);
        overheatWarningEMU(MRheat, Controller1);
        overheatWarningEMU(BRheat, Controller1);
        overheatWarningEMU(FLheat, Controller1);
        overheatWarningEMU(MLheat, Controller1);
        overheatWarningEMU(BLheat, Controller1);

        //pros::delay(10); MAKE SURE TO UNCOMMENT WHEN PUT BACK INTO A SEPARATE TASK
    //}

    // *************** CONTROLLER 2 - Focused on watching data ********************//
        
        Controller1.set_text(0,0, "FR: " + std::to_string(FRheat));
        Controller1.set_text(0,8, "MR: " + std::to_string(MRheat));
        Controller1.set_text(1,0, "BR: " + std::to_string(BRheat));
        Controller1.set_text(1,8, "FL: " + std::to_string(FLheat));
        Controller1.set_text(2,0, "ML: " + std::to_string(MLheat));
        Controller1.set_text(2,8, "BL: " + std::to_string(BLheat));
}