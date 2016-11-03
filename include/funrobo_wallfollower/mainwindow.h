#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

#include <QPen>
#include <QBrush>

#include <ros/ros.h>
#include <std_msgs/Float32.h>

#include "wall.h"
#include "robot.h"
#include "utils.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QGraphicsScene scene;
    Wall wall;
    Robot robot;
    int timerId;

public:
    ros::Publisher ir_f, ir_l, ir_r;
    ros::Subscriber vel_l, vel_r;

public:
    explicit MainWindow(QWidget *parent = 0);
    void sense();
    ~MainWindow();

    void subscribe(ros::NodeHandle& n);
    void advertise(ros::NodeHandle& n);

    void left_ctrl(const std_msgs::Float32ConstPtr& msg);
    void right_ctrl(const std_msgs::Float32ConstPtr& msg);
    void publish_sensors(const std::vector<float>& val);

private:
    Ui::MainWindow *ui;
protected:
    void timerEvent(QTimerEvent *event);
};

#endif // MAINWINDOW_H
