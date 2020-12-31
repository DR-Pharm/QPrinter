#include "QtPLCDialogClass.h"
#include "ui_QtPLCDialogClass.h"

#include <QPropertyAnimation>
#include <QFont>
#include <QBitmap>
#include <QPainter>

std::shared_ptr<spd::logger> SYS_logger;
std::shared_ptr<spd::logger> OPS_logger;//操作
//extern Socket_CPP* m_socket;
QString g_ipAddress;
int g_port;

void message_handler(void* context, DataToPC_typ data)
{
	((QtPLCDialogClass*)context)->emit SHOWEVERYPLCVALUE(data);
}

QtPLCDialogClass::QtPLCDialogClass(QDialog *parent)
	: QDialog(parent)
{
	ui = new Ui::QtPLCDialogClass();
	((Ui::QtPLCDialogClass*)ui)->setupUi(this);

	for (int i = 0; i < 31; i++)//增加一个全部
	{
		QString objname = "pb_cmdTestKick";
		objname = objname + QString::number(i);
		QPushButton* btn = findChild<QPushButton*>(objname); //返回this中一个名为objname的QPushButton孩子，即使按钮不是父亲的直接孩子：30个剔废按钮
		if (btn != nullptr)
		{
			connect(btn, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));//30个剔废按钮checked
			connect(btn, SIGNAL(toggled(bool)), this, SLOT(onDebugMode(bool)));//30个剔废按钮checked
		}

	}

	cyclinderTimer = new QTimer;
	connect(cyclinderTimer, &QTimer::timeout, this, &QtPLCDialogClass::updateCyclinderSituation);
	//connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdHome, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));
	//connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdStart, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));
	//connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdStop, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));
	//connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdEStop, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));
	connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdJog, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));
	//	connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdErrorAck, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));						//报警复位, 1:复位
	//	connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdResetCounter, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));					//复位计数变量, 1:复位
		//connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdParaSave, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));						//参数保存命令, 1:保存
		//connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdParaLoad, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));						//参数读取命令, 1:读取
	connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash0, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));			//手动闪光, 1:闪光,自动复位
	connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash1, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));
	connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash2, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));

	connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveUp, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));						//手动升降气缸, 1:Push, 2:Back
	connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveClip, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));					//手动夹紧气缸, 1:Push, 2:Back
	connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveDrop, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));					//手动落囊气缸, 1:Push, 2:Back
	connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdTestInverter, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));					//手动胶囊料斗启动, 1:Start, 2:Stop
	connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampRead, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));					//手动红灯输出, 1:输出 , 2: 复位
	connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampYellow, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));					//手动黄灯输出, 1:输出 , 2: 复位
	connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampGreen, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));					//手动绿灯输出, 1:输出 , 2: 复位
	connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdTestBuzzer, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));						//手动蜂鸣器输出, 1:输出 , 2: 复位
	connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdTestPhoto, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));						//手动拍照, 1:输出 , 2: 复位
	connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlashPhoto, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));					//手动闪光加拍照, 1:启动
	connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdTestCapPhoto, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));					//手动胶囊拍照
	connect(((Ui::QtPLCDialogClass*)ui)->pb_cmdRotateCtl, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));						//手动转囊启停  报文是1

	connect(((Ui::QtPLCDialogClass*)ui)->pB_enPhoto, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));					//拍照使能
	connect(((Ui::QtPLCDialogClass*)ui)->pB_enReject, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));						//剔废使能  报文是4
	connect(((Ui::QtPLCDialogClass*)ui)->pB_enFeed, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));						//料斗使能  报文是4
	connect(((Ui::QtPLCDialogClass*)ui)->pB_enRotate, SIGNAL(toggled(bool)), this, SLOT(onSendPLCCommand(bool)));						//转囊使能  报文是4

	initContinueKick();//连剔开关、数量初始化

	m_data = new DataToPC_typ;
	memset(m_data, 0, sizeof(DataToPC_typ));//主界面用
	//指示灯部分

	((Ui::QtPLCDialogClass*)ui)->lb_00->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));
	((Ui::QtPLCDialogClass*)ui)->lb_01->setPixmap(QPixmap(AppPath + "/ico/redGreen.png"));
	((Ui::QtPLCDialogClass*)ui)->lb_10->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));
	((Ui::QtPLCDialogClass*)ui)->lb_11->setPixmap(QPixmap(AppPath + "/ico/redGreen.png"));
	((Ui::QtPLCDialogClass*)ui)->lb_20->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));
	((Ui::QtPLCDialogClass*)ui)->lb_21->setPixmap(QPixmap(AppPath + "/ico/redGreen.png"));
	((Ui::QtPLCDialogClass*)ui)->lb_30->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));
	((Ui::QtPLCDialogClass*)ui)->lb_31->setPixmap(QPixmap(AppPath + "/ico/redGreen.png"));
	((Ui::QtPLCDialogClass*)ui)->lb_40->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));
	((Ui::QtPLCDialogClass*)ui)->lb_41->setPixmap(QPixmap(AppPath + "/ico/redGreen.png"));
	//指示灯部分

	//model部分的信号与槽↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
	//键盘部分信号与槽↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	//两个键盘👇👇👇👇
	//1st
	QList<QAbstractButton*> buttonsList = ((Ui::QtPLCDialogClass*)ui)->buttonGroup_Keyboard->buttons();
	if (buttonsList.isEmpty()) {
		qDebug() << "isEmpty";
		return;
	}
	foreach(QAbstractButton * button, buttonsList)
	{
		((QPushButton*)button)->move(670, 10);//前12个按钮
		//((QPushButton*)button)->FocusManager.IsFocusScope = "False";//不获取焦点
		((QPushButton*)button)->setFocusPolicy(Qt::NoFocus);
		//不接受焦点针对某些控件-用户鼠标和键盘不能对控件进行任何操作，对于pushbutton不存在
// 		((Ui::QtPLCDialogClass*)ui)->lineEdit->setFocusPolicy(Qt::NoFocus);
// 
// 		Qt::TabFocus             //可以通过通过Tab键接受焦点
// 			Qt::ClickFocus           //可以通过单击接受焦点
// 			Qt::StrongFocus          //TabFocus | ClickFocus | 0x8
// 			Qt::WheelFocus           //可以通过使用鼠标滚轮接受焦点
// 			Qt::NoFocus              //不接受焦点。

	}
	((Ui::QtPLCDialogClass*)ui)->pushButton_13->setText("");
	((Ui::QtPLCDialogClass*)ui)->pushButton_13->setFocusPolicy(Qt::NoFocus);
	((Ui::QtPLCDialogClass*)ui)->pushButton_12->setIcon(QIcon(AppPath + "/ico/dr_keyboard.ico"));//文件copy到了exe所在目录
	((Ui::QtPLCDialogClass*)ui)->pushButton_12->setText("");//文件copy到了exe所在目录


	connect(((Ui::QtPLCDialogClass*)ui)->pushButton_13, SIGNAL(clicked()), this, SLOT(MoveOut()));
	connectBtnGroup();

	QList<UserLE*> UserLEList = ((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->findChildren<UserLE*>();
	for (int i = 0; i < UserLEList.size(); i++)
	{
		connect(UserLEList[i], SIGNAL(POPUPKEYBOARD()), this, SLOT(MoveOut()));
	}

	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	g_ipAddress = configIniRead.value("ProgramSetting/IpAddress", "127.0.0.1").toString();
	g_port = configIniRead.value("ProgramSetting/Port", 5000).toInt();
	((Ui::QtPLCDialogClass*)ui)->lE_IP->setText(g_ipAddress);
	((Ui::QtPLCDialogClass*)ui)->lE_Port->setText(QString::number(g_port));
	connect(((Ui::QtPLCDialogClass*)ui)->lE_IP, &QLineEdit::editingFinished, [=]() {
		if (g_ipAddress != ((Ui::QtPLCDialogClass*)ui)->lE_IP->text())
		{
			QSettings Dir(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);//找到文件
			Dir.setValue("ProgramSetting/IpAddress", ((Ui::QtPLCDialogClass*)ui)->lE_IP->text());//写当前模板
			//levelOut = new WindowOut;
			//levelOut->getString(QString::fromLocal8Bit("恭喜，IP地址设置成功，重新登入系统后生效！"), 2000);
			//levelOut->show();
			g_ipAddress = ((Ui::QtPLCDialogClass*)ui)->lE_IP->text();
		}

	});
	connect(((Ui::QtPLCDialogClass*)ui)->lE_Port, &QLineEdit::editingFinished, [=]() {
		if (g_port != ((Ui::QtPLCDialogClass*)ui)->lE_Port->text().toInt())
		{
			QSettings Dir(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);//找到文件
			Dir.setValue("ProgramSetting/Port", ((Ui::QtPLCDialogClass*)ui)->lE_Port->text());//写当前模板
			//levelOut = new WindowOut;
			//levelOut->getString(QString::fromLocal8Bit("恭喜，通讯端口设置成功，重新登入系统后生效！"), 2000);
			//levelOut->show();
			g_port = ((Ui::QtPLCDialogClass*)ui)->lE_Port->text().toInt();
		}
	});

	connect(((Ui::QtPLCDialogClass*)ui)->pB_Model_Exit3, &QPushButton::clicked, [=]() {
		if (QMessageBox::Yes == showMsgBox(QMessageBox::Question, "退出确认", "<img src = './ico/question.png'/>\t确认退出系统设置页面吗？", "确认", "取消"))
		{
			emit CLOSESIGNAL();
		}});

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





//确定修改后键盘隐藏
void QtPLCDialogClass::on_pB_changeIPPort_clicked()
{
	MoveOutWhenWrite();
}


//continueKick
void QtPLCDialogClass::initContinueKick()
{
	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);//读取ini文件
	((Ui::QtPLCDialogClass*)ui)->cB_ContinueKickAlarm->setCurrentIndex(configIniRead.value("ProgramSetting/ContinueKickAlarm", 0).toInt());//连剔报警开关
	((Ui::QtPLCDialogClass*)ui)->lE_ContinueKickAlarmCount->setText(configIniRead.value("ProgramSetting/ContinueKickAlarmCount", 50).toString());//连剔报警数量
	((Ui::QtPLCDialogClass*)ui)->cB_ContinueKickStop->setCurrentIndex(configIniRead.value("ProgramSetting/ContinueKickStop", 0).toInt());//连剔停机开关
	((Ui::QtPLCDialogClass*)ui)->lE_ContinueKickStopCount->setText(configIniRead.value("ProgramSetting/ContinueKickStopCount", 60).toString());//连剔停机数量

	QRegExp regx("[0-9]+$");//正则表达式QRegExp,只允许输入中文、数字、字母、下划线以及空格,[\u4e00 - \u9fa5a - zA - Z0 - 9_] + $
	((Ui::QtPLCDialogClass*)ui)->lE_ContinueKickAlarmCount->setValidator(new QRegExpValidator(regx, this));
	((Ui::QtPLCDialogClass*)ui)->lE_ContinueKickStopCount->setValidator(new QRegExpValidator(regx, this));
}


void QtPLCDialogClass::on_pB_ContinueKickOK_clicked()//保存连剔
{
	int alarmCount = ((Ui::QtPLCDialogClass*)ui)->lE_ContinueKickAlarmCount->text().toInt();//为了去掉头部的0
	int stopCount = ((Ui::QtPLCDialogClass*)ui)->lE_ContinueKickStopCount->text().toInt();

	((Ui::QtPLCDialogClass*)ui)->lE_ContinueKickAlarmCount->setText(QString::number(alarmCount));//连剔报警数量
	((Ui::QtPLCDialogClass*)ui)->lE_ContinueKickStopCount->setText(QString::number(stopCount));//连剔停机数量

	if (alarmCount < 1 || stopCount < 1)
	{
		//levelOut = new WindowOut;
		//levelOut->getString(QString::fromLocal8Bit("设置胶囊数不能小于1！"), 2000);
		//levelOut->show();
		initContinueKick();
		return;
	}
	else if (alarmCount > stopCount)
	{
		//levelOut = new WindowOut;
		//levelOut->getString(QString::fromLocal8Bit("报警胶囊数不能大于停机胶囊数！"), 2000);
		//levelOut->show();
		initContinueKick();
		return;
	}
	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);//读取ini文件
	configIniRead.setValue("ProgramSetting/ContinueKickAlarm", ((Ui::QtPLCDialogClass*)ui)->cB_ContinueKickAlarm->currentIndex());
	configIniRead.setValue("ProgramSetting/ContinueKickAlarmCount", alarmCount);
	configIniRead.setValue("ProgramSetting/ContinueKickStop", ((Ui::QtPLCDialogClass*)ui)->cB_ContinueKickStop->currentIndex());
	configIniRead.setValue("ProgramSetting/ContinueKickStopCount", stopCount);


	//levelOut = new WindowOut;
	//levelOut->getString(QString::fromLocal8Bit("恭喜，连剔设置成功！"), 2000);
	//levelOut->show();
	MoveOutWhenWrite();//键盘移开

}
void QtPLCDialogClass::on_pB_ContinueKickCancel_clicked()//取消连剔
{
	initContinueKick();
	MoveOutWhenWrite();//键盘移开
}
/////////////////////////////////////////////////////////////////////

