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
void setCatapult(double power) {
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

    // 323 at top, stop at 297
    // Rotational Sensor Angle increases when going -> up
    while (true) {
        // double prev = kicker_rot.get_angle();

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

         while (kicker_rot.get_angle() < 30000) { // Could change to adjust button value //Prev 20400
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
            setCatapult(200);
            stop = true;
            pros::delay(260);
        }

        pros::delay(10);

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
    wingFR.set_value(dir);
    wingFL.set_value(dir);
}

void setWings(bool right, bool left, int delay) {
    wingF.set_value(__bool_true_false_are_defined);
    // wingL.set_value(left);
    pros::delay(delay);
    wingF.set_value(false);
    // wingL.set_value(false);
}

bool currentWingsF = false;
bool currentWingsB = false;

/**
 * @brief Controls the wings of the bot, opens if it was closed, closes if it is open on button press.
 */
void op_wings() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        currentWingsF = !currentWingsF;
        wingFR.set_value(currentWingsF);
        wingFL.set_value(currentWingsF);
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        currentWingsB = !currentWingsB;
        wingB.set_value(currentWingsB);
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
