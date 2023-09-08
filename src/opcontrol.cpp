#include "main.h"
#include <ostream>
#include <fstream>

// CHORE MOVE THESE 3 FUNCTIONS TO tracking.cpp
std::string getAllPower() {
	std::string left = std::to_string(driveLB.get_power()) + ", " + std::to_string(driveLF.get_power()) 
	+ ", " + std::to_string(ptoL1.get_power()) + ", " + std::to_string(ptoL2.get_power());
	std::string right = std::to_string(driveRB.get_power()) + ", " + std::to_string(driveRF.get_power()) 
	+ ", " + std::to_string(ptoR1.get_power()) + ", " + std::to_string(ptoR2.get_power());

	std::string str = left + ", " + right;
	return str;
}

std::string getAllVelocity() {
	std::string left = std::to_string(driveLB.get_actual_velocity()) + ", " + std::to_string(driveLF.get_actual_velocity()) 
	+ ", " + std::to_string(ptoL1.get_actual_velocity()) + ", " + std::to_string(ptoL2.get_actual_velocity());
	std::string right = std::to_string(driveRB.get_actual_velocity()) + ", " + std::to_string(driveRF.get_actual_velocity()) 
	+ ", " + std::to_string(ptoR1.get_actual_velocity()) + ", " + std::to_string(ptoR2.get_actual_velocity());

	std::string str = left + ", " + right;
	return str;
}

std::string getAllVoltage() {
	std::string left = std::to_string(driveLB.get_voltage()) + ", " + std::to_string(driveLF.get_voltage()) 
	+ ", " + std::to_string(ptoL1.get_voltage()) + ", " + std::to_string(ptoL2.get_voltage());
	std::string right = std::to_string(driveRB.get_voltage()) + ", " + std::to_string(driveRF.get_voltage()) 
	+ ", " + std::to_string(ptoR1.get_voltage()) + ", " + std::to_string(ptoR2.get_voltage());

	std::string str = left + ", " + right;
	return str;
}

/**
 * @brief Code to call during the driving period
 * 
 * UNCOMMENT LINES TO LOG DATA, MAKE SURE YOU HAVE AN SD CARD IN AND DONT END THE CODE WITH POWER BUTTON
 */
void my_opcontrol() {
	driveLB.set_brake_mode(MOTOR_BRAKE_COAST);
    driveLF.set_brake_mode(MOTOR_BRAKE_COAST);

    driveRB.set_brake_mode(MOTOR_BRAKE_COAST);
    driveRF.set_brake_mode(MOTOR_BRAKE_COAST);
	// std::ofstream Data;
    // Data.open("/usd/ROBOT/log.txt", std::ios_base::app);
	// double time = 0;
	// Data << "Time (s), LB, LF, ptoL1, ptoL2, RB, RF, ptoR1, ptoR2" << std::endl;
	while (true) {
		setDriveMotors();
		// op_wings();
		// SetGrabber();

		// macroLoad();
		
		DrivePTO();
		Puncher();
		op_claw();
		// std::string line = getAllPower();
		// Data << std::to_string(time) + ", " + line << std::endl;
		// pros::delay(20);
		// time = time + 0.02;
		// if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
		// 	break;
		// }
	}
	// Data << "END" << std::endl;
    // Data.close();
}