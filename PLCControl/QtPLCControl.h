#pragma once

#include <QApplication>
#include <QSettings>
#include <QtCore/QtCore>
#include <QObject>

#ifndef BUILD_STATIC
# if defined(QtPLCControl_LIB)
#  define QtPLCControl_EXPORT Q_DECL_EXPORT
# else
#  define QtPLCControl_EXPORT Q_DECL_IMPORT
# endif
#else
# define QtPLCControl_EXPORT
#endif

class QtPLCControl_EXPORT QtPLCControl:public QObject
{
	Q_OBJECT
signals:
	void signal_SUCCESSFULCONNECTED();
	void FROMPLC(void*);
	void SOCKETERROR();
	void STARTCONNECT(QString, int);
	void MAXBACK();
private:
	void *m_socket = nullptr;
	QString AppPath = qApp->applicationDirPath(); 
	void *dlg = nullptr;
	int m_cnCount = 0;
public:
	QtPLCControl();
	void setFeedMode(int);
	void* QtCreateDialog(int);
	void ProgramSetCloseEvent();
	void syncData();
	void AlarmReset();
	void CountReset();
	void RunSpeed(int, void*);
	void EnReject(void*);
	void GoHome();
	//单面同步计数
	void QtDestroyDlg();
//	void SetCallBack(MESSAGE_HANDLER,void*);
	void SendPlcCommand(void *, void*);
	void StartWork();
	void StopWork();
	bool SetResult(int counter, unsigned int alarm[2]);

	void InitWork();

	int Getm_bconnected();//收plc连接状态
	void SetAlarm(int index);
public slots:
	bool ConnectPlc();
	void connectIN_AND_OUT(void*);
	void reportSocketError();
	void setStartWork(bool b);
	void setWinMini();
};