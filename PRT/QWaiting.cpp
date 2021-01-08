#include "QWaiting.h"

QWaiting::QWaiting(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::SubWindow);//����Ϊ�Ի����񣬲���ȥ���߿�
	setWindowModality(Qt::ApplicationModal);//����Ϊģʽ�Ի���ͬʱ�ڹ���öԻ���ʱҪ���ø�����

	//����͸����
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
			{//����ALT+F4
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
