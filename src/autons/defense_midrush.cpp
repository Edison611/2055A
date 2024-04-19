#include "lemlib/asset.hpp"
#include "lemlib/pose.hpp"
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include "pros/vision.h"
#include <cmath>
#include <string>
#include <sys/_intsup.h>

void defense_auton_midrush() {
    currentIntake = true;
    intake_up.set_value(true);

    chassis.setPose(-40, -56, 15);
    ActivateWings(true);

    chassis.moveToPose(-28.5, -10, 15, 1250);
    chassis.waitUntil(3);
    ActivateWings(false);
    setIntake(127);
    chassis.waitUntilDone();

    pros::delay(250);
    chassis.moveToPose(-29, -12, 15, 1000, {.forwards = false}, false);
    turnTo(90);
    pros::delay(250);
    ActivateWings(true);
    chassis.moveToPose(-5, chassis.getPose().y, 90, 1300, {.minSpeed = 115}, false);   

    chassis.setPose(-8, -12, 90);
    pros::delay(200);
    ActivateWings(false);
    chassis.moveToPose(-23, -12, 90, 1200, {.forwards = false}, false);
    turnTo(30);
    pros::delay(200);
    chassis.moveToPose(-44, -54, 30, 1200, {.forwards = false}, false);
    turnTo(135);
    pros::delay(200);
    
    chassis.moveToPose(-48, -50, 135, 1000, {.forwards = false}, false);
    ActivateWings(true);
    pros::delay(200);
    chassis.moveToPose(-42, -56, 110, 1000, {}, false);
    // pros::delay(200);
    chassis.moveToPose(-48, -50, 135, 1000, {.forwards = false}, false);
    ActivateWings(false);
    // pros::delay(200);
    chassis.moveToPose(-40, -58, 135, 1000, {}, false);

    turnTo(90);
    setIntake(-127);
    chassis.moveToPose(-15, -58, 90, 1200, {}, false);
    pros::delay(200);
    chassis.moveToPose(-45, -58, 90, 1200, {.forwards = false}, false);

}