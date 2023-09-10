#include "main.h"

class autonSystem {
    private:
        int auton_number;
        int queue_length;
    public:
        autonSystem(int defaultchoice, int queuesize);
        void setAutonNumber(int number);
        void forwardOne();
        void backwardOne();
        void callAuton();
};

autonSystem::autonSystem(int defaultchoice, int queuesize) {
    auton_number =  defaultchoice;
    queue_length = queuesize;
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
    }
    if (auton_number == 2) {
        turnTest();
    }
    else {
        return;
    }
}