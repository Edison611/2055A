#include "lemlib/asset.hpp"
#include "lemlib/pose.hpp"
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include "pros/vision.h"
#include <cmath>
#include <string>

// TEST AUTONS

void test_auton() {
    turnToDir(90, false, 40, 500); // should turn 270 degrees to the left until it reaches 90 degrees, at speed 
    turnToDir(90, true, 90, 2000);
}

void test_auton2() {

}

void test_auton3() {

}

// ------------------------------------------------------------------------------------------------------
// AUTONOMOUS CODES
// ------------------------------------------------------------------------------------------------------

void driver_skills() {
    // Calibration and Robot Setup
    chassis.setPose(-40, 55, -90);
    // pros::Task log_task(log_data);
    shoot();
    wingF.set_value(true);
    pros::delay(200);
    wingF.set_value(false);

    // Begin
    setIntake(127);
    turnTo(-135, 127, 500);
    chassis.moveToPose(-58.75, 36, -135, 700);
    turnTo(180, 127, 600);
    setIntake(-127);
    
    ram(400, 1);
    pros::delay(100);
    chassis.setPose(-60, 30, chassis.getPose().theta);
    pros::delay(100);

    // LINE UP TO SHOOT
    chassis.moveToPose(-60, 49, 180, 1200, {.forwards=false});  
    turnTo(107, 127, 800);

    wingB.set_value(true);
    wingF.set_value(true);

    setIntake(0);
}

// ASSET(skills_txt);

void auton_skills() {
    // Calibration and Robot Setup
    chassis.setPose(-40, 55, -90);
    pros::Task log_task(log_data);
    shoot();
    wingF.set_value(true);
    pros::delay(200);
    wingF.set_value(false);

    // Begin
    setIntake(127);
    turnTo(-135, 127, 500);
    chassis.moveToPose(-58.75, 36, -135, 700);
    turnTo(180, 127, 600);
    setIntake(-127);
    
    ram(400, 1);
    pros::delay(100);
    chassis.setPose(-60, 30, chassis.getPose().theta);
    pros::delay(100);

    // LINE UP TO SHOOT
    chassis.moveToPose(-60, 49, 180, 1200, {.forwards=false});  
    turnTo(107, 127, 800);

    wingB.set_value(true);
    wingF.set_value(true);
    setBrake("brake");

    // shoots x number of times
    // can choose length of gaps between shots
    setIntake(0);
    matchLoad(2, 500); // 500 MILLISECONDS FOR COMPETITIONS /|\ 45 Matchloads Minimum
    setBrake("coast");
    wingF.set_value(false);
    wingB.set_value(false);
    pros::delay(300);
    // chassis.follow(skills_txt, float lookahead, int timeout)

    vector(-40, 57, false, 127, 600, 1000);
    turnTo(90);
    // START MOVING TO OTHER SIDE
    chassis.moveToPose(30, 62, 90, 2000);

    // SIDE RAM ON LEFT #1
    chassis.moveToPose(64, 40, 135, 1000);
    turnTo(180, 127, 500);

    setIntake(-127);
    ram(500, 1);
    chassis.setPose(chassis.getPose().x, 32, chassis.getPose().theta);
    setIntake(-30);

    // BACK UP and MOVE TO MIDDLE
    chassis.moveToPose(60, 48, 190, 1200, {.forwards=false});
    turnTo(75, 127, 600);
    chassis.moveToPose(39, 43, 75, 1400, {.forwards=false});
    // wingB.set_value(true);
    chassis.moveToPose(18, 35, 0, 1200, {.forwards=false});

    // MIDDLE RAM #1 (LEFT SIDE)
    wingB.set_value(true);
    chassis.moveToPose(25, 25, -40, 800, {.forwards=false});
    turnTo(-80, 80, 500);
    ram(800, -1);
    pros::delay(100);
    chassis.setPose(39, chassis.getPose().y, chassis.getPose().theta);
    pros::delay(100);
    
    // MIDDLE RAM #2 (RIGHT SIDE)
    chassis.moveToPose(20, 14, -80, 1000);
    turnTo(-150, 127, 500);
    wingB.set_value(false);
    pros::delay(250);
    chassis.moveToPose(18, 0, 180, 1000);
    chassis.moveToPose(18, -26, 85, 1200);
    // wingF.set_value(true);
    wingF.set_value(true);
    pros::delay(200);
    turnTo(65, 90, 800);
    ram(850, 1);
    pros::delay(100);
    chassis.setPose(39, -19, chassis.getPose().theta);
    pros::delay(100);

    // Middle Ram #3 (In the middle)
    // chassis.moveToPose(20, -14, 90, 1200, false, false);
    wingF.set_value(false);
    chassis.moveToPose(10, 15, 90, 1000, {.forwards=false});
    // turnTo(90, 127, 400);
    // wingF.set_value(true);
    // pros::delay(300);
    // ram(800, 1);
    // chassis.setPose(39, chassis.getPose().y, chassis.getPose().theta);
    // chassis.moveToPose(25, 0, 90, 700, false, false);
    // wingF.set_value(false);
    // chassis.moveToPose(20, -20, 20, 1400, false, false);
    
    chassis.turnTo(48, -48, 600);
    // wingF.set_value(true);
    chassis.moveToPose(46, -46, 120, 1500);
    // wingF.set_value(false);
    // driveFwd(-10, 1000, 127);

    // RIGHT SIDE RAM #1 + 2
    turnTo(30);
    ram(500, 1);
    chassis.moveToPose(chassis.getPose().x, chassis.getPose().y - 8.5, 0, 800, {.forwards=false});
    ram(500, 1);
    pros::delay(100);
    chassis.setPose(60, -30, chassis.getPose().theta);
    setIntake(0);
    
    // Back up
    chassis.moveToPose(60, -40, 0, 800, {.forwards=false});
    turnTo(225, 127, 600);
    chassis.moveToPose(40, -64, -90, 1000);
    turnTo(-90, 127, 400);

    // chassis.moveToPose(33, -62, 90, 1200, false, false);

    // CLIMB
    // turnTo(-90, 127, 1200);
    climb.set_value(true);
    setIntake(0);
    setDrive(600, 600);
    pros::delay(2000);
    // driveFwd(70, 2000, 127);
    climb.set_value(false);
    setDrive(0, 0);
}

