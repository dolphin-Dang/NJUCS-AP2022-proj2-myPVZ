#pragma once

#include <QPushButton>
#include "ui_myPushButton.h"

class myPushButton : public QPushButton
{
	Q_OBJECT

private:
	QString normalImage;
	QString pressedImage;
	int x;
	int y;

public:
	myPushButton(QWidget* parent = Q_NULLPTR);
	myPushButton(int x, int y, QString normalImg, QString pressedImg = "", QWidget* parent = Q_NULLPTR);
	~myPushButton();

	void addPressedImage(QString pressedImg);

	//mouse events
	void enterEvent(QEvent* event);
	void leaveEvent(QEvent* event);

private:
	Ui::myPushButton ui;
};
