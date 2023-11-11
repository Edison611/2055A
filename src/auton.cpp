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
    // chassis.moveTo(0, 0, 2000);
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
    // chassis.moveTo(pose.x + x_new, pose.y + y_new, timeout);
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
    // chassis.moveTo(x, y, driveTimeout, maxSpeed, reversed);
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


ASSET(path1_txt);
ASSET(skills1_txt);
ASSET(newcurve4_txt);
ASSET(leftcurve2_txt);

void test_auton() {
    chassis.setPose(-45.00606998556999, -59.97344660894661, 100.82);
    chassis.follow(leftcurve2_txt, 20000, 15);
}

void test_auton2() {
    chassis.follow(skills1_txt, 6000, 10);
    chassis.setPose(-55, 40, 180);
    // chassis.moveTo(-60, 30);
}

// ------------------------------------------------------------------------------------------------------
// AUTONOMOUS CODES
// ------------------------------------------------------------------------------------------------------
void driver_skills() {

    chassis.setPose(-61, 32, 0);

    int shots = 44; // How many shots to take
    int delay = 1000; // The delay between each shot

    float time = ((shots * delay)/ 1000.0) - 1; // Formula for calculating time it takes to complete based of # of shots and delay
    int shotNum = 1000 * (time+1) / delay; // Formula for finding # of shots based off time and delay

    // Start Code

    // chassis.moveTo(-61, 41, 1000);
    // chassis.turnTo(-73, 68, 500);

    // setDrive(45, 35);
    // pros::delay(100);
    int x = inertial_sensor.get_rotation();
 
    // grabber.set_value(true);
    pros::delay(50);


    for (int i = 0; i < shots; i++) {
        shoot();
        // pros::lcd::set_text(1, "time: " + std::to_string(i));
        // if (inertial_sensor.get_rotation() >= x) {
        //     setDrive(5, 15);
        // }
        // else if (inertial_sensor.get_rotation() <= x-2) {
        //     setDrive(15, 5);
        // }
        // else {
        //     setDrive(15, 10);
        // }

        pros::delay(delay);
    }

    setDrive(0, 0);
    // controller.rumble("-.");
}

void auton_skills() {

    // driveLB.set_brake_mode(MOTOR_BRAKE_BRAKE);
    // driveLF.set_brake_mode(MOTOR_BRAKE_BRAKE);    // driveRB.set_brake_mode(MOTOR_BRAKE_BRAKE);
    // driveRF.set_brake_mode(MOTOR_BRAKE_BRAKE);

    // chassis.setPose(-49.25, -59, 61);

    // chassis.setPose(36, 60, -90); change this -- facing front, front of robot aligned with
    chassis.setPose(-44.75, -57, -90); // for blue net side
    // chassis.setPose(57, -44.75, 180) // for red net side
    wingR.set_value(true); // open wings
    // pros::delay(1000);
    pros::delay(500);
    wingR.set_value(false); // close wings
    chassis.turnTo(-64, -24, 1000); 
    chassis.moveTo(-60,-37,-35, 1000);
    chassis.turnTo(-60, 72, 1000);
    // setDrive(-600,-600);
    // pros::delay(1000);
    setDrive(600, 600);
    // pros::delay(2000);
    pros::delay(1000);
    setDrive(0,0);

    // chassis.moveTo(-43, -48, -30, 2000);
    chassis.moveTo(-43, -48, -30, 2000, false, true, 0, 0.6, 80, false); // sets max speed to 60
    // chassis.moveTo(-44.25, -59.3, 54, 3000);
    turnTo(54);
    setDrive(-400, -400);
    // pros::delay(2000); // ONLY FOR TESTING PURPOSES
    pros::delay(1000);
    setDrive(0, 0);

    // // chassis.setPose(48, 47, 300);
    // // chassis.moveTo(41, 58, 3000);
    // // turnTo(270);
    // // driveFwd(10, 3000);
    // // chassis.setPose(46, 58, -90);
    // // pros::delay(100000);

    // int shots = 40; // How many shots to take
    // int delay = 1000; // The delay between each shot

    // float time = ((shots * delay)/ 1000.0) - 1; // Formula for calculating time it takes to complete based off # of shots and delay
    // int shotNum = 1000 * (time+1) / delay; // Formula for finding # of shots based off time and delay

    // for (int i = 0; i < shots; i++) {
    //     shoot();
    //     // pros::lcd::set_text(1, "time: " + std::to_string(i));
    //     // if (inertial_sensor.get_rotation() >= x) {
    //     //     setDrive(5, 15);
    //     // }
    //     // else if (inertial_sensor.get_rotation() <= x-2) {
    //     //     setDrive(15, 5);
    //     // }
    //     // else {
    //     //     setDrive(15, 10);
    //     // }

    //     pros::delay(delay);
    // }
    // turnTo(300);
    // turnTo(-90);

    // pros::delay(1000);
    // chassis.moveTo(-42.303626984126986, -58.72616522366522, 90, 3000);
    // pros::delay(1000);
    // chassis.follow(newcurve4_txt, 7000, 15.0);
    // ActivateWings(true);
    // chassis.moveTo(-16, 0, 2000);
    // chassis.moveTo(-100, 0, 3000);
    // chassis.moveTo(-24, -12, 1000, 80);
    // chassis.moveTo(-10, -12, 1000, 80);
    
}


