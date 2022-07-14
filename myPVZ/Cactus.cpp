#include "Cactus.h"
#include "balloonZombie.h"
#include "MainGame.h"

Cactus::Cactus(int row, int column)
{
	name = "cactus";
	ATK = 0;
	HP = CACUS_HP;
	this->row = row;
	this->column = column;

	shootTime = 50;
	shootCount = 0;

	movie = new QMovie(":/Plants/images/Plants/cactus/cactus.gif");
	movie->start();
	int coordX = 320 + (CELL_WIDTH - PLANT_WIDTH) / 2 + column * CELL_WIDTH;
	int coordY = 150 + CELL_HEIGHT - PLANT_HEIGHT + row * CELL_HEIGHT;
	setPos(coordX, coordY - 40);

}

Cactus::~Cactus()
{
}

QRectF Cactus::boundingRect() const
{
	return QRectF(0, 0, PLANT_WIDTH + 20, PLANT_HEIGHT + 40);
}

int Cactus::type() const
{
	return Type;
}

void Cactus::advance(int phase)
{
	if (!phase) {
		return;
	}
	update();

	if (shootCount < shootTime) {
		shootCount++;
	}
	else {
		QList<QGraphicsItem*> zombiesInFront = collidingItems();
		if (!zombiesInFront.isEmpty()) {
			qDebug() << "cactus shoot!";
			Spine* spine = new Spine(320 + CELL_WIDTH * column + PLANT_WIDTH * 4 / 5, row);
			scene()->addItem(spine);
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
			qDebug() << "cactus dies!";
			break;
		default:
			break;
		}
	}

}

bool Cactus::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
	Q_UNUSED(mode);
	if (other->type() == balloonZombie::Type) {
		qDebug() << other->y() << ' ' << this->y();
		return other->y() == this->y() - 10 && this->x() < other->x() + 20;
	}
	else {
		return false;
	}
}
