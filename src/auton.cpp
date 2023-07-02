#include "main.h"
#include "pros/llemu.hpp"
#include <string>


void skills() {
    pros::vision_signature_s_t TRIBALL = pros::Vision::signature_from_utility(2, -6223, -4453, -5338, -6399, -4153, -5276, 3.000, 0);

    vision_sensor.set_signature(1, &TRIBALL); 

    while (true) {
        vision_sensor.clear_led();
        pros::vision_object_s_t rtn = vision_sensor.get_by_sig(0, 1);
        int count = vision_sensor.get_object_count();
        int x = rtn.x_middle_coord;
        int y = rtn.y_middle_coord;
        int center = 158;
        
        pros::lcd::set_text(1, "Count: " + std::to_string(count));
        pros::lcd::set_text(2, "X: " + std::to_string(x));
        pros::lcd::set_text(3, "Y: " + std::to_string(y));

        if (x > center) {
            setDrive(-50, 50);
        }

        else if (x < center) {
            setDrive(50, -50);
        }

        else if (x == center) {
            setDrive(50, 50);
        }


        // pros::lcd::set_text(3, std::to_string(rtn.signature));

        pros::delay(20);
    }

}