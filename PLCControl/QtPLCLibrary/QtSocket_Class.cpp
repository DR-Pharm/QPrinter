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

bool QtSocket_Class::slotCb_flash(bool b)
{
#ifndef INSPECTION_EDGE
	memset(m_Dmsg_FromPC, 0, sizeof(DataFromPC_typ));
	memset(m_Dmsg_ToPC, 0, sizeof(DataToPC_typ));
	m_Dmsg_FromPC->Telegram_typ = 1;

	if (b)
	{
		m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[0] = 1;
		m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[1] = 1;
		m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[2] = 1;
	}
	else
	{
		m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[0] = 0;
		m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[1] = 0;
		m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[2] = 0;
	}
	if (Communicate_PLC(m_Dmsg_FromPC, m_Dmsg_ToPC))
	{
		return true;
	}
#endif
	return false;
}

bool QtSocket_Class::slotRotateAndFlash(bool b)
{
#ifdef INSPECTION_360
	memset(m_Dmsg_FromPC, 0, sizeof(DataFromPC_typ));
	memset(m_Dmsg_ToPC, 0, sizeof(DataToPC_typ));
	m_Dmsg_FromPC->Telegram_typ = 1;
	if (b)
	{
		m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[0] = 1;
		m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[1] = 1;
		m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[2] = 1;
		m_Dmsg_FromPC->Machine_Cmd.cmdRotateCtl = 1;
	}
	else
	{
		m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[0] = 0;
		m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[1] = 0;
		m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[2] = 0;
		m_Dmsg_FromPC->Machine_Cmd.cmdRotateCtl = 2;
	}
	if (Communicate_PLC(m_Dmsg_FromPC, m_Dmsg_ToPC))
	{
		return true;
	}
#endif
	return false;
}
bool QtSocket_Class::slotFeed(bool b)
{
	return 1;
}
bool QtSocket_Class::slotStartWork(bool b)
{
#ifndef INSPECTION_EDGE
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
#endif
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
		timer_beat->start(100);
	}
	emit signal_Connected();
}

bool QtSocket_Class::connectServer(QString ip, int port)
{
	m_sip = ip;
	m_iport = port;
	if (mp_TCPSocket != nullptr)
	{
		bool b = connect(mp_TCPSocket, SIGNAL(connected()), this, SLOT(OnServer()));
		b = connect(mp_TCPSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onConnectError(QAbstractSocket::SocketError)));
		b = connect(mp_TCPSocket, SIGNAL(readyRead()), this, SLOT(onReadAllData()));
		mp_TCPSocket->connectToHost(m_sip, m_iport);
		b = mp_TCPSocket->waitForConnected(1000);
		if (!b)
		{
			emit signal_SOCKETERROR();
			mp_TCPSocket = nullptr;
		}
		return true;
	}
	return false;
}

bool QtSocket_Class::disconnect()
{
	return false;
}





bool QtSocket_Class::InitWork()
{
	memset(m_Dmsg_FromPC, 0, sizeof(DataFromPC_typ));
	memset(m_Dmsg_ToPC, 0, sizeof(DataToPC_typ));
	// 	if (Communicate_PLC(m_Dmsg_FromPC, m_Dmsg_ToPC))
	// 	{
	// 	}

	DataFromPC_typ typ;

	QString plcParamPath = qApp->applicationDirPath() + "/ModelFile/plc.txt";
	QFile f(plcParamPath);
	if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return false;
	}
	char* ch = new char[sizeof(DataFromPC_typ) + 1];
	memset(ch, 0, sizeof(DataFromPC_typ) + 1);
	//txtInput.readAll();
	f.read(ch, sizeof(DataFromPC_typ));

	memcpy(&typ, ch, sizeof(DataFromPC_typ));//赋值回来

	f.close();

	typ.Telegram_typ = 2;
	Communicate_PLC(&typ, nullptr);//系统

	typ.Telegram_typ = 4;
	if (Communicate_PLC(&typ, nullptr))//运行
	{
		return true;
	}
	return false;
}

