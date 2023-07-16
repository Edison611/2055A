#include "main.h"
#include "pros/misc.h"

// INTAKE
void setIntake(int intaker_power) {
    intake1.move(intaker_power);
    intake2.move(intaker_power);
}

void setIntakeMotors() {
    int intake_power = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
    setIntake(intake_power);    
}


// CATAPULT

void setCatapult(int power) {
    catapult.move(power);
} 

bool hold = false;

void setCatapultMotors() {
    if (limit_switch.get_value() == 1) {
        hold = true;
    }
    pros::lcd::set_text(3, "Limit Switch: " + std::to_string(limit_switch.get_value()));
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1) == 1) {
        hold = false;
        // Shoot Catapult
        setCatapult(127);
        pros::delay(350);
        setCatapult(127);
    }
}

void shoot() {

}

/**
 * A task to hold the catapult in place.
 * Tune the factor variable to let the catapult sit in place.
 */
void cata_hold() {

    double factor = 1.25; // Tune this value

	while (true) {
       
		if (hold) {
			int absPos = catapult.get_position();
        
            while (hold) {
                int power = (absPos - catapult.get_position())*factor;
                setCatapult(power);
                pros::delay(10);
            }
        }
        pros::delay(10);
	}
    
}

// GRABBER

bool currentGrabber = false;

void SetGrabber() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2) || currentGrabber == false) {
        currentGrabber = true;
        grabber.set_value(true);
    }   
    else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2) || currentGrabber == true) {
        currentGrabber = false;
        grabber.set_value(false);
    }
}

// WINGS

void ActivateWings(bool dir) {
    wings.set_value(dir);
}

bool currentWings = false;

void op_wings() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X) || currentWings == false) {
        currentWings = true;
        wings.set_value(true);
    }
    else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X) || currentWings == true) {
        currentWings = false;
        wings.set_value(false);
    }
}
