#include <string>
#include <iostream>

std::string currentDateTime();

void skills_matchload();

// Testing Functions
void allowContinue();

// Functions for Bot
void turnToNet(bool reversed, bool red, int delay);

void vector(double x, double y, bool reversed=false, int maxSpeed=127, int turnTimout = 700, int driveTimeout = 2000);
void driveFwd(double inches, int timeout, float maxSpeed);
void turnTo(double degrees, int maxSpeed = 127, int timeout = 700, bool reversed = false, bool async = false);
void turnToDir(int targetAngle, bool right);

void setBrake(std::string mode);

void matchLoad(int shots, int delay);
