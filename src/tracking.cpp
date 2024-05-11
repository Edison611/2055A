#include "EZ-Template/drive/drive.hpp"
#include "lemlib/pose.hpp"
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/optical.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include <cmath>
#include <string>
#include <iostream>
#include <ostream>
#include <fstream>

/**
 * @brief Screen task to print the position of the robot using Lemlib
 * 
 */
void screen() {
    // loop forever
    double *x;
    double *y;

    while (true) {
        gps_sensor.get_offset(x, y);
        pros::lcd::set_text(6, "x, y" + std::to_string(*x) + ", "  + std::to_string(*y));
        // pros::lcd::set_text(5, "x: " ); // print the x position
        // pros::lcd::set_text(6, "y: " ); // print the y position
        pros::lcd::set_text(7, "angle: " + std::to_string (gps_sensor.get_heading())); // print the heading
        pros::delay(20);
    }
}

/**
 * @brief Log data for robots position and heading to txt file
 * 
 */
void log_data() {
    // Reads config file number
    std::ifstream ConfigRead ("/usd/config.txt");

    std::string text;
    std::string filenum;

    while (std::getline(ConfigRead, text)) {
        filenum = text;
    }
    ConfigRead.close();
    std::string filepath = "/usd/Logs/" + filenum + ".txt";
    // std::string filepath1 = "/usd/Logs/" + filenum + "/inertial_sensor_data.txt";

    std::ofstream Data (filepath.c_str());
    // std::ofstream DataSensor (filepath1.c_str());

    // Update config file number
    std::ofstream ConfigWrite ("/usd/config.txt");

    ConfigWrite << std::stoi(filenum) + 1;
    ConfigWrite.close();

	double time = 0;
	Data << "X, Y, θ" << std::endl;
    // DataSensor << "Heading, Rotation, Pitch, Roll, Yaw" << std::endl;
	while (true) {
        if (time >= 15000) {
            break;  
        }
        lemlib::Pose pose = chassis.getPose();
        std::string line = std::to_string(pose.x) + ", " + std::to_string(pose.y) + ", " + std::to_string(pose.theta);
		Data << line << std::endl;
        std::string sensor_line =  std::to_string(inertial_sensor.get_heading()) + ", " + std::to_string(inertial_sensor.get_rotation())+ ", " + std::to_string(inertial_sensor.get_pitch()) + ", " + std::to_string(inertial_sensor.get_roll()) + ", " + std::to_string(inertial_sensor.get_yaw());
        // DataSensor << sensor_line << std::endl;
		pros::delay(50);
        time += 50;
	}
    Data.close();
    // DataSensor.close();
}
/**
 * @brief Checks if a value is within a range
 * 
 * @param value The value to check
 * @param target The target value
 * @param tolerance The tolerance of the value
 * @return true if the value is within the range
 * @return false if the value is not within the range
 */
bool withinRange(double value, double target, double tolerance) {
    // Calculate the absolute difference between the value and target
    double diff = std::abs(value - target);
    
    // Check if the absolute difference is less than or equal to the tolerance
    return diff <= tolerance;
}

/**
 * @brief Deploys the claw when the robot is in specific position
 * 
 */
void deploy() {
    while (true) {
        lemlib::Pose pose = chassis.getPose();
        if (withinRange(pose.x, -14, 1) && withinRange(pose.y, 13, 1)) {
            ActivateWings(true);
            // controller.rumble(".");
            pros::delay(100);
        }
 
        // if (withinRange(pose.x, -34, 1) && withinRange(pose.y, 43, 1)) {
        //     //claw.set_value(true);
        //     controller.rumble(".");
        //     pros::delay(100);
        // }
        pros::delay(20);
    }
}

/**
 * @brief variable that toggles between true or false
 * 
 */
bool loadMacro = true;

void macroLoad() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        if (loadMacro == false) {
            loadMacro = true;
        }

        else if (loadMacro == true) {
            loadMacro = false;
        }
    }
}


bool detected = false;


void timeTracker(int *time, int delay) {
    pros::delay(delay);
    *time += delay;
}

int clock_time = 0;
/**
 * @brief Prints information to Brain and Controller
 * 
 * Needs a 100ms delay between clearing the controller
 * Needs a 50ms delay between each print line
 */
void print_info() {
    while (true) {
        // Controller printing
        controller.clear();
        timeTracker(&clock_time, 100);
        
        // pros::lcd::set_text(1, "Switch: " + std::to_string(cata_limit_switch.get_value()));
        
        // Kicker status
        if (hold) controller.print(1, 0, "Kicker: Down");
        else controller.print(1, 0, "Kicker: Up");
        timeTracker(&clock_time, 50);

        // Match load status
        if (loadMacro) controller.print(0, 0, "Match Load: ON (A)");
        else controller.print(0, 0, "Match Load: OFF (A)");
        timeTracker(&clock_time, 50);

        controller.set_text(2, 10, "T: " + std::to_string(clock_time/1000) + "s");
        timeTracker(&clock_time, 50);
    }
}

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