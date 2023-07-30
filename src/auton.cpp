#include "main.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include "pros/vision.h"
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

void turnToNet(bool reversed=false, int delay=1000) {
    lemlib::Pose pose = chassis.getPose();
    chassis.turnTo(pose.x, -60, delay, reversed);
    
}

void driveToNet(int delay = 100) {
    lemlib::Pose pose = chassis.getPose();
    chassis.turnTo(pose.x, netPos[1], 1000);
    pros::delay(delay);
    setIntake(-127);
    chassis.moveTo(pose.x, netPos[1]+15, 1500);
    pros::delay(100);
    setIntake(0);
}

/**
 * @brief Turns and Drives straight to a specified coordinate
 * 
 * @param x 
 * @param y 
 * @param turnTimout timeout for turning (default to 1 second)
 * @param driveTimeout timeout for driving (default to 1 second)
 */
void vector(double x, double y, int turnTimout = 1000, int driveTimeout = 1000) {
    chassis.turnTo(x, y, turnTimout);
    chassis.moveTo(x, y, driveTimeout);
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
 * @brief Skills code (currently testing)
 * 
 * 1. Shoot Match Loads for the first 30 seconds
 */
void skills() {

    chassis.setPose(-52, 54, -30);

    loadMacro = true;
    pros::delay(30000);
    loadMacro = false;

    chassis.moveTo(-10, 24, 2000, 50, true);
    turnToNet();

    // Drive over middle bar
    setDrive(100, 100);
    pros::delay(1000);
    setDrive(0,0);
    pros::delay(200);

    // Drive back and resest position
    setDrive(-50, -50);
    pros::delay(500);
    setDrive(0, 0);
    chassis.setPose(-10, -10, 180);

    // Open Wings and Drive the Triballs into the net
    chassis.moveTo(0, -15, 1000);
    turnToNet(true);
    wings.set_value(true);
    chassis.moveTo(0, -36, 2000);


    // chassis.turnTo(0, -5, 1000);
    // setIntake(127);
    // chassis.moveTo(-5, -10, 1000, 50);



    chassis.turnTo(-10, -60, 1000);

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
    
    // Write the test code in here
    pros::Task hold_triball(intakeLimit);
    setIntake(40);
    pros::delay(4000);
    setIntake(-100);
    pros::delay(1000);
    setIntake(0);
    pros::delay(1000);
    setIntake(40);
    pros::delay(3000);
    setIntake(-100);
    pros::delay(1000);
    setIntake(0);
}

// ------------------------------------------------------------------------------------------------------
// AUTONOMOUS CODES
// ------------------------------------------------------------------------------------------------------

/**
 * @brief solo autononmous for AWP
 *
 * 1. Drive to midline and shoot triball across the field to our net using catapult
 * 2. If there is time, pick up a triball and shoot it across again
 * 3. Go to the corner and take the triball out of the corner
 * 4. Touch our pole
 */
void solo_auton() {
    // pros::Task hold_auton(auton_hold);
    
    // Releases back wedge
    // grabber.set_value(true);
    // pros::delay(100);
    // grabber.set_value(false);
    // pros::delay(100);

    // Drives to net and shoots alliance triball
    chassis.setPose(56, -33, 90);
    chassis.moveTo(27, -33, 2000, 90, true);
    chassis.turnTo(26, 0, 800, true);
    chassis.moveTo(26, -13, 1500, 75, true);
    setDrive(-15, 30);
    pros::delay(200);
    setDrive(0, 0);
    pros::delay(200);
    shoot();
    pros::delay(200);

    // Drives to corner and takes triball out
    
    chassis.moveTo(30, -24, 3000, 70);
    chassis.turnTo(81, -70, 1000, true);
    chassis.moveTo(62, -50, 3000, 70, true);
    // pros::delay(1000);

    grabber.set_value(true);
    pros::delay(500);
    chassis.turnTo(30, -65, 1000);
    // chassis.moveTo(51, -55, 1500, 80);
    grabber.set_value(false);

    // Touch the pole for AWP

    // Goes to lower pole
    chassis.moveTo(64, -32, 2000, 70, true);
    chassis.turnTo(63, 0, 1000, true);
    chassis.moveTo(63, -17, 2000, 70, true);
    grabber.set_value(true);


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

    // Suspends task (We need to make sure that it gets suspended before driver)
    // hold_auton.suspend();
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
    pros::Task hold_triball(intakeLimit);
    // detected = true; // Since there is already a triball inside

    // SET POSITION
    chassis.setPose(-56, -45, -45);

    // Score first triball
    chassis.moveTo(-45, -56, 500);
    chassis.turnTo(50, -55, 750, true);
    setDrive(-100, -100);
    pros::delay(400);
    setDrive(0, 0);
    chassis.moveTo(-53, -50, 500);
    chassis.turnTo(-15, -22, 750);
    setIntake(40);
    chassis.moveTo(-15, -28, 5000, 60);
    chassis.turnTo(-15, -60, 720);
    setIntake(-127);
    chassis.moveTo(-15, -60, 500);

    // driveToNet(); // Currently testing
    // detected = false;

    // chassis.turnTo(-27, -72, 1000);
    // pros::delay(100);
    // setIntake(-127);
    // chassis.moveTo(-27, -36, 1000);
    // pros::delay(100);
    // setIntake(0);

    // Grab second triball and score it
    // setIntake(40);
    // vector(0, -24);
    // driveToNet();


    hold_triball.suspend();

    // OLD CODE
    // -----------------------------------
    // setIntake(50);
    // pros::delay(5000);
    // setIntake(-127);
    // pros::delay(1000);
    // setIntake(0);

    // chassis.setPose(-24, -24, 90);
    // pros::delay(100);
    // setIntake(25); 
    // pros::delay(100);
    // chassis.moveTo(-10, -24, 2000);
    // pros::delay(1000);
    // chassis.turnTo(-10, -50, 2000);
    // pros::delay(200);
    // setIntake(-127);
    // chassis.moveTo(-10, -35, 2000);
}

void defense_auton() {

}
