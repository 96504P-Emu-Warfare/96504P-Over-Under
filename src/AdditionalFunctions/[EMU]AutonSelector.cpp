#include "main.h"

int auton_number =  1;
int queue_length = 4;

void setAutonNumber(int number) {
    auton_number = number;
}

void forwardOne() {
    auton_number += 1;
    if (auton_number > queue_length) {
        auton_number = 1;
    }
}

void getAutonNumber() {
    Controller1.set_text(0,0, to_string(auton_number));
}

void backwardOne() {
    auton_number -= 1;
    if (auton_number < 1) {
        auton_number = queue_length;
    }
}

void callAuton() {
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
        turnTest();
    }
}