void defense_awp() {
    
    /* Shoot Pre-Load Triball */
    chassis.setPose(-41.25, -54.25, 90);
    shoot();
    pros::delay(500);
    wingF.set_value(true);
    pros::delay(500);
    wingF.set_value(false);
    turnTo(63);
    matchLoad(1, 500);

    /* Take Triball Out of Corner */
    chassis.moveToPose(-55, -49, 138, 3500, {.forwards=false});
    wingF.set_value(true);
    pros::delay(500);
    chassis.moveToPose(-52, -52, 135, 2000);
    turnTo(100);
    wingF.set_value(false);

    /* Move to Elevation Bar */
    setIntake(-127); // to shoot triballs it touches to the other side of the field
    chassis.moveToPose(-12, -58, 90, 3000);
    pros::delay(500);
    setIntake(0);
    
}

void defense_auton_max_potential() {
    chassis.setPose(-41.25, -54.25, 90);
    shoot();
    pros::delay(250);
    wingF.set_value(true);
    pros::delay(300);
    wingF.set_value(false);
    turnTo(63);
    matchLoad(1, 500);

    chassis.moveToPose(-55, -49, 138, 3000, {.forwards=false});
    wingF.set_value(true);
    pros::delay(300);
    chassis.moveToPose(-52, -52, 135, 2000);
    turnTo(100);
    wingF.set_value(false);
    pros::delay(200);

    turnTo(45);
    chassis.moveToPose(-39, -12, 0, 2200);
    turnTo(-90);
    wingB.set_value(true);
    pros::delay(300);
    chassis.moveToPose(0, -12, -90, 2000, {.forwards=false});
    wingB.set_value(false);     
    //chassis.moveToPose(-11.5, -8, -90, 1000);
    turnTo(-180);
    //chassis.moveToPose(-11.5, -50, -180, 2000);
    chassis.moveToPose(6, -60, -180, 2000, {.maxSpeed=80});
    // wingF.set_value(true);
}

/**
 * @brief defensive autonomous route
 */
void defense_auton_midrush() {

    /**NEW*/
    chassis.setPose(36, 55, 0);
    wingF.set_value(true);
    wingB.set_value(true);
    pros::delay(500);
    wingF.set_value(false);
    wingB.set_value(false);

    chassis.moveToPose(36, 10, 0, 1300, {.forwards=false});
    // turnTo(195, 127, 650);
    // chassis.moveToPose(36, 15, 195, 800);
    turnTo(90);
    wingB.set_value(true);
    pros::delay(400);
    chassis.moveToPose(-30, 10, 90, 1500, {.forwards=false});
    wingB.set_value(false);
    // setIntake(127);
    chassis.moveToPose(24, 10, 90, 1500);
    turnTo(180);
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
    // Capybaras Website Coordinates -- Courtesy of Edison Ying

    // 46, -56.5, 45
    // 55, -45, 45
    // 44, -55, 45
    // 58, -32, 0
    // 60, -45, 0
    // 60, -28, 0
    // 62, -40, -10

    // 13, -28, -60
    // 20, -20, 40
    // 9, -5, -35
    // 68, -7, 90

    // Corner & Alliance Tri-Ball
    chassis.setPose(46.75, -61, 45);
    wingF.set_value(true);
    setIntake(127);
    chassis.moveToPose(53.75, -52.5, 45, 1200);
    turnTo(-12, 127, 500);
    wingF.set_value(false);
    setIntake(-127);
    chassis.moveToPose(56, 0, 0, 900);
    chassis.moveToPose(57, -50, 0, 900, {.forwards=false});
    chassis.moveToPose(62, 10, 0, 900);
    pros::delay(200);
    chassis.setPose(chassis.getPose().x, -30, chassis.getPose().theta);
    pros::delay(200);
    setIntake(0);
    chassis.moveToPose(60, -55, -10, 800, {.forwards=false});
    

    // Middle Tri-Balls
    chassis.turnTo(-5, -23, 800);
    setIntake(127);
    chassis.moveToPose(10, -29, -67, 1200);
    pros::delay(250);
    turnTo(35, 100);
    chassis.moveToPose(15, -7, 35, 800);
    wingF.set_value(true);
    turnTo(90);
    pros::delay(100);
    chassis.moveToPose(60, -7, 90, 1200);
    chassis.setPose(40, chassis.getPose().y, chassis.getPose().theta);
    pros::delay(150);
    chassis.moveToPose(14, -7, 90, 1000, {.forwards=false});
    wingF.set_value(false);

    // Last
    setIntake(127);
    chassis.turnTo(4, 0, 800);
    chassis.moveToPose(4, 0, -70, 1000);
    // turnTo(-90);
    // chassis.moveToPose(-15, -3, -70, 1000);
    pros::delay(300);
    // chassis.moveToPose(8, -5, -25, 800);
    turnTo(90);
    setIntake(-30);
    wingF.set_value(true);
    chassis.moveToPose(60, -6, 90, 1200);
    setIntake(0);
    chassis.moveToPose(25, -8, 90, 900, {.forwards=false});
    wingF.set_value(false);
}

