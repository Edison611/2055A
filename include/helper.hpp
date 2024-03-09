#include <string>
#include <iostream>

std::string currentDateTime();

void skills_matchload();

// Testing Functions
void allowContinue();

// Functions for Bot
void turnToNet(bool reversed, bool red, int delay);
void driverAssist();

void liftRam(int timeout = 1000);
void secondRam(int backUpInches, int forwardMillis, int backUpTimeout = 1000, bool side = false);

void vector(double x, double y, bool forwards=true, int maxSpeed=127, int turnTimout = 700, int driveTimeout = 2000);
void driveFwd(double inches, int timeout, float maxSpeed);
void turnTo(double degrees, int maxSpeed = 127, int timeout = 800, bool forwards = true, bool async = false);
void turnToDir(int targetAngle, bool right, int maxSpeed = 127, int timeout = 1500);

void setBrake(std::string mode);
void wallReset(std::string wall, std::string sensor);

void matchLoad(int shots, int delay);
