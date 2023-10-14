/**************************************************************
         AUTONOMOUSES / AUTONOMISES / AUTONOMI

Where all the autonomous code is housed, including 
Skills

The selection of autons is:
 - Nothing yet, come back later

Created 6/17/23
****************************************************************/
#include "main.h"

bool cataReady = false;
bool cataOn = true;

void shootCata() {

    if (cataOn) {
        if (cataReady == true) {
            CL.move_relative(5, 200);
            CR.move_relative(5, 200);
            cataReady = false;
        }  
        else {
            Controller2.set_text(0,0, "Cata not ready to fire");
        }
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