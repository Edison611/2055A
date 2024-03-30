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
    pros::delay(200);
    wingFR.set_value(false);
    driveFwd(24, 4000, 600);
    // ezChassis.drive_angle_set(147);
    /*
    setIntake(127);
    // ezChassis.pid_drive_set(58, 127, false);
    // ezChassis.pid_wait_until(3);
    // wingFR.set_value(false);
    // ezChassis.pid_wait();
    
    // setDrive(600, 600);
    // pros::delay(300);
    // wingFR.set_value(false);
    

    // chassis.moveToPose(-6, 3, 145, 1500);
    // -6 3 145
    // chassis.waitUntilDone();
    
    // chassis.moveToPose(-41, 41, 135, 2000, {.forwards = false});
    // chassis.waitUntilDone();

    // ezChassis.pid_drive_set(-58, 127, false);
    // ezChassis.pid_wait();

    ezChassis.pid_turn_set(214, 127, false);
    ezChassis.pid_wait();
    

    // chassis.moveToPose(-32, 61, 230, 2000, {.forwards = false});
    // chassis.waitUntil(6);
    setIntake(-127);
    pros::delay(1000);
    setIntake(0);
    
    // TEST: chassis.moveToPose(-56, 39, 214, 3000);
    // chassis.waitUntilDone();
    // turnTo(225, 127, 700);
    // setIntake(-127);`
    // pros::delay(300);

       
    // Tri-ball 2
    // chassis.waitUntilDone();
    // turnTo(90);
    ezChassis.pid_turn_set(90, 127, false);
    ezChassis.pid_wait();
    // turnToDir(90, false);
    // chassis.waitUntilDone();
    setIntake(127);
    chassis.moveToPose(3.5, 60, 90, 1400);
    chassis.waitUntilDone();
    pros::delay(100);

    // Tri-ball 3
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
    */
}