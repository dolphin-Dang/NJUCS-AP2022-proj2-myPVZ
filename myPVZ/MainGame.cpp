#include "MainGame.h"
#include <qicon.h>
#include <qdebug.h>
#include "beginWindow.h"
#include <qlabel.h>

MainGame::MainGame(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(1800, 1200);
	setWindowIcon(QIcon(":/images/Others/FlagMeterParts1.png"));
	setWindowTitle("myPVZ");

	addZombieCounter = 0;
	stateChangeCounter = 0;
	addZombieTimeSpan = 5;
	addZombieFasterSpan = 3;
	endGameCounter = 0;

	timer = new QTimer;

	scene = new QGraphicsScene(this);
	scene->setSceneRect(0, 0, 1800, 1200);

	view = new QGraphicsView(scene, this);
	view->setBackgroundBrush(QPixmap(":/Interface/images/Interface/backgroundGrass.jpg"));

	//add quit button
	myPushButton* quitGame = new myPushButton\
		(226, 82, ":/Others/images/Others/QuitButton.png", ":/Others/images/Others/QuitButtonPressed.png", this);
	quitGame->move(1800-226, 0);
	quitGame->show();
	connect(quitGame, &QPushButton::clicked, [=]() {
		//qDebug() << "show main window and close this game!";
		emit showMainWindow();
		this->close();
		});

	//add items to the scene
	map = new Map;
	scene->addItem(map);

	shovel = new Shovel;
	scene->addItem(shovel);

	QLabel* sunLabel = new QLabel;
	sunLabel->setParent(this);
	sunLabel->setGeometry(50, 53, 150, 50);
	sunLabel->setStyleSheet("QLabel{"
		"border-image:url(:/Others/images/Others/SunBack.png) 4 4 4 4 stretch stretch;"
		"}");
	sunLabel->setAlignment(Qt::AlignCenter);
	sunLabel->setText(QString::number(Cards::sunTotal));

	Cards* cards[MAX_CARDS];
	for (int i = 0; i < MAX_CARDS; i++) {
		cards[i] = NULL;
	}
	cards[0] = new WallnutCard;
	scene->addItem(cards[0]);
	cards[1] = new peaShooterCard;
	scene->addItem(cards[1]);
	cards[2] = new CactusCard;
	scene->addItem(cards[2]);
	cards[3] = new SpikeweedCard;
	scene->addItem(cards[3]);
	cards[4] = new SunFlowerCard;
	scene->addItem(cards[4]);

	timer->start(TIMER_SPAN);
	view->show();


	//slots
	connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
	connect(timer, &QTimer::timeout, this, &MainGame::addZombie);
	connect(timer, &QTimer::timeout, [=]() {
		if (sunLabel) {
			sunLabel->setText(QString::number(Cards::sunTotal));
		}
		});

	

}

MainGame::~MainGame()
{
	timer->stop();
}

void MainGame::mousePressEvent(QMouseEvent* event)
{
	if (map->plantToSet && event->button() == Qt::RightButton) {
		map->plantToSet = NULL;
		QApplication::restoreOverrideCursor();
		//qDebug() << "planting canceled";
	}
	//qDebug() << event->x() << ' ' << event->y();
}

void MainGame::addPlantToScene(Plants* plant)
{
	this->scene->addItem(plant);
}

void MainGame::addZombie()
{
	addZombieCounter++;
	stateChangeCounter++;

	if (addZombieCounter * TIMER_SPAN >= addZombieTimeSpan * 1000) {
		//add a new zombie
		srand(time(NULL));
		int r = (int)rand() % ZOMBIES + 1;
		Zombies* zombie = NULL;
		switch (r) {
		case 1:
			zombie = new normalZombie;
			break;
		case 2:
			zombie = new balloonZombie;
			break;
		case 3:
			zombie = new flagZombie;
			break;
		case 4:
			zombie = new flyingZombie;
			break;
		default:
			break;
		}
		scene->addItem(zombie);
		//Cards::sunTotal += ADD_SUN;

		//zombie win signal
		connect(zombie, &Zombies::zombieWin, [=]() {
			timer->stop();
			QTimer* endTimer = new QTimer;
			endTimer->start(TIMER_SPAN);
			
			//put picture
			QLabel* endPicture = new QLabel;
			endPicture->setParent(this);
			endPicture->setGeometry(650, 366, 564, 468);
			endPicture->setStyleSheet("QLabel{"
				"border-image:url(:/Others/images/Others/ZombiesWon.png) 4 4 4 4 stretch stretch;"
				"}");
			endPicture->show();

			connect(endTimer, &QTimer::timeout, [=]() {
				endGameCounter++;
				if (endGameCounter == END_GAME_SPAN) {
					emit showMainWindow();
					this->close();
				}
				});
			});
		connect(zombie, &Zombies::playerWin, [=]() {
			timer->stop();
			QTimer* endTimer = new QTimer;
			endTimer->start(TIMER_SPAN);

			//put picture
			QLabel* endPicture = new QLabel;
			endPicture->setParent(this);
			endPicture->setGeometry(650, 366, 564, 468);
			endPicture->setStyleSheet("QLabel{"
				"border-image:url(:/Others/images/Others/playerWin.png) 4 4 4 4 stretch stretch;"
				"}");
			endPicture->show();

			connect(endTimer, &QTimer::timeout, [=]() {
				endGameCounter++;
				if (endGameCounter == END_GAME_SPAN) {
					emit showMainWindow();
					this->close();
				}
				});

			});

		addZombieCounter = 0;
	}
	else if (stateChangeCounter * TIMER_SPAN >= addZombieFasterSpan * 1000) {
		//make zombies' creation faster
		stateChangeCounter = 0;
		if (addZombieFasterSpan > 1) {
			addZombieFasterSpan -= 1;
			//qDebug() << "create zombies faster!";
		}
	}
}
