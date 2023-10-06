#include "lemlib/pose.hpp"
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include "pros/vision.h"
#include <cmath>
#include <string>

// ------------------------------------------------------------------------------------------------------
// GLOBAL VARIABLES
// ------------------------------------------------------------------------------------------------------

double netPos[2] = {0, -48};

// ------------------------------------------------------------------------------------------------------
// HELPER FUNCTIONS
// ------------------------------------------------------------------------------------------------------

void GoToOrigin() {
    chassis.moveTo(0, 0, 2000);
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
 * @brief Turns to the position on the field
 * 
 * @param degrees 
 * @param timeout 
 */
void turnTo(double degrees, int timeout=1000) {
    lemlib::Pose pose = chassis.getPose();
    double rad = degrees * 3.14159265358979323846 / 180;
    double x_offset = sin(rad) * 20;
    double y_offset = cos(rad) * 20;
    chassis.turnTo(pose.x+x_offset, pose.y+y_offset, timeout);
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
    chassis.moveTo(x, y, driveTimeout, maxSpeed, reversed);
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

void test_auton() {
    chassis.setPose(60, 17, 180);
    chassis.moveTo(54.5, 30, 10000, 50);
    chassis.moveTo(40, 30, 10000, 50);
}

// ------------------------------------------------------------------------------------------------------
// AUTONOMOUS CODES
// ------------------------------------------------------------------------------------------------------

/**
 * @brief solo autononmous for AWP
 *
 * 1. Shoot triball across the field to our net using catapult
 * 2. If there is time, push middle triballs over the net
 * 3. Go to the corner and take the triball out of the corner using wings
 * 4. Touch our pole
 */
void solo_auton() {

    chassis.setPose(55, -50, -35);
    shoot();

    // Drives to corner and takes triball out
    
    // chassis.moveTo(30, -21, 3000, 70);
    // chassis.turnTo(82, -71, 1000, true);
    // chassis.moveTo(64, -49, 3000, 70, true);

    // chassis.turnTo(30, -65, 1000);


    // Touch the pole for AWP

    // Goes to lower pole
    // chassis.moveTo(65.5, -32, 2000, 70, true);
    // chassis.turnTo(65.5, 0, 1000, true);
    // chassis.moveTo(65.5, -18, 2000, 70, true);
    // grabber.set_value(true);


    // Goes to center and touch pole (OLD)
    // chassis.turnTo(40, -20, 1000);
    // chassis.moveTo(40, -20, 2000, 70);
    // chassis.turnTo(53, 0, 1000, true);
    // chassis.moveTo(45, -15, 1000, 70, true);
    // chassis.turnTo(55, 0, 1000, true);
    // grabber.set_value(true);
    // setDrive(25, -25);
    // pros::delay(250);
    // setDrive(0, 0);
    // setDrive(-15, -15);
    // pros::delay(250);
    // setDrive(0, 0);  
}

void defense_auton() {
    // Get alliance triball into net
    chassis.setPose(-48, -56, 135);
    chassis.moveTo(-60, -33, 1500, 90, true);
    pros::delay(2000);

    // Go grab the corner triball out of the matchload zone
    chassis.moveTo(-48, -56, 1500, 90);

    // Move to touch the middle pole
    chassis.moveTo(-24, -60, 1500, 90);
    turnTo(90);
    chassis.moveTo(-10, -60, 1500, 90);
}

/**
 * @brief defensive autonomous route
 * TESTING IN PROGRESS
 */
void defense_auton_elim() {
    chassis.setPose(-36, -55, 0);
    claw.set_value(true);
    chassis.moveTo(-36, -9, 2000, 90);
    turnTo(120);
    turnTo(-90);    
    chassis.moveTo(-44, -9, 1000, 80);
    chassis.moveTo(-25, -15, 2000, 60); 
    chassis.turnTo(-8, -2, 1000);
    claw.set_value(false);
    chassis.moveTo(-10, -5, 1000, 60);
    claw.set_value(true);
    // chassis.turnTo(-8, -12, 1000);
    chassis.turnTo(0, -10, 1000);
    chassis.moveTo(-2, -10, 1000, 60);
    
}

/**
 * @brief offensive autonomous
 * 
 * 1. Drive to net and outtake our triball into the net
 * 2. Grab the middle triball and score it
 * 3. Grab the triball in the middle away from the net and score it
 * 4. Grab the triball on our side and score it
 * 5. Touch the pole if needed
 */
void offense_auton() {

}

void offense_auton_elim() {
    chassis.setPose(-12, 60, 90);

    // Grab middle Triball and score both alliance triball and grabbed triball
    claw.set_value(true);
    chassis.moveTo(-40, 60, 1200, 90, true); // Move forward a little
    wings.set_value(true);
    chassis.moveTo(-62.5, 40, 1400, 90, true); // Move the the net
    wings.set_value(false);
    turnTo(0); // Adjust the back of the bot to face the net
    chassis.moveTo(-62.5, 28, 1000, 110, true); // Push the Red Tri-Ball into the net
    chassis.moveTo(-62.5, 35, 1200, 110, true); // Back-Up
    turnTo(180); // Turn the bot around so the front is facing the net
    chassis.moveTo(-62.5, 28, 1000, 110); // Push the Green Tri-Ball into the net
    chassis.moveTo(-55, 42.5, 1200, 110); // Back-Up
    claw.set_value(false);
    
    // Go for center 3 triballs
    chassis.turnTo(-12, 38, 900); // 
    chassis.moveTo(-12, 9, 2200, 90); // Move towards the Middle Back Tr-Ball
    claw.set_value(true);
    pros::delay(400);
    turnTo(-90);
    chassis.moveTo(-47, 10, 1500, 110);

}

