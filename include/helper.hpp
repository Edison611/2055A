#include <string>
#include <iostream>

std::string currentDateTime();

// Testing Functions
void allowContinue();

// Functions for Bot
void turnToNet(bool reversed, bool red, int delay);

void vector(double x, double y, int turnTimeout, int driveTimeout);
void driveFwd(double inches, int timeout, float maxSpeed);
void turnTo(double degrees, int maxSpeed = 127, int timeout = 600, bool reversed = false, bool async = false);

void setBrake(std::string mode);

void matchLoad(int shots, int delay);
