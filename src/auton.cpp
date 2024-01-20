#include "lemlib/pose.hpp"
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include "pros/vision.h"
#include <cmath>
#include <string>

// Curve paths
ASSET(skills_rams_txt);


ASSET(path1_txt);
ASSET(skills1_txt);
ASSET(leftcurve4_txt);
ASSET(skillstest_txt);
ASSET(leftcurve5_txt);

void test_auton() {
    //chassis.setPose(-38.14602236652237, -60.18132683982684, 100.82);
    // chassis.follow(leftcurve4_txt, 20000, 25);
    //chassis.follow(leftcurve5_txt, 20000, 25);
    //chassis.setPose(-12.482, -23.019)
    //chassis.follow(test_txt, 20000, 25);
    //chassis.waitUntil(dist) 
    //pose = chassis.currentPose();
    //setPose(end of path) 
    //setPose(pose)

    turnToDir(90, false, 40, 500); // should turn 270 degrees to the left until it reaches 90 degrees, at speed 
    turnToDir(90, true, 90, 2000);
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
    // Calibration and Robot Setup
    chassis.setPose(-40, 55, -90);
    shoot();
    wingF.set_value(true);
    pros::delay(400);
    wingF.set_value(false);

    // Begin
    setIntake(127);
    turnTo(-135);
    chassis.moveTo(-58.75, 36, -135, 1200);
    turnTo(180);
    setIntake(-127);
    // setDrive(-280, -280);
    // pros::delay(200);
    
    ram(850, 1);
    chassis.setPose(chassis.getPose().x, 30, chassis.getPose().theta);
    pros::delay(500);
    
    chassis.moveTo(-60, 49, 180, 1500, false, false);  
    turnTo(107, 127, 800);

    
    setIntake(0);
    
}

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
    turnTo(-135);
    chassis.moveTo(-58.75, 36, -135, 800);
    turnTo(180);
    setIntake(-127);
    
    ram(400, 1);
    chassis.setPose(chassis.getPose().x, 30, chassis.getPose().theta);
    pros::delay(100);

    // LINE UP TO SHOOT
    chassis.moveTo(-60, 49, 180, 1200, false, false);  
    turnTo(106, 127, 800);

    wingB.set_value(true);
    wingF.set_value(true);
    setBrake("brake");
    pros::delay(100);

    // shoots x number of times
    // can choose length of gaps between shots
    setIntake(0);
    matchLoad(2, 550); // 550 MILLISECONDS FOR COMPETITIONS /|\ 45 Matchloads
    setBrake("hold");
    wingF.set_value(false);
    wingB.set_value(false);
    pros::delay(300);

    vector(-40, 57);
    turnTo(180);
    setDrive(-300, -300);
    pros::delay(800);
    setDrive(0, 0);
    lemlib::Pose l = chassis.getPose();
    chassis.setPose(l.x, 63, 180);
    pros::delay(200);
    chassis.moveTo(-35, 62, 180, 1200);
    turnTo(90);


    // START MOVING TO OTHER SIDE
    chassis.moveTo(30, 62, 90, 3000);

    // SIDE RAM ON LEFT #1
    chassis.moveTo(64, 40, 135, 2000);
    turnTo(180);

    setIntake(-127);
    chassis.moveTo(66, -10, 180, 1000);
    chassis.setPose(chassis.getPose().x, 30, chassis.getPose().theta);
    setIntake(-30);

    // BACK UP
    // chassis.moveTo(60, 43, 180, 1500, false, false); // SKILLS 1
    chassis.moveTo(60, 48, 190, 1500, false, false);

    // turnTo(75); // SKILLS 1
    turnTo(80);

    // chassis.moveTo(11, 36, 80, 1500, false, false);
    chassis.moveTo(35, 40, 75, 1400, false, false);
    wingB.set_value(true);
    chassis.moveTo(25, 25, 0, 1000, false, false);
    chassis.moveTo(40, 16, -90, 1559, false, false);
    // turnTo(90); // SKILLS 1
    // setDrive(-500, -500); // SKILLS !
    ram(500, -1);
    pros::delay(200);
    // setDrive(0, 0); // SKILLS 1

    // MIDDLE RAM #1    
    // turnTo(-75);
    // wingB.set_value(true);
    // pros::delay(250);
    // // ram(750, -1);
    // chassis.moveTo(60, 8, -90, 2000, false, false);  
    // chassis.moveTo(30, 8, -90, 600);
    // ram(500, -1);

    chassis.setPose(35, 8, chassis.getPose().theta);
    
    // MIDDLE RAM #2
    chassis.moveTo(15, 12, -80, 1500);
    turnTo(-120);
    wingB.set_value(false);
    pros::delay(200);
    // wingF.set_value(true);
    chassis.moveTo(5, 0, 180, 1500, false, true, 0, 0.6, 80);
    wingF.set_value(true);
    pros::delay(500);
    chassis.moveTo(18, -23, 85, 1500);
    turnTo(72);
    ram(1000, 1);

    // chassis.moveTo(30, 8, -90, 1750);
    // turnTo(-115);
    // wingB.set_value(false);
    // pros::delay(500);
    // turnTo(-90);
    // chassis.moveTo(5, 8, -90, 1000);
    // chassis.moveTo(2, -20, 0, 2250, false);
    // turnTo(253);
    // pros::delay(200);
    // wingB.set_value(true);
    // pros::delay(300);
    // chassis.moveTo(60, -10, -90, 2000, false, false);   
    // ram(500, -1);
    // wingB.set_value(false);
    chassis.setPose(36, -14, chassis.getPose().theta);
    pros::delay(300);

    // ONE VERSION
    // chassis.moveTo(20, -20, -130, 1400);
    // turnTo(-40);
    // chassis.moveTo(42, -46, -40, 2000, false, false);
    // turnTo(-120);
    // chassis.moveTo(60, 0, -180, 2800, false, false);
    wingF.set_value(false);
    chassis.moveTo(20, -14, 45, 1500, false, false);
    chassis.turnTo(53, -48, 900);
    // wingF.set_value(true);
    chassis.moveTo(55, -48, 120, 2500);
    // wingF.set_value(false);
    // driveFwd(-10, 1000, 127);

    // RIGHT SIDE RAM #3
    // turnTo(0);
    turnTo(30);
    chassis.moveTo(61, 30, 0, 1500);

    chassis.setPose(chassis.getPose().x, -28, chassis.getPose().theta);
    
    chassis.moveTo(33, -62, 90, 1200, false, true);
    turnTo(-90, 127, 1500);
    // climb.set_value(true);
    // setIntake(0);
    // setDrive(600, 600);
    // pros::delay(2000);
    // // driveFwd(70, 2000, 127);
    // climb.set_value(false);
    // setDrive(0, 0);
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
    chassis.moveTo(-55, -49, 138, 3500, false, false);
    wingF.set_value(true);
    pros::delay(500);
    chassis.moveTo(-52, -52, 135, 2000);
    turnTo(100);
    wingF.set_value(false);

    /* Move to Elevation Bar */
    setIntake(-127); // to shoot triballs it touches to the other side of the field
    chassis.moveTo(-12, -58, 90, 3000);
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

    chassis.moveTo(-55, -49, 138, 3000, false, false);
    wingF.set_value(true);
    pros::delay(250);
    chassis.moveTo(-48, -54, 100, 2000); //135
    //turnTo(100);
    wingF.set_value(false);
    pros::delay(200);

    turnTo(45);
    chassis.moveTo(-38, -11, 0, 2200);
    turnTo(-90);
    wingB.set_value(true);
    chassis.moveTo(-10, -12, -90, 2500, false, false);
    wingB.set_value(false);     
    //chassis.moveTo(-11.5, -8, -90, 1000);
    turnTo(-180);
    //chassis.moveTo(-11.5, -50, -180, 2000);
    chassis.moveTo(8, -60, -180, 2000);
}

