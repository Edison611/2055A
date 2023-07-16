#include "main.h"
#include "pros/llemu.hpp"
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
        pros::delay(10);
    }
}