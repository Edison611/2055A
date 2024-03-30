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
    turnTo(200); //200
    wingFR.set_value(false);
    turnTo(220);
    setIntake(-127);
    chassis.moveToPose(-58, 10, 180, 1200, {.minSpeed = 110}, false);
    //chassis.moveToPose(-60, chassis.getPose().y + 10, 180, 1250, {.forwards = false}, false);
    //chassis.moveToPose(-60, chassis.getPose().y - 10, 180, 1500, {.minSpeed = 127}, false);

    //Middle Denter Tri-Balls
    chassis.setPose(chassis.getPose().x, 32.5, chassis.getPose().theta); 
    pros::delay(150);
    chassis.moveToPose(-48, 54, 220, 800, {.forwards = false, .minSpeed = 75}, false); //-54, 48
    turnTo(130);
    setIntake(127);
    chassis.moveToPose(0, 12.5, 145, 1500, {.minSpeed = 80}, false); //0, 4, 145
    pros::delay(250);   
    turnTo(270, 50);
    ActivateWings(true);
    setIntake(-50);
    chassis.moveToPose(-55, chassis.getPose().y, 270, 900, {.minSpeed = 120}, false);
    ActivateWings(false);

    //Last Middle Tri-Ball
    chassis.setPose(-40, chassis.getPose().y, -90);
    chassis.moveToPose(-20, chassis.getPose().y, -90, 1200, {.forwards = false, .minSpeed = 80}, false);    
    turnTo(30);
    setIntake(127);
    chassis.moveToPose(-10, 30, 10, 1000, {.minSpeed = 50}, false);
    pros::delay(200);
    turnTo(-75);
    pros::delay(10000000);
    chassis.moveToPose(-45, 48, -60, 1000, {}, false);
    turnTo(-130);
    setIntake(-127);
}