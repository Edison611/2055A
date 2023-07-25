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
        pros::delay(10);
    }
}

bool ball_detection() {
    double hue = color_sensor.get_hue();
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

bool cata_ball_detection() {
    // int val = line_sensor1.get_value();
    int size = distance_sensor.get_object_size();
    // pros::lcd::set_text(2, "Value: " + std::to_string(val));
    pros::lcd::set_text(3, "Size: " + std::to_string(size));
    pros::lcd::set_text(1, "TEST");
    pros::delay(100);
    if (size < 10) {
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
    while (true) {
        if (loadMacro == true) {
            bool launch = cata_ball_detection();
            if (launch == true) {
                pros::delay(1000);
                shoot();
                pros::delay(300);
            }
        }
        pros::delay(20);
    }
}

// Intake

bool detected = false;

void intakeLimit() {
    while (true) {
        bool x = ball_detection();
        if (x == true && detected == false) {
            setIntake(0);
            detected = true;
        }
    }
}

void print_info() {
    while (true) {
        // Controller printing
        controller.clear();
        pros::delay(200);
        
        pros::lcd::set_text(1, "Switch: " + std::to_string(cata_limit_switch.get_value()));
        if (loadMacro == true) {
            controller.set_text(1, 1, "Match Load: ON");
        }
        else {
            controller.set_text(1, 1, "Match Load: OFF");
        }
    }
}

// void intakeLimit() {
//     if (intake_limit_switch.get_value() == 1) {
//         setIntake(0);
//     }
// }
