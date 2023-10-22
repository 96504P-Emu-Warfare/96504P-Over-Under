#include "main.h"

int auton_number =  1;
int queue_length = 6;
string auton_name;

void setAutonNumber(int number) {
    auton_number = number;
}

void forwardOne() {
    auton_number += 1;
    if (auton_number > queue_length) {
        auton_number = 1;
    }
}

void getAuton() {
    Controller1.set_text(0,0, to_string(auton_number) + " " + auton_name);
}

void backwardOne() {
    auton_number -= 1;
    if (auton_number < 1) {
        auton_number = queue_length;
    }
}

void callAuton() {
    if (auton_number == 1) {
        moveP(-12);
        turnP(-38);
        setDriveSpeed(-400);
        delay(700);
        moveP(12);
        turnP(47);
        moveP(10);
        rightWing.set_value(1);
        turnP(45);
        rightWing.set_value(0);
        turnP(-25);
        moveP(35);
        auton_name = "lukeAuton";
        return;
    }
    if (auton_number == 2) {
        nonGoal1();
        auton_name = "nonGoal1";
        return;
    }
    if (auton_number == 3) {
        skills1();
        auton_name = "skills1";
        return;
    }
    if (auton_number == 4) {
        skills2();
        auton_name = "fullShooting";
        return;
    }
    if (auton_number == 5) {
        turnP(-45);
        auton_name = "turnp-45";
    }
    if (auton_number == 6) {
        turnP(90);
        auton_name = "turnp90";
    }
    if (auton_number == 7) {
        turnP(180);
        auton_name = "turnp180";
    }
}
