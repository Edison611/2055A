#include "main.h"
#include "lemlib/api.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include "pros/vision.h"
#include <string>


void initialize() {
	pros::lcd::initialize();

    chassis.calibrate();

    // driveLB.set_brake_mode(MOTOR_BRAKE_HOLD);
    // driveLF.set_brake_mode(MOTOR_BRAKE_HOLD);

    // driveRB.set_brake_mode(MOTOR_BRAKE_HOLD);
    // driveRF.set_brake_mode(MOTOR_BRAKE_HOLD);

    ptoR1.set_brake_mode(MOTOR_BRAKE_HOLD);
    ptoR2.set_brake_mode(MOTOR_BRAKE_HOLD);

    ptoL1.set_brake_mode(MOTOR_BRAKE_HOLD);
    ptoL2.set_brake_mode(MOTOR_BRAKE_HOLD);

    catapult.set_brake_mode(MOTOR_BRAKE_HOLD);

    // pros::Task holding(cata_hold);
    // pros::Task pos_track(screen);
    // pros::Task print_task(print_info);
    

    pros::delay(2000);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}


/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void autonomous() {
    // pros::Task log_task(log_data);
    // auton_skills(); // SLOT 4
    offense_auton(); // SLOT 6
    // offense_auton_elim();
    // offense_AWP();
    // solo_auton(); // SLOT 5
    // test_auton(); // SLOT 3
    // defense_auton_elim(); // SLOT 7


}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
   chassis.setPose(0, 0, 0);
   // chassis.moveTo(24, 24, -90, 2000, false, true, 1, 0.6, 127, false);
    //chassis.moveTo(24, 24, -90, 2000);
   //driver_skills();
   //chassis.follow("curvetest8.txt", 20000, 10.0);
    // pros::Task MatchLoads(SetMatchLoad);
   my_opcontrol();
}   