#include <cmath>
#include <string>
#include <iostream>

std::string currentDateTime();

void skills_matchload();

// Testing Functions
void allowContinue();

// Functions for Bot
void turnToNet(bool reversed, bool red, int delay);
void driverAssist();

void vector(double x, double y, bool reversed=false, float maxSpeed=127, int turnTimout = 700, int driveTimeout = 2000);
void driveFwd(double inches, int timeout, float maxSpeed);
void turnTo(double degrees, int maxSpeed = 127, int timeout = 800, bool reversed = false, bool async = false);
void turnToDir(int targetAngle, bool right, int maxSpeed = 127, int timeout = 1500);

void setBrake(std::string mode);
void wallReset();

void matchLoad(int shots, int delay);
