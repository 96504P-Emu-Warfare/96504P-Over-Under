#include "main.h"


class sensorTL {
    private:
    double initHeading;
    double initRotations;
    double initMotorPositionL;
    double initMotorPositionR;
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
    initMotorPositionL = convertToInches((FL.get_position() + ML.get_position + BL.get_position) / 3);
    initMotorPositionR = convertToInches((FR.get_position() + MR.get_position + BR.get_position) / 3);
}

sensorTL::updateTL() {
    heading = Inr.get_heading() - initHeading;
    rotations = initRotations + Inr.get_rotation() initHeading;
    if (heading > 360) {
        heading -= 360;
    }
    if (heading < 0) {
        heading = 360 + heading;
    }
}

sensorTL::resetTL() {
    initHeading = Inr.get_heading();
    initRotations = Inr.get_rotation();
    initMotorPositionL = convertToInches((FL.get_position() + ML.get_position + BL.get_position) / 3);
    initMotorPositionR = convertToInches((FR.get_position() + MR.get_position + BR.get_position) / 3);
    heading = initHeading;
    rotations = initRotations;
    motorPositionR = initMotorPositionR;
    motorPositionL = initMotorPositionL;
}

sensorTL::getHeading() {
    return heading;
}

sensorTL::getRotation() {
    return rotations;
}