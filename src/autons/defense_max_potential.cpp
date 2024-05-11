#include "lemlib/asset.hpp"
#include "lemlib/pose.hpp"
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include "pros/vision.h"
#include <cmath>
#include <string>
#include <sys/_intsup.h>

void defense_auton_max_potential() {
    chassis.setPose(-48, -56, 134);
    // ezChassis.drive_angle_set(134);
    // setIntake(127);
    setIntake(127);
    intake_up.set_value(true);
    currentIntake = true;
    chassis.moveToPose(-53, -51, 134, 1200, {.forwards=false});
    chassis.waitUntilDone();
    wingFR.set_value(true);
    pros::delay(250);
    chassis.moveToPose(-50, -54, 134, 1200);
    chassis.waitUntilDone();
    setIntake(0);
    pros::delay(300);
    turnTo(60);
    pros::delay(250);
    wingFR.set_value(false);

    setIntake(127);

    chassis.moveToPose(-33, -8, 10, 3100);
    chassis.waitUntilDone();

    pros::delay(250); //1000

    chassis.moveToPose(-42, -70, 0, 2000, {.forwards=false});
    chassis.waitUntilDone();

    // ezChassis.drive_angle_set(0);

    // ezChassis.pid_drive_set(-48, 127, false, true);
    // ezChassis.pid_wait();
    // ezChassis.
    chassis.setPose(chassis.getPose().x, -60, 0);
    pros::delay(10);

    // turnTo(-120);
    chassis.moveToPose(chassis.getPose().x, -57, 0, 750);
    turnTo(90);

    // ezChassis.pid_turn_set(70, 127, false);
    // ezChassis.pid_wait();
    setIntake(-127);

    chassis.moveToPose(-13, -57, 90, 5100, {.maxSpeed=90}); //-9, -60, 90
    pros::delay(2000);
    setIntake(0);

}