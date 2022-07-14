#pragma once
#include "Zombies.h"
class flyingZombie :
    public Zombies
{
public:
    flyingZombie();
    ~flyingZombie();
    int type() const override;
    void advance(int phase);

    bool dropping;
    enum { Type = UserType + 2 };
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;

    QString flyingMovie;
    QString dropMovie;
};
