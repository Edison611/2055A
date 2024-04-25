#include "lemlib/asset.hpp"
#include "lemlib/pose.hpp"
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include "pros/vision.h"
#include <cmath>
#include <string>
#include <sys/_intsup.h>

void defense_awp() {
    chassis.setPose(-48, -56, 134);
    setIntake(127);
    
    chassis.moveToPose(-53, -51, 134, 1200, {.forwards=false});
    chassis.waitUntilDone();
    intake_up.set_value(true);
    currentIntake = true;
    wingFR.set_value(true);
    pros::delay(250);
    chassis.moveToPose(-50, -54, 134, 1200);
    chassis.waitUntilDone();
    pros::delay(300);
    turnTo(100);
    pros::delay(250);
    wingFR.set_value(false);
    pros::delay(250);
    chassis.moveToPose(-9, -61, 90, 5100, {.maxSpeed=90});
    setIntake(-127);
    chassis.waitUntilDone();
    pros::delay(500);
    setIntake(0);
}