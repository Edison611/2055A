#include "main.h"

void my_opcontrol() {
	while (true) {
		setDriveMotors();
        setIntakeMotors();
		pros::delay(20);
	}
}