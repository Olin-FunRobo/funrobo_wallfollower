#include "funrobo_wallfollower/mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTimer>

int lcnt=0, rcnt=0;

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

    if(++lcnt > 5){ // wait for 5dt and shut off
        robot.setVelocityL(0.0);
    }

    if(++rcnt > 5){ // wait for 5dt and shut off
        robot.setVelocityR(0.0);
    }

    sense(); // sense ir sensors
    robot.update(); // update robot position, apply velocity, etc.
}

void MainWindow::sense(){
    publish_sensors(robot.sense(wall));
}

void MainWindow::subscribe(ros::NodeHandle &n){
    vel_l = n.subscribe<std_msgs::Float32>("/vel_l", 1000, &MainWindow::left_ctrl, this);
    vel_r = n.subscribe<std_msgs::Float32>("/vel_r", 1000, &MainWindow::right_ctrl, this);
}

void MainWindow::advertise(ros::NodeHandle &n){
    ir_f = n.advertise<std_msgs::Float32>("/ir_f", 10, false);
    ir_l = n.advertise<std_msgs::Float32>("/ir_l", 10, false);
    ir_r = n.advertise<std_msgs::Float32>("/ir_r", 10, false);
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
    ui->l_pow_slider->setValue(msg->data);
    lcnt = 0;

}

void MainWindow::right_ctrl(const std_msgs::Float32ConstPtr &msg){
    robot.setVelocityR(msg->data);
    ui->r_pow_slider->setValue(msg->data);
    rcnt = 0;

}
void MainWindow::resetRobot(){
    robot.reset(QPointF(PXL_DIMS/2,PXL_DIMS/2),0);
}

void MainWindow::resetPower(){
    ui->l_pow_slider->setValue(0);
    ui->r_pow_slider->setValue(0);
    robot.setVelocity(0,0);
}

void MainWindow::setSimAccel(double accel){
    killTimer(timerId);
    SIMULATION_ACCELARATION = accel;
    timerId = startTimer(DT * 1000 / SIMULATION_ACCELARATION);
}
