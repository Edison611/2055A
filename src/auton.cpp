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
    chassis.moveTo(pose.x + x_new, pose.y + y_new, pose.theta, timeout);
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
ASSET(leftcurve4_txt);
ASSET(skillstest_txt);
ASSET(leftcurve5_txt);

void test_auton() {
    chassis.setPose(-38.14602236652237, -60.18132683982684, 100.82);
    // chassis.follow(leftcurve4_txt, 20000, 25);
    chassis.follow(leftcurve5_txt, 20000, 25);
}

void test_auton2() {
    chassis.follow(skills1_txt, 6000, 10);
    chassis.setPose(-55, 40, 180);
    // chassis.moveTo(-60, 30);
}

void test_auton3() {
    chassis.setPose(20, 0, 90);
    ActivateWings(true);
    chassis.moveTo(72, 0, 90, 1500);
    chassis.setPose(48, 0, 90);
    //chassis.moveTo(48, 0, 90, 5000);
    ActivateWings(false);
    chassis.moveTo(15, 13, 113, 5000, false, false);
    ActivateWings(true);
    chassis.moveTo(72, 13, 90, 5000);
}

// ------------------------------------------------------------------------------------------------------
// AUTONOMOUS CODES
// ------------------------------------------------------------------------------------------------------
void driver_skills() {

    // chassis.setPose(-61, 32, 0);

    // int shots = 44; // How many shots to take
    // int delay = 1200; // The delay between each shot

    // float time = ((shots * delay)/ 1000.0) - 1; // Formula for calculating time it takes to complete based of # of shots and delay
    // int shotNum = 1000 * (time+1) / delay; // Formula for finding # of shots based off time and delay

    // Start Code

    // chassis.moveTo(-61, 41, 1000);
    // chassis.turnTo(-73, 68, 500);

    // setDrive(45, 35);
    // pros::delay(100);
    // int x = inertial_sensor.get_rotation();
 
    // grabber.set_value(true);
    // pros::delay(50);
    setDrive(-400, -400);
    pros::delay(500);
    setDrive(0, 0);

    setPTO(-600, -600, -600, -600);
    pros::delay(45000);
    setPTO(0, 0, 0, 0);
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

    controller.rumble("-.");
}

void auton_skills() {

    // driveLB.set_brake_mode(MOTOR_BRAKE_BRAKE);
    // driveLF.set_brake_mode(MOTOR_BRAKE_BRAKE);    // driveRB.set_brake_mode(MOTOR_BRAKE_BRAKE);
    // driveRF.set_brake_mode(MOTOR_BRAKE_BRAKE);

    // chassis.setPose(-49.25, -59, 61);

    // chassis.setPose(36, 60, -90); change this -- facing front, front of robot aligned with
                //chassis.setPose(-44.75, -57, -90); // for blue net side
    // chassis.setPose(57, -44.75, 180) // for red net side
                //wingR.set_value(true); // open wings
    // pros::delay(1000);
                //pros::delay(700);
                //wingR.set_value(false); // close wings
                // chassis.turnTo(-64, -15, 700); 
                // chassis.moveTo(-58, -37.5, -35, 1000);
                // chassis.turnTo(-60, 72, 700);
    // setDrive(-600,-600);
    // pros::delay(1000);
    // chassis.moveTo(-60, 0, 0, 750);
                //setDrive(600, 600);
    // pros::delay(2000);
                // pros::delay(1000);
                // setDrive(0,0);

    // chassis.moveTo(-43, -48, -30, 2000);
                //chassis.moveTo(-43, -54, -30, 1200, false, true, 0, 0.6, 80, false); // sets max speed to 60
    // chassis.moveTo(-44.25, -59.3, 54, 3000);
                // turnTo(54);
                //setDrive(-400, -400);
    // pros::delay(2000); // ONLY FOR TESTING PURPOSES
                // pros::delay(700);
                // setDrive(0, 0);
    chassis.setPose(-44.25, -60.5, 54);
    wedge.set_value(true);
    pros::delay(300);
    wedge.set_value(false);
    setDrive(-400, -400);
    pros::delay(800);
    setDrive(0, 0);
    claw.set_value(true);

    setPTO(-600, -600, -600, -600);
    pros::delay(2000);
    setPTO(0, 0, 0, 0);

    // int shots = 15; // How many shots to take
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
    //chassis.moveTo(-38.977543290043286, -59.14192568542568, 90, 3000);
    //pros::delay(1000);
    //chassis.follow(skillstest_txt, 7000, 15.0);
    // ActivateWings(true);
    // chassis.moveTo(-16, 0, 2000);    
    // chassis.moveTo(-100, 0, 3000);
    // chassis.moveTo(-24, -12, 1000, 80);
    // chassis.moveTo(-10, -12, 1000, 80);
    
    setDrive(70, 70);
    pros::delay(200);
    setDrive(0, 0);
    turnTo(90);
    chassis.moveTo(10, -58, 90, 2000);
    claw.set_value(false);
    chassis.moveTo(42, -58, 90, 2000);
    chassis.turnTo(-5, 22, 800);
    chassis.moveTo(10, -5, -25, 2500);
    turnTo(90);
    ActivateWings(true);
    chassis.moveTo(100, -10, 90, 1500);
    // chassis.setPose(40, -10, 90);
    ActivateWings(false);
    chassis.moveTo(-5, 10, 45, 1500, false, false);
    ActivateWings(true);
    chassis.moveTo(100, 13, 90, 1500);
    ActivateWings(false);
    chassis.moveTo(30, 13, 90, 1000);


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
    chassis.moveTo(-49, -55.5, -180, 800); // may lower y value (more negative)
    turnTo(-170);
    turnTo(90);
    pros::delay(100);
    wingR.set_value(false);

    /* Moving Toward Pole */
    chassis.moveTo(-16, -60, 90, 2850);
    pros::delay(500);
    claw.set_value(true);
    
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

    chassis.setPose(35, 60, 130);
    chassis.moveTo(60, 35, 180, 2003, false, true, 0, 0.6, 600);
    turnTo(180);
    setDrive(600, 600);
    pros::delay(1000);
    setDrive(0, 0);
    chassis.moveTo(35, 60, 120, 1518, false, false, 0, 0.6, 600);
    turnTo(180);
    chassis.moveTo(38, 12, 180, 1505, false, true, 0, 0.6, 600);
    turnTo(270);
    wingL.set_value(true);
    chassis.moveTo(2, 12, -90, 1650, false, true, 0, 0.6, 600);
    wingL.set_value(false);
    
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
    // Reverse into Net
    chassis.setPose(-12, 56, 90);
    // chassis.moveTo(-30, 56, 90, 800, false, true, 0.6, 3, 127);
    claw.set_value(true);
    pros::delay(650);
    chassis.moveTo(-20, 50, 90, 1500, false, false, 0.6, 3, 127);
    chassis.moveTo(-50, 50, 45, 1500, false, false, 0.6, 3, 127);
    chassis.moveTo(-62, 20, 0, 1200, false, false);
    
    // Turn Around and Push into Net
    chassis.turnTo(-60, 0, 1000, false, false, 90);   
    // turnTo(180);
    claw.set_value(false);
    pros::delay(300);
    chassis.moveTo(-60, -50, 180, 1300, false, true);
    chassis.moveTo(-50, 50, 110, 1500, false, false);

    
    // // Middle Triballs
    chassis.turnTo(0, 0, 800);
    // chassis.moveTo(-25, 25, 125, 1880, false, true, 0, 0.6); // Move towards centee
    chassis.moveTo(0, 0, 140, 1500); // Move to back middle triball
    claw.set_value(true);
    pros::delay(300);
    chassis.turnTo(-60, 10, 750, false, false, 70); // Turn to net
    claw.set_value(false);  
    ActivateWings(true);
    chassis.moveTo(-50, 10, 270, 1200); // Ram in from the front
    chassis.moveTo(-35, 10, 270, 1000); // Back up 
}

