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
    pros::Task pos_track(screen);
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

    driveLB.set_brake_mode(MOTOR_BRAKE_HOLD);
	driveLM.set_brake_mode(MOTOR_BRAKE_HOLD);
    driveLF.set_brake_mode(MOTOR_BRAKE_HOLD);
    driveLH.set_brake_mode(MOTOR_BRAKE_HOLD);

    driveRB.set_brake_mode(MOTOR_BRAKE_HOLD);
	driveRM.set_brake_mode(MOTOR_BRAKE_HOLD);
    driveRF.set_brake_mode(MOTOR_BRAKE_HOLD);
    driveRH.set_brake_mode(MOTOR_BRAKE_HOLD);

    // Auton selector
    // switch (selector::auton) {
    //     case 1:
    //         // Safe 5 Triball Auton
    //         offense_auton_safe();
    //         break;

    //     case 2:
    //         // 
    //         offense_last_min();
    //         // offense_auton_midrush_new();
    //         break;

    //     case 3:
    //         // offense_auton_6balls_v2();
    //         break;
        
    //     case -1:
    //         // Safe
    //         defense_awp();
    //         break;
        
    //     case -2:
    //         // Midrush
    //         defense_last_min();
    //         break;

    //     case -3:
    //         // Max Potential
    //         defense_auton_max_potential();
    //         break;

    //     case 0:
    //         auton_skills();
    //         break;
    // } 

    // auton_skills();
    // offense_auton_safe(); //SLOT 3
    // defense_awp(); // SLOT 4
    offense_auton_max_potential(); // SLOT 5

    
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
    // chassis.setPose(0, 0, 0);

    // driveLB.set_brake_mode(MOTOR_BRAKE_HOLD);
	// driveLM.set_brake_mode(MOTOR_BRAKE_HOLD);
    // driveLF.set_brake_mode(MOTOR_BRAKE_HOLD);
    // driveLH.set_brake_mode(MOTOR_BRAKE_HOLD);

    // driveRB.set_brake_mode(MOTOR_BRAKE_HOLD);
	// driveRM.set_brake_mode(MOTOR_BRAKE_HOLD);
    // driveRF.set_brake_mode(MOTOR_BRAKE_HOLD);
    // driveRH.set_brake_mode(MOTOR_BRAKE_HOLD);

    // pid_test();

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


    // pros::Task MatchLoads(SetMatchLoad);
    // pid_test();
    // pros::Task kicker_task(kickerTask);
    //pros::Task pistonBoost_task(pistonBoostTask);

    // COMMENT THIS FOR DRIVER SKILLS
    //wingF.set_value(false);
	//wingB.set_value(false);
    ActivateWings(false);
    currentIntake = true;
    intake_up.set_value(true);
    
    my_opcontrol();
}   