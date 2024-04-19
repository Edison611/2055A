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
    // chassis.setPose(-41, 57, 145);
    chassis.setPose(-42, 58, 147);
    wingFR.set_value(true);
        
    // setDrive(600, 600);
    // pros::delay(300);
    // wingFR.set_value(false);
    

    chassis.moveToPose(/*-6, 3, 145, 1500*/ /*-6, 4, 145, 1500*/ /*-10, 7, 145, 1500*/ -7, 6, 145, 1500);
    chassis.waitUntil(3);
    wingFR.set_value(false);
    // setIntake(-127);
    // chassis.waitUntil(6);
    setIntake(127);
    chassis.waitUntilDone();

    // -7 6 145
    
    chassis.moveToPose(-43, 48, 135, 1500, {.forwards = false});
    chassis.waitUntilDone();

    turnTo(220, 127, 500);

    setIntake(-127);
    
    chassis.moveToPose(-28, 60, 220, 1000, {.forwards = false});
    chassis.waitUntil(3);
    setIntake(127);
    // chassis.waitUntil(6);
    // setIntake(-127);
    // pros::delay(1000);
    // setIntake(127);
    chassis.waitUntilDone();
    
    // TEST: chassis.moveToPose(-56, 39, 214, 3000);
    // chassis.waitUntilDone();
    // turnTo(225, 127, 700);
    // setIntake(-127);`
    // pros::delay(300);

       
    // Tri-ball 2
    // chassis.waitUntilDone();
    // turnTo(90);
    // turnToDir(90, false);
    // chassis.waitUntilDone();
    turnTo(90, 127, 600);
    //setIntake(127);
    chassis.moveToPose(/*3.5*/ 3, 68, 90, 1200);
    chassis.waitUntilDone();
    pros::delay(100);

    chassis.moveToPose(-27, 65, 90, 1200, {.forwards = false});
    chassis.waitUntilDone();
    turnTo(225, 127, 500);

    wingFR.set_value(true);

    chassis.moveToPose(-46, 47, 225, 1000);
    chassis.waitUntilDone();

    turnTo(200, 127, 300);
    wingFR.set_value(false);
    setIntake(-127);

    chassis.moveToPose(-66, -20, 185, 650, {.minSpeed = 90});
    chassis.waitUntilDone();
    chassis.setPose(chassis.getPose().x, 30, chassis.getPose().theta);
    chassis.moveToPose(chassis.getPose().x+3, chassis.getPose().y+12, 180, 600, {.forwards=false});
    chassis.waitUntilDone();
    turnTo(180, 127, 500);
    ram(400, 1);
    // chassis.moveToPose(-63, chassis.getPose().y-40, 180, 1200, {.minSpeed = 110});
    chassis.waitUntilDone();
    chassis.setPose(-60, 30, chassis.getPose().theta);
    
    // Back up
    chassis.moveToPose(-53, 40, 225, 1000, {.forwards=false});
    chassis.waitUntilDone();

    chassis.turnTo(-4, 24, 600);
    setIntake(127);
    chassis.moveToPose(-9, 25, 125, 1400);
    chassis.waitUntilDone(); 
    turnTo(180, 127, 500);
    chassis.moveToPose(-60, -5, 270, 1500);
    chassis.waitUntil(10);
    wingFR.set_value(true);
    setIntake(-127);


    pros::delay(1000000);  

    // .
    chassis.moveToPose(-35.5, 69, 225, 3000);
    chassis.waitUntilDone();

    // pros::delay(1000000);

    // Tri-ball
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
    ram(650, 1);
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
    setIntake(127);
    chassis.turnTo(-4, 24, 700);
    chassis.waitUntilDone();
    chassis.moveToPose(-12, 30, 120, 1000);
    chassis.waitUntilDone();

    // Final 2 Middle Triballs
    
}