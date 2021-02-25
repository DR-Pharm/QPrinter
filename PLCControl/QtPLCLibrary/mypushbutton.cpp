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
		qDebug() << "图片加载失败";
		return;
	}

	//设置图片固定大小
	this->setFixedSize(m_btnW, m_btnH);

	//设置不规则图片样式
	this->setStyleSheet("QPushButton{border:0px;}");

	//设置图标
	this->setIcon(pix);

	//设置图标大小
	this->setIconSize(QSize(m_btnW, m_btnH));
	//创建动态对象
	{
		animation1 = new QPropertyAnimation(this, "geometry");
	//设置动画时间间隔
	animation1->setDuration(200);

	//起始位置
	animation1->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
	//结束位置
	animation1->setEndValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));

	//设置弹跳曲线
	animation1->setEasingCurve(QEasingCurve::OutBounce);
	}
	{    //创建动态对象
		animation2 = new QPropertyAnimation(this, "geometry");
		//设置动画时间间隔
		animation2->setDuration(200);

		//起始位置
		animation2->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
		//结束位置
		animation2->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));

		//设置弹跳曲线
		animation2->setEasingCurve(QEasingCurve::OutBounce);
	}
}

MyPushButton::~MyPushButton()
{
}

void MyPushButton::zoom1()
{    
	//执行动画
	animation1->start();
}

void MyPushButton::zoom2()
{
	//执行动画
	animation2->start();
}

void MyPushButton::mousePressEvent(QMouseEvent * e)
{
	if (this->pressImgPath != "") //传入的按下图片不为空 说明需要有按下状态，切换图片
	{
		QPixmap pix;
		bool ret = pix.load(this->pressImgPath);
		if (!ret)
		{
			qDebug() << "图片加载失败";
			return;
		}

		//设置图片固定大小
		this->setFixedSize(m_btnW, m_btnH);

		//设置不规则图片样式
		this->setStyleSheet("QPushButton{border:0px;}");

		//设置图标
		this->setIcon(pix);

		//设置图标大小
		this->setIconSize(QSize(m_btnW, m_btnH));

	}
	//让父类执行其他内容
	return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent * e)
{
	QThread::msleep(50);
	if (this->pressImgPath != "") //传入的按下图片不为空 说明需要有按下状态，切换成初始图片
	{
		QPixmap pix;
		bool ret = pix.load(this->normalImgPath);
		if (!ret)
		{
			qDebug() << "图片加载失败";
			return;
		}

		//设置图片固定大小
		//this->setFixedSize(pix.width(), pix.height());
		this->setFixedSize(m_btnW, m_btnH);

		//设置不规则图片样式
		this->setStyleSheet("QPushButton{border:0px;}");

		//设置图标
		this->setIcon(pix);

		//设置图标大小
		//this->setIconSize(QSize(pix.width(), pix.height()));
		this->setIconSize(QSize(m_btnW, m_btnH));

	}

	//让父类执行其他内容
	return QPushButton::mouseReleaseEvent(e);
}
