#include "main.h"
#include "pros/llemu.hpp"
#include "pros/vision.h"
#include <string>

// GLOBAL VARIABLES

int netPos[2] = {100, 100};


void GoToOrigin() {
    chassis.moveTo(0, 0, 2000);
}

void driveToNet(int pos[]) {
    chassis.turnTo(pos[0], pos[1], 1000);
}

bool GoToTriball(pros::vision_object_s_t triball) {
    int center = 158;
    bool pause = false;
    double x = triball.x_middle_coord;
    double width = triball.width;

    if ((x > (center - 5)) || (x < (center + 5))) {
        setDrive(50, 50);
        if (width > 200) {
            setDrive(0, 0);
            pause = true;
            return true;
        }
    }

    else if (x < center || pause == true) {
        setDrive(50, -50);
    }

    else if (x > center || pause == true) {
        setDrive(-50, 50);
    }

    return false;

}

void skills() {
    // Defining Triball Signatures
    pros::vision_signature_s_t TRIBALL_SIG = pros::Vision::signature_from_utility(2, -6223, -4453, -5338, -6399, -4153, -5276, 3.000, 0);
    vision_sensor.set_signature(1, &TRIBALL_SIG); 


    int center = 158;
    chassis.calibrate();

    while (true) {
        vision_sensor.clear_led();
        pros::vision_object_s_t rtn = vision_sensor.get_by_sig(0, 1);   

        // Vision sensor values
        int count = vision_sensor.get_object_count();
        int x = rtn.x_middle_coord;
        int y = rtn.y_middle_coord;
        // double angle = rtn.angle;
        
        pros::lcd::set_text(1, "Count: " + std::to_string(count));
        pros::lcd::set_text(2, "Triball X, Y: " + std::to_string(x) + ", " + std::to_string(y));
        // pros::lcd::set_text(3, "Triball angle: " + std::to_string(angle));
        pros::lcd::set_text(4, "Triball width: " + std::to_string(rtn.width));

        if (count >= 1) {
            bool grabbed = GoToTriball(rtn);
            if (grabbed == true) {

            }
        }

        

        pros::delay(20);
    }

}

void solo_auton() {
}
