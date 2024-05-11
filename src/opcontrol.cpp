#include "main.h"
#include "pros/gps.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include <ostream>
#include <fstream>


/**
 * @brief Code to call during the driving period
 * 
 * UNCOMMENT LINES TO LOG DATA, MAKE SURE YOU HAVE AN SD CARD IN AND DONT END THE CODE WITH POWER BUTTON
 */
void my_opcontrol() {

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
	
	// double *x;
    // double *y;

    while (true) {
		double x = gps_sensor.get_status().x;
		double y = gps_sensor.get_status().y;

		x = x * 39.370079;
		y = y * 39.370079;

        pros::lcd::set_text(6, "x, y: " + std::to_string(x) + ", "  + std::to_string(y));
        // pros::lcd::set_text(5, "x: " ); // print the x position
        // pros::lcd::set_text(6, "y: " ); // print the y position
        pros::lcd::set_text(7, "angle: " + std::to_string (gps_sensor.get_heading())); // print the heading
        pros::delay(20);
    }

	while (true) {
		
		// lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        // pros::lcd::set_text(5, "x: "  +  std::to_string(pose.x)); // print the x position
        // pros::lcd::set_text(6, "y: " + std::to_string(pose.y)); // print the y position
        // pros::lcd::set_text(7, "angle: " + std::to_string(pose.theta)); // print the heading
        // pros::delay(30);
		// controller.clear();
		// pros::delay(200);
		// controller.set_text(2, 5, distance_sensor.get() * 0.0393701);
		setIntakeMotors();
		op_intake();
		// setDriveMotors();
		op_wings();
		// op_climb();
		op_endgame();
		// setDrivePTO();
	    int x = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    	int y = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		chassis.arcade(y, x, 1);
		rightWing();

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