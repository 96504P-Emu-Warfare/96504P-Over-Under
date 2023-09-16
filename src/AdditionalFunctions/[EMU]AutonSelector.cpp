#include "main.h"

autonSystem::autonSystem() {
    auton_number =  1;
    queue_length = 4;
}

void autonSystem::setAutonNumber(int number) {
    auton_number = number;
}

void autonSystem::forwardOne() {
    auton_number += 1;
    if (auton_number > queue_length) {
        auton_number = 1;
    }
}

void autonSystem::backwardOne() {
    auton_number -= 1;
    if (auton_number < 1) {
        auton_number = queue_length;
    }
}

void autonSystem::callAuton() {
    if (auton_number == 1) {
        moveTest();
        return;
    }
    if (auton_number == 2) {
        turnTest();
        return;
    }
    if (auton_number == 3) {
        nonGoal1();
        return;
    }
    if (auton_number == 4) {
        nonGoal1();
        return;
    }
    else {
        return;
    }
}