/**
 * @brief defensive autonomous route
 */
void defense_auton_midrush() {

    /**NEW*/
    chassis.setPose(36, 55, 0);
    // shoot();
    // pros::delay(400);
    wingF.set_value(true);
    wingB.set_value(true);
    pros::delay(500);
    wingF.set_value(false);
    wingB.set_value(false);
    // turnTo(-36);
    // matchLoad(1, 500);
    // pros::delay(300);
    // turnTo(0);
    chassis.moveTo(36, 10, 0, 1300, false, false);
    // turnTo(195, 127, 650);
    // chassis.moveTo(36, 15, 195, 800);
    turnTo(90);
    wingB.set_value(true);
    pros::delay(400);
    chassis.moveTo(-30, 10, 90, 1500, false, false);
    wingB.set_value(false);
    // setIntake(127);
    chassis.moveTo(24, 10, 90, 1500);
    turnTo(180);
    // wingL.set_value(false);
    // turnTo(0);
    // turnTo(-90);
    // chassis.moveTo(8, 9, -90, 1500);
    // turnTo(225);
    // chassis.moveTo(50, , 45, 3000, false, false);
    // turnTo(-45);
    // wingF.set_value(true);
    // pros::delay(500);
    // chassis.moveTo(52, 52, 135, 2000);
    // turnTo(100);
    // wingF.set_value(false);

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
    // wingF.set_value(true);
    // wingF.set_value(true);
    setIntake(127);
    chassis.moveTo(53.75, -52.5, 45, 1200);
    turnTo(-12, 127, 500);
    wingF.set_value(false);
    //turnTo(-8);
    // wingF.set_value(false);
    // wingF.set_value(false);
    // chassis.moveTo(44, -55, 45, 1500, false, false);
    setIntake(-127);
    chassis.moveTo(56, 0, 0, 900);
    chassis.moveTo(57, -50, 0, 900, false, false);
    chassis.moveTo(58, 10, 0, 900);
    setIntake(0);
    chassis.moveTo(60, -55, -10, 800, false, false);

    // Middle Tri-Balls
    chassis.turnTo(-6, -21, 800);
    setIntake(127);
    chassis.moveTo(6, -27.5, -67, 1200);
    pros::delay(250);
    turnTo(35);
    wingF.set_value(true);
    chassis.moveTo(15, -10, 35, 800);
    turnTo(90);
    pros::delay(100);
    chassis.moveTo(60, -6, 90, 1200);
    pros::delay(150);
    wingF.set_value(false);
    chassis.moveTo(14, -7, 90, 1000, false, false);
    //chassis.turnTo(48, 5, 1000, false, false);

    // Last
    setIntake(127);
    turnTo(-90);
    chassis.moveTo(-15, -3, -70, 1000);
    pros::delay(300);
    // chassis.moveTo(8, -5, -25, 800);
    turnTo(90);
    setIntake(-30);
    wingF.set_value(true);
    chassis.moveTo(60, -6, 90, 1200);
    wingF.set_value(false);
    chassis.moveTo(25, -8, 90, 900, false, false);
    //turnTo(-60);
    //chassis.turnTo(-9, 1, 800);
    //setIntake(127);
    // chassis.moveTo(-15, 1, -60, 1400);
    // pros::delay(300);
    // chassis.turnTo(65, -8, 1000, false, false);
    // // wingF.set_value(true); // Change to wingL
    // wingF.set_value(true);
    // pros::delay(500);
    // setIntake(-127);
    // chassis.moveTo(68, -8, 90, 1300);
    // chassis.moveTo(30, -8, 90, 1000, false, false);
    // setIntake(0);

    
    // // Reverse into Net
    // chassis.setPose(-12, 56, 90);
    // // chassis.moveTo(-30, 56, 90, 800, false, true, 0.6, 3, 127);
    // claw.set_value(true);
    // pros::delay(650);+
    // chassis.moveTo(-20, 50, 90, 1500, false, false, 0.6, 3, 127);
    // chassis.moveTo(-50, 50, 45, 1500, false, false, 0.6, 3, 127);
    // chassis.moveTo(-62, 20, 0, 1200, false, false);
    
    // // Turn Around and Push into Net
    // chassis.turnTo(-60, 0, 1000, false, false, 50);   
    // // turnTo(180)
    // claw.set_value(false);
    // pros::delay(300);
    // chassis.moveTo(-60, -50, 180, 1300, false, true);
    // chassis.moveTo(-50, 50, 110, 1500, false, false);

    
    // // // Middle Triballs
    // chassis.turnTo(0, 0, 800);
    // // chassis.moveTo(-25, 25, 125, 1880, false, true, 0, 0.6); // Move towards centee
    // chassis.moveTo(0, 0, 140, 1500); // Move to back middle triball
    // claw.set_value(true);
    // pros::delay(800);
    // chassis.turnTo(-60, 10, 750, false, false, 50); // Turn to net
    // claw.set_value(false);  
    // ActivateWings(true);
    // chassis.moveTo(-50, 10, 270, 1200); // Ram in from the front
    // chassis.moveTo(-35, 10, 270, 1000); // Back up 
}

