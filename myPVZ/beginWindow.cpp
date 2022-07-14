#include "beginWindow.h"

beginWindow::beginWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    setFixedSize(1800, 1200);
    setWindowIcon(QIcon(":/images/Others/FlagMeterParts1.png"));
    setWindowTitle("myPVZ");

    ////build a exit button
    myPushButton* exitBtn = new myPushButton\
        (204, 186, ":/Others/images/Others/Exit.png", ":/Others/images/Others/Exit2.png");
    exitBtn->setParent(this);
    exitBtn->move(1575, 925);

    connect(exitBtn, &QPushButton::clicked, this, &QMainWindow::close);


    //build a start button
    myPushButton* startBtn = new myPushButton\
        (712, 300, ":/Others/images/Others/Adventure_1.png", ":/Others/images/Others/Adventure_0.png");
    startBtn->setParent(this);
    startBtn->move(930, 200);

    connect(startBtn, &QPushButton::clicked, this, &beginWindow::chooseMap);
    Cards::sunTotal = BEGIN_SUN;
}

void beginWindow::paintEvent(QPaintEvent* e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap(":/Interface/images/Interface/MainMenu.png"), QRect());

}

void beginWindow::mousePressEvent(QMouseEvent* event)
{
    qDebug() << event->x() << ' ' << event->y();
}

void beginWindow::chooseMap()
{
    QDialog* cm = new QDialog();
    cm->setWindowTitle("µØÍ¼Ñ¡Ôñ");
    cm->setWindowIcon(QIcon(":/Others/images/Others/FlagMeterParts1.png"));
    cm->setFixedSize(900, 600);
    //set background image
    cm->setStyleSheet\
        ("QDialog{border-image:url(:/Interface/images/Interface/SeedChooser_Background.png);}");

    //create three buttons of map-choice
    myPushButton* defaultMap = new myPushButton\
        (508, 184, ":/Others/images/Others/ButtonDefault.png", ":/Others/images/Others/ButtonDefaultPressed.png", cm);
    myPushButton* userDefinedMap1 = new myPushButton\
        (226, 82, ":/Others/images/Others/ButtonUser1.png", ":/Others/images/Others/ButtonUser1Pressed.png", cm);
    myPushButton* userDefinedMap2 = new myPushButton\
        (226, 82, ":/Others/images/Others/ButtonUser2.png", ":/Others/images/Others/ButtonUser2Pressed.png", cm);
    myPushButton* quit = new myPushButton\
        (226, 82, ":/Others/images/Others/ButtonQuit.png", ":/Others/images/Others/ButtonQuitPressed.png", cm);

    //move to their places
    defaultMap->move((cm->width() - defaultMap->width()) / 2, cm->height() / 2 - defaultMap->height() - 30);
    userDefinedMap1->move((cm->width() - defaultMap->width()) / 2, cm->height() / 2 + 50);
    userDefinedMap2->move((cm->width() - defaultMap->width()) / 2 + defaultMap->width() - userDefinedMap2->width(), cm->height() / 2 + 50);
    quit->move(cm->width() - quit->width() - 40, cm->height() - quit->height() - 20);

    //build the main game scene
    //MainGame* mainGameScene = new MainGame;

    //connect the slots
    connect(quit, &QPushButton::clicked, cm, &QDialog::close);
    connect(defaultMap, &QPushButton::clicked, [=]() {
        cm->close();
        this->hide();
        Map::whichMap = 0;
        MainGame* mainGameScene = new MainGame;
        connect(mainGameScene, &MainGame::showMainWindow, [=]() {
            this->show();
            });
        mainGameScene->setAttribute(Qt::WA_DeleteOnClose);
        mainGameScene->show();
        });
    connect(userDefinedMap1, &QPushButton::clicked, [=]() {
        cm->close();
        this->hide();
        Map::whichMap = 1;
        MainGame* mainGameScene = new MainGame;
        connect(mainGameScene, &MainGame::showMainWindow, [=]() {
            this->show();
            });
        mainGameScene->map->setBlock();
        mainGameScene->setAttribute(Qt::WA_DeleteOnClose);
        mainGameScene->show();
        });
    connect(userDefinedMap2, &QPushButton::clicked, [=]() {
        cm->close();
        this->hide();
        Map::whichMap = 2;
        MainGame* mainGameScene = new MainGame;
        connect(mainGameScene, &MainGame::showMainWindow, [=]() {
            this->show();
            });
        mainGameScene->map->setBlock();
        mainGameScene->setAttribute(Qt::WA_DeleteOnClose);
        mainGameScene->show();
        });
    cm->exec();
}


