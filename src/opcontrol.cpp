#include "main.h"

/**
 * @brief Code to call during the driving period
 * 
 */
void my_opcontrol() {
	driveLB.set_brake_mode(MOTOR_BRAKE_COAST);
    driveLM.set_brake_mode(MOTOR_BRAKE_COAST);
    driveLF.set_brake_mode(MOTOR_BRAKE_COAST);

    driveRB.set_brake_mode(MOTOR_BRAKE_COAST);
    driveRM.set_brake_mode(MOTOR_BRAKE_COAST);
    driveRF.set_brake_mode(MOTOR_BRAKE_COAST);
	while (true) {
		setDriveMotors();
        setIntakeMotors();
		setCatapultMotors();
		op_wings();
		SetGrabber();
		SetCataRatchet();
		CataRatchet();

		macroLoad();
		// SetMatchLoad();
		int size = distance_sensor.get_object_size();
		// pros::lcd::set_text(2, "Value: " + std::to_string(val));
		pros::lcd::set_text(3, "Size: " + std::to_string(size));
		int dist = distance_sensor.get();
		// pros::lcd::set_text(2, "Value: " + std::to_string(val));
		pros::lcd::set_text(2, "Distance: " + std::to_string(dist));
		
		pros::delay(20);
	}
}