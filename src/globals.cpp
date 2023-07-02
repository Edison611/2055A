#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/vision.hpp"
#include "lemlib/api.hpp"
#include <cstddef>


// Define the port numbers here: 

int MOTOR_LB = 3;
int MOTOR_LM = 20;
int MOTOR_LF = 6;

int MOTOR_RB = 2;
int MOTOR_RM = 4;
int MOTOR_RF = 9;

int MOTOR_INTAKE = 5;
int MOTOR_CATAPULT = 10;

int VISION_SENSOR_PORT = 1;
char LIMIT_SWITCH_PORT = 'A';


// Drivetrain 
pros::Motor driveLB(MOTOR_LB, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLM(MOTOR_LM, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLF(MOTOR_LF, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor driveRB(MOTOR_RB, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveRM(MOTOR_RM, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRF(MOTOR_RF, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::MotorGroup leftMotors({driveLB, driveLM, driveLF});
pros::MotorGroup rightMotors({driveRB, driveRM, driveRF});

lemlib::Drivetrain_t drivetrain {
    &leftMotors, // left drivetrain motors
    &rightMotors, // right drivetrain motors
    12, // track width
    3.25, // wheel diameter
    400 // wheel rpm
};


// forward/backward PID
lemlib::ChassisController_t lateralController {
    30, // kP
    125, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    3 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    2, // kP
    20, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    3 // slew rate
};


lemlib::OdomSensors_t sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    nullptr // inertial sensor
};

lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);



// Subsystems
pros::Motor intake(MOTOR_INTAKE, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor catapult(MOTOR_CATAPULT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);

// Sensors
pros::Vision vision_sensor(VISION_SENSOR_PORT);
pros::ADIDigitalIn limit_switch(LIMIT_SWITCH_PORT);

pros::Controller controller(pros::E_CONTROLLER_MASTER);