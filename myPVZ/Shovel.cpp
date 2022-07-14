#include "shovel.h"
#include "Map.h"

Shovel::Shovel()
{
    setCursor(Qt::PointingHandCursor);
}

Shovel::~Shovel()
{
}


QRectF Shovel::boundingRect() const
{
    return QRectF(820, 30, 70, 70);
}

void Shovel::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(820, 30, 70, 70), QPixmap(":/Others/images/Others/shovelSlot.png"));
    painter->drawPixmap(QRect(830, 30, 50, 50), QPixmap(":/Others/images/Others/Shovel.png"));
}

void Shovel::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (Map::plantToSet == NULL) {
        if (event->button() == Qt::LeftButton) {
            if (!Map::shovelCursor) {
                QCursor cursor(QPixmap(":/Others/images/Others/Shovel.png"));
                QApplication::setOverrideCursor(cursor);
                Map::shovelCursor = true;
            }
            else {
                QApplication::restoreOverrideCursor();
                Map::shovelCursor = false;
            }
        }
    }
}


void Shovel::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
}

