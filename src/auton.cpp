#include "lemlib/asset.hpp"
#include "lemlib/pose.hpp"
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include "pros/vision.h"
#include <cmath>
#include <string>
#include <sys/_intsup.h>

// Curve paths

void test_auton() {


}

void test_auton2() {
}


// ------------------------------------------------------------------------------------------------------
// AUTONOMOUS CODES
// ------------------------------------------------------------------------------------------------------

ASSET(s1_txt);
void auton_skills() {
    driveLB.set_brake_mode(MOTOR_BRAKE_HOLD);
	driveLM.set_brake_mode(MOTOR_BRAKE_HOLD);
    driveLF.set_brake_mode(MOTOR_BRAKE_HOLD);
    driveLH.set_brake_mode(MOTOR_BRAKE_HOLD);

    driveRB.set_brake_mode(MOTOR_BRAKE_HOLD);
	driveRM.set_brake_mode(MOTOR_BRAKE_HOLD);
    driveRF.set_brake_mode(MOTOR_BRAKE_HOLD);
    driveRH.set_brake_mode(MOTOR_BRAKE_HOLD);

    inertial_sensor.set_roll(0);
    chassis.setPose(-60, 46, 100);
    chassis.follow(s1_txt, 30, 900, true);
    wingFL.set_value(true);
    turnTo(0);
    wingFR.set_value(true);
    liftRam();
    wingFL.set_value(false);
}


void defense_awp() {
    
}

void defense_auton_max_potential() {
    
}

/**
 * @brief defensive autonomous route
 */
void defense_auton_midrush() {

}

/**
 * @brief offensive autonomous
 * 
 * 1. SCORE ALLIANCE TRIBALL (IMPORTANT)
 * 2. Grab the middle triball and score it
 * 3. Grab the triball in the middle away from the net and score it
 * 4. Grab the triball on our side and score it
 */
void offense_auton_safe() {

}

void offense_auton_midrush() {
}

