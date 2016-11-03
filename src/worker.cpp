#include "funrobo_wallfollower/worker.h"

// Spinner for pumping messages

Worker::Worker(){

}

Worker::~Worker(){

}

void Worker::process(){
    ros::spin();
}
