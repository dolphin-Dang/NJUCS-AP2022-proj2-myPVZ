#include "mapBlock.h"

mapBlock::mapBlock(int row, int column):
	Plants()
{
	name = "block";
	HP = INT_MAX;
	ATK = 0;
	this->row = row;
	this->column = column;

	movie = new QMovie(":/Plants/images/Plants/blockLogo.png");
	movie->start();
	int coordX = 320 + (CELL_WIDTH - PLANT_WIDTH) / 2 + column * CELL_WIDTH;
	int coordY = 150 + CELL_HEIGHT - PLANT_HEIGHT + row * CELL_HEIGHT;
	setPos(coordX, coordY);

}

mapBlock::~mapBlock()
{
}

int mapBlock::type() const
{
	return Type;
}