void offenseV2() {
    // Alliance tri-ball
    chassis.setPose(-45, 60, 225);
    chassis.moveTo(-60, -40, 180, 2154);
    chassis.moveTo(-60, 50, 180, 1000);
    // chassis.moveTo(-60, -100, 180, 1500);
    turnTo(180);
    setDrive(600, 600);
    pros::delay(1000);
    setDrive(0, 0);
    chassis.moveTo(-50, 50, 210, 1596, false, false);
    chassis.turnTo(5, -7, 800);

    // Middle tri-balls
    chassis.moveTo(-12.5, 12.5, 145, 2725);
    pros::delay(200);
    claw.set_value(true);
    pros::delay(200);
    chassis.turnTo(-65, 12.5, 800, false, false, 80);
    wingL.set_value(true);
    claw.set_value(false);
    chassis.moveTo(-60, 13, 270, 2000);
    wingL.set_value(false);

    // Last tri-ball 
    chassis.moveTo(-15, 13, 270, 2500, false, false);
    chassis.turnTo(10, 40, 800);
    claw.set_value(true);
    pros::delay(500);
    chassis.turnTo(-65, 12.5, 1000, false, false, 70);
    claw.set_value(false);
    chassis.moveTo(-68, 13, 270, 2000);
    chassis.moveTo(-25, 13, 270, 2000, false, false);
}


void offense_auton_elim() {
    chassis.setPose(-44.75, 54, -90);
    wingL.set_value(true);
    pros::delay(1000);
    wingL.set_value(false);
    chassis.moveTo(-44.75, 54, -90, 1000);
    chassis.moveTo(-56, 47, 225, 913);
    turnTo(180);
    chassis.moveTo(-60, 0, 180, 2000);

    // Middle Triball
    chassis.moveTo(-50, 50, 30, 1596, false, false); // ONLY LINE DIFFERENT
    chassis.moveTo(-12.5, 12.5, 145, 2000);
    pros::delay(200);
    claw.set_value(true);
    pros::delay(200);
    chassis.turnTo(-65, 12.5, 800, false, false, 80);
    wingL.set_value(true);
    claw.set_value(false);
    chassis.moveTo(-60, 13, 270, 2000);
    wingL.set_value(false);
}

