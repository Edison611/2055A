#include "main.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
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

void skills_matchload() {
    matchLoad(47, 500);
    // matchLoad(2, 500); // FOR TESTING
    wingF.set_value(false);
	wingB.set_value(false);
}

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

// NEW FEATURE
void driverAssist() {
    lemlib::Pose pose = chassis.getPose();

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
        if (pose.y > 25 && pose.x < 0) {
        turnTo(107, 127, 800);
        wingB.set_value(true);
        }

        if (pose.y < -25 && pose.x < 0) {
        turnTo(73, 127, 800);
        wingB.set_value(true);
        }

        if (pose.y > 25 && pose.x > 0) {
        chassis.turnTo(55, 30, 100);
        }

        if (pose.y < -25 && pose.x > 0) {
        chassis.turnTo(55, -25, 100);
        }
    }
}

/**
 * @brief Drives x inches forward
 * We should change this function from Lemlib to our own function
 * 
 * @param inches 
 * @param timeout 
 * @param maxSpeed
 */
void driveFwd(double inches, int timeout=1000, float maxSpeed = 127) {
    lemlib::Pose pose = chassis.getPose();
    double x_new = inches * sin(pose.theta);
    double y_new = inches * cos(pose.theta);
    bool dir = inches > 0;
    chassis.moveToPose(pose.x + x_new, pose.y + y_new, pose.theta, timeout, {.forwards=dir, .maxSpeed=maxSpeed});
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
    double x_offset = sin(rad) * 30;
    double y_offset = cos(rad) * 30;
    chassis.turnTo(pose.x+x_offset, pose.y+y_offset, timeout, async, reversed, maxSpeed);
}

void turnToDir(int targetAngle, bool right, int maxSpeed, int timeout) {

    float actualMaxSpeed = maxSpeed * (600.0/127.0);
    int time = 0;
    double kP = 2.1;

    while (true) {
        /* If the amount of time in variable timeout has passed, the while loop breaks */
        if (time >= timeout) {
            break;
        }
        /* Get Current Angle */
        lemlib::Pose pose = chassis.getPose();
        int currentAngle = pose.theta;
        currentAngle = currentAngle % 360;

        if ((currentAngle - targetAngle) > 0) {
            if (right) {
                currentAngle = currentAngle - 360;
                int error = abs(targetAngle - currentAngle);
                if (abs(error) < 2) {
                    break;
                }
                if (error * kP > actualMaxSpeed) {
                    setDrive(actualMaxSpeed, -actualMaxSpeed);
                }
                else {
                    setDrive(error * kP, -error * kP);
                }
            }

            else {
                int error = abs(targetAngle - currentAngle);
                if (abs(error) < 2) {
                    break;                
                }
                if (error * kP > actualMaxSpeed) {
                    setDrive(-actualMaxSpeed, actualMaxSpeed);
                }
                else {
                    setDrive(-error * kP, error * kP);
                }
            }
        }


        if ((currentAngle - targetAngle) < 0) {
            if (right){
                int error = abs(targetAngle - currentAngle);
                if (abs(error) < 2) {
                    break;
                }
                if (error * kP > actualMaxSpeed) {
                    setDrive(actualMaxSpeed, -actualMaxSpeed);
                }
                else {
                    setDrive(error * kP, -error * kP);    
                }
            }
        

            else {
                currentAngle = currentAngle + 360;
                int error = abs(targetAngle - currentAngle);
                if (abs(error) < 2) {
                    break;
                }
                if (error * kP > actualMaxSpeed) {
                    setDrive(-actualMaxSpeed, actualMaxSpeed);
                }
                else {
                    setDrive(-error * kP, error * kP);
                }
            }
            // turn left:
            // right motors positive
            // left motors negative
        }
        pros::delay(20);
        time += 20;
    }
    setDrive(0, 0);
}


/**
 * @brief Turns and Drives straight to a specified coordinate
 * 
 * @param x 
 * @param y 
 * @param turnTimout timeout for turning (default to 1 second)
 * @param driveTimeout timeout for driving (default to 1 second)
 */
void vector(double x, double y, bool reversed, float maxSpeed, int turnTimout, int driveTimeout) {
    chassis.turnTo(x, y, turnTimout, false, reversed);
    chassis.moveToPose(x, y, chassis.getPose().theta, driveTimeout, {.forwards=!reversed, .maxSpeed=maxSpeed});
}


void matchLoad(int shots, int delay) {
    float time = ((shots * delay)/ 1000.0) - 1; // Formula for calculating time it takes to complete based of # of shots and delay
    int shotNum = 1000 * (time+1) / delay; // Formula for finding # of shots based off time and delay
    

    for(int i = 0; i < shots; i++) {
        shoot();
        pros::delay(delay);

        if (i+5 == shots) controller.rumble("-.");
    }
}

void setBrake(std::string mode) {
    if (mode == "coast") {
        driveLB.set_brake_mode(MOTOR_BRAKE_COAST);
        driveLM.set_brake_mode(MOTOR_BRAKE_COAST);
        driveLF.set_brake_mode(MOTOR_BRAKE_COAST);

        driveRB.set_brake_mode(MOTOR_BRAKE_COAST);
        driveRM.set_brake_mode(MOTOR_BRAKE_COAST);
        driveRF.set_brake_mode(MOTOR_BRAKE_COAST);

    }
    else if (mode == "brake") {
        driveLB.set_brake_mode(MOTOR_BRAKE_BRAKE);
        driveLM.set_brake_mode(MOTOR_BRAKE_BRAKE);
        driveLF.set_brake_mode(MOTOR_BRAKE_BRAKE);

        driveRB.set_brake_mode(MOTOR_BRAKE_BRAKE);
        driveRM.set_brake_mode(MOTOR_BRAKE_BRAKE);
        driveRF.set_brake_mode(MOTOR_BRAKE_BRAKE);
    }
    else if (mode == "hold") {
        driveLB.set_brake_mode(MOTOR_BRAKE_HOLD);
        driveLM.set_brake_mode(MOTOR_BRAKE_HOLD);
        driveLF.set_brake_mode(MOTOR_BRAKE_HOLD);

        driveRB.set_brake_mode(MOTOR_BRAKE_HOLD);
        driveRM.set_brake_mode(MOTOR_BRAKE_HOLD);
        driveRF.set_brake_mode(MOTOR_BRAKE_HOLD);
    }
}
/**
 * @brief Resets the position of the robot to a set distance 
 *        from the wall using the distance sensor
 */
void wallReset() {
    double inches = distance_sensor.get() * 0.0393701;
    chassis.setPose(10, 72 - (inches + 4), 90);
    pros::delay(200);
}

/**
 * @brief Detects whether there is a triball in front of the color sensor
 * 
 * @param triball the triball objectx
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