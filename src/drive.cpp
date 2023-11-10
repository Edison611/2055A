#include "main.h"
#include "pros/colors.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include <cstdlib>
#include <iostream>
#include <string>


// DRIVER CONTROL FUNCTIONS:

/**
 * @brief Sets motor power to drivebase
 * 
 * @param left The power to give the left side
 * @param right The power to give the right side
 */
void setDrive(double left, double right) {
    if (currentDrivePTO) {
        driveLB.move_velocity(left);
        driveLF.move_velocity(left);
        ptoL1.move_velocity(left);
        ptoL2.move_velocity(left);

        driveRB.move_velocity(right);
        driveRF.move_velocity(right);
        ptoR1.move_velocity(right);
        ptoR2.move_velocity(right);
    }   
    else {
        driveLB.move_velocity(left);
        driveLF.move_velocity(left);
        
        driveRB.move_velocity(right);
        driveRF.move_velocity(right);   
    }
    
    
}
// dkadso
/**
 * @brief Set the Drive Motors object to control the robot using the controller
 * 
 */
void setDriveMotors() {
    const int deadband = 5;
    int x = abs(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
    int y = abs(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
    double LjoyY = y/10.0;
    double LjoyX = x/10.0;
    double power = 0;
    double turn = 0;
    double pTune = 7.5;
    double tTune = 7.5;

    power = exp((abs(y) - 127) * pTune / 1000) * y;
    power = power * 600 / 127;
    turn = (exp(-1 * (tTune/10)) + exp((abs(x) - 127) / 10) * (1 - exp(-1 * (tTune / 10)))) * x;
    turn = turn * 600 / 127;


    // if (y > deadband || x > deadband) {
    //     if (y > 85) {
    //         power = (12.7 / (1.0 + exp(-(3.0/4.0)*(LjoyY - 6.0)))) * 10.0 - 3.0;
    //     }
    //     else if (y > 55 && y <= 85) {
    //         power = (12.7 / (1.0 + exp(-(3.0/4.0)*(LjoyY - 6.0)))) * 10.0 - 10.0;
    //     }
    //     else {
    //         power = 5*pow((1.0/5.5)*(LjoyY), 3.0) * 12.7;
    //     }

    //     if (x > 95) {
    //         turn = 0.6*(12.7 / (1.0 + exp(-(3.0/4.0)*(LjoyX - 6.0)))) * 10.0 - 3.0;
    //     }
    //     else if (x > 55 && x <= 85) {
    //         turn = 0.25*(12.7 / (1.0 + exp(-(3.0/4.0)*(LjoyX - 6.0)))) * 10.0 - 10.0;
    //     }
    //     else {
    //         turn = 0.5*5*pow((1.0/5.5)*(LjoyX), 3.0) * 12.7;
    //     }
    // }

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