/**
 * @brief solo autononmous for AWP
 *
 * 1. Shoot triball across the field to our net using catapult
 * 2. If there is time, push middle triballs over the net
 * 3. Go to the corner and take the triball out of the corner using wings
 * 4. Touch our pole
 */
void solo_auton() {

    /* Shoot Alliance Triball */
    chassis.setPose(-44.25, -59.3, 54);
    shoot();
    pros::delay(1000);

    /* Take Out Corner Triball */
    turnTo(0);
    chassis.moveTo(-44.25, -48, 0, 800);
    turnTo(-90);
    pros::delay(100);
    chassis.moveTo(-50, -48, -90, 800);
    turnTo(-180);
    wingR.set_value(true);
    chassis.moveTo(-49, -55.5, -180, 800);
    turnTo(-170);
    turnTo(90);
    pros::delay(100);
    wingR.set_value(false);

    /* Moving Toward Pole */
    chassis.moveTo(-15, -60, 90, 2850);
    pros::delay(500);
    claw.set_value(true);
    
    
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
    // chassis.moveTo(-48, -56, 1500, 90);

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
    // chassis.setPose(-36, -55, 0);
    // claw.set_value(true);
    // chassis.moveTo(-36, -9, 2000, 90);
    // turnTo(120);
    // turnTo(-90);    
    // chassis.moveTo(-44, -9, 1000, 80);
    // chassis.moveTo(-25, -15, 2000, 60); 
    // chassis.turnTo(-8, -2, 1000);
    // claw.set_value(false);
    // chassis.moveTo(-10, -5, 1000, 60);
    // claw.set_value(true);
    // // chassis.turnTo(-8, -12, 1000);
    // chassis.turnTo(0, -10, 1000);
    // chassis.moveTo(-2, -10, 1000, 60);

    chassis.setPose(35, 60, -50);
    chassis.moveTo(62, 35, 0, 2090);
    chassis.moveTo(45, 55, -40, 1562);
    chassis.moveTo(45, 55, 35, 800);
    chassis.moveTo(38, 8, 0, 2626);
    chassis.moveTo(38, 8, -90, 800);
    chassis.moveTo(10, 8, -90, 1650);
    ActivateWings(true);
    chassis.moveTo(10, 8, -90, 1600);
    
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
    chassis.setPose(-12, 57, 90);
    claw.set_value(true);
    pros::delay(750);
    chassis.moveTo(-35, 57, 90, 1500, false, false); // Move forward 
    chassis.moveTo(-50, 52, 45, 1500, false, false);
    //pros::delay(200);
    //wingL.set_value(true);
    chassis.moveTo(-58, 40, 0, 1500, false, false); // Align with net
    chassis.turnTo(-60, 0, 1500, false, false, 80);   
    //wingL.set_value(false);  
    chassis.moveTo(-55, 0, 180, 1500, false, true); // Rams in from the front
    chassis.moveTo(-55, 60, 110, 1500, false, false); // Back up and face the middle three triballs
    claw.set_value(false);

    // Middle Triballs
    // chassis.moveTo(-25, 25, 125, 1880, false, true, 0, 0.6); // Move towards centee
    chassis.moveTo(-10, 10, 140, 1084, false, true, 0, 0.6); // Move to back middle triball
    claw.set_value(true);
    pros::delay(300);
    chassis.turnTo(-60, 10, 500); // Turn to net
    chassis.moveTo(-42, 10, 270, 1533, false, true, 0, 0.6); // Ram in from the front
    chassis.moveTo(-35, 10, 270, 500, false, false, 0, 0.6); // Back up 
}

void offense_auton_elim() {
    chassis.setPose(-12, 60, 90);

    // Grab middle Triball and score both alliance triball and grabbed triball
    // claw.set_value(true);
    // chassis.moveTo(-40, 60, 1200, 90, true); // Move forward a little
    // // wings.set_value(true);
    // chassis.moveTo(-62.5, 40, 1400, 90, true); // Move the the net
    // // wings.set_value(false);
    // turnTo(0); // Adjust the back of the bot to face the net
    // chassis.moveTo(-62.5, 28, 1000, 110, true); // Push the Red Tri-Ball into the net
    // chassis.moveTo(-62.5, 35, 1200, 110, true); // Back-Up
    // turnTo(180); // Turn the bot around so the front is facing the net
    // chassis.moveTo(-62.5, 28, 1000, 110); // Push the Green Tri-Ball into the net
    // chassis.moveTo(-55, 42.5, 1200, 110); // Back-Up
    // claw.set_value(false);
    
    // // Go for center 3 triballs
    // chassis.turnTo(-12, 38, 900); // 
    // chassis.moveTo(-12, 9, 2200, 90); // Move towards the Middle Back Tr-Ball
    // claw.set_value(true);
    // pros::delay(400);
    // turnTo(-90);
    // chassis.moveTo(-47, 10, 1500, 110);

}

