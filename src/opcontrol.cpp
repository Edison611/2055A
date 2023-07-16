#include "main.h"

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