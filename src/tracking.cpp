#include "main.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/optical.h"
#include "pros/rtos.h"
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

bool ball_detection() {
    double hue = color_sensor.get_hue();
    pros::c::optical_rgb_s_t rgb = color_sensor.get_rgb();
    pros::lcd::set_text(2, "R: " + std::to_string(int(rgb.red)) + ", G: " + std::to_string(int(rgb.green)) + ", B: " + std::to_string(int(rgb.blue)));
    pros::lcd::set_text(3, "Hue: " + std::to_string(hue));
    if (rgb.red < 50 && rgb.green < 50 && rgb.blue < 50) {
        return true;
    }
    else {
        return false;
    }
}

bool loadMacro = false;

void macroLoad() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        if (loadMacro == false) {
            loadMacro = true;
        }

        else if (loadMacro == true) {
            loadMacro = false;
        }
    }
}

void SetMatchLoad() {
    if (loadMacro == true) {
        bool launch = ball_detection();
        if (launch == true) {
            shoot();
        }
    }
}

// Intake

void intakeLimit() {
    if (intake_limit_switch.get_value() == 1) {
        setIntake(0);
    }
}
