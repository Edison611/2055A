#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include <ostream>
#include <fstream>

// CHORE MOVE THESE 3 FUNCTIONS TO tracking.cpp
// std::string getAllPower() {
// 	std::string left = std::to_string(driveLB.get_power()) + ", " + std::to_string(driveLF.get_power()) 
// 	+ ", " + std::to_string(ptoL1.get_power()) + ", " + std::to_string(ptoL2.get_power());
// 	std::string right = std::to_string(driveRB.get_power()) + ", " + std::to_string(driveRF.get_power()) 
// 	+ ", " + std::to_string(ptoR1.get_power()) + ", " + std::to_string(ptoR2.get_power());

// 	std::string str = left + ", " + right;
// 	return str;
// }

// std::string getAllVelocity() {
// 	std::string left = std::to_string(driveLB.get_actual_velocity()) + ", " + std::to_string(driveLF.get_actual_velocity()) 
// 	+ ", " + std::to_string(ptoL1.get_actual_velocity()) + ", " + std::to_string(ptoL2.get_actual_velocity());
// 	std::string right = std::to_string(driveRB.get_actual_velocity()) + ", " + std::to_string(driveRF.get_actual_velocity()) 
// 	+ ", " + std::to_string(ptoR1.get_actual_velocity()) + ", " + std::to_string(ptoR2.get_actual_velocity());

// 	std::string str = left + ", " + right;
// 	return str;
// }

// std::string getAllVoltage() {
// 	std::string left = std::to_string(driveLB.get_voltage()) + ", " + std::to_string(driveLF.get_voltage()) 
// 	+ ", " + std::to_string(ptoL1.get_voltage()) + ", " + std::to_string(ptoL2.get_voltage());
// 	std::string right = std::to_string(driveRB.get_voltage()) + ", " + std::to_string(driveRF.get_voltage()) 
// 	+ ", " + std::to_string(ptoR1.get_voltage()) + ", " + std::to_string(ptoR2.get_voltage());

// 	std::string str = left + ", " + right;
// 	return str;
// }

/**
 * @brief Code to call during the driving period
 * 
 * UNCOMMENT LINES TO LOG DATA, MAKE SURE YOU HAVE AN SD CARD IN AND DONT END THE CODE WITH POWER BUTTON
 */
void my_opcontrol() {
	// driveLB.set_brake_mode(MOTOR_BRAKE_COAST);
	// driveLM.set_brake_mode(MOTOR_BRAKE_COAST);
    // driveLF.set_brake_mode(MOTOR_BRAKE_COAST);

    // driveRB.set_brake_mode(MOTOR_BRAKE_COAST);
	// driveRM.set_brake_mode(MOTOR_BRAKE_COAST);
    // driveRF.set_brake_mode(MOTOR_BRAKE_COAST);
	//chassis.setPose(0, 0, 0);
	// chassis.setPose(-15, 59, -90);
	// pros::Task deploy_task(deploy);

	// chassis.follow("path5.txt", 35000, 6);

	// std::ofstream Data;
    // Data.open("/usd/ROBOT/log.txt", std::ios_base::app);
	// double time = 0;
	// Data << "Time (s), LB, LF, ptoL1, ptoL2, RB, RF, ptoR1, ptoR2" << std::endl;
	// claw.set_value(false);
	// wedge.set_value(true);
	// pros::delay(50);
	// wedge.set_value(false);
	// driver_skills();
	// loadMacro = true;
	// setPTO(-600, -600, -600, -600);

	// wingF.set_value(false);
	// wingB.set_value(false);
	

	while (true) {
		// lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        // pros::lcd::set_text(5, "x: "  +  std::to_string(pose.x)); // print the x position
        // pros::lcd::set_text(6, "y: " + std::to_string(pose.y)); // print the y position
        // pros::lcd::set_text(7, "angle: " + std::to_string(pose.theta)); // print the heading
        // pros::delay(30);
		// controller.clear();
		// pros::delay(200);
		// controller.set_text(2, 5, distance_sensor.get() * 0.0393701);
		driverAssist();
		setIntakeMotors();
		// setDriveMotors();
		op_wings();
	    int x = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    	int y = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		chassis.arcade(y, x, 1);
		rightWing();

		setCatapultMotors();
		op_climb();
		// if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y) == 1) {
		// 	setPTO(0, 0, 0, 0);
		// }
		// std::string line = getAllPower();
		// Data << std::to_string(time) + ", " + line << std::endl;
		// pros::delay(20);
		// time = time + 0.02;
		// if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
		// 	break;
		// }

		// pros::lcd::set_text(3, "angle:" + std::to_string(puncher_rot.get_angle()));
		// pros::delay(100);
		pros::delay(10);
	}
	// Data << "END" << std::endl;
    // Data.close();
}