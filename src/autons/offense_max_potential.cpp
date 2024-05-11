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
    setIntake(127);
    wingFR.set_value(true);
        
    // setDrive(600, 600);
    // pros::delay(300);
    // wingFR.set_value(false);
    

    chassis.moveToPose(/*-6, 3, 145, 1500*/ /*-6, 4, 145, 1500*/ /*-10, 7, 145, 1500*/ /*-7, 6, 145, 1500*/ -6, 6, 145, 1500, {.minSpeed = 80}); // rush to middle triball
    chassis.waitUntil(3);
    wingFR.set_value(false);
    // setIntake(-127);
    // chassis.waitUntil(6);
    chassis.waitUntilDone();

    // -7 6 145
    
    chassis.moveToPose(-43, 48, 135, 1300, {.forwards = false, .minSpeed = 60}); // go back
    chassis.waitUntilDone();

    turnTo(230, 127, 400); // face the net so triball can be outtaked towards the net

    setIntake(-127);
    
    chassis.moveToPose(-28, 63, 230, 1000, {.forwards = false}); // head towards 3rd triball
    // chassis.waitUntil(3);
    // setIntake(127);
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
    turnTo(80, 127, 500);
    setIntake(127);
    //setIntake(127);
    chassis.moveToPose(/*3.5*/ 7, 66, 90, 1200); // get third triball
    chassis.waitUntilDone();

    chassis.moveToPose(-30, 62, 90, 1200, {.forwards = false}); // go back
    chassis.waitUntilDone();
    turnTo(225, 127, 500); // turn so parallel to matchload bar

    wingFR.set_value(true);

    // chassis.moveToPose(-46, 47, 225, 1000);
    chassis.moveToPose(-62, 40, 225, 900); // moves forward parallel to matchload bar with wing open
    chassis.waitUntilDone();

    // turnTo(200, 127, 300);
    turnTo(160, 127, 350); // turn to smack triball out of corner
    wingFR.set_value(false);

    turnTo(190, 127, 250); // tunr to net
    setIntake(-127);

    chassis.moveToPose(-52, -20, 180, 650, {.minSpeed = 120}); // RAM 1
    chassis.waitUntilDone();
    chassis.setPose(chassis.getPose().x, 30, chassis.getPose().theta);
    turnTo(165, 127, 300);
    chassis.moveToPose(chassis.getPose().x-3, chassis.getPose().y+18, 180, 600, {.forwards=false}); // go back
    // chassis.moveToPose(-57, 45, 190, 2000, {.forwards=false});
    // chassis.moveToPose(-56, 46, 180, 1500, {.forwards=false});
    chassis.waitUntilDone();
    turnTo(190, 127, 250);
    ram(400, 1); // RAM 2
    // chassis.moveToPose(-63, chassis.getPose().y-40, 180, 1200, {.minSpeed = 110});
    chassis.waitUntilDone();
    chassis.setPose(-60, 30, chassis.getPose().theta);
    
    // Back up
    chassis.moveToPose(-53, 40, 225, 700, {.forwards=false});
    chassis.waitUntilDone();

    // Last 2
    chassis.turnTo(-4, 24, 550);
    setIntake(127);
    chassis.moveToPose(-5, 24, 125, 900, {.minSpeed = 80});
    chassis.waitUntilDone(); 
    turnTo(180, 127, 400);
    chassis.moveToPose(-18, 3, 200, 800, {.minSpeed = 70});
    chassis.waitUntilDone();
    wingFR.set_value(true);
    turnTo(272, 127, 400);
    setIntake(-127);
    ram(500, 1);
    chassis.moveToPose(chassis.getPose().x-15, 5, 270, 800, {.forwards=false});
    chassis.waitUntilDone();
    wingFR.set_value(false);
    

    // pros::delay(1000000);  

    // chassis.moveToPose(-35.5, 69, 225, 3000);
    // chassis.waitUntilDone();

    // pros::delay(1000000);

    // Tri-ball
    // chassis.moveToPose(-33, 60, 90, 1300, {.forwards = false});
    // chassis.waitUntilDone();
    // // chassis.setPose(-40, chassis.getPose().y, chassis.getPose().theta);
    // turnTo(225);
    // // turnToDir(-90, true);
    // chassis.moveToPose(-58, 45, 225, 1000);
    // chassis.waitUntil(5);
    // wingFR.set_value(true);
    // chassis.waitUntilDone();
    // turnTo(180);
    // wingFR.set_value(false);
    // setIntake(-127);

    // // 2 Rams to get Triballs #1-4
    // // chassis.moveToPose(-57, -10, 180, 1500, {.minSpeed = 110});
    // ram(650, 1);
    // chassis.waitUntilDone();
    // chassis.setPose(chassis.getPose().x, 30, chassis.getPose().theta);
    // chassis.moveToPose(chassis.getPose().x, chassis.getPose().y+10, 180, 650, {.forwards=false});
    // chassis.waitUntilDone();
    // turnTo(190);
    // ram(500, 1);
    // // chassis.moveToPose(-63, chassis.getPose().y-40, 180, 1200, {.minSpeed = 110});
    // chassis.waitUntilDone();
    // chassis.setPose(-60, 30, chassis.getPose().theta);
    // chassis.moveToPose(-57, 46, 225, 1000, {.forwards=false});
    // chassis.waitUntilDone();
    // setIntake(127);
    // chassis.turnTo(-4, 24, 700);
    // chassis.waitUntilDone();
    // chassis.moveToPose(-12, 30, 120, 1000);
    // chassis.waitUntilDone();

    // Final 2 Middle Triballs
    
}