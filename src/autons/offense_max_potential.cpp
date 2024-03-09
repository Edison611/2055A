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

    // Tri-ball 1
    chassis.setPose(-41, 57, 150);
    setIntake(127);
    chassis.moveToPose(-13, 0, 145, 1500, {.minSpeed = 100});
    chassis.waitUntilDone();
    chassis.moveToPose(-34, 55, 180, 1500, {.forwards = false, .minSpeed = 80});
    chassis.waitUntilDone();
    turnTo(260);
    setIntake(-127);
    pros::delay(200);

    // Tri-ball 2
    turnTo(140);
    turnTo(80);
    chassis.waitUntilDone();
    setIntake(127);
    chassis.moveToPose(0, 50, 90, 1600, {.minSpeed = 90});

}