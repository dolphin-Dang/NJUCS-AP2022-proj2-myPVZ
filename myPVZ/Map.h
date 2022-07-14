#pragma once

#include <QGraphicsItem>
#include <qrect.h>
#include <qpainter.h>
#include <qmouseeventtransition.h>
#include "Wallnut.h"
#include "peaShooter.h"
#include "Cards.h"
#include "helper.h"
#include "mapBlock.h"
#include "Cactus.h"
#include "spikeweed.h"
#include "sunFlower.h"

class Map : public QObject, public QGraphicsItem
{
public:
	Map();
	~Map();

	static Cards* plantToSet;
	static bool shovelCursor;
	static Plants* plantsInMap[MAP_ROWS][MAP_COLUMNS];
	static Plants* blocks[MAP_ROWS][MAP_COLUMNS];
	static int zombiesInMap[MAP_ROWS][MAP_COLUMNS];
	static int whichMap;

	QRectF boundingRect() const;
	void advance(int phase);
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	void setBlock();
private:

};
