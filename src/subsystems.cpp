#include "main.h"
#include "pros/misc.h"

void setIntake(int intaker_power) {
    intake = intaker_power;
}

void setIntakeMotors() {
    int intake_power = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
    setIntake(intake_power);    
}