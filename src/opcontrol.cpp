#include "main.h"

void my_opcontrol() {
	while (true) {
		setDriveMotors();
        setIntakeMotors();
		setCatapultMotors();
		pros::delay(20);
	}
}