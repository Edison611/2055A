#include "lemlib/pose.hpp"
#include "main.h"  // Include the PROS header file
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include <string>
#include <vector>

// Constants for the robot and pure pursuit
const double MAX_SPEED = 50;  // Maximum motor power
const double WHEELBASE_WIDTH = 12.0;  // Distance between the left and right wheels

// Function to calculate distance between two points
double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Function to calculate the target point for pure pursuit
void calculateTargetPoint(double robotX, double robotY, double robotHeading,
                          double *targetX, double *targetY,
                          const std::vector<std::pair<double, double>> &path,
                          int currentIndex) {
    // Find the closest point on the path
    int closestIndex = currentIndex;
    double closestDistance = distance(robotX, robotY, path[currentIndex].first, path[currentIndex].second);
    for (int i = currentIndex + 1; i < path.size(); ++i) {
        double dist = distance(robotX, robotY, path[i].first, path[i].second);
        if (dist < closestDistance) {
            closestDistance = dist;
            closestIndex = i;
        }
    }

    // Calculate the lookahead distance based on robot speed
    double lookaheadDistance = 10.0 + 0.1 * MAX_SPEED;

    // Find the target point by projecting a line from the robot's position
    // in the direction of the robot's heading
    double dx = path[closestIndex].first - robotX;
    double dy = path[closestIndex].second - robotY;
    double projection = (dx * cos(robotHeading) + dy * sin(robotHeading));
    if (projection > lookaheadDistance) {
        projection = lookaheadDistance;
    }
    *targetX = robotX + projection * cos(robotHeading);
    *targetY = robotY + projection * sin(robotHeading);
}

// Main autonomous function
void chatgpt() {
    // List of waypoints for the robot to follow (x, y coordinates)
    std::vector<std::pair<double, double>> path = {
        {12.0, 12.0},
        {24.0, 0.0},
        {36.0, 20.0}
    };

    // Robot's initial position and heading
    double robotX = 0.0;
    double robotY = 0.0;
    double robotHeading = 0.0;

    // Index of the current waypoint
    int currentIndex = 0;

    // Loop for pure pursuit
    while (currentIndex < path.size()) {
        double targetX, targetY;
        lemlib::Pose pose = chassis.getPose();
        double robotX = pose.x;
        double robotY = pose.y;
        double robotHeading = pose.theta;
        calculateTargetPoint(robotX, robotY, robotHeading, &targetX, &targetY, path, currentIndex);

        // Calculate the curvature for steering
        double dx = targetX - robotX;
        double dy = targetY - robotY;
        double curvature = (2 * dy) / (dx * dx);

        // Calculate the left and right motor powers based on curvature
        double leftPower = MAX_SPEED * (1 - WHEELBASE_WIDTH * curvature / 2);
        double rightPower = MAX_SPEED * (1 + WHEELBASE_WIDTH * curvature / 2);

        if (leftPower > MAX_SPEED) {
            leftPower = MAX_SPEED;
        }
        if (rightPower > MAX_SPEED) {
            rightPower = MAX_SPEED;
        }

        pros::lcd::set_text(1, "left: " + std::to_string(leftPower));
        pros::lcd::set_text(2, "right: " + std::to_string(rightPower));

        // Set the motor powers using the setDrive function
        setDrive(leftPower, rightPower);

        // Update robot's position and heading (replace with your own odometry code)
        robotX += 0.1 * cos(robotHeading);
        robotY += 0.1 * sin(robotHeading);
        robotHeading += curvature * 0.1;  // Assuming constant curvature for simplicity

        // Check if the robot is close enough to the current waypoint to move to the next
        if (distance(robotX, robotY, path[currentIndex].first, path[currentIndex].second) < 0.5) {
            setDrive(0, 0);
            currentIndex++;
            pros::delay(2000);
        }

        pros::delay(20);  // Delay for simulation purposes
    }
}
