#include "Map.h"
#include <qdebug.h>
#include "MainGame.h"
#include <fstream>
#include <string>

Cards* Map::plantToSet = NULL;
Plants* Map::plantsInMap[MAP_ROWS][MAP_COLUMNS];
Plants* Map::blocks[MAP_ROWS][MAP_COLUMNS];
int Map::zombiesInMap[MAP_ROWS][MAP_COLUMNS];
int Map::whichMap = 0;		//0:defaultMap 1:userDefinedMap1 2:userDefinedMap2
bool Map::shovelCursor = false;

using namespace std;

Map::Map()
{
	for (int i = 0; i < MAP_ROWS; i++) {
		for (int j = 0; j < MAP_COLUMNS; j++) {
			plantsInMap[i][j] = NULL;
            blocks[i][j] = NULL;
            zombiesInMap[i][j] = 0;
		}
	}
}

Map::~Map()
{
}

QRectF Map::boundingRect() const
{
	return QRectF(320, 170, 1430, 970);
}

void Map::advance(int phase)
{
    if (!phase) {
        return;
    }
}

void Map::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

}

void Map::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    //set plant
    int i = ((int)event->scenePos().y() - 170) / CELL_HEIGHT;
    int j = ((int)event->scenePos().x() - 320) / CELL_WIDTH;
    if (plantToSet && event->button() == Qt::LeftButton)
    {
        //qDebug() << i << ' ' << j;
        if (i < 0 || i>4 || j < 0 || j>8) {
            plantToSet = NULL;
            QApplication::restoreOverrideCursor();
            //qDebug() << "out of range!";
            return;
        }
        if (!plantsInMap[i][j])
        {
            switch (plantToSet->num)
            {
            case 1:
                plantsInMap[i][j] = new Wallnut(i, j);
                break;
            case 2:
                plantsInMap[i][j] = new peaShooter(i, j);
                break;
            case 3:
                plantsInMap[i][j] = new Cactus(i, j);
                break;
            case 4:
                plantsInMap[i][j] = new Spikeweed(i, j);
                break;
            case 5:
                plantsInMap[i][j] = new sunFlower(i, j);
                break;
            default:
                break;
            }

            //I can't use scene object here!
            scene()->addItem(plantsInMap[i][j]);

            plantToSet->sunTotal -= plantToSet->sunNeed;
            plantToSet->coolCounter = 0;
            plantToSet = NULL;
            QApplication::restoreOverrideCursor();
            
        }
    }
    else if (plantToSet && event->button() == Qt::RightButton) {
        plantToSet = NULL;
        QApplication::restoreOverrideCursor();
        //qDebug() << "planting canceled";
    }

    //remove plant
    if (!plantToSet && shovelCursor) {
        if (!plantsInMap[i][j]) {
            QApplication::restoreOverrideCursor();
            shovelCursor = false;
        }
        else {
            delete plantsInMap[i][j];
            plantsInMap[i][j] = NULL;
            QApplication::restoreOverrideCursor();
            shovelCursor = false;
        }
    }

}

void Map::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	Q_UNUSED(event);	
}

void Map::setBlock()
{
    qDebug() << "Map " << whichMap << " is chosen!";

    //set blocks
    fstream userMap;
    string lines;

    switch (whichMap) {
    case 1:
        userMap.open("userDefinedMap1.txt");
        break;
    case 2:
        userMap.open("userDefinedMap2.txt");
        break;
    default:
        break;
    }

    if (!userMap.is_open()) {
        qDebug() << "file open failed!";
        return;
    }
    for (int i = 0; i < MAP_ROWS; i++) {
        if (getline(userMap, lines)) {
            if (lines.length() == MAP_COLUMNS) {
                for (int j = 0; j < MAP_COLUMNS; j++) {
                    if (lines[j] == '1') {
                        blocks[i][j] = new mapBlock(i, j);
                        scene()->addItem(blocks[i][j]);
                        qDebug() << "block created in " << i << ' ' << j;
                    }
                    else if (lines[j] == '0') {
                        blocks[i][j] = NULL;
                    }
                    else {
                        qDebug() << "wrong map format!";
                        break;;
                    }
                }
            }
            else {
                qDebug() << "wrong map format!";
                break;;
            }
        }
        else {
            qDebug() << "wrong map format!";
            break;;
        }
    }
    userMap.close();
}

