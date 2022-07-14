#include "Zombies.h"
#include "MainGame.h"

int Zombies::zombieBeaten = 0;
Zombies* Zombies::staticZombie = NULL;

Zombies::Zombies()
{
	staticZombie = this;
	connect(this, &Zombies::staticPlayerWin, this, &Zombies::sendPlayerWin);

	srand((unsigned)time(NULL));
	row = (int)rand() % 5;
	rowToGo = row;
	column = MAP_COLUMNS - 1;
	coordY = 100 + CELL_HEIGHT - PLANT_HEIGHT + row * CELL_HEIGHT;
	setPos(1800, coordY);

	Map::zombiesInMap[row][column]++;
	speed = NORMALZOMBIE_SPEED;
	moveState = 1;
	moveStateToChange = 1;
	healthState = 1;
	healthStateToChange = 1;
	setZValue(2);
}

Zombies::~Zombies()
{
}

int Zombies::type() const
{
	return Type;
}

void Zombies::advance(int phase)
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

	//calculate zombie's position
	if (x() < 1600) {
		Map::zombiesInMap[row][column]--;
		column = MAP_COLUMNS - 1 - (1450 - x()) / CELL_WIDTH;
		Map::zombiesInMap[row][column]++;
	}

	if (row != rowToGo && healthState != 0) {
		if (moveState == 3) {
			coordY += 4;
			setY(coordY);
		}
		else if (moveState == 4) {
			coordY -= 4;
			setY(coordY);
		}

		if (coordY == 100 + CELL_HEIGHT - PLANT_HEIGHT + rowToGo * CELL_HEIGHT) {
			//zombie successfully goes to rowToGo
			Map::zombiesInMap[row][column]--;
			row = rowToGo;
			Map::zombiesInMap[row][column]++;
			moveStateToChange = 1;
			//qDebug() << "zombie successfully moved to target row : " << rowToGo;
		}
	}

	QList <QGraphicsItem*> plantsInFront = collidingItems();
	//cast item to a real plant
	Plants* plant = NULL;
	if (!plantsInFront.isEmpty()) {
		plant = dynamic_cast<Plants*>(plantsInFront[0]);
	}

	if (plantsInFront.isEmpty() || plantsInFront[0]->type() == Spikeweed::Type) {
		//advance!
		if (row == rowToGo && healthState != 0) {
			setX(x() - speed);
			moveStateToChange = 1;
		}
	}
	else if (plantsInFront[0]->type() >= Plants::Type && \
		plantsInFront[0]->type() != Pea::Type && plantsInFront[0]->type() != mapBlock::Type) {
		if (plant->blocked < plant->blockMax) {
			//still can block
			moveStateToChange = 2;
		}
		//else {
		//	qDebug() << "can not block'em!";
		//}
		//qDebug() << "zombie encounter a plant";
	}
	else if (plantsInFront[0]->type() == mapBlock::Type) {
		//zombie move basic rule:
		//first go forward, then go down, then go up, last boom die
		if (row < 4 && Map::blocks[row + 1][column] == NULL) {
			rowToGo = row + 1;
			moveStateToChange = 3;
			//qDebug() << "zombie move to row " << rowToGo << " from row " << row;
		}
		else if (row > 0 && Map::blocks[row - 1][column] == NULL) {
			rowToGo = row - 1;
			moveStateToChange = 4;
			//qDebug() << "zombie move to row " << rowToGo << " from row " << row;
		}
		else {
			healthStateToChange = 0;
			dyingMovie = ":/Zombies/images/Zombies/BoomDie.gif";
		}
	}

	if (HP <= 0) {
		healthStateToChange = 0;
	}

	//change states
	if (moveState != moveStateToChange) {
		moveState = moveStateToChange;
		switch (moveState) {
		case 1:
		case 3:
		case 4:
			if (healthStateToChange) {
				//if the zombie is not stuck
				delete movie;
				movie = new QMovie(walkMovie);
				movie->start();
				//qDebug() << "zombie starts walking (moveState: " << moveState;
			}
			break;
		case 2:
			//add blocked zombie
			if (plant) {
				plant->blocked++;
				//qDebug() << "blocked zombies add one! " << plant->blocked;
			}

			delete movie;
			movie = new QMovie(attackMovie);
			movie->start();
			//qDebug() << "zombie starts attacking";
			break;
		default:
			break;
		}
	}
	if (healthState != healthStateToChange) {
		healthState = healthStateToChange;
		switch (healthState) {
		case 0:
			//dying so minus blocked zombie
			if (plant) {
				plant->blocked--;
				//qDebug() << "blocked zombies minus one! " << plant->blocked;
			}
			Map::zombiesInMap[row][column]--;
			delete movie;
			movie = new QMovie(dyingMovie);
			movie->start();
			break;
		case 1:
			break;
		default:
			break;
		}
	}

	//attack each other
	//or avoid to eat the logo
	if (healthState == 1 && (moveState == 2 || moveState == 1)) {
		if (!plantsInFront.isEmpty()) {
			for (int i = 0; i < plantsInFront.size(); i++) {
				if (plantsInFront[i]->type() > UserType + 1 && plantsInFront[i]->type() != mapBlock::Type) {
					Plants* plant = dynamic_cast<Plants*>(plantsInFront[i]);
					if (plant) {
						if (plant->type() != Spikeweed::Type) {
							this->HP -= plant->ATK;
							plant->HP -= this->ATK;
							plant->stackBefore(this);
							//qDebug() << "zombie eating!" << "plant HP: " << plant->HP;
						}
						else {
							this->HP -= plant->ATK;
							plant->stackBefore(this);
							//qDebug() << "zombie on the spikeweed!";
						}
					}
				}
			}
		}
	}

	//play dying movie
	if (healthState == 0) {
		if (movie->currentFrameNumber() == movie->frameCount() - 1) {
			delete this;
			//qDebug() << "zombie dies!";
			return;
		}
	}

	setToolTip(QString::number(HP) + tip);

}

QRectF Zombies::boundingRect() const
{
	return QRectF(0, 0, 180, 180);
}

void Zombies::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);
	painter->drawImage(boundingRect(), movie->currentImage());
}

bool Zombies::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
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

void Zombies::operator delete(void* p)
{
	zombieBeaten++;
	if (zombieBeaten == WIN_NUM) {
		emit staticZombie->staticPlayerWin();
	}
	delete p;
}

void Zombies::sendPlayerWin()
{
	emit playerWin();
}
