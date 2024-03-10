#include "lemlib/asset.hpp"
#include "lemlib/pose.hpp"
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include "pros/vision.h"
#include <cmath>
#include <string>
#include <sys/_intsup.h>


void offense_auton_max_potential() {
    currentIntake = true;
    intake_up.set_value(true);

    // Tri-ball 1
    chassis.setPose(-41, 57, 145);
    wingFR.set_value(true);
    setIntake(127);
    setDrive(600, 600);
    pros::delay(300);
    wingFR.set_value(false);
    setDrive(0, 0);
    // chassis.moveToPose(-13, 0, 145, 1500, {.minSpeed = 60});
    chassis.moveToPose(-6, 3, 145, 1500, {.minSpeed = 60});
    chassis.waitUntilDone();
    chassis.moveToPose(-36, 58, 180, 2500, {.forwards = false});
    chassis.waitUntilDone();
    turnTo(260);
    setIntake(-127);
    pros::delay(200);

    // Tri-ball 2
    turnTo(140);
    // chassis.waitUntilDone();
    turnTo(80);
    // turnToDir(90, false);
    // chassis.waitUntilDone();
    setIntake(127);
    chassis.moveToPose(5, 60, 90, 1600);
    chassis.waitUntilDone();

    // Tri-ball 3
    chassis.moveToPose(-10, 60, 90, 1000, {.forwards = false});
    chassis.waitUntilDone();
    turnTo(-90);
    // turnToDir(-90, true);
    chassis.moveToPose(-46, 54, 225, 1000);
    chassis.waitUntilDone();
    setIntake(-127);
    wingFR.set_value(true);
    turnTo(180);
    chassis.waitUntilDone();

    // Tri-ball 4
    wingFR.set_value(false);
    chassis.moveToPose(-54, 50, 225, 1000, {.minSpeed = 80}, false);
    turnTo(180);
    wingFR.set_value(false);
    turnTo(220);
    setIntake(-127);
    chassis.moveToPose(-60, 10, 180, 1500, {.minSpeed = 110}, false);
}