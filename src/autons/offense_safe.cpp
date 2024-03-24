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
    turnTo(200);
    wingFR.set_value(false);
    turnTo(220);
    setIntake(-127);
    chassis.moveToPose(-58, 15, 180, 1200, {.minSpeed = 110}, false);
    //chassis.moveToPose(-60, chassis.getPose().y + 10, 180, 1250, {.forwards = false}, false);
    //chassis.moveToPose(-60, chassis.getPose().y - 10, 180, 1500, {.minSpeed = 127}, false);

    //Middle Denter Tri-Balls
    chassis.setPose(chassis.getPose().x, 32.5, chassis.getPose().theta); 
    pros::delay(150);
    chassis.moveToPose(-54, 48, 220, 1000, {.forwards = false}, false); 
    turnTo(115);
    setIntake(127);
    chassis.moveToPose(0, 4, 145, 1750, {.minSpeed = 80}, false); //-8
    pros::delay(100);   
    turnTo(270);
    ActivateWings(true);
    setIntake(-50);
    chassis.moveToPose(-55, chassis.getPose().y, 270, 1000, {.minSpeed = 120}, false);
    ActivateWings(false);

    //Last Middle Tri-Ball
    chassis.setPose(-40, chassis.getPose().y, -90);
    chassis.moveToPose(-20, 7.5, -90, 1250, {.forwards = false}, false);    
    chassis.turnTo(-5, 26, 750);
    //turnTo(40);
    setIntake(127);
    chassis.moveToPose(-8, 32, 0, 1250, {}, false); //-6, 90, 20
    pros::delay(100);
    chassis.moveToPose(-20, 7.5, 40, 1250, {.forwards = false}, false); //40
    turnTo(-90);
    setIntake(-50);
    ActivateWings(true);
    chassis.moveToPose(-65, chassis.getPose().y, -90, 1000, {.minSpeed = 120}, false);
    ActivateWings(false);

    //Back-Up   
    chassis.moveToPose(-25, 7.5, -90, 1250, {.forwards = false}, false);
    turnTo(90);
}