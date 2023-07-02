// pros::vision_signature_s_t TRIBALL = pros::Vision::signature_from_utility(2, -6223, -4453, -5338, -6399, -4153, -5276, 3.000, 0);

// vision_sensor.set_signature(1, &TRIBALL); 


//     while (true) {
//         vision_sensor.clear_led();
//         pros::vision_object_s_t rtn = vision_sensor.get_by_sig(0, 1);
//         int count = vision_sensor.get_object_count();
        
//         pros::lcd::set_text(1, "Count: " + std::to_string(count));
//         pros::lcd::set_text(3, std::to_string(rtn.signature));

//         pros::delay(20);
//     }
