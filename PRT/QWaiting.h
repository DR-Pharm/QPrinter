#pragma once

#include <QWidget>
#include <QMovie>
#include <QLabel>
#include <QKeyEvent>
#include "ui_QWaiting.h"

class QWaiting : public QWidget
{
	Q_OBJECT

public:
	QWaiting(QWidget *parent = Q_NULLPTR);
	~QWaiting();
	bool eventFilter(QObject*, QEvent*);
	void setTxt(QString);
private:
	Ui::QWaiting ui;	
	QMovie *m_movie = nullptr;
	bool m_bAltKeyPressed = false;
};
