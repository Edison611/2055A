#include "lemlib/asset.hpp"
#include "lemlib/pose.hpp"
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include "pros/vision.h"
#include <cmath>
#include <string>
#include <sys/_intsup.h>

// 5 Ball
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
    turnTo(200);
    wingFR.set_value(false);
    turnTo(220);
    setIntake(-127);
    chassis.moveToPose(-58, 15, 180, 1400, {.minSpeed = 110}, false);
    //chassis.moveToPose(-60, chassis.getPose().y + 10, 180, 1250, {.forwards = false}, false);
    //chassis.moveToPose(-60, chassis.getPose().y - 10, 180, 1500, {.minSpeed = 127}, false);

    //Middle Denter Tri-Balls
    chassis.setPose(chassis.getPose().x, 32.5, chassis.getPose().theta); 
    chassis.moveToPose(-62, 47.5, 90, 1250, {.forwards = false}, false); //180
    //turnTo(95);
    setIntake(127);
    chassis.moveToPose(-12, 10, 145, 2000, {}, false); //-12, 12
    pros::delay(250);
    turnTo(270);
    ActivateWings(true);
    setIntake(-50);
    chassis.moveToPose(-55, chassis.getPose().y, 270, 2000, {.minSpeed = 110}, false);
    ActivateWings(false);

    //Last Middle Tri-Ball
    chassis.setPose(-45, chassis.getPose().y, -90);
    chassis.moveToPose(-20, 7.5, -90, 1250, {.forwards = false}, false);
    chassis.turnTo(-5, 26, 1000);
    //turnTo(40);
    setIntake(127);
    chassis.moveToPose(-6, 22, 40, 1250, {}, false); //-8, 18
    pros::delay(100);
    chassis.moveToPose(-20, 7.5, -90, 1250, {.forwards = false}, false); //40
    //turnTo(-90);
    setIntake(-50);
    ActivateWings(true);
    chassis.moveToPose(-65, chassis.getPose().y, -90, 2250, {.minSpeed = 120}, false);
    ActivateWings(false);

    //Back-Up   
    chassis.moveToPose(-25, 7.5, -90, 1250, {.forwards = false}, false);
    turnTo(90);
}