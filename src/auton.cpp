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
    chassis.setPose(-38.14602236652237, -60.18132683982684, 100.82);
    // chassis.follow(leftcurve4_txt, 20000, 25);
    chassis.follow(leftcurve5_txt, 20000, 25);
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

    // chassis.setPose(-61, 32, 0);

    // int shots = 44; // How many shots to take
    // int delay = 1200; // The delay between each shot

    // float time = ((shots * delay)/ 1000.0) - 1; // Formula for calculating time it takes to complete based of # of shots and delay
    // int shotNum = 1000 * (time+1) / delay; // Formula for finding # of shots based off time and delay

    // Start Code

    setDrive(-400, -400);
    pros::delay(500);
    setDrive(0, 0);

    setPTO(-600, -600, -600, -600);
    // for (int i = 0; i < shots; i++) {
    //     shoot();
    //     // pros::lcd::set_text(1, "time: " + std::to_string(i));
    //     // if (inertial_sensor.get_rotation() >= x) {
    //     //     setDrive(5, 15);
    //     // }
    //     // else if (inertial_sensor.get_rotation() <= x-2) {
    //     //     setDrive(15, 5);
    //     // }
    //     // else {
    //     //     setDrive(15, 10);
    //     // }

    //     pros::delay(delay);
    // }

    controller.rumble("-.");
}

