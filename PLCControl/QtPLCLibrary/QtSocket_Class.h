#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QAbstractSocket>
#include "comm.h"

class QtSocket_Class : public QObject
{
	Q_OBJECT
signals:
	void signal_Connected();
	void signal_FROMPLC(void*,int,int,int,int);
	void signal_SOCKETERROR();
public:
	QtSocket_Class(QObject *parent);
	~QtSocket_Class();

private:
	QTimer *timer_beat = nullptr;
	QTcpSocket *mp_TCPSocket = nullptr;
	int m_bconnected = 0;//是否连上PLC 1连上 2没有
	//for beat signal
	DataToPC_typ *_ToPC = new DataToPC_typ();
	DataFromPC_typ	*_FromPC = new DataFromPC_typ();
	char *_ctoPC = new char[sizeof(DataToPC_typ)];
	char *_cfromPC = new char[sizeof(DataFromPC_typ)]; 
	QString m_sip;//IP 10.86.50.210
	int m_iport;//port 5000

	DataToPC_typ *m_Dmsg_ToPC; //PC接收
	DataFromPC_typ	*m_Dmsg_FromPC; //PC发送

	float m_fRejectTime;
public:

	bool slotCb_flash(bool);
	bool slotFeed(bool b);
	bool slotRotateAndFlash(bool b);
	bool slotStartWork(bool b);
	int Getm_bconnected();//是否连上PLC 1连上 2没有
	bool initialization(); //初始化
	bool disconnect(); //断开
	bool ResetError(); //错误复位
	bool SetResult(int counter, unsigned int alarm[4]); //结果
	//void set_message_handler(MESSAGE_HANDLER, void*); //消息头
	bool Communicate_PLC(DataFromPC_typ*, DataToPC_typ*);//PLC通信

	void programsetCloseEvent();

	bool StartWork(); //开始任务
	bool StopWork(); //停止
	bool InitWork();
	bool clean(bool b);//clean axle & raise reject
	//初始化任务
	bool syncData();
	bool AlarmReset();
	bool CountReset();
	bool SetAlarm(int index);
	bool RunSpeed(int, DataToPC_typ*);
	bool EnReject(DataToPC_typ*);
	bool GoHome();
public slots:
	void OnServer();
	bool connectServer(QString, int); //连接服务器
	void onConnectError(QAbstractSocket::SocketError);
	void onBeatSignal();
	void onReadAllData();
};
