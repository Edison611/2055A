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
    setCatapult(133.33);
    pros::delay(21150);
    setCatapult(0);
    // SmatchLoad(47, 500);
    // matchLoad(2, 525); // FOR TESTING
    // wingF.set_value(false);
	// wingB.set_value(false);
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

void liftRam(int timeout) {
    int time = 0;
    while (abs(int(inertial_sensor.get_roll())) <= 7 && abs(int(inertial_sensor.get_pitch())) <= 7) {
        if (time >= timeout) {
            break;
        }
        setDrive(600, 600);
        pros::delay(10);
        time += 10;
    }
    setDrive(0, 0);
    while (abs(int(inertial_sensor.get_roll())) >= 1 || abs(int(inertial_sensor.get_pitch())) >= 1) {
        if (time >= timeout) {
            break;
        }
        setDrive(-150, -150);
        pros::delay(10);
        time += 10;
    }
    setDrive(0, 0);
}

void secondRam(int backUpInches, int forwardMillis, int backUpTimeout, bool side) {
    if (side == false) {
        if (chassis.getPose().x < 0){
            chassis.moveToPose(chassis.getPose().x + backUpInches, chassis.getPose().y, chassis.getPose().theta, backUpTimeout);
        }
        else {
            chassis.moveToPose(chassis.getPose().x - backUpInches, chassis.getPose().y, chassis.getPose().theta, backUpTimeout);
        }
        setDrive(600, 600);
        pros::delay(forwardMillis);
        setDrive(0, 0);
    }
    else {
        if (chassis.getPose().y < 0){
            chassis.moveToPose(chassis.getPose().x, chassis.getPose().y - backUpInches, chassis.getPose().theta, backUpTimeout);
        }
        else {
            chassis.moveToPose(chassis.getPose().x, chassis.getPose().y + backUpInches, chassis.getPose().theta, backUpTimeout);
        }
        setDrive(600, 600);
        pros::delay(forwardMillis);
        setDrive(0, 0);
    }
}

// NEW FEATURE
void driverAssist() {
    lemlib::Pose pose = chassis.getPose();

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
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
    chassis.moveToPose(pose.x + x_new, pose.y + y_new, pose.theta, timeout, {.forwards = dir, .maxSpeed = maxSpeed});
}

/**
 * @brief Turns to the position on the field
 * 
 * @param degrees 
 * @param timeout 
 */
void turnTo(double degrees, int maxSpeed, int timeout, bool forwards, bool async) {
    lemlib::Pose pose = chassis.getPose();
    double rad = degrees * 3.14159265358979323846 / 180;
    double x_offset = sin(rad) * 100;
    double y_offset = cos(rad) * 100;
    chassis.turnTo(pose.x+x_offset, pose.y+y_offset, timeout, forwards, maxSpeed, async);
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
void vector(double x, double y, bool reversed, int maxSpeed, int turnTimout, int driveTimeout) {
    chassis.turnTo(x, y, turnTimout, false, reversed);
    // chassis.moveTo(x, y, chassis.getPose().theta, driveTimeout, false, !reversed, 0, 0.6, maxSpeed);
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
        driveLH.set_brake_mode(MOTOR_BRAKE_COAST);

        driveRB.set_brake_mode(MOTOR_BRAKE_COAST);
        driveRM.set_brake_mode(MOTOR_BRAKE_COAST);
        driveRF.set_brake_mode(MOTOR_BRAKE_COAST);
        driveRH.set_brake_mode(MOTOR_BRAKE_COAST);

    }
    else if (mode == "brake") {
        driveLB.set_brake_mode(MOTOR_BRAKE_BRAKE);
        driveLM.set_brake_mode(MOTOR_BRAKE_BRAKE);
        driveLF.set_brake_mode(MOTOR_BRAKE_BRAKE);
        driveLH.set_brake_mode(MOTOR_BRAKE_BRAKE);

        driveRB.set_brake_mode(MOTOR_BRAKE_BRAKE);
        driveRM.set_brake_mode(MOTOR_BRAKE_BRAKE);
        driveRF.set_brake_mode(MOTOR_BRAKE_BRAKE);
        driveRH.set_brake_mode(MOTOR_BRAKE_BRAKE);
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
void wallReset(std::string wall, std::string sensor) {
    double Pi = 3.14159265358979323846;
    if (wall == "top" && sensor == "left") {
        double inches = distance_sensorL.get() * 0.0393701;
        double distance = inches * cos((Pi/2)-(chassis.getPose().theta*Pi/180));
        chassis.setPose(chassis.getPose().x, 71 - (distance + 4 * cos((Pi/2)-(chassis.getPose().theta*Pi/180))), chassis.getPose().theta);
    }
    else if (wall == "top" && sensor == "right") {
        double inches = distance_sensorR.get() * 0.0393701;
        double distance = inches * cos((Pi/2)-(chassis.getPose().theta*Pi/180));
        chassis.setPose(chassis.getPose().x, 71 - (distance + 4 * cos((Pi/2)-(chassis.getPose().theta*Pi/180))), chassis.getPose().theta);
    }
    else if (wall == "bottom" && sensor == "left") {
        double inches = distance_sensorL.get() * 0.0393701;
        double distance = inches * cos((Pi/2)-(chassis.getPose().theta*Pi/180));
        chassis.setPose(chassis.getPose().x, -71 + (distance + 4 * cos((Pi/2)-(chassis.getPose().theta*Pi/180))), chassis.getPose().theta);
    }
    else if (wall == "bottom" && sensor == "right"){
        double inches = distance_sensorR.get() * 0.0393701;
        double distance = inches * cos((Pi/2)-(chassis.getPose().theta*Pi/180));
        chassis.setPose(chassis.getPose().x, -72 + (distance + 4 * cos((Pi/2)-(chassis.getPose().theta*Pi/180))), chassis.getPose().theta);
    }
    else if (wall == "right" && sensor == "right") {
        double inches = distance_sensorR.get() * 0.0393701;
        double distance = inches * cos((Pi/2)-(chassis.getPose().theta*Pi/180));
        chassis.setPose(71 - (distance + 4 * cos((Pi/2)-(chassis.getPose().theta*Pi/180))), chassis.getPose().y, chassis.getPose().theta);
    }
    else if (wall == "right" && sensor == "left") {
        double inches = distance_sensorL.get() * 0.0393701;
        double distance = inches * cos((Pi/2)-(chassis.getPose().theta*Pi/180));
        chassis.setPose(71 - (distance + 4 * cos((Pi/2)-(chassis.getPose().theta*Pi/180))), chassis.getPose().y, chassis.getPose().theta);
    }

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
