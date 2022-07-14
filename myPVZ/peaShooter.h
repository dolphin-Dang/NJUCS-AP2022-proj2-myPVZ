#pragma once
#include "Plants.h"
#include "helper.h"
#include "Pea.h"

class peaShooter :
    public Plants
{
public:
    peaShooter(int row, int column);
    ~peaShooter();

    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const;

private:
    int shootTime;
    int shootCount;

};

