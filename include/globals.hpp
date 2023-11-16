#include "lemlib/chassis/chassis.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/imu.hpp"
#include "pros/misc.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/vision.hpp"

/**
 * Globals header file to store all the pros variables
 */

extern pros::Motor driveLB;
extern pros::Motor driveLF;
extern pros::Motor ptoL1;
extern pros::Motor ptoL2;

extern pros::Motor driveRB;
extern pros::Motor driveRF;
extern pros::Motor ptoR1;
extern pros::Motor ptoR2;

extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

extern pros::Motor intake1;
extern pros::Motor intake2;
extern pros::Motor catapult;

extern pros::Vision vision_sensor;
extern pros::ADIDigitalIn cata_limit_switch;
extern pros::IMU inertial_sensor;
extern pros::Optical color_sensor;
// extern pros::ADIDigitalIn intake_limit_switch;
extern pros::ADIAnalogIn line_sensor;
extern pros::Distance distance_sensor;


extern pros::ADIDigitalOut blocker;
extern pros::ADIDigitalOut wingR;
extern pros::ADIDigitalOut wingL;
extern pros::ADIDigitalOut grabber;
extern pros::ADIDigitalOut drivePTO;
extern pros::ADIDigitalOut claw;
extern pros::ADIDigitalOut wedge;

extern pros::Controller controller;

extern lemlib::ChassisController_t lateralController;
extern lemlib::Chassis chassis;

extern pros::Rotation puncher_rot;