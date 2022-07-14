#include "Plants.h"
#include "Map.h"

Plants::Plants()
{
	blockMax = INT_MAX;
	blocked = 0;
	healthState = 1;
	healthStateToChange = 1;
	setZValue(1);

	int coordX = 320 + (CELL_WIDTH - PLANT_WIDTH) / 2 + column * CELL_WIDTH;
	int coordY = 150 + CELL_HEIGHT - PLANT_HEIGHT + row * CELL_HEIGHT;
	setPos(coordX, coordY);

	isSun = false;
}

Plants::~Plants()
{
}

int Plants::type() const
{
	return Type;
}

QRectF Plants::boundingRect() const
{
	return QRectF(0, 0, PLANT_WIDTH, PLANT_HEIGHT);
}

void Plants::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);
	painter->drawImage(boundingRect(), movie->currentImage());
}

void Plants::advance(int phase)
{
	if (!phase) {
		return;
	}
	update();

}

void Plants::operator delete(void* plant)
{
	Plants* plantPtr = (Plants*)plant;
	if (plantPtr->isSun) {
		Map::plantsInMap[plantPtr->row][plantPtr->column] = NULL;
	}
	delete plant;
}
