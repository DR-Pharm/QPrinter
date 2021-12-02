#pragma once
#include <QLabel>
#include <QPoint>
#include <QMovie>
class MyLabels : public QLabel
{
	Q_OBJECT
signals:
private:
	QLabel*lb;	
	QMovie *movie;
	QString AppPath = qApp->applicationDirPath();
public:
	bool b_scale = false;
	MyLabels(QWidget *parent, int i = -1)
		: QLabel(parent)
	{
		lb = new QLabel(parent);
		lb->setVisible(false);
		pa = parent;
	};
	QWidget *pa;
public slots:
	void mousePressEvent(QMouseEvent*)
	{
	};
	void enterEvent(QEvent *e)
	{
		//this->setText(QString::fromLocal8Bit("»¶Ó­Ê¹ÓÃ"));

		lb->setFixedHeight(this->height()*1.9);
		lb->move(pa->width()/2-lb->width()/2, 0);
		lb->setAlignment(Qt::AlignCenter);
		lb->setPixmap(QPixmap(AppPath + "/ico/dr.ico"));
		lb->setScaledContents(true);
		lb->setVisible(true);
		lb->lower();
	}
	void leaveEvent(QEvent *e)
	{
		lb->setVisible(false);
	}
};