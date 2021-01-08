#include "QtPLCDialogClass.h"
#include "ui_QtPLCDialogClass.h"
#include <QPropertyAnimation>
#include <QFont>
#include <QBitmap>
#include <QPainter>

QtPLCDialogClass::QtPLCDialogClass(QDialog *parent)
	: QDialog(parent)
{
	ui = new Ui::QtPLCDialogClass();
	((Ui::QtPLCDialogClass*)ui)->setupUi(this);
	((Ui::QtPLCDialogClass*)ui)->frame->move(0, 0);
	initFont();

	m_data = new DataToPC_typ;
	memset(m_data, 0, sizeof(DataToPC_typ));//主界面用

	//指示灯部分
	((Ui::QtPLCDialogClass*)ui)->lb_00->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));
	lb_01 = new QLabel(((Ui::QtPLCDialogClass*)ui)->tabWidget->widget(0));
	lb_01->setPixmap(QPixmap(AppPath + "/ico/redGreen.png"));
	lb_01->move(321 + 9, 37 + 38);
	lb_01->setVisible(false);

	((Ui::QtPLCDialogClass*)ui)->lb_10->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));
	lb_11 = new QLabel(((Ui::QtPLCDialogClass*)ui)->tabWidget->widget(0));
	lb_11->setPixmap(QPixmap(AppPath + "/ico/redGreen.png"));
	lb_11->move(670 + 9, 37 + 38);
	lb_11->setVisible(false);

	QString LogInfo;
	LogInfo.sprintf("%p", QThread::currentThread());
	qDebug() << "PLC DLG" << "threadID : " << LogInfo;
}
QtPLCDialogClass::~QtPLCDialogClass()
{
	if (m_socket != nullptr)
	{
		//		m_socket->set_message_handler(nullptr, this);
	}
	//disconnect(this, SIGNAL(SHOWEVERYPLCVALUE(DataToPC_typ)), this, SLOT(getPLCData(DataToPC_typ)));
	bool b = disconnect(m_socket, SIGNAL(signal_FROMPLC(void*, int, int, int, int)), this, SLOT(getPLCData(void*, int, int, int, int)));

	if (cyclinderTimer != nullptr)
	{
		delete cyclinderTimer;
		cyclinderTimer = nullptr;
	}

	if (m_data != nullptr)
	{
		delete m_data;
		m_data = nullptr;
	}
}

#pragma region ui stylesheet
void QtPLCDialogClass::initFont()
{
	setupFont.setFamily(QString::fromLocal8Bit("迷你简菱心"));
	setupFont.setPointSize(36);
	startFont.setFamily(QString::fromLocal8Bit("迷你简菱心"));
	startFont.setPointSize(60);
}
void QtPLCDialogClass::setStyleCommand(QPushButton*btn, QString bg, QFont ft, QString tt)
{
	btn->setStyleSheet(bg);
	btn->setFont(ft);
	if (tt != "")
	{
		btn->setText(tt);
	}
}
#pragma endregion

