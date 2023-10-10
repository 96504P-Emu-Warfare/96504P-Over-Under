/**************************************************************
         AUTONOMOUSES / AUTONOMISES / AUTONOMI

Where all the autonomous code is housed, including 
Skills

The selection of autons is:
 - Nothing yet, come back later

Created 6/17/23
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

void nonGoal1() {
  Controller1.set_text(0,0, "NG1");
  moveP(-9);
  // flip out wing
  moveP(14);
  turnP(-155);
  moveP(22);
  turnP(30);
  //CR.move_velocity(200);
  delay(1000);
  //CR.move_velocity(0);
  moveP(3);
  turnP(-45);
  moveP(-28);
  turnP(-45);
  moveP(-33);
}

void goal1() {
  //flip out triball slapper thing
  turnP(90);
  turnP(-110);
  moveP(24);
  //outtake triball
  //possibly slam triball
  turnP(20);
  moveP(-30);
  turnP(-120);
  moveP(30);
  //extend arm to touch elevation bar
}