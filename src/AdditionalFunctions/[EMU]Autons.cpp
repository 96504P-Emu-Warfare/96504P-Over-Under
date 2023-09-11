/**************************************************************
         AUTONOMOUSES / AUTONOMISES / AUTONOMI

Where all the autonomous code is housed, including 
Skills

The selection of autons is:
 - Nothing yet, come back later

Created 6/17/23
Last update 6/18/23

****************************************************************/
#include "main.h"

sensorTL autonTL;

void moveTest() {
  moveP(12);
  delay(100);
  moveP(-12);
}

void turnTest() {
  turnP(90);
  delay(1000);
  turnP(-90);
  delay(100);
  turnP(180);
}