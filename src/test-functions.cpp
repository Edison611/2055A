#include "main.h"

void pid_test() {
    chassis.setPose(0, 0, 0);
    chassis.moveToPose(0, 24, 0, 5000);
    allowContinue();
    chassis.moveToPose(0, 0, 0, 5000, {.forwards = false});
    allowContinue();
    chassis.moveToPose(0, 48, 0, 5000);
    allowContinue();
    chassis.moveToPose(0, 0, 0, 5000, {.forwards = false});
    allowContinue();

    turnTo(-90, 127, 1000);
    allowContinue();
    turnTo(0, 127, 1000);
    allowContinue();
    turnTo(90, 127, 1000);
    allowContinue();
    // pros::delay(1500);
    turnTo(0, 127, 1000);
    allowContinue();
    // pros::delay(1500);
    turnTo(180, 127, 1000);
    allowContinue();
}