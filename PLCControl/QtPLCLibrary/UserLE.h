#pragma once

#include <QLineEdit>

class UserLE : public QLineEdit
{
	Q_OBJECT
signals:
	void POPUPKEYBOARD(); 
	void CHANGERUNSPEED();
public:
	UserLE(QWidget *parent);
	~UserLE();
public slots:
	void mousePressEvent(QMouseEvent*);
	virtual void focusInEvent(QFocusEvent *event);
};
