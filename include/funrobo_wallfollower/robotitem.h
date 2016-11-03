#ifndef ROBOTITEM_H
#define ROBOTITEM_H

#include <QObject>
#include <QPointF>
#include <QWidget>
#include <QPainter>
#include <QGraphicsItem>

#include "utils.h"

class RobotItem : public QGraphicsItem{
private:
    QPointF pos;
    QPointF ir_f, ir_l, ir_r; // ir positions
    float d_irf, d_irl, d_irr; // distances
    QPointF dims;
    float theta;
public:
    RobotItem(QPointF pos, QPointF dims, float theta);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setPos(QPointF pos, float theta);

    void setSensors(float d_irf, float d_irl, float d_irr); // sensor limits

};

#endif // ROBOTITEM_H
