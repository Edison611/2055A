#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/gps.h"
#include "pros/imu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/vision.hpp"
#include "lemlib/api.hpp"
#include <cstddef>

// ------------------------------------------------------------------------------------------------------
/**
 * Globals cpp file to store all the pros variables
 * This is where you change the ports, direction of motors, and encoder values
*/
// ------------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------------
// Define the port numbers here: 
// - Use numbers if it is in a port
// - Use letters if it is a triport
// ------------------------------------------------------------------------------------------------------
int MOTOR_LB = 18;
int MOTOR_LM = 19;
int MOTOR_LF = 20;

int MOTOR_RB = 16;
int MOTOR_RM = 12;
int MOTOR_RF = 11;

int MOTOR_INTAKE = 6;
int MOTOR_CATAPULT = 1;
int MOTOR_CATAPULT2 = 2;

int VISION_SENSOR_PORT = 23;
char CATA_LIMIT_SWITCH_PORT = 'H'; // RENAME TO BUMPER
int INERTIAL_SENSOR_PORT = 9;
int COLOR_SENSOR_PORT = 25;
// char INTAKE_LIMIT_SWITCH_PORT = 'E';
int DISTANCE_SENSOR_PORT = 10;

char CLIMB_PORT = 'C';
char WINGB_PORT = 'A';
char WINGF_PORT = 'D'; 

// pros::Rotation back_rot(6, false);
pros::Rotation kicker_rot(4, false);

// lemlib::TrackingWheel back_tracking_wheel(&back_rot, 2.75, -5.75);

// ------------------------------------------------------------------------------------------------------
// Drivetrain 
// ------------------------------------------------------------------------------------------------------
pros::Motor driveLB(MOTOR_LB, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLM(MOTOR_LM, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLF(MOTOR_LF, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor driveRB(MOTOR_RB, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveRM(MOTOR_RM, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveRF(MOTOR_RF, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);


pros::MotorGroup leftMotors({driveLB, driveLM, driveLF});
pros::MotorGroup rightMotors({driveRB, driveRM, driveRF});


// ------------------------------------------------------------------------------------------------------
// Subsystems
// ------------------------------------------------------------------------------------------------------
pros::Motor intake(MOTOR_INTAKE, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor catapult(MOTOR_CATAPULT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor catapult2(MOTOR_CATAPULT2, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

// ------------------------------------------------------------------------------------------------------
// Sensors
// ------------------------------------------------------------------------------------------------------
pros::Vision vision_sensor(VISION_SENSOR_PORT);
pros::ADIDigitalIn cata_limit_switch(CATA_LIMIT_SWITCH_PORT);
pros::IMU inertial_sensor(INERTIAL_SENSOR_PORT);
pros::Optical color_sensor(COLOR_SENSOR_PORT);
// pros::ADIDigitalIn intake_limit_switch(INTAKE_LIMIT_SWITCH_PORT);
// pros::ADIAnalogIn line_sensor(LINE_SENSOR_PORT);
pros::Distance distance_sensor(DISTANCE_SENSOR_PORT);

// ------------------------------------------------------------------------------------------------------
// Pneumatics
// ------------------------------------------------------------------------------------------------------
pros::ADIDigitalOut climb(CLIMB_PORT);
pros::ADIDigitalOut wingF(WINGF_PORT);
pros::ADIDigitalOut wingB(WINGB_PORT);
// ------------------------------------------------------------------------------------------------------
// CONTROLLER
// ------------------------------------------------------------------------------------------------------
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// ------------------------------------------------------------------------------------------------------
// LEMLIB (For position tracking)
// ------------------------------------------------------------------------------------------------------

/**
 * @brief Define the parameters of your drivetrain here:
 */
lemlib::Drivetrain drivetrain {
    &leftMotors, // left drivetrain motors
    &rightMotors, // right drivetrain motors
    10.50, // track width
    2.75, // wheel diameter
    480, // wheel rpm
    3 // Chase Power
};

// forward/backward PID
lemlib::ControllerSettings linearController {
    80, // kP
    0, // 0
    800, // kD May lower in the future
    0, // anti windup
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    20 // slew rate
};
 
// turning PID
lemlib::ControllerSettings angularController {
    4, // kP  
    0, // kI
    30, // kD 
    3, // anti windup
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
    
/**
 * @brief Define the sensors used for the robot here:
 */
lemlib::OdomSensors sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // horizontal tracking wheel 2
    &inertial_sensor // inertial sensor
};

lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors);
// ------------------------------------------------------------------------------------------------------