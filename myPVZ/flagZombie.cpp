#include "flagZombie.h"
#include "Pea.h"
#include "MainGame.h"

flagZombie::flagZombie()
{
	HP = NORMALZOMBIE_HP;
	ATK = NORMALZOMBIE_ATK;
	speed = NORMALZOMBIE_SPEED;

	walkMovie = ":/Zombies/images/Zombies/FlagZombie/FlagZombie.gif";
	attackMovie = ":/Zombies/images/Zombies/FlagZombie/FlagZombieAttack.gif";
	dyingMovie = ":/Zombies/images/Zombies/FlagZombie/FlagZombieLostHead.gif";

	dying = false;
	shootSpan = 50;
	shootCounter = 0;

	movie = new QMovie(walkMovie);
	movie->start();

	qDebug() << "flag zombie created in row " << row;

	tip = "/" + QString::number(HP);
}

flagZombie::~flagZombie()
{
}

void flagZombie::advance(int phase)
{
	if (x() < 1600 && moveState == 1) {
		shootCounter++;
		if (shootCounter >= shootSpan) {
			//shoot!
			//qDebug() << "zombie shoot!";
			zombiePea* zPea = new zombiePea(x(), row);
			scene()->addItem(zPea);
			shootCounter = 0;
		}
	}

	update();
	if (healthState == 0) {
		if (!dying) {
			if (movie->currentFrameNumber() == movie->frameCount() - 1) {
				delete movie;
				movie = new QMovie(":/Zombies/images/Zombies/NormalZombie/ZombieDie.gif");
				movie->start();
				dying = true;
			}
			else {
				setX(x() - speed);
			}
		}
		else {
			if (movie->currentFrameNumber() == movie->frameCount() - 1) {
				delete this;
				//qDebug() << "flag zombie dies!";
				return;
			}

		}

	}
	else {
		Zombies::advance(phase);
	}

	setToolTip(QString::number(HP) + tip);
}
