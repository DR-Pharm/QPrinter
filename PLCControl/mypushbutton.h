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
	~MyPushButton();    //��Ա���� �����û������Ĭ����ʾ·�� �Լ����º���ʾ��ͼƬ·��
	QString normalImgPath;
	QString pressImgPath;
	int m_btnW;
	int m_btnH;
	//������Ч
	QPropertyAnimation * animation1 = nullptr;
	QPropertyAnimation * animation2 = nullptr;
	void zoom1(); //������
	void zoom2(); //������

	//��д��ť ���� �� �ͷ��¼�
	void mousePressEvent(QMouseEvent *e);

	void mouseReleaseEvent(QMouseEvent *e);
};
