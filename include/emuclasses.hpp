#pragma once

class drivetrain {
    private:
        double heading;
        double newDistance;
        double xPos;
        double yPos;
        double posArray[2];

    public: 
        drivetrain(int portML, int portMR);
        double getCenterPosition();
        void updatePos();
        double getXPos();
        double getYPos();
        double getAngle();
        void motorsStop();
        void setDriveSpeed(double power);
        void setDriveSpeed(double power, std::string leftOrRight);
};

void updatePosTask();

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
        sensorTL(void);
        void resetTL();
        void updateTL();
        double getPosition();
        double getHeading();
        double getRotation();
};

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
