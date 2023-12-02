#include <string>
#include <iostream>

std::string currentDateTime();

// Testing Functions
void allowContinue();

// Functions for Bot
void turnToNet(bool reversed, bool red, int delay);


void vector(double x, double y, int turnTimeout, int driveTimeout);
void driveFwd(double inches, int timeout, float maxSpeed);
void turnTo(double degrees, int timeout=800);
