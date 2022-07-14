#include "Wallnut.h"

Wallnut::Wallnut(int row, int column):
	Plants()
{
	blockMax = 2;
	name = "wallnut";
	HP = WALLNUT_HP;
	ATK = WALLNUT_ATK;
	this->row = row;
	this->column = column;

	movie = new QMovie(":/Plants/images/Plants/wallnut/wallnut.gif");
	movie->start();
	int coordX = 320 + (CELL_WIDTH - PLANT_WIDTH) / 2 + column * CELL_WIDTH;
	int coordY = 150 + CELL_HEIGHT - PLANT_HEIGHT + row * CELL_HEIGHT;
	setPos(coordX, coordY);

}

Wallnut::~Wallnut()
{
}

int Wallnut::type() const
{
	return Type;
}

void Wallnut::advance(int phase)
{
	if (!phase) {
		return;
	}
	update();

	if (HP <= 0) {
		healthStateToChange = 0;
	}
	else if (HP < WALLNUT_HP / 3) {
		healthStateToChange = 3;
	}
	else if (HP < WALLNUT_HP * 2 / 3) {
		healthStateToChange = 2;
	}

	if (healthState != healthStateToChange) {
		healthState = healthStateToChange;
		switch (healthState) {
		case 0:
			delete this;
			qDebug() << "wallnut dies!";
			break;
		case 1:
			delete movie;
			movie = new QMovie(":/Plants/images/Plants/wallnut/Wallnut.gif");
			movie->start();
			qDebug() << "wallnut state change to 1";
			break;
		case 2:
			delete movie;
			movie = new QMovie(":/Plants/images/Plants/wallnut/Wallnut_cracked1.gif");
			movie->start();
			qDebug() << "wallnut state change to 1";
			break;
		case 3:
			if (movie) {
				delete movie;
			}
			movie = new QMovie(":/Plants/images/Plants/wallnut/Wallnut_cracked2.gif");
			movie->start();
			qDebug() << "wallnut state change to 2";
			break;
		default:
			break;
		}
	}

}


