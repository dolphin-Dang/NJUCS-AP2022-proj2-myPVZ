#include "balloonZombie.h"

balloonZombie::balloonZombie()
{
	Map::zombiesInMap[row][column]--;

	dropping = false;

	HP = NORMALZOMBIE_HP;
	ATK = NORMALZOMBIE_ATK;
	speed = NORMALZOMBIE_SPEED;

	//walkMovie = ":/Zombies/images/Zombies/BalloonZombie/Walk.gif";
	//attackMovie = ":/Zombies/images/Zombies/BalloonZombie/Attack.gif";
	flyingMovie = ":/Zombies/images/Zombies/BalloonZombie/1.gif";
	dropMovie = ":/Zombies/images/Zombies/BalloonZombie/Drop.gif";
	dyingMovie = ":/Zombies/images/Zombies/BalloonZombie/Die.gif";

	movie = new QMovie(flyingMovie);
	movie->start();

	qDebug() << "balloon zombie created in row " << row;

	tip = "/" + QString::number(HP);
}

balloonZombie::~balloonZombie()
{
}

int balloonZombie::type() const
{
	return Type;
}

void balloonZombie::advance(int phase)
{
	if (!phase) {
		return;
	}
	update();

	//end game
	if (x() <= 50) {
		emit zombieWin();
		//qDebug() << "Zombie entered Dave's house!";
		delete this;
		return;
	}
	else if(healthState) {
		QList <QGraphicsItem*> plantsInFront = collidingItems();
		//cast item to a real plant
		Plants* plant = NULL;
		if (healthState != 0 && !plantsInFront.isEmpty()) {
			plant = dynamic_cast<Plants*>(plantsInFront[0]);
			if (plant->type() == Spikeweed::Type) {
				this->HP -= plant->ATK * 3;
				plant->stackBefore(this);
				//qDebug() << "balloon zombie on the spikeweed!";
			}
		}
		setX(x() - BALLOONZOMBIE_SPEED);
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


	//if (flyState) {
	//	if (attacked) {
	//		switch (flyState) {
	//		case 1:
	//			delete movie;
	//			movie = new QMovie(dropMovie);
	//			movie->start();
	//			flyState = 2;
	//			qDebug() << "balloon exploding!";
	//			break;
	//		case 2:
	//			if (movie->currentFrameNumber() == movie->frameCount() - 1) {
	//				qDebug() << "balloon zombie to the ground!";
	//				flyState = 0;
	//				delete movie;
	//				movie = new QMovie(walkMovie);
	//				movie->start();
	//			}
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//	else {
	//		setX(x() - BALLOONZOMBIE_SPEED);
	//	}
	//}
	//else {
	//	Zombies::advance(phase);
	//}

}

bool balloonZombie::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
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
