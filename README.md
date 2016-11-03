## FunRobo Wall Follower

![Demo](images/demo.png)

### Deliverable

For this deliverable, you're going to implement a simple automata for a simulation.

Namely, we're going to develop a wall-following robot. This may even be a useful behavior for your final robot.

After you fork this repository, do your hardware developments and create a pull request.

We'll run your code and see how well it performs with the system!

If you have any problems, or discover a strange bug, feel free to contact me.

Your task description is as follows:

input : [sensor_msgs/Range] d_front, d_left, d_right
		or [std_msgs/Float32] d_front_val, d_left_val, d_right_val

output : [std_msgs/Twist] cmd_vel
		or [std_msgs/Float32] w_left, w_right

### System Description

#### Inputs

- [std_msgs/Float32] ir_f : front IR with 80cm range
- [std_msgs/Float32] ir_l : left IR with 80cm range
- [std_msgs/Float32] ir_r : right IR with 80cm range

#### Outputs

- [std_msgs/Float32] vel_l : velocity of the left motor
- [std_msgs/Flaot32] vel_r : velocity of the right motor

#### Learning Objectives :

- Basic Inverse-Kinematics for Differential-Drive Robot
- Simple Autonomy Engine for Wall-Following Behavior
- Experience with Software-In-The-Loop Testing Control Code
- Proficiency with C++ and ROS

### Setup

```bash
sudo apt-get install qtbase5-dev
```

### Installing the simulator

First, [Fork the repository](https://help.github.com/articles/fork-a-repo/) to your own copy.
Then, you can work off of the fork and submit your results via pull request!

```bash
roscd && cd ../src
git clone https://github.com/Olin-FunRobo/funrobo_wallfollower.git 
cd ..
rosdep install funrobo_wallfollower
catkin_make [--pkg funrobo_wallfollower]
```

The content within the bracket is optional.

### Running the simulator

```bash
rosrun funrobo_wallfollower simulator
```
