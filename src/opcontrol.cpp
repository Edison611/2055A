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
		SetCataRatchet();
		CataRatchet();

		macroLoad();
		// SetMatchLoad();
		
		pros::delay(20);
	}
}