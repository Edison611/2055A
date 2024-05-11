#include "main.h"
#include "EZ-Template/api.hpp"
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

    // chassis.calibrate();
    // gps_sensor.initialize_full(30, 60, 270, 0, 0);

    driveLB.set_brake_mode(MOTOR_BRAKE_COAST);
	driveLM.set_brake_mode(MOTOR_BRAKE_COAST);
    driveLF.set_brake_mode(MOTOR_BRAKE_COAST);
    driveLH.set_brake_mode(MOTOR_BRAKE_COAST);

    driveRB.set_brake_mode(MOTOR_BRAKE_COAST);
	driveRM.set_brake_mode(MOTOR_BRAKE_COAST);
    driveRF.set_brake_mode(MOTOR_BRAKE_COAST);
    driveRH.set_brake_mode(MOTOR_BRAKE_COAST);


    catapult.set_brake_mode(MOTOR_BRAKE_HOLD);
    catapult2.set_brake_mode(MOTOR_BRAKE_HOLD);

    // selector::init();
    // pros::Task log_task(log_data);
    // pros::Task kicker_task(kickerTask);
    // pros::Task pos_track(screen);

    // ezChassis.pid_targets_reset();
    // ezChassis.drive_imu_reset(); 
    // ezChassis.drive_sensor_reset(); 
    // pros::Task print_task(print_info);
    

    // pros::delay(3000);
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
    // pros::Task pos_track(screen);

    // gps_sensor.set_position(0, 0, 0);
    

    driveLB.set_brake_mode(MOTOR_BRAKE_COAST);
	driveLM.set_brake_mode(MOTOR_BRAKE_COAST);
    driveLF.set_brake_mode(MOTOR_BRAKE_COAST);
    driveLH.set_brake_mode(MOTOR_BRAKE_COAST);

    driveRB.set_brake_mode(MOTOR_BRAKE_COAST);
	driveRM.set_brake_mode(MOTOR_BRAKE_COAST);
    driveRF.set_brake_mode(MOTOR_BRAKE_COAST);
    driveRH.set_brake_mode(MOTOR_BRAKE_COAST);
    // pid_test();
    // driver_skills();
    // pros::Task matchload_task(skills_matchload);



    
    my_opcontrol();   
    
}   