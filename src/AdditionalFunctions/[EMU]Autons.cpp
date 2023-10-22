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
  moveP(-12);
  turnP(38);
  setDriveSpeed(-400);
  delay(700);
  moveP(12);
  turnP(-47);
  moveP(10);
  rightWing.set_value(1);
  turnP(-30);
  leftWing.set_value(1);
  rightWing.set_value(0);
  CR.move_velocity(200);
  moveP(40);
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

void skills1() {
  CL.move_velocity(80);
  delay(60000); // 60 seconds of shooting
  turnP(-75);
  moveP(6);
  turnP(-60);
  moveP(70);
  turnP(-45);
  rightWing.set_value(1);
  moveP(24);
  turnP(-45);
  setDriveSpeed(300);
  delay(500);
  setDriveSpeed(-100);
  delay(300);
  setDriveSpeed(300);
  delay(400);
  rightWing.set_value(0);
  moveP(-6);
  turnP(-45);
  moveP(25);
  turnP(150);
  rightWing.set_value(1);
  leftWing.set_value(1);
  setDriveSpeed(400);
  delay(600);
}

void skills2() {
  CL.move_velocity(80);
}

void lukeAuton() {
  setDriveSpeed(-500);
  delay(1000);
  setDriveSpeed(200);
  delay(1000);
  setDriveSpeed(-500);
  delay(1000);
  setDriveSpeed(0);
  }