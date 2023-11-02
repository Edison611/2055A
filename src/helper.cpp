#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <cmath>

const std::string currentDateTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d-%X", &tstruct);

    return buf;
}


/**
 * @brief Theoretically uses vision sensor to turn to where there is a triball and drive there (NOT TESTED)
 * 
 */
void triballVision() {
    // Defining Triball Signatures
    // pros::vision_signature_s_t TRIBALL_SIG = pros::Vision::signature_from_utility(2, -6223, -4453, -5338, -6399, -4153, -5276, 3.000, 0);
    // vision_sensor.set_signature(1, &TRIBALL_SIG); 


    // int center = 158;
    // chassis.calibrate();

    // while (true) {
    //     vision_sensor.clear_led();
    //     pros::vision_object_s_t rtn = vision_sensor.get_by_sig(0, 1);   

    //     // Vision sensor values
    //     int count = vision_sensor.get_object_count();
    //     int x = rtn.x_middle_coord;
    //     int y = rtn.y_middle_coord;
    //     // double angle = rtn.angle;
        
    //     pros::lcd::set_text(1, "Count: " + std::to_string(count));
    //     pros::lcd::set_text(2, "Triball X, Y: " + std::to_string(x) + ", " + std::to_string(y));
    //     // pros::lcd::set_text(3, "Triball angle: " + std::to_string(angle));
    //     pros::lcd::set_text(4, "Triball width: " + std::to_string(rtn.width));

    //     if (count >= 1) {
    //         bool grabbed = GoToTriball(rtn);
    //         if (grabbed == true) {

    //         }
    //     }

        

    //     pros::delay(20);
    // }
}