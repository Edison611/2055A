#include "pros/adi.hpp"
#include "pros/misc.hpp"
#include "pros/motors.hpp"
#include "pros/vision.hpp"


extern pros::Motor driveLB;
extern pros::Motor driveLM;
extern pros::Motor driveLF;

extern pros::Motor driveRB;
extern pros::Motor driveRM;
extern pros::Motor driveRF;

extern pros::Motor intake;
extern pros::Motor catapult;

extern pros::Vision vision_sensor;
extern pros::ADIDigitalIn limit_switch;

extern pros::Controller controller;