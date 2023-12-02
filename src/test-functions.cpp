#include "main.h"

void pid_test() {
    chassis.setPose(0, 0, 0);
    chassis.moveTo(0, 24, 0, 4000);
    allowContinue();
    chassis.moveTo(0, 0, 0, 4000, false, false);
    allowContinue();
    chassis.moveTo(0, 48, 0, 4000);
    allowContinue();
    chassis.moveTo(0, 0, 0, 4000, false, false);
    allowContinue();

    turnTo(-45);
    // chassis.turnTo(-24, 0, 800);
    allowContinue();
    chassis.moveTo(-24, 24, -45, 4000);
    allowContinue();
}