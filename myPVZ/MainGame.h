#pragma once
#pragma execution_character_set("utf-8")

#include <QWidget>
#include "ui_MainGame.h"
#include <qgraphicsscene.h>
#include <qtimer.h>
#include "Map.h"
#include <QMouseEvent>
#include <qgraphicsview.h>
#include "Map.h"
#include "normalZombie.h"
#include "balloonZombie.h"
#include "flagZombie.h"
#include "myPushButton.h"
#include "Shovel.h"
#include "flyingZombie.h"

class MainGame : public QWidget
{
	Q_OBJECT

public:
	MainGame(QWidget *parent = Q_NULLPTR);
	~MainGame();

	int addZombieCounter;
	int stateChangeCounter;
	int addZombieTimeSpan;
	int addZombieFasterSpan;
	int endGameCounter;

	QGraphicsScene* scene;
	void mousePressEvent(QMouseEvent* event);

	void addPlantToScene(Plants* plant);
	void addZombie();

	Map* map;
	QTimer* timer;
	QGraphicsView* view;
	Shovel* shovel;

signals:
	void showMainWindow();

private:
	Ui::MainGame ui;
};
