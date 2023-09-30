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

void nonGoal1() {
  //flip out triball slapper thing
  turnP(-90);
  turnP(-110);
  moveP(25);
  //outtake triball
  //possible slam triball
  turnP(-20);
  moveP(-35);
  turnP(160);
  moveP(25);
  //extend arm to touch elevation bar
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

void scrim1() {
  Controller1.set_text(0,1, "Running Scrim 1");
  moveP(30);
  turnP(100);
  moveP(12);
  //outtake
  moveP(-12);
  turnP(-145);
  //intaking
  moveP(10);
  moveP(-10);
  turnP(145);
  moveP(12);
  //outtake
}