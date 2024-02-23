#include "main.h"

void pid_test() {
    chassis.setPose(0, 0, 0);
    // chassis.moveTo(0, 24, 0, 5000);
    // pros::delay(2000);
    // chassis.moveTo(0, 0, 0, 5000, false, false);
    // pros::delay(20000);
    // chassis.moveTo(0, 48, 0, 5000);
    // pros::delay(2000);
    // chassis.moveTo(0, 0, 0, 5000, false, false);
    // pros::delay(2000);

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