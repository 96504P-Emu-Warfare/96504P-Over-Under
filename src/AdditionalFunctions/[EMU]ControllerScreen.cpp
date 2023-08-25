/**************************************************************
                CONTROLLER SCREEN

The controller screen data is stored here and will be run as
a task in main. The controller includes data such as
 - Battery life
 - Drive speed
 - Robot odometry position
 - Flywheel speed
etc....

Controller 1 will focus on the drive itself
Controller 2 will focus on other operations, such as shooting and elevating

Created 6/17/23
Last update 6/19/23

****************************************************************/
#include "main.h"

using namespace pros;

// Motor overheat warning
void overheatWarningEMU(int motorHeat, Controller controller){
    if (motorHeat > 74) {
    controller.set_text(2,0, "DRIVE MOTOR OVERHEAT WARNING: " + motorHeat);
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

// *************** CONTROLLER 1 - Focused on the drive itself ********************//

// Setting text of controller
while (true) {
Controller1.set_text(0,0, "Bat: " + std::to_string(batteryCapacity) + "%");
//Controller1.set_text(0,8, "LDS: " + std::to_string(LdriveSpeed) + "RPM");
Controller1.set_text(0,8, "xPOS: " + std::to_string(getPosX()));
//Controller1.set_text(0,16, "RDS: " + std::to_string(RdriveSpeed) + "RPM");
Controller1.set_text(0,16, "RDS: " + std::to_string(getPosY()));
Controller1.set_text(1,0, "FR: " + std::to_string(FRheat));
Controller1.set_text(1,8, "MR: " + std::to_string(MRheat));
Controller1.set_text(1,16, "BR: " + std::to_string(BRheat));
Controller1.set_text(2,0, "FL: " + std::to_string(FLheat));
Controller1.set_text(2,8, "ML: " + std::to_string(MLheat));
Controller1.set_text(2,16, "BL: " + std::to_string(BLheat));

// Overheat warnings for drive motors
overheatWarningEMU(FRheat, Controller1);
overheatWarningEMU(MRheat, Controller1);
overheatWarningEMU(BRheat, Controller1);
overheatWarningEMU(FLheat, Controller1);
overheatWarningEMU(MLheat, Controller1);
overheatWarningEMU(BLheat, Controller1);

pros::delay(60);
}

// *************** CONTROLLER 2 - Focused on everything else ********************//

}