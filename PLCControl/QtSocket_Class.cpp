#include "QtSocket_Class.h"
#include <QApplication>
#include <QFile>
#include <QThread>
#include "PLCRelayHead.h"

QtSocket_Class::QtSocket_Class(QObject *parent)
	: QObject(parent)
{
	m_Dmsg_FromPC = nullptr;
	m_Dmsg_FromPC = new DataFromPC_typ();
	memset(m_Dmsg_FromPC, 0, sizeof(DataFromPC_typ));
	m_Dmsg_ToPC = nullptr;
	m_Dmsg_ToPC = new DataToPC_typ();
	memset(m_Dmsg_ToPC, 0, sizeof(DataToPC_typ));

	m_iport = 0;
}



QtSocket_Class::~QtSocket_Class()
{
	if (nullptr != m_Dmsg_FromPC)
	{
		delete m_Dmsg_FromPC;
		m_Dmsg_FromPC = nullptr;
	}
	if (nullptr != m_Dmsg_ToPC)
	{
		delete m_Dmsg_ToPC;
		m_Dmsg_ToPC = nullptr;
	}
	if (nullptr != timer_beat)
	{
		timer_beat->stop();
		delete timer_beat;
		timer_beat = nullptr;
	}
}

bool QtSocket_Class::Communicate_PLC(DataFromPC_typ* m_Dmsg_FromPC, DataToPC_typ* m_Dmsg_ToPC)
{
	char* m_Cmsg_ToPC = new char[sizeof(DataToPC_typ)];//注意区分C和D，创建一新char
	memset(m_Cmsg_ToPC, 0, sizeof(DataToPC_typ));//将新char所指向的前size字节的内存单元用一个0替换，初始化内存。下同
	char* msg_cfromPC = new char[sizeof(DataFromPC_typ)];
	memset(msg_cfromPC, 0, sizeof(DataFromPC_typ));
	memcpy(msg_cfromPC, m_Dmsg_FromPC, sizeof(DataFromPC_typ));//将m_Dmsg_FromPC值赋值/覆盖给msg_cfromPC
	if (nullptr == mp_TCPSocket)
	{
		return false;
	}
	int index = mp_TCPSocket->write(msg_cfromPC, sizeof(DataFromPC_typ));
	mp_TCPSocket->flush();
	if (0 < index)
	{
		//		int times = 0;
		// 		while (0 == mp_TCPSocket->read(m_Cmsg_ToPC, sizeof(DataToPC_typ)))//接收到m_Cmsg_ToPC
		// 		{
		// 			times++;
		// 			if (times > 10)
		// 			{
		// 				break;
		// 			}
		// 			QThread::msleep(10);
		// 		}
		// 		if (m_Dmsg_ToPC != nullptr)
		// 		{
		// 			memcpy(m_Dmsg_ToPC, m_Cmsg_ToPC, sizeof(DataToPC_typ));//将接收到m_Cmsg_ToPC的值赋值/覆盖给m_Dmsg_ToPC
		// 		}
		delete m_Cmsg_ToPC;
		delete msg_cfromPC;
		return true;
	}
	// 	if (0 < send(s_client, msg_cfromPC, sizeof(DataFromPC_typ), 0))//发送msg_cfromPC，第4个参数一般置零
	// 	{//如果send函数copy数据成功，就返回实际copy的字节数，如果send在copy数据时出现错误，那么send就返回SOCKET_ERROR （-1）
	// 		int times = 0;
	// 		while (0 == recv(s_client, m_Cmsg_ToPC, sizeof(DataToPC_typ), 0))//接收到m_Cmsg_ToPC
	// 		{
	// 			times++;
	// 			if (times > 10)
	// 			{
	// 				break;
	// 			}
	// 			Sleep(10);
	// 		}
	// 		if (m_Dmsg_ToPC != nullptr)
	// 		{
	// 			memcpy(m_Dmsg_ToPC, m_Cmsg_ToPC, sizeof(DataToPC_typ));//将接收到m_Cmsg_ToPC的值赋值/覆盖给m_Dmsg_ToPC
	// 		}
	// 		delete m_Cmsg_ToPC;
	// 		delete msg_cfromPC;
	// 		return true;
	// 	}
	delete m_Cmsg_ToPC;
	delete msg_cfromPC;
	return false;
}

bool QtSocket_Class::slotStartWork(bool b)
{
	memset(m_Dmsg_FromPC, 0, sizeof(DataFromPC_typ));
	memset(m_Dmsg_ToPC, 0, sizeof(DataToPC_typ));
	m_Dmsg_FromPC->Telegram_typ = 1;
	if (b)
	{
		m_Dmsg_FromPC->Machine_Cmd.cmdStart = 1;
	}
	else
	{
		m_Dmsg_FromPC->Machine_Cmd.cmdStart = 0;
	}
	if (Communicate_PLC(m_Dmsg_FromPC, m_Dmsg_ToPC))
	{
		return true;
	}
	return false;
}
int QtSocket_Class::Getm_bconnected()
{
	return m_bconnected;
}

