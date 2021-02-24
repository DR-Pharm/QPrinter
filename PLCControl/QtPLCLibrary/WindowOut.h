#pragma once
#include <QDialog>
#include "ui_WindowOut.h"
class WindowOut : public QDialog
{
	Q_OBJECT
signals:
	void MINUSONE();
public:
	WindowOut(QWidget *parent = Q_NULLPTR);
	~WindowOut();
	void getString(QString str, int time);
	void setWindowCount(int index);
	void showMe();

private:
	Ui::WindowOut ui;
	int windowCount=0;
};
