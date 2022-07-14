#pragma once
#pragma execution_character_set("utf-8")

#include <QtWidgets/QMainWindow>
#include "ui_beginWindow.h"
#include <qpainter.h>
#include <qpixmap.h>
#include "myPushButton.h"
#include <QMouseEvent>
#include <qdebug.h>
#include "MainGame.h"
#include <QDialog>

class beginWindow : public QMainWindow
{
    Q_OBJECT

public:
    beginWindow(QWidget *parent = Q_NULLPTR);

    void paintEvent(QPaintEvent* e);
    void mousePressEvent(QMouseEvent* event);
    void chooseMap();

private:
    Ui::beginWindowClass ui;
};