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


// ------------------------------------------------------------------------------------------------------
// CATAPULT
// ------------------------------------------------------------------------------------------------------
void setCatapult(int power) {
    catapult.move_velocity(power);
    catapult2.move_velocity(power);
} 

//bool hold = false;
bool cata_shoot = false;

void setCatapultMotors() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        cata_shoot = true;
    }
}
bool hold = false;

void toggleDown() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        hold = true;
    }
}

void kickerTask() {
    // one shot at a time
    
    double prev;
    bool stop = true;

    // 232 at top, stop at 205
    // Rotational Sensor Angle increases when going -> up
    while (true) {
        double prev = kicker_rot.get_angle();

        // if (hold) {
        //     setCatapult(600);
        //     while (kicker_rot.get_angle() < 20500) {
        //         setCatapult(0);
        //         if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        //             hold = false;
        //             break;
        //         }
        //         pros::delay(10);
        //     }

        // }

         while (kicker_rot.get_angle() < 20500) { // Could change to adjust button value
            // pros::lcd::set_text(1, "REACHED");
            if (stop == true) {
                setCatapult(0);
                stop = false;
            }

            if (cata_shoot == true) {
                cata_shoot = true;
                break;
            }
        }

        if (cata_shoot == true) {
            // pros::lcd::set_text(2, "Shoot");
            cata_shoot = false;
            setCatapult(600);
            stop = true;
            pros::delay(150);
        }

        pros::delay(20);

    }
}

// false
// true
bool pistonValue = false;

void pistonBoostTask() {
    while (true) {
        if (kicker_rot.get_velocity() > 100) pistonBoost.set_value(true);
        if (kicker_rot.get_velocity() < -100) pistonBoost.set_value(false);
        pros::delay(20);
    }
}

void shoot() {
    cata_shoot = true;
}

/**
 * A task to hold the catapult in place.
 * Tune the factor variable to let the catapult sit in place.
 */
// void cata_hold() { ///

//     // double factor = 9.25; // Tune this value
//     // int x = 0;
//     bool stop = true;

// 	while (true) {

//         while (puncher_rot.get_angle() < 17500) { // Could change to adjust button value
//             // pros::lcd::set_text(1, "REACHED");
//             if (stop == true) {
//                 setPTO(0, 0, 0, 0);
//                 stop = false;
//             }

//             if (cata_shoot == true) {
//                 cata_shoot = true;
//                 break;
//             }
//         }

//         if (cata_shoot == true) {
//             // pros::lcd::set_text(2, "Shoot");
//             cata_shoot = false;
//             setPTO(-600, -600, -600, -600);
//             stop = true;
//             pros::delay(300);
//         }

        
//         pros::delay(20);

// 	}
    
// }

// ------------------------------------------------------------------------------------------------------
// INTAKE
// ------------------------------------------------------------------------------------------------------

void setIntake(int power) {
    intake.move(power);
}

void setIntakeMotors() {
    int intake_power = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
    setIntake(intake_power);    
}

// 50

// ------------------------------------------------------------------------------------------------------
// WINGS
// ------------------------------------------------------------------------------------------------------

void ActivateWings(bool dir) {
    wingR.set_value(dir);
    wingL.set_value(dir);
}

void setWings(bool right, bool left, int delay) {
    wingR.set_value(right);
    wingL.set_value(left);
    pros::delay(delay);
    wingR.set_value(false);
    wingL.set_value(false);
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

/**
 * @brief Manually rams the robot. 
 */
void ram(int time, int dir=1) {
    setDrive(600*dir, 600*dir);
    pros::delay(time);
    setDrive(0, 0);
}


//bool currentClaw = false;

/**
 * @brief Controls the grabber of the bot, drops if it was up, pulls it up if it is dropped on button press.
 */

// void op_claw() {
//     if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
//         currentClaw = !currentClaw;
//         claw.set_value(currentClaw);

//         // if (currentClaw == false) {
//         //     currentClaw = true;
//         //     claw.set_value(true);
//         // }
        
//         // else if (currentClaw == true) {
//         //     currentClaw = false;
//         //     claw.set_value(false);
//         // }
//     }
// }


bool currentClimb = false;

/**
 * @brief Controls the blocker of the bot. On button press, it pulls it up if it is dropped, and drops it if it was up.
 */

void op_climb() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        currentClimb = !currentClimb;
        climb.set_value(currentClimb);
    }
}

// ------------------------------------------------------------------------------------------------------
// WINGS
// ------------------------------------------------------------------------------------------------------






// ------------------------------------------------------------------------------------------------------
