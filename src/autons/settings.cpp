#include "main.h"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/RQuantity.hpp"

// const int DRIVE_SPEED = 110;  
// const int TURN_SPEED = 90;
// const int SWING_SPEED = 90;

void default_constants() {
  ezChassis.pid_heading_constants_set(3, 0, 20);
  ezChassis.pid_drive_constants_set(5, 0, 40);
  ezChassis.pid_turn_constants_set(3, 0, 20);
  ezChassis.pid_swing_constants_set(5, 0, 30);

  ezChassis.pid_turn_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  ezChassis.pid_swing_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  ezChassis.pid_drive_exit_condition_set(300_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);


  ezChassis.slew_drive_constants_set(7_in, 80);
}
