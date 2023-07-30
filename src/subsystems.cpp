#include "main.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include <string>

// Define all the subsystems in this file

// ------------------------------------------------------------------------------------------------------
// INTAKE
// ------------------------------------------------------------------------------------------------------
void setIntake(int intaker_power) {
    intake1.move(intaker_power);
    intake2.move(intaker_power);
}

void setIntakeMotors() {
    int intake_power = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
    setIntake(intake_power);    
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
    if (cata_limit_switch.get_value() == 1) {
        hold = true;
    }
    // pros::lcd::set_text(3, "Limit Switch: " + std::to_string(limit_switch.get_value()));
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1) == 1) {
        hold = false;
        // Shoot Catapult
        setCatapult(127);
        pros::delay(350);
        setCatapult(127);
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

        while (cata_limit_switch.get_value() == 1) { // Could change to just button value
            
            catapult.move_velocity(0);
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
            // pros::lcd::set_text(2, "Shoot");
            cata_shoot = false;
            catapult.move_velocity(200);
            pros::delay(350);
        }

        // if (cata_limit_switch.get_value() == 1) {
        //     cata_shoot = false;
        //     hold = true;
        // }

        // catapult.move_velocity(200);

        // pros::lcd::set_text(2, "None");
        pros::delay(20);

        // setCatapult(127);
       
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

    while (true) {

        pros::delay(10);
    }

    

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

bool currentCataRatchet = false;

/**
 * @brief Controls the catapult ratchet of the bot based on button presses
 */
void SetCataRatchet() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        if (currentCataRatchet == false) {
            currentCataRatchet = true;
            cata_ratchet.set_value(true);
        }

        else if (currentCataRatchet == true) {
            currentCataRatchet = false;
            cata_ratchet.set_value(false);
        }
    }
}
/**
 * @brief Spins catapult other way in case of jam
 * 
 */
void CataRatchet() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        setCatapult(-40);
        cata_ratchet.set_value(true);
        pros::delay(300);
        setCatapult(0);
        cata_ratchet.set_value(false);
    }
}


// ------------------------------------------------------------------------------------------------------
// GRABBER
// ------------------------------------------------------------------------------------------------------
bool currentGrabber = false;

/**
 * @brief Controls the grabber of the bot, drops if it was up, pulls it up if it is dropped on button press.
 */
void SetGrabber() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        if (currentGrabber == false) {
            currentGrabber = true;
            grabber.set_value(true);
        }
        else if (currentGrabber == true) {
            currentGrabber = false;
            grabber.set_value(false);
        }
    }
}

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
// ------------------------------------------------------------------------------------------------------
