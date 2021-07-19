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
#ifdef TCPIP
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
#endif
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
#ifdef TCPIP
		mp_TCPSocket = new QTcpSocket(this);	

		bool b = connect(mp_TCPSocket, SIGNAL(connected()), this, SLOT(OnServer()));
			 b = connect(mp_TCPSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onConnectError(QAbstractSocket::SocketError)));
			b = connect(mp_TCPSocket, SIGNAL(readyRead()), this, SLOT(onReadAllData()));
#else
		/********************************************
 * �������ƣ�Connect_to_modbus(QString IP_address,int Port)
 * ���ܣ����ӵ�modbus�豸
 * ������ʽ��
 * ������
        ����1��modbus�豸��IP��ַ               QString ����
        ����2��modbus�豸�Ķ˿ں�(һ����502)     int ����
 * ����ֵ���ɹ�����true��ʧ�ܷ���fasle��
*********************************************/
		mp_TCPSocket = new QModbusTcpClient();
		mp_TCPSocket->setConnectionParameter(QModbusDevice::NetworkPortParameter, 502);//�˿�
		mp_TCPSocket->setConnectionParameter(QModbusDevice::NetworkAddressParameter, "10.86.50.210");//IP ID��
		//mp_TCPSocket->setTimeout(2000);
		//mp_TCPSocket->setNumberOfRetries(3);//���Դ���
		connect(mp_TCPSocket, &QModbusClient::stateChanged, this, &QtSocket_Class::onStateChanged);
		mp_TCPSocket->connectDevice();
