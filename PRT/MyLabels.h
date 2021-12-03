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
	int i = 0;
	QString AppPath = qApp->applicationDirPath();
public:
	bool b_scale = false;
	MyLabels(QWidget *parent, int i = -1)
		: QLabel(parent)
	{
		lb = new QLabel(parent);
		pa = parent;
		//movie = new QMovie("D:/5.gif");
		movie = new QMovie(AppPath+"/ico/5.gif");
		movie->setSpeed(100);
		lb->setFixedSize(483, 366);
		lb->move(0, -200);
		lb->setAlignment(Qt::AlignCenter);
		lb->setMovie(movie);
		movie->start();
		lb->setScaledContents(true);
		lb->lower();
	};
	QWidget *pa;
public slots:
	void mousePressEvent(QMouseEvent*)
	{
		if (i==0)
		{
			i = 1;
			lb->setVisible(false);
		}
		else if (i==1)
		{
			i = 2; 
			lb->setFixedSize(60, 60);
			lb->move((pa->width() - 50) / 2, 20);
			lb->setPixmap(AppPath + "/ico/dr.ico");
			lb->setVisible(true);
		}
		else
		{
			i = 0; 
			lb->move(0, -200);
			lb->setFixedSize(483, 366);
			lb->setMovie(movie);
			lb->setVisible(true);
		}
	};
	void enterEvent(QEvent *e)
	{
		//this->setText(QString::fromLocal8Bit("»¶Ó­Ê¹ÓÃ"));


		//lb->setVisible(true);		
	}
	void leaveEvent(QEvent *e)
	{
		//lb->setVisible(false);
	}
};