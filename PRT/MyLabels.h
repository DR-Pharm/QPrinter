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
		//movie = new QMovie("D:/5.gif");
		movie = new QMovie(AppPath+"/ico/5.gif");
		movie->setSpeed(100);
		lb->setFixedSize(483, 366);
		lb->move(0, -200);
		lb->setAlignment(Qt::AlignCenter);
		lb->setMovie(movie);
		movie->start();
		//lb->setScaledContents(true);
		lb->lower();
	};
	QWidget *pa;
public slots:
	void mousePressEvent(QMouseEvent*)
	{
	};
	void enterEvent(QEvent *e)
	{
		//this->setText(QString::fromLocal8Bit("»¶Ó­Ê¹ÓÃ"));


		lb->setVisible(true);		
	}
	void leaveEvent(QEvent *e)
	{
		lb->setVisible(false);
	}
};