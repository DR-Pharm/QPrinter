#include "QWaiting.h"

QWaiting::QWaiting(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::SubWindow);//设置为对话框风格，并且去掉边框
	setWindowModality(Qt::ApplicationModal);//设置为模式对话框，同时在构造该对话框时要设置父窗口

	//设置透明度
	//setWindowOpacity(0.8);
	m_movie = new QMovie("./ico/wait.gif");
	ui.label->setStyleSheet("background-color: transparent;");
	ui.label->setMovie(m_movie);
	ui.label->setScaledContents(true);
	m_movie->start();
	installEventFilter(this);
}

QWaiting::~QWaiting()
{
	m_movie->stop();
}

bool QWaiting::eventFilter(QObject* obj, QEvent* event)
{
	if (obj == this)
	{
		switch (event->type())
		{
		case QKeyEvent::KeyPress:
		{
			int key_type = static_cast<QKeyEvent*>(event)->key();
			if (key_type == Qt::Key_Alt)
				m_bAltKeyPressed = true;
			break;
		}
		case QEvent::KeyRelease:
		{
			int key_type = static_cast<QKeyEvent*>(event)->key();
			if (key_type == Qt::Key_Alt)
				m_bAltKeyPressed = false;
			break;
		}
		case QEvent::Close:
		{
			if (m_bAltKeyPressed)
			{//屏蔽ALT+F4
				event->ignore();
				return true;
				break;
			}
		}
		default:break;
		}
	}
	return QObject::eventFilter(obj, event);
}

void QWaiting::setTxt(QString str)
{
	ui.label_2->setText(str);
}
