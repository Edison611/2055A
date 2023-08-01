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
		
		pros::delay(20);
	}
}