#include "Cards.h"
#include <qdebug.h>
#include "Map.h"

int Cards::sunTotal = BEGIN_SUN;

Cards::Cards()
{
	setCursor(Qt::PointingHandCursor);
    coolCounter = 0;
}

Cards::~Cards()
{
}

QRectF Cards::boundingRect() const
{
	return QRectF(220 + num * 100, 30, 96, 135);
}

void Cards::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QImage image(":/Cards/images/Cards/card_" + name + ".png");
    painter->drawImage(boundingRect(), image);

    if (sunTotal < sunNeed)
    {
        painter->setBrush(QColor(0, 0, 0, 200));
        painter->drawRect(boundingRect());
    }
    if (coolCounter < coolTime)
    {
        painter->setBrush(QColor(0, 0, 0, 100));
        painter->drawRect(QRectF(220 + num * 100, 30, 96, 135 * (1 - (double)coolCounter / coolTime)));
    }
}

void Cards::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (Map::plantToSet) {
        Map::plantToSet = NULL;
        QApplication::restoreOverrideCursor();
        qDebug() << "planting canceled";

    }
    else {
        if (event->button() == Qt::LeftButton) {
            if (sunTotal >= sunNeed && coolCounter == coolTime) {
                QCursor cursor(QPixmap(":/Plants/images/Plants/" + name + '/' + name + ".gif"));
                QApplication::setOverrideCursor(cursor);
                Map::plantToSet = this;
                qDebug() << "Card clicked!";

            }
        }
    }
}

void Cards::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
}

void Cards::advance(int phase)
{
    if (!phase) {
        return;
    }
    update();
    if (coolCounter < coolTime) {
        coolCounter++;
    }
}

WallnutCard::WallnutCard()
{
	name = "wallnut";
	sunNeed = 50;
	coolTime = 100;
	num = 1;
    tip = "坚果墙\n近战反伤";
    setToolTip(tip);
}

peaShooterCard::peaShooterCard()
{
    name = "peashooter";
    sunNeed = 100;
    coolTime = 50;
    num = 2;
    tip = "豌豆射手\n面前整行";
    setToolTip(tip);
}

CactusCard::CactusCard()
{
    name = "cactus";
    sunNeed = 150;
    coolTime = 50;
    num = 3;
    tip = "仙人掌\n对空 面前一格";
    setToolTip(tip);
}

SpikeweedCard::SpikeweedCard()
{
    name = "spikeweed";
    sunNeed = 100;
    coolTime = 50;
    num = 4;
    tip = "地刺\n对地 同一格";
    setToolTip(tip);
}

SunFlowerCard::SunFlowerCard()
{
    name = "sunflower";
    sunNeed = 50;
    coolTime = 50;
    num = 5;
    tip = "向日葵\n生产阳光";
    setToolTip(tip);
}
