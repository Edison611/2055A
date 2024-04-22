#include "lemlib/asset.hpp"
#include "lemlib/pose.hpp"
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include "pros/vision.h"
#include <cmath>
#include <string>
#include <sys/_intsup.h>

ASSET(s1_txt);
ASSET(s2_txt);
ASSET(s3_txt);
void auton_skills() {
    // Initialize settings
    setBrake("hold");

    // inertial_sensor.set_roll(0);
    // inertial_sensor.set_pitch(0);
    chassis.setPose(-47, 59, 230);

    // Score the first 2 Alliance Triballs
    // ------------------------------------------------
    chassis.moveToPose(-64, 10, 180, 1200, {.minSpeed = 90});
    // turnTo(180);
    // ram(400, 1);
    chassis.waitUntilDone();
    chassis.setPose(chassis.getPose().x, 28, chassis.getPose().theta);

    // Line up with the Bar
    // ------------------------------------------------
    chassis.moveToPose(-60, 47, 180, 1000, {.forwards = false});
    turnTo(107);
    pros::delay(2000);
    chassis.setPose(-60, 47, 107);

    // Wedge Triballs Over the Bar
    // ------------------------------------------------
    chassis.moveToPoint(-22, 31.5, 800);
    chassis.waitUntil(30);
    wingFL.set_value(true);
    chassis.waitUntilDone();
    turnTo(180);
    ActivateWings(true);
    chassis.moveToPose(chassis.getPose().x, chassis.getPose().y - 60, 180, 2000, {.minSpeed = 90});
    chassis.waitUntilDone();
    liftRam();
    wingFR.set_value(false);
    chassis.moveToPose(chassis.getPose().x, chassis.getPose().y-15, 180, 1000);
    chassis.waitUntilDone();
    liftRam();
    wingFL.set_value(false);

    // Jerryio Curve To Cross Under the Tunnel
    // ------------------------------------------------
    turnTo(-100);
    chassis.setPose(-16, -35, chassis.getPose().theta);
    chassis.follow(s2_txt, 15, 3000);
    chassis.waitUntil(26);
    wingFR.set_value(true);
    chassis.waitUntil(50);
    wingFR.set_value(false);
    chassis.waitUntilDone();
    wallReset("bottom", "right");

    // Get Corner Triball Out
    // ------------------------------------------------
    chassis.moveToPose(60, -45, 45, 1500);
    chassis.waitUntil(10);
    wingFR.set_value(true);
    chassis.waitUntilDone();
    turnTo(-10);

    // Right Side Pushes
    // ------------------------------------------------
    wingFR.set_value(false);
    // driveFwd(-5, 1000, 127);
    wingFL.set_value(true);
    chassis.moveToPose(63, -10, 0, 1000);
    chassis.waitUntilDone();
    wingFL.set_value(false);
    chassis.moveToPose(chassis.getPose().x-10, chassis.getPose().y-10, 0, 900, {.forwards=false});
    chassis.waitUntilDone();
    turnTo(0);
    ram(400, 1);
    chassis.setPose(chassis.getPose().x, -28, chassis.getPose().theta);
    wallReset("right", "right");

    // Middle Push #1
    // ------------------------------------------------
    chassis.follow(s3_txt, 30, 3000);



}