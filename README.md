# INSTALLATION
- For team members, clone the repository locally and pull the main branch
- An alternative is to go to [Releases](https://github.com/Edison611/2055A/releases) and install the most up to date version

# JUDGING
Below are some of the features that can be mentioned for programming when judging:

## Inertial Sensor:
- Used to track the angle of the robot which helps with position tracking. (Big part of Odometry)

## Motor Encoders:
- Used to track distance that wheels travel to calculate the x, y position on the field. Used alongside inertial sensor for accurate measurements.

## Rotational Sensor:
- Used for the puncher to track the angle at which the puncher is at. Once it reaches a set angle from the start, we notify the motors to stop spinning to hold its position there.

## PID:
- **P**: **Proportional** term used to calculate error between actual and desired value. The farther away from the target, the more power you give to the motor.
- **I**: **Integral** term (currently not in use). Accumulated error (sum of error), so it keeps increasing. This will often cause the robot to overshoot which is why a hard cap on the value is required. 
- **D**: **Derivative** term (Δerror) used to find the change in your error which predicts future trends on the change in power given to the motor.
- **Tuning** these value uses **Manual Trial & Error** and requires:
    1. Increasing the kP term until the robot begins overshooting and slightly oscillating.
    2. Increase the kD value until it stops oscillating
    3. Keep repeating those steps until the robot can no longer stop oscillating and use those kP and kD values

## Version Control System / Managing the Code:
- We use Github to manage all of our code with different branches to organize different features on the robot (e.g One branch for a brain display, another branch for testing odometry, another one for pure pursuit). At the end, we can combine all of these branches for our finalized code
- We can also record the issues that we face, so that all members are aware of them and can think of solutions.
- We also use Liveshare (VsCode Extension) to directly share the code during meetings where all members will can directly edit the code on different devices. 

## Solo Autonomous Win Point:
- Our robot is designed to be able to get the autonomous win point by itself by shooting the alliance triball across the field into the net, picking up the triball in the corner, and also touching the pole

## Autonomous Coding Process:
- The first step is to find a possible route that is able to perform the tasks required in autonomous
- Odometry is used to keep track of the position of the robot, so that even if it our robot gets knocked off course in one place, it will be able to correct itself for the later tasks. (It is able to drive to a position on the field or turn to any position through a coordinate system)
- Instead of blindly testing where to make our robot drive to, we have a coordinate system where the center of the field is (0,0).
- We created a [website](https://capybaras-2055.vercel.app/) where we can enter the dimensions of our robot, an (x, y) coordinate and it will draw the robot on the field, so that we can test if our coordinates are reasonable before we testing it physically. This feature can be found [here](https://capybaras-2055.vercel.app/#/tracker/).
- It can also directly generate the code to perform those movements after giving it coordinates.
- Calculates the required timeout based on the distance between the current and new positions using Pythagorean Theorem.
- After checking all of the coordinates to drive to, we can implement it physically and add all other tasks to do in between each movement such as intaking and shooting.

## Issues We Faced:
- Rotational Sensor Angle Tuning:
  - We needed to figure out an angle for the puncher to go to in order to hold that position without it slipping
  - Tried different fixed values but that would cause variation after multiple shots
- Programming the routes:
  - The code on the website did not directly equal the route in real life
  - E.g The bot would graze a wall, not drive with enough speed, direction would be flipped
  - Many edits still had to made, but the website overall sped up the process and helped visualize the paths

# OLD
## Vision Sensor:
- By giving the sensor an image of a triball, it is able to detect any triballs in its view and tells us information such as the size with the x and y positions.
- We can then tell our robot to drive to the triball and pick it up for skills matches

## Color Sensor:
- Used to detect triballs using its RGB values; however it does not give its coordinates, just a true/false if it is detected
- Detects a triball coming into the intake and can be used to hold a triball in place before outtaking

## Distance Sensor:
- Detects if a triball is placed in the match load position, so that it can shoot automatically for matchloads after a triball is placed. This makes it easier for the driver as they don't have to keep clicking a button over and over, and it would be faster for the person placing the triball on the bot as there is less human error involved.
