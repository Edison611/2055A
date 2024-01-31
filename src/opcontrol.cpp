#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include <ostream>
#include <fstream>

/**
 * @brief Code to call during the driving period
 * 
 * UNCOMMENT LINES TO TRACK ROBOT POSITION
 */
void my_opcontrol() {
	driveLB.set_brake_mode(MOTOR_BRAKE_COAST);
	driveLM.set_brake_mode(MOTOR_BRAKE_COAST);
    driveLF.set_brake_mode(MOTOR_BRAKE_COAST);

    driveRB.set_brake_mode(MOTOR_BRAKE_COAST);
	driveRM.set_brake_mode(MOTOR_BRAKE_COAST);
    driveRF.set_brake_mode(MOTOR_BRAKE_COAST);

	chassis.setPose(0, 0, 0);

	while (true) {
		// lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        // pros::lcd::set_text(5, "x: "  +  std::to_string(pose.x)); // print the x position
        // pros::lcd::set_text(6, "y: " + std::to_string(pose.y)); // print the y position
        // pros::lcd::set_text(7, "angle: " + std::to_string(pose.theta)); // print the heading
        // pros::delay(30);

		driverAssist();
		setIntakeMotors();
		// setDriveMotors();
		op_wings();
		setCatapultMotors();
		op_climb();
		int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		chassis.arcade(leftY, rightX, 100); // Tune the 3rd value to change the speed of the robot

		pros::delay(10);
	}
}