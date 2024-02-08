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
    // pros::Task log_task(log_data);
    shoot();

    // Begin
    setIntake(127);
    turnTo(-135, 127, 500);
    chassis.moveTo(-58.75, 36, -135, 700);
    turnTo(180, 127, 600);
    setIntake(-127);
    
    ram(400, 1);
    pros::delay(100);
    chassis.setPose(-60, 30, chassis.getPose().theta);
    pros::delay(100);

    // LINE UP TO SHOOT
    chassis.moveTo(-60, 49, 180, 1200, false, false);  
    turnTo(107, 127, 800);

    wingB.set_value(true);
    // wingF.set_value(true);
    // setBrake("brake");

    setIntake(0);
    // matchLoad(47, 530); // 550 MILLISECONDS FOR COMPETITIONS /|\ 45 Matchloads
    // setBrake("hold");
    // wingF.set_value(false);
    // wingB.set_value(false);
    // pros::delay(300);
}

void auton_skills() {
    // Calibration and Robot Setup
    chassis.setPose(-40, 55, -90);
    pros::Task log_task(log_data);
    shoot();

    // Begin
    setIntake(127);
    turnTo(-135, 127, 500);
    chassis.moveTo(-58.75, 36, -135, 700);
    turnTo(180, 127, 600);
    setIntake(-127);
    
    ram(500, 1);
    pros::delay(100);
    chassis.setPose(chassis.getPose().x, 30, chassis.getPose().theta);

    // LINE UP TO SHOOT
    chassis.moveTo(chassis.getPose().x, 49, 180, 1000, false, false);  
    turnTo(104, 127, 800); //105

    wingB.set_value(true);
    // wingF.set_value(true);
    setBrake("brake");

    // shoots x number of times
    // can choose length of gaps between shots
    setIntake(0);
    setCatapult(120);
    pros::delay(2000); // 24000
    setCatapult(0);
    // matchLoad(47, 500); // 550 MILLISECONDS FOR COMPETITIONS /|\ 45 Matchloads
    setBrake("hold");
    // wingF.set_value(false);
    wingB.set_value(false);
    pros::delay(300);

    vector(-40, 60, false, 127, 600, 1000);
    
    turnTo(90);
    // wingB.set_value(true);
    // pros::delay(300);
    wallReset("top");
    pros::delay(100);
    // wingB.set_value(false);


    // START MOVING TO OTHER SIDE
    chassis.moveTo(30, 60, 90, 1800);

    // SIDE RAM ON LEFT #1
    chassis.moveTo(62, 40, 135, 1200);
    turnTo(175, 127, 500);

    setIntake(-127);
    ram(600, 1);
    chassis.setPose(chassis.getPose().x, 32, chassis.getPose().theta);
    pros::delay(100);
    setIntake(-30);

    // BACK UP and MOVE TO MIDDLE
    chassis.moveTo(63, 48, 190, 1200, false, false);
    // turnTo(75, 127, 600);
    chassis.turnTo(12, 24, 700);
    chassis.moveTo(12, 24, -108, 1600);
    // chassis.moveTo(39, 43, 75, 1400, false, false);
    // wingB.set_value(true);
    // chassis.moveTo(18, 35, 0, 1200, false, false);

    // MIDDLE RAM #1 (LEFT SIDE)
    // wingB.set_value(true);
    // chassis.moveTo(25, 25, -40, 800, false, false);
    turnTo(-55, 80, 600); //70
    wingB.set_value(true);
    pros::delay(200);
    // ram(800, -1);
    chassis.moveTo(70, 10, -90, 1400, false, false); //Test
    chassis.moveTo(chassis.getPose().x-10, chassis.getPose().y, -90, 700);
    ram(450, -1); 
    chassis.setPose(39, chassis.getPose().y, chassis.getPose().theta);
    pros::delay(100);
    
    // MIDDLE RAM #2 (RIGHT SIDE)
    chassis.moveTo(20, 19, -90, 1000);
    // turnTo(-150, 127, 800);
    wingB.set_value(false);
    pros::delay(250);
    chassis.moveTo(18, 0, 180, 1000, false, true);
    chassis.moveTo(18, -24, 85, 1200);
    // wingF.set_value(true);
    turnTo(60, 127, 800);
    wingF.set_value(true);
    pros::delay(200);
    ram(850, 1);
    pros::delay(100);
    chassis.setPose(39, -19, chassis.getPose().theta);
    // pros::delay(100);

    // Middle Ram #3 (In the middle)
    chassis.moveTo(20, -14, 90, 1200, false, false);
    wingF.set_value(false);
    chassis.moveTo(10, 5, 90, 1000, false, false);
    turnTo(90, 127, 400);
    wingF.set_value(true);
    pros::delay(200);
    ram(750, 1);
    pros::delay(50);
    chassis.setPose(39, 0, chassis.getPose().theta);
    pros::delay(50);
    chassis.moveTo(25, 0, 90, 700, false, false);
    wingF.set_value(false);
    chassis.moveTo(20, -20, 20, 1400, false, false);
    
    chassis.turnTo(48, -48, 600);
    // wingF.set_value(true);
    chassis.moveTo(48, -48, 135, 1200);
    // wingF.set_value(false);
    // driveFwd(-10, 1000, 127);

    // RIGHT SIDE RAM #1 + 2
    turnTo(30);
    //ram(500, 1); idk
    setDrive(400, 600);
    pros::delay(600);
    setDrive(0, 0);
    // chassis.moveTo(chassis.getPose().x+2, chassis.getPose().y - 8.5, 0, 800, false, false);
    // ram(500, 1);
    chassis.moveTo(chassis.getPose().x+1, chassis.getPose().y - 8.5, 0, 800, false, false);
    turnTo(190);
    ram(500, -1);
    chassis.setPose(60, -30, chassis.getPose().theta);
    pros::delay(0);
    setIntake(0);
    
    // Back up
    // chassis.moveTo(60, -40, 0, 800);
    // turnTo(225, 127, 600);
    chassis.moveTo(34, -58, 225, 1500);
    // chassis.moveTo(40, -60, 225, 1500);
    turnTo(-90, 127, 600);
    wallReset("bottom");

    // chassis.moveTo(33, -62, 90, 1200, false, false);

    // CLIMB
    //turnTo(-90, 127, 1200);
    climb.set_value(true);
    setIntake(0);
    // chassis.moveTo(chassis.getPose().x-200, chassis.getPose().y, -90, 1500); //idk
    setDrive(500, 450);
    pros::delay(1500);
    setDrive(0, 0);
    // setDrive(600, 600);
    // pros::delay(1500);
    // driveFwd(70, 2000, 127);
    climb.set_value(false);
}

