#include "funrobo_wallfollower/mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    scene(new QGraphicsScene(0,0,PXL_DIMS,PXL_DIMS,this)),
    robot(scene, QPointF(PXL_DIMS/2,PXL_DIMS/2),0.0),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);

    wall.reset(10);
    scene.addItem(&wall.poly_item);


    timerId = startTimer(DT * 1000 / SIMULATION_ACCELARATION);
}


MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *){
    sense();


    // publish sensor data to ros
    // look at ros input msg and control robot
    robot.update();
    robot.setVelocity(0.0,0.0);
}

void MainWindow::sense(){
    publish_sensors(robot.sense(wall));
    // this is the important code
}

void MainWindow::publish_sensors(const std::vector<float>& val){
    std_msgs::Float32 msg;
    msg.data = val[0];
    ir_f.publish(msg);
    msg.data = val[1];
    ir_l.publish(msg);
    msg.data = val[2];
    ir_r.publish(msg);
}

void MainWindow::left_ctrl(const std_msgs::Float32ConstPtr &msg){
    robot.setVelocityL(msg->data);
}

void MainWindow::right_ctrl(const std_msgs::Float32ConstPtr &msg){
    robot.setVelocityR(msg->data);
}