bool QtSocket_Class::initialization()//连接初始化
{
	if (nullptr == mp_TCPSocket)
	{
		mp_TCPSocket = new QTcpSocket(this);	

		bool b = connect(mp_TCPSocket, SIGNAL(connected()), this, SLOT(OnServer()));
			 b = connect(mp_TCPSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onConnectError(QAbstractSocket::SocketError)));
			b = connect(mp_TCPSocket, SIGNAL(readyRead()), this, SLOT(onReadAllData()));
	}
	return true;
}

void QtSocket_Class::OnServer()
{

	m_bconnected = 1;//连接成功
	if (nullptr == timer_beat)
	{
		timer_beat = new QTimer(this);
		connect(timer_beat, SIGNAL(timeout()), this, SLOT(onBeatSignal()));
		timer_beat->start(200);
	}
	emit signal_Connected();
}

bool QtSocket_Class::connectServer(QString ip, int port)
{
	m_sip = ip;
	m_iport = port;
	if (mp_TCPSocket != nullptr)
	{
		mp_TCPSocket->connectToHost(m_sip, m_iport);
		bool b = mp_TCPSocket->waitForConnected(100);//1000 before
		if (!b)
		{
			emit signal_SOCKETERROR();
			//mp_TCPSocket = nullptr;
		}
		return true;
	}
	return false;
}

bool QtSocket_Class::disconnect()
{
	return false;
}


bool QtSocket_Class::ResetError()
{
#ifndef INSPECTION_EDGE
	memset(m_Dmsg_FromPC, 0, sizeof(DataFromPC_typ));
	memset(m_Dmsg_ToPC, 0, sizeof(DataToPC_typ));
	m_Dmsg_FromPC->Telegram_typ = 1;
	//m_Dmsg_FromPC->Machine_Cmd.cmdErrorAck = true;
	if (Communicate_PLC(m_Dmsg_FromPC, m_Dmsg_ToPC))
	{
		return true;
	}
#endif
	return false;
}


