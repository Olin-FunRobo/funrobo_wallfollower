#include "funrobo_wallfollower/robot.h"
#include <iostream>

// 1 pxl = .5 cm
// 270 x 270 cm world

// robot = 20x16 cm

float coneRadius(float h, float fov){
    return h*tan(fov/2);
}

// RobotBody
Robot::Robot(QGraphicsScene& scene, QPointF pos, float theta):
    pos(pos),
    theta(theta)
{
    vel_l = vel_r = 0.;

    body = new RobotItem(pos,QPointF(ROBOT_LENGTH,ROBOT_WIDTH), 0.0);
    scene.addItem(body);


    update();
}

Robot::~Robot(){
    delete body;
}

void Robot::reset(QPointF p, float t){
    pos=p; theta=t;
    body->setPos(pos,theta);
}

void Robot::reset(QPolygonF route){
    pos = route.front();
    float dst_x = route[1].x();
    float dst_y = route[1].y();

    theta = atan2(pos.y() - dst_y,dst_x - pos.x());

}

void Robot::move(float delta, float dtheta){
    theta += dtheta * DT;
    pos += delta * QPointF(cos(theta), -sin(theta)) * DT;
    update();
}

void Robot::update(){
    // update position
    float w = (vel_r - vel_l) / WHEEL_DISTANCE;
    if(w != 0){
        float R = (vel_l + vel_r) / (2*w);

        QPointF ICC = pos + R * QPointF(-sin(theta), -cos(theta));
        // ICC = virtual center of rotation

        //std::cout << ICC << std::endl;

        float x = pos.x();
        float y = pos.y();
        float iccx = ICC.x();
        float iccy = ICC.y();

        pos.setX(
                    cos(-w*DT) * (x - iccx) +
                    -sin(-w*DT) * (y - iccy) +
                    iccx
                    );
        pos.setY(
                    sin(-w*DT) * (x - iccx) +
                    cos(-w*DT) * (y - iccy) +
                    iccy
                    );
        theta += w * DT;
    }else{
        // if w == 0, then division by zero would be bad..
        // since it's a special (and well-defined) case, we should handle this
        pos += vel_l * QPointF(cos(theta), -sin(theta)) * DT;
    }

    body->setPos(pos, theta);
    body->update();

    QPointF nx = QPointF(cos(theta), -sin(theta)); // normalized components in local coordinates
    QPointF ny = QPointF(sin(theta), cos(theta));

    ir[FRONT].src = pos + ROBOT_LENGTH/2 * nx;
    ir[FRONT].dst = ir[FRONT].src + IR_RANGE * nx;

    ir[LEFT].src = pos - ROBOT_WIDTH/2 * ny;
    ir[LEFT].dst = ir[LEFT].src - IR_RANGE * ny;

    ir[RIGHT].src = pos + ROBOT_WIDTH/2 * ny;
    ir[RIGHT].dst = ir[RIGHT].src + IR_RANGE * ny;

}
void Robot::setVelocityL(float v){
    vel_l = v;
}

void Robot::setVelocityR(float v){
    vel_r = v;
}

void Robot::setVelocity(float l, float r){
    setVelocityL(l);
    setVelocityR(r);
}

std::vector<float> Robot::sense(const Wall& wall){
    int n = wall.poly.size();


    QPointF res;
    std::vector<float> val{IR_RANGE, IR_RANGE, IR_RANGE};

    for(int i=0; i < 3; ++i){
        for(int j=0; j < n; ++j){

            // wall segment
            QPointF s_0 = wall.poly[j];
            QPointF s_1 = wall.poly[(j+1) % n]; // cyclic

            if (intersect(ir[i].src, ir[i].dst, s_0, s_1, res)){
                val[i] = min(val[i], norm(res - ir[i].src));
                // TODO : account for multiple-segment scenarios
            }

        }
    }

    body->setSensors(val[FRONT], val[LEFT], val[RIGHT]);

    return val;
}

void Robot::setVisible(bool visible){
    body->setVisible(visible);
}
