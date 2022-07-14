#pragma once

#include <QGraphicsItem>
#include <qmovie.h>
#include "helper.h"
#include <qpainter.h>
#include "Plants.h"
#include "Wallnut.h"
#include <qdebug.h>
#include "mapBlock.h"
#include "Map.h"

class Zombies : public QObject, public QGraphicsItem
{
	Q_OBJECT

public:
	Zombies();
	~Zombies();

	enum { Type = UserType + 1 };
	int type() const override;

	int HP;
	int ATK;
	int speed;
	int healthState;
	int healthStateToChange;
	int moveState;
	int moveStateToChange;

	static int zombieBeaten;

	QString name;
	QString tip;
	int row;
	int rowToGo;

	QString walkMovie;
	QString attackMovie;
	QString dyingMovie;

	void advance(int phase);
	QRectF boundingRect() const;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
	bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;

	void operator delete(void* p);
	//make a static zombie to send static signals
	static Zombies* staticZombie;

protected:
	int column;
	int coordX;
	int coordY;
	QMovie* movie;

signals:
	void zombieWin();
signals:
	void playerWin();
signals:
	void staticPlayerWin();

private slots:
	void sendPlayerWin();
};

