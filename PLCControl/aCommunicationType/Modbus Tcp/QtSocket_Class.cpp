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
	char* m_Cmsg_ToPC = new char[sizeof(DataToPC_typ)];//ע������C��D������һ��char
	memset(m_Cmsg_ToPC, 0, sizeof(DataToPC_typ));//����char��ָ���ǰsize�ֽڵ��ڴ浥Ԫ��һ��0�滻����ʼ���ڴ档��ͬ
	char* msg_cfromPC = new char[sizeof(DataFromPC_typ)];
	memset(msg_cfromPC, 0, sizeof(DataFromPC_typ));
	memcpy(msg_cfromPC, m_Dmsg_FromPC, sizeof(DataFromPC_typ));//��m_Dmsg_FromPCֵ��ֵ/���Ǹ�msg_cfromPC
	if (nullptr == mp_TCPSocket)
	{
		return false;
	}
	int index = mp_TCPSocket->write(msg_cfromPC, sizeof(DataFromPC_typ));
	mp_TCPSocket->flush();
	if (0 < index)
	{
		//		int times = 0;
		// 		while (0 == mp_TCPSocket->read(m_Cmsg_ToPC, sizeof(DataToPC_typ)))//���յ�m_Cmsg_ToPC
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
		// 			memcpy(m_Dmsg_ToPC, m_Cmsg_ToPC, sizeof(DataToPC_typ));//�����յ�m_Cmsg_ToPC��ֵ��ֵ/���Ǹ�m_Dmsg_ToPC
		// 		}
		delete m_Cmsg_ToPC;
		delete msg_cfromPC;
		return true;
	}
	// 	if (0 < send(s_client, msg_cfromPC, sizeof(DataFromPC_typ), 0))//����msg_cfromPC����4������һ������
	// 	{//���send����copy���ݳɹ����ͷ���ʵ��copy���ֽ��������send��copy����ʱ���ִ�����ôsend�ͷ���SOCKET_ERROR ��-1��
	// 		int times = 0;
	// 		while (0 == recv(s_client, m_Cmsg_ToPC, sizeof(DataToPC_typ), 0))//���յ�m_Cmsg_ToPC
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
	// 			memcpy(m_Dmsg_ToPC, m_Cmsg_ToPC, sizeof(DataToPC_typ));//�����յ�m_Cmsg_ToPC��ֵ��ֵ/���Ǹ�m_Dmsg_ToPC
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

bool QtSocket_Class::initialization()//���ӳ�ʼ��
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

	m_bconnected = 1;//���ӳɹ�
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
	//����
#ifdef INSPECTION_1
//m_Dmsg_FromPC->Machine_Cmd.cmdHome = ((Ui::QtDialogClass*)ui)->pb_cmdHome->isChecked() ? 1 : 0;//Ѱ��,1:Ѱ������
	m_Dmsg_FromPC->Machine_Cmd.cmdStart = 0;							//����,1:��������
	m_Dmsg_FromPC->Machine_Cmd.cmdStop = 0;							//ֹͣ,ͣ��0��λ,1:ֹͣ
	m_Dmsg_FromPC->Machine_Cmd.cmdEStop = 0;							//����ֹͣ(����ֹͣ), 1:ֹͣ
//	m_Dmsg_FromPC->Machine_Cmd.cmdJog = ((Ui::QtDialogClass*)ui)->pb_cmdJog->isChecked() ? 1 : 0;							//�㶯����, 1,����,2,ֹͣ
	m_Dmsg_FromPC->Machine_Cmd.cmdErrorAck = 0;						//������λ, 1:��λ
	m_Dmsg_FromPC->Machine_Cmd.cmdResetCounter = 0;					//��λ��������, 1:��λ
	m_Dmsg_FromPC->Machine_Cmd.cmdParaSave = 0;// ((Ui::QtDialogClass*)ui)->pb_cmdParaSave->isChecked() ? 1 : 0;						//������������, 1:����
	m_Dmsg_FromPC->Machine_Cmd.cmdParaLoad = 0;// ((Ui::QtDialogClass*)ui)->pb_cmdParaLoad->isChecked() ? 1 : 0;						//������ȡ����, 1:��ȡ
	m_Dmsg_FromPC->Machine_Cmd.cmdTestKick = 2;		//�ֶ��޷�, 1:Push, 2:Back

	m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[0] = 0;			//�ֶ�����, 1:����,�Զ���λ
	m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[1] = 0;			//�ֶ�����, 1:����,�Զ���λ

	m_Dmsg_FromPC->Machine_Cmd.cmdTestLampRead = 2;					//�ֶ�������, 1:��� , 2: ��λ
	m_Dmsg_FromPC->Machine_Cmd.cmdTestLampYellow = 2;					//�ֶ��Ƶ����, 1:��� , 2: ��λ
	m_Dmsg_FromPC->Machine_Cmd.cmdTestLampGreen = 2;					//�ֶ��̵����, 1:��� , 2: ��λ
	m_Dmsg_FromPC->Machine_Cmd.cmdTestBuzzer = 2;						//�ֶ����������, 1:��� , 2: ��λ
