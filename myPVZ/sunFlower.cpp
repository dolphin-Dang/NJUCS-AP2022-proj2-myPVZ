#include "sunFlower.h"
#include "Cards.h"
#include "MainGame.h"

sunFlower::sunFlower(int row, int column)
{
	name = "sunflower";
	ATK = 0;
	HP = PEASHOOTER_HP;
	this->row = row;
	this->column = column;

	sunTime = 100;
	sunCount = 0;

	movie = new QMovie(":/Plants/images/Plants/sunflower/sunflower.gif");
	movie->start();
	int coordX = 320 + (CELL_WIDTH - PLANT_WIDTH) / 2 + column * CELL_WIDTH;
	int coordY = 150 + CELL_HEIGHT - PLANT_HEIGHT + row * CELL_HEIGHT;
	setPos(coordX, coordY);

}

sunFlower::~sunFlower()
{
}

void sunFlower::advance(int phase)
{
	if (!phase) {
		return;
	}
	update();

	if (sunCount < sunTime) {
		sunCount++;
	}
	else {
		sunCount = 0;
		Sun *newSun = new Sun(row, column);
		scene()->addItem(newSun);
		qDebug() << "create sun!";
	}
}

int sunFlower::type() const
{
	return Type;
}

Sun::Sun(int row, int column)
{
	name = "sun";
	ATK = 0;
	HP = PEASHOOTER_HP;
	this->row = row;
	this->column = column;

	movie = new QMovie(":/Others/images/Others/Sun.gif");
	movie->start();
	int coordX = 340 + (CELL_WIDTH - PLANT_WIDTH) / 2 + column * CELL_WIDTH;
	int coordY = 160 + CELL_HEIGHT - PLANT_HEIGHT + row * CELL_HEIGHT;
	setPos(coordX, coordY);

	isSun = true;
}

Sun::~Sun()
{
}

int Sun::type() const
{
	return Type;
}

void Sun::advance(int phase)
{
	if (!phase) {
		return;
	}

	update();
}

void Sun::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	Q_UNUSED(event);

	if (!Map::shovelCursor) {
		Cards::sunTotal += 25;
		delete this;
	}
}

void Sun::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	Q_UNUSED(event);
}
