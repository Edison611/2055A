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
#include "EZ-Template/api.hpp"
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
int MOTOR_LB = 7;
int MOTOR_LM = 20;
int MOTOR_LF = 19;
int MOTOR_LH = 6;

int MOTOR_RB = 4;
int MOTOR_RM = 11;
int MOTOR_RF = 12;
int MOTOR_RH = 5;

int MOTOR_INTAKE = 13;
// int MOTOR_INTAKE2 = 16;
int MOTOR_CATAPULT = 1;
int MOTOR_CATAPULT2 = 2;

int VISION_SENSOR_PORT = 23;
char CATA_LIMIT_SWITCH_PORT = 'H'; // RENAME TO BUMPER
int INERTIAL_SENSOR_PORT = 15;
int COLOR_SENSOR_PORT = 25;
// char INTAKE_LIMIT_SWITCH_PORT = 'E';
int DISTANCE_SENSOR_PORT = 10;

char CLIMB_PORT = 'C';
char WINGB_PORT = 'A';
char WINGF_PORT = 'D'; 
// char GRABBER_PORT = 'D';
// char DRIVEPTO_PORT = 'B';
// char CLAW_PORT = 'C';
char WEDGE_PORT = 'F'; // NOT IN USE
char PISTON_BOOST_PORT = 'B';

// pros::Rotation back_rot(6, false);
pros::Rotation kicker_rot(14, false);

// lemlib::TrackingWheel back_tracking_wheel(&back_rot, 2.75, -5.75);

// ------------------------------------------------------------------------------------------------------
// Drivetrain 
// ------------------------------------------------------------------------------------------------------
pros::Motor driveLB(MOTOR_LB, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLM(MOTOR_LM, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLF(MOTOR_LF, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLH(MOTOR_LH, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor driveRB(MOTOR_RB, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveRM(MOTOR_RM, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveRF(MOTOR_RF, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveRH(MOTOR_RH, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);


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
pros::Distance distance_sensor(DISTANCE_SENSOR_PORT);

// ------------------------------------------------------------------------------------------------------
// Pneumatics
// ------------------------------------------------------------------------------------------------------
pros::ADIDigitalOut climb(CLIMB_PORT);
pros::ADIDigitalOut wingF(WINGF_PORT);
pros::ADIDigitalOut wingB(WINGB_PORT);
// pros::ADIDigitalOut grabber(GRABBER_PORT);
// pros::ADIDigitalOut drivePTO(DRIVEPTO_PORT);
// pros::ADIDigitalOut claw(CLAW_PORT);
pros::ADIDigitalOut wedge(WEDGE_PORT);
pros::ADIDigitalOut pistonBoost(PISTON_BOOST_PORT);

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
lemlib::Drivetrain_t drivetrain {
    &leftMotors, // left drivetrain motors
    &rightMotors, // right drivetrain motors
    10.50, // track width
    2.75, // wheel diameter
    480, // wheel rpm
    5 // Chase Power
};

// forward/backward PID
lemlib::ChassisController_t lateralController {
    80, // kP
    800, // kD May lower in the future
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    3 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    4, // kP  
    30, // kD 
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    3 // slew rate
};
    
/**
 * @brief Define the sensors used for the robot here:
 */
lemlib::OdomSensors_t sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // horizontal tracking wheel 2
    &inertial_sensor // inertial sensor
};


ez::Drive ezChassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  {-18, -19, -20}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  ,{16, 12, 11}

  // IMU Port
  ,9

  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
  ,2.03

  // Cartridge RPM
  ,450

  // External Gear Ratio (MUST BE DECIMAL) This is WHEEL GEAR / MOTOR GEAR
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 84/36 which is 2.333
  // eg. if your drive is 60:36 where the 36t is powered, your RATIO would be 60/36 which is 0.6
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 36/60 which is 0.6
  ,0.75
);


lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);
// ------------------------------------------------------------------------------------------------------