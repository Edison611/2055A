#include "main.h"
#include "pros/misc.h"

// INTAKE
void setIntake(int intaker_power) {
    intake = intaker_power;
    intake.move(intaker_power);
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