void auton_skills() {
    chassis.setPose(-38, -53, 90);
    wingL.set_value(true);
    pros::delay(200);
    wingL.set_value(false);
    turnTo(130);
    chassis.moveTo(-55, -40, 130, 1320);
    turnTo(80);
    chassis.moveTo(-60, -40, 80, 800);  
    pros::delay(200);
    // wedge.set_value(true);
    // pros::delay(300);
    // wedge.set_value(false);

    // shoots x number of times
    // can choose length of gaps between shots
    matchLoad(10, 600);
    
    // PUSH TWO ALLIANCE TRIBALLS INTO OUR SIDE
    chassis.setPose(-47.75, -62.75, 54);
    setDrive(70, 70);
    pros::delay(200);
    setDrive(0, 0);
    chassis.turnTo(-62, -37, 800, false, true);

    chassis.moveTo(-62, -37, 180, 1500, false, false);
    turnTo(180);
    setDrive(-600, -600);
    pros::delay(800);
    setDrive(0, 0);
    setDrive(600, 600);
    pros::delay(200);
    setDrive(0, 0);
    chassis.turnTo(-34, -60, 800);
    chassis.moveTo(-34, -60, 90, 1500, false, true);
    turnTo(90);

    // START MOVING TO OTHER SIDE
    chassis.moveTo(22, -58, 90, 1600);
    chassis.moveTo(44, -51, 90, 1600);
    chassis.turnTo(-5, 22, 800);
    chassis.moveTo(10, -5, -25, 1600);
    
    // START RAMMING
    // First ram
    chassis.moveTo(30, 0, 90, 1500);
    ActivateWings(true);
    turnTo(90);
    setDrive(600, 600);
    pros::delay(1200);
    setDrive(0, 0);
    // chassis.setPose(35, 8, 90);
    ActivateWings(false);
    // chassis.moveTo(14, 22, 170, 2000, false, false);

    // Second ram
    chassis.moveTo(10, 38, 180, 3500, false, false);
    chassis.moveTo(13, 24, 120, 1000); // may remove
    // chassis.moveTo(13, 24, 120, 1000, false, false);
    ActivateWings(true);
    // setDrive(600, 600);
    chassis.moveTo(30, 17, 90, 1500);
    // chassis.moveTo(48, 14, -90, 2000);
    setDrive(600, 600);
    pros::delay(800);
    // setDrive(-300, -300);
    // pros::delay(800);

    // Third ram
    setDrive(-600, -600);
    // pros::delay(200);
    pros::delay(300);
    setDrive(0, 0);
    // chassis.moveTo(72, 14, -90, 1000);
    setDrive(600, 600);
    pros::delay(500);
    ActivateWings(false);

    // Move backwards so not touching any triballs
    setDrive(-600, -600);
    pros::delay(150);
    setDrive(0, 0);
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
    wingR.set_value(true);
    chassis.moveTo(-50, -57.5, 180, 1200); // may lower y value (more negative)
    turnTo(-170);
    turnTo(90);
    pros::delay(100);


    wingR.set_value(false);

    /* Moving Toward Pole */
    chassis.moveTo(-15, -60, 90, 3000); 
    pros::delay(500);
    setIntake(127);
    
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
    wingL.set_value(true);
    pros::delay(300);
    wingL.set_value(false);
    chassis.moveTo(36, 40, 180, 800);
    turnTo(195, 127, 650);
    chassis.moveTo(30, 15, 195, 800);
    //claw.set_value(true);
    setIntake(127);
    wingL.set_value(true);
    pros::delay(300);
    turnTo(-90, 60);
    pros::delay(100);
    setIntake(0);
    wingL.set_value(false);
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
    chassis.setPose(46, -55, 45);
    wingR.set_value(true);
    chassis.moveTo(62, -43, 45, 1500);
    wingR.set_value(false);
    chassis.moveTo(46, -55, 45, 1500, false, false);
    setIntake(-127);
    chassis.moveTo(62, -5, 0, 1500);
    chassis.moveTo(62, -45, 0, 1000, false, false);
    chassis.moveTo(62, -5, 0, 1000);
    chassis.moveTo(62, -40, -10, 1000, false, false);

    chassis.turnTo(0, -16, 1000);
    chassis.moveTo(15, -28, -60, 1500);
    pros::delay(500);
    setIntake(127);
    pros::delay(500);
    chassis.turnTo(48, 20, 1000, false, false, 50);
    chassis.moveTo(20, -20, 40, 800, false, true, 50);
    setIntake(-40);
    pros::delay(500);
    setIntake(127);
    chassis.turnTo(-5, 20, 1000);
    chassis.moveTo(9, -5, -35, 1000);
    // setIntake(127);
    pros::delay(500);
    chassis.turnTo(65, -7, 1000, false, false, 50);
    setIntake(-127);
    wingR.set_value(true); // Change to wingL
    chassis.moveTo(65, -7, 90, 1500);

    
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
    wingL.set_value(true);
    // claw.set_value(false);
    chassis.moveTo(-60, 8, 270, 1000);
    wingL.set_value(false);

    // Last tri-ball 
    chassis.moveTo(-16, 13, 270, 2000, false, false);
    chassis.turnTo(-4, 24, 800);    
    // claw.set_value(true);
    pros::delay(600);
    chassis.turnTo(-65, 8, 1200, false, false);
    // claw.set_value(false);
    wingL.set_value(true);
    chassis.moveTo(-68, 8, 270, 800);
    wingL.set_value(false);
    chassis.moveTo(-35, 8, 270, 600, false, false);

    // Corner Triball Push
    chassis.turnTo(-50, 57, 700);
    chassis.moveTo(-50, 57, 315, 1200);
    turnTo(-135);
    wingR.set_value(true);
    chassis.moveTo(-62, 40, 180, 1000);
    wingR.set_value(false);
    

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
    wingR.set_value(true);
    //chassis.moveTo(46, -55, 45, 1750, false, true);
    chassis.moveTo(56, -45, 45, 1750, false, true);
    wingR.set_value(false);
    // chassis.moveTo(50, -50, 45, 1000, false, false);
    chassis.moveTo(48, -55, 45, 1000, false, false);
    wingL.set_value(true);
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
    // wingR.set_value(true);
    // pros::delay(200);
    // chassis.moveTo(60, -45, 48, 1000, false, true);
    // pros::delay(100);
    // wingR.set_value(false);
    // pros::delay(200);
    // chassis.moveTo(35, -60, 60, 1000, false, false);
    // // chassis.moveTo(40, -55, -120, 800);
    // // chassis.moveTo(50, -50, -140, 809);
    // chassis.moveTo(57, -45, 30, 1750, false, true);
    // turnTo(0);
    // wingR.set_value(false);
    // pros::delay(200);
    // chassis.moveTo(57, -30, 0, 1000, false, true);
    
    /* Mirror Curve Entry + Re-Entry */
    // chassis.moveTo(57, -45, -180, 1000, false, true);
    // turnTo(30);    
    // chassis.moveTo(35, -60, 90, 1750, false, false);
    // wingR.set_value(true);
    // pros::delay(200);
    // chassis.moveTo(57, -45, 30, 1750, false, true);
    // turnTo(0);
    // wingR.set_value(false);
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
    // Pole & Alliance Tri-Ball
    chassis.setPose(9, -58, -90);
    setIntake(70); // Intake: Input

    // Corner Tri-Ball
    chassis.moveTo(40, -58, -90, 1750, false, false);
    turnTo(-130);
    wingR.set_value(true);
    chassis.moveTo(55, -48, -130, 1151, false, false);
    wingR.set_value(false);

    // First Net
    turnTo(-160);
    wingR.set_value(true);
    wingL.set_value(true);
    chassis.moveTo(59, -34, -180, 978, false, false);
    
    // Second Net
    wingR.set_value(false);
    wingL.set_value(false);
    chassis.moveTo(59, -38, -180, 800, false, true);
    turnTo(-90);
    turnTo(0);
    chassis.moveTo(59, -34, 0, 800);
    setIntake(-127);

    // Rush Middle
}