#endif
	}
	return true;
}
void QtSocket_Class::onStateChanged()
{ //����״̬�ı�ʱ�Ĳۺ���
#ifdef MODBUSTCP
	if (mp_TCPSocket->state() == QModbusDevice::ConnectedState)
	{
		emit statechange_on();
	}

	else
	{
		emit statechange_off();
	}
#endif
}
/********************************************
 * �������ƣ�read_modbus_tcp_Coils(int start_add,quint16 numbers ,int Server_ID)
 * ���ܣ����Ͷ�ȡmodbus�豸��Ȧ��������
 * ������ʽ��
 * ������
 *      ����1��int start_add           ��ȡ����ʼ��ַ
 *      ����2��quint16 numbers         ��ȡ�ĸ���
 *      ����3��int Server_ID           Modbus���豸ID
 * ����ֵ���ɹ�����true��ʧ�ܷ���fasle��
 * ��ע��
 * �޸ļ�¼:
*********************************************/
bool QtSocket_Class::read_modbus_tcp_Coils(int start_add, quint16 numbers, int Server_ID)
{
#ifdef MODBUSTCP
	if (!(mp_TCPSocket->state() == QModbusDevice::ConnectedState)) {//!��������Ų���ȥ���������ȣ���==
		return false;
	}

	QModbusDataUnit ReadUnit(QModbusDataUnit::Coils, start_add, numbers);
	qDebug() << "����ReadUnit���";
	if (auto *reply = mp_TCPSocket->sendReadRequest(ReadUnit, Server_ID))     //1��Server_ID
	{
		if (!reply->isFinished())
		{
			qDebug() << "׼�������ź��������";
			QObject::connect(reply, &QModbusReply::finished, this, &QtSocket_Class::ReadReady_Coils);
			qDebug() << "�����ȡ�Ĳۺ��� ";
			return true;
		}
		else
		{
			qDebug() << "��ǰdelete reply";
			delete reply;
			return false;
		}

	}

	else {
		qDebug() << "��ǰ�˳�";
		return false;
	}
#endif
	return true;
}
//��������
/********************************************
 * �������ƣ�ReadReady_Coils()
 * ���ܣ����յ���ȡ�����ִ�еĲۺ���
 * ������ʽ��
 * �������޲���
 * ����ֵ��û�з���ֵ
��ȡ��ɢ����ʱ�Ͷ�ȡ��Ȧ����һ����Ψһ����������ö�ȡ���ݵ�Ԫʱ����
QModbusDataUnit ReadUnit(QModbusDataUnit::DiscreteInputs,start_add,numbers);

��ɢ������ȡ���ʱ�����Լ����źţ��Զ����źţ���
*********************************************/
void QtSocket_Class::ReadReady_Coils()
{
#ifdef MODBUSTCP
	qDebug() << "��ʼִ�вۺ���";
	QModbusReply *reply = qobject_cast<QModbusReply *>(sender());
	if (!reply) {
		qDebug() << "��ǰ�˳�";
		return;
	}
	if (reply->error() == QModbusDevice::NoError)
	{
		qDebug() << "��������";
		const QModbusDataUnit unit = reply->result();
		char Coils_Bufer[23];//23?
		for (uint16_t i = 0; i < unit.valueCount(); i++)
		{
			/*
			 QByteArray  AllData =unit.values();	//һ���Զ���
			*/

			uint16_t res = unit.value(i);			//һ��һ����
			Coils_Bufer[i] = static_cast<uint8_t>(res);
			//���꽫���ݴ洢����  Coils_Bufer[i] �Զ������� �����������

		}

	}
	else
	{
	}

	reply->deleteLater(); // delete the reply
	emit my_readC_finished();	//coils��ȡ��ɺ�emit ��ȡ��ɵ��źţ�
#endif
}
/********************************************
 * �������ƣ�read_modbus_tcp_HoldingRegisters(int start_add,quint16 numbers ,int Server_ID)
 * ���ܣ����Ͷ�ȡmodbus�豸HoldingRegisters��������
 * ������ʽ��
 * ����
 * 		����1����ȡ���ݵ���ʼ��ַ
 * 		����2����ȡ���ٸ�����
 * 		����3��SerVer ID��
 * ����ֵ���ɹ�����true��ʧ�ܷ���fasle��
 * ��ע��
 *      QModbusDataUnit ReadUnit(QModbusDataUnit::HoldingRegisters,����1,����2);
 *      ����1����ȡmodbus�豸����ʼ��ַ          int ����
		����2����ȡ����modbus����               quint16 ����
 * �޸ļ�¼:
*********************************************/
bool QtSocket_Class::read_modbus_tcp_HoldingRegisters(int start_add, quint16 numbers, int Server_ID)
{
#ifdef MODBUSTCP
	QModbusDataUnit ReadUnit(QModbusDataUnit::HoldingRegisters, start_add, numbers);

	if (auto *reply = mp_TCPSocket->sendReadRequest(ReadUnit, Server_ID))     //1��Server_ID
	{
		if (!reply->isFinished())
		{
			QObject::connect(reply, &QModbusReply::finished, this, &QtSocket_Class::ReadReady_HoldingRegisters);

		}
		else
		{
			delete reply;
		}

	}
#endif
	return true;
}
/********************************************
 * �������ƣ�ReadReady_HoldingRegisters()
 * ���ܣ��ۺ�������������ɹ��󣬽������ݽ���洢��Hold_Bufer[]������
 * ������ʽ��
 * �������޲���
 * ����ֵ��û�з���ֵ
 * ��ע��
����Ĵ������ƣ��������õ�Ԫ�����ݼ��ɡ�
*********************************************/
void QtSocket_Class::ReadReady_HoldingRegisters()
{
#ifdef MODBUSTCP
	QModbusReply *reply = qobject_cast<QModbusReply *>(sender());
	if (!reply) {
		return;
	}
	if (reply->error() == QModbusDevice::NoError)
	{
		const QModbusDataUnit unit = reply->result();
		char Input_Bufer[23];//23?
		for (uint16_t i = 0; i < unit.valueCount(); )
		{
			uint16_t res = unit.value(i);
			Input_Bufer[i] = static_cast<uint8_t>(res);
			i++;
		}

	}
	else
	{
	}

	reply->deleteLater(); // delete the reply
	emit my_readH_finished();		//�Զ�����ź�
#endif
}
/********************************************
 * �������ƣ� Write_modbus_tcp_Coils(QString str1,int star_add,int number)
 * ��   �ܣ� ����Ҫ�޸ĵ�����д�뵽modbus�豸ĳ����ĳЩ����ַ��Coils�С�
 * ������ʽ��
 * ��   ����
 *          ����1��Ҫд������ݣ�����1 0 1 0 1 0��   QString ����
 *          ����2��д�����ݵ���ʼ��ַ               int ����
 *          ����3��д�����ݵĸ���                   quint16
 * ����ֵ��û�з���ֵ
 * ��ע��һ���Կ���д�뵥�����߶�����ݣ�ȡ���ڸú���ִ��ʱ������
 * ������д����ʱ����ת��λ16����д��
*********************************************/
bool QtSocket_Class::Write_modbus_tcp_Coils(QString str1, int star_add, int number)
{
#ifdef MODBUSTCP
	quint16 number1 = static_cast<quint16>(number); //C++�е���������ת��
	QModbusDataUnit writeUnit(QModbusDataUnit::Coils, star_add, number1);

	for (uint i1 = 0; i1 < writeUnit.valueCount(); i1++) {
		int j1 = 2 * i1;
		QString stt = str1.mid(j1, 1);
		bool ok;
		quint16 hex1 = stt.toInt(&ok, 16);//��textedit�ж�ȡ��������ת��Ϊ16���Ʒ���
		writeUnit.setValue(i1, hex1);//���÷�������
	}

	if (auto *reply = mp_TCPSocket->sendWriteRequest(writeUnit, 1)) {// ui->spinBox_SerAddress->value()��server address   sendWriteRequest���������д����
		if (!reply->isFinished()) {   //reply Returns true when the reply has finished or was aborted.
			connect(reply, &QModbusReply::finished, this, [this, reply]() {
				if (reply->error() == QModbusDevice::ProtocolError) {
					qDebug() << (tr("Write response error: %1 (Mobus exception: 0x%2)")
						.arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16),
						5000);
				}
				else if (reply->error() != QModbusDevice::NoError) {
					qDebug() << (tr("Write response error: %1 (code: 0x%2)").
						arg(reply->errorString()).arg(reply->error(), -1, 16), 5000);
				}
				reply->deleteLater();
			});
		}
		else {
			// broadcast replies return immediately
			reply->deleteLater();
		}
	}
	else {
		qDebug() << (tr("Write error: ") + mp_TCPSocket->errorString(), 5000);
	}
