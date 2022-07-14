#pragma once
#include <qgraphicsitem.h>
#include "helper.h"
#include <qmovie.h>
#include <qpainter.h>
#include "Zombies.h"

class Pea : public QObject, public QGraphicsItem
{
public:
    Pea(int coordX, int row);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
    void advance(int phase) override;
    enum { Type = UserType + 12 };

protected:
    int coordX;
    int row;

    int ATK;
    QMovie* movie;
};

class Spine : public Pea
{
public:
    Spine(int coordX, int row);
    ~Spine();
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
    QRectF boundingRect() const;
};

class zombiePea :public Pea
{
public:
    zombiePea(int coordX, int row);
    ~zombiePea();
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
    void advance(int phase) override;
    QRectF boundingRect() const;

};