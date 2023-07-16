#include "main.h"

/**
 * @brief Code to call during the driving period
 * 
 */
void my_opcontrol() {
	while (true) {
		setDriveMotors();
        setIntakeMotors();
		setCatapultMotors();
		op_wings();
		SetGrabber();
		pros::delay(20);
	}
}