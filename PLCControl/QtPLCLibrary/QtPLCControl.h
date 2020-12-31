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
	void FROMPLC(void*, int, int, int, int);
	void SOCKETERROR();
	void STARTCONNECT(QString, int);
private:
	void *m_socket = nullptr;
	QString AppPath = qApp->applicationDirPath(); 
	void *dlg = nullptr;
public:
	QtPLCControl();
	void* QtCreateDialog(int);
	void ProgramSetCloseEvent();
	void clean(bool);//clean axle & raise reject
	void syncData();
	void AlarmReset();
	void CountReset();
	void RunSpeed(int, void*);
	void EnReject(void*);
	void GoHome();
	//����ͬ������
	void QtDestroyDlg();
//	void SetCallBack(MESSAGE_HANDLER,void*);
	void SendPlcCommand(void *, void*);
	void StartWork();
	void StopWork();
	bool SetResult(int counter, unsigned int alarm[2]);

	void InitWork();

	int Getm_bconnected();//��plc����״̬
	void SetAlarm(int index);
public slots:
	bool ConnectPlc();
	void connectIN_AND_OUT(void*, int, int, int, int);
	void reportSocketError();
	void setCb_flash(bool);
	void setRotateAndFlash(bool b);
	void setFeed(bool b);
	void setStartWork(bool b);
};