void QtPLCDialogClass::on_pb_cmdParaSave_clicked()//加一个按钮保存
{
	DataFromPC_typ typ;
	typ = getPCData();

	if (((Ui::QtPLCDialogClass*)ui)->lE_FeedAxisHomeOffset->text() != QString::number(m_data->Machine_Para.FeedAxisHomeOffset / 100.0, 'f', 2) || ((Ui::QtPLCDialogClass*)ui)->lE_FeedLength->text() != QString::number(m_data->Machine_Para.FeedLength / 100.0, 'f', 2))
	{
		typ.Telegram_typ = 1;
		typ.Machine_Cmd.cmdHome = 1;
		m_socket->Communicate_PLC(&typ, nullptr);//cmd
	}
	typ.Telegram_typ = 2;
	m_socket->Communicate_PLC(&typ, nullptr);//系统

	typ.Telegram_typ = 4;
	m_socket->Communicate_PLC(&typ, nullptr);//运行



	char* plcParam = new char[sizeof(DataFromPC_typ) + 1];
	memset(plcParam, 0, sizeof(DataFromPC_typ) + 1); //1实验用
	memcpy(plcParam, &typ, sizeof(DataFromPC_typ));
	int a = strlen(plcParam);//字符串的长度

	QString plcParamPath = AppPath + "/ModelFile/plc.txt";

	QFile f(plcParamPath);
	f.resize(0);
	if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		showMsgBox(QMessageBox::Question, "错误提示", "<img src = './ico/critical.png'/>\t参数文件写入错误，请重试", "我知道了", "");
		return;
	}
	f.write(plcParam, sizeof(DataFromPC_typ));
	f.close();
	emit GETSTRING(QString::fromLocal8Bit("恭喜，参数文件保存成功！"));
}

