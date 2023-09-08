#include "main.h"


class sensorTL {
    private:
    double initHeading;
    double initRotations;
    double initMotorPositionL;
    double initMotorPositionR;
    double heading;
    double rotations;
    double motorPositionR;
    double motorPositionL;

    public:
    sensorTL();
    void resetTL();
    void updateTL();
    double getPosition();
    double getHeading();
    double getRotation();

};

sensorTL::sensorTL() {
    initHeading = Inr.get_heading();
    initRotations = Inr.get_rotation();
    initMotorPositionL = convertToInches((FL.get_position() + ML.get_position() + BL.get_position()) / 3);
    initMotorPositionR = convertToInches((FR.get_position() + MR.get_position() + BR.get_position()) / 3);
}

void sensorTL::updateTL() {
    heading = Inr.get_heading() - initHeading;
    rotations = Inr.get_rotation() - initRotations;
    if (heading > 360) {
        heading -= 360;
    }
    if (heading < 0) {
        heading = 360 + heading;
    }
}

void sensorTL::resetTL() {
    initHeading = Inr.get_heading();
    initRotations = Inr.get_rotation();
    initMotorPositionL = convertToInches((FL.get_position() + ML.get_position() + BL.get_position()) / 3);
    initMotorPositionR = convertToInches((FR.get_position() + MR.get_position() + BR.get_position()) / 3);
    heading = initHeading;
    rotations = initRotations;
    motorPositionR = initMotorPositionR;
    motorPositionL = initMotorPositionL;
}

double sensorTL::getHeading() {
    return heading;
}

double sensorTL::getRotation() {
    return rotations;
}