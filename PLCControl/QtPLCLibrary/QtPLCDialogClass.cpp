#include "QtPLCDialogClass.h"
#include "ui_QtPLCDialogClass.h"
#include <QPropertyAnimation>
#include <QFont>
#include <QBitmap>
#include <QPainter>
#include "mypushbutton.h"

QtPLCDialogClass::QtPLCDialogClass(QDialog *parent)
	: QDialog(parent)
{
	ui = new Ui::QtPLCDialogClass();
	((Ui::QtPLCDialogClass*)ui)->setupUi(this);
	((Ui::QtPLCDialogClass*)ui)->frame->move(0, 0);
	initFont();
	initDlg();
	initUI();
	initMovie();
	inittabicon();
	m_data = new DataToPC_typ;
	memset(m_data, 0, sizeof(DataToPC_typ));//主界面用

	((Ui::QtPLCDialogClass*)ui)->lb_logo->setPixmap(QPixmap(AppPath + "/ico/dr-pharmTrans_2.png"));
	((Ui::QtPLCDialogClass*)ui)->lb_logo->setScaledContents(true);
	//设置

	((Ui::QtPLCDialogClass*)ui)->pB_SetUp->setFixedSize(347, 99);
	((Ui::QtPLCDialogClass*)ui)->pB_SetUp->setStyleSheet("QPushButton{border:0px;}");
	QPixmap pix;
	bool ret = pix.load(AppPath + "/ico/sznt.png");
	((Ui::QtPLCDialogClass*)ui)->pB_SetUp->setIcon(pix);
	((Ui::QtPLCDialogClass*)ui)->pB_SetUp->setIconSize(QSize(347, 99));
	((Ui::QtPLCDialogClass*)ui)->pB_SetUp->move(15, 10);

	((Ui::QtPLCDialogClass*)ui)->pB_dtDlg->setFixedSize(170, 140);
	((Ui::QtPLCDialogClass*)ui)->pB_dtDlg->setStyleSheet("QPushButton{border:0px;}");
	ret = pix.load(AppPath + "/ico/data2.png");
	((Ui::QtPLCDialogClass*)ui)->pB_dtDlg->setIcon(pix);
	((Ui::QtPLCDialogClass*)ui)->pB_dtDlg->setIconSize(QSize(170, 140));
	((Ui::QtPLCDialogClass*)ui)->pB_dtDlg->move(640, 575);

	MyPushButton * AlarmResetBtn = new MyPushButton(AppPath + "/ico/bjfwnt.png", AppPath + "/ico/bjfw.png",347, 99);
	AlarmResetBtn->setParent(((Ui::QtPLCDialogClass*)ui)->frame_20);
	AlarmResetBtn->move(15, 120);
	connect(AlarmResetBtn, &MyPushButton::clicked, [=]() {
		on_pB_cmdAlarmReset_clicked(); });

	AlarmResetBtn = new MyPushButton(AppPath + "/ico/qkjnnt.png", AppPath + "/ico/qkjn.png", 347, 99);
	AlarmResetBtn->setParent(((Ui::QtPLCDialogClass*)ui)->frame_20);
	AlarmResetBtn->move(15, 230);
	connect(AlarmResetBtn, &MyPushButton::clicked, [=]() {
		on_pB_cmdCapClean_clicked();});

	AlarmResetBtn = new MyPushButton(AppPath + "/ico/jsqlnt.png", AppPath + "/ico/jsql.png", 347, 99);
	AlarmResetBtn->setParent(((Ui::QtPLCDialogClass*)ui)->frame_20);
	AlarmResetBtn->move(15, 340);
	connect(AlarmResetBtn, &MyPushButton::clicked, [=]() {
		on_pB_cmdCounterZero_clicked();});

	AlarmResetBtn = new MyPushButton(AppPath + "/ico/jtnt.png", AppPath + "/ico/jt.png", 347, 99);
	AlarmResetBtn->setParent(((Ui::QtPLCDialogClass*)ui)->frame_20);
	AlarmResetBtn->move(15, 450);
	connect(AlarmResetBtn, &MyPushButton::clicked, [=]() {
		//on_pB_cmdCounterZero_clicked();
		//做弹起特效
		//startBtn->zoom1();
		/*startBtn->zoom2();*/ });

		//开始

		((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->setFixedSize(347, 200);
		((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->setStyleSheet("QPushButton{border:0px;}");
		ret = pix.load(AppPath + "/ico/start.png");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->setIcon(pix);
		((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->setIconSize(QSize(347, 200));
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

	btnTimer = new QTimer();
	connect(btnTimer, SIGNAL(timeout()), this, SLOT(startMovie()));
}
QtPLCDialogClass::~QtPLCDialogClass()
{
	m_dtDlg->close();
	if (m_socket != nullptr)
	{
		//		m_socket->set_message_handler(nullptr, this);
	}
	//disconnect(this, SIGNAL(SHOWEVERYPLCVALUE(DataToPC_typ)), this, SLOT(getPLCData(DataToPC_typ)));
	bool b = disconnect(m_socket, SIGNAL(signal_FROMPLC(void*, int, int, int, int)), this, SLOT(getPLCData(void*, int, int, int, int)));

	if (btnTimer != nullptr)
	{
		delete btnTimer;
		btnTimer = nullptr;
	}

	if (m_data != nullptr)
	{
		delete m_data;
		m_data = nullptr;
	}
}

#pragma region ui stylesheet

void QtPLCDialogClass::initMovie()
{//创建动态对象
	{
		animation1 = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pB_cmdStart, "geometry");
		//设置动画时间间隔
		animation1->setDuration(200);

		//起始位置
		animation1->setStartValue(QRect(((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->x(), ((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->y(), ((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->width(), ((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->height()));
		//结束位置
		animation1->setEndValue(QRect(((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->x(), ((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->y() + 10, ((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->width(), ((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->height()));

		//设置弹跳曲线
		animation1->setEasingCurve(QEasingCurve::OutBounce);
	}
	{    //创建动态对象
		animation2 = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pB_cmdStart, "geometry");
		//设置动画时间间隔
		animation2->setDuration(200);

		//起始位置
		animation2->setStartValue(QRect(((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->x(), ((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->y() + 10, ((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->width(), ((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->height()));
		//结束位置
		animation2->setEndValue(QRect(((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->x(), ((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->y(), ((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->width(), ((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->height()));

		//设置弹跳曲线
		animation2->setEasingCurve(QEasingCurve::OutBounce);
	}
}
void QtPLCDialogClass::initUI()
{
	lb_dataNow = new QLabel(((Ui::QtPLCDialogClass*)ui)->frame);
	lb_dataNow->resize(140, 35);
	lb_dataNow->move(30, 16);
	lb_dataNow->setPixmap(QPixmap(AppPath + "/ico/fontImage/datanow.png"));
	lb_dataNow->setScaledContents(true);

	((Ui::QtPLCDialogClass*)ui)->label_15->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_15.png"));
	((Ui::QtPLCDialogClass*)ui)->label_15->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_18->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_18.png"));
	((Ui::QtPLCDialogClass*)ui)->label_18->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_78->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_78.png"));
	((Ui::QtPLCDialogClass*)ui)->label_78->setScaledContents(true);	((Ui::QtPLCDialogClass*)ui)->label_80->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_80.png"));
	((Ui::QtPLCDialogClass*)ui)->label_80->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_10->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_10.png"));
	((Ui::QtPLCDialogClass*)ui)->label_10->setScaledContents(true);	((Ui::QtPLCDialogClass*)ui)->label_39->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_39.png"));
	((Ui::QtPLCDialogClass*)ui)->label_39->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_49->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_49.png"));
	((Ui::QtPLCDialogClass*)ui)->label_49->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_16->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_16.png"));
	((Ui::QtPLCDialogClass*)ui)->label_16->setScaledContents(true);	((Ui::QtPLCDialogClass*)ui)->label_45->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_45.png"));
	((Ui::QtPLCDialogClass*)ui)->label_45->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_17->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_17.png"));
	((Ui::QtPLCDialogClass*)ui)->label_17->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_48->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_48.png"));
	((Ui::QtPLCDialogClass*)ui)->label_48->setScaledContents(true);	((Ui::QtPLCDialogClass*)ui)->label_43->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_43.png"));
	((Ui::QtPLCDialogClass*)ui)->label_43->setScaledContents(true);
}

void QtPLCDialogClass::inittabicon()
{
	((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setIconSize(QSize(160, 40));
	((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(0, QIcon(AppPath + "/ico/fontImage/xtjk.png"));
	((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(1, QIcon(AppPath + "/ico/fontImage/xtcs.png"));
	((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(2, QIcon(AppPath + "/ico/fontImage/yxcs.png"));
	((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(3, QIcon(AppPath + "/ico/fontImage/yxzt.png"));

	((Ui::QtPLCDialogClass*)ui)->tabWidget->setIconSize(QSize(140, 35));
	((Ui::QtPLCDialogClass*)ui)->tabWidget->setTabIcon(0, QIcon(AppPath + "/ico/fontImage/srsc.png"));
	((Ui::QtPLCDialogClass*)ui)->tabWidget->setTabIcon(1, QIcon(AppPath + "/ico/fontImage/xlxz.png"));
	((Ui::QtPLCDialogClass*)ui)->tabWidget->setTabIcon(2, QIcon(AppPath + "/ico/fontImage/czdy.png"));

}
void QtPLCDialogClass::initFont()
{
	setupFont.setFamily(QString::fromLocal8Bit("迷你简菱心"));
	setupFont.setPointSize(36);
	startFont.setFamily(QString::fromLocal8Bit("迷你简菱心"));
	startFont.setPointSize(60); 
	contentFont.setFamily(QString::fromLocal8Bit("宋体"));
	contentFont.setBold(true);
	contentFont.setPointSize(20);
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
void QtPLCDialogClass::SetSocket(QtSocket_Class *sc)
{
	m_socket = sc;
	bool b = connect(m_socket, SIGNAL(signal_FROMPLC(void*, int, int, int, int)), this, SLOT(getPLCData(void*, int, int, int, int)));
}
#pragma endregion

#pragma region data
DataFromPC_typ QtPLCDialogClass::getPCParaData()//2
{
	DataFromPC_typ tmp;
	memset(&tmp, 0, sizeof(DataFromPC_typ));
//	tmp.Machine_Para.enable = m_data->Machine_Para.enable;
	tmp.Machine_Para.s_trg_stop[0] = m_data->Machine_Para.s_trg_stop[0];
	tmp.Machine_Para.s_trg_stop[1] = m_data->Machine_Para.s_trg_stop[1];
	tmp.Machine_Para.FeedTimeOut = m_data->Machine_Para.FeedTimeOut;
	tmp.Machine_Para.CapPickInterval = m_data->Machine_Para.CapPickInterval;
	tmp.Machine_Para.CapBackInterval = m_data->Machine_Para.CapBackInterval;
	tmp.Machine_Para.TireDelay = m_data->Machine_Para.TireDelay;
	tmp.Machine_Para.ReadDelay = m_data->Machine_Para.ReadDelay;
	tmp.Machine_Para.TireWaitTime = m_data->Machine_Para.TireWaitTime;
	tmp.Machine_Para.StopSignalDelay = m_data->Machine_Para.StopSignalDelay;
	return tmp;
}
DataFromPC_typ QtPLCDialogClass::getPCRunData()//4
{
	DataFromPC_typ tmp;
	memset(&tmp, 0, sizeof(DataFromPC_typ));
	tmp.Run_Para.SysOveride = m_data->ActData.SysOveride;				//系统速度，0-10000对应0-100%
	tmp.Run_Para.PassCount = m_data->ActData.PassCount;				//通过计数
	tmp.Run_Para.RejectCount = m_data->ActData.RejectCount;			//剔废计数
	tmp.Run_Para.ProdCount = m_data->ActData.ProdCount;				//称重计数
	tmp.Run_Para.TOCount = m_data->ActData.TOCount;				//过重计数
	tmp.Run_Para.TUCount = m_data->ActData.TUCount;				//过轻计数
	tmp.Run_Para.TOverload = m_data->ActData.TOverload;				//超重重量,单位g
	tmp.Run_Para.TUnderload = m_data->ActData.TUnderload;				//超轻重量,单位g
	tmp.Run_Para.InterOverLoad = m_data->ActData.InterOverLoad;			//内控线，上限,单位g
	tmp.Run_Para.InterUnderLoad = m_data->ActData.InterUnderLoad;			//内控线，下限,单位g
	tmp.Run_Para.TDemand = m_data->ActData.TDemand;				//期望重量,单位g			
	tmp.Run_Para.TireMode = m_data->ActData.TireMode;				//0:每组去皮重,1:每次称重去皮重
	tmp.Run_Para.GroupSet = m_data->ActData.GroupSet;				//每组测试胶囊数量
	tmp.Run_Para.TestInterval = m_data->ActData.TestInterval;			//测试间隔时间,单位s
	tmp.Run_Para.BatchName[40] = m_data->ActData.BatchName[40];			//批号字符串
	tmp.Run_Para.GroupNo = m_data->ActData.GroupNo;				//当前组号
	tmp.Run_Para.Language = m_data->ActData.Language;				//当前语言，0：中文，1：英文
	tmp.Run_Para.UserAnalogoutput = m_data->ActData.UserAnalogoutput;		//用户模拟量输入
	tmp.Run_Para.Adjustvalue = m_data->ActData.Adjustvalue;			//自动调整系数
	tmp.Run_Para.DeltaInput = m_data->ActData.DeltaInput;				//装量调整偏差值
	tmp.Run_Para.sWAutoPrint = m_data->ActData.sWAutoPrint;			//自动打印，1:自动，0：手动

	return tmp;
}
void QtPLCDialogClass::getPLCData(void* data, int machinetype, int home, int kickOpen, int kickMode)
{
	memcpy(m_data, (DataToPC_typ*)data, sizeof(DataToPC_typ));//主界面用
	
	//运行数据
#pragma region run
	if (!((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->hasFocus())//系统速度，0-10000对应0-100%
	{
		((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->setText(QString::number(m_data->ActData.SysOveride));
		((Ui::QtPLCDialogClass*)ui)->lE_SysOveride_2->setText(QString::number(m_data->ActData.SysOveride));
	}	
	if (!((Ui::QtPLCDialogClass*)ui)->lE_PassCount->hasFocus())//通过计数
	{
		((Ui::QtPLCDialogClass*)ui)->lE_PassCount->setText(QString::number(m_data->ActData.PassCount));
	}	
	if (!((Ui::QtPLCDialogClass*)ui)->lE_RejectCount->hasFocus())//剔废计数
	{
		((Ui::QtPLCDialogClass*)ui)->lE_RejectCount->setText(QString::number(m_data->ActData.RejectCount));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_ProdCount->hasFocus())//称重计数
	{
		((Ui::QtPLCDialogClass*)ui)->lE_ProdCount->setText(QString::number(m_data->ActData.ProdCount));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TOCount->hasFocus())//过重计数,单位g
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TOCount->setText(QString::number(m_data->ActData.TOCount));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TUCount->hasFocus())//过轻计数,单位g
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TUCount->setText(QString::number(m_data->ActData.TUCount));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TOverload->hasFocus())//超重重量,单位g
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TOverload->setText(QString::number(m_data->ActData.TOverload));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->hasFocus())//超轻重量,单位g
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->setText(QString::number(m_data->ActData.TUnderload));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->hasFocus())//内控线，上限,单位g
	{
		((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->setText(QString::number(m_data->ActData.InterOverLoad));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->hasFocus())//内控线，下限,单位g
	{
		((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->setText(QString::number(m_data->ActData.InterUnderLoad));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TDemand->hasFocus())//期望重量, 单位g
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TDemand->setText(QString::number(m_data->ActData.TDemand));
	}	
	if (!((Ui::QtPLCDialogClass*)ui)->cB_TireMode->hasFocus())//0:每组去皮重,1:每次称重去皮重
	{
		((Ui::QtPLCDialogClass*)ui)->cB_TireMode->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->cB_TireMode->setCurrentIndex(m_data->ActData.TireMode);
		((Ui::QtPLCDialogClass*)ui)->cB_TireMode->blockSignals(false);
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->hasFocus())//每组测试胶囊数量
	{
		((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->setText(QString::number(m_data->ActData.GroupSet));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->hasFocus())////测试间隔时间,单位s
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->setText(QString::number(m_data->ActData.TestInterval));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_BatchName->hasFocus())//BatchName[40];			//批号字符串
	{
		((Ui::QtPLCDialogClass*)ui)->lE_BatchName->setText(m_data->ActData.BatchName);
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_GroupNo->hasFocus())//GroupNo;				//当前组号
	{
		((Ui::QtPLCDialogClass*)ui)->lE_GroupNo->setText(QString::number(m_data->ActData.GroupNo));
	}
	//int				Language;				//当前语言，0：中文，1：英文
	//float			UserAnalogoutput;		//用户模拟量输入
	//float			Adjustvalue;			//自动调整系数
	//unsigned int	DeltaInput;				//装量调整偏差值
	//int				cmdAutoPrint;			//自动打印，1:自动，0：手动
#pragma endregion
	//系统状态	
#pragma region status	
	((Ui::QtPLCDialogClass*)ui)->lE_Finished->setText(QString::number(m_data->Status.Finished));//本组结束
	((Ui::QtPLCDialogClass*)ui)->lE_GroupIndex->setText(QString::number(m_data->Status.GroupIndex));//本组序号
	((Ui::QtPLCDialogClass*)ui)->lE_Weight->setText(QString::number(m_data->Status.Weight));//本次重量
	((Ui::QtPLCDialogClass*)ui)->lE_ScaleResult->setText(QString::number(m_data->Status.ScaleResult));//天平当前读数，单位g
	((Ui::QtPLCDialogClass*)ui)->cB_ScaleStableState->setCurrentIndex(m_data->Status.ScaleStableState);//天平当前稳定状态,0:非常稳定,1:稳定,2:不稳定,3:非常不稳定

	//Group Data
	//Displaytyp			CapDataDisp;			//组数据

	((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedStep->setText(QString::number(m_data->Status.AxisFeedStep));			//下料电机状态机步骤
	((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedErrorNo->setText(QString::number(m_data->Status.AxisFeedErrorNo));		//下料电机错误代码
	((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedRelMovDistance->setText(QString::number(m_data->Status.AxisFeedRelMovDistance));	//下料电机相对运动距离，单位unit
	((Ui::QtPLCDialogClass*)ui)->lE_AxisSwingStep->setText(QString::number(m_data->Status.AxisSwingStep));			//旋转电机状态机步骤
	((Ui::QtPLCDialogClass*)ui)->lE_AxisSwingErrorNo->setText(QString::number(m_data->Status.AxisSwingErrorNo));		//旋转电机错误代码
	((Ui::QtPLCDialogClass*)ui)->lE_AxisSwingRelMovDistance->setText(QString::number(m_data->Status.AxisSwingRelMovDistance));//旋转电机相对运动距离，单位unit
	((Ui::QtPLCDialogClass*)ui)->lE_MachineStep->setText(QString::number(m_data->Status.MachineStep));			//系统运行状态机步骤
	((Ui::QtPLCDialogClass*)ui)->lE_TimeInterval->setText(QString::number(m_data->Status.TimeInterval));			//测量实际间隔时间
	((Ui::QtPLCDialogClass*)ui)->lE_AlarmStatus->setText(QString::number(m_data->Status.AlarmStatus));
	((Ui::QtPLCDialogClass*)ui)->lE_Alarm16->setText((char*)(m_data->Status.Alarm));
#pragma endregion
	//系统参数
#pragma region para
/*	if (!((Ui::QtPLCDialogClass*)ui)->cB_enable->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->cB_enable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->cB_enable->setCurrentIndex(m_data->Machine_Para.enable);
		((Ui::QtPLCDialogClass*)ui)->cB_enable->blockSignals(false);
	}*/	
	if (!((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop0->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop0->setText(QString::number(m_data->Machine_Para.s_trg_stop[0]));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop1->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop1->setText(QString::number(m_data->Machine_Para.s_trg_stop[1]));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->setText(QString::number(m_data->Machine_Para.FeedTimeOut));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->setText(QString::number(m_data->Machine_Para.CapPickInterval));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->setText(QString::number(m_data->Machine_Para.CapBackInterval / 100.0, 'f', 2));
	}	
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->setText(QString::number(m_data->Machine_Para.TireDelay / 100.0, 'f', 2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->setText(QString::number(m_data->Machine_Para.ReadDelay / 100.0, 'f', 2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->setText(QString::number(m_data->Machine_Para.TireWaitTime / 100.0, 'f', 2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->setText(QString::number(m_data->Machine_Para.StopSignalDelay));
	}
#pragma endregion
	//输入点
#pragma region input
	lb_01->setVisible(m_data->Inputs.FeedTrigger ? true : false);
	((Ui::QtPLCDialogClass*)ui)->lb_00->setVisible(m_data->Inputs.FeedTrigger ? false : true);
	lb_11->setVisible(m_data->Inputs.SwingTrigger ? true : false);
	((Ui::QtPLCDialogClass*)ui)->lb_10->setVisible(m_data->Inputs.SwingTrigger ? false : true);
#pragma endregion
	//输出点
#pragma region output
	((Ui::QtPLCDialogClass*)ui)->lE_Analogoutput->setText(QString::number(m_data->Outputs.Analogoutput));		//模拟量输出
	if (m_data->Outputs.Reject)			//排废电磁铁
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
	if (m_data->Outputs.ChannelSwith)	//胶囊通道切换
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
	if (m_data->Outputs.Vaccum)//真空发生器
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
	if (m_data->Outputs.CapGet)//取料电磁铁
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
	if (m_data->Outputs.CapGetValve)//取料电磁阀
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
	if (m_data->Outputs.CapBackValve)//回料电磁阀
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
	if (m_data->Outputs.AlarmOut)//报警蜂鸣器
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
	if (m_data->Outputs.StopSignal)//停机信号
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
	if (m_data->Outputs.AlarmSignal)//报警输出
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
	if (m_data->Outputs.YellowAlarmout)//黄灯报警
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
	if (m_data->Outputs.Baffle)//挡板
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
	//bool		Photo;					//拍照
	//bool		Flash;					//闪光
#pragma endregion
}//PC显示数据
#pragma endregion
 
#pragma region popup window
void QtPLCDialogClass::initDlg()
{
	m_dtDlg = new QDialog();
	m_dtDlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
	m_dtDlg->setWindowIcon(QIcon(AppPath + "/ico/dr.ico"));
	m_dtDlg->setWindowTitle(QString::fromLocal8Bit("检测数据明细表"));
	connect(m_dtDlg, SIGNAL(rejected()), this, SLOT(dtClose()));
	m_dtDlg->move(15,15);
	m_dtDlg->resize(797, 550);
	QGridLayout *glayout = new QGridLayout(m_dtDlg);

	QLabel *lb = new QLabel();
	lb->setText(QString::fromLocal8Bit("每粒重量(g)："));
	glayout->addWidget(lb, 0, 0, 1, 3);
	
	int i = 0;
	for (;i<80;i++)
	{
		lb = new QLabel();
		lb->setObjectName(QString::number(i));
		lb->setFrameShape(QFrame::Panel);
		lb->setFrameShadow(QFrame::Raised);
		lb->setText("0.123");
		glayout->addWidget(lb, i/10+1, i%10+1, 1, 1);
		lb->setVisible(false);

	}
	lb = new QLabel();
	glayout->addWidget(lb, i++, 0, 1, 3);

	lb = new QLabel();
	lb->setText(QString::fromLocal8Bit("重量结果："));
	glayout->addWidget(lb, i++, 0, 1, 3);

	int j = 0;
	for (; j < 8; j++)
	{
		lb = new QLabel();
		lb->setObjectName("Cal" + QString::number(j));
		lb->setFrameShape(QFrame::Panel);
		lb->setFrameShadow(QFrame::Raised);
		lb->setText(QString::fromLocal8Bit("平均值(g)：") + "0.1236");
		glayout->addWidget(lb, j / 4 + i, j * 3 % 12, 1, 3);
		lb->setVisible(false);
	}

	lb = new QLabel();
	glayout->addWidget(lb, j / 4 + i + 1, 0, 1, 3);	
	lb = new QLabel();
	lb->setText(QString::fromLocal8Bit("更多数据信息请查看<打印预览>项..."));
	glayout->addWidget(lb, j / 4 + i + 2, 0, 1, 8);
}
void QtPLCDialogClass::setWindowMinimized()
{
	((Ui::QtPLCDialogClass*)ui)->pB_dtDlg->setChecked(false);
}

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

#pragma region ui run slots
void QtPLCDialogClass::on_lE_SysOveride_returnPressed()//系统速度，0-10000对应0-100%
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.Run_Para.SysOveride = ((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_RejectCount_returnPressed()//通过计数
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.Run_Para.RejectCount = ((Ui::QtPLCDialogClass*)ui)->lE_RejectCount->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_ProdCount_returnPressed()//称重计数
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.Run_Para.ProdCount = ((Ui::QtPLCDialogClass*)ui)->lE_ProdCount->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_TOCount_returnPressed()//过重计数
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.Run_Para.TOCount = ((Ui::QtPLCDialogClass*)ui)->lE_TOCount->text().toUInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_TUCount_returnPressed()//过轻计数
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.Run_Para.TUCount = ((Ui::QtPLCDialogClass*)ui)->lE_TUCount->text().toUInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_TOverload_returnPressed()//超重重量,单位g
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.Run_Para.TOverload = ((Ui::QtPLCDialogClass*)ui)->lE_TOverload->text().toFloat();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_TUnderload_returnPressed()//超轻重量,单位g
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.Run_Para.TUnderload = ((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->text().toFloat();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_InterOverLoad_returnPressed()//内控线，上限,单位g
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.Run_Para.InterOverLoad = ((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->text().toFloat();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_InterUnderLoad_returnPressed()//内控线，下限,单位g
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.Run_Para.InterUnderLoad = ((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->text().toFloat();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_TDemand_returnPressed()///期望重量,单位g	
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.Run_Para.TDemand = ((Ui::QtPLCDialogClass*)ui)->lE_TDemand->text().toFloat();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_cB_TireMode_currentIndexChanged(int index)//0:每组去皮重,1:每次称重去皮重
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 4;
	typ.Run_Para.TireMode = index;
	m_socket->Communicate_PLC(&typ, nullptr);
}

void QtPLCDialogClass::on_lE_GroupSet_returnPressed()///每组测试胶囊数量
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.Run_Para.GroupSet = ((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_TestInterval_returnPressed()///测试间隔时间,单位s
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.Run_Para.TestInterval = ((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_BatchName_returnPressed()//批号字符串
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	//typ.Run_Para.BatchName = (char*)(((Ui::QtPLCDialogClass*)ui)->lE_BatchName->text());
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_GroupNo_returnPressed()//当前组号,单位s
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.Run_Para.GroupNo = ((Ui::QtPLCDialogClass*)ui)->lE_GroupNo->text().toUInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}			
//int				Language;				//当前语言，0：中文，1：英文
//float			UserAnalogoutput;		//用户模拟量输入
//float			Adjustvalue;			//自动调整系数
//unsigned int	DeltaInput;				//装量调整偏差值
//int				cmdAutoPrint;			//自动打印，1:自动，0：手动
#pragma endregion

#pragma region ui para slots
//void QtPLCDialogClass::on_cB_enable_currentIndexChanged(int index)
//{
//	DataFromPC_typ typ;
//	typ = getPCParaData();
//	typ.Telegram_typ = 2;
//	typ.Machine_Para.enable = index;
//	m_socket->Communicate_PLC(&typ, nullptr);
//}
void QtPLCDialogClass::on_lE_s_trg_stop0_returnPressed()
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.s_trg_stop[0] = ((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop0->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_s_trg_stop1_returnPressed()
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.s_trg_stop[1] = ((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop1->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_FeedTimeOut_returnPressed()
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.FeedTimeOut = ((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_CapPickInterval_returnPressed()
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.CapPickInterval = ((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_CapBackInterval_returnPressed()
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.CapBackInterval = ((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_TireDelay_returnPressed()
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.TireDelay = ((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_ReadDelay_returnPressed()
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.ReadDelay = ((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_TireWaitTime_returnPressed()
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.TireWaitTime = ((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_StopSignalDelay_returnPressed()
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.StopSignalDelay = ((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}
#pragma endregion

#pragma region ui cmd slots
//DateTimeStructTyp		DateTimeSet;		//设定日期时间目标
//unsigned char		cmdChangeDT;					//修改日期时间,1:执行，自动复位
void QtPLCDialogClass::on_pB_cmdScaleRead_clicked()//秤读数命令,1:执行，自动复位
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdScaleRead = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdScaleTire_clicked()//秤清零,1:执行，自动复位
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdScaleTire = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdScaleSetStable_clicked()//设定秤稳定状态,1:执行，自动复位
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdScaleSetStable = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_cB_paraScaleSetStable_currentIndexChanged(int index)//稳定状态设定目标，0:非常稳定,1:稳定,2:不稳定,3:非常不稳定
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdScaleSetStable = index;
	m_socket->Communicate_PLC(&typ, nullptr);
}	
void QtPLCDialogClass::on_pB_cmdScaleCalibExt_clicked()//秤外部校正,1:执行，自动复位
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdScaleCalibExt = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisFeedJogPos_clicked()//下料正转点动，1:执行，0:停止
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisFeedJogPos = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisFeedJogNeg_clicked()//下料反转点动，1:执行，0:停止
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisFeedJogNeg = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}	
void QtPLCDialogClass::on_pB_cmdAxisFeedRelMov_clicked()//下料相对运动启动，1:执行，自动复位
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisFeedRelMov = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}	
void QtPLCDialogClass::on_pB_cmdAxisFeedPosMov_clicked()//下料正向连续运动启动，1:执行，自动复位
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisFeedPosMov = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisFeedStopMov_clicked()//下料停止运动，1:执行，自动复位
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisFeedPosMov = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}	
void QtPLCDialogClass::on_pB_cmdAxisSwingJogPos_clicked()//旋转正转点动，1:执行，0:停止
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisSwingJogPos = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}	
void QtPLCDialogClass::on_pB_cmdAxisSwingJogNeg_clicked()//旋转反转点动，1:执行，0:停止
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisSwingJogNeg = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}	
void QtPLCDialogClass::on_pB_cmdAxisSwingRelMov_clicked()//旋转相对运动启动，1:执行，自动复位
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisSwingRelMov = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}	
void QtPLCDialogClass::on_pB_cmdAxisSwingPosMov_clicked()//旋转正向连续运动启动，1:执行，自动复位
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisSwingPosMov = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisSwingStopMov_clicked()//旋转停止运动，1:执行，自动复位
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisSwingStopMov = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}	
void QtPLCDialogClass::on_pB_cmdFeedSingle_clicked()//单粒下料，1:执行，自动复位
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdFeedSingle = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}				
void QtPLCDialogClass::on_pB_cmdFeedSingleStop_clicked()//单粒下料停止，1:执行，自动复位
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdFeedSingleStop = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}					
void QtPLCDialogClass::on_pB_cmdSwing_clicked()//旋转单工位,1:执行，自动复位
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdSwing = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdStart_toggled(bool checked)//启动 停止
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	if (checked)
	{
		QPixmap pix;
		bool ret = pix.load(AppPath + "/ico/stop.png");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->setIcon(pix);
		((Ui::QtPLCDialogClass*)ui)->pB_SetUp->setEnabled(false);
		((Ui::QtPLCDialogClass*)ui)->lE_BatchName->setEnabled(false);
		typ.Machine_Cmd.cmdStart = 1;
		btnTimer->start(1);
	}
	else
	{
		QPixmap pix;
		bool ret = pix.load(AppPath + "/ico/start.png");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->setIcon(pix);
		((Ui::QtPLCDialogClass*)ui)->pB_SetUp->setEnabled(true);
		((Ui::QtPLCDialogClass*)ui)->lE_BatchName->setEnabled(true); 
		typ.Machine_Cmd.cmdStop = 1;
		btnTimer->start(1);
	}
	m_socket->Communicate_PLC(&typ, nullptr);
}
//unsigned char		cmdStart;						//启动称重，1:执行，自动复位
//unsigned char		cmdEStop;						//急停，1:执行，自动复位
//unsigned char		cmdStop;						//停止,1:执行，自动复位
//unsigned char		cmdInit;						//初始化，1:执行，自动复位
void QtPLCDialogClass::on_pB_cmdAlarmReset_clicked()
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAlarmReset = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdCounterZero_clicked()
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdCounterZero = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
//unsigned char		cmdPrintStart;					//启动打印,1:执行，自动复位
//unsigned char		cmdPrintStartE;					//启动英文打印，1:执行，自动复位
void QtPLCDialogClass::on_pB_cmdCapClean_clicked()
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdCapClean = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAlogtest_clicked()//模拟量输出测试,1:执行，自动复位
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdCapClean = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_SetUp_toggled(bool checked)//设置
{
	if (checked)
	{
		((Ui::QtPLCDialogClass*)ui)->frame->setVisible(false);
		QPixmap pix;
		bool ret = pix.load(AppPath + "/ico/sz.png");
		((Ui::QtPLCDialogClass*)ui)->pB_SetUp->setIcon(pix);
		((Ui::QtPLCDialogClass*)ui)->pB_SetUp->setIconSize(QSize(347, 99));
		((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->setEnabled(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->frame->setVisible(true);
		QPixmap pix;
		bool ret = pix.load(AppPath + "/ico/sznt.png");
		((Ui::QtPLCDialogClass*)ui)->pB_SetUp->setIcon(pix);
		((Ui::QtPLCDialogClass*)ui)->pB_SetUp->setIconSize(QSize(347, 99));
		((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->setEnabled(true);
	}
}
void QtPLCDialogClass::on_pB_dtDlg_toggled(bool checked)//数据dialog
{
	if (checked)
	{
		m_dtDlg->show();		
		QPixmap pix;
		bool ret = pix.load(AppPath + "/ico/data1.png");
		((Ui::QtPLCDialogClass*)ui)->pB_dtDlg->setIcon(pix);
		((Ui::QtPLCDialogClass*)ui)->pB_dtDlg->setIconSize(QSize(170, 140));
	}
	else
	{
		m_dtDlg->close();
		QPixmap pix;
		bool ret = pix.load(AppPath + "/ico/data2.png");
		((Ui::QtPLCDialogClass*)ui)->pB_dtDlg->setIcon(pix);
		((Ui::QtPLCDialogClass*)ui)->pB_dtDlg->setIconSize(QSize(170, 140));
	}
}
void QtPLCDialogClass::dtClose()
{
	((Ui::QtPLCDialogClass*)ui)->pB_dtDlg->setChecked(false);
}
void QtPLCDialogClass::startMovie()
{
	animation1->start();
	animation2->start();
	btnTimer->stop();
}
#pragma endregion

