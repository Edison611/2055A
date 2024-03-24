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
    setIntake(127);
    
    chassis.moveToPose(-53, -51, 134, 1200, {.forwards=false});
    chassis.waitUntilDone();
    intake_up.set_value(true);
    currentIntake = true;
    wingFR.set_value(true);
    pros::delay(250);
    chassis.moveToPose(-50, -54, 134, 1200);
    chassis.waitUntilDone();
    pros::delay(300);
    turnTo(60);
    pros::delay(250);
    wingFR.set_value(false);

    setIntake(127);

    chassis.moveToPose(-27, -6, 20, 3100);
    chassis.waitUntilDone();

    ezChassis.drive_angle_set(0);

    ezChassis.pid_drive_set(-48, 127, true);
    ezChassis.pid_wait();
    ezChassis.pid_drive_set(0, 127, false);
    ezChassis.pid_wait();

    turnTo(90);

    // ezChassis.pid_turn_set(70, 127, false);
    // ezChassis.pid_wait();

    chassis.moveToPose(-11.5, -61, 90, 5100, {.maxSpeed=90});
    setIntake(-127);
    pros::delay(2000);
    setIntake(0);




}