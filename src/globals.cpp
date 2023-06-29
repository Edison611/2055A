#include "main.h"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/vision.hpp"


// Define the port numbers here: 

int MOTOR_LB = 3;
int MOTOR_LM = 4;
int MOTOR_LF = 10;

int MOTOR_RB = 11;
int MOTOR_RM = 9;
int MOTOR_RF = 19;

int MOTOR_INTAKE = 20;

int VISION_SENSOR_PORT = 1;


// Drivetrain 
pros::Motor driveLB(MOTOR_LB, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLM(MOTOR_LM, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLF(MOTOR_LF, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor driveRB(MOTOR_RB, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveRM(MOTOR_RM, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRF(MOTOR_RF, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

// Subsystems
pros::Motor intake(MOTOR_INTAKE, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

// Sensors
pros::Vision vision_sensor(VISION_SENSOR_PORT);

pros::Controller controller(pros::E_CONTROLLER_MASTER);