#include "QtPLCControl.h"
#include "QtSocket_Class.h"
#include "QtPLCDialogClass.h"
#include <QDebug>
#include "comm.h"

QtPLCControl::QtPLCControl()
{
	qRegisterMetaType<DataToPC_typ>("DataToPC_typ");
	qRegisterMetaType<DataToPC_typ>("DataToPC_typ&");//注册DataToPC_typ函数，在槽函数中避免出错
	AppPath = qApp->applicationDirPath();//exe所在目录

	QString LogInfo;
	LogInfo.sprintf("%p", QThread::currentThread());
	qDebug() << "PLC CONTROL" << "threadID : " << LogInfo;
}

void* QtPLCControl::QtCreateDialog(int index)
{
	dlg = new QtPLCDialogClass();
	((QtPLCDialogClass*)dlg)->SetSocket(((QtSocket_Class*)m_socket));
	return dlg;
}

void QtPLCControl::ProgramSetCloseEvent()
{
	if (m_socket !=nullptr)
	{
		((QtSocket_Class*)m_socket)->programsetCloseEvent();
	}
}
/////NewUI_Demo↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓


void QtPLCControl::syncData()
{
	if (m_socket !=nullptr)
	{
		((QtSocket_Class*)m_socket)->syncData();
	}
}

void QtPLCControl::AlarmReset()
{
	if (m_socket != nullptr)
	{
		((QtSocket_Class*)m_socket)->AlarmReset();
	}
}

void QtPLCControl::CountReset()
{
	if (m_socket != nullptr)
	{
		((QtSocket_Class*)m_socket)->CountReset();
	}
}

void QtPLCControl::SetAlarm(int index)
{
	if (m_socket != nullptr)
	{
		((QtSocket_Class*)m_socket)->SetAlarm(index);
	}
}
void QtPLCControl::RunSpeed(int index, void* data)
{
	if (m_socket !=nullptr)
	{
		((QtSocket_Class*)m_socket)->RunSpeed(index,(DataToPC_typ*)data);
	}
}

void QtPLCControl::EnReject(void* data)
{
	if (nullptr != m_socket)
	{
		((QtSocket_Class*)m_socket)->EnReject((DataToPC_typ*)data);
	}
}

void QtPLCControl::GoHome()
{
	if (nullptr != m_socket)
	{
		((QtSocket_Class*)m_socket)->GoHome();
	}
}
/////NewUI_Demo↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

void QtPLCControl::QtDestroyDlg()
{
	if (dlg!=nullptr)
	{
		((QtPLCDialogClass*)dlg)->dtClose();
		delete ((QtPLCDialogClass*)dlg);
		dlg = nullptr;
	}
}

int QtPLCControl::Getm_bconnected()
{
	if (nullptr != ((QtSocket_Class*)m_socket))
	{
		return ((QtSocket_Class*)m_socket)->Getm_bconnected();
	}
	return -1;
}
void QtPLCControl::connectIN_AND_OUT(void * d,int type,int home,int kickOpen,int kickMode)
{
	emit FROMPLC(d,type,home,kickOpen,kickMode);
}
void QtPLCControl::reportSocketError()
{
//	emit SOCKETERROR();
}

bool QtPLCControl::ConnectPlc()
{
	m_socket = new QtSocket_Class(nullptr);

	if (((QtSocket_Class*)m_socket)->initialization())
	{
		//bool b = connect(this, SIGNAL(SHOWEVERYPLCCONNECT(DataToPC_typ)), this, SLOT(showPLCValue(DataToPC_typ)));
		bool b = connect(((QtSocket_Class*)m_socket), &QtSocket_Class::signal_Connected, [=] {
			emit signal_SUCCESSFULCONNECTED();
		});
		b = connect(((QtSocket_Class*)m_socket), &QtSocket_Class::signal_SOCKETERROR, [=] {
			emit SOCKETERROR();
		});
		b = connect(((QtSocket_Class*)m_socket), SIGNAL(signal_FROMPLC(void*, int, int, int, int)), this, SLOT(connectIN_AND_OUT(void*,int,int, int, int)));
		//b = connect(m_socket, SIGNAL(signal_SOCKETERROR(QAbstractSocket::SocketError)), this, SLOT(reportSocketError(QAbstractSocket::SocketError)));
		b = connect(this, SIGNAL(STARTCONNECT(QString, int)), ((QtSocket_Class*)m_socket), SLOT(connectServer(QString,int)));
		//m_socket->connectServer(ipAddress.toStdString().c_str(), port);
		emit STARTCONNECT("10.86.50.210", 5000);
	}
	return false;
}

void QtPLCControl::SendPlcCommand(void *fromPLC, void *toPlc)
{
	if (nullptr != m_socket)
	{
		((QtSocket_Class*)m_socket)->Communicate_PLC((DataFromPC_typ*)fromPLC, (DataToPC_typ *) toPlc);
	}
}


void QtPLCControl::StartWork()
{
	if (nullptr != m_socket)
	{
		((QtSocket_Class*)m_socket)->StartWork();
	}
}

void QtPLCControl::StopWork()
{
	if (nullptr != m_socket)
	{
		((QtSocket_Class*)m_socket)->StopWork();
	}
}

bool QtPLCControl::SetResult(int counter, unsigned int alarm[2])
{

	return ((QtSocket_Class*)m_socket)->SetResult(counter,&alarm[0]);
}

void QtPLCControl::setStartWork(bool b)
{
	if (nullptr != m_socket)
	{
		if (b)
		{
			((QtSocket_Class*)m_socket)->StartWork();
		}
		else
		{
			((QtSocket_Class*)m_socket)->StopWork();
		}
	}
}

void QtPLCControl::InitWork()//PLC.txt
{
	if (nullptr != m_socket)
	{
		((QtSocket_Class*)m_socket)->InitWork();
	}
}

void QtPLCControl::setWinMini()
{
	if (dlg != nullptr)
	{
		((QtPLCDialogClass*)dlg)->setWindowMinimized();
	}
}