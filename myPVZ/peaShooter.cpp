#include "peaShooter.h"
#include "MainGame.h"

peaShooter::peaShooter(int row, int column)
{
	name = "peashooter";
	ATK = 0;
	HP = PEASHOOTER_HP;
	this->row = row;
	this->column = column;

	shootTime = 50;
	shootCount = 0;

	movie = new QMovie(":/Plants/images/Plants/peashooter/peashooter.gif");
	movie->start();
	int coordX = 320 + (CELL_WIDTH - PLANT_WIDTH) / 2 + column * CELL_WIDTH;
	int coordY = 150 + CELL_HEIGHT - PLANT_HEIGHT + row * CELL_HEIGHT;
	setPos(coordX, coordY);

}

peaShooter::~peaShooter()
{
}

void peaShooter::advance(int phase)
{
	if (!phase) {
		return;
	}
	update();

	if (shootCount < shootTime) {
		shootCount++;
	}
	else {
		//QList<QGraphicsItem*> zombiesInFront = collidingItems();
		//if (!zombiesInFront.isEmpty()) {
		//	qDebug() << "shoot!";
		//	Pea* pea = new Pea(320 + CELL_WIDTH * column + PLANT_WIDTH * 4 / 5, row);
		//	scene()->addItem(pea);
		//	shootCount = 0;
		//	return;
		//}

		bool shoot = false;
		for (int i = column; i < MAP_COLUMNS; i++) {
			if (Map::zombiesInMap[row][i]) shoot = true;
		}
		if (shoot) {
			qDebug() << "shoot!";
			Pea* pea = new Pea(320 + CELL_WIDTH * column + PLANT_WIDTH * 4 / 5, row);
			scene()->addItem(pea);
			shootCount = 0;
			return;
		}
	}

	if (HP <= 0) {
		healthStateToChange = 0;
	}

	if (healthState != healthStateToChange) {
		healthState = healthStateToChange;
		switch (healthState) {
		case 0:
			delete this;
			qDebug() << "peashooter dies!";
			break;
		default:
			break;
		}
	}

}

bool peaShooter::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
	Q_UNUSED(mode);
	//int shooterY = other->boundingRect().y();
	//int zombieY = this->boundingRect().y();
	if (other->type() == Zombies::Type) {
		return other->y() == this->y() - 50 && this->x() < other->x() + 20;
	}
	else {
		return false;
	}

}