#pragma region socket
void QtPLCDialogClass::onSendPLCCommand(bool b)
{
	obj = qobject_cast<QPushButton*>(sender());//判断是哪个按钮触发了槽函数
	obj->setFocus();
	QString objname = obj->objectName();//获取触发者objectname
	DataFromPC_typ typ;

	if (!objname.contains("pb_cmdTestKick"))
	{
		typ = getPCData();
	}
	typ.Telegram_typ = 1;//命令报文
	if (obj != nullptr)
	{

		if (b)
		{
			if (objname == "pB_enPhoto" || objname == "pB_enReject" || objname == "pB_enFeed" || objname == "pB_enRotate")
			{
				typ.Telegram_typ = 4;//运行报文
				//if (objname == "pB_enPhoto")
				//{
				//	typ.Run_Para.enPhoto = 1;
				//}
				//if (objname == "pB_enReject")
				//{
				//	typ.Run_Para.enReject = 1;
				//}
				//if (objname == "pB_enFeed")
				//{
				//	typ.Run_Para.enFeed = 1;
				//}
				//if (objname == "pB_enRotate")
				//{
				//	typ.Run_Para.enRotate = 1;
				//}
				//////////obj->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
				m_socket->Communicate_PLC(&typ, nullptr);//此处只发送，不接收
			}

			else {

				/*if (objname == "pb_cmdHome") typ.Machine_Cmd.cmdHome = 1;//结构体数据赋值
				if (objname == "pb_cmdStart") typ.Machine_Cmd.cmdStart = 1;
				if (objname == "pb_cmdStop") typ.Machine_Cmd.cmdStop = 1;
				if (objname == "pb_cmdEStop")
				{
					typ.Machine_Cmd.cmdEStop = 1;//非点动按钮,点动需要到最下面setChecked(false)
					obj->setText(QString::fromLocal8Bit("急停\n按下！"));
				}
				if (objname == "pb_cmdJog")
				{
					typ.Machine_Cmd.cmdJog = 1;
					obj->setText(QString::fromLocal8Bit("运行..."));
				}
				if (objname == "pb_cmdErrorAck") typ.Machine_Cmd.cmdErrorAck = 1;					//报警复位, 1:复位
				if (objname == "pb_cmdResetCounter") typ.Machine_Cmd.cmdResetCounter = 1;				//复位计数变量, 1:复位
				if (objname == "pb_cmdParaSave") typ.Machine_Cmd.cmdParaSave = 1;						//参数保存命令, 1:保存
				if (objname == "pb_cmdParaLoad") typ.Machine_Cmd.cmdParaLoad = 1;						//参数读取命令, 1:读取
				if (objname == "pb_cmdTestFlash0") typ.Machine_Cmd.cmdTestFlash[0] = 1;			//手动闪光, 1:闪光,自动复位
				if (objname == "pb_cmdTestFlash1") typ.Machine_Cmd.cmdTestFlash[1] = 1;
				if (objname == "pb_cmdTestFlash2") typ.Machine_Cmd.cmdTestFlash[2] = 1;

				if (objname == "pb_cmdTestValveUp") typ.Machine_Cmd.cmdTestValveUp = 1;						//手动升降气缸, 1:Push, 2:Back
				if (objname == "pb_cmdTestValveClip") typ.Machine_Cmd.cmdTestValveClip = 1;					//手动夹紧气缸, 1:Push, 2:Back
				if (objname == "pb_cmdTestValveDrop") typ.Machine_Cmd.cmdTestValveDrop = 1;					//手动落囊气缸, 1:Push, 2:Back
				if (objname == "pb_cmdTestInverter") typ.Machine_Cmd.cmdTestInverter = 1;				//手动胶囊料斗启动, 1:Start, 2:Stop
				if (objname == "pb_cmdTestLampRead") typ.Machine_Cmd.cmdTestLampRead = 1;				//手动红灯输出, 1:输出 , 2: 复位
				if (objname == "pb_cmdTestLampYellow") typ.Machine_Cmd.cmdTestLampYellow = 1;					//手动黄灯输出, 1:输出 , 2: 复位
				if (objname == "pb_cmdTestLampGreen") typ.Machine_Cmd.cmdTestLampGreen = 1;					//手动绿灯输出, 1:输出 , 2: 复位
				if (objname == "pb_cmdTestBuzzer") typ.Machine_Cmd.cmdTestBuzzer = 1;						//手动蜂鸣器输出, 1:输出 , 2: 复位
				if (objname == "pb_cmdTestPhoto") typ.Machine_Cmd.cmdTestPhoto = 1;						//手动拍照, 1:输出 , 2: 复位
				if (objname == "pb_cmdTestFlashPhoto") typ.Machine_Cmd.cmdTestFlashPhoto = 1;					//手动闪光加拍照, 1:启动
				if (objname == "pb_cmdTestCapPhoto") typ.Machine_Cmd.cmdTestCapPhoto = 1;				//手动胶囊拍照
				if (objname == "pb_cmdRotateCtl") typ.Machine_Cmd.cmdRotateCtl = 1;						//手动转囊启停

				/////////////////obj->setStyleSheet("background: rgb(0,255,0)");*/
			}
		}
		if (!b)
		{
			if (objname == "pB_enPhoto" || objname == "pB_enReject" || objname == "pB_enFeed" || objname == "pB_enRotate")
			{
				typ.Telegram_typ = 4;//运行报文
				/*if (objname == "pB_enPhoto")
				{
					typ.Run_Para.enPhoto = 0;
				}
				if (objname == "pB_enReject")
				{
					typ.Run_Para.enReject = 0;
				}
				if (objname == "pB_enFeed")
				{
					typ.Run_Para.enFeed = 0;
				}
				if (objname == "pB_enRotate")
				{
					typ.Run_Para.enRotate = 0;
				}*/
				obj->setStyleSheet("font-size:20pt");
				m_socket->Communicate_PLC(&typ, nullptr);//此处只发送，不接收
			}
			else {
				/*if (objname == "pb_cmdHome")typ.Machine_Cmd.cmdHome = 0;
				if (objname == "pb_cmdStart") typ.Machine_Cmd.cmdStart = 0;
				if (objname == "pb_cmdStop") typ.Machine_Cmd.cmdStop = 0;
				if (objname == "pb_cmdEStop")
				{
					typ.Machine_Cmd.cmdEStop = 0;//非点动按钮
					obj->setText(QString::fromLocal8Bit("急停"));
				}
				if (objname == "pb_cmdJog")
				{
					typ.Machine_Cmd.cmdJog = 0; //非点动按钮
					obj->setText(QString::fromLocal8Bit("点动"));
				}
				/*if (objname == "pb_cmdErrorAck") typ.Machine_Cmd.cmdErrorAck = 0;					//报警复位, 1:复位
				if (objname == "pb_cmdResetCounter") typ.Machine_Cmd.cmdResetCounter = 0;				//复位计数变量, 1:复位
				//if (objname == "pb_cmdParaSave") typ.Machine_Cmd.cmdParaSave = 0;						//参数保存命令, 1:保存
				//if (objname == "pb_cmdParaLoad") typ.Machine_Cmd.cmdParaLoad = 0;						//参数读取命令, 1:读取
				if (objname == "pb_cmdTestFlash0") typ.Machine_Cmd.cmdTestFlash[0] = 0;			//手动闪光, 1:闪光,自动复位
				if (objname == "pb_cmdTestFlash1") typ.Machine_Cmd.cmdTestFlash[1] = 0;
				if (objname == "pb_cmdTestFlash2") typ.Machine_Cmd.cmdTestFlash[2] = 0;

				if (objname == "pb_cmdTestValveUp") typ.Machine_Cmd.cmdTestValveUp = 2;						//手动升降气缸, 1:Push, 2:Back
				if (objname == "pb_cmdTestValveClip") typ.Machine_Cmd.cmdTestValveClip = 2;					//手动夹紧气缸, 1:Push, 2:Back
				if (objname == "pb_cmdTestValveDrop") typ.Machine_Cmd.cmdTestValveDrop = 2;					//手动落囊气缸, 1:Push, 2:Back
				if (objname == "pb_cmdTestInverter") typ.Machine_Cmd.cmdTestInverter = 2;				//手动胶囊料斗启动, 1:Start, 2:Stop
				if (objname == "pb_cmdTestLampRead") typ.Machine_Cmd.cmdTestLampRead = 2;				//手动红灯输出, 1:输出 , 2: 复位
				if (objname == "pb_cmdTestLampYellow") typ.Machine_Cmd.cmdTestLampYellow = 2;					//手动黄灯输出, 1:输出 , 2: 复位
				if (objname == "pb_cmdTestLampGreen") typ.Machine_Cmd.cmdTestLampGreen = 2;					//手动绿灯输出, 1:输出 , 2: 复位
				if (objname == "pb_cmdTestBuzzer") typ.Machine_Cmd.cmdTestBuzzer = 2;						//手动蜂鸣器输出, 1:输出 , 2: 复位
				if (objname == "pb_cmdTestPhoto") typ.Machine_Cmd.cmdTestPhoto = 2;						//手动拍照, 1:输出 , 2: 复位
				if (objname == "pb_cmdTestFlashPhoto") typ.Machine_Cmd.cmdTestFlashPhoto = 0;					//手动闪光加拍照, 1:启动
				if (objname == "pb_cmdTestCapPhoto") typ.Machine_Cmd.cmdTestCapPhoto = 0;				//手动胶囊拍照
				if (objname == "pb_cmdRotateCtl") typ.Machine_Cmd.cmdRotateCtl = 2;						//手动转囊启停
				obj->setStyleSheet("");*/
			}
		}
		if (objname != "pb_StWritePLC")//写入debug两次发送/旨在上面发送一次
		{
			m_socket->Communicate_PLC(&typ, nullptr);//此处只发送，不接收
		}//参数报文


		if (objname == "pb_StWritePLC" /*|| objname.contains("pb_cmdTestKick")*/ || objname == "pb_cmdHome" || objname == "pb_cmdStart"
			|| objname == "pb_cmdStop" || objname == "pb_cmdErrorAck"
			|| objname == "pb_cmdResetCounter" || objname == "pb_cmdParaSave" || objname == "pb_cmdParaLoad"
			//|| objname == "pb_cmdTestFlash0" || objname == "pb_cmdTestFlash1" || objname == "pb_cmdTestFlash2"
			//|| objname == "pb_cmdTestValveUp" || objname == "pb_cmdTestValveClip" || objname == "pb_cmdTestValveDrop"
			//|| objname == "pb_cmdTestInverter" || objname == "pb_cmdTestLampRead" || objname == "pb_cmdTestLampYellow"
			//|| objname == "pb_cmdTestLampGreen" || objname == "pb_cmdTestBuzzer"  || objname == "pb_cmdRotateCtl"
			|| objname == "pb_cmdTestPhoto" || objname == "pb_cmdTestFlashPhoto" || objname == "pb_cmdTestCapPhoto")
		{
			obj->setChecked(false);
		}
	}
}
void QtPLCDialogClass::SetSocket(QtSocket_Class *sc)
{
	m_socket = sc;
	bool b = connect(m_socket, SIGNAL(signal_FROMPLC(void*, int, int, int, int)), this, SLOT(getPLCData(void*, int, int, int, int)));

	//	m_socket->set_message_handler(&message_handler, this);//全局
}
#pragma endregion

