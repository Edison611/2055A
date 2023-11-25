/**
 * @file subsystems.cpp
 * @author 2055A Team
 * @brief Create all the subsystems features in this file
 * @version 0.1
 * @date 2023-07-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "main.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include <string>

// ------------------------------------------------------------------------------------------------------
bool currentDrivePTO = false; // This means that puncher is active when it is false
void DrivePTO() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
        if (currentDrivePTO == false) {
            currentDrivePTO = true;
            while (puncher_rot.get_angle() < 25000) {
                setPTO(-600, -600, -600, -600);
                pros::delay(20);
            }
            setPTO(0, 0, 0, 0);
            pros::delay(100);
            drivePTO.set_value(true);
            controller.print(1,1,"drive");
            ptoL1.set_brake_mode(MOTOR_BRAKE_COAST);
            ptoL2.set_brake_mode(MOTOR_BRAKE_COAST);

            ptoR1.set_brake_mode(MOTOR_BRAKE_COAST);
            ptoR2.set_brake_mode(MOTOR_BRAKE_COAST);
        }
        
        else if (currentDrivePTO == true) {
            currentDrivePTO = false;
            drivePTO.set_value(false);
            
            controller.print(1,1,"puncher");

            ptoL1.set_brake_mode(MOTOR_BRAKE_COAST);
            ptoL2.set_brake_mode(MOTOR_BRAKE_COAST);

            ptoR1.set_brake_mode(MOTOR_BRAKE_COAST);
            ptoR2.set_brake_mode(MOTOR_BRAKE_COAST);
            pros::delay(500);
            // cata_shoot = true;
        }
        controller.rumble(".");
    }
}

void setPTO(int L1, int L2, int R1, int R2) {
    ptoL1.move_velocity(L1);
    ptoL2.move_velocity(L2);
    ptoR1.move_velocity(R1);
    ptoR2.move_velocity(R2);
}

void Puncher() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        // ptoR1.set_brake_mode(MOTOR_BRAKE_HOLD);
        // ptoR2.set_brake_mode(MOTOR_BRAKE_HOLD);

        // ptoL1.set_brake_mode(MOTOR_BRAKE_HOLD);
        // ptoL2.set_brake_mode(MOTOR_BRAKE_HOLD);
        
        // ptoL1.move(-127);
        // ptoL2.move(-127);
        // ptoR1.move(127);
        // ptoR2.move(127);
    // } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
    //     ptoR1.set_brake_mode(MOTOR_BRAKE_HOLD);
    //     ptoR2.set_brake_mode(MOTOR_BRAKE_HOLD);

    //     ptoL1.set_brake_mode(MOTOR_BRAKE_HOLD);
    //     ptoL2.set_brake_mode(MOTOR_BRAKE_HOLD);

    //     ptoL1.move(127);
    //     ptoL2.move(127);
    //     ptoR1.move(-127);
    //     ptoR2.move(-127);
    }
    // else {
    //     ptoL1.move(0);
    //     ptoL2.move(0);
    //     ptoR1.move(0);
    //     ptoR2.move(0);
    // }
}


// ------------------------------------------------------------------------------------------------------
// CATAPULT
// ------------------------------------------------------------------------------------------------------
void setCatapult(int power) {
    catapult.move(power);
} 

bool hold = false;
bool cata_shoot = false;

void setCatapultMotors() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1) == 1) {
        cata_shoot = true;
    }
}

void shoot() {
    cata_shoot = true;
}

/**
 * A task to hold the catapult in place.
 * Tune the factor variable to let the catapult sit in place.
 */
void cata_hold() { ///

    // double factor = 9.25; // Tune this value
    // int x = 0;
    bool stop = true;

	while (true) {

        while (puncher_rot.get_angle() < 17500) { // Could change to adjust button value
            // pros::lcd::set_text(1, "REACHED");
            if (stop == true) {
                setPTO(0, 0, 0, 0);
                stop = false;
            }

            if (cata_shoot == true) {
                cata_shoot = true;
                break;
            }
        }

        // while (currentDrivePTO == true) {
        //     pros::delay(20);
        // }

        if (cata_shoot == true) {
            // pros::lcd::set_text(2, "Shoot");
            cata_shoot = false;
            setPTO(-600, -600, -600, -600);
            stop = true;
            pros::delay(300);
        }

        
        pros::delay(20);

	}
    
}





// ------------------------------------------------------------------------------------------------------
// GRABBER (OLD)
// ------------------------------------------------------------------------------------------------------
// bool currentGrabber = false;

// /**
//  * @brief Controls the grabber of the bot, drops if it was up, pulls it up if it is dropped on button press.
//  */
// void SetGrabber() {
//     if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
//         if (currentGrabber == false) {
//             currentGrabber = true;
//             grabber.set_value(true);
//         }
//         else if (currentGrabber == true) {
//             currentGrabber = false;
//             grabber.set_value(false);
//         }
//     }
// }

// ------------------------------------------------------------------------------------------------------
// WINGS
// ------------------------------------------------------------------------------------------------------

void ActivateWings(bool dir) {
    wingR.set_value(dir);
    wingL.set_value(dir);

}

/**
 * @brief Manually rams the robot. 
 */
void ram(int time, int dir=1) {
    setDrive(600*dir, 600*dir);
    pros::delay(time);
    setDrive(0, 0);
}

bool currentWings = false;

/**
 * @brief Controls the wings of the bot, opens if it was closed, closes if it is open on button press.
 */
void op_wings() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        currentWings = !currentWings;
        wingR.set_value(currentWings);
        wingL.set_value(currentWings);

    }
}


bool currentClaw = false;

/**
 * @brief Controls the grabber of the bot, drops if it was up, pulls it up if it is dropped on button press.
 */

void op_claw() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
        currentClaw = !currentClaw;
        claw.set_value(currentClaw);

        // if (currentClaw == false) {
        //     currentClaw = true;
        //     claw.set_value(true);
        // }
        
        // else if (currentClaw == true) {
        //     currentClaw = false;
        //     claw.set_value(false);
        // }
    }
}


bool currentBlocker = false;

/**
 * @brief Controls the blocker of the bot. On button press, it pulls it up if it is dropped, and drops it if it was up.
 */

void op_blocker() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        currentBlocker = !currentBlocker;
        blocker.set_value(currentBlocker);
    }
}


// ------------------------------------------------------------------------------------------------------
