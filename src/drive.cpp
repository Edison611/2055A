#include "main.h"
#include "pros/colors.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include <cstdlib>
#include <iostream>
#include <string>


// DRIVER CONTROL FUNCTIONS

void setDrive(double left, double right) {
    driveLB.move(left);
    driveLF.move(left);
    driveLM.move(left);
    
    driveRB.move(right);
    driveRM.move(right);
    driveRF.move(right);
}


void setDriveMotors() {

    const int deadband = 5;
    int x = abs(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
    int y = abs(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
    double LjoyY = y/10.0;
    double LjoyX = x/10.0;
    double power = 0;
    double turn = 0;

    if (y > deadband || x > deadband) {
        if (y > 85) {
            power = (12.7 / (1.0 + exp(-(3.0/4.0)*(LjoyY - 6.0)))) * 10.0 - 3.0;
        }
        else if (y > 55 && y <= 85) {
            power = (12.7 / (1.0 + exp(-(3.0/4.0)*(LjoyY - 6.0)))) * 10.0 - 10.0;
        }
        else {
            power = 5*pow((1.0/5.5)*(LjoyY), 3.0) * 12.7;
        }

        if (x > 95) {
            turn = 0.8*(12.7 / (1.0 + exp(-(3.0/4.0)*(LjoyX - 6.0)))) * 10.0 - 3.0;
        }
        else if (x > 55 && x <= 85) {
            turn = 0.35*(12.7 / (1.0 + exp(-(3.0/4.0)*(LjoyX - 6.0)))) * 10.0 - 10.0;
        }
        else {
            turn = 0.6*5*pow((1.0/5.5)*(LjoyX), 3.0) * 12.7;
        }
    }

    if (controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) < 0) {
        power = -power;
    }

    if (controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) < 0) {
        turn = -turn;
    }

    double leftPower = power + turn;
    double rightPower = power - turn;
    setDrive(leftPower, rightPower);

}
