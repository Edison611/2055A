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
    setIntake(127);

    chassis.moveToPose(-28, -8, 15, 1250, {.minSpeed = 60});
    chassis.waitUntil(3);
    ActivateWings(false);
    chassis.waitUntilDone();

    chassis.moveToPose(-30, -15, 15, 1200, {.forwards = false}, false);
    turnTo(90);
    pros::delay(200);
    ActivateWings(true);
    chassis.moveToPose(-5, chassis.getPose().y, 90, 1300, {.minSpeed = 120}, false);   

    chassis.setPose(-8, chassis.getPose().y, 90);
    pros::delay(250);   
    ActivateWings(false);
    chassis.moveToPose(-20, chassis.getPose().y, 90, 1200, {.forwards = false}, false);
    turnTo(30);
    pros::delay(200);
    chassis.moveToPose(-44, -54, 30, 1200, {.forwards = false, .maxSpeed = 50}, false); //-42, -52
    turnTo(135);
    pros::delay(200);
    chassis.moveToPoint(-50, -48, 1200, false, 127, false); //-48, -46
    // chassis.moveToPose(-48, -45, 135, 1200, {.forwards = false}, false); //-48, -46
    ActivateWings(true);
    pros::delay(250);
    chassis.moveToPoint(-44, -54, 1200, true, 127, false); //-41, -52
    // chassis.moveToPose(-41, -52, 135, 1200, {}, false); //-41, -52

    
    // chassis.moveToPose(-48, -48, 135, 1500, {.forwards = false}, false);
    // ActivateWings(true);
    // pros::delay(200);

    // chassis.moveToPose(-44, -52, 135, 1500, {.minSpeed = 35}, false);
    // ActivateWings(true);
    pros::delay(1000000);
    turnTo(50);
    ActivateWings(false);   
    pros::delay(250);
    turnTo(105);

    setIntake(-127);
    pros::delay(200);
    chassis.moveToPose(-10, -55, 90, 1500, {}, false); // Change to -5 instead of -15
    pros::delay(250);
    chassis.moveToPose(-45, -55, 90, 2000, {.forwards = false, .minSpeed = 40}, false);

}