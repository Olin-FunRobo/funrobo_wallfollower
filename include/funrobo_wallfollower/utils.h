#ifndef __UTILS_H__
#define __UTILS_H__

#include <math.h>
#include <QPointF>
#include <iostream>

extern const float CM_DIMS; // 256 cm x 256 cm
extern const float PXL_DIMS; // 512 cm x 512 cm

extern const float DT; // simulation resolution, in seconds
extern float SIMULATION_ACCELARATION; //simulation acceleration multiplier

extern const float ROBOT_WIDTH; // in cm
extern const float ROBOT_LENGTH;

extern const float WHEEL_DISTANCE; // in cm

extern const float IR_RANGE;

extern float i2c(float in); // inches to cm
extern float c2p(float cm); // cm 2 pxl
extern float min(float a, float b); //minimum of a,b

extern float d2r(float d); //degress to radians
extern float r2d(float r); //radians to degrees

extern float pow2vel(float v); // converts "power" (input to adafruit board) to velocity

extern float map(float val, float input_min, float input_max, float output_min, float output_max);
extern float limit(float x, float min, float max);

extern float randu();

std::ostream& operator<<(std::ostream& os, QPointF p);

bool within(float low, float x, float high);

float cross(const QPointF& a, const QPointF& b);

float norm(const QPointF&);

bool intersect(
        const QPointF& p_0, const QPointF& p_1,
        const QPointF& q_0, const QPointF& q_1,
        QPointF& res);

enum {FRONT, LEFT, RIGHT};

#endif // UTILS_H
