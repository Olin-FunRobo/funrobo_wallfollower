#include "funrobo_wallfollower/wall.h"

#include <time.h>

#define R_MAX (PXL_DIMS / 2)
#define R_MIN (PXL_DIMS / 8)

Wall::Wall(){
    QBrush wallBrush = QBrush(QColor::fromRgb(0,0,0),Qt::SolidPattern);
    wallPen = QPen(wallBrush, c2p(10.0));
}

void Wall::reset(int n){
    QVector<QPointF> wall;

    float x = R_MAX;
    float y = R_MAX; // at center

    for(int i=0; i<n; ++i){
        float t = (2 * M_PI) * i / n;
        float r = R_MIN + (R_MAX - R_MIN) * randu();
        wall.push_back(QPointF(x + r*cos(t), y + r*sin(t)));
    }
    //std::cout << "N : " << n << " wall SIZE : " << wall.size() << std::endl;
    reset(wall);
}

void Wall::reset(const QVector<QPointF> &wall){
    poly = QPolygonF(wall);
    poly_item.setPolygon(poly);
    poly_item.setPen(wallPen);
}
