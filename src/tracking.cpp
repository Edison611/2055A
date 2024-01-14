#include "lemlib/pose.hpp"
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/optical.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
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
    while (true) {
        lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        pros::lcd::set_text(5, "x: " + std::to_string(pose.x)); // print the x position
        pros::lcd::set_text(6, "y: " + std::to_string(pose.y)); // print the y position
        pros::lcd::set_text(7, "angle: " + std::to_string(pose.theta)); // print the heading
        pros::delay(20);
    }
}

/**
 * @brief Log data for robots position and heading to txt file
 * 
 */
void log_data() {
    // std::string date = currentDateTime() + ".txt";
    // std::string date = "14-01-2024-2-14PM";
    std::string date = "11111";
    std::string filepath = "/usd/Logs/" + date + "/position.txt";
    std::string filepath1 = "/usd/Logs/" + date + "/inertial_sensor_data.txt";

    std::ofstream Data (filepath.c_str());
    std::ofstream DataSensor (filepath1.c_str());
    // Data.open("/usd/2055/" + date, std::ios_base::app);
	double time = 0;
	Data << "X, Y, θ" << std::endl;
    DataSensor << "Heading, Rotation, Pitch, Roll, Yaw" << std::endl;
	while (true) {
        if (time >= 35000) {
            break;  
        }
        lemlib::Pose pose = chassis.getPose();
        std::string line = std::to_string(pose.x) + ", " + std::to_string(pose.y) + ", " + std::to_string(pose.theta);
		Data << line << std::endl;
        std::string sensor_line = std::to_string(inertial_sensor.get_heading()) + ", " + std::to_string(inertial_sensor.get_rotation())+ ", " + std::to_string(inertial_sensor.get_pitch()) + ", " + std::to_string(inertial_sensor.get_roll()) + ", " + std::to_string(inertial_sensor.get_yaw());
        DataSensor << sensor_line << std::endl;
		pros::delay(50);
        time += 50;
	}
	// Data << "END" << std::endl;
    Data.close();
    DataSensor.close();
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
 * @brief Detects triball using Color Sensor
 * 
 *
 * @return true when the rgb values are less than 50
 * @return false in all other cases
 */
bool ball_detection() {
    // double hue = color_sensor.get_hue();
    pros::c::optical_rgb_s_t rgb = color_sensor.get_rgb();
    // pros::lcd::set_text(2, "R: " + std::to_string(int(rgb.red)) + ", G: " + std::to_string(int(rgb.green)) + ", B: " + std::to_string(int(rgb.blue)));
    // pros::lcd::set_text(3, "Hue: " + std::to_string(hue));
    if (rgb.red < 50 && rgb.green < 50 && rgb.blue < 50) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief Detects triball using Distance Sensor
 * 
 *
 * @return true when the size is less than 10
 * @return false in all other cases
 */
bool cata_ball_detection() {
    // int val = line_sensor1.get_value();
    int size = distance_sensor.get_object_size();
    int dist = distance_sensor.get();
    // pros::lcd::set_text(2, "Value: " + std::to_string(val));
    pros::lcd::set_text(2, "Distance: " + std::to_string(dist));
    pros::lcd::set_text(3, "Size: " + std::to_string(size));

    if (dist < 30) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief Detects triball using line sensor
 * 
 * @return true 
 * @return false 
 */
bool ball_detection_line() {
    int val = line_sensor.get_value();
    if (val < 4000 && val > 2000) {
        return true;
    }
    else {
        return false;
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
            //cata_ratchet.set_value(true);
            loadMacro = true;
            // setPTO(-600, -600, -600, -600);
        }

        else if (loadMacro == true) {
            loadMacro = false;
            //cata_ratchet.set_value(false);
            // setPTO(0, 0, 0, 0);
        }
    }
}

/**
 * @brief Triggers the matchload phase where if a triball is detected than it shoots
 * 
 */
void SetMatchLoad() {
    // while (true) {
    //     if (loadMacro == true && currentDrivePTO == false) {
        
    //         shoot();
    //         pros::delay(1200);
    //         // bool launch = cata_ball_detection();
    //         // if (launch == true) {
    //         //     pros::delay(100);
    //         //     shoot();
                
    //         // }
    //     }
    //     pros::delay(10);
    // }
}

bool detected = false;


void timeTracker(int *time, int delay) {
    pros::delay(delay);
    *time += delay;
}


/**
 * @brief Prints information to Brain and Controller
 * 
 * Needs a 100ms delay between clearing the controller
 * Needs a 50ms delay between each print line
 */
void print_info() {
    int time = 0;
    while (true) {
        // Controller printing
        controller.clear();
        timeTracker(&time, 100);
        
        // pros::lcd::set_text(1, "Switch: " + std::to_string(cata_limit_switch.get_value()));
        
        // Kicker status
        if (hold) controller.print(1, 0, "Kicker: Down");
        else controller.print(1, 0, "Kicker: Up");
        timeTracker(&time, 50);

        // Match load status
        if (loadMacro) controller.print(0, 0, "Match Load: ON (A)");
        else controller.print(0, 0, "Match Load: OFF (A)");
        timeTracker(&time, 50);

        controller.set_text(2, 10, "T: " + std::to_string(time/1000) + "s");
        timeTracker(&time, 50);
    }
}
