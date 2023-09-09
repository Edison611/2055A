#include "main.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/optical.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include <string>

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
bool loadMacro = false;

void macroLoad() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        if (loadMacro == false) {
            cata_ratchet.set_value(true);
            loadMacro = true;
        }

        else if (loadMacro == true) {
            loadMacro = false;
            cata_ratchet.set_value(false);
        }
    }
}

/**
 * @brief Triggers the matchload phase where if a triball is detected than it shoots
 * 
 */
void SetMatchLoad() {
    while (true) {
        if (loadMacro == true) {
            bool launch = cata_ball_detection();
            if (launch == true) {
                pros::delay(100);
                // if (cata_ball_detection() == true) {
                //     pros::delay(150);
                //     shoot();
                // }
                // pros::delay(700);
                shoot();
                
            }
        }
        pros::delay(10);
    }
}

// Intake

bool detected = false;

/**
 * @brief Detects a triball within our intake system
 * 
 * Changes a global variable between true and false, while setting the Intake to 0 power if a triball is detected
 */


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
        pros::delay(100);
        time += 100;
        
        // pros::lcd::set_text(1, "Switch: " + std::to_string(cata_limit_switch.get_value()));
        controller.print(1, 0, "Arm: (B), Wing: (X)");
        pros::delay(50);
        time += 50;

        if (loadMacro == true) {
            controller.print(0, 0, "Match Load: ON (A)");
        }
        else {
            controller.print(0, 0, "Match Load: OFF (A)");
        }
        pros::delay(50);
        time += 50;

        // if (currentIntakeHold == true) {
        //     controller.print(2, 0, "HOLD");
        // }
        // else {
        //     controller.print(2, 0, "PASS");
        // }
        pros::delay(50);
        time += 50;


        controller.set_text(2, 10, "T: " + std::to_string(time/1000) + "s");
        // pros::delay(50);
        // time += 50;
    }
}
