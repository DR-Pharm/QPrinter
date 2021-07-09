#pragma once

#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>
#include <QPropertyAnimation>

class MyPushButton : public QPushButton
{
	Q_OBJECT

public:
	MyPushButton(QString normalImg, QString pressImg = "",int w=260,int h=80);
	~MyPushButton();    //成员属性 保存用户传入的默认显示路径 以及按下后显示的图片路径
	QString normalImgPath;
	QString pressImgPath;
	int m_btnW;
	int m_btnH;
	//弹跳特效
	QPropertyAnimation * animation1 = nullptr;
	QPropertyAnimation * animation2 = nullptr;
	void zoom1(); //向下跳
	void zoom2(); //向上跳

	//重写按钮 按下 和 释放事件
	void mousePressEvent(QMouseEvent *e);

	void mouseReleaseEvent(QMouseEvent *e);
};