void offense_auton_midrush() {
    chassis.setPose(-43.5, 59, 164);
    
    wingF.set_value(true); // lower front wings so intake is lowered
    setIntake(127); // intake
    chassis.moveToPose(-28, 8, 164, 1200); // async true
    chassis.waitUntil(5); // waits until bot has travelled 5 inches
    wingF.set_value(false); // close front wings
    pros::delay(1200);
    chassis.moveToPose(-30, 60, 265, 2000, {.forwards=false}); // move behind the bar, to the right of short barrier, facing bar
   
    //chassis.moveToPose(-54, 52, 230, 1750, true); // move to get corner triball out
    chassis.moveToPose(-60, 40, 190, 1400);
    chassis.waitUntil(5); // waits until bot has travelled 5 inches
    wingF.set_value(true); // open the wing to get corner triball out
    pros::delay(1400);
    setIntake(-20);

    wingF.set_value(false); // close wing
    chassis.moveToPose(-55, 55, 210, 1200, {.forwards=false}); // back up
    chassis.moveToPose(-72, -00, 180, 1000);
    chassis.moveToPose(chassis.getPose().x, chassis.getPose().y + 7.5, chassis.getPose().theta, 850, {.forwards=false});
    ram(500, 1);
    pros::delay(100);
    chassis.setPose(chassis.getPose().x, 30, chassis.getPose().theta);
    pros::delay(100);
    // Go for middle triballs
    chassis.moveToPose(-52, 52, 220, 1000, {.forwards=false});
    turnTo(123, 127, 600);
    setIntake(127);
    chassis.moveToPose(-11, 26, 120, 1500);
    pros::delay(500);
    turnTo(240, 80, 600);
    setIntake(0);
    wingF.set_value(true);
    chassis.moveToPose(-70, 10, 270, 1200);
    pros::delay(200);
    chassis.setPose(-40, chassis.getPose().y, chassis.getPose().theta);
    pros::delay(100);

    // Final Triball
    chassis.moveToPose(-15, 10, 270, 1200, {.forwards=false});
    wingF.set_value(false);
    // setIntake(127);
    // chassis.moveToPose(-2, 0, 110, 900);
    // turnTo(-90, 127, 600);
    // wingF.set_value(true);
    // chassis.moveToPose(-70, 5, -90, 800);
    // setIntake(0);

    // Back up
    chassis.moveToPose(-20, 5, -90, 800, {.forwards=false});
    wingF.set_value(false);
}

void offense_auton_6balls_v1() {
    
}

void offense_auton_6balls_v2() {
 
    // Capybaras Website Coordinates -- Courtesy of Edison Ying
    // 9, -58, -90
    // 40, -58, -90
    // 40, -58, -130
    // 55, -48, -130
    // 55, -48, -160
    // 59, -34, -180
    // 59, -38, -180
    // 59, -38, -90
    // 59, -38, 0
    // 59, -34, 0

    // Pole & Alliance Tri-Ball
    chassis.setPose(9, -58, -90);
    setIntake(70); // Intake: Input
    chassis.moveToPose(1, 1, 1, 1000);
    // Corner Tri-Ball
    chassis.moveToPose(40, -58, -90, 1750, {.forwards=false});
    turnTo(-130);
    wingF.set_value(true);
    chassis.moveToPose(55, -48, -130, 1151, {.forwards=false});
    wingF.set_value(false);

    // First Net
    turnTo(-160);
    wingF.set_value(true);
    // // wingL.set_value(true);
    chassis.moveToPose(59, -34, -180, 978, {.forwards=false});
    
    // Second Net
    wingF.set_value(false);
    // wingL.set_value(false);
    chassis.moveToPose(59, -38, -180, 800);
    turnTo(-90);
    turnTo(0);
    chassis.moveToPose(59, -34, 0, 800);
    setIntake(-127);
}