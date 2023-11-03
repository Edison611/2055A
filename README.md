# Installation
- For team members, clone the repository locally and pull the main branch
- An alternative is to go to [Releases](https://github.com/Edison611/2055A/releases) and install the most up to date version

# Judging
Below are some of the features that can be mentioned for programming when judging:

## Vision Sensor:
- By giving the sensor an image of a triball, it is able to detect any triballs in its view and tells us information such as the size with the x and y positions.
- We can then tell our robot to drive to the triball and pick it up for skills matches

## Color Sensor:
- Used to detect triballs using its RGB values; however it does not give its coordinates, just a true/false if it is detected
- Detects a triball coming into the intake and can be used to hold a triball in place before outtaking

## Distance Sensor:
- Detects if a triball is placed in the match load position, so that it can shoot automatically for matchloads after a triball is placed. This makes it easier for the driver as they don't have to keep clicking a button over and over, and it would be faster for the person placing the triball on the bot as there is less human error involved.

## Solo Autonomous Win Point:
- Our robot is designed to be able to get the autonomous win point by itself by shooting the alliance triball across the field, picking up the triball in the corner, and also touching the pole

## Autonomous Coding Process:
- The first step is to find a possible route that is able to perform the tasks required in autonomous
- Odometry is used to keep track of the position of the robot, so that even if it our robot gets knocked off course in one place, it will be able to correct itself for the later tasks. (It is able to drive to a position on the field or turn to any position through a coordinate system) 
- Instead of blindly testing where to make our robot drive to, we have a coordinate system where the center of the field is (0,0).
- We created a [website](https://capybaras-2055.vercel.app/) where we can enter the dimensions of our robot, an (x, y) coordinate and it will draw the robot on the field, so that we can test if our coordinates are reasonable before we testing it physically. This feature can be found here: https://edison611.github.io/robot-tracker/#/tracker
- After checking all of the coordinates to drive to, we can implement it physically and add all other tasks to do in between each movement such as intaking and shooting.
