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
	int m_bconnected = 0;//�Ƿ�����PLC 1���� 2û��
	//for beat signal
	DataToPC_typ *_ToPC = new DataToPC_typ();
	DataFromPC_typ	*_FromPC = new DataFromPC_typ();
	char *_ctoPC = new char[sizeof(DataToPC_typ)];
	char *_cfromPC = new char[sizeof(DataFromPC_typ)]; 
	QString m_sip;//IP 10.86.50.210
	int m_iport;//port 5000

	DataToPC_typ *m_Dmsg_ToPC; //PC����
	DataFromPC_typ	*m_Dmsg_FromPC; //PC����

	float m_fRejectTime;
public:

	bool slotCb_flash(bool);
	bool slotFeed(bool b);
	bool slotRotateAndFlash(bool b);
	bool slotStartWork(bool b);
	int Getm_bconnected();//�Ƿ�����PLC 1���� 2û��
	bool initialization(); //��ʼ��
	bool disconnect(); //�Ͽ�
	bool ResetError(); //����λ
	bool SetResult(int counter, unsigned int alarm[4]); //���
	//void set_message_handler(MESSAGE_HANDLER, void*); //��Ϣͷ
	bool Communicate_PLC(DataFromPC_typ*, DataToPC_typ*);//PLCͨ��

	void programsetCloseEvent();

	bool StartWork(); //��ʼ����
	bool StopWork(); //ֹͣ
	bool InitWork();
	bool clean(bool b);//clean axle & raise reject
	//��ʼ������
	bool syncData();
	bool AlarmReset();
	bool CountReset();
	bool SetAlarm(int index);
	bool RunSpeed(int, DataToPC_typ*);
	bool EnReject(DataToPC_typ*);
	bool GoHome();
public slots:
	void OnServer();
	bool connectServer(QString, int); //���ӷ�����
	void onConnectError(QAbstractSocket::SocketError);
	void onBeatSignal();
	void onReadAllData();
};