void offense_auton_midrush() {

    // Coordinates 
    // -41, 55, 180
    // -41, 55, 150
    // -16, 10, 152
    // -16, 10, -90
    // -70, 10, -90
    // -40, 10, -90
    // -20, 10, -90
    // -20, 10, 130
    // -8, 2, 130
    // -20, 10, 130
    // -20, 10, -90
    // -70, 10, -90
    // -40, 10, -90
    // -16, 10, -90
    // -16, 10, 35
    // -8, 22, 35
    // -16, 10, 35
    // -16, 10, -90
    // -70, 10, -90
    // -40, 10, -90
    // -14, 10, -90
    // -14, 10, -35
    // -45, 58, -35
    // -45, 58, 88
    // -10, 60, 88
    // -45, 58, 88
    // -45, 58, 225
    // -59, 45, 225
    // -59, 45, 180
    // -59, 0, 180

   chassis.setPose(-41, 55, 180);
   wingF.set_value(true);
   setIntake(127);
   turnTo(150);
   wingF.set_value(false);
   chassis.moveTo(-16, 10, 152, 1200);
   turnTo(-90);
   wingF.set_value(true);
   chassis.moveTo(-70, 10, -90, 1200);

   chassis.setPose(-40, 10, -90);
   chassis.moveTo(-20, 10, -90, 800, false, false);
   wingF.set_value(false);
   turnTo(130);
   chassis.moveTo(-8, 2, 130, 1000);
   pros::delay(200);
   chassis.moveTo(-20, 10, 130, 1000, false, false);
   turnTo(-90);
   chassis.moveTo(-70, 10, -90, 1200);

   chassis.setPose(-40, 10, -90);
   chassis.moveTo(-16, 10, -90, 800, false, false);
   turnTo(35);
   chassis.moveTo(-8, 22, 35, 1000);
   pros::delay(200);
   chassis.moveTo(-16, 10, 35, 1000, false, false);
   turnTo(-90);
   chassis.moveTo(-70, 10, -90, 1200);

   chassis.setPose(-40, 10, -90);
   chassis.moveTo(-14, 10, -90, 1000, false, false);
   turnTo(-35);
   chassis.moveTo(-45, 58, -35, 1200);
   turnTo(88);
   chassis.moveTo(-10, 60, 88, 1200);
   pros::delay(200);
   chassis.moveTo(-45, 58, 88, 1200, false, false);
   turnTo(225);
   chassis.moveTo(-59, 45, 225, 1200);
   turnTo(180);
   chassis.moveTo(-59, 0, 180, 1200);
}