void QtSocket_Class::programsetCloseEvent()
{
	memset(m_Dmsg_FromPC, 0, sizeof(DataFromPC_typ));
	memset(m_Dmsg_ToPC, 0, sizeof(DataToPC_typ));
	m_Dmsg_FromPC->Telegram_typ = 1;
	//命令
#ifdef INSPECTION_1
//m_Dmsg_FromPC->Machine_Cmd.cmdHome = ((Ui::QtDialogClass*)ui)->pb_cmdHome->isChecked() ? 1 : 0;//寻参,1:寻参启动
	m_Dmsg_FromPC->Machine_Cmd.cmdStart = 0;							//启动,1:启动运行
	m_Dmsg_FromPC->Machine_Cmd.cmdStop = 0;							//停止,停在0相位,1:停止
	m_Dmsg_FromPC->Machine_Cmd.cmdEStop = 0;							//紧急停止(立即停止), 1:停止
//	m_Dmsg_FromPC->Machine_Cmd.cmdJog = ((Ui::QtDialogClass*)ui)->pb_cmdJog->isChecked() ? 1 : 0;							//点动运行, 1,启动,2,停止
	m_Dmsg_FromPC->Machine_Cmd.cmdErrorAck = 0;						//报警复位, 1:复位
	m_Dmsg_FromPC->Machine_Cmd.cmdResetCounter = 0;					//复位计数变量, 1:复位
	m_Dmsg_FromPC->Machine_Cmd.cmdParaSave = 0;// ((Ui::QtDialogClass*)ui)->pb_cmdParaSave->isChecked() ? 1 : 0;						//参数保存命令, 1:保存
	m_Dmsg_FromPC->Machine_Cmd.cmdParaLoad = 0;// ((Ui::QtDialogClass*)ui)->pb_cmdParaLoad->isChecked() ? 1 : 0;						//参数读取命令, 1:读取
	m_Dmsg_FromPC->Machine_Cmd.cmdTestKick = 2;		//手动剔废, 1:Push, 2:Back

	m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[0] = 0;			//手动闪光, 1:闪光,自动复位
	m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[1] = 0;			//手动闪光, 1:闪光,自动复位

	m_Dmsg_FromPC->Machine_Cmd.cmdTestLampRead = 2;					//手动红灯输出, 1:输出 , 2: 复位
	m_Dmsg_FromPC->Machine_Cmd.cmdTestLampYellow = 2;					//手动黄灯输出, 1:输出 , 2: 复位
	m_Dmsg_FromPC->Machine_Cmd.cmdTestLampGreen = 2;					//手动绿灯输出, 1:输出 , 2: 复位
	m_Dmsg_FromPC->Machine_Cmd.cmdTestBuzzer = 2;						//手动蜂鸣器输出, 1:输出 , 2: 复位
//	m_Dmsg_FromPC->Machine_Cmd.cmdTestPhoto = ((Ui::QtDialogClass*)ui)->pb_cmdTestPhoto->isChecked() ? 1 : 2;						//手动拍照, 1:输出 , 2: 复位
	m_Dmsg_FromPC->Machine_Cmd.cmdTestFlashPhoto[0] = 0;					//手动闪光加拍照, 1:启动
	m_Dmsg_FromPC->Machine_Cmd.cmdTestFlashPhoto[1] = 0;					//手动闪光加拍照, 1:启动
	m_Dmsg_FromPC->Machine_Cmd.cmdFanCtl = 2;					//手动胶囊拍照
	m_Dmsg_FromPC->Machine_Cmd.cmdBandCtl = 2;						//手动转囊启停
	m_Dmsg_FromPC->Machine_Cmd.cmdSetAlarm = 0;								//手动触发报警号，不等于零触发。范围1-99
	m_Dmsg_FromPC->Machine_Cmd.cmdPhotoCntZero = 0;
#endif
#ifdef INSPECTION_361
	m_Dmsg_FromPC->Machine_Cmd.cmdHome = 0;							//寻参,1:寻参启动
	m_Dmsg_FromPC->Machine_Cmd.cmdStart = 0;							//启动,1:启动运行
	m_Dmsg_FromPC->Machine_Cmd.cmdStop = 0;							//停止,停在0相位,1:停止
	m_Dmsg_FromPC->Machine_Cmd.cmdEStop = 0;							//紧急停止(立即停止), 1:停止
	m_Dmsg_FromPC->Machine_Cmd.cmdJog = 0;							//点动运行, 1,启动,2,停止
	m_Dmsg_FromPC->Machine_Cmd.cmdErrorAck = 0;						//报警复位, 1:复位
	m_Dmsg_FromPC->Machine_Cmd.cmdResetCounter = 0;					//复位计数变量, 1:复位
	m_Dmsg_FromPC->Machine_Cmd.cmdParaSave = 0;// ((Ui::QtDialogClass*)ui)->pb_cmdParaSave->isChecked() ? 1 : 0;						//参数保存命令, 1:保存
	m_Dmsg_FromPC->Machine_Cmd.cmdParaLoad = 0;// ((Ui::QtDialogClass*)ui)->pb_cmdParaLoad->isChecked() ? 1 : 0;						//参数读取命令, 1:读取
	for (int i = 0; i < 30; i++)
	{
		m_Dmsg_FromPC->Machine_Cmd.cmdTestKick[i] = 2;		//手动剔废, 1:Push, 2:Back
	}

	m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[0] = 0;			//手动闪光, 1:闪光,自动复位
	m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[1] = 0;			//手动闪光, 1:闪光,自动复位
	m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[2] = 0;			//手动闪光, 1:闪光,自动复位

	m_Dmsg_FromPC->Machine_Cmd.cmdTestValveUp = 1;						//手动升降气缸, 1:Push, 2:Back
	m_Dmsg_FromPC->Machine_Cmd.cmdTestValveClip = 2;					//手动夹紧气缸, 1:Push, 2:Back
	m_Dmsg_FromPC->Machine_Cmd.cmdTestValveDrop = 2;					//手动落囊气缸, 1:Push, 2:Back
	m_Dmsg_FromPC->Machine_Cmd.cmdTestInverter = 2;					//手动胶囊料斗启动, 1:Start, 2:Stop	m_Dmsg_FromPC->Machine_Cmd.cmdTestLampRead = 2;					//手动红灯输出, 1:输出 , 2: 复位

	m_Dmsg_FromPC->Machine_Cmd.cmdTestLampRead = 2;					//手动红灯输出, 1:输出 , 2: 复位
	m_Dmsg_FromPC->Machine_Cmd.cmdTestLampYellow = 2;					//手动黄灯输出, 1:输出 , 2: 复位
	m_Dmsg_FromPC->Machine_Cmd.cmdTestLampGreen = 2;					//手动绿灯输出, 1:输出 , 2: 复位
	m_Dmsg_FromPC->Machine_Cmd.cmdTestBuzzer = 2;						//手动蜂鸣器输出, 1:输出 , 2: 复位
	m_Dmsg_FromPC->Machine_Cmd.cmdTestPhoto = 2;						//手动拍照, 1:输出 , 2: 复位
	m_Dmsg_FromPC->Machine_Cmd.cmdTestFlashPhoto = 0;					//手动闪光加拍照, 1:启动
	m_Dmsg_FromPC->Machine_Cmd.cmdTestCapPhoto = 0;					//手动胶囊拍照
	m_Dmsg_FromPC->Machine_Cmd.cmdRotateCtl = 2;						//手动转囊启停
	m_Dmsg_FromPC->Machine_Cmd.cmdSetAlarm = 0;						//手动触发报警号，不等于零触发。范围1-99
#endif // INSPECTION_360
	Communicate_PLC(m_Dmsg_FromPC, m_Dmsg_ToPC);
}
/////NewUI_Demo↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
bool QtSocket_Class::StartWork()
{
#ifndef INSPECTION_EDGE
	memset(m_Dmsg_FromPC, 0, sizeof(DataFromPC_typ));
	memset(m_Dmsg_ToPC, 0, sizeof(DataToPC_typ));
	m_Dmsg_FromPC->Telegram_typ = 1;
	m_Dmsg_FromPC->Machine_Cmd.cmdStart = 1;
	if (Communicate_PLC(m_Dmsg_FromPC, m_Dmsg_ToPC))
	{
		return true;
	}
#endif
	return false;
}