bool QtSocket_Class::ResetError()
{
#ifndef INSPECTION_EDGE
	memset(m_Dmsg_FromPC, 0, sizeof(DataFromPC_typ));
	memset(m_Dmsg_ToPC, 0, sizeof(DataToPC_typ));
	m_Dmsg_FromPC->Telegram_typ = 1;
	m_Dmsg_FromPC->Machine_Cmd.cmdErrorAck = true;
	if (Communicate_PLC(m_Dmsg_FromPC, m_Dmsg_ToPC))
	{
		return true;
	}
#endif
	return false;
}


bool QtSocket_Class::SetResult(int counter, unsigned int alarm[2])
{
	memset(m_Dmsg_FromPC, 0, sizeof(DataFromPC_typ));
	memset(m_Dmsg_ToPC, 0, sizeof(DataToPC_typ));
	m_Dmsg_FromPC->Telegram_typ = 3;
#ifdef INSPECTION_1//时↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	m_Dmsg_FromPC->PhotoResult.Result[0] = alarm[0]; //0b00000101;
	//m_Dmsg_FromPC->PhotoResult.Result[1] = alarm[1]; //0b00001001;
	//m_Dmsg_FromPC->PhotoResult.Alarm[2] = alarm[2]; //0b00010001;
	//m_Dmsg_FromPC->PhotoResult.Alarm[3] = alarm[3]; //0b00100001;
	m_Dmsg_FromPC->PhotoResult.PhotoCnt[0] = counter;
#endif
	//phototimes!=0时↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
#ifdef INSPECTION_360
	m_Dmsg_FromPC->PhotoResult.Alarm[0] = alarm[0]; //0b00000101;
	m_Dmsg_FromPC->PhotoResult.Alarm[1] = alarm[1]; //0b00001001;
	m_Dmsg_FromPC->PhotoResult.Alarm[2] = alarm[2]; //0b00010001;
	m_Dmsg_FromPC->PhotoResult.Alarm[3] = alarm[3]; //0b00100001;
#endif
// 	for (int i=0;i<30;i++)
// 	{
// 		SET_BIT(msg_FromPC->PhotoResult.Alarm[i/8], i-i/8*8);
// 	}
	if (Communicate_PLC(m_Dmsg_FromPC, m_Dmsg_ToPC))
	{
		return true;
	}
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
#ifdef INSPECTION_360
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

bool QtSocket_Class::clean(bool b)
{
#ifdef INSPECTION_360	
	memset(m_Dmsg_FromPC, 0, sizeof(DataFromPC_typ));
	memcpy(m_Dmsg_ToPC, _ToPC, sizeof(DataToPC_typ));//主界面用
	m_Dmsg_FromPC->Telegram_typ = 2;
	//if (b)
	//{
	//	m_fRejectTime = _ToPC->Machine_Para.RejectTime;
	//}
	//m_Dmsg_FromPC->Machine_Para.FeedAxisHomeOffset = _ToPC->Machine_Para.FeedAxisHomeOffset;
	//m_Dmsg_FromPC->Machine_Para.ClipPhase1 = _ToPC->Machine_Para.ClipPhase1;
	//m_Dmsg_FromPC->Machine_Para.ClipPhase2 = _ToPC->Machine_Para.ClipPhase2;
	//m_Dmsg_FromPC->Machine_Para.UpPhase1 = _ToPC->Machine_Para.UpPhase1;
	//m_Dmsg_FromPC->Machine_Para.UpPhase2 = _ToPC->Machine_Para.UpPhase2;
	//m_Dmsg_FromPC->Machine_Para.DropPhase1 = _ToPC->Machine_Para.DropPhase1;
	//m_Dmsg_FromPC->Machine_Para.DropPhase2 = _ToPC->Machine_Para.DropPhase2;
	//m_Dmsg_FromPC->Machine_Para.tClip1 = _ToPC->Machine_Para.tClip1;
	//m_Dmsg_FromPC->Machine_Para.tClip2 = _ToPC->Machine_Para.tClip2;
	//m_Dmsg_FromPC->Machine_Para.tUp1 = _ToPC->Machine_Para.tUp1;
	//m_Dmsg_FromPC->Machine_Para.tUp2 = _ToPC->Machine_Para.tUp2;
	//m_Dmsg_FromPC->Machine_Para.tDrop1 = _ToPC->Machine_Para.tDrop1;
	//m_Dmsg_FromPC->Machine_Para.tDrop2 = _ToPC->Machine_Para.tDrop2;
	//m_Dmsg_FromPC->Machine_Para.FeedLength = _ToPC->Machine_Para.FeedLength;
	//m_Dmsg_FromPC->Machine_Para.FlashTime = _ToPC->Machine_Para.FlashTime;
	//m_Dmsg_FromPC->Machine_Para.PhotoTime = _ToPC->Machine_Para.PhotoTime;
	//m_Dmsg_FromPC->Machine_Para.RejectTime = _ToPC->Machine_Para.RejectTime;
	//m_Dmsg_FromPC->Machine_Para.PhotoDelay = _ToPC->Machine_Para.PhotoDelay;
	//m_Dmsg_FromPC->Machine_Para.PhotoPhase = _ToPC->Machine_Para.PhotoPhase;
	//m_Dmsg_FromPC->Machine_Para.RejectPhase = _ToPC->Machine_Para.RejectPhase;
	//m_Dmsg_FromPC->Machine_Para.PhotoTimes = _ToPC->Machine_Para.PhotoTimes;
	//m_Dmsg_FromPC->Machine_Para.RotateSpeed = _ToPC->Machine_Para.RotateSpeed;
	//m_Dmsg_FromPC->Machine_Para.DisableForceReject = _ToPC->Machine_Para.DisableForceReject;		//关闭强制剔废,1:关闭
	//m_Dmsg_FromPC->Machine_Para.CapCheckAlarmTime = _ToPC->Machine_Para.CapCheckAlarmTime;		//胶囊检测报警时间，单位ms
	//m_Dmsg_FromPC->Machine_Para.RejectFallingTime = _ToPC->Machine_Para.RejectFallingTime;		//剔废胶囊下落时间，单位ms
	//m_Dmsg_FromPC->Machine_Para.PhotoInterval = _ToPC->Machine_Para.PhotoInterval;

	//m_Dmsg_FromPC->Machine_Para.RejectTime = b ? 5000 : m_fRejectTime;
	Communicate_PLC(m_Dmsg_FromPC, m_Dmsg_ToPC);

	m_Dmsg_FromPC->Telegram_typ = 1;
	m_Dmsg_FromPC->Machine_Cmd.cmdRotateCtl = b ? 1 : 2;
	m_Dmsg_FromPC->Machine_Cmd.cmdTestValveUp = b ? 2 : 1;
	for (int i = 0; i < 30; i++)
	{
		m_Dmsg_FromPC->Machine_Cmd.cmdTestKick[i] = b;//结构体数据赋值
	}
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
	m_Dmsg_FromPC->Machine_Cmd.cmdErrorAck = 1;
	if (Communicate_PLC(m_Dmsg_FromPC, m_Dmsg_ToPC))
	{
		return true;
	}
#endif
	return false;
}
bool QtSocket_Class::CountReset()
{
#ifndef INSPECTION_EDGE
	memset(m_Dmsg_FromPC, 0, sizeof(DataFromPC_typ));
	memset(m_Dmsg_ToPC, 0, sizeof(DataToPC_typ));
	m_Dmsg_FromPC->Telegram_typ = 1;
	m_Dmsg_FromPC->Machine_Cmd.cmdResetCounter = 1;
#ifdef INSPECTION_1
	m_Dmsg_FromPC->Machine_Cmd.cmdPhotoCntZero = 1;
#endif
	if (Communicate_PLC(m_Dmsg_FromPC, m_Dmsg_ToPC))
	{
		return true;
	}
#endif
	return false;
}

bool QtSocket_Class::SetAlarm(int index)
{
	memset(m_Dmsg_FromPC, 0, sizeof(DataFromPC_typ));
	memset(m_Dmsg_ToPC, 0, sizeof(DataToPC_typ));
	m_Dmsg_FromPC->Telegram_typ = 1;

	if (0 == index)
	{
#ifdef INSPECTION_1
		m_Dmsg_FromPC->Machine_Cmd.cmdTestBuzzer = 0;
#endif
	}
	if (1 == index)
	{
#ifdef INSPECTION_1
		m_Dmsg_FromPC->Machine_Cmd.cmdTestBuzzer = 1;
#endif
	}
	if (2 == index)
	{
#ifdef INSPECTION_1
		m_Dmsg_FromPC->Machine_Cmd.cmdSetAlarm = 2;
#endif
	}
	if (Communicate_PLC(m_Dmsg_FromPC, m_Dmsg_ToPC))
	{
		return true;
	}
	return false;
}


bool QtSocket_Class::RunSpeed(int index, DataToPC_typ* data)//data no use 
{
	memset(m_Dmsg_FromPC, 0, sizeof(DataFromPC_typ));
	memcpy(m_Dmsg_ToPC, _ToPC, sizeof(DataToPC_typ));//主界面用
#ifdef INSPECTION_360
	m_Dmsg_FromPC->Telegram_typ = 4;
	//m_Dmsg_FromPC->Run_Para.RunSpeed = index;
	//m_Dmsg_FromPC->Run_Para.enFeed = _ToPC->ActData.enFeed;
	//m_Dmsg_FromPC->Run_Para.enPhoto = _ToPC->ActData.enPhoto;
	//m_Dmsg_FromPC->Run_Para.enReject = _ToPC->ActData.enReject;
	//m_Dmsg_FromPC->Run_Para.enRotate = _ToPC->ActData.enRotate;
#endif // INSPECTION_360

	if (Communicate_PLC(m_Dmsg_FromPC, m_Dmsg_ToPC))
	{
		return true;
	}
	return false;
}

bool QtSocket_Class::EnReject(DataToPC_typ* data)
{
#ifndef INSPECTION_EDGE
	memset(m_Dmsg_FromPC, 0, sizeof(DataFromPC_typ));
	memcpy(m_Dmsg_ToPC, &data, sizeof(DataToPC_typ));//主界面用

	m_Dmsg_FromPC->Telegram_typ = 4;
	//m_Dmsg_FromPC->Run_Para.enReject = 1;
	if (Communicate_PLC(m_Dmsg_FromPC, m_Dmsg_ToPC))
	{
		return true;
	}
#endif
	return false;
}

bool QtSocket_Class::GoHome()
{
	memset(m_Dmsg_FromPC, 0, sizeof(DataFromPC_typ));
	memset(m_Dmsg_ToPC, 0, sizeof(DataToPC_typ));

	m_Dmsg_FromPC->Telegram_typ = 1;
#ifdef INSPECTION_360
	m_Dmsg_FromPC->Machine_Cmd.cmdHome = 1;
#endif // INSPECTION_360
	if (Communicate_PLC(m_Dmsg_FromPC, m_Dmsg_ToPC))
	{
		return true;
	}
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

		if (mp_TCPSocket->write(_cfromPC, sizeof(DataFromPC_typ)))
		{
			// 			while (sizeof(DataToPC_typ) == mp_TCPSocket->read(_ctoPC, sizeof(DataToPC_typ)))
			// 				memcpy(_ToPC, _ctoPC, sizeof(DataToPC_typ));
		}

		memset(_ToPC, 0, sizeof(DataToPC_typ));
		memset(_ctoPC, 0, sizeof(DataToPC_typ));
	}
}

void QtSocket_Class::onReadAllData()
{
	mp_TCPSocket->read(_ctoPC, sizeof(DataToPC_typ));
	memcpy(_ToPC, _ctoPC, sizeof(DataToPC_typ));
	int MachineType=0;
	int home=0;
	int ContinueKickIsOpen = 0;
	int ContinueKickIsNormal = 0;
#ifdef INSPECTION_1
	MachineType = 1;
	home = 1;
	ContinueKickIsOpen = _ToPC->ActData.enReject;//0 不剔废 1 剔废
	ContinueKickIsNormal = _ToPC->ActData.TestRejectModel;//0 正常 1 间隔 2全部
#endif // INSPECTION_1
#ifdef INSPECTION_360
	MachineType = 360;
	home = _ToPC->Status.HomeOK;
#endif // INSPECTION_1
	emit signal_FROMPLC((void*)_ToPC, MachineType, home, ContinueKickIsOpen, ContinueKickIsNormal);

}
