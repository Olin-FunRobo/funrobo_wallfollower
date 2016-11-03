#include "funrobo_wallfollower/robotitem.h"


RobotItem::RobotItem(QPointF pos, QPointF dims, float theta):
pos(pos),dims(dims),theta(theta){
    ir_f = QPointF(dims.x() / 2, 0);
    ir_l = QPointF(0, -dims.y()/2);
    ir_r = QPointF(0, dims.y()/2);

}

QRectF RobotItem::boundingRect() const{
    return QRectF(pos - dims/2, pos + dims/2);
}

void RobotItem::setPos(QPointF p, float t){
    pos = p;
    theta = t;
}

void RobotItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    painter->translate(pos);
    painter->rotate(r2d(-theta));

    painter->drawRect(QRectF(-dims/2,dims/2));

    QColor trust(255,0,0,255);
    QColor doubt(0,128,0,64);

    painter->setPen(QPen(d_irf < IR_RANGE? trust : doubt, 4, Qt::DashLine));
    painter->drawLine(ir_f, ir_f + d_irf * QPointF(1.0, 0.0));


    painter->setPen(QPen(d_irl < IR_RANGE? trust : doubt, 4, Qt::DashLine));
    painter->drawLine(ir_l, ir_l - d_irl * QPointF(0.0, 1.0)); // TODO : IR_RANGE --> contact point

    painter->setPen(QPen(d_irr < IR_RANGE? trust : doubt, 4, Qt::DashLine));
    painter->drawLine(ir_r, ir_r + d_irr * QPointF(0.0, 1.0));

}

void RobotItem::setSensors(float d_irf, float d_irl, float d_irr){
    this->d_irf = d_irf;
    this->d_irl = d_irl;
    this->d_irr = d_irr;
}
