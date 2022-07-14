#pragma once
#include <QGraphicsItem>
#include <qrect.h>
#include <qpainter.h>
#include <qmouseeventtransition.h>
#include <qcursor.h>
#include <qgraphicssceneevent.h>
#include  <qapplication.h>

class Shovel : public QObject, public QGraphicsItem
{
	Q_OBJECT

public:
	Shovel();
	~Shovel();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
};
