#pragma once
#include "Plants.h"

class Cactus :
    public Plants
{
public:
    Cactus(int row, int column);
    ~Cactus();

    enum { Type = UserType + 13 };
    int type() const override;
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const;
    QRectF boundingRect() const;

private:
    int shootTime;
    int shootCount;

};