void offense_auton_midrush_new() {
    chassis.setPose(-43.5, 59, 164);
    
    wingF.set_value(true); // lower front wings so intake is lowered
    setIntake(127); // intake
    chassis.moveTo(-30, 10, 164, 1500, true); // async true
    chassis.waitUntilDist(5); // waits until bot has travelled 5 inches
    wingF.set_value(false); // close front wings
    pros::delay(1250);
    chassis.moveTo(-33, 60, 265, 2000, false, false);
   
    chassis.moveTo(-60, 45, 200, 1750, true);
    chassis.waitUntilDist(8);
    wingF.set_value(true);
    pros::delay(1500);

    wingF.set_value(false);
    chassis.moveTo(-56, 55, 220, 1500, false, false);
    chassis.moveTo(-65, -20, 180, 1500);

    chassis.moveTo(-15, 60, 200, 2000, false, false);
}

void offense_auton_6balls_v1() {
    /* Pole & Alliance Tri-Balls */
    chassis.setPose(9, -60, -90);
    setIntake(70);
    // Intake: Input
    // chassis.moveTo(5, -60, -90, 400);   
    // Intake: Stop

    /* Curve Entry to Net + Corner Tri-Ball */
    chassis.moveTo(35, -60, -90, 1750, false, false);
    turnTo(-100);
    pros::delay(200);
    turnTo(60);
    chassis.moveTo(40, -60, 45, 1000, false, true);
    wingF.set_value(true);
    //chassis.moveTo(46, -55, 45, 1750, false, true);
    chassis.moveTo(56, -45, 45, 1750, false, true);
    wingF.set_value(false);
    // chassis.moveTo(50, -50, 45, 1000, false, false);
    chassis.moveTo(48, -55, 45, 1000, false, false);
    // wingL.set_value(true);
    chassis.moveTo(59, -45, 45, 1000, false, true);    
    // turnTo(0);
    // ram(500, 1);
    // chassis.setPose(59, -30, 0);
    chassis.moveTo(59, -30, 0, 1200, false, true);
    ram(200, -1);
    ram(200, 1);
    
    // turnTo(-100);
    // pros::delay(200);
    // turnTo(60);
    // wingF.set_value(true);
    // pros::delay(200);
    // chassis.moveTo(60, -45, 48, 1000, false, true);
    // pros::delay(100);
    // wingF.set_value(false);
    // pros::delay(200);
    // chassis.moveTo(35, -60, 60, 1000, false, false);
    // // chassis.moveTo(40, -55, -120, 800);
    // // chassis.moveTo(50, -50, -140, 809);
    // chassis.moveTo(57, -45, 30, 1750, false, true);
    // turnTo(0);
    // wingF.set_value(false);
    // pros::delay(200);
    // chassis.moveTo(57, -30, 0, 1000, false, true);
    
    /* Mirror Curve Entry + Re-Entry */
    // chassis.moveTo(57, -45, -180, 1000, false, true);
    // turnTo(30);    
    // chassis.moveTo(35, -60, 90, 1750, false, false);
    // wingF.set_value(true);
    // pros::delay(200);
    // chassis.moveTo(57, -45, 30, 1750, false, true);
    // turnTo(0);
    // wingF.set_value(false);
    // chassis.moveTo(57, -30, 0, 1000, false, true);


    // chassis.setPose(57, -30, -180);

    // /* Mirror Entry */
    // chassis.moveTo(57, -40, -180, 800);
    // turnTo(-90);
    // turnTo(0);
    // // Right Wing: Open
    // chassis.moveTo(57, -30, 0, 800);
    // Intake: Output
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

    // Corner Tri-Ball
    chassis.moveTo(40, -58, -90, 1750, false, false);
    turnTo(-130);
    wingF.set_value(true);
    chassis.moveTo(55, -48, -130, 1151, false, false);
    wingF.set_value(false);

    // First Net
    turnTo(-160);
    wingF.set_value(true);
    // // wingL.set_value(true);
    chassis.moveTo(59, -34, -180, 978, false, false);
    
    // Second Net
    wingF.set_value(false);
    // wingL.set_value(false);
    chassis.moveTo(59, -38, -180, 800, false, true);
    turnTo(-90);
    turnTo(0);
    chassis.moveTo(59, -34, 0, 800);
    setIntake(-127);

    // Rush Middle
}