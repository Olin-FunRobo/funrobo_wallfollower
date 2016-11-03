#ifndef ROBOT_H
#define ROBOT_H

#include <vector>

#include <QObject>
#include <QPointF>

#include <QPolygonF>

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>

#include <QGraphicsScene>

#include "utils.h"
#include "robotitem.h"
#include "wall.h"

struct IR{
    QPointF src, dst;
    float val;
};

class Robot
{

public:
    QPointF pos; // current position

    float theta; // heading, measured from horz.  radians
    float vel_l, vel_r;

    bool emergency;

    IR ir[3];

    RobotItem* body;

public:
    Robot(QGraphicsScene& scene, QPointF pos, float theta);
    ~Robot();

    void reset(QPointF pos, float theta);
    void reset(QPolygonF route);

    void update();
    void move(float delta, float dtheta);
    void setVelocity(float left, float right);
    void setVelocityR(float r);
    void setVelocityL(float l);

    std::vector<float> sense(const Wall& wall);

    void setVisible(bool visible);
};

#endif // ROBOT_H
