#include "Spikeweed.h"

Spikeweed::Spikeweed(int row, int column) :
	Plants()
{
	blockMax = 0;
	name = "spikeweed";
	HP = 1;
	ATK = WALLNUT_ATK;
	this->row = row;
	this->column = column;

	movie = new QMovie(":/Plants/images/Plants/spikeweed/spikeweed.gif");
	movie->start();
	int coordX = 320 + (CELL_WIDTH - PLANT_WIDTH) / 2 + column * CELL_WIDTH;
	int coordY = 150 + CELL_HEIGHT - PLANT_HEIGHT + row * CELL_HEIGHT;
	setPos(coordX, coordY);

}

Spikeweed::~Spikeweed()
{
}

int Spikeweed::type() const
{
	return Type;
}

void Spikeweed::advance(int phase)
{
	if (!phase) {
		return;
	}
	update();

	if (HP <= 0) {
		healthStateToChange = 0;
	}

	if (healthState != healthStateToChange) {
		healthState = healthStateToChange;
		switch (healthState) {
		case 0:
			delete this;
			qDebug() << "Spikeweed dies!";
			break;
		default:
			break;
		}
	}

}


