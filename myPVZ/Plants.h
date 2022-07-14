#pragma once

#include <QGraphicsItem>
#include <qrect.h>
#include <qpainter.h>
#include <qmouseeventtransition.h>
#include <qmovie.h>
#include "helper.h"
#include <qdebug.h>

class Plants : public QObject,public QGraphicsItem
{
public:
	Plants();
	~Plants();

	enum { Type = UserType + 10 };
	int type() const override;

	int HP;
	int ATK;
	int healthState;
	int healthStateToChange;
	int blockMax;
	int blocked;

	bool isSun;
	QString name;
	QRectF boundingRect() const;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
	void advance(int phase);

	void operator delete(void* plant);
	//void mousePressEvent(QGraphicsSceneMouseEvent* event);
	//void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

	int row, column;
protected:
	QMovie* movie;
};
