# Installation
- For team members, clone the repository locally and pull the main branch
- An alternative is to go to [Releases](Releases) and install the most up to date version

# Judging
Below are some of the features that can be mentioned for programming when judging:

## Vision Sensor:
- By giving the sensor an image of a triball, it is able to detect any triballs in its view and tells us information such as the size with the x and y positions.
- We can then tell our robot to drive to the triball and pick it up for skills matches

## Color Sensor:
- Used to detect triballs using its RGB values; however it does not give its coordinates, just a true/false if it is detected
- Detects a triball coming into the intake and can be used to hold a triball in place before outtaking
- Detects if a triball is placed in the catapult basket, so that it can shoot automatically for matchloads after a triball is placed. This makes it easier for the driver as they don't have to keep clicking a button over and over, and it would be faster as there is less human error involved

## Solo Autonomous Win Point:
- Our robot is designed to be able to get the autonomous win point by itself by shooting the alliance triball across the field, picking up the triball in the corner, and also touching the pole
