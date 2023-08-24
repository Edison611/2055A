#include "lemlib/pose.hpp"
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

void turnToNet(bool reversed=false, bool red=true, int delay=1000) {
    lemlib::Pose pose = chassis.getPose();
    if (red == true) {
        chassis.turnTo(pose.x, -60, delay, reversed);
    }
    else {
        chassis.turnTo(pose.x, 60, delay, reversed);
    }
    
}

void driveToNet(int delay = 100, bool red = true) {
    int y;
    if (red == true) {
        y = netPos[1];
    }
    else {
        y = -netPos[1];
    }
    lemlib::Pose pose = chassis.getPose();
    chassis.turnTo(pose.x, y, 1000);
    pros::delay(delay);
    setIntake(-127);
    chassis.moveTo(pose.x, y+15, 1500);
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

/**
 * @brief Skills code (currently testing)
 * 
 * 1. Shoot Match Loads for the first x seconds represented by (int timeout)
 */
void auton_skills() {
    driveLB.set_brake_mode(MOTOR_BRAKE_BRAKE);
    driveLM.set_brake_mode(MOTOR_BRAKE_BRAKE);
    driveLF.set_brake_mode(MOTOR_BRAKE_BRAKE);

    driveRB.set_brake_mode(MOTOR_BRAKE_BRAKE);
    driveRM.set_brake_mode(MOTOR_BRAKE_BRAKE);
    driveRF.set_brake_mode(MOTOR_BRAKE_BRAKE);

    chassis.setPose(-61, 32, 0);

    int shots = 10; // How many shots to take
    int delay = 1100; // The delay between each shot

    float time = ((shots * delay)/ 1000.0) - 1; // Formula for calculating time it takes to complete based of # of shots and delay
    int shotNum = 1000 * (time+1) / delay; // Formula for finding # of shots based off time and delay

    // Start Code

    
    cata_ratchet.set_value(true);

    chassis.moveTo(-61, 41, 1000);
    chassis.turnTo(-73, 68, 500);

    setDrive(45, 35);
    pros::delay(100);
    int x = inertial_sensor.get_rotation();
    
    
 
    // grabber.set_value(true);
    pros::delay(50);


    for (int i = 0; i < shots; i++) {
        shoot();
        // pros::lcd::set_text(1, "time: " + std::to_string(i));
        if (inertial_sensor.get_rotation() >= x) {
            setDrive(5, 15);
        }
        else if (inertial_sensor.get_rotation() <= x-2) {
            setDrive(15, 5);
        }
        else {
            setDrive(15, 10);
        }

        pros::delay(delay);
    }

    setDrive(0, 0);
    // driveLB.set_brake_mode(MOTOR_BRAKE_BRAKE);
    // driveLM.set_brake_mode(MOTOR_BRAKE_BRAKE);
    // driveLF.set_brake_mode(MOTOR_BRAKE_BRAKE);

    // driveRB.set_brake_mode(MOTOR_BRAKE_BRAKE);
    // driveRM.set_brake_mode(MOTOR_BRAKE_BRAKE);
    // driveRF.set_brake_mode(MOTOR_BRAKE_BRAKE);

    // chassis.setPose(-61, 32, 0);

    // int shots = 43; // How many shots to take
    // int delay = 1000; // The delay between each shot

    // float time = ((shots * delay)/ 1000.0) - 1; // Formula for calculating time it takes to complete based of # of shots and delay
    // int shotNum = 1000 * (time+1) / delay; // Formula for finding # of shots based off time and delay

    // // Start Code
    // cata_ratchet.set_value(true);

    // chassis.moveTo(-61, 41, 1000);
    // chassis.turnTo(-73, 68, 500);

    // setDrive(45, 35);
    // pros::delay(100);
    // setDrive(15, 5);
    // grabber.set_value(true);
    // pros::delay(50);


    // for (int i=0; i < shots; i++) {
    //     shoot();
    //     // pros::lcd::set_text(1, "time: " + std::to_string(i));
    //     pros::delay(delay);
    // }

    // setDrive(0, 0);

    // catapult.move_velocity(200); // Spin the catapult back to the lowered position

    lemlib::Pose pose = chassis.getPose();
    chassis.setPose(-57.5, 47.5, pose.theta);
    grabber.set_value(true);

    // Moves bot to other side
    chassis.turnTo(-65, 0, 1000, true);
    // grabber.set_value(true);
    pros::delay(200);
    chassis.moveTo(-63.5, -6, 2000, 127, true);
    grabber.set_value(false);
    chassis.moveTo(-63.5, -7, 2000, 127, true);
    //wings.set_value(true);

    // Drives to the corner and pushes triballs on the side
    vector(-46, -23, true, 100, 1000, 2000);
    chassis.turnTo(0, -27, 1000, true);
    //wings.set_value(false);
    setDrive(-127, -127);
    pros::delay(600);
    setDrive(0, 0);
    

    // chassis.moveTo(-50, -25, 1000);

    // chassis.moveTo(-44, -27, 1000, 80, true);

    // Drive towards the center and activate wings to push it in
    chassis.moveTo(-53, -15, 1000);
    vector(-40, 10, false, 100, 1000, 2000);
    vector(-18, 10, false, 100, 1000, 1000);
    // wings.set_value(true);
    chassis.turnTo(-18, -30, 1000, true);
    wings.set_value(true);
    chassis.moveTo(-26, -25, 2000, 127, true);

    // vector(-13, -25, true, 127, 1000, 2000);

    // // Drive over middle bar
    // setDrive(100, 100);
    // pros::delay(1000);
    // setDrive(0,0);
    // pros::delay(200);

    // // Drive back and resest position
    // setDrive(-50, -50);
    // pros::delay(500);
    // setDrive(0, 0);
    // chassis.setPose(-10, -10, 180);

    // // Open Wings and Drive the Triballs into the net
    // chassis.moveTo(0, -15, 1000);
    // turnToNet(true);
    // wings.set_value(true);
    // chassis.moveTo(0, -36, 2000);


    // // chassis.turnTo(0, -5, 1000);
    // // setIntake(127);
    // // chassis.moveTo(-5, -10, 1000, 50);

    // chassis.turnTo(-10, -60, 1000);

}

//---------------------------------------
void driver_skills() {
    driveLB.set_brake_mode(MOTOR_BRAKE_BRAKE);
    driveLM.set_brake_mode(MOTOR_BRAKE_BRAKE);
    driveLF.set_brake_mode(MOTOR_BRAKE_BRAKE);

    driveRB.set_brake_mode(MOTOR_BRAKE_BRAKE);
    driveRM.set_brake_mode(MOTOR_BRAKE_BRAKE);
    driveRF.set_brake_mode(MOTOR_BRAKE_BRAKE);

    chassis.setPose(-61, 32, 0);

    int shots = 42; // How many shots to take
    int delay = 1100; // The delay between each shot

    float time = ((shots * delay)/ 1000.0) - 1; // Formula for calculating time it takes to complete based of # of shots and delay
    int shotNum = 1000 * (time+1) / delay; // Formula for finding # of shots based off time and delay

    // Start Code
    cata_ratchet.set_value(true);

    chassis.moveTo(-61, 41, 1000);
    chassis.turnTo(-73, 68, 500);

    setDrive(45, 35);
    pros::delay(100);
    int x = inertial_sensor.get_rotation();
    
    
 
    // grabber.set_value(true);
    pros::delay(50);


    for (int i = 0; i < shots; i++) {
        shoot();

        if (i == 38) {
            controller.rumble("_.");
        }

        // pros::lcd::set_text(1, "time: " + std::to_string(i));
        if (inertial_sensor.get_rotation() >= x) {
            setDrive(5, 15);
        }
        else if (inertial_sensor.get_rotation() <= x-2) {
            setDrive(15, 5);
        }
        else {
            setDrive(15, 10);
        }

        pros::delay(delay);
    }

    setDrive(0, 0);
    controller.rumble("-.");

    // catapult.move_velocity(200); // Spin the catapult back to the lowered position
    //Gives control to driver
    // grabber.set_value(false);

}
//---------------------------------------

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
    // Releases back wedge
    // grabber.set_value(true);
    // pros::delay(100);
    // grabber.set_value(false);
    // pros::delay(100);

    // Drives to net and shoots alliance triball
    chassis.setPose(56, -33, 90);
    chassis.moveTo(40, -30, 2000, 90, true); //Previous: 27
    chassis.turnTo(30, 0, 800, true); //Previous: 26
    // wings.set_value(true);
    chassis.moveTo(30, -13, 1500, 75, true); //Previous: 26
    chassis.turnTo(27, 0, 800, true);
    setDrive(-15, 20);
    pros::delay(150);
    setDrive(0, 0);
    pros::delay(100);
    // wings.set_value(false);
    shoot();
    pros::delay(300);

    // Drives to corner and takes triball out
    
    chassis.moveTo(30, -21, 3000, 70);
    chassis.turnTo(82, -71, 1000, true);
    chassis.moveTo(64, -49, 3000, 70, true);
    // pros::delay(1000);

    grabber.set_value(true);
    pros::delay(500);
    chassis.turnTo(30, -65, 1000);
    // chassis.moveTo(51, -55, 1500, 80);
    grabber.set_value(false);

    // Touch the pole for AWP

    // Goes to lower pole
    chassis.moveTo(65.5, -32, 2000, 70, true);
    chassis.turnTo(65.5, 0, 1000, true);
    chassis.moveTo(65.5, -18, 2000, 70, true);
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


    chassis.moveTo(-60, -35, 500); //Back Up


    chassis.turnTo(-15, -22, 600); //First Tri-Ball
    setIntake(55);
    chassis.moveTo(-15, -28, 5000, 80); //First Tri-Ball

    chassis.turnTo(-17, -54, 1000); //Net
    setIntake(-80);
    chassis.moveTo(-17, -45, 500, 90); //Net
    pros::delay(100);

    chassis.turnTo(-15, -13, 1000); //Second Tri-Ball
    setIntake(50);
    chassis.moveTo(-15, -16, 2000, 80); //Second Tri-Ball
    pros::delay(100);

    chassis.turnTo(-17, -54, 1250); //Net
    //wings.set_value(true);
    setIntake(-35);
    chassis.moveTo(-17, -40, 1000, 90); //Net
    //wings.set_value(false);
    pros::delay(100);

    chassis.turnTo(-32, -15, 1000); //Third Tri-Ball
    setIntake(50);
    chassis.moveTo(-32, -18, 2000, 90); //Third Tri-Ball
    pros::delay(100);

    chassis.turnTo(-24, -54, 1000); //Net
    setIntake(-25);
    chassis.moveTo(-24, -45, 1000, 100); //Net
    pros::delay(100);


    //chassis.moveTo(-65, -16, 1000, 90, true); //Pole

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

//Not Using
void offense_AWP() {
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


    chassis.moveTo(-60, -35, 500); //Back Up


    chassis.turnTo(-15, -22, 600); //First Tri-Ball
    setIntake(50);
    chassis.moveTo(-17, -28, 5000, 85); //First Tri-Ball

    chassis.turnTo(-17, -54, 1000); //Net
    setIntake(-80);
    chassis.moveTo(-17, -40, 500, 90); //Net
    pros::delay(100);

    chassis.turnTo(-15, -13, 1000); //Second Tri-Ball
    setIntake(50);
    chassis.moveTo(-15, -16, 2000, 80); //Second Tri-Ball
    pros::delay(100);

    chassis.turnTo(-17, -54, 1250); //Net
    // wings.set_value(true);
    setIntake(-35);
    chassis.moveTo(-17, -38, 1000, 80); //Net
    // wings.set_value(false);

    chassis.moveTo(-65, -30, 2000, true); //Pole
    chassis.turnTo(-65, 0, 1000, true); //Pole
    chassis.moveTo(-65, -18, 2000, 80, true); //Pole
    grabber.set_value(true);
    pros::delay(100);

    hold_triball.suspend();

}

void defense_auton() {
    //pros::Task hold_intake_task(intakeLimit);

    chassis.setPose(56, -33, 90);
    chassis.moveTo(27, -33, 2000, 90, true);
    chassis.turnTo(26, 0, 800, true);
    wings.set_value(true);
    chassis.moveTo(26, -13, 1500, 75, true);
    setDrive(-15, 20);
    pros::delay(150);
    setDrive(0, 0);
    pros::delay(200);
    wings.set_value(false);
    shoot();
    pros::delay(350);

    chassis.moveTo(30, -24, 3000, 70);
    chassis.turnTo(77, -70, 1000);
    chassis.moveTo(49, -40, 3000, 70);



    // chassis.turnTo(-5, 0, 1000);
    // setIntake(127);
    // chassis.turnTo(-20, 0, 1000, true);
    // shoot();



    //hold_intake_task.suspend();

}


void defense_MOA() {
    //pros::Task hold_triball(intakeLimit);

    chassis.setPose(58, -37, -75);
    wings.set_value(true);
    pros::delay(100);
    wings.set_value(false);
    setIntake(127);

    //Move to Middle Tri-Ball
    chassis.moveTo(10, -27, 1500, 70); 
    pros::delay(200);
    setIntake(0);
    chassis.moveTo(15, -27, 800, 70);

    //Move to Middle Bar
    chassis.turnTo(15, 0, 800, true);
    wings.set_value(true);
    chassis.moveTo(15, -13, 1500, 75, true);
    wings.set_value(false);
    setDrive(-15, 20);
    pros::delay(100);
    setDrive(0, 0);
    pros::delay(100);
    shoot();
    pros::delay(350);

    //Move to Corner
    chassis.moveTo(15, -17, 1000, 70);
    chassis.turnTo(70, -42, 1000);
    chassis.moveTo(59, -37, 1000, 70);

    //Move to Pole
    chassis.turnTo(59, 0, 800, true);
    chassis.moveTo(59, -17, 1500, 70, true);

    //hold_triball.suspend();


}

void testAuton2(){
    chassis.setPose(60, 17, 180);
    chassis.moveTo(54.5, 30, 10000, 50);
    chassis.moveTo(40, 30, 10000, 50);
}