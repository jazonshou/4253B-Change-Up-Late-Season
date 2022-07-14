# 4253B Change Up Late Season Code

This repository contains the software [VRC](https://www.vexrobotics.com/v5/competition/vrc-current-game) team 4253B used in the 2020-21 season, [Change Up](https://www.youtube.com/watch?v=Hxs0q9UoMDQ). We used VEX's proprietary coding software, [VEXCode Pro](https://www.vexrobotics.com/vexcode/pro-v5), to program our software. 

## Code Highlights

* [`/src/drive/odom.cpp`](src/drive/odom.cpp) - Global state positioning using nonlinear state estimator. 

We used 2 tracking wheels, to measure distance, and 1 inertial measurement unit (IMU), to measure rotation. The sensor inputs give feedback that can be used to calculate the robot's position during autonomous. This tracking algorithm allows us to have incredibly accurate movements that can dynamically adapt to outside influence. 

* [`/src/drive/visiontt.cpp`](src/drive/visiontt.cpp) - Computer vision used for accurate turns



## Usage

1. Install VEXCode Pro [here](https://www.vexrobotics.com/vexcode/pro-v5)
2. Download code: 
| Git Installed | No Git Installed |
|---|---|
| Run ``git clone https://github.com/Yessir120/4253B-Change-Up-Late-Season.git`` in your terminal | Click the green ``Code`` button and select ``Download ZIP`` |
3. Enjoy!

## License
[MIT](https://choosealicense.com/licenses/mit/)
