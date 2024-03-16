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
int MOTOR_LB = 9;
int MOTOR_LM = 8;
int MOTOR_LF = 20;
int MOTOR_LH = 10;

int MOTOR_RB = 2;
int MOTOR_RM = 3;
int MOTOR_RF = 11;
int MOTOR_RH = 1;

int MOTOR_INTAKE = 16;
// int MOTOR_INTAKE2 = 16;
int MOTOR_CATAPULT = 1;
int MOTOR_CATAPULT2 = 2;

int VISION_SENSOR_PORT = 23;
char CATA_LIMIT_SWITCH_PORT = 'I'; // RENAME TO BUMPER
int INERTIAL_SENSOR_PORT = 15;
int COLOR_SENSOR_PORT = 25;
// char INTAKE_LIMIT_SWITCH_PORT = 'E';
int DISTANCE_SENSOR_PORT_LEFT = 10;
int DISTANCE_SENSOR_PORT_RIGHT = 14;

char INTAKE_PORT = 'G';
char CLIMB_PORT = 'F';
char WINGFR_PORT = 'F';
char WINGFL_PORT = 'A'; 
char ENDGAME_PORT = 'E';
// char GRABBER_PORT = 'D';
char DRIVEPTO_PORT = 'H';
// char CLAW_PORT = 'C';
char WEDGE_PORT = 'A'; // NOT IN USE
char PISTON_BOOST_PORT = 'B';

// pros::Rotation back_rot(6, false);
pros::Rotation kicker_rot(13, false);

// lemlib::TrackingWheel back_tracking_wheel(&back_rot, 2.75, -5.75);

// ------------------------------------------------------------------------------------------------------
// Drivetrain 
// ------------------------------------------------------------------------------------------------------
pros::Motor driveLB(MOTOR_LB, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLM(MOTOR_LM, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLF(MOTOR_LF, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLH(MOTOR_LH, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor driveRB(MOTOR_RB, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveRM(MOTOR_RM, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveRF(MOTOR_RF, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveRH(MOTOR_RH, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);


pros::MotorGroup leftMotors({driveLB, driveLM, driveLF, driveLH});
pros::MotorGroup rightMotors({driveRB, driveRM, driveRF, driveRH});

// pros::MotorGroup lPTOMotors({ptoL1, ptoL2});
// pros::MotorGroup rPTOMotors({ptoR1, ptoR2});


// ------------------------------------------------------------------------------------------------------
// Subsystems
// ------------------------------------------------------------------------------------------------------
pros::Motor intake(MOTOR_INTAKE, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
//pros::Motor intake2(MOTOR_INTAKE2, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
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
pros::Distance distance_sensorL(DISTANCE_SENSOR_PORT_LEFT);
pros::Distance distance_sensorR(DISTANCE_SENSOR_PORT_RIGHT);

// ------------------------------------------------------------------------------------------------------
// Pneumatics
// ------------------------------------------------------------------------------------------------------
pros::ADIDigitalOut intake_up(INTAKE_PORT);
pros::ADIDigitalOut climb(CLIMB_PORT);
pros::ADIDigitalOut wingFR(WINGFR_PORT);
pros::ADIDigitalOut wingFL(WINGFL_PORT);
pros::ADIDigitalOut endgame(ENDGAME_PORT);
pros::ADIDigitalOut drivePTO(DRIVEPTO_PORT);

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
    3.25, // wheel diameter
    450, // wheel rpm
    2 // Chase Power
};

// forward/backward PID
lemlib::ControllerSettings linearController {
    110, // kP    //80
    0, // KI
    700, // kD May lower in the future      //800
    0, // anti windup
    1, // smallErrorRange
    300, // smallErrorTimeout
    3, // largeErrorRange
    600, // largeErrorTimeout
    5 // slew rate     //3
};
 
// turning PID
lemlib::ControllerSettings angularController {
    2.1,
    0, // kI
    12,
    3, // anti windup
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    3 // slew rate
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