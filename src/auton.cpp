#include "lemlib/pose.hpp"
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include "pros/vision.h"
#include <cmath>
#include <string>

// Curve paths
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
    chassis.setPose(-40, -55, -90);
    // chassis.setPose(-40, -53, 90); // Facing forward
    shoot();
    // wingB.set_value(true);
    wingF.set_value(true);
    pros::delay(400);
    // wingB.set_value(false);
    wingF.set_value(false);

    // Begin
    setIntake(127);
    turnTo(-45);
    chassis.moveTo(-60, -36, -45, 1200);
    turnTo(0);
    setIntake(-127);
    chassis.moveTo(-60, 0, 0, 800);
    //---//
    // turnTo(130);
    // chassis.moveTo(-55, -42, 130, 1000, false, false);
    // chassis.moveTo(-60, -43, 130, 1000, false, false);  
    chassis.moveTo(-60, -39.5, 0, 1000, false, false);  
    turnTo(66.25);
    wingB.set_value(true);
    wingF.set_value(true);
    setBrake("brake");
    pros::delay(175);
    wingF.set_value(false);


    
    // shoots x number of times
    // can choose length of gaps between shots
    setIntake(0);
    matchLoad(45, 500);
    setBrake("coast");
    
    wingB.set_value(false);
}

void auton_skills() {
    //PATH (OLD)
    // -60, -39.5, 0
    // -60, -39.5, 69
    // -60, -39.5, 120
    // -32, -55, 120
    // -32, -55, 90
    // 38, -55, 90
    // 38, -55, 60
    // 58, -47.5, 45
    // 58, -47.5, 0
    // 60, 0, 0
    // 54, -45, 30
    // 54, -45, -50
    // 6, -5, -50
    // 6, -5, -90
    // 60, -6, -90
    // 8, -6, -90
    // 8, -6, 180
    // 8, 15, 180
    // 8, 15, -90
    // 60, 15, -90
    // 15, 15, -75
    // 15, 15, 115
    // 70, 5, 90
    // 30, 5, 90
    // Calibration and Robot Setup
    chassis.setPose(-40, -55, -90);
    // chassis.setPose(-40, -53, 90); // Facing forward
    shoot();
    // wingB.set_value(true);
    wingF.set_value(true);
    pros::delay(400);
    // wingB.set_value(false);
    wingF.set_value(false);

    // Begin
    setIntake(127);
    turnTo(-45);
    chassis.moveTo(-58.75, -36, -45, 1200);
    turnTo(0);
    setDrive(-200, -200);
    pros::delay(200);
    setIntake(-127);
    
    ram(500, 1);
    // chassis.moveTo(-58.75, 30, 0, 1000);
    //---//
    // turnTo(130);
    // chassis.moveTo(-55, -42, 130, 1000, false, false);
    // chassis.moveTo(-60, -43, 130, 1000, false, false);  
    chassis.moveTo(-60, -39.5, 0, 1000, false, false);  
    turnTo(66.25);
    wingB.set_value(true);
    // wingF.set_value(true);
    setBrake("brake");
    pros::delay(175);
    // wingF.set_value(false);


    
    // shoots x number of times
    // can choose length of gaps between shots
    setIntake(0);
    matchLoad(45, 550); // 550 MILLISECONDS FOR COMPETITIONS
    setBrake("coast");
    
    wingB.set_value(false);

    // OLD
    // turnTo(-10); // turns to close net
    // setIntake(-127); 
    // chassis.moveTo(-62, 20, 0, 1000); // rams net (these coordinates are way past net)
    // //chassis.setPose(-60, -30, 0);
    // chassis.moveTo(-62, -40, 0, 800, false, false); // moves back
    // setIntake(0);
    turnTo(120);
    ////////chassis.turnTo(-32, -55, 800);
    //////wingF.set_value(true);
    setIntake(127);
    chassis.moveTo(-32, -55, 120, 1400);
    turnTo(90);
    ///////wingF.set_value(false);
    pros::delay(200);
    // turnTo(90);
    // 46.75, -61


    // START MOVING TO OTHER SIDE

    chassis.moveTo(34, -55, 90, 1750);

    //**//
    turnTo(60);
    /////wingF.set_value(true);
    chassis.moveTo(56, -40, 50, 1000);
    turnTo(0);
    ////  wingF.set_value(false);
    
    setIntake(-127);
    /////chassis.moveTo(55, 20, 0, 1200);
    ram(500, 1);
    setIntake(0);

    // UNCOMMENT NEXT TWO LINES FOR 2nd RAM
    // chassis.moveTo(60, -38, 0, 1000, false, false);
    // chassis.moveTo(60, 0, 0, 1200);
    chassis.moveTo(56, -45, 0, 1000, false, false);
    ram(500, 1);
    //////chassis.moveTo(54, -45, 30, 1400, false, false);
    chassis.moveTo(56, -45, 0, 1000, false, false);
    turnTo(-60);
    // pros::delay(20000);
    //**//

    //chassis.turnTo(-2, -12, 800, false, true);
    
    chassis.moveTo(2, -15, -60, 2000);
    wingB.set_value(true);
    
    // -----------------------------------------------
    // START RAMMING
    // Ram #1
    //////////chassis.turnTo(47, 0, 1500, false, true, 60);
    // wingB.set_value(true);
    turnTo(-90);
    ram(750, -1);
    wingB.set_value(false);

    // Second ram
    // chassis.moveTo(10, 0, 120, 1750, false, false);
    setIntake(127);
    // chassis.moveTo(6, 0, -60, 1750);
    // turnTo(-90);
    // wingB.set_value(true);
    // chassis.moveTo(70, 0, -90, 1500, false, false);
    // wingB.set_value(false);

    chassis.moveTo(8, -6, -90, 1000);
    turnTo(-180);
    chassis.moveTo(8, 15, -180, 1200, false, false, 0, 0.6, 80);
    /////chassis.turnTo(47, 47, 1000, false, true);
    turnTo(-90);
    wingB.set_value(true);
    ram(750, -1);
    ////chassis.turnTo(47, 5, 2000, false, true, 50);

    // turnTo(-90);
    // setIntake(-127);
    //////chassis.moveTo(70, 10, -90, 1400, false, false);
    wingB.set_value(false);
    chassis.moveTo(15, 15, -75, 1000);
    turnTo(115);
    wingF.set_value(true);
    setIntake(-40);
    chassis.moveTo(70, 5, 90, 1000);    
    setIntake(0);
    wingF.set_value(false);
    chassis.moveTo(30, 5, 90, 800);
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
    pros::delay(1500);

    /* Take Out Corner Triball */
    turnTo(0);
    chassis.moveTo(-44.25, -48, 0, 1200);
    turnTo(-90);
    pros::delay(100);
    chassis.moveTo(-50, -48, -90, 1200);
    turnTo(180);
    wingF.set_value(true);
    chassis.moveTo(-50, -57.5, 180, 1200); // may lower y value (more negative)
    turnTo(-170);
    turnTo(90);
    pros::delay(100);


    wingF.set_value(false);

    /* Moving Toward Pole */
    chassis.moveTo(-15, -60, 90, 3000); 
    pros::delay(500);
    setIntake(127);
    
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
    chassis.moveTo(-11, -58, 90, 3000);
    pros::delay(500);
    setIntake(0);
    
    /*
    // Take triball out of corner
    setIntake(127);
    chassis.setPose(-47, -60, 142);
    chassis.moveTo(-51, -53, 142, 500); // moves backwards
    wingF.set_value(true);
    pros::delay(500);
    // chassis.moveTo(-51, -57, 142, 2000);
    // chassis.moveTo(-47, -57, 142, 2000); // moves forward to scoop triball out with maxspeed 80
    // chassis.moveTo(-49, -59, 142, 2000); // moves forward to scoop triball out with maxspeed 80
    chassis.moveTo(-50, -57, 142, 2000); // moves forward to scoop triball out with maxspeed 80
    // chassis.moveTo(-47, -57, 90, 2000); // turns to scoop
    turnTo(90);
    wingF.set_value(false);

    /*
    // Score alliance triball in net
    turnTo(-34, 112, 1750); 
    chassis.moveTo(-67, -35, -34, 5000);
    setIntake(0);
    turnTo(0);
    setIntake(-127);
    pros::delay(750);
    // chassis.moveTo(-67, -36, 0, 1000, false, false);
    // chassis.moveTo(-67, 10, 0, 1000);

    // Move to touch elevation bar 
    // chassis.moveTo(-67, -35, 0, 1000, false, false);
    chassis.moveTo(-67, -40, 0, 1000, false, false); // moves backwards away from net
    setIntake(0);
    turnTo(132);
    chassis.moveTo(-38, -56, 128, 3000);
    */

    /*
    turnTo(90);
    // chassis.moveTo(-8.5, -58, -90, 2000, false, false, 0, 0.59999999999999998, 80);
    setIntake(-127);
    chassis.moveTo(-32, -60, 90, 2000, false, true, 0, 0.59999999999999998, 80);
    pros::delay(500);
    setIntake(0);
    // chassis.moveTo(-53, -53, -38, 2000);
    // turnTo(-90);
    // chassis.moveTo(-8.5, -53, -90, 3000);
    */
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
 */
void defense_auton_elim() {

    /**NEW*/
    chassis.setPose(36, 62, 180);
    // wingL.set_value(true);
    pros::delay(300);
    // wingL.set_value(false);
    chassis.moveTo(36, 40, 180, 800);
    turnTo(195, 127, 650);
    chassis.moveTo(30, 15, 195, 800);
    //claw.set_value(true);
    setIntake(127);
    // wingL.set_value(true);
    pros::delay(300);
    turnTo(-90, 60);
    pros::delay(100);
    setIntake(0);
    // wingL.set_value(false);
    // turnTo(0);
    // turnTo(-90);
    chassis.moveTo(8, 9, -90, 1500);
    chassis.moveTo(50, 50, 45, 3000, false, false);
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
    chassis.moveTo(7, -7, 90, 1000, false, false);
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
    chassis.moveTo(30, -8, 90, 900, false, false);
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
   // Alliance tri-ball
    chassis.setPose(-41, 55, 180);
    setWings(true, false, 500);
    chassis.turnTo(-5, 0, 600);

    // Middle 2 tri-balls
    chassis.moveTo(-10, 9, 145, 1650);
    pros::delay(200);
    // claw.set_value(true);
    pros::delay(300);
    chassis.turnTo(-65, 8, 1500, false, false);
    // wingL.set_value(true);
    // claw.set_value(false);
    chassis.moveTo(-60, 8, 270, 1000);
    // wingL.set_value(false);

    // Last tri-ball 
    chassis.moveTo(-16, 13, 270, 2000, false, false);
    chassis.turnTo(-4, 24, 800);    
    // claw.set_value(true);
    pros::delay(600);
    chassis.turnTo(-65, 8, 1200, false, false);
    // claw.set_value(false);
    // wingL.set_value(true);
    chassis.moveTo(-68, 8, 270, 800);
    // wingL.set_value(false);
    chassis.moveTo(-35, 8, 270, 600, false, false);

    // Corner Triball Push
    chassis.turnTo(-50, 57, 700);
    chassis.moveTo(-50, 57, 315, 1200);
    turnTo(-135);
    wingF.set_value(true);
    chassis.moveTo(-62, 40, 180, 1000);
    wingF.set_value(false);
    

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