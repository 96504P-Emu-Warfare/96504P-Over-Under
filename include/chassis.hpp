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