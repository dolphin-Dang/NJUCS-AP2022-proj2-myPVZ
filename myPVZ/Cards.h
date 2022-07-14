#pragma once
#pragma execution_character_set("utf-8")

#include <QGraphicsItem>
#include <qrect.h>
#include <qpainter.h>
#include <qmouseeventtransition.h>
#include <qcursor.h>
#include <qgraphicssceneevent.h>
#include  <qapplication.h>

class Cards : public QObject,public QGraphicsItem
{
	Q_OBJECT

public:
	Cards();
	~Cards();

	QString picture;
	QString name;
	QString tip;
	int num;
	int sunNeed;
	static int sunTotal;
	int coolTime;
	int coolCounter;

	QRectF boundingRect() const;
	void advance(int phase);
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

};

class WallnutCard :public Cards
{
public:
	WallnutCard();
};

class peaShooterCard : public Cards 
{
public:
	peaShooterCard();
};

class CactusCard : public Cards
{
public:
	CactusCard();
};

class SpikeweedCard : public Cards
{
public:
	SpikeweedCard();
};

class SunFlowerCard : public Cards
{
public:
	SunFlowerCard();
};