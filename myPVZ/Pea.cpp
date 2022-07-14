#include "Pea.h"
#include "balloonZombie.h"

Pea::Pea(int coordX, int row)
{
    this->coordX = coordX;
    this->row = row;
    setPos(coordX, 220 + row * CELL_HEIGHT);

    ATK = PEA_ATK;
    movie = new QMovie(":/Others/images/Others/pea.gif");
    movie->start();
}

QRectF Pea::boundingRect() const
{
    return QRectF(0, 0, 75, 50);
}

void Pea::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(boundingRect(), movie->currentImage());
}

bool Pea::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);
    if (other->type() == Zombies::Type) {
        return other->y() < this->y() && other->y() + 90 > this->y() && x() < other->x() + 20 && x() > other->x() - 20;
    }
    else {
        return false;
    }
}

void Pea::advance(int phase)
{
    if (!phase) {
        return;
    }
    update();

    QList<QGraphicsItem*> zombiesInFront = collidingItems();
    if (!zombiesInFront.isEmpty())
    {
        Zombies* zombie = dynamic_cast<Zombies*>(zombiesInFront[0]);
        zombie->HP -= ATK;
        qDebug() << "zombie hit by pea HP: " << zombie->HP;
        delete this;
        return;
    }

    if (x() > 1800) {
        delete this;
    }
    else {
        setX(x()+20);
    }
}

Spine::Spine(int coordX, int row):
    Pea(coordX,row)
{
    this->coordX = coordX;
    this->row = row;
    setPos(coordX, 220 + row * CELL_HEIGHT);

    ATK = SPINE_ATK;
    movie = new QMovie(":/Plants/images/Plants/cactus/Projectile32.png");
    movie->start();
}

Spine::~Spine()
{
}

bool Spine::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);
    if (other->type() == balloonZombie::Type) {
        return other->y() < this->y() && other->y() + 90 > this->y() && x() < other->x() + 20 && x() > other->x() - 20;
    }
    else {
        return false;
    }
}

QRectF Spine::boundingRect() const
{
    return QRectF(0,0,30,16);
}

zombiePea::zombiePea(int coordX, int row):
    Pea(coordX, row)
{
    ATK = PEA_ATK;
    movie = new QMovie(":/Zombies/images/Zombies/FlagZombie/brain.png");
    movie->start();

    setPos(coordX, 240 + row * CELL_HEIGHT);
}

zombiePea::~zombiePea()
{
}

bool zombiePea::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);
    if (other->type() == Plants::Type || other->type() == Wallnut::Type || other->type() == sunFlower::Type) {
        return other->y() - 50 < this->y() && other->y() + 50 > this->y() && x() < other->x() + 100 && x() > other->x();
    }
    else if (other->type() == Cactus::Type) {
        return other->y() - 10 < this->y() && other->y() + 90 > this->y() && x() < other->x() + 100 && x() > other->x();
    }
    else {
        return false;
    }
}

void zombiePea::advance(int phase)
{
    if (!phase) {
        return;
    }
    update();

    QList<QGraphicsItem*> plantsInFront = collidingItems();
    if (!plantsInFront.isEmpty())
    {
        Plants* plant = dynamic_cast<Plants*>(plantsInFront[0]);
        if (plant) {
            plant->HP -= ATK;
            //qDebug() << "plant hit by zombie pea HP: " << plant->HP;
            Map::plantsInMap[plant->row][plant->column] = NULL;
            delete this;
            return;
        }
    }

    if (x() < 0) {
        delete this;
    }
    else {
        setX(x() - 20);
    }

}

QRectF zombiePea::boundingRect() const
{
    return QRectF(0, 0, 32, 31);
}
