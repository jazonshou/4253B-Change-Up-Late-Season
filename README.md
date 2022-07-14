# 4253B Change Up Late Season Code

This repository contains the software [VRC](https://www.vexrobotics.com/v5/competition/vrc-current-game) team 4253B used in the 2020-21 season, [Change Up](https://www.youtube.com/watch?v=Hxs0q9UoMDQ). We used VEX's proprietary coding software, [VEXCode Pro](https://www.vexrobotics.com/vexcode/pro-v5), to program our software. 

## Code Highlights

* [`/src/drive/odom.cpp`](src/drive/odom.cpp) - Global state positioning using nonlinear state estimator. 

We used 2 tracking wheels, to measure distance, and 1 inertial measurement unit (IMU), to measure rotation. The sensor inputs give feedback that can be used to calculate the robot's position during autonomous. This tracking algorithm allows us to have incredibly accurate movements that can dynamically adapt to outside influence. 

See more regarding odometry [here](http://thepilons.ca/wp-content/uploads/2018/10/Tracking.pdf) (*Introduction to Position Tracking*, VRC Team 5225A)

* [`/src/drive/visiontt.cpp`](src/drive/visiontt.cpp) - Computer vision used for accurate turns

As powerful as odometry may seem, it is still good practice to maneuver the robot relative to field elements. With the help of computer vision, we can accurately turn towards target field elements without completely relying on our tracking wheel odometry. The turn algorithm uses PID for even more accurate movements. 

PID essentially works by taking a mechanism's current state and comparing the state to the desired state. For example, with a drivetrain, the current location might be (0, 0) and the target location might be (5, 0). PID then computes the desired power the motors need to be at. 

![PID diagram](https://upload.wikimedia.org/wikipedia/commons/thumb/4/40/Pid-feedback-nct-int-correct.png/1200px-Pid-feedback-nct-int-correct.png)

* [`/src/drive/drive.cpp`](src/drive/drive.cpp) - Computer vision used for accurate turns

In VEX, the traditional approach to movement consists of point turns and lateral movement. While it may be simple, the approach is quite slow as you need to wait for PID to slow down in both turns and lateral movements. Thus, we created a custom algorithm that combines turns and lateral movements into smooth curves. Instead of turning and moving, the chassis moves in a smooth arc to get to its desired location. We attempted to achieve this result by combining the turn and lateral movement PID. Our implementation can be found in line 151 at the function ``moveToCurve``. 

* [`/src/rollers_intakes.cpp`](src/rollers_intakes.cpp) - Automatic color detection index system

A key element of Change Up is being able to index the right colored ball as fast as possible. We achieved this by using color sensors placed around the robot to provide feedback as to where and what color the ball(s) are. Then, we dynamically change the movement of the rollers to remove opponent balls from our robot and/or index our alliance's balls. Our implementation of this algorithm can be found on line 27 in the function ``autoIndex``. 

* [`/src/screen`](src/screen) - Screen experiments

We experimented with the v5 Brain's screen with mini-projects such as creating a [Pong](https://www.ponggame.org/) game. The screen was especially useful in applications like our auton selector, making selecting autons much easier. 

## Installation

1. Install VEXCode Pro [here](https://www.vexrobotics.com/vexcode/pro-v5)
2. Download code: 

| Git Installed | No Git Installed |
|---|---|
| Run ``git clone https://github.com/Yessir120/4253B-Change-Up-Late-Season.git`` in your terminal | Click the green ``Code`` button and select ``Download ZIP`` |
3. Compile & download to v5 Brain
4. Enjoy!

## License
[MIT](https://choosealicense.com/licenses/mit/)
