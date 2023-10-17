/**************************************************************
         AUTONOMOUSES / AUTONOMISES / AUTONOMI

Where all the autonomous code is housed, including 
Skills

The selection of autons is:
 - Nothing yet, come back later

Created 6/17/23
****************************************************************/
#include "main.h"

using namespace pros

bool cataReady = false;
bool cataOn = true;

void shootCata() {
    double hue = Opt.get_hue();
    if (cataOn && cataReady && hue < 140 && hue > 81) {
            CL.move_relative(5, 200);
            CR.move_relative(5, 200);
            cataReady = false;
    } 
    else {
        Controller2.set_text(2,1, "Cata not ready to fire");
    }
}

void primeCata() {
    if (cataOn) {
        //make sure to change cataGearing in robot setup
        primeP(180);
        cataReady = true;
    }
}

void disableCata() {
    cataOn = false;
}

void enableCata() {
    cataOn = true;
}

bool getCataStatus() {
    return cataOn;
}

void calibrateCata() {
    CL.set_zero_position(0);
    delay(20);
    while (cataSwitch.get_value() == 0) {
        CL.move_velocity(50);
    }
    Controller1.set_text(1,1, to_string(CL.get_position))
}