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
    // setDrive(0, 0);
    // chassis.moveToPose(-13, 0, 145, 1500, {.minSpeed = 60});
    chassis.moveToPose(-6, 3, 145, 1500);
    // -6 3 145
    chassis.waitUntilDone();
    // driveFwd(-55, 1500, 127);

    chassis.moveToPose(-32, 61, 180, 2000, {.forwards = false});
    chassis.waitUntilDone();
    turnTo(225, 127, 700);
    setIntake(-127);
    pros::delay(300);

    // Tri-ball 2
    // chassis.waitUntilDone();
    turnTo(70);
    // turnToDir(90, false);
    // chassis.waitUntilDone();
    setIntake(127);
    chassis.moveToPose(3.5, 65, 90, 1400);
    chassis.waitUntilDone();
    pros::delay(100);

    // Tri-ball 3
    chassis.moveToPose(-33, 60, 90, 1300, {.forwards = false});
    chassis.waitUntilDone();
    // chassis.setPose(-40, chassis.getPose().y, chassis.getPose().theta);
    turnTo(225);
    // turnToDir(-90, true);
    chassis.moveToPose(-58, 45, 225, 1000);
    chassis.waitUntil(5);
    wingFR.set_value(true);
    chassis.waitUntilDone();
    turnTo(180);
    wingFR.set_value(false);
    setIntake(-127);

    // 2 Rams to get Triballs #1-4
    // chassis.moveToPose(-57, -10, 180, 1500, {.minSpeed = 110});
    ram(750, 1);
    chassis.waitUntilDone();
    chassis.setPose(chassis.getPose().x, 30, chassis.getPose().theta);
    chassis.moveToPose(chassis.getPose().x, chassis.getPose().y+10, 180, 650, {.forwards=false});
    chassis.waitUntilDone();
    turnTo(190);
    ram(500, 1);
    // chassis.moveToPose(-63, chassis.getPose().y-40, 180, 1200, {.minSpeed = 110});
    chassis.waitUntilDone();
    chassis.setPose(-60, 30, chassis.getPose().theta);
    chassis.moveToPose(-57, 46, 225, 1000, {.forwards=false});
    chassis.waitUntilDone();

    // Final 2 Middle Triballs

}