bool QtSocket_Class::StopWork()
{
#ifndef INSPECTION_EDGE
	memset(m_Dmsg_FromPC, 0, sizeof(DataFromPC_typ));
	memset(m_Dmsg_ToPC, 0, sizeof(DataToPC_typ));
	m_Dmsg_FromPC->Telegram_typ = 1;
	m_Dmsg_FromPC->Machine_Cmd.cmdStop = 1;
	if (Communicate_PLC(m_Dmsg_FromPC, m_Dmsg_ToPC))
	{
		return true;
	}
#endif
	return false;
}

bool QtSocket_Class::syncData()//单面同步计数
{
#ifdef INSPECTION_1
	memset(m_Dmsg_FromPC, 0, sizeof(DataFromPC_typ));
	memset(m_Dmsg_ToPC, 0, sizeof(DataToPC_typ));
	m_Dmsg_FromPC->Telegram_typ = 1;
	m_Dmsg_FromPC->Machine_Cmd.cmdPhotoCntZero = TRUE;
	if (Communicate_PLC(m_Dmsg_FromPC, m_Dmsg_ToPC))
	{
		return true;
}
#endif // INSPECTION_1
	return false;
}

bool QtSocket_Class::AlarmReset()
{
#ifndef INSPECTION_EDGE
	memset(m_Dmsg_FromPC, 0, sizeof(DataFromPC_typ));
	memset(m_Dmsg_ToPC, 0, sizeof(DataToPC_typ));
	m_Dmsg_FromPC->Telegram_typ = 1;
	//m_Dmsg_FromPC->Machine_Cmd.cmdErrorAck = 1;
	if (Communicate_PLC(m_Dmsg_FromPC, m_Dmsg_ToPC))
	{
		return true;
	}
#endif
	return false;
}

void QtSocket_Class::onConnectError(QAbstractSocket::SocketError err)
{

}
void QtSocket_Class::onBeatSignal()
{
	memset(_ctoPC, 0, sizeof(DataToPC_typ));
	memset(_ToPC, 0, sizeof(DataToPC_typ));
	memset(_cfromPC, 0, sizeof(DataFromPC_typ));
	memset(_FromPC, 0, sizeof(DataFromPC_typ));
	int n = sizeof(DataToPC_typ);
	{
		_FromPC->Telegram_typ = 0;////报文类型，0:心跳报文,1:命令报文,2:参数报文,3:结果报文,100:应答
		memcpy(_cfromPC, _FromPC, sizeof(DataFromPC_typ));

		// 		_ToPC->Telegram_typ = 100;
		// 		_ToPC->Status.HomeOK = 1;
		// 		memcpy(_ctoPC, _ToPC, sizeof(DataFromPC_typ));

		if (mp_TCPSocket!=nullptr)
		{
		if (mp_TCPSocket->write(_cfromPC, sizeof(DataFromPC_typ)))
		{
			// 			while (sizeof(DataToPC_typ) == mp_TCPSocket->read(_ctoPC, sizeof(DataToPC_typ)))
			// 				memcpy(_ToPC, _ctoPC, sizeof(DataToPC_typ));
		}

		}
		memset(_ToPC, 0, sizeof(DataToPC_typ));
		memset(_ctoPC, 0, sizeof(DataToPC_typ));
	}
}

void QtSocket_Class::onReadAllData()
{
	mp_TCPSocket->read(_ctoPC, sizeof(DataToPC_typ));
	memcpy(_ToPC, _ctoPC, sizeof(DataToPC_typ));


	emit signal_FROMPLC((void*)_ToPC);

}