//	m_Dmsg_FromPC->Machine_Cmd.cmdTestPhoto = ((Ui::QtDialogClass*)ui)->pb_cmdTestPhoto->isChecked() ? 1 : 2;						//�ֶ�����, 1:��� , 2: ��λ
	m_Dmsg_FromPC->Machine_Cmd.cmdTestFlashPhoto[0] = 0;					//�ֶ����������, 1:����
	m_Dmsg_FromPC->Machine_Cmd.cmdTestFlashPhoto[1] = 0;					//�ֶ����������, 1:����
	m_Dmsg_FromPC->Machine_Cmd.cmdFanCtl = 2;					//�ֶ���������
	m_Dmsg_FromPC->Machine_Cmd.cmdBandCtl = 2;						//�ֶ�ת����ͣ
	m_Dmsg_FromPC->Machine_Cmd.cmdSetAlarm = 0;								//�ֶ����������ţ��������㴥������Χ1-99
	m_Dmsg_FromPC->Machine_Cmd.cmdPhotoCntZero = 0;
#endif
#ifdef INSPECTION_361
	m_Dmsg_FromPC->Machine_Cmd.cmdHome = 0;							//Ѱ��,1:Ѱ������
	m_Dmsg_FromPC->Machine_Cmd.cmdStart = 0;							//����,1:��������
	m_Dmsg_FromPC->Machine_Cmd.cmdStop = 0;							//ֹͣ,ͣ��0��λ,1:ֹͣ
	m_Dmsg_FromPC->Machine_Cmd.cmdEStop = 0;							//����ֹͣ(����ֹͣ), 1:ֹͣ
	m_Dmsg_FromPC->Machine_Cmd.cmdJog = 0;							//�㶯����, 1,����,2,ֹͣ
	m_Dmsg_FromPC->Machine_Cmd.cmdErrorAck = 0;						//������λ, 1:��λ
	m_Dmsg_FromPC->Machine_Cmd.cmdResetCounter = 0;					//��λ��������, 1:��λ
	m_Dmsg_FromPC->Machine_Cmd.cmdParaSave = 0;// ((Ui::QtDialogClass*)ui)->pb_cmdParaSave->isChecked() ? 1 : 0;						//������������, 1:����
	m_Dmsg_FromPC->Machine_Cmd.cmdParaLoad = 0;// ((Ui::QtDialogClass*)ui)->pb_cmdParaLoad->isChecked() ? 1 : 0;						//������ȡ����, 1:��ȡ
	for (int i = 0; i < 30; i++)
	{
		m_Dmsg_FromPC->Machine_Cmd.cmdTestKick[i] = 2;		//�ֶ��޷�, 1:Push, 2:Back
	}

	m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[0] = 0;			//�ֶ�����, 1:����,�Զ���λ
	m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[1] = 0;			//�ֶ�����, 1:����,�Զ���λ
	m_Dmsg_FromPC->Machine_Cmd.cmdTestFlash[2] = 0;			//�ֶ�����, 1:����,�Զ���λ

	m_Dmsg_FromPC->Machine_Cmd.cmdTestValveUp = 1;						//�ֶ���������, 1:Push, 2:Back
	m_Dmsg_FromPC->Machine_Cmd.cmdTestValveClip = 2;					//�ֶ��н�����, 1:Push, 2:Back
	m_Dmsg_FromPC->Machine_Cmd.cmdTestValveDrop = 2;					//�ֶ���������, 1:Push, 2:Back
	m_Dmsg_FromPC->Machine_Cmd.cmdTestInverter = 2;					//�ֶ������϶�����, 1:Start, 2:Stop	m_Dmsg_FromPC->Machine_Cmd.cmdTestLampRead = 2;					//�ֶ�������, 1:��� , 2: ��λ

	m_Dmsg_FromPC->Machine_Cmd.cmdTestLampRead = 2;					//�ֶ�������, 1:��� , 2: ��λ
	m_Dmsg_FromPC->Machine_Cmd.cmdTestLampYellow = 2;					//�ֶ��Ƶ����, 1:��� , 2: ��λ
	m_Dmsg_FromPC->Machine_Cmd.cmdTestLampGreen = 2;					//�ֶ��̵����, 1:��� , 2: ��λ
	m_Dmsg_FromPC->Machine_Cmd.cmdTestBuzzer = 2;						//�ֶ����������, 1:��� , 2: ��λ
	m_Dmsg_FromPC->Machine_Cmd.cmdTestPhoto = 2;						//�ֶ�����, 1:��� , 2: ��λ
	m_Dmsg_FromPC->Machine_Cmd.cmdTestFlashPhoto = 0;					//�ֶ����������, 1:����
	m_Dmsg_FromPC->Machine_Cmd.cmdTestCapPhoto = 0;					//�ֶ���������
	m_Dmsg_FromPC->Machine_Cmd.cmdRotateCtl = 2;						//�ֶ�ת����ͣ
	m_Dmsg_FromPC->Machine_Cmd.cmdSetAlarm = 0;						//�ֶ����������ţ��������㴥������Χ1-99
#endif // INSPECTION_360
	Communicate_PLC(m_Dmsg_FromPC, m_Dmsg_ToPC);
}
/////NewUI_Demo����������������������������������������������
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

bool QtSocket_Class::syncData()//����ͬ������
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
		_FromPC->Telegram_typ = 0;////�������ͣ�0:��������,1:�����,2:��������,3:�������,100:Ӧ��
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
