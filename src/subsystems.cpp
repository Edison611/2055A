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
bool currentDrivePTO = false;
void DrivePTO() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        if (currentDrivePTO == false) {
            // if (abs(ptoL1.get_actual_velocity()) > 0) 
            currentDrivePTO = true;
            drivePTO.set_value(true);
            // cata_shoot = true;

            ptoL1.set_brake_mode(MOTOR_BRAKE_COAST);
            ptoL2.set_brake_mode(MOTOR_BRAKE_COAST);

            ptoR1.set_brake_mode(MOTOR_BRAKE_COAST);
            ptoR2.set_brake_mode(MOTOR_BRAKE_COAST);
        }
        
        else if (currentDrivePTO == true) {
            currentDrivePTO = false;
            drivePTO.set_value(false);
            

            ptoL1.set_brake_mode(MOTOR_BRAKE_COAST);
            ptoL2.set_brake_mode(MOTOR_BRAKE_COAST);

            ptoR1.set_brake_mode(MOTOR_BRAKE_COAST);
            ptoR2.set_brake_mode(MOTOR_BRAKE_COAST);
            pros::delay(500);
            cata_shoot = true;
        }
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
        ptoR1.set_brake_mode(MOTOR_BRAKE_HOLD);
        ptoR2.set_brake_mode(MOTOR_BRAKE_HOLD);

        ptoL1.set_brake_mode(MOTOR_BRAKE_HOLD);
        ptoL2.set_brake_mode(MOTOR_BRAKE_HOLD);
        
        ptoL1.move(-127);
        ptoL2.move(-127);
        ptoR1.move(127);
        ptoR2.move(127);
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
bool cata_shoot = true;

void setCatapultMotors() {
    if (cata_limit_switch.get_value() == 1) {
        hold = true;
    }
    // pros::lcd::set_text(3, "Limit Switch: " + std::to_string(limit_switch.get_value()));
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1) == 1) {
        hold = false;
        // Shoot Catapult
        // setPTO(-600, -600, -600, -600);
        // setCatapult(127);
        pros::delay(250);
        // setCatapult(127);
    }
}

void shoot() {
    cata_shoot = true;
}

/**
 * A task to hold the catapult in place.
 * Tune the factor variable to let the catapult sit in place.
 */
void cata_hold() {

    double factor = 9.25; // Tune this value
    int x = 0;

	while (true) {

        // while (cata_limit_switch.get_value() == 1) { // Could change to just button value
        //     pros::lcd::set_text(1, "TEST");
        //     setPTO(0, 0, 0, 0);
        //     // int x = x + 1;
        //     // int absPos = catapult.get_position();
        //     // int power = (absPos - catapult.get_position())*factor;
        //     // pros::lcd::set_text(2, "Hold");
        //     // setCatapult(power);
        //     // pros::delay(10);

        while (puncher_rot.get_angle() < 17000) { // Could change to just button value
            pros::lcd::set_text(1, "REACHED");
            setPTO(0, 0, 0, 0);
        // int x = x + 1;
        // int absPos = catapult.get_position();
        // int power = (absPos - catapult.get_position())*factor;
        // pros::lcd::set_text(2, "Hold");
        // setCatapult(power);
        // pros::delay(10);

            if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1) == 1 || cata_shoot == true) {
                hold = false;
                cata_shoot = true;
                break;
                // hold = false;
                // cata_shoot = false;
                // setCatapult(127);
                // pros::delay(300);
            }
        }

        if (cata_shoot == true) {
            pros::lcd::set_text(2, "Shoot");
            cata_shoot = false;
            setPTO(-600, -600, -600, -600);
            // ptoL1.move(-127);
            // ptoL2.move(-127);
            // ptoR1.move(-127);
            // ptoR2.move(-127);
            pros::delay(350);
        }

        // if (cata_limit_switch.get_value() == 1) {
        //     cata_shoot = false;
        //     hold = true;
        // }

        // catapult.move_velocity(200);
        
        pros::delay(20);

        // OLD HOLD CODE
        // ------------------------------------------
		// if (hold) {
		// 	int absPos = catapult.get_position();
        
        //     // while (hold) {
        //         int power = (absPos - catapult.get_position())*factor;
        //         setCatapult(power);
        //         pros::delay(10);
        //     // }
        // }
        // pros::delay(10);
	}
    
}

void auton_hold() {
    
    // while (true) {
    //     if (cata_limit_switch.get_value() == 1) {
    //         hold = true;
    //         }
    //     }

    // if (cata_shoot == true) {
    //     cata_shoot = false;
    //     setCatapult(127);
    //     pros::delay(200);
            
    // }

    //     pros::delay(10);
}


/**
 * @brief Controls the catapult ratchet of the bot based on button presses
 */

/**
 * @brief Spins catapult other way in case of jam
 * 
 */



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
    wings.set_value(dir);
}

bool currentWings = false;

/**
 * @brief Controls the wings of the bot, opens if it was closed, closes if it is open on button press.
 */
void op_wings() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        if (currentWings == false) {
            currentWings = true;
            wings.set_value(true);
        }
        
        else if (currentWings == true) {
            currentWings = false;
            wings.set_value(false);
        }
    }
}


bool currentClaw = false;

/**
 * @brief Controls the grabber of the bot, drops if it was up, pulls it up if it is dropped on button press.
 */

void op_claw() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
        if (currentClaw == false) {
            currentClaw = true;
            claw.set_value(true);
        }
        
        else if (currentClaw == true) {
            currentClaw = false;
            claw.set_value(false);
        }
    }
}
// ------------------------------------------------------------------------------------------------------
