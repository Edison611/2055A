#include "main.h"

void pid_test() {
    chassis.setPose(0, 0, 0);
    chassis.moveToPose(0, 24, 0, 4000);
    allowContinue();
    chassis.moveToPose(0, 0, 0, 4000, {.forwards = false});
    allowContinue();
    chassis.moveToPose(0, 48, 0, 4000);
    allowContinue();
    chassis.moveToPose(0, 0, 0, 4000, {.forwards = false});
    allowContinue();

    turnTo(-45);
    // chassis.turnTo(-24, 0, 800);
    allowContinue();
    chassis.moveToPose(-24, 24, -45, 4000);
    allowContinue();
}