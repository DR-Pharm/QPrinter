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

bool QtSocket_Class::initialization()//连接初始化
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
 * 函数名称：Connect_to_modbus(QString IP_address,int Port)
 * 功能：连接到modbus设备
 * 工作方式：
 * 参数：
        参数1：modbus设备的IP地址               QString 类型
        参数2：modbus设备的端口号(一般用502)     int 类型
 * 返回值：成功返回true，失败返回fasle。
*********************************************/
		mp_TCPSocket = new QModbusTcpClient();
		mp_TCPSocket->setConnectionParameter(QModbusDevice::NetworkPortParameter, 502);//端口
		mp_TCPSocket->setConnectionParameter(QModbusDevice::NetworkAddressParameter, "10.86.50.210");//IP ID？
		//mp_TCPSocket->setTimeout(2000);
		//mp_TCPSocket->setNumberOfRetries(3);//重试次数
		connect(mp_TCPSocket, &QModbusClient::stateChanged, this, &QtSocket_Class::onStateChanged);
		mp_TCPSocket->connectDevice();
#endif
	}
	return true;
}
void QtSocket_Class::onStateChanged()
{ //连接状态改变时的槽函数
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
 * 函数名称：read_modbus_tcp_Coils(int start_add,quint16 numbers ,int Server_ID)
 * 功能：发送读取modbus设备线圈数据请求
 * 工作方式：
 * 参数：
 *      参数1：int start_add           读取的起始地址
 *      参数2：quint16 numbers         读取的个数
 *      参数3：int Server_ID           Modbus的设备ID
 * 返回值：成功返回true，失败返回fasle。
 * 备注：
 * 修改记录:
*********************************************/
bool QtSocket_Class::read_modbus_tcp_Coils(int start_add, quint16 numbers, int Server_ID)
{
#ifdef MODBUSTCP
	if (!(mp_TCPSocket->state() == QModbusDevice::ConnectedState)) {//!后面的括号不能去掉，否则先！后==
		return false;
	}

	QModbusDataUnit ReadUnit(QModbusDataUnit::Coils, start_add, numbers);
	qDebug() << "配置ReadUnit完成";
	if (auto *reply = mp_TCPSocket->sendReadRequest(ReadUnit, Server_ID))     //1是Server_ID
	{
		if (!reply->isFinished())
		{
			qDebug() << "准备进行信号与槽连接";
			QObject::connect(reply, &QModbusReply::finished, this, &QtSocket_Class::ReadReady_Coils);
			qDebug() << "进入读取的槽函数 ";
			return true;
		}
		else
		{
			qDebug() << "提前delete reply";
			delete reply;
			return false;
		}

	}

	else {
		qDebug() << "提前退出";
		return false;
	}
#endif
	return true;
}
//处理请求
/********************************************
 * 函数名称：ReadReady_Coils()
 * 功能：接收到读取请求后执行的槽函数
 * 工作方式：
 * 参数：无参数
 * 返回值：没有返回值
读取离散变量时和读取线圈数据一样，唯一区别就是配置读取数据单元时换成
QModbusDataUnit ReadUnit(QModbusDataUnit::DiscreteInputs,start_add,numbers);

离散变量读取完成时发出自己的信号（自定义信号）。
*********************************************/
void QtSocket_Class::ReadReady_Coils()
{
#ifdef MODBUSTCP
	qDebug() << "开始执行槽函数";
	QModbusReply *reply = qobject_cast<QModbusReply *>(sender());
	if (!reply) {
		qDebug() << "提前退出";
		return;
	}
	if (reply->error() == QModbusDevice::NoError)
	{
		qDebug() << "接收数据";
		const QModbusDataUnit unit = reply->result();
		char Coils_Bufer[23];//23?
		for (uint16_t i = 0; i < unit.valueCount(); i++)
		{
			/*
			 QByteArray  AllData =unit.values();	//一次性读完
			*/

			uint16_t res = unit.value(i);			//一个一个读
			Coils_Bufer[i] = static_cast<uint8_t>(res);
			//读完将数据存储起来  Coils_Bufer[i] 自定的数组 用来存放数据

		}

	}
	else
	{
	}

	reply->deleteLater(); // delete the reply
	emit my_readC_finished();	//coils读取完成后emit 读取完成的信号；
#endif
}
/********************************************
 * 函数名称：read_modbus_tcp_HoldingRegisters(int start_add,quint16 numbers ,int Server_ID)
 * 功能：发送读取modbus设备HoldingRegisters数据请求
 * 工作方式：
 * 参数
 * 		参数1：读取数据的起始地址
 * 		参数2：读取多少个数据
 * 		参数3：SerVer ID号
 * 返回值：成功返回true，失败返回fasle。
 * 备注：
 *      QModbusDataUnit ReadUnit(QModbusDataUnit::HoldingRegisters,参数1,参数2);
 *      参数1：读取modbus设备的起始地址          int 类型
		参数2：读取几个modbus数据               quint16 类型
 * 修改记录:
*********************************************/
bool QtSocket_Class::read_modbus_tcp_HoldingRegisters(int start_add, quint16 numbers, int Server_ID)
{
#ifdef MODBUSTCP
	QModbusDataUnit ReadUnit(QModbusDataUnit::HoldingRegisters, start_add, numbers);

	if (auto *reply = mp_TCPSocket->sendReadRequest(ReadUnit, Server_ID))     //1是Server_ID
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
 * 函数名称：ReadReady_HoldingRegisters()
 * 功能：槽函数，发送请求成功后，接收数据将其存储在Hold_Bufer[]数组中
 * 工作方式：
 * 参数：无参数
 * 返回值：没有返回值
 * 备注：
输入寄存器类似，换掉配置单元的数据即可。
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
	emit my_readH_finished();		//自定义的信号
#endif
}
/********************************************
 * 函数名称： Write_modbus_tcp_Coils(QString str1,int star_add,int number)
 * 功   能： 将想要修改的数据写入到modbus设备某个（某些）地址的Coils中。
 * 工作方式：
 * 参   数：
 *          参数1：要写入的数据（例：1 0 1 0 1 0）   QString 类型
 *          参数2：写入数据的起始地址               int 类型
 *          参数3：写入数据的个数                   quint16
 * 返回值：没有返回值
 * 备注：一次性可以写入单个或者多个数据，取决于该函数执行时参数。
 * ！！！写数据时必须转化位16进制写入
*********************************************/
bool QtSocket_Class::Write_modbus_tcp_Coils(QString str1, int star_add, int number)
{
#ifdef MODBUSTCP
	quint16 number1 = static_cast<quint16>(number); //C++中的数据类型转换
	QModbusDataUnit writeUnit(QModbusDataUnit::Coils, star_add, number1);

	for (uint i1 = 0; i1 < writeUnit.valueCount(); i1++) {
		int j1 = 2 * i1;
		QString stt = str1.mid(j1, 1);
		bool ok;
		quint16 hex1 = stt.toInt(&ok, 16);//将textedit中读取到的数据转换为16进制发送
		writeUnit.setValue(i1, hex1);//设置发送数据
	}

	if (auto *reply = mp_TCPSocket->sendWriteRequest(writeUnit, 1)) {// ui->spinBox_SerAddress->value()是server address   sendWriteRequest是向服务器写数据
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
 * 函数名称： Write_modbus_tcp_HoldingRegisters(QString str1,int star_add,int number)
 * 功   能： 将想要修改的数据写入到modbus设备某个（某些）地址的HoldingRegisters中。
 * 工作方式：
 * 参   数：
 *          参数1：要写入的数据（例：FF A0 00等）   QString 类型
 *          参数2：写入数据的起始地址               int 类型
 *          参数3：写入数据的个数                   quint16
 * 返回值：没有返回值
 * 备注：一次性可以写入单个或者多个数据，取决于该函数执行时参数。
 * 修改记录
*********************************************/
bool QtSocket_Class::Write_modbus_tcp_HoldingRegisters(QString str1, int star_add, int number)
{
#ifdef MODBUSTCP
	qDebug() << "准备写holding数据：：";
	QByteArray str2 = QByteArray::fromHex(str1.toLatin1().data());//按十六进制编码接入文本
	QString str3 = str2.toHex().data();//以十六进制显示

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
		quint16 hex1 = static_cast<quint16>(stt.toInt(&ok, 16));//将textedit中读取到的数据转换为16进制发送
		writeUnit.setValue(static_cast<int>(i1), hex1);//设置发送数据
	}

	if (auto *reply = mp_TCPSocket->sendWriteRequest(writeUnit, 1)) {// ui->spinBox_SerAddress->value()是server address   sendWriteRequest是向服务器写数据
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
#ifdef TCPIP
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