void QtPLCDialogClass::on_pb_cmdParaLoad_clicked()//
{
	DataFromPC_typ typ;

	QString plcParamPath = AppPath + "/ModelFile/plc.txt";
	QFile f(plcParamPath);
	if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		showMsgBox(QMessageBox::Question, "错误提示", "<img src = './ico/critical.png'/>\t参数文件读取错误，请重试", "我知道了", "");
		return;
	}
	char* ch = new char[sizeof(DataFromPC_typ) + 1];
	memset(ch, 0, sizeof(DataFromPC_typ) + 1);
	//txtInput.readAll();
	f.read(ch, sizeof(DataFromPC_typ));

	memcpy(&typ, ch, sizeof(DataFromPC_typ));//赋值回来

	f.close();


	emit GETSTRING(QString::fromLocal8Bit("恭喜，参数文件读取成功，已写入PLC！"));

	typ.Telegram_typ = 2;
	m_socket->Communicate_PLC(&typ, nullptr);//系统

	typ.Telegram_typ = 4;
	m_socket->Communicate_PLC(&typ, nullptr);//运行
}

void QtPLCDialogClass::MoveOut()
{
	int i = 2;//first x
	int x = 670;// last x
	int y = 10;
	int j = 55;//增量
	int delay = 600;
	int delay_1 = 300;

	if (((Ui::QtPLCDialogClass*)ui)->pushButton_13->text() == "")
	{
		QPropertyAnimation* animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_1, "pos");
		animation->setDuration(delay);
		animation->setStartValue(QPoint(x, y));
		animation->setEndValue(QPoint(i, y));
		animation->setEasingCurve(QEasingCurve::OutBack);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_2, "pos");
		animation->setDuration(delay);
		animation->setStartValue(QPoint(x, y));
		animation->setEndValue(QPoint(i, y));
		animation->setEasingCurve(QEasingCurve::OutBack);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_3, "pos");
		animation->setDuration(delay);
		animation->setStartValue(QPoint(x, y));
		animation->setEndValue(QPoint(i, y));
		animation->setEasingCurve(QEasingCurve::OutBack);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_4, "pos");
		animation->setDuration(delay);
		animation->setStartValue(QPoint(x, y));
		animation->setEndValue(QPoint(i, y));
		animation->setEasingCurve(QEasingCurve::OutBack);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_5, "pos");
		animation->setDuration(delay);
		animation->setStartValue(QPoint(x, y));
		animation->setEndValue(QPoint(i, y));
		animation->setEasingCurve(QEasingCurve::OutBack);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_6, "pos");
		animation->setDuration(delay);
		animation->setStartValue(QPoint(x, y));
		animation->setEndValue(QPoint(i, y));
		animation->setEasingCurve(QEasingCurve::OutBack);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_7, "pos");
		animation->setDuration(delay);
		animation->setStartValue(QPoint(x, y));
		animation->setEndValue(QPoint(i, y));
		animation->setEasingCurve(QEasingCurve::OutBack);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_8, "pos");
		animation->setDuration(delay);
		animation->setStartValue(QPoint(x, y));
		animation->setEndValue(QPoint(i, y));
		animation->setEasingCurve(QEasingCurve::OutBack);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_9, "pos");
		animation->setDuration(delay);
		animation->setStartValue(QPoint(x, y));
		animation->setEndValue(QPoint(i, y));
		animation->setEasingCurve(QEasingCurve::OutBack);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_10, "pos");
		animation->setDuration(delay);
		animation->setStartValue(QPoint(x, y));
		animation->setEndValue(QPoint(i, y));
		animation->setEasingCurve(QEasingCurve::OutBack);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_11, "pos");
		animation->setDuration(delay);
		animation->setStartValue(QPoint(x, y));
		animation->setEndValue(QPoint(i, y));
		animation->setEasingCurve(QEasingCurve::OutBack);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_14, "pos");
		animation->setDuration(delay);
		animation->setStartValue(QPoint(x, y + 30));
		animation->setEndValue(QPoint(i, y + 30));
		animation->setEasingCurve(QEasingCurve::OutBack);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_12, "pos");
		animation->setDuration(delay);
		animation->setStartValue(QPoint(x, y));
		animation->setEndValue(QPoint(i, y));
		animation->setEasingCurve(QEasingCurve::OutBack);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		((Ui::QtPLCDialogClass*)ui)->pushButton_13->setText(">>");
		((Ui::QtPLCDialogClass*)ui)->pushButton_12->setIcon(QIcon(""));//文件copy到了exe所在目录
		((Ui::QtPLCDialogClass*)ui)->pushButton_12->setText(QString::fromLocal8Bit("删"));//文件copy到了exe所在目录
	}
	else if (((QPushButton*)sender()) == ((Ui::QtPLCDialogClass*)ui)->pushButton_13)
	{
		QPropertyAnimation* animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_1, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_2, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_3, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_4, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_5, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_6, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_7, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_8, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_9, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_10, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_11, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_14, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y + 30));
		animation->setEndValue(QPoint(x, y + 30));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_12, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		((Ui::QtPLCDialogClass*)ui)->pushButton_13->setText("");
		((Ui::QtPLCDialogClass*)ui)->pushButton_12->setIcon(QIcon(AppPath + "/ico/dr_keyboard.ico"));//文件copy到了exe所在目录
		((Ui::QtPLCDialogClass*)ui)->pushButton_12->setText("");//文件copy到了exe所在目录
	}
}


void QtPLCDialogClass::MoveOutWhenWrite()
{
	int i = 2;//first x
	int x = 670;// last x
	int y = 10;
	int j = 55;//增量
	int delay = 600;
	int delay_1 = 300;

	if (((Ui::QtPLCDialogClass*)ui)->pushButton_13->text() == ">>")
	{
		QPropertyAnimation* animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_1, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_2, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_3, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_4, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_5, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_6, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_7, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_8, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_9, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_10, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_11, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_14, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y + 30));
		animation->setEndValue(QPoint(x, y + 30));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
		i += j;
		animation = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pushButton_12, "pos");
		animation->setDuration(delay_1);
		animation->setStartValue(QPoint(i, y));
		animation->setEndValue(QPoint(x, y));
		animation->setEasingCurve(QEasingCurve::Linear);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		((Ui::QtPLCDialogClass*)ui)->pushButton_13->setText("");
		((Ui::QtPLCDialogClass*)ui)->pushButton_12->setIcon(QIcon(AppPath + "/ico/dr_keyboard.ico"));//文件copy到了exe所在目录
		((Ui::QtPLCDialogClass*)ui)->pushButton_12->setText("");//文件copy到了exe所在目录
	}
}

