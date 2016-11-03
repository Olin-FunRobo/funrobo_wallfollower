#include "funrobo_wallfollower/utils.h"
#include <random>
#include <iostream>
#include <QPointF>


const float CM_DIMS = 2048; // 2048 cm x 2048 cm

const float PXL_DIMS = 512; // 512 cm x 512 cm

const float DT = 0.01;

float SIMULATION_ACCELARATION = 1.;

const float ROBOT_LENGTH = c2p(60);
const float ROBOT_WIDTH = c2p(40);

const float WHEEL_DISTANCE = c2p(40);

const float IR_RANGE = c2p(80); // 0 ~ 80 cm


float i2c(float in){
    // inches to cm
    return 2.54 * in;
}

float c2p(float cm){
    // cm to pxl
    return cm * PXL_DIMS / CM_DIMS;
}

float min(float a, float b){
    return a<b?a:b;
}

float d2r(float d){
    return d / 180. * M_PI;
}
float r2d(float r){
    return r / M_PI * 180.;
}


float map(float val, float input_min, float input_max, float output_min, float output_max){
    return (val - input_min) / (input_max - input_min) * (output_max - output_min) + output_min;
}

float pow2vel(float v){
    return map(v, 0., 255., 0., 180.); // 180 is a rough extrapolation
}

float limit(float x, float min, float max){
    if(x < min)
        return min;
    if(x > max)
        return max;
    return x;
}

float norm(const QPointF& p){
    return sqrt(QPointF::dotProduct(p,p));
}

std::ostream& operator<<(std::ostream& os, QPointF p){
    os << "(" << p.x() << "," << p.y() << ")";
    return os;
}

class Randomizer{
private:
    std::mt19937 rng;
    std::uniform_real_distribution<float> dist;
public:
    Randomizer(float min, float max)
        : dist(min,max){
        rng.seed(std::random_device()());
    }
    float operator()(){
        return dist(rng);
    }
} randomizer(0.0,1.0);

float randu(){
    return randomizer();
}


bool within(float low, float x, float high){
    return low <= x && x <= high;
}

float cross(const QPointF& a, const QPointF& b){
    return a.x()*b.y() - a.y()*b.x();
}

bool intersect(
        const QPointF& p_0, const QPointF& p_1,
        const QPointF& q_0, const QPointF& q_1,
        QPointF& res){

    QPointF r(p_1-p_0);
    QPointF s(q_1-q_0);

    float csr = cross(s,r);

    if(csr != 0){
        float t = cross(q_0 - p_0, s) / -csr;
        float u = cross(p_0 - q_0, r) / csr;
        if(within(0, t, 1) && within(0, u, 1)){
           res = p_0 + t * r; // == q_0 + u * s
           return true;
        }
    }

    return false;
}
