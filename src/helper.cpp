#include "main.h"
#include "pros/misc.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <cmath>

// ------------------------------------------------------------------------------------------------------
// GLOBAL VARIABLES
// ------------------------------------------------------------------------------------------------------

double netPos[2] = {0, -48};

// ------------------------------------------------------------------------------------------------------
// HELPER FUNCTIONS
// ------------------------------------------------------------------------------------------------------

void allowContinue() {
    while (true) {
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
            break;
        }
        pros::delay(20);
    }
}

void turnToNet(bool reversed=false, bool red=true, int delay=1000) {
    lemlib::Pose pose = chassis.getPose();
    if (red == true) {
        chassis.turnTo(pose.x, -60, delay, reversed);
    }
    else {
        chassis.turnTo(pose.x, 60, delay, reversed);
    }
    
}

/**
 * @brief Drives x inches forward
 * 
 * @param inches 
 * @param timeout 
 * @param maxSpeed
 */
void driveFwd(double inches, int timeout=1000, float maxSpeed = (200.0F)) {
    lemlib::Pose pose = chassis.getPose();
    double x_new = inches * sin(pose.theta);
    double y_new = inches * cos(pose.theta);
    chassis.moveTo(pose.x + x_new, pose.y + y_new, pose.theta, timeout);
}

/**
 * @brief Turns to the position on the field
 * 
 * @param degrees 
 * @param timeout 
 */
void turnTo(double degrees, int maxSpeed, int timeout, bool reversed, bool async) {
    lemlib::Pose pose = chassis.getPose();
    double rad = degrees * 3.14159265358979323846 / 180;
    double x_offset = sin(rad) * 20;
    double y_offset = cos(rad) * 20;
    chassis.turnTo(pose.x+x_offset, pose.y+y_offset, timeout, async, reversed, maxSpeed);
}

/**
 * @brief Turns and Drives straight to a specified coordinate
 * 
 * @param x 
 * @param y 
 * @param turnTimout timeout for turning (default to 1 second)
 * @param driveTimeout timeout for driving (default to 1 second)
 */
void vector(double x, double y, bool reversed=false, int maxSpeed=127, int turnTimout = 1000, int driveTimeout = 1000) {
    chassis.turnTo(x, y, turnTimout, reversed);
    // chassis.moveTo(x, y, driveTimeout, maxSpeed, reversed);
}


void matchLoad(int shots, int delay) {
    

    float time = ((shots * delay)/ 1000.0) - 1; // Formula for calculating time it takes to complete based of # of shots and delay
    int shotNum = 1000 * (time+1) / delay; // Formula for finding # of shots based off time and delay

    for(int i = 0; i < shots; i++) {
        shoot();
        pros::delay(delay);
        // setCatapult(600);
        // while (true) {
        //     if (kicker_rot.get_angle() < 20500) {
        //         setCatapult(0);
        //         pros::delay(delay);
        //         setCatapult(600);
        //         while (true) {
        //             if (kicker_rot.get_angle() > 20500) {
        //                 break;
        //             }
        //         }
        //         break;
        //     }
        // }
    }
    // while (true) {
    //     if(kicker_rot.get_angle() < 20500) {
    //         setCatapult(0);
    //         break;
    //     }
    // }
}


/**
 * @brief Detects whether there is a triball in front of the color sensor
 * 
 * @param triball the triball object
 * @return true when a triball is detected (when rgb values are all less than 50)
 * @return false all other cases
 */
bool GoToTriball(pros::vision_object_s_t triball) {
    int center = 158;
    bool pause = false;
    double x = triball.x_middle_coord;
    double width = triball.width;

    if ((x > (center - 5)) || (x < (center + 5))) {
        setDrive(50, 50);
        if (width > 200) {
            setDrive(0, 0);
            pause = true;
            return true;
        }
    }

    else if (x < center || pause == true) {
        setDrive(50, -50);
    }

    else if (x > center || pause == true) {
        setDrive(-50, 50);
    }

    return false;

}

std::string currentDateTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d-%X", &tstruct);

    return buf;
}

/**
 * @brief Theoretically uses vision sensor to turn to where there is a triball and drive there (NOT TESTED)
 * 
 */
void triballVision() {
    // Defining Triball Signatures
    // pros::vision_signature_s_t TRIBALL_SIG = pros::Vision::signature_from_utility(2, -6223, -4453, -5338, -6399, -4153, -5276, 3.000, 0);
    // vision_sensor.set_signature(1, &TRIBALL_SIG); 


    // int center = 158;
    // chassis.calibrate();

    // while (true) {
    //     vision_sensor.clear_led();
    //     pros::vision_object_s_t rtn = vision_sensor.get_by_sig(0, 1);   

    //     // Vision sensor values
    //     int count = vision_sensor.get_object_count();
    //     int x = rtn.x_middle_coord;
    //     int y = rtn.y_middle_coord;
    //     // double angle = rtn.angle;
        
    //     pros::lcd::set_text(1, "Count: " + std::to_string(count));
    //     pros::lcd::set_text(2, "Triball X, Y: " + std::to_string(x) + ", " + std::to_string(y));
    //     // pros::lcd::set_text(3, "Triball angle: " + std::to_string(angle));
    //     pros::lcd::set_text(4, "Triball width: " + std::to_string(rtn.width));

    //     if (count >= 1) {
    //         bool grabbed = GoToTriball(rtn);
    //         if (grabbed == true) {

    //         }
    //     }

    //     pros::delay(20);
    // }
}