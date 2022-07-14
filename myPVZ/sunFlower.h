#pragma once

#include "Plants.h"
#include "helper.h"

class sunFlower :
    public Plants
{
public:
    sunFlower(int row, int column);
    ~sunFlower();

    void advance(int phase) override;
    enum { Type = UserType + 16 };
    int type() const override;

private:
    int sunTime;
    int sunCount;

};

class Sun : public Plants {
public:
    Sun(int row, int column);
    ~Sun();

    enum { Type = UserType + 17 };
    int type() const override;

    void advance(int phase) override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

};