void defense_awp() {

    chassis.setPose(-48, -56, 134);
    setIntake(127);
    chassis.moveTo(-53, -51, 134, 1200, false, false);
    wingF.set_value(true);
    pros::delay(250);
    chassis.moveTo(-50, -54, 134, 1200);
    pros::delay(300);
    turnTo(100);
    pros::delay(250);
    wingF.set_value(false);
    pros::delay(250);
    chassis.moveTo(-13.5, -58, 90, 2100);
    setIntake(-127);
    pros::delay(500);
    setIntake(0);
    
    // /* Shoot Pre-Load Triball */
    // chassis.setPose(-41.25, -54.25, 90);
    // shoot();
    // pros::delay(500);
    // wingF.set_value(true);
    // pros::delay(500);
    // wingF.set_value(false);
    // turnTo(63);
    // matchLoad(1, 500);

    // /* Take Triball Out of Corner */
    // chassis.moveTo(-55, -49, 138, 3500, false, false);
    // wingF.set_value(true);
    // pros::delay(500);
    // chassis.moveTo(-52, -52, 135, 2000);
    // turnTo(100);
    // wingF.set_value(false);

    // /* Move to Elevation Bar */
    // setIntake(-127); // to shoot triballs it touches to the other side of the field
    // chassis.moveTo(-12, -58, 90, 3000);
    // pros::delay(500);
    // setIntake(0);
    
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
    pros::delay(300);
    chassis.moveTo(-52, -52, 135, 2000);
    turnTo(100);
    wingF.set_value(false);
    pros::delay(200);

    turnTo(45);
    chassis.moveTo(-39, -14, 0, 2200);
    turnTo(-90);
    wingB.set_value(true);
    pros::delay(300);
    chassis.moveTo(0, -14, -90, 2000, false, false);
    wingB.set_value(false);     
    //chassis.moveTo(-11.5, -8, -90, 1000);
    turnTo(-180);
    //chassis.moveTo(-11.5, -50, -180, 2000);
    /* NORMAL */ chassis.moveTo(6, -60, -180, 2000, false, true, 0, 0.6, 70);
    // wingF.set_value(true);
    // /* TEST */ chassis.moveTo(9, -60, -180, 2000, false, true, 0, 0.6, 70); // this works
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
    setIntake(127);
    chassis.moveTo(53.75, -52.5, 45, 1200);
    turnTo(-12, 127, 500);
    wingF.set_value(false);
    setIntake(-127);
    chassis.moveTo(56, 0, 0, 900);
    chassis.moveTo(57, -50, 0, 900, false, false);
    chassis.moveTo(62, 10, 0, 900);
    pros::delay(200);
    chassis.setPose(chassis.getPose().x, -30, chassis.getPose().theta);
    pros::delay(200);
    setIntake(0);
    chassis.moveTo(60, -55, -10, 800, false, false);
    

    // Middle Tri-Balls
    chassis.turnTo(-5, -23, 800);
    setIntake(127);
    chassis.moveTo(10, -29, -67, 1200);
    pros::delay(250);
    turnTo(35, 100);
    chassis.moveTo(15, -7, 35, 800);
    wingF.set_value(true);
    turnTo(90);
    pros::delay(100);
    chassis.moveTo(60, -7, 90, 1200);
    chassis.setPose(40, chassis.getPose().y, chassis.getPose().theta);
    pros::delay(150);
    chassis.moveTo(20, -7, 90, 1000, false, false);
    wingF.set_value(false);

    // Last
    setIntake(127);
    chassis.turnTo(4, 0, 800);
    chassis.moveTo(4, 0, -70, 1000);
    // turnTo(-90);
    // chassis.moveTo(-15, -3, -70, 1000);
    pros::delay(300);
    // chassis.moveTo(8, -5, -25, 800);
    turnTo(90);
    setIntake(-30);
    wingF.set_value(true);
    chassis.moveTo(60, -6, 90, 1200);
    setIntake(0);
    chassis.moveTo(25, -8, 90, 900, false, false);
    wingF.set_value(false);
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
    chassis.moveTo(-28, 8, 164, 1200, true); // async true
    chassis.waitUntilDist(5); // waits until bot has travelled 5 inches
    wingF.set_value(false); // close front wings
    pros::delay(1200);
    chassis.moveTo(-30, 60, 265, 2000, false, false); // move behind the bar, to the right of short barrier, facing bar
   
    //chassis.moveTo(-54, 52, 230, 1750, true); // move to get corner triball out
    chassis.moveTo(-60, 40, 190, 1400, true);
    chassis.waitUntilDist(5); // waits until bot has travelled 5 inches
    wingF.set_value(true); // open the wing to get corner triball out
    pros::delay(1400);
    setIntake(-20);

    wingF.set_value(false); // close wing
    chassis.moveTo(-55, 55, 210, 1200, false, false); // back up
    chassis.moveTo(-72, -00, 180, 1000);
    chassis.moveTo(chassis.getPose().x, chassis.getPose().y + 7.5, chassis.getPose().theta, 850, false, false);
    ram(500, 1);
    pros::delay(100);
    chassis.setPose(chassis.getPose().x, 30, chassis.getPose().theta);
    pros::delay(100);
    // Go for middle triballs
    chassis.moveTo(-52, 52, 220, 1000, false, false);
    turnTo(123, 127, 600);
    setIntake(127);
    chassis.moveTo(-11, 26, 120, 1500);
    pros::delay(500);
    turnTo(240, 80, 600);
    setIntake(0);
    wingF.set_value(true);
    chassis.moveTo(-70, 10, 270, 1200);
    pros::delay(200);
    chassis.setPose(-40, chassis.getPose().y, chassis.getPose().theta);
    pros::delay(100);

    // Final Triball
    chassis.moveTo(-15, 10, 270, 1200, false, false);
    wingF.set_value(false);
    // setIntake(127);
    // chassis.moveTo(-2, 0, 110, 900);
    // turnTo(-90, 127, 600);
    // wingF.set_value(true);
    // chassis.moveTo(-70, 5, -90, 800);
    // setIntake(0);

    // Back up
    chassis.moveTo(-20, 5, -90, 800, false, false);
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