#include "flyingZombie.h"

flyingZombie::flyingZombie()
{
	Map::zombiesInMap[row][column]--;

	dropping = false;

	HP = NORMALZOMBIE_HP * 2;
	ATK = NORMALZOMBIE_ATK;
	speed = NORMALZOMBIE_SPEED;

	flyingMovie = ":/Zombies/images/Zombies/FlyingZombie/1.gif";
	dropMovie = ":/Zombies/images/Zombies/FlyingZombie/Drop.gif";
	dyingMovie = ":/Zombies/images/Zombies/FlyingZombie/Die.gif";

	movie = new QMovie(flyingMovie);
	movie->start();

	tip = "/" + QString::number(HP);
	qDebug() << "flying zombie!";
}

flyingZombie::~flyingZombie()
{
}

int flyingZombie::type() const
{
	return Type;
}

void flyingZombie::advance(int phase)
{
	if (!phase) {
		return;
	}
	update();

	//end game
	if (x() <= 50) {
		emit zombieWin();
		delete this;
		return;
	}
	else if (healthState) {
		QList <QGraphicsItem*> plantsInFront = collidingItems();
		//cast item to a real plant
		Plants* plant = NULL;
		if (healthState != 0 && !plantsInFront.isEmpty()) {
			plant = dynamic_cast<Plants*>(plantsInFront[0]);
			if (plant->type() == Spikeweed::Type) {
				this->HP -= plant->ATK * 5;
				plant->stackBefore(this);
				setX(x() - BALLOONZOMBIE_SPEED);
			}
			else if(plant->type() != mapBlock::Type) {
				this->HP -= plant->ATK;
				plant->HP -= this->ATK;
				plant->stackBefore(this);
			}
			else {
				setX(x() - BALLOONZOMBIE_SPEED);
			}
		}
		else {
			setX(x() - BALLOONZOMBIE_SPEED);
		}
	}

	if (HP <= 0) {
		healthStateToChange = 0;
	}
	if (healthState != healthStateToChange) {
		healthState = healthStateToChange;
		switch (healthState) {
		case 0:
			delete movie;
			movie = new QMovie(dropMovie);
			movie->start();
			dropping = true;
			break;
		case 1:
			break;
		default:
			break;
		}
	}

	if (healthState == 0) {
		if (dropping) {
			if (movie->currentFrameNumber() == movie->frameCount() - 1) {
				delete movie;
				movie = new QMovie(dyingMovie);
				movie->start();
				dropping = false;
				return;
			}
		}
		else {
			if (movie->currentFrameNumber() == movie->frameCount() - 1) {
				delete this;
				return;
			}

		}
	}

	setToolTip(QString::number(HP) + tip);

}

bool flyingZombie::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
	Q_UNUSED(mode);
	if (other->type() == Cactus::Type) {
		return other->y() == this->y() + 10 && other->x() + 55 > x() && x() > other->x() - 120;
	}
	else if (other->type() > UserType + 1) {
		return other->y() == this->y() + 50 && other->x() + 15 > x() && x() > other->x() - 120;
	}
	return false;
}
