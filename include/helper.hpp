#include <string>
std::string currentDateTime();

void vector(double x, double y, int turnTimeout, int driveTimeout);
void driveFwd(double inches, int timeout, float maxSpeed);
void turnTo(double degrees, int timeout);
