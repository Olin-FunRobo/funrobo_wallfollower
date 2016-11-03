#include <ros/ros.h>
#include <iostream>

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

    w.subscribe(n);
    w.advertise(n);

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
