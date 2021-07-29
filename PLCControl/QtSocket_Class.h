#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QAbstractSocket>
#include "comm.h"
#include <QtSerialBus/QModbusTcpClient>
#include <QtSerialBus/QModbusReply>

class QtSocket_Class : public QObject
{
	Q_OBJECT
signals:
	void signal_Connected();
	void signal_FROMPLC(void*);
	void signal_FROMPLCHLODING(void*);
	void SHOWSTATUS(QString);
	void signal_SOCKETERROR();
	void statechange_Connected();
	void statechange_Connecting();
	void statechange_Unconnected();
	void statechange_Closing();
	void my_readC_finished();
	void my_readH_finished();
	void WRITECOILS();
	void WRITEHOLDINGREGISTERS();
public:
	QtSocket_Class(QObject *parent);
	~QtSocket_Class();

private:
	int m_iCircleFlag = 0;
	QTimer *timer_beat = nullptr;
#ifdef TCPIP
	QTcpSocket *mp_TCPSocket = nullptr;
#else
	QModbusClient *mp_TCPSocket = nullptr;
#endif
	int m_bconnected = 0;//是否连上PLC 1连上 2没有
	//for beat signal
	DataToPC_typ *_ToPC = new DataToPC_typ();
	DataFromPC_typ	*_FromPC = new DataFromPC_typ();
	char *_ctoPC = new char[sizeof(DataToPC_typ)];
	char *_cfromPC = new char[sizeof(DataFromPC_typ)]; 
	QString m_sip;//IP 10.86.50.210
	int m_iport;//port 5000

	int COILS = 120;
	int REGISTERS = 120;

	quint16 *Coils_Bufer = new quint16[COILS];//读取到的数据
	quint16 *Input_Bufer = new quint16[REGISTERS];//寄存器

	DataToPC_typ *m_Dmsg_ToPC; //PC接收
	DataFromPC_typ	*m_Dmsg_FromPC; //PC发送

	float m_fRejectTime;
public:
	bool slotStartWork(bool b);
	int Getm_bconnected();//是否连上PLC 1连上 2没有
	bool initialization(); //初始化


	bool disconnect(); //断开
	bool ResetError(); //错误复位
	//void set_message_handler(MESSAGE_HANDLER, void*); //消息头
	bool Communicate_PLC(DataFromPC_typ*, DataToPC_typ*);//PLC通信

	void programsetCloseEvent();

	bool StartWork(); //开始任务
	bool StopWork(); //停止
	//初始化任务
	bool syncData();
	bool AlarmReset();
	bool read_modbus_tcp_Coils(int start_add, quint16 numbers, int Server_ID);
	bool read_modbus_tcp_HoldingRegisters(int start_add, quint16 numbers, int Server_ID);
	bool Write_modbus_tcp_Coils(QString str1, int star_add, int number);
	bool Write_modbus_tcp_HoldingRegisters(QString str1, int star_add, int number);
public slots:
	void OnServer();
	bool connectServer(QString, int); //连接服务器
	void onConnectError(QAbstractSocket::SocketError);
	void onBeatSignal();
	void onReadAllData();
	void ReadReady_Coils();
	void onStateChanged();
	void ReadReady_HoldingRegisters();
	void onErrorOccurred();
};