void QtPLCDialogClass::onDebugMode(bool b)
{
	if (((Ui::QtPLCDialogClass*)ui)->cB_debugMode->isChecked())
	{
		((Ui::QtPLCDialogClass*)ui)->cB_debugMode->setEnabled(false);
		if (m_objname == ""&& b)
			cyclinderTimer->start(2000);

		obj = qobject_cast<QPushButton*>(sender());//判断是哪个按钮触发了槽函数	obj->setFocus();
		m_tempname = m_objname;
		m_objname = obj->objectName();//获取触发者objectname	

		/////////////////////////先动作一次
		DataFromPC_typ typ;
		typ.Dummy = 0;//占空
		typ.Telegram_typ = 1;//命令报文
		int index_cmdkick = m_objname.mid(14).toInt();//从0开始，14位之后的字符转为int，0-29
		if (30 > index_cmdkick)
		{
			typ.Machine_Cmd.cmdTestKick[index_cmdkick] = 1;//结构体数据赋值
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick30->setStyleSheet("");
			blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick30->setChecked(false);
			blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick30->setStyleSheet("background: rgb(0,255,0)");
			for (int i = 0; i < 30; i++)
			{
				typ.Machine_Cmd.cmdTestKick[i] = 1;//结构体数据赋值
			}
		}
		m_socket->Communicate_PLC(&typ, nullptr);//此处只发送，不接收

		if (m_tempname == m_objname)
		{
			cyclinderTimer->stop();
			m_objname = "";
			((Ui::QtPLCDialogClass*)ui)->cB_debugMode->setEnabled(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick30->setStyleSheet("");
			blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick30->setChecked(false);
			blockSignals(false);
		}
	}

}

void QtPLCDialogClass::updateCyclinderSituation()
{
	DataFromPC_typ typ;
	typ.Dummy = 0;//占空
	typ.Telegram_typ = 1;//命令报文
	int index_cmdkick = m_objname.mid(14).toInt();//从0开始，14位之后的字符转为int，0-29

	if (m_currentSituationOfCyclinder)
	{
		if (30 > index_cmdkick)
		{
			typ.Machine_Cmd.cmdTestKick[index_cmdkick] = 1;//结构体数据赋值
		}
		else
		{
			for (int i = 0; i < 30; i++)
			{
				typ.Machine_Cmd.cmdTestKick[i] = 1;//结构体数据赋值
			}
		}
		m_currentSituationOfCyclinder = false;
	}
	else
	{
		if (30 > index_cmdkick)
		{
			typ.Machine_Cmd.cmdTestKick[index_cmdkick] = 0;//结构体数据赋值
		}
		else
		{
			for (int i = 0; i < 30; i++)
			{
				typ.Machine_Cmd.cmdTestKick[i] = 0;//结构体数据赋值
			}
		}
		m_currentSituationOfCyclinder = true;
	}

	m_socket->Communicate_PLC(&typ, nullptr);//此处只发送，不接收
}

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
	typ.Dummy = 0;//占空
	typ.Telegram_typ = 1;//命令报文
	if (obj != nullptr)
	{

		if (b)
		{
			if (objname == "pB_enPhoto" || objname == "pB_enReject" || objname == "pB_enFeed" || objname == "pB_enRotate")
			{
				typ.Telegram_typ = 4;//运行报文
				if (objname == "pB_enPhoto")
				{
					typ.Run_Para.enPhoto = 1;
				}
				if (objname == "pB_enReject")
				{
					typ.Run_Para.enReject = 1;
				}
				if (objname == "pB_enFeed")
				{
					typ.Run_Para.enFeed = 1;
				}
				if (objname == "pB_enRotate")
				{
					typ.Run_Para.enRotate = 1;
				}
				//////////obj->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
				m_socket->Communicate_PLC(&typ, nullptr);//此处只发送，不接收
			}

			else {
				if (objname.contains("pb_cmdTestKick"))
				{
					if (!((Ui::QtPLCDialogClass*)ui)->cB_debugMode->isChecked())
					{
						cyclinderTimer->stop();
						m_objname = "";
						int index_cmdkick = objname.mid(14).toInt();//从0开始，14位之后的字符转为int，0-29
						if (30 > index_cmdkick)
						{
							typ.Machine_Cmd.cmdTestKick[index_cmdkick] = 1;//结构体数据赋值
						}
						else
						{
							for (int i = 0; i < 30; i++)
							{
								typ.Machine_Cmd.cmdTestKick[i] = 1;//结构体数据赋值
							}
						}
					}
				}
				if (objname == "pb_cmdHome") typ.Machine_Cmd.cmdHome = 1;//结构体数据赋值
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

				/////////////////obj->setStyleSheet("background: rgb(0,255,0)");
			}
		}
		if (!b)
		{
			if (objname == "pB_enPhoto" || objname == "pB_enReject" || objname == "pB_enFeed" || objname == "pB_enRotate")
			{
				typ.Telegram_typ = 4;//运行报文
				if (objname == "pB_enPhoto")
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
				}
				obj->setStyleSheet("font-size:20pt");
				m_socket->Communicate_PLC(&typ, nullptr);//此处只发送，不接收
			}
			else {
				if (objname.contains("pb_cmdTestKick"))
				{
					if (!((Ui::QtPLCDialogClass*)ui)->cB_debugMode->isChecked())
					{
						cyclinderTimer->stop();
						m_objname = "";
						int index_cmdkick = objname.mid(14).toInt();//从0开始，14位之后的字符转为int，0-29	
						if (30 > index_cmdkick)
						{
							typ.Machine_Cmd.cmdTestKick[index_cmdkick] = 0;//结构体数据赋值
						}
						else
						{
							for (int i = 0; i < 30; i++)
							{
								typ.Machine_Cmd.cmdTestKick[i] = 0;//结构体数据赋值
							}
						}
					}
				}
				if (objname == "pb_cmdHome")typ.Machine_Cmd.cmdHome = 0;
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
				if (objname == "pb_cmdErrorAck") typ.Machine_Cmd.cmdErrorAck = 0;					//报警复位, 1:复位
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
				obj->setStyleSheet("");
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

		if (!((Ui::QtPLCDialogClass*)ui)->cB_debugMode->isChecked())
		{
			blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick30->setChecked(false);
			blockSignals(false);
		}
	}
	MoveOutWhenWrite();


}
//获取pc数据
DataFromPC_typ QtPLCDialogClass::getPCData()
{

	DataFromPC_typ tmp;
	memset(&tmp, 0, sizeof(DataFromPC_typ));//将新char所指向的前size字节的内存单元用一个0替换，初始化内存。下同
	tmp.Dummy = 0;
	//tmp.Telegram_typ = ((Ui::QtPLCDialogClass*)ui)->lE_Telegram_typ->text().toInt();

	//系统参数
	tmp.Machine_Para.FeedAxisHomeOffset = QString::number(((Ui::QtPLCDialogClass*)ui)->lE_FeedAxisHomeOffset->text().toFloat() * 100).toInt();//qstring-float-qstring-int
	tmp.Machine_Para.ClipPhase1 = QString::number(((Ui::QtPLCDialogClass*)ui)->lE_ClipPhase1->text().toFloat() * 100).toInt();
	tmp.Machine_Para.ClipPhase2 = QString::number(((Ui::QtPLCDialogClass*)ui)->lE_ClipPhase2->text().toFloat() * 100).toInt();
	tmp.Machine_Para.UpPhase1 = QString::number(((Ui::QtPLCDialogClass*)ui)->lE_UpPhase1->text().toFloat() * 100).toInt();
	tmp.Machine_Para.UpPhase2 = QString::number(((Ui::QtPLCDialogClass*)ui)->lE_UpPhase2->text().toFloat() * 100).toInt();
	tmp.Machine_Para.DropPhase1 = QString::number(((Ui::QtPLCDialogClass*)ui)->lE_DropPhase1->text().toFloat() * 100).toInt();
	tmp.Machine_Para.DropPhase2 = QString::number(((Ui::QtPLCDialogClass*)ui)->lE_DropPhase2->text().toFloat() * 100).toInt();
	tmp.Machine_Para.tClip1 = ((Ui::QtPLCDialogClass*)ui)->lE_tClip1->text().toFloat();
	tmp.Machine_Para.tClip2 = ((Ui::QtPLCDialogClass*)ui)->lE_tClip2->text().toFloat();
	tmp.Machine_Para.tUp1 = ((Ui::QtPLCDialogClass*)ui)->lE_tUp1->text().toFloat();
	tmp.Machine_Para.tUp2 = ((Ui::QtPLCDialogClass*)ui)->lE_tUp2->text().toFloat();
	tmp.Machine_Para.tDrop1 = ((Ui::QtPLCDialogClass*)ui)->lE_tDrop1->text().toFloat();
	tmp.Machine_Para.tDrop2 = ((Ui::QtPLCDialogClass*)ui)->lE_tDrop2->text().toFloat();
	tmp.Machine_Para.FeedLength = QString::number(((Ui::QtPLCDialogClass*)ui)->lE_FeedLength->text().toFloat() * 100).toInt();
	tmp.Machine_Para.FlashTime = ((Ui::QtPLCDialogClass*)ui)->lE_FlashTime->text().toFloat();
	tmp.Machine_Para.PhotoTime = ((Ui::QtPLCDialogClass*)ui)->lE_PhotoTime->text().toFloat();
	tmp.Machine_Para.RejectTime = ((Ui::QtPLCDialogClass*)ui)->lE_RejectTime->text().toFloat();
	tmp.Machine_Para.PhotoDelay = ((Ui::QtPLCDialogClass*)ui)->lE_PhotoDelay->text().toFloat();
	tmp.Machine_Para.PhotoPhase = QString::number(((Ui::QtPLCDialogClass*)ui)->lE_PhotoPhase->text().toFloat() * 100).toInt();
	tmp.Machine_Para.RejectPhase = QString::number(((Ui::QtPLCDialogClass*)ui)->lE_RejectPhase->text().toFloat() * 100).toInt();
	tmp.Machine_Para.PhotoTimes = ((Ui::QtPLCDialogClass*)ui)->lE_PhotoTimes->text().toInt();
	tmp.Machine_Para.RotateSpeed = ((Ui::QtPLCDialogClass*)ui)->lE_RotateSpeed->text().toFloat();
	tmp.Machine_Para.DisableForceReject = ((Ui::QtPLCDialogClass*)ui)->lE_DisableForceReject->text().toInt();		//关闭强制剔废,1:关闭
	tmp.Machine_Para.CapCheckAlarmTime = ((Ui::QtPLCDialogClass*)ui)->lE_CapCheckAlarmTime->text().toInt();		//胶囊检测报警时间，单位ms
	tmp.Machine_Para.RejectFallingTime = ((Ui::QtPLCDialogClass*)ui)->lE_RejectFallingTime->text().toInt();		//剔废胶囊下落时间，单位ms
	tmp.Machine_Para.PhotoInterval = ((Ui::QtPLCDialogClass*)ui)->lE_PhotoInterval->text().toFloat();
	//运行数据
	tmp.Run_Para.RunSpeed = ((Ui::QtPLCDialogClass*)ui)->lE_RunSpeed->text().toInt();
	tmp.Run_Para.SysPhase = ((Ui::QtPLCDialogClass*)ui)->lE_SysPhase->text().toInt();
	tmp.Run_Para.enPhoto = ((Ui::QtPLCDialogClass*)ui)->pB_enPhoto->isChecked() ? 1 : 0;
	tmp.Run_Para.enReject = ((Ui::QtPLCDialogClass*)ui)->pB_enReject->isChecked() ? 1 : 0;
	tmp.Run_Para.enFeed = ((Ui::QtPLCDialogClass*)ui)->pB_enFeed->isChecked() ? 1 : 0;
	tmp.Run_Para.enRotate = ((Ui::QtPLCDialogClass*)ui)->pB_enRotate->isChecked() ? 1 : 0;
	tmp.Run_Para.CheckCount = m_data->ActData.CheckCount;
	tmp.Run_Para.RejectCount = m_data->ActData.RejectCount;
	tmp.Run_Para.ForceRejectCount = m_data->ActData.ForceRejectCount;

	//命令
	//tmp.Machine_Cmd.cmdHome = ((Ui::QtPLCDialogClass*)ui)->pb_cmdHome->isChecked() ? 1 : 0;//寻参,1:寻参启动
	tmp.Machine_Cmd.cmdStart = 0;							//启动,1:启动运行
	tmp.Machine_Cmd.cmdStop = 0;							//停止,停在0相位,1:停止
	tmp.Machine_Cmd.cmdEStop = 0;							//紧急停止(立即停止), 1:停止
	tmp.Machine_Cmd.cmdJog = ((Ui::QtPLCDialogClass*)ui)->pb_cmdJog->isChecked() ? 1 : 0;							//点动运行, 1,启动,2,停止
	tmp.Machine_Cmd.cmdErrorAck = 0;						//报警复位, 1:复位
	tmp.Machine_Cmd.cmdResetCounter = 0;					//复位计数变量, 1:复位
	//tmp.Machine_Cmd.cmdParaSave = ((Ui::QtPLCDialogClass*)ui)->pb_cmdParaSave->isChecked() ? 1 : 0;						//参数保存命令, 1:保存
	//tmp.Machine_Cmd.cmdParaLoad = ((Ui::QtPLCDialogClass*)ui)->pb_cmdParaLoad->isChecked() ? 1 : 0;						//参数读取命令, 1:读取
	tmp.Machine_Cmd.cmdTestKick[0] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick0->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[1] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick1->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[2] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick2->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[3] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick3->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back	
	tmp.Machine_Cmd.cmdTestKick[4] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick4->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[5] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick5->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[6] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick6->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[7] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick7->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[8] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick8->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[9] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick9->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[10] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick10->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[11] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick11->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[12] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick12->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[13] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick13->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back	
	tmp.Machine_Cmd.cmdTestKick[14] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick14->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[15] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick15->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[16] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick16->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[17] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick17->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[18] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick18->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[19] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick19->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[20] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick20->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[21] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick21->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[22] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick22->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[23] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick23->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back	
	tmp.Machine_Cmd.cmdTestKick[24] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick24->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[25] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick25->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[26] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick26->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[27] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick27->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[28] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick28->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestKick[29] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick29->isChecked() ? 1 : 2;		//手动剔废, 1:Push, 2:Back

	tmp.Machine_Cmd.cmdTestFlash[0] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash0->isChecked() ? 1 : 0;			//手动闪光, 1:闪光,自动复位
	tmp.Machine_Cmd.cmdTestFlash[1] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash1->isChecked() ? 1 : 0;			//手动闪光, 1:闪光,自动复位
	tmp.Machine_Cmd.cmdTestFlash[2] = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash2->isChecked() ? 1 : 0;			//手动闪光, 1:闪光,自动复位

	tmp.Machine_Cmd.cmdTestValveUp = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveUp->isChecked() ? 1 : 2;						//手动升降气缸, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestValveClip = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveClip->isChecked() ? 1 : 2;					//手动夹紧气缸, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestValveDrop = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveDrop->isChecked() ? 1 : 2;					//手动落囊气缸, 1:Push, 2:Back
	tmp.Machine_Cmd.cmdTestInverter = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestInverter->isChecked() ? 1 : 0;					//手动胶囊料斗启动, 1:Start, 2:Stop
	tmp.Machine_Cmd.cmdTestLampRead = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampRead->isChecked() ? 1 : 2;					//手动红灯输出, 1:输出 , 2: 复位
	tmp.Machine_Cmd.cmdTestLampYellow = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampYellow->isChecked() ? 1 : 2;					//手动黄灯输出, 1:输出 , 2: 复位
	tmp.Machine_Cmd.cmdTestLampGreen = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampGreen->isChecked() ? 1 : 2;					//手动绿灯输出, 1:输出 , 2: 复位
	tmp.Machine_Cmd.cmdTestBuzzer = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestBuzzer->isChecked() ? 1 : 2;						//手动蜂鸣器输出, 1:输出 , 2: 复位
	tmp.Machine_Cmd.cmdTestPhoto = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestPhoto->isChecked() ? 1 : 2;						//手动拍照, 1:输出 , 2: 复位
	tmp.Machine_Cmd.cmdTestFlashPhoto = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlashPhoto->isChecked() ? 1 : 0;					//手动闪光加拍照, 1:启动
	tmp.Machine_Cmd.cmdTestCapPhoto = ((Ui::QtPLCDialogClass*)ui)->pb_cmdTestCapPhoto->isChecked() ? 1 : 0;					//手动胶囊拍照
	tmp.Machine_Cmd.cmdRotateCtl = ((Ui::QtPLCDialogClass*)ui)->pb_cmdRotateCtl->isChecked() ? 1 : 0;						//手动转囊启停
	tmp.Machine_Cmd.cmdSetAlarm = 0;								//手动触发报警号，不等于零触发。范围1-99

	//照相处理结果和按钮在上面⬆⬆⬆⬆⬆⬆

	return tmp;
}
//PC显示数据
void QtPLCDialogClass::getPLCData(void* data, int machinetype, int home, int kickOpen, int kickMode)
{
	memcpy(m_data, (DataToPC_typ*)data, sizeof(DataToPC_typ));//主界面用

	//报文类型
	//((Ui::QtPLCDialogClass*)ui)->lE_Telegram_typ->setText(QString::number(m_data->Telegram_typ));

	//运行数据
	if (!((Ui::QtPLCDialogClass*)ui)->lE_RunSpeed->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_RunSpeed->setText(QString::number(m_data->ActData.RunSpeed));
	}
	((Ui::QtPLCDialogClass*)ui)->lE_SysPhase->setText(QString::number(m_data->ActData.SysPhase / 100.0, 'f', 2));
	if (m_data->ActData.enPhoto == 1)
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
	//((Ui::QtPLCDialogClass*)ui)->lE_ForceRejectCount->setText(QString::number(m_data->ActData.ForceRejectCount));

	//系统状态
	((Ui::QtPLCDialogClass*)ui)->lE_AlarmStatus->setText(QString::number(m_data->Status.AlarmStatus));
	((Ui::QtPLCDialogClass*)ui)->lE_Alarm16->setText((char*)(m_data->Status.Alarm));
	((Ui::QtPLCDialogClass*)ui)->lE_ServoErrorNum0->setText(QString::number(m_data->Status.ServoErrorNum[0]));
	((Ui::QtPLCDialogClass*)ui)->lE_ServoErrorNum1->setText(QString::number(m_data->Status.ServoErrorNum[1]));
	((Ui::QtPLCDialogClass*)ui)->lE_SysPhase_1->setText(QString::number(m_data->Status.SysPhase / 100.0, 'f', 2));
	((Ui::QtPLCDialogClass*)ui)->lE_HomeOK->setText(QString::number(m_data->Status.HomeOK));

	//系统参数
	if (!((Ui::QtPLCDialogClass*)ui)->lE_FeedAxisHomeOffset->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_FeedAxisHomeOffset->setText(QString::number(m_data->Machine_Para.FeedAxisHomeOffset / 100.0, 'f', 2));//显示到小数点后两位
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_ClipPhase1->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_ClipPhase1->setText(QString::number(m_data->Machine_Para.ClipPhase1 / 100.0, 'f', 2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_ClipPhase2->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_ClipPhase2->setText(QString::number(m_data->Machine_Para.ClipPhase2 / 100.0, 'f', 2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_UpPhase1->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_UpPhase1->setText(QString::number(m_data->Machine_Para.UpPhase1 / 100.0, 'f', 2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_UpPhase2->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_UpPhase2->setText(QString::number(m_data->Machine_Para.UpPhase2 / 100.0, 'f', 2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_DropPhase1->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_DropPhase1->setText(QString::number(m_data->Machine_Para.DropPhase1 / 100.0, 'f', 2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_DropPhase2->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_DropPhase2->setText(QString::number(m_data->Machine_Para.DropPhase2 / 100.0, 'f', 2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_tClip1->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_tClip1->setText(QString::number(m_data->Machine_Para.tClip1));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_tClip2->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_tClip2->setText(QString::number(m_data->Machine_Para.tClip2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_tUp1->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_tUp1->setText(QString::number(m_data->Machine_Para.tUp1));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_tUp2->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_tUp2->setText(QString::number(m_data->Machine_Para.tUp2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_tDrop1->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_tDrop1->setText(QString::number(m_data->Machine_Para.tDrop1));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_tDrop2->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_tDrop2->setText(QString::number(m_data->Machine_Para.tDrop2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_FeedLength->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_FeedLength->setText(QString::number(m_data->Machine_Para.FeedLength / 100.0, 'f', 2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_FlashTime->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_FlashTime->setText(QString::number(m_data->Machine_Para.FlashTime));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_PhotoTime->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_PhotoTime->setText(QString::number(m_data->Machine_Para.PhotoTime));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_RejectTime->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_RejectTime->setText(QString::number(m_data->Machine_Para.RejectTime));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_PhotoDelay->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_PhotoDelay->setText(QString::number(m_data->Machine_Para.PhotoDelay));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_PhotoPhase->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_PhotoPhase->setText(QString::number(m_data->Machine_Para.PhotoPhase / 100.0, 'f', 2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_RejectPhase->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_RejectPhase->setText(QString::number(m_data->Machine_Para.RejectPhase / 100.0, 'f', 2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_PhotoTimes->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_PhotoTimes->setText(QString::number(m_data->Machine_Para.PhotoTimes));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_RotateSpeed->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_RotateSpeed->setText(QString::number(m_data->Machine_Para.RotateSpeed));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_DisableForceReject->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_DisableForceReject->setText(QString::number(m_data->Machine_Para.DisableForceReject));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_CapCheckAlarmTime->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_CapCheckAlarmTime->setText(QString::number(m_data->Machine_Para.CapCheckAlarmTime));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_RejectFallingTime->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_RejectFallingTime->setText(QString::number(m_data->Machine_Para.RejectFallingTime));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_PhotoInterval->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_PhotoInterval->setText(QString::number(m_data->Machine_Para.PhotoInterval));
	}

	//输入点
	//((Ui::QtPLCDialogClass*)ui)->lE_EStop->setText(m_data->Inputs.EStop ? "1" : "0");
	((Ui::QtPLCDialogClass*)ui)->lb_00->setVisible(m_data->Inputs.EStop ? true : false);
	//((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedPosEnd->setText(m_data->Inputs.AxisFeedPosEnd ? "1" : "0");
	((Ui::QtPLCDialogClass*)ui)->lb_10->setVisible(m_data->Inputs.AxisFeedPosEnd ? false : true);
	//((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedNegEnd->setText(m_data->Inputs.AxisFeedNegEnd ? "1" : "0");
	((Ui::QtPLCDialogClass*)ui)->lb_20->setVisible(m_data->Inputs.AxisFeedNegEnd ? false : true);
	//((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedHome->setText(m_data->Inputs.AxisFeedHome ? "1" : "0");
	((Ui::QtPLCDialogClass*)ui)->lb_30->setVisible(m_data->Inputs.AxisFeedHome ? false : true);
	//((Ui::QtPLCDialogClass*)ui)->lE_AirPressChk->setText(m_data->Inputs.AirPressChk ? "1" : "0");
	((Ui::QtPLCDialogClass*)ui)->lb_40->setVisible(m_data->Inputs.AirPressChk ? false : true);

	//输出点
	//((Ui::QtPLCDialogClass*)ui)->lE_Inveter->setText(m_data->Outputs.Inveter ? "1" : "0");	
	if (m_data->Outputs.Inveter)
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestInverter->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestInverter->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestInverter->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestInverter->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestInverter->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestInverter->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestInverter->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestInverter->blockSignals(false);
	}
	//((Ui::QtPLCDialogClass*)ui)->lE_ClipValve->setText(m_data->Outputs.ClipValve ? "1" : "0");
	if (m_data->Outputs.ClipValve)
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveClip->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveClip->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveClip->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveClip->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveClip->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveClip->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveClip->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveClip->blockSignals(false);
	}
	//((Ui::QtPLCDialogClass*)ui)->lE_UpValve->setText(m_data->Outputs.UpValve ? "1" : "0");
	if (m_data->Outputs.UpValve)
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveUp->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveUp->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveUp->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveUp->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveUp->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveUp->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveUp->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveUp->blockSignals(false);
	}
	//((Ui::QtPLCDialogClass*)ui)->lE_DropValve->setText(m_data->Outputs.DropValve ? "1" : "0");
	if (m_data->Outputs.DropValve)
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveDrop->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveDrop->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveDrop->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveDrop->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveDrop->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveDrop->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveDrop->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestValveDrop->blockSignals(false);
	}
	//((Ui::QtPLCDialogClass*)ui)->lE_LampRed->setText(m_data->Outputs.LampRed ? "1" : "0");
	if (m_data->Outputs.LampRed)
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampRead->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampRead->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampRead->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampRead->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampRead->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampRead->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampRead->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampRead->blockSignals(false);
	}
	//((Ui::QtPLCDialogClass*)ui)->lE_LampYellow->setText(m_data->Outputs.LampYellow ? "1" : "0");
	if (m_data->Outputs.LampYellow)
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampYellow->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampYellow->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampYellow->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampYellow->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampYellow->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampYellow->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampYellow->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampYellow->blockSignals(false);
	}
	//((Ui::QtPLCDialogClass*)ui)->lE_LampGreen->setText(m_data->Outputs.LampGreen ? "1" : "0");
	if (m_data->Outputs.LampGreen)
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampGreen->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampGreen->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampGreen->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampGreen->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampGreen->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampGreen->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampGreen->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestLampGreen->blockSignals(false);
	}
	//((Ui::QtPLCDialogClass*)ui)->lE_Buzzer->setText(m_data->Outputs.Buzzer ? "1" : "0");
	if (m_data->Outputs.Buzzer)
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestBuzzer->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestBuzzer->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestBuzzer->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestBuzzer->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestBuzzer->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestBuzzer->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestBuzzer->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestBuzzer->blockSignals(false);
	}
	//((Ui::QtPLCDialogClass*)ui)->lE_Photo->setText(m_data->Outputs.Photo ? "1" : "0");
	if (m_data->Outputs.Photo)
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestPhoto->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestPhoto->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestPhoto->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestPhoto->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestPhoto->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestPhoto->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestPhoto->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestPhoto->blockSignals(false);
	}

	//((Ui::QtPLCDialogClass*)ui)->lE_Flash0->setText(m_data->Outputs.Flash[0] ? "1" : "0");
	if (m_data->Outputs.Flash[0])
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash0->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash0->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash0->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash0->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash0->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash0->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash0->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash0->blockSignals(false);
	}
	//((Ui::QtPLCDialogClass*)ui)->lE_Flash1->setText(m_data->Outputs.Flash[1] ? "1" : "0");
	if (m_data->Outputs.Flash[1])
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash1->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash1->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash1->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash1->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash1->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash1->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash1->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash1->blockSignals(false);
	}
	//((Ui::QtPLCDialogClass*)ui)->lE_Flash2->setText(m_data->Outputs.Flash[2] ? "1" : "0");	
	if (m_data->Outputs.Flash[2])
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash2->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash2->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash2->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash2->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash2->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash2->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash2->setStyleSheet("font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdTestFlash2->blockSignals(false);
	}

	/*((Ui::QtPLCDialogClass*)ui)->lE_Reject0->setText(m_data->Outputs.Reject[0] ? "1" : "0");*/
	//if (!((Ui::QtPLCDialogClass*)ui)->cB_debugMode->isChecked())
	{
		if (m_data->Outputs.Reject[0])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick0->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick0->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick0->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick0->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick0->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick0->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick0->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick0->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject1->setText(m_data->Outputs.Reject[1] ? "1" : "0");	
		if (m_data->Outputs.Reject[1])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick1->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick1->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick1->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick1->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick1->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick1->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick1->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick1->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject2->setText(m_data->Outputs.Reject[2] ? "1" : "0");
		if (m_data->Outputs.Reject[2])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick2->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick2->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick2->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick2->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick2->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick2->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick2->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick2->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject3->setText(m_data->Outputs.Reject[3] ? "1" : "0");
		if (m_data->Outputs.Reject[3])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick3->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick3->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick3->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick3->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick3->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick3->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick3->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick3->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject4->setText(m_data->Outputs.Reject[4] ? "1" : "0");
		if (m_data->Outputs.Reject[4])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick4->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick4->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick4->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick4->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick4->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick4->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick4->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick4->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject5->setText(m_data->Outputs.Reject[5] ? "1" : "0");
		if (m_data->Outputs.Reject[5])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick5->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick5->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick5->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick5->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick5->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick5->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick5->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick5->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject6->setText(m_data->Outputs.Reject[6] ? "1" : "0");
		if (m_data->Outputs.Reject[6])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick6->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick6->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick6->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick6->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick6->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick6->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick6->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick6->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject7->setText(m_data->Outputs.Reject[7] ? "1" : "0");
		if (m_data->Outputs.Reject[7])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick7->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick7->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick7->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick7->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick7->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick7->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick7->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick7->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject8->setText(m_data->Outputs.Reject[8] ? "1" : "0");
		if (m_data->Outputs.Reject[8])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick8->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick8->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick8->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick8->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick8->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick8->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick8->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick8->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject9->setText(m_data->Outputs.Reject[9] ? "1" : "0");
		if (m_data->Outputs.Reject[9])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick9->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick9->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick9->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick9->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick9->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick9->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick9->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick9->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject10->setText(m_data->Outputs.Reject[10] ? "1" : "0");
		if (m_data->Outputs.Reject[10])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick10->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick10->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick10->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick10->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick10->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick10->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick10->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick10->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject11->setText(m_data->Outputs.Reject[11] ? "1" : "0");
		if (m_data->Outputs.Reject[11])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick11->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick11->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick11->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick11->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick11->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick11->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick11->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick11->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject12->setText(m_data->Outputs.Reject[12] ? "1" : "0");
		if (m_data->Outputs.Reject[12])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick12->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick12->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick12->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick12->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick12->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick12->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick12->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick12->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject13->setText(m_data->Outputs.Reject[13] ? "1" : "0");
		if (m_data->Outputs.Reject[13])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick13->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick13->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick13->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick13->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick13->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick13->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick13->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick13->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject14->setText(m_data->Outputs.Reject[14] ? "1" : "0");
		if (m_data->Outputs.Reject[14])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick14->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick14->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick14->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick14->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick14->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick14->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick14->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick14->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject15->setText(m_data->Outputs.Reject[15] ? "1" : "0");
		if (m_data->Outputs.Reject[15])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick15->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick15->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick15->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick15->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick15->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick15->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick15->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick15->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject16->setText(m_data->Outputs.Reject[16] ? "1" : "0");
		if (m_data->Outputs.Reject[16])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick16->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick16->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick16->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick16->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick16->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick16->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick16->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick16->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject17->setText(m_data->Outputs.Reject[17] ? "1" : "0");
		if (m_data->Outputs.Reject[17])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick17->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick17->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick17->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick17->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick17->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick17->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick17->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick17->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject18->setText(m_data->Outputs.Reject[18] ? "1" : "0");
		if (m_data->Outputs.Reject[18])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick18->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick18->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick18->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick18->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick18->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick18->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick18->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick18->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject19->setText(m_data->Outputs.Reject[19] ? "1" : "0");
		if (m_data->Outputs.Reject[19])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick19->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick19->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick19->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick19->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick19->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick19->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick19->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick19->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject20->setText(m_data->Outputs.Reject[20] ? "1" : "0");
		if (m_data->Outputs.Reject[20])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick20->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick20->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick20->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick20->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick20->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick20->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick20->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick20->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject21->setText(m_data->Outputs.Reject[21] ? "1" : "0");
		if (m_data->Outputs.Reject[21])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick21->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick21->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick21->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick21->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick21->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick21->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick21->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick21->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject22->setText(m_data->Outputs.Reject[22] ? "1" : "0");
		if (m_data->Outputs.Reject[22])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick22->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick22->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick22->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick22->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick22->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick22->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick22->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick22->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject23->setText(m_data->Outputs.Reject[23] ? "1" : "0");
		if (m_data->Outputs.Reject[23])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick23->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick23->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick23->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick23->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick23->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick23->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick23->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick23->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject24->setText(m_data->Outputs.Reject[24] ? "1" : "0");
		if (m_data->Outputs.Reject[24])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick24->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick24->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick24->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick24->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick24->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick24->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick24->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick24->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject25->setText(m_data->Outputs.Reject[25] ? "1" : "0");
		if (m_data->Outputs.Reject[25])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick25->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick25->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick25->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick25->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick25->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick25->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick25->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick25->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject26->setText(m_data->Outputs.Reject[26] ? "1" : "0");
		if (m_data->Outputs.Reject[26])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick26->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick26->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick26->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick26->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick26->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick26->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick26->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick26->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject27->setText(m_data->Outputs.Reject[27] ? "1" : "0");
		if (m_data->Outputs.Reject[27])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick27->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick27->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick27->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick27->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick27->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick27->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick27->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick27->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject28->setText(m_data->Outputs.Reject[28] ? "1" : "0");
		if (m_data->Outputs.Reject[28])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick28->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick28->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick28->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick28->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick28->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick28->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick28->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick28->blockSignals(false);
		}
		//((Ui::QtPLCDialogClass*)ui)->lE_Reject29->setText(m_data->Outputs.Reject[29] ? "1" : "0");
		if (m_data->Outputs.Reject[29])
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick29->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick29->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick29->setStyleSheet("background: rgb(0,255,0);font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick29->blockSignals(false);
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick29->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick29->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick29->setStyleSheet("font-size:20pt");
			((Ui::QtPLCDialogClass*)ui)->pb_cmdTestKick29->blockSignals(false);
		}
	}
}


// MESSAGE_HANDLER QtPLCDialogClass::ShowFunc(void* context, DataToPC_typ)
// {
// 	return MESSAGE_HANDLER();
// }



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

void QtPLCDialogClass::SetSocket(QtSocket_Class *sc)
{
	m_socket = sc;
	bool b = connect(m_socket, SIGNAL(signal_FROMPLC(void*, int, int, int, int)), this, SLOT(getPLCData(void*, int, int, int, int)));

	//	m_socket->set_message_handler(&message_handler, this);//全局
}

void QtPLCDialogClass::connectBtnGroup()//键盘弹出
{
	connect(((Ui::QtPLCDialogClass*)ui)->buttonGroup_Keyboard, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),
		[=](QAbstractButton* button) {
		if (button->objectName() == "pushButton_1") { keybd_event(0x31, 0, 0, 0); keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0); }
		if (button->objectName() == "pushButton_2") { keybd_event(0x32, 0, 0, 0); keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0); }
		if (button->objectName() == "pushButton_3") { keybd_event(0x33, 0, 0, 0); keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0); }
		if (button->objectName() == "pushButton_4") { keybd_event(0x34, 0, 0, 0); keybd_event(0x34, 0, KEYEVENTF_KEYUP, 0); }
		if (button->objectName() == "pushButton_5") { keybd_event(0x35, 0, 0, 0); keybd_event(0x35, 0, KEYEVENTF_KEYUP, 0); }
		if (button->objectName() == "pushButton_6") { keybd_event(0x36, 0, 0, 0); keybd_event(0x36, 0, KEYEVENTF_KEYUP, 0); }
		if (button->objectName() == "pushButton_7") { keybd_event(0x37, 0, 0, 0); keybd_event(0x37, 0, KEYEVENTF_KEYUP, 0); }
		if (button->objectName() == "pushButton_8") { keybd_event(0x38, 0, 0, 0); keybd_event(0x38, 0, KEYEVENTF_KEYUP, 0); }
		if (button->objectName() == "pushButton_9") { keybd_event(0x39, 0, 0, 0); keybd_event(0x39, 0, KEYEVENTF_KEYUP, 0); }
		if (button->objectName() == "pushButton_10") { keybd_event(0x30, 0, 0, 0); keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0); }
		if (button->objectName() == "pushButton_11") { keybd_event(0xBE, 0, 0, 0); keybd_event(0xBE, 0, KEYEVENTF_KEYUP, 0); }
		if (button->objectName() == "pushButton_14") { keybd_event(0x6D, 0, 0, 0); keybd_event(0x6D, 0, KEYEVENTF_KEYUP, 0); }
		if (button->objectName() == "pushButton_12") { keybd_event(0x08, 0, 0, 0); keybd_event(0x08, 0, KEYEVENTF_KEYUP, 0); }

	});

}

void QtPLCDialogClass::setm_iCameraTotal(int index)
{
}
