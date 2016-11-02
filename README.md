## FunRobo Wall Follower

### Deliverable

For this deliverable, you're going to implement a simple automata for a simulation.

Your task description is as follows:

input : [sensor_msgs/Range] d_front, d_left, d_right
		or [std_msgs/Float32] d_front_val, d_left_val, d_right_val

output : [std_msgs/Twist] cmd_vel
		or [std_msgs/Float32] w_left, w_right

### Setup

```bash
sudo apt-get install qtbase5-dev
```

### Installing the simulator

```bash
roscd && cd ../
catkin_make [--pkg funrobo_wallfollower]
```
The content within the bracket is optional.


### Running the simulator

```bash
rosrun funrobo_wallfollower simulator
```