#endif
	return true;
}
/********************************************
 * �������ƣ� Write_modbus_tcp_HoldingRegisters(QString str1,int star_add,int number)
 * ��   �ܣ� ����Ҫ�޸ĵ�����д�뵽modbus�豸ĳ����ĳЩ����ַ��HoldingRegisters�С�
 * ������ʽ��
 * ��   ����
 *          ����1��Ҫд������ݣ�����FF A0 00�ȣ�   QString ����
 *          ����2��д�����ݵ���ʼ��ַ               int ����
 *          ����3��д�����ݵĸ���                   quint16
 * ����ֵ��û�з���ֵ
 * ��ע��һ���Կ���д�뵥�����߶�����ݣ�ȡ���ڸú���ִ��ʱ������
 * �޸ļ�¼
*********************************************/
bool QtSocket_Class::Write_modbus_tcp_HoldingRegisters(QString str1, int star_add, int number)
{
#ifdef MODBUSTCP
	qDebug() << "׼��дholding���ݣ���";
	QByteArray str2 = QByteArray::fromHex(str1.toLatin1().data());//��ʮ�����Ʊ�������ı�
	QString str3 = str2.toHex().data();//��ʮ��������ʾ

	quint16 number1 = static_cast<quint16>(number);
	QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, star_add, number1);
	int j1 = 0;
	for (uint i1 = 0; i1 < writeUnit.valueCount(); i1++) {

		if (i1 == 0) {
			j1 = static_cast<int>(2 * i1);
		}
		else {
			j1 = j1 + 3;
		}
		QString stt = str1.mid(j1, 2);
		bool ok;
		quint16 hex1 = static_cast<quint16>(stt.toInt(&ok, 16));//��textedit�ж�ȡ��������ת��Ϊ16���Ʒ���
		writeUnit.setValue(static_cast<int>(i1), hex1);//���÷�������
	}

	if (auto *reply = mp_TCPSocket->sendWriteRequest(writeUnit, 1)) {// ui->spinBox_SerAddress->value()��server address   sendWriteRequest���������д����
		if (!reply->isFinished()) {   //reply Returns true when the reply has finished or was aborted.
			connect(reply, &QModbusReply::finished, this, [this, reply]() {
				if (reply->error() == QModbusDevice::ProtocolError) {
					qDebug() << (tr("Write response error: %1 (Mobus exception: 0x%2)")
						.arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16),
						5000);
				}
				else if (reply->error() != QModbusDevice::NoError) {
					qDebug() << (tr("Write response error: %1 (code: 0x%2)").
						arg(reply->errorString()).arg(reply->error(), -1, 16), 5000);
				}
				reply->deleteLater();
			});
		}
		else {
			// broadcast replies return immediately
			reply->deleteLater();
		}
	}
	else {
		qDebug() << (tr("Write error: ") + mp_TCPSocket->errorString(), 5000);
	}
#endif
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
#ifdef TCPIP
	m_sip = ip;
	m_iport = port;
	if (mp_TCPSocket != nullptr)
	{
		mp_TCPSocket->connectToHost(m_sip, m_iport);
		//bool b = mp_TCPSocket->waitForConnected(100);//1000 before
		bool b = mp_TCPSocket->waitForConnected(1000);//1000 before
		if (!b)
		{
			emit signal_SOCKETERROR();
			//mp_TCPSocket = nullptr;
		}
		return true;
	}
#endif
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
#ifdef TCPIP
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
#endif
}

void QtSocket_Class::onReadAllData()
{
#ifdef TCPIP
	mp_TCPSocket->read(_ctoPC, sizeof(DataToPC_typ));
	memcpy(_ToPC, _ctoPC, sizeof(DataToPC_typ));


	emit signal_FROMPLC((void*)_ToPC);
#endif
}
