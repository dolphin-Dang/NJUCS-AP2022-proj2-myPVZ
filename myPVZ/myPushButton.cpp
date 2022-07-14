#include "myPushButton.h"
#include <qdebug.h>

myPushButton::myPushButton(QWidget* parent)
{
	setParent(parent);
	normalImage = "";
	pressedImage = "";
}

myPushButton::myPushButton(int x, int y, QString normalImg, QString pressedImg, QWidget* parent)
{
	this->x = x;
	this->y = y;
	normalImage = normalImg;
	pressedImage = pressedImg;

	QPixmap pix;
	bool ret = pix.load(normalImage);
	if (!ret) {
		qDebug() << "Image open failed!";
		return;
	}

	this->setFixedSize(x, y);
	this->setStyleSheet("QPushButton{border:0px;}");
	this->setIcon(pix);
	this->setIconSize(QSize(x, y));

	if (parent != Q_NULLPTR) {
		setParent(parent);
		//qDebug() << "here";
	}
}

myPushButton::~myPushButton()
{
}

void myPushButton::addPressedImage(QString pressedImg)
{
	pressedImage = pressedImg;
}

void myPushButton::enterEvent(QEvent* event)
{
	if (this->pressedImage != "") {
		QPixmap pix;
		bool ret = pix.load(pressedImage);
		if (!ret) {
			qDebug() << "Image open failed!";
			return;
		}

		this->setFixedSize(x, y);
		this->setStyleSheet("QPushButton{border:0px;}");
		this->setIcon(pix);
		this->setIconSize(QSize(x, y));
	}

	qDebug() << "Mouse enter btn";
}

void myPushButton::leaveEvent(QEvent* event)
{
	QPixmap pix;
	bool ret = pix.load(normalImage);
	if (!ret) {
		qDebug() << "Image open failed!";
		return;
	}

	this->setFixedSize(x, y);
	this->setStyleSheet("QPushButton{border:0px;}");
	this->setIcon(pix);
	this->setIconSize(QSize(x, y));

	qDebug() << "Mouse leave btn";
}
