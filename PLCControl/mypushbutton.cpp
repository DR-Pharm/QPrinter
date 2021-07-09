#include "mypushbutton.h"
#include <QThread>
MyPushButton::MyPushButton(QString normalImg, QString pressImg,int w,int h)
{
	this->normalImgPath = normalImg;
	this->pressImgPath = pressImg;
	m_btnW = w;
	m_btnH = h;
	QPixmap pix;
	bool ret = pix.load(normalImg);
	if (!ret)
	{
		qDebug() << "ͼƬ����ʧ��";
		return;
	}

	//����ͼƬ�̶���С
	this->setFixedSize(m_btnW, m_btnH);

	//���ò�����ͼƬ��ʽ
	this->setStyleSheet("QPushButton{border:0px;}");

	//����ͼ��
	this->setIcon(pix);

	//����ͼ���С
	this->setIconSize(QSize(m_btnW, m_btnH));
	//������̬����
	{
		animation1 = new QPropertyAnimation(this, "geometry");
	//���ö���ʱ����
	animation1->setDuration(200);

	//��ʼλ��
	animation1->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
	//����λ��
	animation1->setEndValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));

	//���õ�������
	animation1->setEasingCurve(QEasingCurve::OutBounce);
	}
	{    //������̬����
		animation2 = new QPropertyAnimation(this, "geometry");
		//���ö���ʱ����
		animation2->setDuration(200);

		//��ʼλ��
		animation2->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
		//����λ��
		animation2->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));

		//���õ�������
		animation2->setEasingCurve(QEasingCurve::OutBounce);
	}
}

MyPushButton::~MyPushButton()
{
}

void MyPushButton::zoom1()
{    
	//ִ�ж���
	animation1->start();
}

void MyPushButton::zoom2()
{
	//ִ�ж���
	animation2->start();
}

void MyPushButton::mousePressEvent(QMouseEvent * e)
{
	if (this->pressImgPath != "") //����İ���ͼƬ��Ϊ�� ˵����Ҫ�а���״̬���л�ͼƬ
	{
		QPixmap pix;
		bool ret = pix.load(this->pressImgPath);
		if (!ret)
		{
			qDebug() << "ͼƬ����ʧ��";
			return;
		}

		//����ͼƬ�̶���С
		this->setFixedSize(m_btnW, m_btnH);

		//���ò�����ͼƬ��ʽ
		this->setStyleSheet("QPushButton{border:0px;}");

		//����ͼ��
		this->setIcon(pix);

		//����ͼ���С
		this->setIconSize(QSize(m_btnW, m_btnH));

	}
	//�ø���ִ����������
	return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent * e)
{
	QThread::msleep(50);
	if (this->pressImgPath != "") //����İ���ͼƬ��Ϊ�� ˵����Ҫ�а���״̬���л��ɳ�ʼͼƬ
	{
		QPixmap pix;
		bool ret = pix.load(this->normalImgPath);
		if (!ret)
		{
			qDebug() << "ͼƬ����ʧ��";
			return;
		}

		//����ͼƬ�̶���С
		//this->setFixedSize(pix.width(), pix.height());
		this->setFixedSize(m_btnW, m_btnH);

		//���ò�����ͼƬ��ʽ
		this->setStyleSheet("QPushButton{border:0px;}");

		//����ͼ��
		this->setIcon(pix);

		//����ͼ���С
		//this->setIconSize(QSize(pix.width(), pix.height()));
		this->setIconSize(QSize(m_btnW, m_btnH));

	}

	//�ø���ִ����������
	return QPushButton::mouseReleaseEvent(e);
}
