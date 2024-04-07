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
    pros::delay(150);
    chassis.moveToPose(-54, 50, 225, 1000, {.minSpeed = 80}, false);
    turnTo(205); 
    wingFR.set_value(false);
    turnTo(220);
    setIntake(-127);
    chassis.moveToPose(-58, 10, 180, 1000, {.minSpeed = 115}, false);
    //chassis.moveToPose(-60, chassis.getPose().y + 10, 180, 1250, {.forwards = false}, false);
    //chassis.moveToPose(-60, chassis.getPose().y - 10, 180, 1500, {.minSpeed = 127}, false);
    //Middle Denter Tri-Balls
    chassis.setPose(chassis.getPose().x, 32.5, chassis.getPose().theta); 
    pros::delay(150);
    chassis.moveToPose(-48, 54, 220, 800, {.forwards = false, .minSpeed = 75}, false); //-54, 48
    turnTo(130);
    setIntake(127);
    chassis.moveToPose(0, 8, 140, 1400, {.chasePower = 4}, false); 
    pros::delay(250);   
    turnTo(270, 50);
    ActivateWings(true);
    setIntake(-50);
    chassis.moveToPose(-55, chassis.getPose().y, 270, 850, {.minSpeed = 120}, false);
    ActivateWings(false);

    //Last Middle Tri-Ball
    chassis.setPose(-40, chassis.getPose().y, -90);
    chassis.moveToPose(-20, chassis.getPose().y, -90, 1200, {.forwards = false, .minSpeed = 80}, false);    
    turnTo(30);
    setIntake(127);
    pros::delay(200);
    // chassis.moveToPose(-7, 23, 30, 1000, {.chasePower = 4}, false);
    chassis.moveToPose(-10, 25, 50, 1000, {.chasePower = 4}, false);

    //Last Middle Ram
    turnTo(-57.5);
    pros::delay(250);
    chassis.moveToPose(-52, 52, -57.5, 1400, {.minSpeed = 80}, false);
    turnTo(-135);
    pros::delay(250);
    setIntake(-127);
    chassis.moveToPose(-58, 10, 180, 1000, {.minSpeed = 115}, false);
    chassis.moveToPose(-60, chassis.getPose().y + 20, -180, 1000, {.forwards = false, .minSpeed = 50}, false);
    turnTo(-250);
}