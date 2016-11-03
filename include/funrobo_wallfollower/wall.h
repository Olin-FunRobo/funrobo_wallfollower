#ifndef __WALL_H__
#define __WALL_H__

#include <QPolygonF>
#include <QGraphicsPolygonItem>
#include <QPen>

#include "utils.h"

class WallItem : public QGraphicsPolygonItem{

};

struct Wall
{
    QPolygonF poly;
    WallItem poly_item;
    QPen wallPen;
public:
    Wall();

    void draw();
    void reset(int n); //randomize to length
    void reset(const QVector<QPointF>& wall);

    void save(const QString& filename);
    void load(const QString& filename);
};

#endif
