#include "normalZombie.h"

normalZombie::normalZombie():
	Zombies()
{
	HP = NORMALZOMBIE_HP;
	ATK = NORMALZOMBIE_ATK;
	speed = NORMALZOMBIE_SPEED;

	walkMovie = ":/Zombies/images/Zombies/NormalZombie/Zombie.gif";
	attackMovie = ":/Zombies/images/Zombies/NormalZombie/ZombieAttack.gif";
	dyingMovie = ":/Zombies/images/Zombies/NormalZombie/ZombieDie.gif";

	movie = new QMovie(walkMovie);
	movie->start();

	qDebug() << "normal zombie created in row " << row;

	tip = "/" + QString::number(HP);
}

normalZombie::~normalZombie()
{
}