#pragma region data
DataFromPC_typ QtPLCDialogClass::getPCData()
{
	DataFromPC_typ tmp;
	memset(&tmp, 0, sizeof(DataFromPC_typ));//将新char所指向的前size字节的内存单元用一个0替换，初始化内存。下同
	//tmp.Telegram_typ = ((Ui::QtPLCDialogClass*)ui)->lE_Telegram_typ->text().toInt();

	//Machine_Pare
	tmp.Machine_Para.enable = ((Ui::QtPLCDialogClass*)ui)->cB_enable->currentIndex();
	tmp.Machine_Para.s_trg_stop[0] = ((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop0->text().toFloat();
	tmp.Machine_Para.s_trg_stop[1] = ((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop1->text().toFloat();
	tmp.Machine_Para.FeedTimeOut = ((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->text().toFloat(); 
	tmp.Machine_Para.CapPickInterval = ((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->text().toFloat();
	tmp.Machine_Para.CapBackInterval = QString::number(((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->text().toFloat() * 100).toInt();
	tmp.Machine_Para.TireDelay = QString::number(((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->text().toFloat() * 100).toInt();
	tmp.Machine_Para.ReadDelay = QString::number(((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->text().toFloat() * 100).toInt();
	tmp.Machine_Para.TireWaitTime = QString::number(((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->text().toFloat() * 100).toInt();
	tmp.Machine_Para.StopSignalDelay = ((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->text().toInt();

	//运行数据
//	tmp.Run_Para.RunSpeed = ((Ui::QtPLCDialogClass*)ui)->lE_RunSpeed->text().toInt();
/////	tmp.Run_Para.SysPhase = ((Ui::QtPLCDialogClass*)ui)->lE_SysPhase->text().toInt();
//	tmp.Run_Para.enPhoto = ((Ui::QtPLCDialogClass*)ui)->pB_enPhoto->isChecked() ? 1 : 0;
//	tmp.Run_Para.enReject = ((Ui::QtPLCDialogClass*)ui)->pB_enReject->isChecked() ? 1 : 0;
//	tmp.Run_Para.enFeed = ((Ui::QtPLCDialogClass*)ui)->pB_enFeed->isChecked() ? 1 : 0;
//	tmp.Run_Para.enRotate = ((Ui::QtPLCDialogClass*)ui)->pB_enRotate->isChecked() ? 1 : 0;
//	tmp.Run_Para.CheckCount = m_data->ActData.CheckCount;
//	tmp.Run_Para.RejectCount = m_data->ActData.RejectCount;
//	tmp.Run_Para.ForceRejectCount = m_data->ActData.ForceRejectCount;

	//命令

	//tmp.Machine_Cmd.cmdParaSave = ((Ui::QtPLCDialogClass*)ui)->pb_cmdParaSave->isChecked() ? 1 : 0;						//参数保存命令, 1:保存
	//tmp.Machine_Cmd.cmdParaLoad = ((Ui::QtPLCDialogClass*)ui)->pb_cmdParaLoad->isChecked() ? 1 : 0;						//参数读取命令, 1:读取
/*	tmp.Machine_Cmd.Reject = ((Ui::QtPLCDialogClass*)ui)->pb_cmdReject->isChecked() ? 1 : 0;
	tmp.Machine_Cmd.ChannelSwith = ((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwith->isChecked() ? 1 : 0;
	tmp.Machine_Cmd.Vaccum = ((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccum->isChecked() ? 1 : 0;
	tmp.Machine_Cmd.CapGet = ((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGet->isChecked() ? 1 : 0;
	tmp.Machine_Cmd.CapGetValve = ((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValve->isChecked() ? 1 : 0;
	tmp.Machine_Cmd.CapBackValve = ((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValve->isChecked() ? 1 : 0;
	tmp.Machine_Cmd.AlarmOut = ((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOut->isChecked() ? 1 : 0;
	tmp.Machine_Cmd.StopSignal = ((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignal->isChecked() ? 1 : 0;
	tmp.Machine_Cmd.AlarmSignal = ((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignal->isChecked() ? 1 : 0;
	tmp.Machine_Cmd.YellowAlarmout = ((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmout->isChecked() ? 1 : 0;
	tmp.Machine_Cmd.Baffle = ((Ui::QtPLCDialogClass*)ui)->pb_cmdBaffle->isChecked() ? 1 : 0;	*/
	//照相处理结果和按钮在上面⬆⬆⬆⬆⬆⬆

	return tmp;
}//获取pc数据
void QtPLCDialogClass::getPLCData(void* data, int machinetype, int home, int kickOpen, int kickMode)
{
	memcpy(m_data, (DataToPC_typ*)data, sizeof(DataToPC_typ));//主界面用

	//报文类型
	//((Ui::QtPLCDialogClass*)ui)->lE_Telegram_typ->setText(QString::number(m_data->Telegram_typ));

	//运行数据
	//if (!((Ui::QtPLCDialogClass*)ui)->lE_RunSpeed->hasFocus())
	//{
	//	((Ui::QtPLCDialogClass*)ui)->lE_RunSpeed->setText(QString::number(m_data->ActData.RunSpeed));
	//}
///	((Ui::QtPLCDialogClass*)ui)->lE_SysPhase->setText(QString::number(m_data->ActData.SysPhase / 100.0, 'f', 2));
	/*if (m_data->ActData.enPhoto == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_enPhoto->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pB_enPhoto->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pB_enPhoto->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pB_enPhoto->blockSignals(false);

	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_enPhoto->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pB_enPhoto->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pB_enPhoto->setStyleSheet("font-size:20pt");

		((Ui::QtPLCDialogClass*)ui)->pB_enPhoto->blockSignals(false);
	}
	if (m_data->ActData.enReject == 1)

	{
		((Ui::QtPLCDialogClass*)ui)->pB_enReject->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pB_enReject->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pB_enReject->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pB_enReject->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_enReject->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pB_enReject->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pB_enReject->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pB_enReject->blockSignals(false);
	}

	if (m_data->ActData.enFeed == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_enFeed->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pB_enFeed->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pB_enFeed->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pB_enFeed->blockSignals(false);

	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_enFeed->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pB_enFeed->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pB_enFeed->setStyleSheet("font-size:20pt");

		((Ui::QtPLCDialogClass*)ui)->pB_enFeed->blockSignals(false);
	}
	if (m_data->ActData.enRotate == 1)

	{
		((Ui::QtPLCDialogClass*)ui)->pB_enRotate->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pB_enRotate->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pB_enRotate->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pB_enRotate->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_enRotate->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pB_enRotate->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pB_enRotate->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pB_enRotate->blockSignals(false);
	}

	//((Ui::QtPLCDialogClass*)ui)->lE_CheckCount->setText(QString::number(m_data->ActData.CheckCount));
	//((Ui::QtPLCDialogClass*)ui)->lE_RejectCount->setText(QString::number(m_data->ActData.RejectCount));
	//((Ui::QtPLCDialogClass*)ui)->lE_ForceRejectCount->setText(QString::number(m_data->ActData.ForceRejectCount));*/

	//系统状态
	((Ui::QtPLCDialogClass*)ui)->lE_AlarmStatus->setText(QString::number(m_data->Status.AlarmStatus));
	((Ui::QtPLCDialogClass*)ui)->lE_Alarm16->setText((char*)(m_data->Status.Alarm));
	//((Ui::QtPLCDialogClass*)ui)->lE_ServoErrorNum0->setText(QString::number(m_data->Status.ServoErrorNum[0]));
	//((Ui::QtPLCDialogClass*)ui)->lE_ServoErrorNum1->setText(QString::number(m_data->Status.ServoErrorNum[1]));
	//((Ui::QtPLCDialogClass*)ui)->lE_SysPhase_1->setText(QString::number(m_data->Status.SysPhase / 100.0, 'f', 2));
	//((Ui::QtPLCDialogClass*)ui)->lE_HomeOK->setText(QString::number(m_data->Status.HomeOK));

	//系统参数

	if (!((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->setText(QString::number(m_data->Machine_Para.CapBackInterval / 100.0, 'f', 2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->setText(QString::number(m_data->Machine_Para.TireWaitTime / 100.0, 'f', 2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->setText(QString::number(m_data->Machine_Para.TireDelay / 100.0, 'f', 2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->setText(QString::number(m_data->Machine_Para.ReadDelay / 100.0, 'f', 2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->setText(QString::number(m_data->Machine_Para.FeedTimeOut));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->setText(QString::number(m_data->Machine_Para.CapPickInterval));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->setText(QString::number(m_data->Machine_Para.StopSignalDelay));
	}

	//输入点
	lb_01->setVisible(m_data->Inputs.FeedTrigger ? true : false);
	((Ui::QtPLCDialogClass*)ui)->lb_00->setVisible(m_data->Inputs.FeedTrigger ? false : true);
	lb_11->setVisible(m_data->Inputs.SwingTrigger ? true : false);
	((Ui::QtPLCDialogClass*)ui)->lb_10->setVisible(m_data->Inputs.SwingTrigger ? false : true);
	//输出点
	//((Ui::QtPLCDialogClass*)ui)->lE_Inveter->setText(m_data->Outputs.Inveter ? "1" : "0");	
	if (m_data->Outputs.Reject)
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdReject->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdReject->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdReject->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdReject->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdReject->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdReject->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdReject->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdReject->blockSignals(false);
	}
	//((Ui::QtPLCDialogClass*)ui)->lE_ClipValve->setText(m_data->Outputs.ClipValve ? "1" : "0");
	if (m_data->Outputs.ChannelSwith)
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwith->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwith->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwith->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwith->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwith->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwith->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwith->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwith->blockSignals(false);
	}
	//((Ui::QtPLCDialogClass*)ui)->lE_UpValve->setText(m_data->Outputs.UpValve ? "1" : "0");
	if (m_data->Outputs.Vaccum)
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccum->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccum->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccum->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccum->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccum->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccum->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccum->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccum->blockSignals(false);
	}
	//((Ui::QtPLCDialogClass*)ui)->lE_DropValve->setText(m_data->Outputs.DropValve ? "1" : "0");
	if (m_data->Outputs.CapGet)
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGet->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGet->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGet->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGet->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGet->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGet->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGet->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGet->blockSignals(false);
	}
	//((Ui::QtPLCDialogClass*)ui)->lE_LampRed->setText(m_data->Outputs.LampRed ? "1" : "0");
	if (m_data->Outputs.CapGetValve)
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValve->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValve->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValve->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValve->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValve->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValve->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValve->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValve->blockSignals(false);
	}
	//((Ui::QtPLCDialogClass*)ui)->lE_LampYellow->setText(m_data->Outputs.LampYellow ? "1" : "0");
	if (m_data->Outputs.CapBackValve)
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValve->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValve->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValve->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValve->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValve->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValve->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValve->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValve->blockSignals(false);
	}
	//((Ui::QtPLCDialogClass*)ui)->lE_LampGreen->setText(m_data->Outputs.LampGreen ? "1" : "0");
	if (m_data->Outputs.AlarmOut)
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOut->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOut->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOut->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOut->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOut->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOut->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOut->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOut->blockSignals(false);
	}
	//((Ui::QtPLCDialogClass*)ui)->lE_Buzzer->setText(m_data->Outputs.Buzzer ? "1" : "0");
	if (m_data->Outputs.StopSignal)
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignal->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignal->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignal->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignal->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignal->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignal->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignal->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignal->blockSignals(false);
	}
	//((Ui::QtPLCDialogClass*)ui)->lE_Photo->setText(m_data->Outputs.Photo ? "1" : "0");
	if (m_data->Outputs.AlarmSignal)
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignal->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignal->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignal->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignal->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignal->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignal->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignal->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignal->blockSignals(false);
	}

	//((Ui::QtPLCDialogClass*)ui)->lE_Flash0->setText(m_data->Outputs.Flash[0] ? "1" : "0");
	if (m_data->Outputs.YellowAlarmout)
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmout->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmout->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmout->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmout->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmout->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmout->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmout->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmout->blockSignals(false);
	}
	//((Ui::QtPLCDialogClass*)ui)->lE_Flash1->setText(m_data->Outputs.Flash[1] ? "1" : "0");
	if (m_data->Outputs.Baffle)
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBaffle->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBaffle->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBaffle->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBaffle->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBaffle->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBaffle->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBaffle->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBaffle->blockSignals(false);
	}
}//PC显示数据
#pragma endregion

#pragma region popup window
int QtPLCDialogClass::showMsgBox(QMessageBox::Icon icon, const char* titleStr, const char* contentStr, const char* button1Str, const char* button2Str)//全是中文
{
	if (QString::fromLocal8Bit(button2Str) == "")
	{
		QMessageBox msg(QMessageBox::NoIcon, QString::fromLocal8Bit(titleStr), QString::fromLocal8Bit(contentStr), QMessageBox::Ok);
		msg.setWindowFlags(Qt::FramelessWindowHint);
		msg.setStyleSheet(
			"QPushButton {"
			"background-color:#f0f0f0;"
			"color:#00aa7f;"
			//" border-style: inherit;"
			//" border-width: 2px;"
			//" border-radius: 10px;"
			//" border-color: beige;"
			" font: bold 24px;"
			" min-width: 6em;"
			" min-height: 3em;"
			"}"
			"QLabel { min-width: 20em;min-height:3em;font:24px;background-color:#f0f0f0;}"
		);
		msg.setGeometry((768 - 523) / 2, 320, msg.width(), msg.height());
		//圆角👇
		QBitmap bmp(523, 185);
		bmp.fill();
		QPainter p(&bmp);
		p.setPen(Qt::NoPen);
		p.setBrush(Qt::black);
		p.drawRoundedRect(bmp.rect(), 5, 5);
		msg.setMask(bmp);

		msg.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit(button1Str));
		msg.setWindowIcon(QIcon(AppPath + "/ico/dr.ico"));
		return msg.exec();
	}
	else
	{
		QMessageBox msg(QMessageBox::NoIcon, QString::fromLocal8Bit(titleStr), QString::fromLocal8Bit(contentStr), QMessageBox::Yes | QMessageBox::No);
		msg.setWindowFlags(Qt::FramelessWindowHint);
		msg.setStyleSheet(
			"QPushButton {"
			"background-color:#f0f0f0;"
			"color:#00aa7f;"
			//" border-style: inherit;"
			//" border-width: 2px;"
			//" border-radius: 10px;"
			//" border-color: beige;"
			" font: bold 24px;"
			" min-width: 6em;"
			" min-height: 3em;"
			"}"
			"QLabel { min-width: 20em;min-height:3em;font:24px;background-color:#f0f0f0;}"
		);
		msg.setGeometry((768 - 523) / 2, 320, msg.width(), msg.height());
		//圆角👇
		QBitmap bmp(523, 185);
		bmp.fill();
		QPainter p(&bmp);
		p.setPen(Qt::NoPen);
		p.setBrush(Qt::black);
		p.drawRoundedRect(bmp.rect(), 5, 5);
		msg.setMask(bmp);

		msg.setButtonText(QMessageBox::Yes, QString::fromLocal8Bit(button1Str));
		msg.setButtonText(QMessageBox::No, QString::fromLocal8Bit(button2Str));
		msg.setWindowIcon(QIcon(AppPath + "/ico/dr.ico"));
		return msg.exec();
	}

	//  QMessageBox::NoIcon
	//	QMessageBox::Question
	//	QMessageBox::Information
	//	QMessageBox::Warning
	//	QMessageBox::Critical

}
#pragma endregion

#pragma region ui slots
void QtPLCDialogClass::on_pB_SetUp_toggled(bool checked)//设置
{
	if (checked)
	{
		((Ui::QtPLCDialogClass*)ui)->frame->setVisible(false);
		setStyleCommand(((Ui::QtPLCDialogClass*)ui)->pB_SetUp, "background: rgb(0,255,0)", setupFont, "");
		setStyleCommand(((Ui::QtPLCDialogClass*)ui)->pB_cmdStart, "", startFont, QString::fromLocal8Bit("启动"));
		((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->setEnabled(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->frame->setVisible(true);
		setStyleCommand(((Ui::QtPLCDialogClass*)ui)->pB_SetUp, "", setupFont, "");
		setStyleCommand(((Ui::QtPLCDialogClass*)ui)->pB_cmdStart, "background: rgb(200,200,100)", startFont, QString::fromLocal8Bit("启动"));
		((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->setEnabled(true);
	}
}
void QtPLCDialogClass::on_pB_cmdStart_toggled(bool checked)//启动 停止
{
	DataFromPC_typ typ;
	typ = getPCData();
	typ.Telegram_typ = 1;
	if (checked)
	{
		setStyleCommand(((Ui::QtPLCDialogClass*)ui)->pB_cmdStart, "background: rgb(0,255,0)", startFont, QString::fromLocal8Bit("停止"));
		((Ui::QtPLCDialogClass*)ui)->pB_SetUp->setEnabled(false);
		typ.Machine_Cmd.cmdStart = 1;
	}
	else
	{
		setStyleCommand(((Ui::QtPLCDialogClass*)ui)->pB_cmdStart, "background: rgb(200,200,100)", startFont, QString::fromLocal8Bit("启动"));
		((Ui::QtPLCDialogClass*)ui)->pB_SetUp->setEnabled(true);
		typ.Machine_Cmd.cmdStop = 1;
	}
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdCounterZero_clicked()
{
	DataFromPC_typ typ;
	typ = getPCData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdCounterZero = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAlarmReset_clicked()
{
	DataFromPC_typ typ;
	typ = getPCData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAlarmReset = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdCapClean_clicked()
{
	DataFromPC_typ typ;
	typ = getPCData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdCapClean = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}//cmdCapClean
#pragma endregion

