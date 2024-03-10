#include "lemlib/asset.hpp"
#include "lemlib/pose.hpp"
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include "pros/vision.h"
#include <cmath>
#include <string>
#include <sys/_intsup.h>

void offense_auton_safe() {
    //Alliance Tri-ball and Corner Tri-ball

    currentIntake = true;
    intake_up.set_value(true);

    chassis.setPose(-46, 58, 225);
    //DROP INTAKE
    wingFR.set_value(true);
    setIntake(127);
    pros::delay(250);
    chassis.moveToPose(-54, 50, 225, 1000, {.minSpeed = 80}, false);
    turnTo(180);
    wingFR.set_value(false);
    turnTo(220);
    setIntake(-127);
    chassis.moveToPose(-58, 10, 180, 1500, {.minSpeed = 110}, false);
    //chassis.moveToPose(-60, chassis.getPose().y + 15, 180, 1250, {.forwards = false}, false);
    // chassis.moveToPose(-60, chassis.getPose().y - 15, 180, 1500, {.minSpeed = 127}, false);

    //Middle Tri-Balls
    chassis.setPose(-58, 32.5, 180);
    chassis.moveToPose(-58, 45, 180, 1250, {.forwards = false}, false);
    turnTo(100);
    chassis.moveToPose(-10, 10, 140, 2000, {.minSpeed = 80}, false);

}