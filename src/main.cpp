#include <ros/ros.h>
#include <iostream>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h> // cmd_vel
#include <QApplication>
#include <QThread>

#include "funrobo_wallfollower/mainwindow.h"
#include "funrobo_wallfollower/worker.h"


MainWindow* w_ptr = nullptr;

int main(int argc, char* argv[]){
    // initialize window
    QApplication a(argc, argv);

    MainWindow w(nullptr);
    w_ptr = &w;

    //start ROS thread for pumping ROS messages
    ros::init(argc, argv, "simulator");
    ros::NodeHandle n;

    ros::Subscriber vel_l = n.subscribe<std_msgs::Float32>("/vel_l", 1000, &MainWindow::left_ctrl, w_ptr);
    ros::Subscriber vel_r = n.subscribe<std_msgs::Float32>("/vel_r", 1000, &MainWindow::right_ctrl, w_ptr);

    w.ir_f = n.advertise<std_msgs::Float32>("/ir_f", 10, false);
    w.ir_l = n.advertise<std_msgs::Float32>("/ir_l", 10, false);
    w.ir_r = n.advertise<std_msgs::Float32>("/ir_r", 10, false);

    QThread* thread = new QThread;
    Worker* worker = new Worker();
    worker->moveToThread(thread);

    QObject::connect(thread, SIGNAL(started()), worker, SLOT(process()));
    QObject::connect(worker, SIGNAL(finished()), thread, SLOT(quit()));

    QObject::connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();


    // begin interaction

    w.show();
    return a.exec();
}
