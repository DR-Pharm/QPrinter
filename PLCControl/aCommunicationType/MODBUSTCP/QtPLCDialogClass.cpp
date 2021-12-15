#include "QtPLCDialogClass.h"
#include "ui_QtPLCDialogClass.h"
#include <QPropertyAnimation>
#include <QFont>
#include <QBitmap>
#include <QPainter>
#include "mypushbutton.h"
#include "Keyboard.h"
#include <QDesktopWidget>
#include "windows.h"
#include <QMovie>

QtPLCDialogClass::QtPLCDialogClass(QDialog *parent)
	: QDialog(parent)
{
	QDesktopWidget* w = QApplication::desktop();
	deskWidth = w->screenGeometry().width();
	deskHeight = w->screenGeometry().height();
	frmWidth = this->width();
	frmHeight = this->height();
	// 靠上居中显示
	movePoint = QPoint(deskWidth / 2 - frmWidth / 2, 0);
	key = new keyBoard();

	ui = new Ui::QtPLCDialogClass();
	setAttribute(Qt::WA_AcceptTouchEvents, true);

	((Ui::QtPLCDialogClass*)ui)->setupUi(this);

	QFile fl(AppPath + "/ico/PLC.qss");
	if (fl.open(QFile::ReadOnly))
	{
		QString ss = fl.readAll();
		setStyleSheet(ss);
		fl.close();
	}

	((Ui::QtPLCDialogClass*)ui)->pB_showPrt->setVisible(false);
	((Ui::QtPLCDialogClass*)ui)->pB_cmdAlogtest->setVisible(false);
	((Ui::QtPLCDialogClass*)ui)->frame->move(0, 0);

	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	lg = configIniRead.value("Language/currentLanguage", "").toInt();

	initFont();
	initDlg();
	initUI();
	initMovie();
	inittabicon();
	initUser();
	if (lg == 1) ChangeLanguage();
	m_data = new DataToPC_typ;
	memset(m_data, 0, sizeof(DataToPC_typ));//主界面用
	//int jdd = sizeof(m_data->ActData.BatchName);//40
	memset(m_data->ActData.BatchName, '\0', sizeof(m_data->ActData.BatchName));
	short za;
	int aaa = sizeof(za);
	DataToPC_typ dt1;
	int i = sizeof(dt1);							//712
	int i1 = sizeof(dt1.Telegram_typ);				//4
	int i2 = sizeof(dt1.ActData);					//236
	int i3 = sizeof(dt1.Status);					//264
	int i4 = sizeof(dt1.Machine_Para);				//124
	int i5 = sizeof(dt1.Inputs);					//2
	int i6 = sizeof(dt1.Outputs);					//18
	int i7 = sizeof(dt1.Reserve);					//64
													
	DataFromPC_typ dt2;								
	int j = sizeof(dt2);							//604
	int j1 = sizeof(dt2.Telegram_typ);				//4
	int j2 = sizeof(dt2.Machine_Para);				//124
	int j3 = sizeof(dt2.ActData);					//236
	int j4 = sizeof(dt2.Machine_Cmd);				//108
	int j5 = sizeof(dt2.PhotoResult);				//68
	int j6 = sizeof(dt2.Reserve);					//64

	float a;
	double b;
	int i22 = sizeof(a);
	int i33 = sizeof(b);
	((Ui::QtPLCDialogClass*)ui)->lb_logo->setPixmap(QPixmap(AppPath + "/ico/dr-pharmTrans_2.png"));
	((Ui::QtPLCDialogClass*)ui)->lb_logo->setScaledContents(true);
	//设置

	((Ui::QtPLCDialogClass*)ui)->pB_SetUpcheckable->setFixedSize(347, 99);
	((Ui::QtPLCDialogClass*)ui)->pB_SetUpcheckable->setStyleSheet("QPushButton{border:0px;}");
	QPixmap pix;
	bool ret;
	if (lg == 0) ret = pix.load(AppPath + "/ico/sznt.png");
	if (lg == 1) ret = pix.load(AppPath + "/ico/E/sznt.png");
	((Ui::QtPLCDialogClass*)ui)->pB_SetUpcheckable->setIcon(pix);
	((Ui::QtPLCDialogClass*)ui)->pB_SetUpcheckable->setIconSize(QSize(347, 99));
	int firstl = 20;
	int offsetx = 15;
	int offsety = 105;
	((Ui::QtPLCDialogClass*)ui)->pB_SetUpcheckable->move(offsetx, firstl);
	int icszx = 230;
	int icsxy = 200;
	((Ui::QtPLCDialogClass*)ui)->pB_dtDlgcheckable->setFixedSize(icszx, icsxy);
	((Ui::QtPLCDialogClass*)ui)->pB_dtDlgcheckable->setStyleSheet("\
		QPushButton\
		{\
		border:0px;\
		}\
		QPushButton::checked\
		{\
		Padding-left:0px;\
		Padding-top:0px;\
		}");

	if (lg == 0) pix.load(AppPath + "/ico/data2.png");
	if (lg == 1) pix.load(AppPath + "/ico/E/data2.png");
	((Ui::QtPLCDialogClass*)ui)->pB_dtDlgcheckable->setIcon(pix);
	((Ui::QtPLCDialogClass*)ui)->pB_dtDlgcheckable->setIconSize(QSize(icszx, icsxy));
	((Ui::QtPLCDialogClass*)ui)->pB_dtDlgcheckable->move(650, 580);

	MyPushButton * AlarmResetBtn;
	if (lg == 0) AlarmResetBtn = new MyPushButton(AppPath + "/ico/bjfwnt.png", AppPath + "/ico/bjfw.png", 347, 99);
	if (lg == 1) AlarmResetBtn = new MyPushButton(AppPath + "/ico/E/bjfwnt.png", AppPath + "/ico/E/bjfw.png", 347, 99);
	AlarmResetBtn->setParent(((Ui::QtPLCDialogClass*)ui)->frame_20);
	AlarmResetBtn->move(offsetx, firstl+offsety);
	connect(AlarmResetBtn, &MyPushButton::clicked, [=]() {
		pB_cmdAlarmReset(); });

	if (lg == 0) AlarmResetBtn = new MyPushButton(AppPath + "/ico/jsqlnt.png", AppPath + "/ico/jsql.png", 347, 99);
	if (lg == 1) AlarmResetBtn = new MyPushButton(AppPath + "/ico/E/jsqlnt.png", AppPath + "/ico/E/jsql.png", 347, 99);
	AlarmResetBtn->setParent(((Ui::QtPLCDialogClass*)ui)->frame_20);
	AlarmResetBtn->move(offsetx, firstl + 2 * offsety);
	connect(AlarmResetBtn, &MyPushButton::clicked, [=]() {
		pB_cmdCounterZero(); });

	if (lg == 0) LanguageBtn = new MyPushButton(AppPath + "/ico/languageCNnt.png", AppPath + "/ico/languageCN.png", 347, 99);
	if (lg == 1) LanguageBtn = new MyPushButton(AppPath + "/ico/E/languageCNnt.png", AppPath + "/ico/E/languageCN.png", 347, 99);
	LanguageBtn->setParent(((Ui::QtPLCDialogClass*)ui)->frame_20);
	LanguageBtn->move(offsetx, firstl + 3 * offsety);
	connect(LanguageBtn, &MyPushButton::clicked, [=]() {
		pB_ChangeLanguage(); });

	if (lg == 0) ExitBtn = new MyPushButton(AppPath + "/ico/exitnt.png", AppPath + "/ico/exit.png", 347, 99);
	if (lg == 1) ExitBtn = new MyPushButton(AppPath + "/ico/E/exitnt.png", AppPath + "/ico/E/exit.png", 347, 99);
	ExitBtn->setParent(((Ui::QtPLCDialogClass*)ui)->frame_20);
	ExitBtn->move(offsetx, firstl + 4 * offsety);
	connect(ExitBtn, &MyPushButton::clicked, [=]() {
		emit CLOSESIGNAL(); });
	//AlarmResetBtn = new MyPushButton(AppPath + "/ico/jtnt.png", AppPath + "/ico/jt.png", 347, 99);
	/*AlarmResetBtn = new MyPushButton(AppPath + "/ico/dr_keyboard.ico", AppPath + "/ico/dr_keyboard.ico", 347, 99);
	AlarmResetBtn->setParent(((Ui::QtPLCDialogClass*)ui)->frame_20);
	AlarmResetBtn->setFocusPolicy(Qt::NoFocus);
	AlarmResetBtn->move(15, 450);
	connect(AlarmResetBtn, &MyPushButton::clicked, [=]() {
		if (key == nullptr) key = new keyBoard(this);

		key->move(movePoint);
		key->repaint();
		key->show();});
		*/

	m_Input_Bufer[0] = 0;
	m_Coils_Bufer[0] = 0;
	dtcoils = new quint8[COILS];
	memset(dtcoils, 0, COILS);
	dtregisters = new quint16[REGISTERS];
	memset(dtregisters, 0, REGISTERS*2);
	//开始

	((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setFixedSize(380, 230);
	((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setStyleSheet("QPushButton{border:0px;}");
	if (lg == 0) ret = pix.load(AppPath + "/ico/start.png");
	if (lg == 1) ret = pix.load(AppPath + "/ico/E/start.png");

	((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setIcon(pix);
	((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setIconSize(QSize(380, 230));
	((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setEnabled(false);
	((Ui::QtPLCDialogClass*)ui)->lb_Alarm->setStyleSheet("color: rgb(255, 0,0);font-size:20pt");
	if (lg == 0) ((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("设备未就绪~");
	if (lg == 1) ((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("Not Ready~");
	//指示灯部分
	((Ui::QtPLCDialogClass*)ui)->lb_00->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));
	((Ui::QtPLCDialogClass*)ui)->lb_10->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));
	((Ui::QtPLCDialogClass*)ui)->lb_20->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));
	((Ui::QtPLCDialogClass*)ui)->lb_30->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));
	((Ui::QtPLCDialogClass*)ui)->lb_40->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));
	((Ui::QtPLCDialogClass*)ui)->lb_60->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));

	btnTimer = new QTimer();
	connect(btnTimer, SIGNAL(timeout()), this, SLOT(startMovie()));

	((Ui::QtPLCDialogClass*)ui)->widget_cv->move(0, 0);
	((Ui::QtPLCDialogClass*)ui)->widget_cv->setVisible(false);
	initChartOne();
	QStringList str1;
	if (lg == 0) str1 << QString::fromLocal8Bit("重量(g)") << QString::fromLocal8Bit("厚度(mm)") << QString::fromLocal8Bit("硬度(Kg)");
	if (lg == 1) str1 << "Weight" << "Thickness" << "Hardness";
	((Ui::QtPLCDialogClass*)ui)->tableWidget->setColumnCount(3);
	((Ui::QtPLCDialogClass*)ui)->tableWidget->setHorizontalHeaderLabels(str1);//加水平表头 每行加日期结果
	((Ui::QtPLCDialogClass*)ui)->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//均分填充表头

	((Ui::QtPLCDialogClass*)ui)->lW_data->setVisible(false);
	/*dtCurve = new DataCurve();	
	connect(dtCurve, SIGNAL(rejected()), this, SLOT(dtClose()));
	connect(this, SIGNAL(TODATACURVE(int,float, float, float, QList<qreal>)), dtCurve, SLOT(dataReceived(int, float, float, float, QList<qreal>)));
	dtCurve->move(0, 0);*/
	//dtCurve->setFixedSize(QSize(860, 755));//1280 800

	QList<QPushButton*> btnList = this->findChildren<QPushButton*>();
	for (int i = 0; i < btnList.size(); i++)
	{
		if (!btnList[i]->objectName().contains("checkable"))
		{
			connect(btnList[i], SIGNAL(toggled(bool)), this, SLOT(on_Input(bool)));
		}
	}
	((Ui::QtPLCDialogClass*)ui)->label_57->setVisible(false);
	((Ui::QtPLCDialogClass*)ui)->lE_FeedOveride->setVisible(false);
	((Ui::QtPLCDialogClass*)ui)->label_10->setVisible(false);
	((Ui::QtPLCDialogClass*)ui)->lE_PassCount->setVisible(false);
	((Ui::QtPLCDialogClass*)ui)->label_62->setVisible(false);
	((Ui::QtPLCDialogClass*)ui)->lE_MultiCount->setVisible(false);
	((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedAmount->setVisible(false);
	((Ui::QtPLCDialogClass*)ui)->pB_enTMUcheckable->setVisible(false);
	((Ui::QtPLCDialogClass*)ui)->pB_enHMUcheckable->setVisible(false);

	sp = AppPath + "/ico/beijing2.jpg";
	QLabel *lbDr = new QLabel(((Ui::QtPLCDialogClass*)ui)->frame);
	lbDr->resize(1280, 800);
	lbDr->move(0, 0);
	lbDr->setPixmap(QPixmap(sp));
	lbDr->setScaledContents(true);
	lbDr->setAttribute(Qt::WA_TransparentForMouseEvents);
	lbDr->lower();

	lbDr = new QLabel(((Ui::QtPLCDialogClass*)ui)->frame_20);
	lbDr->resize(1280, 800);
	lbDr->move(-904, 0);
	lbDr->setPixmap(QPixmap(sp));
	lbDr->setScaledContents(true);
	lbDr->setAttribute(Qt::WA_TransparentForMouseEvents);
	lbDr->lower();

	lbDr = new QLabel(((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC);
	lbDr->resize(1280, 800);
	lbDr->move(0, 0);
	lbDr->setPixmap(QPixmap(sp));
	lbDr->setScaledContents(true);
	lbDr->setAttribute(Qt::WA_TransparentForMouseEvents);
	lbDr->lower();

	lbDr = new QLabel(((Ui::QtPLCDialogClass*)ui)->tabWidget_Users);
	lbDr->resize(1280, 800);
	lbDr->move(-10, -60);
	lbDr->setPixmap(QPixmap(sp));
	lbDr->setScaledContents(true);
	lbDr->setAttribute(Qt::WA_TransparentForMouseEvents);
	lbDr->lower();
	
	lbDr = new QLabel(((Ui::QtPLCDialogClass*)ui)->tabWidget);
	lbDr->resize(1280, 800);
	lbDr->move(-9, -49);
	lbDr->setPixmap(QPixmap(sp));
	lbDr->setScaledContents(true);
	lbDr->setAttribute(Qt::WA_TransparentForMouseEvents);
	lbDr->lower();

	

	((Ui::QtPLCDialogClass*)ui)->label_us->setPixmap(AppPath + "/ico/us.png");
	((Ui::QtPLCDialogClass*)ui)->label_us->setScaledContents(true);

	((Ui::QtPLCDialogClass*)ui)->lb_search->setPixmap(AppPath + "/ico/fangdajing.png");
	((Ui::QtPLCDialogClass*)ui)->lb_search->setScaledContents(true); 
	((Ui::QtPLCDialogClass*)ui)->lb_search->setVisible(false);

	lbDr = new QLabel(((Ui::QtPLCDialogClass*)ui)->widget_cv);
	lbDr->resize(1280, 800);
	lbDr->move(0, 0);
	lbDr->setPixmap(QPixmap(sp));
	lbDr->setScaledContents(true);
	lbDr->setAttribute(Qt::WA_TransparentForMouseEvents);
	lbDr->lower();
}

QtPLCDialogClass::~QtPLCDialogClass()
{
	if (m_socket != nullptr)
	{
		//		m_socket->set_message_handler(nullptr, this);
	}
	//disconnect(this, SIGNAL(SHOWEVERYPLCVALUE(DataToPC_typ)), this, SLOT(getPLCData(DataToPC_typ)));
	bool b = disconnect(m_socket, SIGNAL(signal_FROMPLC(void*)), this, SLOT(getPLCData(void*)));
	b = disconnect(m_socket, SIGNAL(signal_FROMPLCHLODING(void*)), this, SLOT(getPLCHolding(void*)));//();
	b = disconnect(m_socket, SIGNAL(WRITECOILS()), this, SLOT(on_WriteCoils()));
	b = disconnect(m_socket, SIGNAL(WRITEHOLDINGREGISTERS()), this, SLOT(on_WriteHolding()));
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
bool QtPLCDialogClass::event(QEvent *event)
{

	switch (event->type())
	{
	case QEvent::TouchBegin:
	{
		QTouchEvent* touch = static_cast<QTouchEvent*>(event);
		QList<QTouchEvent::TouchPoint> touch_list = touch->touchPoints();
		float xf = touch_list.at(0).lastScreenPos().x();
		float yf = touch_list.at(0).lastScreenPos().y();
		int x = QString::number(xf, 'f', 0).toInt();
		int y = QString::number(yf, 'f', 0).toInt();

		/*((Ui::QtPLCDialogClass*)ui)->lb_x->setText("X:" + QString::number(x));
		((Ui::QtPLCDialogClass*)ui)->lb_y->setText("Y:" + QString::number(y));*/

		int xl, yl, xr, yr;

		xl = ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedJogPos->mapToGlobal(QPoint(0, 0)).x();
		xr = ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedJogPos->mapToGlobal(QPoint(0, 0)).x() + ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedJogPos->width();
		yl = ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedJogPos->mapToGlobal(QPoint(0, 0)).y();
		yr = ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedJogPos->mapToGlobal(QPoint(0, 0)).y() + ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedJogPos->height();

		if (((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedJogPos->hasFocus()
			&& x >= xl && x <= xr && y >= yl && y <= yr)
		{
			m_flag = axis_fun_axis0_com_jog_pos;
			m_iDontReadCoilsFlag = 1;
			m_str_sendCoils.replace(axis_fun_axis0_com_jog_pos, 1, "1");
			event->accept();
			return true;
		}
		xl = ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedJogNeg->mapToGlobal(QPoint(0, 0)).x();
		xr = ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedJogNeg->mapToGlobal(QPoint(0, 0)).x() + ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedJogNeg->width();
		yl = ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedJogNeg->mapToGlobal(QPoint(0, 0)).y();
		yr = ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedJogNeg->mapToGlobal(QPoint(0, 0)).y() + ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedJogNeg->height();

		if (((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedJogNeg->hasFocus()
			&& x >= xl && x <= xr && y >= yl && y <= yr)
		{
			m_flag = axis_fun_axis0_com_jog_neg;
			m_iDontReadCoilsFlag = 1;
			m_str_sendCoils.replace(axis_fun_axis0_com_jog_neg, 1, "1");
			event->accept();
			return true;
		}
		xl = ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingJogPos->mapToGlobal(QPoint(0, 0)).x();
		xr = ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingJogPos->mapToGlobal(QPoint(0, 0)).x() + ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingJogPos->width();
		yl = ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingJogPos->mapToGlobal(QPoint(0, 0)).y();
		yr = ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingJogPos->mapToGlobal(QPoint(0, 0)).y() + ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingJogPos->height();

		if (((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingJogPos->hasFocus()
			&& x >= xl && x <= xr && y >= yl && y <= yr)
		{
			m_flag = axis_fun_axis1_com_jog_pos;
			m_iDontReadCoilsFlag = 1;
			m_str_sendCoils.replace(axis_fun_axis1_com_jog_pos, 1, "1");
			event->accept();
			return true;
		}
		xl = ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingJogNeg->mapToGlobal(QPoint(0, 0)).x();
		xr = ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingJogNeg->mapToGlobal(QPoint(0, 0)).x() + ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingJogNeg->width();
		yl = ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingJogNeg->mapToGlobal(QPoint(0, 0)).y();
		yr = ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingJogNeg->mapToGlobal(QPoint(0, 0)).y() + ((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingJogNeg->height();

		if (((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingJogNeg->hasFocus()
			&& x >= xl && x <= xr && y >= yl && y <= yr)
		{
			m_flag = axis_fun_axis1_com_jog_neg;
			m_iDontReadCoilsFlag = 1;
			m_str_sendCoils.replace(axis_fun_axis1_com_jog_neg, 1, "1");
			event->accept();
			return true;
		}

		xl = ((Ui::QtPLCDialogClass*)ui)->pB_cmdRollingOverNeg->mapToGlobal(QPoint(0, 0)).x();
		xr = ((Ui::QtPLCDialogClass*)ui)->pB_cmdRollingOverNeg->mapToGlobal(QPoint(0, 0)).x() + ((Ui::QtPLCDialogClass*)ui)->pB_cmdRollingOverNeg->width();
		yl = ((Ui::QtPLCDialogClass*)ui)->pB_cmdRollingOverNeg->mapToGlobal(QPoint(0, 0)).y();
		yr = ((Ui::QtPLCDialogClass*)ui)->pB_cmdRollingOverNeg->mapToGlobal(QPoint(0, 0)).y() + ((Ui::QtPLCDialogClass*)ui)->pB_cmdRollingOverNeg->height();

		if (((Ui::QtPLCDialogClass*)ui)->pB_cmdRollingOverNeg->hasFocus()
			&& x >= xl && x <= xr && y >= yl && y <= yr)
		{
			m_flag = axis_fun_axis2_com_jog_neg;

			m_iDontReadCoilsFlag = 1;
			m_str_sendCoils.replace(axis_fun_axis2_com_jog_neg, 1, "1");
			event->accept();
			return true;
		}		
		
		xl = ((Ui::QtPLCDialogClass*)ui)->pB_cmdRollingOverPos->mapToGlobal(QPoint(0, 0)).x();
		xr = ((Ui::QtPLCDialogClass*)ui)->pB_cmdRollingOverPos->mapToGlobal(QPoint(0, 0)).x() + ((Ui::QtPLCDialogClass*)ui)->pB_cmdRollingOverPos->width();
		yl = ((Ui::QtPLCDialogClass*)ui)->pB_cmdRollingOverPos->mapToGlobal(QPoint(0, 0)).y();
		yr = ((Ui::QtPLCDialogClass*)ui)->pB_cmdRollingOverPos->mapToGlobal(QPoint(0, 0)).y() + ((Ui::QtPLCDialogClass*)ui)->pB_cmdRollingOverPos->height();

		if (((Ui::QtPLCDialogClass*)ui)->pB_cmdRollingOverPos->hasFocus()
			&& x >= xl && x <= xr && y >= yl && y <= yr)
		{
			m_flag = axis_fun_axis2_com_jog_pos;

			m_iDontReadCoilsFlag = 1;
			m_str_sendCoils.replace(axis_fun_axis2_com_jog_pos, 1, "1");
			event->accept();
			return true;
		}

		xl = ((Ui::QtPLCDialogClass*)ui)->pB_cmdPushNeg->mapToGlobal(QPoint(0, 0)).x();
		xr = ((Ui::QtPLCDialogClass*)ui)->pB_cmdPushNeg->mapToGlobal(QPoint(0, 0)).x() + ((Ui::QtPLCDialogClass*)ui)->pB_cmdPushNeg->width();
		yl = ((Ui::QtPLCDialogClass*)ui)->pB_cmdPushNeg->mapToGlobal(QPoint(0, 0)).y();
		yr = ((Ui::QtPLCDialogClass*)ui)->pB_cmdPushNeg->mapToGlobal(QPoint(0, 0)).y() + ((Ui::QtPLCDialogClass*)ui)->pB_cmdPushNeg->height();

		if (((Ui::QtPLCDialogClass*)ui)->pB_cmdPushNeg->hasFocus()
			&& x >= xl && x <= xr && y >= yl && y <= yr)
		{
			m_flag = axis_fun_axis3_com_jog_neg; 

			m_iDontReadCoilsFlag = 1;
			m_str_sendCoils.replace(axis_fun_axis3_com_jog_neg, 1, "1");
			event->accept();
			return true;
		}

		xl = ((Ui::QtPLCDialogClass*)ui)->pB_cmdPushPos->mapToGlobal(QPoint(0, 0)).x();
		xr = ((Ui::QtPLCDialogClass*)ui)->pB_cmdPushPos->mapToGlobal(QPoint(0, 0)).x() + ((Ui::QtPLCDialogClass*)ui)->pB_cmdPushPos->width();
		yl = ((Ui::QtPLCDialogClass*)ui)->pB_cmdPushPos->mapToGlobal(QPoint(0, 0)).y();
		yr = ((Ui::QtPLCDialogClass*)ui)->pB_cmdPushPos->mapToGlobal(QPoint(0, 0)).y() + ((Ui::QtPLCDialogClass*)ui)->pB_cmdPushPos->height();

		if (((Ui::QtPLCDialogClass*)ui)->pB_cmdPushPos->hasFocus()
			&& x >= xl && x <= xr && y >= yl && y <= yr)
		{
			m_flag = axis_fun_axis3_com_jog_pos;

			m_iDontReadCoilsFlag = 1;
			m_str_sendCoils.replace(axis_fun_axis3_com_jog_pos, 1, "1");
		}
		event->accept(); 
		return true;

	}
	case QEvent::TouchUpdate:
	{
		QTouchEvent* touch = static_cast<QTouchEvent*>(event);

		QList<QTouchEvent::TouchPoint> touch_list = touch->touchPoints();
		float x = touch_list.at(0).lastScreenPos().x();
		float y = touch_list.at(0).lastScreenPos().y();
		if (touch->touchPointStates() & Qt::TouchPointPressed) {
			//判断是否有触摸点处于TouchPointPressed或TouchPointMoved或TouchPointStationary或TouchPointReleased
			
		}
		event->accept();
		return true;
	}
	case QEvent::TouchEnd:
	{
		QTouchEvent* touch = static_cast<QTouchEvent*>(event);
		if (m_flag == axis_fun_axis3_com_jog_pos)
		{
			m_iDontReadCoilsFlag = 1; 
			m_str_sendCoils.replace(axis_fun_axis3_com_jog_pos, 1, "0");
		}
		else if (m_flag == axis_fun_axis3_com_jog_neg) 
		{

			m_iDontReadCoilsFlag = 1; 
			m_str_sendCoils.replace(axis_fun_axis3_com_jog_neg, 1, "0");
		}
		else if (m_flag == axis_fun_axis2_com_jog_pos) 
		{
			m_iDontReadCoilsFlag = 1;
			m_str_sendCoils.replace(axis_fun_axis2_com_jog_pos, 1, "0");
		}
		else if (m_flag == axis_fun_axis2_com_jog_neg) 
		{
			m_iDontReadCoilsFlag = 1;
			m_str_sendCoils.replace(axis_fun_axis2_com_jog_neg, 1, "0");
		}
		else if (m_flag == axis_fun_axis1_com_jog_neg) 
		{
			m_iDontReadCoilsFlag = 1;
			m_str_sendCoils.replace(axis_fun_axis1_com_jog_neg, 1, "0");
		}
		else if (m_flag == axis_fun_axis1_com_jog_pos) 
		{
			m_iDontReadCoilsFlag = 1;
			m_str_sendCoils.replace(axis_fun_axis1_com_jog_pos, 1, "0");
		}
		else if (m_flag == axis_fun_axis0_com_jog_neg)
		{ 
			m_iDontReadCoilsFlag = 1; 
			m_str_sendCoils.replace(axis_fun_axis0_com_jog_neg, 1, "0");
		}
		else if (m_flag == axis_fun_axis0_com_jog_pos)
		{
			m_iDontReadCoilsFlag = 1;
			m_str_sendCoils.replace(axis_fun_axis0_com_jog_pos, 1, "0");
		}

		if (m_flag!=0)
		{		
			m_flag = 0;
		}
		event->accept();
		return true;
	}
	return QWidget::event(event);
	}
	return false;
}
#pragma region ui stylesheet

void QtPLCDialogClass::initUser()
{
	initTableOfUserPermission();
	checkPermission();//查看权限部分

	initTableWidget();

	connect(((Ui::QtPLCDialogClass*)ui)->cB_Users, SIGNAL(currentTextChanged(const QString)), this, SLOT(updateCheckPermission(const QString)));
	connect(((Ui::QtPLCDialogClass*)ui)->tabWidget_Users, SIGNAL(currentChanged(int)), this, SLOT(btn_Enabled(int)));

	connect(((Ui::QtPLCDialogClass*)ui)->pB_AddUser, SIGNAL(clicked()), this, SLOT(addUser()));

	//Users部分的信号与槽↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	QRegExp regx("[a-zA-Z0-9_]+$");//正则表达式QRegExp,只允许输入中文、数字、字母、下划线以及空格,[\u4e00 - \u9fa5a - zA - Z0 - 9_] + $
	((Ui::QtPLCDialogClass*)ui)->lE_SetUserName->setValidator(new QRegExpValidator(regx, this));
	((Ui::QtPLCDialogClass*)ui)->cB_SetUserPermission->setEnabled(false);
	QStringList strlst;
	if (lg == 0) strlst << QString::fromLocal8Bit("管理员：0") << QString::fromLocal8Bit("工程师：1") << QString::fromLocal8Bit("操作员：2") << QString::fromLocal8Bit("代码人员：3");
	if (lg == 1) strlst << QString::fromLocal8Bit("Admin：0") << QString::fromLocal8Bit("Engineer：1") << QString::fromLocal8Bit("Operator：2") << QString::fromLocal8Bit("Coder：3");
	((Ui::QtPLCDialogClass*)ui)->cB_SetUserPermission->addItems(strlst);
	QStringList strlst2;
	if (lg == 0) strlst2 << QString::fromLocal8Bit("管理员") << QString::fromLocal8Bit("工程师") << QString::fromLocal8Bit("操作员") << QString::fromLocal8Bit("代码人员");
	if (lg == 1) strlst2 << QString::fromLocal8Bit("Admin") << QString::fromLocal8Bit("Engineer") << QString::fromLocal8Bit("Operator") << QString::fromLocal8Bit("Coder");
	((Ui::QtPLCDialogClass*)ui)->cB_Users->addItems(strlst2);

	QRegExp regx2("[0-9]+$");//正则表达式QRegExp,只允许输入中文、数字、字母、下划线以及空格,[\u4e00 - \u9fa5a - zA - Z0 - 9_] + $
	((Ui::QtPLCDialogClass*)ui)->lE_SetUserSecretNum->setValidator(new QRegExpValidator(regx2, this));
	((Ui::QtPLCDialogClass*)ui)->lE_print1->setValidator(new QRegExpValidator(regx2, this));
	((Ui::QtPLCDialogClass*)ui)->lE_print2->setValidator(new QRegExpValidator(regx2, this));
	((Ui::QtPLCDialogClass*)ui)->lE_SetUserSecretNum->setEnabled(false);
	((Ui::QtPLCDialogClass*)ui)->pB_AddUser->setEnabled(false);

	connect(((Ui::QtPLCDialogClass*)ui)->treeWidget_2, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(onTreeItemChanged(QTreeWidgetItem*)));

	if (lg == 0)updateCheckPermission(QString::fromLocal8Bit("管理员"));
	if (lg == 1)updateCheckPermission(QString::fromLocal8Bit("Admin"));

}
void QtPLCDialogClass::initTableOfUserPermission()
{
	//QFont font;
	//font = ui.tabWidget_CameraVec->font();//左下角白框的字体——[SimSun,21]
	//font.setPointSize(21);
	QWidget* tab = new QWidget();//新建tab
	tab->setFont(font);//设置tab字体
	tab->setObjectName(QString::fromUtf8("tab_0"));//tab_23170685
	if (lg == 0)((Ui::QtPLCDialogClass*)ui)->tabWidget_Users->addTab(tab, QString::fromLocal8Bit("用户权限"));//将tab添加到左下角tabwidget boject name:tab_23170685 tttle:23170685
	if (lg == 1)((Ui::QtPLCDialogClass*)ui)->tabWidget_Users->addTab(tab, QString::fromLocal8Bit("User Permission"));//将tab添加到左下角tabwidget boject name:tab_23170685 tttle:23170685
	QTableWidget* tableWidget = new QTableWidget(tab);//tab下面加tablewidget
	tableWidget->setObjectName(QString::fromLocal8Bit("tableWidget_permission"));//tableWidget_23170685
	tableWidget->setGeometry(QRect(9, 9, ((Ui::QtPLCDialogClass*)ui)->tabWidget_Users->width()-21, 200));//设置widget尺寸 黑边是边界
	
	tableWidget->setFrameShape(QFrame::NoFrame); //设置无边框
	tableWidget->setShowGrid(false); //设置不显示格子线
	/*QPalette pll = tableWidget->palette();
	pll.setBrush(QPalette::Base, QBrush(QColor(255, 255, 255, 0)));
	tableWidget->setPalette(pll);*/

	QStringList strlist;
	if (lg == 0)strlist << QString::fromLocal8Bit("权限名称") << QString::fromLocal8Bit("权限级别");
	if (lg == 1)strlist << QString::fromLocal8Bit("Permission") << QString::fromLocal8Bit("Level");
	tableWidget->setColumnCount(2);//两列
	tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//均分填充表头
	tableWidget->verticalHeader()->setDefaultSectionSize(35);//默认行高20
	tableWidget->setHorizontalHeaderLabels(strlist);//水平表头参数、数值
	tableWidget->verticalHeader()->setVisible(false);
	tableWidget->horizontalHeader()->setVisible(true);//表头可见
	font = tableWidget->horizontalHeader()->font();//表头字体
	font.setPointSize(18);//字号
	tableWidget->horizontalHeader()->setFont(font);//设置表头字体
	font.setPointSize(16);//字号
	tableWidget->setFont(font);//设置内容字体
	int currentcolumn = tableWidget->rowCount();//行数
	tableWidget->insertRow(currentcolumn);//插入行
	if (lg == 0)tableWidget->setItem(currentcolumn, 0, new QTableWidgetItem(QString::fromLocal8Bit("管理员")));//0列设置
	if (lg == 1)tableWidget->setItem(currentcolumn, 0, new QTableWidgetItem(QString::fromLocal8Bit("Admin")));//0列设置
	tableWidget->item(currentcolumn, 0)->setFlags(tableWidget->item(currentcolumn, 0)->flags() & (~Qt::ItemIsEditable));//单元格不可编辑
	tableWidget->item(currentcolumn, 0)->setFlags(tableWidget->item(currentcolumn, 0)->flags() & (~Qt::ItemIsSelectable));//单元格不可选择
	tableWidget->setItem(currentcolumn, 1, new QTableWidgetItem(QString::number(0)));//1列设置
	tableWidget->item(currentcolumn, 1)->setFlags(tableWidget->item(currentcolumn, 1)->flags() & (~Qt::ItemIsEditable));
	tableWidget->item(currentcolumn, 1)->setFlags(tableWidget->item(currentcolumn, 1)->flags() & (~Qt::ItemIsSelectable));
	//if (g_IUserLevel == 0)
	{
		tableWidget->item(currentcolumn, 0)->setBackground(QBrush(QColor("#8889ff81")));//AARRGGBB /RRGGBB
		tableWidget->item(currentcolumn, 1)->setBackground(QBrush(QColor("#8889ff81")));//AARRGGBB /RRGGBB
	}
	//currentcolumn->setBackgroundColor(QColor(255, 0, 0));
	currentcolumn = tableWidget->rowCount();
	tableWidget->insertRow(currentcolumn);	
	if (lg == 0)tableWidget->setItem(currentcolumn, 0, new QTableWidgetItem(QString::fromLocal8Bit("工程师")));
	if (lg == 1)tableWidget->setItem(currentcolumn, 0, new QTableWidgetItem(QString::fromLocal8Bit("Engineer")));
	tableWidget->item(currentcolumn, 0)->setFlags(tableWidget->item(currentcolumn, 0)->flags() & (~Qt::ItemIsEditable));
	tableWidget->item(currentcolumn, 0)->setFlags(tableWidget->item(currentcolumn, 0)->flags() & (~Qt::ItemIsSelectable));
	tableWidget->setItem(currentcolumn, 1, new QTableWidgetItem(QString::number(1)));
	tableWidget->item(currentcolumn, 1)->setFlags(tableWidget->item(currentcolumn, 1)->flags() & (~Qt::ItemIsEditable));
	tableWidget->item(currentcolumn, 1)->setFlags(tableWidget->item(currentcolumn, 1)->flags() & (~Qt::ItemIsSelectable));
	currentcolumn = tableWidget->rowCount();
	tableWidget->insertRow(currentcolumn);
	if (lg == 0)tableWidget->setItem(currentcolumn, 0, new QTableWidgetItem(QString::fromLocal8Bit("操作员")));
	if (lg == 1)tableWidget->setItem(currentcolumn, 0, new QTableWidgetItem(QString::fromLocal8Bit("Operator")));
	tableWidget->item(currentcolumn, 0)->setFlags(tableWidget->item(currentcolumn, 0)->flags() & (~Qt::ItemIsEditable));
	tableWidget->item(currentcolumn, 0)->setFlags(tableWidget->item(currentcolumn, 0)->flags() & (~Qt::ItemIsSelectable));
	tableWidget->setItem(currentcolumn, 1, new QTableWidgetItem(QString::number(2)));
	tableWidget->item(currentcolumn, 1)->setFlags(tableWidget->item(currentcolumn, 1)->flags() & (~Qt::ItemIsEditable));
	tableWidget->item(currentcolumn, 1)->setFlags(tableWidget->item(currentcolumn, 1)->flags() & (~Qt::ItemIsSelectable));
	currentcolumn = tableWidget->rowCount();
	tableWidget->insertRow(currentcolumn);
	if (lg == 0)tableWidget->setItem(currentcolumn, 0, new QTableWidgetItem(QString::fromLocal8Bit("代码人员")));
	if (lg == 1)tableWidget->setItem(currentcolumn, 0, new QTableWidgetItem(QString::fromLocal8Bit("Coder")));
	tableWidget->item(currentcolumn, 0)->setFlags(tableWidget->item(currentcolumn, 0)->flags() & (~Qt::ItemIsEditable));
	tableWidget->item(currentcolumn, 0)->setFlags(tableWidget->item(currentcolumn, 0)->flags() & (~Qt::ItemIsSelectable));
	tableWidget->setItem(currentcolumn, 1, new QTableWidgetItem(QString::number(3)));
	tableWidget->item(currentcolumn, 1)->setFlags(tableWidget->item(currentcolumn, 1)->flags() & (~Qt::ItemIsEditable));
	tableWidget->item(currentcolumn, 1)->setFlags(tableWidget->item(currentcolumn, 1)->flags() & (~Qt::ItemIsSelectable));

}

//下面是查看权限
void QtPLCDialogClass::checkPermission()
{
	((Ui::QtPLCDialogClass*)ui)->treeWidget_2->clear();    //初始化树形控件
	((Ui::QtPLCDialogClass*)ui)->treeWidget_2->setHeaderHidden(true);  //隐藏表头
	QFont serifFont("Times", 16);
	((Ui::QtPLCDialogClass*)ui)->treeWidget_2->setFont(serifFont);
	//定义第一个树形组 爷爷项
	checkPermissionGroup = new QTreeWidgetItem(((Ui::QtPLCDialogClass*)ui)->treeWidget_2);
	QString str = ((Ui::QtPLCDialogClass*)ui)->cB_Users->currentText();
	checkPermissionGroup->setText(0, str);    //树形控件显示的文本信息
	//group->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);   //设置树形控件子项的属性
	//Qt::ItemIsUserCheckable | Qt::ItemIsSelectable 两个都是方框是否可选状态，暂时没用
	//Qt::ItemIsEnabled 使能，不使能会显示为灰色，可以在查看的时候而非添加的时候用
	//Qt::ItemIsEditable 文字可编辑与否，我们都不让编辑
	checkPermissionGroup->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);   //设置树形控件子项的属性
	checkPermissionGroup->setCheckState(0, Qt::Checked); //初始状态没有被选中
	checkPermissionGroup->setBackground(0, QBrush(QColor("#880f97ff")));//AARRGGBB /RRGGBB
	//第一组子项
	QTreeWidgetItem* group1 = new QTreeWidgetItem(checkPermissionGroup);
	// 	QFont headFont("Times", 16,QFont::Bold);
	group1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	if (lg == 0)group1->setText(0, QString::fromLocal8Bit("设备运行"));
	if (lg == 1)group1->setText(0, QString::fromLocal8Bit("Operation"));
	group1->setCheckState(0, Qt::Checked); //设置子选项的显示格式和状态
	QTreeWidgetItem* group2 = new QTreeWidgetItem(checkPermissionGroup);
	group2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	if (lg == 0)group2->setText(0, QString::fromLocal8Bit("设置"));
	if (lg == 1)group2->setText(0, QString::fromLocal8Bit("Setup"));
	group2->setCheckState(0, Qt::Checked);
	//设置蓝色group2->setBackground(0, QBrush(QColor("#0000FF")));
	//父亲项
	QTreeWidgetItem* group21 = new QTreeWidgetItem(group2);
	if (lg == 0)group21->setText(0, QString::fromLocal8Bit("系统监控"));
	if (lg == 1)group21->setText(0, QString::fromLocal8Bit("Monitor"));
	group21->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group21->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group22 = new QTreeWidgetItem(group2);
	if (lg == 0)group22->setText(0, QString::fromLocal8Bit("系统参数"));
	if (lg == 1)group22->setText(0, QString::fromLocal8Bit("Sys Para"));
	group22->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group22->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group23 = new QTreeWidgetItem(group2);
	if (lg == 0)group23->setText(0, QString::fromLocal8Bit("运行参数"));
	if (lg == 1)group23->setText(0, QString::fromLocal8Bit("Run Para"));
	group23->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group23->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group24 = new QTreeWidgetItem(group2);
	if (lg == 0)group24->setText(0, QString::fromLocal8Bit("用户管理"));
	if (lg == 1)group24->setText(0, QString::fromLocal8Bit("Users"));
	group24->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group24->setCheckState(0, Qt::Checked);
	//孙子项1
	QTreeWidgetItem* group211 = new QTreeWidgetItem(group21);   //指定子项属于哪一个父项
	group211->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	if (lg == 0)group211->setText(0, QString::fromLocal8Bit("输入输出"));
	if (lg == 1)group211->setText(0, QString::fromLocal8Bit("IO"));
	group211->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group212 = new QTreeWidgetItem(group21);
	group212->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	if (lg == 0)group212->setText(0, QString::fromLocal8Bit("下料旋转"));
	if (lg == 1)group212->setText(0, QString::fromLocal8Bit("Motors"));
	group212->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group213 = new QTreeWidgetItem(group21);
	group213->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	if (lg == 0)group213->setText(0, QString::fromLocal8Bit("检测单元"));
	if (lg == 1)group213->setText(0, QString::fromLocal8Bit("Units"));
	group213->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group214 = new QTreeWidgetItem(group21);
	group214->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	if (lg == 0)group214->setText(0, QString::fromLocal8Bit("其它"));
	if (lg == 1)group214->setText(0, QString::fromLocal8Bit("Others"));
	group214->setCheckState(0, Qt::Checked);
	/*QTreeWidgetItem* group2133 = new QTreeWidgetItem(group213);
	group2133->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group2133->setText(0, QString::fromLocal8Bit("打印设置"));
	group2133->setCheckState(0, Qt::Checked);*/
	/*QTreeWidgetItem* group214 = new QTreeWidgetItem(group21);
	group214->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group214->setText(0, QString::fromLocal8Bit("修改名称"));
	group214->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group215 = new QTreeWidgetItem(group21);
	group215->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group215->setText(0, QString::fromLocal8Bit("算法设置"));
	group215->setCheckState(0, Qt::Checked);
	//孙子项2
	QTreeWidgetItem* group221 = new QTreeWidgetItem(group22);
	group221->setText(0, QString::fromLocal8Bit("相机调试"));
	group221->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group221->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group222 = new QTreeWidgetItem(group22);
	group222->setText(0, QString::fromLocal8Bit("采集测试"));
	group222->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group222->setCheckState(0, Qt::Checked);
	//孙子项3
	QTreeWidgetItem* group231 = new QTreeWidgetItem(group23);
	group231->setText(0, QString::fromLocal8Bit("参数读取"));
	group231->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group231->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group232 = new QTreeWidgetItem(group23);
	group232->setText(0, QString::fromLocal8Bit("参数写入"));
	group232->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group232->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group233 = new QTreeWidgetItem(group23);
	group233->setText(0, QString::fromLocal8Bit("采集"));
	group233->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group233->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group234 = new QTreeWidgetItem(group23);
	group234->setText(0, QString::fromLocal8Bit("控制测试"));
	group234->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group234->setCheckState(0, Qt::Checked);*/
	//孙子项4
	QTreeWidgetItem* group241 = new QTreeWidgetItem(group24);
	if (lg == 0)group241->setText(0, QString::fromLocal8Bit("添加用户"));
	if (lg == 1)group241->setText(0, QString::fromLocal8Bit("Add user"));
	group241->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group241->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group242 = new QTreeWidgetItem(group24);
	if (lg == 0)group242->setText(0, QString::fromLocal8Bit("删除用户"));
	if (lg == 1)group242->setText(0, QString::fromLocal8Bit("Delete user"));
	group242->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group242->setCheckState(0, Qt::Checked);
	((Ui::QtPLCDialogClass*)ui)->treeWidget_2->expandAll();  //展开树
	//ui.treeWidget_2->expandToDepth(1);
}

void QtPLCDialogClass::initTableWidget()
{//第二个表
	tab = new QWidget();
	tableWidget = new QTableWidget(tab);//tab下面加tablewidget

	tab->setObjectName(QString::fromUtf8("tab_1"));//tab_23170685
	if (lg == 0)((Ui::QtPLCDialogClass*)ui)->tabWidget_Users->addTab(tab, QString::fromLocal8Bit("自定义用户"));//将tab添加到左下角tabwidget boject name:tab_23170685 tttle:23170685
	if (lg == 1)((Ui::QtPLCDialogClass*)ui)->tabWidget_Users->addTab(tab, QString::fromLocal8Bit("Users"));//将tab添加到左下角tabwidget boject name:tab_23170685 tttle:23170685
	tableWidget->setObjectName(QString::fromLocal8Bit("tableWidget_username"));//tableWidget_23170685
	tableWidget->setGeometry(QRect(9, 9, ((Ui::QtPLCDialogClass*)ui)->tabWidget_Users->width() - 21, ((Ui::QtPLCDialogClass*)ui)->tabWidget_Users->height() - 80));//设置widget尺寸 黑边是边界

	tableWidget->setFrameShape(QFrame::NoFrame); //设置无边框
	tableWidget->setShowGrid(false); //设置不显示格子线

	QStringList strlist2;
	if (lg == 0)strlist2 << QString::fromLocal8Bit("用户名") << QString::fromLocal8Bit("权限级别");
	if (lg == 1)strlist2 << QString::fromLocal8Bit("User") << QString::fromLocal8Bit("Permission");
	tableWidget->setColumnCount(2);//两列
	tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//均分填充表头
	tableWidget->verticalHeader()->setDefaultSectionSize(35);//默认行高20
	tableWidget->setHorizontalHeaderLabels(strlist2);//水平表头参数、数值
	tableWidget->verticalHeader()->setVisible(false);
	tableWidget->horizontalHeader()->setVisible(true);//表头可见
	font = tableWidget->horizontalHeader()->font();//表头字体
	tableWidget->horizontalHeader()->setFont(font);//设置表头字体
	QSettings FinalDir(AppPath + "/ModelFile/ProgramSet.ini", QSettings::IniFormat);//所有结果文件
	QStringList str = FinalDir.childGroups();
	int count = str.size();
	int j = 0;
	for (int i = 0; i < count; i++)
	{
		QString One = str.at(i);//节点
		if (One.mid(0, 4) == "USER")
		{
			tableWidget->insertRow(j);//加一行
			QString j0 = One.mid(5);
			tableWidget->setItem(j, 0, new QTableWidgetItem(j0));//添加日期result行
			tableWidget->item(j, 0)->setFlags(tableWidget->item(j, 0)->flags() & (~Qt::ItemIsEditable));//单元格不可编辑
			QString j1 = FinalDir.value(One + "/" + "Level", -1).toString();
			tableWidget->setItem(j, 1, new QTableWidgetItem(j1));//添加日期result行
			tableWidget->item(j, 1)->setFlags(tableWidget->item(j, 1)->flags() & (~Qt::ItemIsEditable));//单元格不可编辑
			tableWidget->item(j, 1)->setFlags(tableWidget->item(j, 1)->flags() & (~Qt::ItemIsSelectable));//单元格不可选择
			j++;
		}
	}
	connect(tableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(selectedName(int, int)));
	tab = nullptr;
	tableWidget = nullptr;
}

void QtPLCDialogClass::initMovie()
{//创建动态对象
	{
		animation1 = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable, "geometry");
		//设置动画时间间隔
		animation1->setDuration(200);

		//起始位置
		animation1->setStartValue(QRect(((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->x(), ((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->y(), ((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->width(), ((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->height()));
		//结束位置
		animation1->setEndValue(QRect(((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->x(), ((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->y() + 10, ((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->width(), ((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->height()));

		//设置弹跳曲线
		animation1->setEasingCurve(QEasingCurve::OutBounce);
	}
	{    //创建动态对象
		animation2 = new QPropertyAnimation(((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable, "geometry");
		//设置动画时间间隔
		animation2->setDuration(200);

		//起始位置
		animation2->setStartValue(QRect(((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->x(), ((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->y() + 10, ((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->width(), ((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->height()));
		//结束位置
		animation2->setEndValue(QRect(((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->x(), ((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->y(), ((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->width(), ((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->height()));

		//设置弹跳曲线
		animation2->setEasingCurve(QEasingCurve::OutBounce);
	}
}
void QtPLCDialogClass::initUI()
{
	gettime();
	((Ui::QtPLCDialogClass*)ui)->pB_TMUStop->setVisible(false);
	((Ui::QtPLCDialogClass*)ui)->pB_HMUZero->setVisible(false);
	//QRegExp regx("[a-zA-Z0-9_]+$");//正则表达式QRegExp,只允许输入中文、数字、字母、下划线以及空格,[\u4e00 - \u9fa5a - zA - Z0 - 9_] + $
	QRegExp regx("[0-9]+$");
	((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->setValidator(new QRegExpValidator(regx, this));
	((Ui::QtPLCDialogClass*)ui)->lE_year1->setValidator(new QRegExpValidator(regx, this));
	((Ui::QtPLCDialogClass*)ui)->lE_month1->setValidator(new QRegExpValidator(regx, this));
	((Ui::QtPLCDialogClass*)ui)->lE_day1->setValidator(new QRegExpValidator(regx, this));
	((Ui::QtPLCDialogClass*)ui)->lE_hour1->setValidator(new QRegExpValidator(regx, this));
	((Ui::QtPLCDialogClass*)ui)->lE_hour2->setValidator(new QRegExpValidator(regx, this));
	((Ui::QtPLCDialogClass*)ui)->lE_minute1->setValidator(new QRegExpValidator(regx, this));
	((Ui::QtPLCDialogClass*)ui)->lE_minute2->setValidator(new QRegExpValidator(regx, this));

	((Ui::QtPLCDialogClass*)ui)->pB_copyIn->setEnabled(false);

	QRegExp regx_2("[a-zA-Z0-9_]+$");
	((Ui::QtPLCDialogClass*)ui)->lE_BatchName->setValidator(new QRegExpValidator(regx_2, this));
	lb_dataNow = new QLabel(((Ui::QtPLCDialogClass*)ui)->frame);
	lb_dataNow->move(30, 16);
	lb_dataNow->setScaledContents(true);

	if (lg == 0)
	{
		((Ui::QtPLCDialogClass*)ui)->groupBox_10->setTitle("                                     ");
		lb_dataNow->resize(140, 35);
		lb_dataNow->setPixmap(QPixmap(AppPath + "/ico/fontImage/datanow.png"));
	}
	else if (lg == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->groupBox_10->setTitle("                                                                         ");
		lb_dataNow->resize(280, 35);
		lb_dataNow->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/datanow.png"));
	}
	lb_dataNow->setScaledContents(true);

	if (lg == 0)
	{
		((Ui::QtPLCDialogClass*)ui)->label_15->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_15.png"));
		((Ui::QtPLCDialogClass*)ui)->label_18->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_18.png"));
		((Ui::QtPLCDialogClass*)ui)->label_20->setPixmap(QPixmap(AppPath + "/ico/fontImage/tfh.png"));
		((Ui::QtPLCDialogClass*)ui)->label_79->setPixmap(QPixmap(AppPath + "/ico/fontImage/dqzh.png"));
		((Ui::QtPLCDialogClass*)ui)->label_78->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_78.png"));
		((Ui::QtPLCDialogClass*)ui)->label_80->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_80.png"));
		((Ui::QtPLCDialogClass*)ui)->label_10->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_10.png"));
		((Ui::QtPLCDialogClass*)ui)->label_39->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_39.png"));
		((Ui::QtPLCDialogClass*)ui)->label_50->setPixmap(QPixmap(AppPath + "/ico/fontImage/yxbz.png"));
		((Ui::QtPLCDialogClass*)ui)->label_49->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_49.png"));
		((Ui::QtPLCDialogClass*)ui)->label_16->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_16.png"));
		((Ui::QtPLCDialogClass*)ui)->label_17->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_17.png"));
		((Ui::QtPLCDialogClass*)ui)->label_48->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_48.png"));


		((Ui::QtPLCDialogClass*)ui)->label_55->setPixmap(QPixmap(AppPath + "/ico/fontImage/clhd.png"));
		((Ui::QtPLCDialogClass*)ui)->label_37->setPixmap(QPixmap(AppPath + "/ico/fontImage/clyd.png"));
		((Ui::QtPLCDialogClass*)ui)->label_59->setPixmap(QPixmap(AppPath + "/ico/fontImage/clzj.png"));
		((Ui::QtPLCDialogClass*)ui)->label_23->setPixmap(QPixmap(AppPath + "/ico/fontImage/dqyd.png"));
	}
	else if (lg == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->label_15->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/label_15.png"));
		((Ui::QtPLCDialogClass*)ui)->label_18->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/label_18.png"));
		((Ui::QtPLCDialogClass*)ui)->label_20->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/tfh.png"));
		((Ui::QtPLCDialogClass*)ui)->label_79->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/dqzh.png"));
		((Ui::QtPLCDialogClass*)ui)->label_78->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/label_78.png"));
		((Ui::QtPLCDialogClass*)ui)->label_80->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/label_80.png"));
		((Ui::QtPLCDialogClass*)ui)->label_10->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/label_10.png"));
		((Ui::QtPLCDialogClass*)ui)->label_39->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/label_39.png"));
		((Ui::QtPLCDialogClass*)ui)->label_50->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/yxbz.png"));
		((Ui::QtPLCDialogClass*)ui)->label_49->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/label_49.png"));
		((Ui::QtPLCDialogClass*)ui)->label_16->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/label_16.png"));
		((Ui::QtPLCDialogClass*)ui)->label_17->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/label_17.png"));
		((Ui::QtPLCDialogClass*)ui)->label_48->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/label_48.png"));

		((Ui::QtPLCDialogClass*)ui)->label_55->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/clhd.png"));
		((Ui::QtPLCDialogClass*)ui)->label_37->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/clyd.png"));
		((Ui::QtPLCDialogClass*)ui)->label_59->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/clzj.png"));
		((Ui::QtPLCDialogClass*)ui)->label_23->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/dqyd.png"));
	}
	((Ui::QtPLCDialogClass*)ui)->label_15->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_18->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_20->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_79->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_78->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_80->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_10->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_39->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_50->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_49->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_16->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_17->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_48->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_55->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_37->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_59->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_23->setScaledContents(true);

	setYearMonthDay();
}

void QtPLCDialogClass::inittabicon()
{
	((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setIconSize(QSize(132, 33));
	((Ui::QtPLCDialogClass*)ui)->tabWidget->setIconSize(QSize(132, 33));
	if (lg==0)
	{
	((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(0, QIcon(AppPath + "/ico/fontImage/xtjk.png"));
	((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(1, QIcon(AppPath + "/ico/fontImage/xtcs.png"));
	((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(2, QIcon(AppPath + "/ico/fontImage/yxcs.png"));
	//((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(3, QIcon(AppPath + "/ico/fontImage/yxzt.png"));
	((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(3, QIcon(AppPath + "/ico/fontImage/yhgl.png"));

	((Ui::QtPLCDialogClass*)ui)->tabWidget->setTabIcon(0, QIcon(AppPath + "/ico/fontImage/srsc.png"));
	((Ui::QtPLCDialogClass*)ui)->tabWidget->setTabIcon(1, QIcon(AppPath + "/ico/fontImage/xlxz.png"));
	((Ui::QtPLCDialogClass*)ui)->tabWidget->setTabIcon(2, QIcon(AppPath + "/ico/fontImage/unit.png"));
	((Ui::QtPLCDialogClass*)ui)->tabWidget->setTabIcon(3, QIcon(AppPath + "/ico/fontImage/others.png"));
	}	
	else if (lg == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(0, QIcon(AppPath + "/ico/fontImage/E/xtjk.png"));
		((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(1, QIcon(AppPath + "/ico/fontImage/E/xtcs.png"));
		((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(2, QIcon(AppPath + "/ico/fontImage/E/yxcs.png"));
		//((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(3, QIcon(AppPath + "/ico/fontImage/yxzt.png"));
		((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(3, QIcon(AppPath + "/ico/fontImage/E/yhgl.png"));

		((Ui::QtPLCDialogClass*)ui)->tabWidget->setTabIcon(0, QIcon(AppPath + "/ico/fontImage/E/srsc.png"));
		((Ui::QtPLCDialogClass*)ui)->tabWidget->setTabIcon(1, QIcon(AppPath + "/ico/fontImage/E/xlxz.png"));
		((Ui::QtPLCDialogClass*)ui)->tabWidget->setTabIcon(2, QIcon(AppPath + "/ico/fontImage/E/unit.png"));
		((Ui::QtPLCDialogClass*)ui)->tabWidget->setTabIcon(3, QIcon(AppPath + "/ico/fontImage/E/others.png"));
	}

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
bool sortImgLists(QString a, QString b)//排序方法
{
	return a.toLongLong() > b.toLongLong();
}
void QtPLCDialogClass::CompareYearMonthDay()
{
	QStringList lst;
	if (lg == 0)lst << QString::fromLocal8Bit("符合组号");
	if (lg == 1)lst << QString::fromLocal8Bit("Matched");

	QString str1 = ((Ui::QtPLCDialogClass*)ui)->lE_year1->text() +
		((Ui::QtPLCDialogClass*)ui)->lE_month1->text() +
		((Ui::QtPLCDialogClass*)ui)->lE_day1->text() +
		((Ui::QtPLCDialogClass*)ui)->lE_hour1->text() +
		((Ui::QtPLCDialogClass*)ui)->lE_minute1->text();
	LONGLONG ll1 = str1.toLongLong();

	QString str2 = ((Ui::QtPLCDialogClass*)ui)->lE_year1->text() +
		((Ui::QtPLCDialogClass*)ui)->lE_month1->text() +
		((Ui::QtPLCDialogClass*)ui)->lE_day1->text() +
		((Ui::QtPLCDialogClass*)ui)->lE_hour2->text() +
		((Ui::QtPLCDialogClass*)ui)->lE_minute2->text();
	LONGLONG ll2 = str2.toLongLong();

	if (ll1 > ll2)
	{
		if (lg == 0)((Ui::QtPLCDialogClass*)ui)->lb_searchResult->setText(QString::fromLocal8Bit("条件有误!"));
		if (lg == 1)((Ui::QtPLCDialogClass*)ui)->lb_searchResult->setText(QString::fromLocal8Bit("Wrong condition!"));
		((Ui::QtPLCDialogClass*)ui)->pB_copyIn->setEnabled(false);
	}
	else if (ll1 == ll2)
	{
		QSettings timIni(AppPath + "\\data\\time.ini", QSettings::IniFormat);
		QString str = timIni.value(str1.mid(8) + "/" + str1, "0").toString();
		if (str == "0")
		{
			if (lg == 0)((Ui::QtPLCDialogClass*)ui)->lb_searchResult->setText(QString::fromLocal8Bit("该时间不存在数据!"));
			if (lg == 1)((Ui::QtPLCDialogClass*)ui)->lb_searchResult->setText(QString::fromLocal8Bit("No data exists at this time!"));
			((Ui::QtPLCDialogClass*)ui)->pB_copyIn->setEnabled(false);
		}
		else
		{
			m_gn1 = str;
			m_gn2 = str;
			((Ui::QtPLCDialogClass*)ui)->pB_copyIn->setEnabled(true);
		}
	}
	else
	{
		m_gn1 = "";
		m_gn2 = "";
		QSettings timIni(AppPath + "\\data\\time.ini", QSettings::IniFormat);
		// 获取一个节点下的key值
		timIni.beginGroup(str1.mid(0, 8));    // 设置查找节点
		QStringList str2 = timIni.allKeys();    // 获取所有的key 已经排序完成，小到大不许再次排序
		qSort(str2.begin(), str2.end(), sortImgLists);

		if (str2.size() == 0)
		{
			if (lg == 0)((Ui::QtPLCDialogClass*)ui)->lb_searchResult->setText(QString::fromLocal8Bit("该时间段不存在数据!"));
			if (lg == 1)((Ui::QtPLCDialogClass*)ui)->lb_searchResult->setText(QString::fromLocal8Bit("No data in the time period!"));
			((Ui::QtPLCDialogClass*)ui)->pB_copyIn->setEnabled(false);
			return;
		}
		int itemp = 0;
		LONGLONG ltemp1;
		LONGLONG ltemp2;
		foreach(QString key, str2)
		{
			LONGLONG value = key.toLongLong();
			if (value >= ll1 && value <= ll2)
			{
				lst << timIni.value(key, "0").toString();
				if (itemp == 0)
				{
					itemp = 1;
					ltemp1 = value;
					ltemp2 = value;
				}
				if (ltemp1 > value)
				{
					ltemp1 = value;
				}
				if (ltemp2 < value)
				{
					ltemp2 = value;
				}
				if (value <= ltemp1)
				{
					int finalvalue = timIni.value(key).toInt();  // 直接用 key 获取数据
					m_gn1 = QString::number(finalvalue);
				}
				if (value >= ltemp2)
				{
					int finalvalue = timIni.value(key).toInt();  // 直接用 key 获取数据
					m_gn2 = QString::number(finalvalue);
				}
			}
		}
		timIni.endGroup();

		if (m_gn1 == "")
		{
			if (lg == 0)((Ui::QtPLCDialogClass*)ui)->lb_searchResult->setText(QString::fromLocal8Bit("不存在符合条件的数据!"));
			if (lg == 1)((Ui::QtPLCDialogClass*)ui)->lb_searchResult->setText(QString::fromLocal8Bit("No eligible data!"));
			((Ui::QtPLCDialogClass*)ui)->pB_copyIn->setEnabled(false);
			((Ui::QtPLCDialogClass*)ui)->lW_data->setVisible(false);
			((Ui::QtPLCDialogClass*)ui)->lb_search->setVisible(false);
			((Ui::QtPLCDialogClass*)ui)->tableWidget->setVisible(true);

			((Ui::QtPLCDialogClass*)ui)->lW_data->clear();
		}
		else
		{
			if (m_gn1 == m_gn2)
			{
				if (lg == 0)((Ui::QtPLCDialogClass*)ui)->lb_searchResult->setText(QString::fromLocal8Bit("符合组号为：(共1组)\n") + m_gn1);
				if (lg == 1)((Ui::QtPLCDialogClass*)ui)->lb_searchResult->setText(QString::fromLocal8Bit("Matched group number:\n") + m_gn1);

				((Ui::QtPLCDialogClass*)ui)->lW_data->setVisible(false);
				((Ui::QtPLCDialogClass*)ui)->lb_search->setVisible(false);
				((Ui::QtPLCDialogClass*)ui)->tableWidget->setVisible(true);

				((Ui::QtPLCDialogClass*)ui)->lW_data->clear();
			}
			else
			{
				if (lg == 0)((Ui::QtPLCDialogClass*)ui)->lb_searchResult->setText(QString::fromLocal8Bit("符合组号为：(实际共") + QString::number(lst.size()-1) + QString::fromLocal8Bit("组)\n") + m_gn1 + "-" + m_gn2);
				if (lg == 1)((Ui::QtPLCDialogClass*)ui)->lb_searchResult->setText(QString::fromLocal8Bit("Matched group number:\n") + m_gn1 + "-" + m_gn2);

				((Ui::QtPLCDialogClass*)ui)->lW_data->setVisible(true);
				((Ui::QtPLCDialogClass*)ui)->lb_search->setVisible(true);
				((Ui::QtPLCDialogClass*)ui)->tableWidget->setVisible(false);

				((Ui::QtPLCDialogClass*)ui)->lW_data->clear();

				((Ui::QtPLCDialogClass*)ui)->lW_data->addItems(lst);

			}
			((Ui::QtPLCDialogClass*)ui)->pB_copyIn->setEnabled(true);
		}

	}
}
void QtPLCDialogClass::setg_IUserLevel(int index)
{
	g_IUserLevel = index;	
	//user part
	if (g_IUserLevel == 0)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_showPrt->setEnabled(false);
	}
	else if (g_IUserLevel == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->removeTab(3);
	}
	else if (g_IUserLevel == 2)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_SetUpcheckable->setEnabled(false);
	}
}
#pragma endregion

#pragma region socket
void QtPLCDialogClass::SetSocket(QtSocket_Class *sc)
{
	m_socket = sc;
	bool b = connect(m_socket, SIGNAL(signal_FROMPLC(void*)), this, SLOT(getPLCData(void*)));//signal_FROMPLCHLODING
	b = connect(m_socket, SIGNAL(signal_FROMPLCHLODING(void*)), this, SLOT(getPLCHolding(void*)));//();
	b = connect(m_socket, SIGNAL(WRITECOILS()), this, SLOT(on_WriteCoils()));
	b = connect(m_socket, SIGNAL(WRITEHOLDINGREGISTERS()), this, SLOT(on_WriteHolding()));
	b = connect(m_socket, SIGNAL(statechange_Unconnected()), this, SLOT(OnUnconnectedState()));
	b = connect(m_socket, SIGNAL(statechange_Closing()), this, SLOT(OnClosingState()));
	b = connect(m_socket, SIGNAL(SHOWSTATUS(QString)), this, SLOT(OnShowState(QString)));
	b = connect(m_socket, SIGNAL(ValueCountFlag(int)), this, SLOT(OnShowValueCountFlag(int)));
	
}
#pragma endregion

#pragma region data
DataFromPC_typ QtPLCDialogClass::getPCParaData()//2
{
	DataFromPC_typ tmp;
	memset(&tmp, 0, sizeof(DataFromPC_typ));	
	tmp.Machine_Para.enable = 0;
	tmp.Machine_Para.s_trg_stop[0] = m_data->Machine_Para.s_trg_stop[0];					
	tmp.Machine_Para.s_trg_stop[1] = m_data->Machine_Para.s_trg_stop[1];			//停止位置
	tmp.Machine_Para.Feed_shakeoffset = m_data->Machine_Para.Feed_shakeoffset;
	tmp.Machine_Para.FeedTimeOut = m_data->Machine_Para.FeedTimeOut;				//下料超时时间,单位s
	tmp.Machine_Para.CapPickInterval = m_data->Machine_Para.CapPickInterval;		//自动取料周期,单位s
	tmp.Machine_Para.CapBackInterval = m_data->Machine_Para.CapBackInterval;		//成品返还周期,单位s

	tmp.Machine_Para.TireDelay = m_data->Machine_Para.TireDelay;					//去皮延迟启动时间,单位s
	tmp.Machine_Para.ReadDelay = m_data->Machine_Para.ReadDelay;					//读数延迟启动时间,单位s
	tmp.Machine_Para.TireWaitTime = m_data->Machine_Para.TireWaitTime;				//去皮等待时间,单位s
	tmp.Machine_Para.StopSignalDelay = m_data->Machine_Para.StopSignalDelay;		//连续几次超重或超轻后输出停机信号

	return tmp;
}
DataFromPC_typ QtPLCDialogClass::getPCRunData()//4
{
	DataFromPC_typ tmp;
	memset(&tmp, 0, sizeof(DataFromPC_typ));

	tmp.ActData.SysOveride = m_data->ActData.SysOveride;				//系统速度，0-10000对应0-100%
	tmp.ActData.StableState = m_data->ActData.StableState;			//天平当前稳定状态,0:非常稳定,1:稳定,2:不稳定,3:非常不稳定   maybe move
	tmp.ActData.FeedOveride = m_data->ActData.FeedOveride;

	tmp.ActData.PassCount = m_data->ActData.PassCount;				//通过计数
	tmp.ActData.ProdCount = m_data->ActData.ProdCount;				//称重计数
	tmp.ActData.TOCount = m_data->ActData.TOCount;				//过重计数
	tmp.ActData.TUCount = m_data->ActData.TUCount;				//过轻计数
	tmp.ActData.RejectCount = m_data->ActData.RejectCount;			//剔废计数
		
	tmp.ActData.WorkMode = m_data->ActData.WorkMode;				//0:片剂，1：胶囊				new8
	tmp.ActData.GroupSet = m_data->ActData.GroupSet;				//每组测试胶囊数量				new9
	tmp.ActData.GroupCounter = m_data->ActData.GroupCounter;			//组落料数量				     new10
	tmp.ActData.TireMode = 0;				//0:每组去皮重,1:每次称重去皮重	 new11
	tmp.ActData.TestInterval = m_data->ActData.TestInterval;			//测试间隔时间,单位s		     new12
		
	tmp.ActData.TOverload = m_data->ActData.TOverload;				//超重重量,单位g
	tmp.ActData.TUnderload = m_data->ActData.TUnderload;				//超轻重量,单位g
	tmp.ActData.TDemand = m_data->ActData.TDemand;				//期望重量,单位g	

	tmp.ActData.DeltaSwing = m_data->ActData.DeltaSwing;				//位置偏差,未使用									new13	
	tmp.ActData.GroupWeightCounter = m_data->ActData.GroupWeightCounter;		//组称重数量								new14
	tmp.ActData.GroupRejectCounter = m_data->ActData.GroupRejectCounter;		 //组踢废数量,指剔废处理,非剔废动作		 new15
		
	tmp.ActData.GroupNo = m_data->ActData.GroupNo;		//组号
	tmp.ActData.GroupIndex = m_data->ActData.GroupIndex;		//组数量计数
	tmp.ActData.GroupSum = m_data->ActData.GroupSum;		//组总重
	tmp.ActData.GroupAvg = m_data->ActData.GroupAvg;		//组平均重量,g
	tmp.ActData.GroupMax = m_data->ActData.GroupMax;		//组最大值
	tmp.ActData.GroupMin = m_data->ActData.GroupMin;		//组最小值
	tmp.ActData.GroupMaxRatio = m_data->ActData.GroupMaxRatio;		//组最大偏差
	tmp.ActData.GroupMinRatio = m_data->ActData.GroupMinRatio;		//组最小偏差
		
	tmp.ActData.InterOverLoad = m_data->ActData.InterOverLoad;			//内控线，上限,单位g
	tmp.ActData.InterUnderLoad = m_data->ActData.InterUnderLoad;		//内控线，下限,单位g	
		
	tmp.ActData.UsbOk = m_data->ActData.UsbOk;		//U盘准备好
	tmp.ActData.UsbPrintOk = m_data->ActData.UsbPrintOk;		//Print准备好
	tmp.ActData.Feedmode = m_data->ActData.Feedmode;

	tmp.ActData.UserAnalogoutput = m_data->ActData.UserAnalogoutput;		//用户模拟量输入
	tmp.ActData.Adjustvalue = m_data->ActData.Adjustvalue;			//自动调整系数
	tmp.ActData.DeltaInput = m_data->ActData.DeltaInput;				//装量调整偏差值
	tmp.ActData.MultiCount = m_data->ActData.MultiCount;

	memset(tmp.ActData.BatchName, '\0', sizeof(tmp.ActData.BatchName));
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_BatchName->text();
	QByteArray ba = str.toLatin1();
	char *c = ba.data();
	strcpy(tmp.ActData.BatchName, c);

	return tmp;
}

////////////////////////////////曲线
void QtPLCDialogClass::initChartOne()
{
	maxX = 41;
	maxSize = maxX - 1; // 只存储最新的 31 个数据
	maxY = 255;
	splineSeries = new QLineSeries();
	splineSeries->setPointLabelsFormat("@yPoint");
	splineSeries->setPointLabelsClipping(false);
	splineSeries->setPointsVisible(true);
	splineSeries->setPointLabelsVisible(false);
	if (lg == 0) splineSeries->setName(QString::fromLocal8Bit("组重量曲线"));
	if (lg == 1) splineSeries->setName(QString::fromLocal8Bit("Group Data & Curve"));

	chart = new QChart();
	chart->legend()->hide();

	if (lg == 0) chart->setTitle(QString::fromLocal8Bit("组重量曲线"));
	if (lg == 1) chart->setTitle(QString::fromLocal8Bit("Group Data & Curve"));


	chart->addSeries(splineSeries);

	axisx = new QValueAxis;
	axisx->setLabelFormat("%d");
	axisx->setTickCount(2);
	axisx->setRange(0, 1);
	axisx->setGridLineVisible(true);
	chart->setAxisX(axisx, splineSeries);
	chart->addAxis(axisx, Qt::AlignBottom);

	axisy = new QValueAxis;
	//axisy->setLabelFormat("%d");
	axisy->setLabelFormat("%.3f");
	axisy->setTickCount(6);
	axisy->setRange(0.210, 0.250);
	axisy->setGridLineVisible(true);
	chart->setAxisY(axisy, splineSeries);
	chart->addAxis(axisy, Qt::AlignLeft);

	chart->setTheme(QChart::ChartThemeBlueCerulean);
	chartView = new QChartView(chart);

	chartView->setRenderHint(QPainter::Antialiasing);

	((Ui::QtPLCDialogClass*)ui)->gridLayout_One->addWidget(chartView);
}
void QtPLCDialogClass::getPLCHolding(void*data)
{
	if (m_iDontReadRegistersFlag == 1)
	{
		return;
	}
	memcpy(dtregisters, (quint16*)data, REGISTERS*2);//主界面用
#ifdef MODBUSTCP
	m_str_registers = "0000";//no this cause bug
	for (int i = 0; i < REGISTERS; i++)
	{
		m_Input_Bufer[i + 1] = dtregisters[i];
		quint16 a = dtregisters[i];
		QString strtmp = QString("%1").arg(a, 4, 16, QLatin1Char('0'));

		//arg中第二个参数表示字符串的位数，第三个参数表示int的进制，第4个参数表示自动补全的字符；
		m_str_registers += strtmp;
	}
	m_InputFlag = 1;

	if (!((Ui::QtPLCDialogClass*)ui)->lE_Finished->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_Finished->setText(QString::number(m_Input_Bufer[GroupDone]));
	}
	
	double dbhex_res = hexToeightbytefloat(ActData_GroupSum);
	if (dbhex_res >0)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_GroupSum->setText(QString::number(dbhex_res, 'f', 3));
		((Ui::QtPLCDialogClass*)ui)->lE_GroupAvg->setText(QString::number(hexTofloat(ActData_GroupAvg)));
		((Ui::QtPLCDialogClass*)ui)->lE_GroupMax->setText(QString::number(hexTofloat(ActData_GroupMax)));
		((Ui::QtPLCDialogClass*)ui)->lE_GroupMin->setText(QString::number(hexTofloat(ActData_GroupMin)));
		((Ui::QtPLCDialogClass*)ui)->lE_GroupMaxRatio->setText(QString::number(hexTofloat(ActData_GroupMaxRatio)));
		((Ui::QtPLCDialogClass*)ui)->lE_GroupMinRatio->setText(QString::number(hexTofloat(ActData_GroupMinRatio)));
	}
	
	if (!((Ui::QtPLCDialogClass*)ui)->lE_FeedCounter->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_FeedCounter->setText(QString::number(m_Input_Bufer[FeedCounter]));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_ThickRejectCount->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_ThickRejectCount->setText(QString::number(m_Input_Bufer[ActData_ThickRejectCount] + m_Input_Bufer[ActData_ThickRejectCount + 1] * 65536));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_RejectBoxCnt->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_RejectBoxCnt->setText(QString::number(m_Input_Bufer[ActData_RejectBoxCnt] + m_Input_Bufer[ActData_RejectBoxCnt + 1] * 65536));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_MultiCount->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_MultiCount->setText(QString::number(m_Input_Bufer[ActData_FeedAmount]));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_GroupNo->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_GroupNo->setText(QString::number(m_Input_Bufer[ActData_GroupNo] + m_Input_Bufer[ActData_GroupNo + 1] * 65536));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_GroupNo_2->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_GroupNo_2->setText(QString::number(m_Input_Bufer[ActData_GroupNo] + m_Input_Bufer[ActData_GroupNo + 1] * 65536));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_GroupIndex->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_GroupIndex->setText(QString::number(m_Input_Bufer[ActData_GroupIndex] + m_Input_Bufer[ActData_GroupIndex + 1] * 65536));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_GroupIndex_2->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_GroupIndex_2->setText(QString::number(m_Input_Bufer[ActData_GroupIndex] + m_Input_Bufer[ActData_GroupIndex + 1] * 65536));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_MachineStep->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_MachineStep->setText(QString::number(m_Input_Bufer[Machine_step]));
		if (m_b && m_Input_Bufer[Machine_step]!=0)
		{
			m_b = 0;
			((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->blockSignals(false);
			QPixmap pix;
			if (lg == 0) pix.load(AppPath + "/ico/stop.png");
			if (lg == 1) pix.load(AppPath + "/ico/E/stop.png");
			ExitBtn->setEnabled(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setIcon(pix);
			((Ui::QtPLCDialogClass*)ui)->lE_BatchName->setEnabled(false);
		}
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_PassCount->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_PassCount->setText(QString::number(m_Input_Bufer[ActData_PassCount] + m_Input_Bufer[ActData_PassCount+1] * 65536));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_ProdCount->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_ProdCount->setText(QString::number(m_Input_Bufer[ActData_ProdCount] + m_Input_Bufer[ActData_ProdCount+1] * 65536));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TOCount->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TOCount->setText(QString::number(m_Input_Bufer[ActData_TOCount] + m_Input_Bufer[ActData_TOCount+1] * 65536));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TUCount->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TUCount->setText(QString::number(m_Input_Bufer[ActData_TUCount] + m_Input_Bufer[ActData_TUCount+1] * 65536));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_RejectCount->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_RejectCount->setText(QString::number(m_Input_Bufer[ActData_RejectCount] + m_Input_Bufer[ActData_RejectCount+1] * 65536));
	}
		
	if (!((Ui::QtPLCDialogClass*)ui)->lE_HardnessChkCnt->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_HardnessChkCnt->setText(QString::number(m_Input_Bufer[ActData_HardnessChkCnt]));
	}
	{
		float hex_res = hexTofloat(HMU_ResultForce);
		((Ui::QtPLCDialogClass*)ui)->lE_ResultForce->setText(QString::number(hex_res));
		((Ui::QtPLCDialogClass*)ui)->lE_ResultForce_2->setText(QString::number(hex_res));
	}

	{
		float hex_res = hexTofloat(HMU_ResultDiam);
		((Ui::QtPLCDialogClass*)ui)->lE_ResultDiam->setText(QString::number(hex_res));
		((Ui::QtPLCDialogClass*)ui)->lE_ResultDiam_2->setText(QString::number(hex_res));
	}

	{
		float hex_res = hexTofloat(HMU_ActForce);
		((Ui::QtPLCDialogClass*)ui)->lE_ActForce->setText(QString::number(hex_res));
		((Ui::QtPLCDialogClass*)ui)->lE_ActForce_2->setText(QString::number(hex_res));

	}
	{
		float hex_res = hexTofloat(TMU_ThicknessResult);
		((Ui::QtPLCDialogClass*)ui)->lE_ThicknessResult->setText(QString::number(hex_res));
		((Ui::QtPLCDialogClass*)ui)->lE_ThicknessResult_2->setText(QString::number(hex_res));
	}


	if (!((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->setText(QString::number(m_Input_Bufer[ActData_SysOveride]/100));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->setText(QString::number(m_Input_Bufer[ActData_GroupSet]));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_GroupCounter->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_GroupCounter->setText(QString::number(m_Input_Bufer[ActData_GroupCounter]));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->setText(QString::number(m_Input_Bufer[ActData_TestInterval]));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TOverload->hasFocus())
	{
		float hex_res = hexTofloat(ActData_TOverload);
		((Ui::QtPLCDialogClass*)ui)->lE_TOverload->setText(QString::number(hex_res));

	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->hasFocus())
	{
		float hex_res = hexTofloat(ActData_TUnderload);
		((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TDemand->hasFocus())
	{
		float hex_res = hexTofloat(ActData_TDemand);
		((Ui::QtPLCDialogClass*)ui)->lE_TDemand->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->hasFocus())
	{
		float hex_res = hexTofloat(ActData_InterOverLoad);
		((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->hasFocus())
	{
		float hex_res = hexTofloat(ActData_InterUnderLoad);
		((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_HMU_Zero->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_HMU_Zero->setText(QString::number(m_Input_Bufer[ActData_HMU_Zero]));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_HMU_K->hasFocus())
	{
		float hex_res = hexTofloat(ActData_HMU_K);
		((Ui::QtPLCDialogClass*)ui)->lE_HMU_K->setText(QString::number(hex_res, 'f', 5));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TMU_Zero->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TMU_Zero->setText(QString::number(m_Input_Bufer[ActData_TMU_Zero]));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TMU_K->hasFocus())
	{
		float hex_res = hexTofloat(ActData_TMU_K);
		((Ui::QtPLCDialogClass*)ui)->lE_TMU_K->setText(QString::number(hex_res, 'f', 5));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_SetPillDiam->hasFocus())
	{
		float hex_res = hexTofloat(ActData_SetPillDiam);
		((Ui::QtPLCDialogClass*)ui)->lE_SetPillDiam->setText(QString::number(hex_res));
	}

	if (!((Ui::QtPLCDialogClass*)ui)->lE_PillDiamOffset->hasFocus())
	{
		float hex_res = hexTofloat(ActData_PillDiamOffset);
		((Ui::QtPLCDialogClass*)ui)->lE_PillDiamOffset->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_HardnessChkNum->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_HardnessChkNum->setText(QString::number(m_Input_Bufer[ActData_HardnessChkNum]));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_RecipeNo->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_RecipeNo->setText(QString::number(m_Input_Bufer[ActData_RecipeNo]));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_ThickUpperLimit->hasFocus())
	{
		float hex_res = hexTofloat(ActData_ThickUpperLimit);
		((Ui::QtPLCDialogClass*)ui)->lE_ThickUpperLimit->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_ThickUnderLimit->hasFocus())
	{
		float hex_res = hexTofloat(ActData_ThickUnderLimit);
		((Ui::QtPLCDialogClass*)ui)->lE_ThickUnderLimit->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_HMU_paraCalibForce->hasFocus())
	{
		float hex_res = hexTofloat(HMU_paraCalibForce);
		((Ui::QtPLCDialogClass*)ui)->lE_HMU_paraCalibForce->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TMU_calibThickness->hasFocus())
	{
		float hex_res = hexTofloat(TMU_calibThickness);
		((Ui::QtPLCDialogClass*)ui)->lE_TMU_calibThickness->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->setText(QString::number(m_Input_Bufer[System_StopSignalDelay]));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_paraTurnUpSpd->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_paraTurnUpSpd->setText(QString::number(m_Input_Bufer[System_paraTurnUpSpd]));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_paraTurnDnSpd->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_paraTurnDnSpd->setText(QString::number(m_Input_Bufer[System_paraTurnDnSpd]));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop0->hasFocus())
	{
		float hex_res = hexTofloat(System_s_trg_stop0);
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop0->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop1->hasFocus())
	{
		float hex_res = hexTofloat(System_s_trg_stop1);
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop1->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop2->hasFocus())
	{
		float hex_res = hexTofloat(System_s_trg_stop2);
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop2->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop3->hasFocus())
	{
		float hex_res = hexTofloat(System_s_trg_stop3);
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop3->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->hasFocus())
	{
		float hex_res = hexTofloat(System_FeedTimeOut);
		((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->hasFocus())
	{
		float hex_res = hexTofloat(System_CapPickInterval);
		((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->hasFocus())
	{
		float hex_res = hexTofloat(System_CapBackInterval);
		((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->hasFocus())
	{
		float hex_res = hexTofloat(System_TireDelay);
		((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->hasFocus())
	{
		float hex_res = hexTofloat(System_ReadDelay);
		((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->hasFocus())
	{
		float hex_res = hexTofloat(System_TireWaitTime);
		((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_paraTurnUpPosition->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_paraTurnUpPosition->setText(QString::number(m_Input_Bufer[System_paraTurnUpPosition] + m_Input_Bufer[System_paraTurnUpPosition + 1] * 65536));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_paraTurnDnPosition->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_paraTurnDnPosition->setText(QString::number(m_Input_Bufer[System_paraTurnDnPosition] + m_Input_Bufer[System_paraTurnDnPosition + 1] * 65536));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_paraPushDestPosition->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_paraPushDestPosition->setText(QString::number(m_Input_Bufer[System_paraPushDestPosition] + m_Input_Bufer[System_paraPushDestPosition + 1] * 65536));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_ForceThresholdSlow->hasFocus())
	{
		float hex_res = hexTofloat(System_ForceThresholdSlow);
		((Ui::QtPLCDialogClass*)ui)->lE_ForceThresholdSlow->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_CapThickValve_t1->hasFocus())
	{
		float hex_res = hexTofloat(System_CapThickValve_t1);
		((Ui::QtPLCDialogClass*)ui)->lE_CapThickValve_t1->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_CapThickValve_t2->hasFocus())
	{
		float hex_res = hexTofloat(System_CapThickValve_t2);
		((Ui::QtPLCDialogClass*)ui)->lE_CapThickValve_t2->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_CapTurnValve_t1->hasFocus())
	{
		float hex_res = hexTofloat(System_CapTurnValve_t1);
		((Ui::QtPLCDialogClass*)ui)->lE_CapTurnValve_t1->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_CapTurnValve_t2->hasFocus())
	{
		float hex_res = hexTofloat(System_CapTurnValve_t2);
		((Ui::QtPLCDialogClass*)ui)->lE_CapTurnValve_t2->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_HMU_PressStopPercent->hasFocus())
	{
		float hex_res = hexTofloat(System_HMU_PressStopPercent);
		((Ui::QtPLCDialogClass*)ui)->lE_HMU_PressStopPercent->setText(QString::number(hex_res));
	}	
	if (!((Ui::QtPLCDialogClass*)ui)->lE_RejectBoxFullNum->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_RejectBoxFullNum->setText(QString::number(m_Input_Bufer[System_RejectBoxFullNum]));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_Scale_Result->hasFocus())
	{
		float hex_res = hexTofloat(Scale_Result);
		((Ui::QtPLCDialogClass*)ui)->lE_Scale_Result->setText(QString::number(hex_res));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedRelMovDistance->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedRelMovDistance->setText(QString::number(m_Input_Bufer[axis0_s_rel] + m_Input_Bufer[axis0_s_rel + 1] * 65536));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_AxisSwingRelMovDistance->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_AxisSwingRelMovDistance->setText(QString::number(m_Input_Bufer[axis1_s_rel] + m_Input_Bufer[axis1_s_rel + 1] * 65536));
	}
#endif
}
float QtPLCDialogClass::hexTofloat(int i)
{
	QString a = QString("%1").arg(m_Input_Bufer[i], 4, 16, QLatin1Char('0'));
	QString b = QString("%1").arg(m_Input_Bufer[i+1], 4, 16, QLatin1Char('0'));
	QString hex_float = b + a; 
	int k = 1;
	if (hex_float.mid(0, 1).toInt(nullptr, 16) >= 8)
	{
		k = -1;
		QString str = QString::number((hex_float.mid(0, 1).toInt(nullptr, 16) - 8), 16);
		hex_float = str + hex_float.mid(1);
	}
	int hex_uint = hex_float.toInt(nullptr, 16);
	float hex_res = *(float*)&hex_uint*k;
	return hex_res;
}

double QtPLCDialogClass::hexToeightbytefloat(int i)
{
	QString a = QString("%1").arg(m_Input_Bufer[i], 4, 16, QLatin1Char('0'));
	QString b = QString("%1").arg(m_Input_Bufer[i + 1], 4, 16, QLatin1Char('0'));
	QString c = QString("%1").arg(m_Input_Bufer[i + 2], 4, 16, QLatin1Char('0'));
	QString d = QString("%1").arg(m_Input_Bufer[i + 3], 4, 16, QLatin1Char('0'));
	QString hex_float = d + c + b + a;
	int k = 1;
	if (hex_float.mid(0, 1).toLongLong(nullptr, 16) >= 8)
	{
		k = -1;
		QString str = QString::number((hex_float.mid(0, 1).toInt(nullptr, 16) - 8), 16);
		hex_float = str + hex_float.mid(1);
	}
	LONGLONG hex_uint = hex_float.toLongLong(nullptr, 16);
	double hex_res = *(double*)&hex_uint*k;
	return hex_res;
}
void QtPLCDialogClass::on_WriteHolding()
{
	if (m_InputFlag == 1 && m_iDontReadRegistersFlag == 1)//已经读过(第一次即可) 且 请求写入
	{
		QString strSend = m_str_sendRegisters.mid(53 * 4, (REGISTERS-52) * 4);
		m_socket->Write_modbus_tcp_HoldingRegisters(strSend, 53, (REGISTERS - 52));//160
		m_iDontReadRegistersFlag = 0;
	}
}
void QtPLCDialogClass::on_WriteCoils()
{
	if (m_CoilsFlag == 1 && m_iDontReadCoilsFlag == 1)//已经读过(第一次即可) 且 请求写入
	{
		QString strSend = m_str_sendCoils.mid(58, COILS-57);
		m_socket->Write_modbus_tcp_Coils(strSend, 58, COILS - 57);//106
		m_iDontReadCoilsFlag = 0;
	}

}
QString QtPLCDialogClass::gettime()
{
QDateTime time = QDateTime::currentDateTime();
QString strtm = time.toString("yyyy-MM-dd hh:mm:ss");
((Ui::QtPLCDialogClass*)ui)->lb_tm->setText(strtm);
return strtm;
}
void QtPLCDialogClass::getPLCData(void* data)
{
	gettime();
	if (m_iDontReadCoilsFlag ==1)
	{
		return;
	}
#ifdef MODBUSTCP
	
	memcpy(dtcoils, (quint8*)data, COILS);//主界面用
	m_str_coils = "0";
	QString st = "0";
	for (int i = 0; i < COILS; i++)
	{
		m_Coils_Bufer[i + 1] = dtcoils[i];
		quint8 a = dtcoils[i];
		QString strtmp = QString::number(a,16);
		m_str_coils += strtmp;
		st += strtmp;
		if (i%10==0 && i!=0)
		{
			st += "_";
		}
		if (i%90==0 && i != 0)
		{
			st += "\n";
		}
	}
	//if (m_CoilsFlag == 0)//第一次赋值
	{
		//((Ui::QtPLCDialogClass*)ui)->label_21->setText(st);
		m_str_sendCoils = m_str_coils;
	}

	m_CoilsFlag = 1;
	//报警
#pragma region alarm
	if (m_Coils_Bufer[Alarm1] == 1 //落料步进报警
		|| m_Coils_Bufer[Alarm2] == 1//旋转步进报警
		|| m_Coils_Bufer[Alarm3] == 1//翻板步进报警
		|| m_Coils_Bufer[Alarm4] == 1//测硬度步进报警
		|| m_Coils_Bufer[Alarm5] == 1//落料超时
		|| m_Coils_Bufer[Alarm6] == 1//秤读数超时
		|| m_Coils_Bufer[Alarm7] == 1//硬度检测失败
		|| m_Coils_Bufer[Alarm31] == 1//剔废盒满
		)
	{
		if (m_Coils_Bufer[Alarm1] == 1 //落料步进报警
			|| m_Coils_Bufer[Alarm2] == 1//旋转步进报警
			|| m_Coils_Bufer[Alarm3] == 1//翻板步进报警
			|| m_Coils_Bufer[Alarm4] == 1//测硬度步进报警
			|| m_Coils_Bufer[Alarm5] == 1//落料超时
			|| m_Coils_Bufer[Alarm6] == 1//秤读数超时
			|| m_Coils_Bufer[Alarm7] == 1//硬度检测失败
			|| m_Coils_Bufer[Alarm31] == 1//剔废盒满
			)
		{
			/*((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setEnabled(false);*/
		}
		((Ui::QtPLCDialogClass*)ui)->lb_Alarm->setStyleSheet("color: rgb(255,0,0);font-size:20pt");
		if (m_Coils_Bufer[Alarm1] == 1)
		{
			if (lg == 0)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("落料步进报警! ");
			if (lg == 1)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("F-Motor err!");
		}
		else if (m_Coils_Bufer[Alarm2] == 1)
		{
			if (lg == 0)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("旋转步进报警!");
			if (lg == 1)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("R-Motor err!");
		}
		else if (m_Coils_Bufer[Alarm3] == 1)
		{
			if (lg == 0)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("翻板步进报警!");
			if (lg == 1)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("T-Motor err!");
		}
		else if (m_Coils_Bufer[Alarm4] == 1)
		{
			if (lg == 0)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("测硬度步进报警!");
			if (lg == 1)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("H-Motor err!");
		}
		else if (m_Coils_Bufer[Alarm5] == 1)
		{
			if (lg == 0)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("落料超时!");
			if (lg == 1)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("Feeding err!");
		}
		else if (m_Coils_Bufer[Alarm6] == 1)
		{
			if (lg == 0)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("秤读数超时!");
			if (lg == 1)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("Weighing err!");
		}
		else if (m_Coils_Bufer[Alarm7] == 1)
		{
			if (lg == 0)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("硬度检测失败!");
			if (lg == 1)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("HardNess err!");
		}
		else if (m_Coils_Bufer[Alarm31] == 1)
		{
			if (lg == 0)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("剔废盒满!");
			if (lg == 1)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("Box full!");
		}
	}
	else
	{
		if (m_istartFlag==0)
		{
			((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setEnabled(true);
		}
		((Ui::QtPLCDialogClass*)ui)->lb_Alarm->setStyleSheet("color: rgb(0, 170, 127);font-size:20pt");
		if (lg == 0)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("设备运行正常~");
		if (lg == 1)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("System normal");
	}
#pragma endregion
	//输入点
#pragma region input
	if (m_Coils_Bufer[Input_FeedTrigger] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->lb_00->setPixmap(QPixmap(AppPath + "/ico/redGreen.png"));
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->lb_00->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));
	}
	if (m_Coils_Bufer[Input_PressTrigger] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->lb_10->setPixmap(QPixmap(AppPath + "/ico/redGreen.png"));
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->lb_10->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));

	}
	if (m_Coils_Bufer[Input_stCapThickValve] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->lb_20->setPixmap(QPixmap(AppPath + "/ico/redGreen.png"));
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->lb_20->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));

	}
	if (m_Coils_Bufer[Input_stCapTurnValve] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->lb_30->setPixmap(QPixmap(AppPath + "/ico/redGreen.png"));
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->lb_30->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));

	}
	if (m_Coils_Bufer[Input_SwingTrigger] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->lb_40->setPixmap(QPixmap(AppPath + "/ico/redGreen.png"));
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->lb_40->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));

	}
	if (m_Coils_Bufer[Input_TurnTrigger] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->lb_60->setPixmap(QPixmap(AppPath + "/ico/redGreen.png"));
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->lb_60->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));

	}
#pragma endregion
	//输出点
#pragma region output
	if (m_Coils_Bufer[ActData_enHMU] == 1)
	{
		if (m_str_sendCoils.mid(ActData_enHMU, 1) == "0")
		{
			((Ui::QtPLCDialogClass*)ui)->pB_enHMUcheckable->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pB_enHMUcheckable->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pB_enHMUcheckable->blockSignals(false);
			((Ui::QtPLCDialogClass*)ui)->pB_enHMUcheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
			m_str_sendCoils.replace(ActData_enHMU, 1, "1");
		}
	}
	else
	{
		if (m_str_sendCoils.mid(ActData_enHMU, 1) == "1")
		{
			((Ui::QtPLCDialogClass*)ui)->pB_enHMUcheckable->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pB_enHMUcheckable->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pB_enHMUcheckable->blockSignals(false);
			((Ui::QtPLCDialogClass*)ui)->pB_enHMUcheckable->setStyleSheet("font: bold;font-size:20pt");
			m_str_sendCoils.replace(ActData_enHMU, 1, "0");
		}
	}
	if (m_Coils_Bufer[ActData_enTMU] == 1)
	{
		if (m_str_sendCoils.mid(ActData_enTMU, 1) == "0")
		{
			((Ui::QtPLCDialogClass*)ui)->pB_enTMUcheckable->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pB_enTMUcheckable->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pB_enTMUcheckable->blockSignals(false);
			((Ui::QtPLCDialogClass*)ui)->pB_enTMUcheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
			m_str_sendCoils.replace(ActData_enTMU, 1, "1");
		}
	}
	else
	{
		if (m_str_sendCoils.mid(ActData_enTMU, 1) == "1")
		{
			((Ui::QtPLCDialogClass*)ui)->pB_enTMUcheckable->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pB_enTMUcheckable->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pB_enTMUcheckable->blockSignals(false);
			((Ui::QtPLCDialogClass*)ui)->pB_enTMUcheckable->setStyleSheet("font: bold;font-size:20pt");
			m_str_sendCoils.replace(ActData_enTMU, 1, "0");
		}
	}
	if (m_Coils_Bufer[HMU_cmdStart] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_HMUStart->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(HMU_cmdStart, 1) == "0")
		{
			m_str_sendCoils.replace(HMU_cmdStart, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_HMUStart->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(HMU_cmdStart, 1) == "1")
		{
			m_str_sendCoils.replace(HMU_cmdStart, 1, "0");
		}
	}
	if (m_Coils_Bufer[HMU_cmdStop] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_HMUStop->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(HMU_cmdStop, 1) == "0")
		{
			m_str_sendCoils.replace(HMU_cmdStop, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_HMUStop->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(HMU_cmdStop, 1) == "1")
		{
			m_str_sendCoils.replace(HMU_cmdStop, 1, "0");
		}
	}
	if (m_Coils_Bufer[HMU_cmdHome] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_HMUHome->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(HMU_cmdHome, 1) == "0")
		{
			m_str_sendCoils.replace(HMU_cmdHome, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_HMUHome->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(HMU_cmdHome, 1) == "1")
		{
			m_str_sendCoils.replace(HMU_cmdHome, 1, "0");
		}
	}
	if (m_Coils_Bufer[HMU_cmdZero] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_HMUZero->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(HMU_cmdZero, 1) == "0")
		{
			m_str_sendCoils.replace(HMU_cmdZero, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_HMUZero->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(HMU_cmdZero, 1) == "1")
		{
			m_str_sendCoils.replace(HMU_cmdZero, 1, "0");
		}
	}
	if (m_Coils_Bufer[HMU_cmdCalibStd] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_HMUCalibStd->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(HMU_cmdCalibStd, 1) == "0")
		{
			m_str_sendCoils.replace(HMU_cmdCalibStd, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_HMUCalibStd->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(HMU_cmdCalibStd, 1) == "1")
		{
			m_str_sendCoils.replace(HMU_cmdCalibStd, 1, "0");
		}
	}
	if (m_Coils_Bufer[HMU_cmdTurn] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_HMUTurn->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(HMU_cmdTurn, 1) == "0")
		{
			m_str_sendCoils.replace(HMU_cmdTurn, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_HMUTurn->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(HMU_cmdTurn, 1) == "1")
		{
			m_str_sendCoils.replace(HMU_cmdTurn, 1, "0");
		}
	}
	if (m_Coils_Bufer[HMU_cmdReject] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_HMUReject->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(HMU_cmdReject, 1) == "0")
		{
			m_str_sendCoils.replace(HMU_cmdReject, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_HMUReject->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(HMU_cmdReject, 1) == "1")
		{
			m_str_sendCoils.replace(HMU_cmdReject, 1, "0");
		}
	}
	if (m_Coils_Bufer[Machine_cmdStart] == 1)
	{
		if (m_str_sendCoils.mid(Machine_cmdStart, 1) == "0")
		{
			m_str_sendCoils.replace(Machine_cmdStart, 1, "1");
		}
	}
	else
	{
		if (m_str_sendCoils.mid(Machine_cmdStart, 1) == "1")
		{
			m_str_sendCoils.replace(Machine_cmdStart, 1, "0");
		}
	}
	if (m_Coils_Bufer[Machine_cmdEStop] == 1)
	{
		if (m_str_sendCoils.mid(Machine_cmdEStop, 1) == "0")
		{
			m_str_sendCoils.replace(Machine_cmdEStop, 1, "1");
		}
	}
	else
	{
		if (m_str_sendCoils.mid(Machine_cmdEStop, 1) == "1")
		{
			m_str_sendCoils.replace(Machine_cmdEStop, 1, "0");
		}
	}
	if (m_Coils_Bufer[TMU_cmdStart] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_TMUStartDelayRelease->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(TMU_cmdStart, 1) == "0")
		{
			m_str_sendCoils.replace(TMU_cmdStart, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_TMUStartDelayRelease->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(TMU_cmdStart, 1) == "1")
		{
			m_str_sendCoils.replace(TMU_cmdStart, 1, "0");
		}
	}
	if (m_Coils_Bufer[TMU_cmdStop] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_TMUStop->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(TMU_cmdStop, 1) == "0")
		{
			m_str_sendCoils.replace(TMU_cmdStop, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_TMUStop->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(TMU_cmdStop, 1) == "1")
		{
			m_str_sendCoils.replace(TMU_cmdStop, 1, "0");
		}
	}
	if (m_Coils_Bufer[TMU_cmdZero] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_TMUZero->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(TMU_cmdZero, 1) == "0")
		{
			m_str_sendCoils.replace(TMU_cmdZero, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_TMUZero->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(TMU_cmdZero, 1) == "1")
		{
			m_str_sendCoils.replace(TMU_cmdZero, 1, "0");
		}
	}
	if (m_Coils_Bufer[TMU_cmdCalib] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_TMUCalib->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(TMU_cmdCalib, 1) == "0")
		{
			m_str_sendCoils.replace(TMU_cmdCalib, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_TMUCalib->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(TMU_cmdCalib, 1) == "1")
		{
			m_str_sendCoils.replace(TMU_cmdCalib, 1, "0");
		}
	}
	if (m_Coils_Bufer[AlarmReset] == 1)
	{
		if (m_str_sendCoils.mid(AlarmReset, 1) == "0")
		{
			m_str_sendCoils.replace(AlarmReset, 1, "1");
		}
	}
	else
	{
		if (m_str_sendCoils.mid(AlarmReset, 1) == "1")
		{
			m_str_sendCoils.replace(AlarmReset, 1, "0");
		}
	}

	if (m_Coils_Bufer[cmdFeedSingle] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedSingle->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(cmdFeedSingle, 1) == "0")
		{
			m_str_sendCoils.replace(cmdFeedSingle, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedSingle->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(cmdFeedSingle, 1) == "1")
		{
			m_str_sendCoils.replace(cmdFeedSingle, 1, "0");
		}
	}
	if (m_Coils_Bufer[cmdFeedFive] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedFive->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(cmdFeedFive, 1) == "0")
		{
			m_str_sendCoils.replace(cmdFeedFive, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedFive->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(cmdFeedFive, 1) == "1")
		{
			m_str_sendCoils.replace(cmdFeedFive, 1, "0");
		}
	}
	if (m_Coils_Bufer[cmdFeedSingleStop] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedSingleStop->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(cmdFeedSingleStop, 1) == "0")
		{
			m_str_sendCoils.replace(cmdFeedSingleStop, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedSingleStop->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(cmdFeedSingleStop, 1) == "1")
		{
			m_str_sendCoils.replace(cmdFeedSingleStop, 1, "0");
		}
	}
	if (m_Coils_Bufer[cmdSwing] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdSwing->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(cmdSwing, 1) == "0")
		{
			m_str_sendCoils.replace(cmdSwing, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdSwing->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(cmdSwing, 1) == "1")
		{
			m_str_sendCoils.replace(cmdSwing, 1, "0");
		}
	}
	if (m_Coils_Bufer[SetCounterZero] == 1)
	{
		if (m_str_sendCoils.mid(SetCounterZero, 1) == "0")
		{
			m_str_sendCoils.replace(SetCounterZero, 1, "1");
		}
	}
	else
	{
		if (m_str_sendCoils.mid(SetCounterZero, 1) == "1")
		{
			m_str_sendCoils.replace(SetCounterZero, 1, "0");
		}
	}
	if (m_Coils_Bufer[cmdCapClean] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdCapClean->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(cmdCapClean, 1) == "0")
		{
			m_str_sendCoils.replace(cmdCapClean, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdCapClean->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(cmdCapClean, 1) == "1")
		{
			m_str_sendCoils.replace(cmdCapClean, 1, "0");
		}
	}
	if (m_Coils_Bufer[cmdGetCap] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdGetCap->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(cmdGetCap, 1) == "0")
		{
			m_str_sendCoils.replace(cmdGetCap, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdGetCap->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(cmdGetCap, 1) == "1")
		{
			m_str_sendCoils.replace(cmdGetCap, 1, "0");
		}
	}	
	if (m_Coils_Bufer[FeedDone] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_FeedDone->setText("1");
		if (m_str_sendCoils.mid(FeedDone, 1) == "0")
		{
			m_str_sendCoils.replace(FeedDone, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->lE_FeedDone->setText("0");
		if (m_str_sendCoils.mid(FeedDone, 1) == "1")
		{
			m_str_sendCoils.replace(FeedDone, 1, "0");
		}
	}
	if (m_Coils_Bufer[cmdFeedAmount] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedAmount->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(cmdFeedAmount, 1) == "0")
		{
			m_str_sendCoils.replace(cmdFeedAmount, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedAmount->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(cmdFeedAmount, 1) == "1")
		{
			m_str_sendCoils.replace(cmdFeedAmount, 1, "0");
		}
	}
	if (m_Coils_Bufer[Output_CapGet]==1)//电磁铁
	{
		if (m_str_sendCoils.mid(Output_CapGet, 1) == "0")
		{
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapGetcheckable->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapGetcheckable->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapGetcheckable->blockSignals(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapGetcheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
			m_str_sendCoils.replace(Output_CapGet, 1, "1");
		}
	}
	else
	{
		if (m_str_sendCoils.mid(Output_CapGet, 1) == "1")
		{
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapGetcheckable->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapGetcheckable->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapGetcheckable->blockSignals(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapGetcheckable->setStyleSheet("font: bold;font-size:20pt");
			m_str_sendCoils.replace(Output_CapGet, 1, "0");
		}
	}
	if (m_Coils_Bufer[Output_AlarmOut] == 1)//报警蜂鸣器
	{
		if (m_str_sendCoils.mid(Output_AlarmOut, 1) == "0")
		{
			((Ui::QtPLCDialogClass*)ui)->pB_cmdAlarmOutcheckable->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdAlarmOutcheckable->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdAlarmOutcheckable->blockSignals(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdAlarmOutcheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
			m_str_sendCoils.replace(Output_AlarmOut, 1, "1");
		}
	}
	else
	{
		if (m_str_sendCoils.mid(Output_AlarmOut, 1) == "1")
		{
			((Ui::QtPLCDialogClass*)ui)->pB_cmdAlarmOutcheckable->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdAlarmOutcheckable->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdAlarmOutcheckable->blockSignals(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdAlarmOutcheckable->setStyleSheet("font: bold;font-size:20pt");
			m_str_sendCoils.replace(Output_AlarmOut, 1, "0");
		}
	}
	if (m_Coils_Bufer[Output_StopSignal] == 1)//停机信号
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdStopSignal->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(Output_StopSignal, 1) == "0")
		{
			m_str_sendCoils.replace(Output_StopSignal, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdStopSignal->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(Output_StopSignal, 1) == "1")
		{
			m_str_sendCoils.replace(Output_StopSignal, 1, "0");
		}
	}
	if (m_Coils_Bufer[Output_AlarmSignal] == 1)//报警输出
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAlarmSignal->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(Output_AlarmSignal, 1) == "0")
		{
			m_str_sendCoils.replace(Output_AlarmSignal, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAlarmSignal->setStyleSheet("font: bold;font-size:20pt");	
		if (m_str_sendCoils.mid(Output_AlarmSignal, 1) == "1")
		{
			m_str_sendCoils.replace(Output_AlarmSignal, 1, "0");
		}
	}
	if (m_Coils_Bufer[Output_YellowAlarmout] == 1)//黄灯报警
	{
		if (m_str_sendCoils.mid(Output_YellowAlarmout, 1) == "0")
		{
			((Ui::QtPLCDialogClass*)ui)->pB_cmdYellowAlarmoutcheckable->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdYellowAlarmoutcheckable->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdYellowAlarmoutcheckable->blockSignals(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdYellowAlarmoutcheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
			m_str_sendCoils.replace(Output_YellowAlarmout, 1, "1");
		}
	}
	else
	{
		if (m_str_sendCoils.mid(Output_YellowAlarmout, 1) == "1")
		{
			((Ui::QtPLCDialogClass*)ui)->pB_cmdYellowAlarmoutcheckable->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdYellowAlarmoutcheckable->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdYellowAlarmoutcheckable->blockSignals(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdYellowAlarmoutcheckable->setStyleSheet("font: bold;font-size:20pt");
			m_str_sendCoils.replace(Output_YellowAlarmout, 1, "0");
		}
	}
	if (m_Coils_Bufer[Output_Baffle] == 1)//挡板
	{
		if (m_str_sendCoils.mid(Output_Baffle, 1) == "0")
		{
			((Ui::QtPLCDialogClass*)ui)->pB_cmdBafflecheckable->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdBafflecheckable->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdBafflecheckable->blockSignals(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdBafflecheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
			m_str_sendCoils.replace(Output_Baffle, 1, "1");
		}
	}
	else
	{
		if (m_str_sendCoils.mid(Output_Baffle, 1) == "1")
		{
			((Ui::QtPLCDialogClass*)ui)->pB_cmdBafflecheckable->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdBafflecheckable->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdBafflecheckable->blockSignals(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdBafflecheckable->setStyleSheet("font: bold;font-size:20pt");
			m_str_sendCoils.replace(Output_Baffle, 1, "0");
		}
	}
	if (m_Coils_Bufer[Output_CapTurnValve] == 1)
	{
		if (m_str_sendCoils.mid(Output_CapTurnValve, 1) == "0")
		{
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapTurnValvecheckable->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapTurnValvecheckable->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapTurnValvecheckable->blockSignals(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapTurnValvecheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
			m_str_sendCoils.replace(Output_CapTurnValve, 1, "1");
		}
	}
	else
	{
		if (m_str_sendCoils.mid(Output_CapTurnValve, 1) == "1")
		{
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapTurnValvecheckable->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapTurnValvecheckable->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapTurnValvecheckable->blockSignals(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapTurnValvecheckable->setStyleSheet("font: bold;font-size:20pt");
			m_str_sendCoils.replace(Output_CapTurnValve, 1, "0");
		}
	}
	if (m_Coils_Bufer[Output_CapThickValve] == 1)
	{
		if (m_str_sendCoils.mid(Output_CapThickValve, 1) == "0")
		{
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapThickValvecheckable->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapThickValvecheckable->setChecked(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapThickValvecheckable->blockSignals(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapThickValvecheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
			m_str_sendCoils.replace(Output_CapThickValve, 1, "1");
		}
	}
	else
	{
		if (m_str_sendCoils.mid(Output_CapThickValve, 1) == "1")
		{
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapThickValvecheckable->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapThickValvecheckable->setChecked(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapThickValvecheckable->blockSignals(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapThickValvecheckable->setStyleSheet("font: bold;font-size:20pt");
			m_str_sendCoils.replace(Output_CapThickValve, 1, "0");
		}
	}

	if (m_Coils_Bufer[axis_fun_axis0_com_rel_pos_start] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedRelMov->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis0_com_rel_pos_start, 1) == "0")
		{
			m_str_sendCoils.replace(axis_fun_axis0_com_rel_pos_start, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedRelMov->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis0_com_rel_pos_start, 1) == "1")
		{
			m_str_sendCoils.replace(axis_fun_axis0_com_rel_pos_start, 1, "0");
		}
	}
	if (m_Coils_Bufer[axis_fun_axis0_com_jog_pos] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedJogPos->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis0_com_jog_pos, 1) == "0")
		{
			m_str_sendCoils.replace(axis_fun_axis0_com_jog_pos, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedJogPos->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis0_com_jog_pos, 1) == "1")
		{
			m_str_sendCoils.replace(axis_fun_axis0_com_jog_pos, 1, "0");
		}
	}
	if (m_Coils_Bufer[axis_fun_axis0_com_jog_neg] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedJogNeg->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis0_com_jog_neg, 1) == "0")
		{
			m_str_sendCoils.replace(axis_fun_axis0_com_jog_neg, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedJogNeg->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis0_com_jog_neg, 1) == "1")
		{
			m_str_sendCoils.replace(axis_fun_axis0_com_jog_neg, 1, "0");
		}
	}
	if (m_Coils_Bufer[axis_fun_axis0_com_pos_move] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedPosMov->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis0_com_pos_move, 1) == "0")
		{
			m_str_sendCoils.replace(axis_fun_axis0_com_pos_move, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedPosMov->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis0_com_pos_move, 1) == "1")
		{
			m_str_sendCoils.replace(axis_fun_axis0_com_pos_move, 1, "0");
		}
	}
	if (m_Coils_Bufer[axis_fun_axis1_com_rel_pos_start] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingRelMov->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis1_com_rel_pos_start, 1) == "0")
		{
			m_str_sendCoils.replace(axis_fun_axis1_com_rel_pos_start, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingRelMov->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis1_com_rel_pos_start, 1) == "1")
		{
			m_str_sendCoils.replace(axis_fun_axis1_com_rel_pos_start, 1, "0");
		}
	}
	if (m_Coils_Bufer[axis_fun_axis1_com_jog_pos] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingJogPos->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis1_com_jog_pos, 1) == "0")
		{
			m_str_sendCoils.replace(axis_fun_axis1_com_jog_pos, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingJogPos->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis1_com_jog_pos, 1) == "1")
		{
			m_str_sendCoils.replace(axis_fun_axis1_com_jog_pos, 1, "0");
		}
	}
	if (m_Coils_Bufer[axis_fun_axis1_com_jog_neg] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingJogNeg->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis1_com_jog_neg, 1) == "0")
		{
			m_str_sendCoils.replace(axis_fun_axis1_com_jog_neg, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingJogNeg->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis1_com_jog_neg, 1) == "1")
		{
			m_str_sendCoils.replace(axis_fun_axis1_com_jog_neg, 1, "0");
		}
	}
	if (m_Coils_Bufer[axis_fun_axis1_com_pos_move] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingPosMov->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis1_com_pos_move, 1) == "0")
		{
			m_str_sendCoils.replace(axis_fun_axis1_com_pos_move, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingPosMov->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis1_com_pos_move, 1) == "1")
		{
			m_str_sendCoils.replace(axis_fun_axis1_com_pos_move, 1, "0");
		}
	}
	if (m_Coils_Bufer[axis_fun_axis1_com_stop_move] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingStopMov->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis1_com_stop_move, 1) == "0")
		{
			m_str_sendCoils.replace(axis_fun_axis1_com_stop_move, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingStopMov->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis1_com_stop_move, 1) == "1")
		{
			m_str_sendCoils.replace(axis_fun_axis1_com_stop_move, 1, "0");
		}
	}
	if (m_Coils_Bufer[axis_fun_axis2_com_jog_neg] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdRollingOverNeg->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis2_com_jog_neg, 1) == "0")
		{
			m_str_sendCoils.replace(axis_fun_axis2_com_jog_neg, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdRollingOverNeg->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis2_com_jog_neg, 1) == "1")
		{
			m_str_sendCoils.replace(axis_fun_axis2_com_jog_neg, 1, "0");
		}
	}
	if (m_Coils_Bufer[axis_fun_axis2_com_jog_pos] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdRollingOverPos->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis2_com_jog_pos, 1) == "0")
		{
			m_str_sendCoils.replace(axis_fun_axis2_com_jog_pos, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdRollingOverPos->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis2_com_jog_pos, 1) == "1")
		{
			m_str_sendCoils.replace(axis_fun_axis2_com_jog_pos, 1, "0");
		}
	}
	if (m_Coils_Bufer[axis_fun_axis3_com_jog_neg] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdPushNeg->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis3_com_jog_neg, 1) == "0")
		{
			m_str_sendCoils.replace(axis_fun_axis3_com_jog_neg, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdPushNeg->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis3_com_jog_neg, 1) == "1")
		{
			m_str_sendCoils.replace(axis_fun_axis3_com_jog_neg, 1, "0");
		}
	}
	if (m_Coils_Bufer[axis_fun_axis3_com_jog_pos] == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdPushPos->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis3_com_jog_pos, 1) == "0")
		{
			m_str_sendCoils.replace(axis_fun_axis3_com_jog_pos, 1, "1");
		}
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdPushPos->setStyleSheet("font: bold;font-size:20pt");
		if (m_str_sendCoils.mid(axis_fun_axis3_com_jog_pos, 1) == "1")
		{
			m_str_sendCoils.replace(axis_fun_axis3_com_jog_pos, 1, "0");
		}
	}

	if (((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->isChecked())
	{
		//thickness
		if (m_Coils_Bufer[Output_CapThickValve] == 1 && m_imeasured == 0) m_imeasured = 1;
		else if (m_Coils_Bufer[Output_CapThickValve] == 0 && m_imeasured==1)
		{
			m_imeasured = 2;
			QTimer *tm = new QTimer();
			connect(tm, &QTimer::timeout, this, [=] {
				m_imeasured = 3;
				tm->stop();
				delete tm;
			});
			tm->start(500);
		}
		else if (m_imeasured==3)
		{
			m_imeasured = 0;
			Thicknesslst << QString::number(hexTofloat(TMU_ThicknessResult)); 
			ThicknessSummary << QString::number(hexTofloat(TMU_ThicknessResult));
		}
		//hardness
		if (m_iHardmeasured==0&&m_Input_Bufer[ActData_HardnessChkCnt] != m_ihardnum && m_Input_Bufer[ActData_HardnessChkCnt] != 0 && m_Coils_Bufer[Input_stCapTurnValve] == 1)//Hardness
		{
			m_iHardmeasured = 1;
		}
		else if (m_iHardmeasured == 1 && m_Coils_Bufer[Input_stCapTurnValve] == 0)
		{
			m_iHardmeasured = 2;
			QTimer *tm = new QTimer();
			connect(tm, &QTimer::timeout, this, [=] {
				m_iHardmeasured = 3;
				tm->stop();
				delete tm;
			});
			tm->start(500);
		}
		else if (m_iHardmeasured == 3)
		{
			m_iHardmeasured = 0;
			m_ihardnum = m_Input_Bufer[ActData_HardnessChkCnt]; 
			HardnessSummary << QString::number(hexTofloat(HMU_ResultForce));

			int i = ((Ui::QtPLCDialogClass*)ui)->tableWidget->verticalHeaderItem(0)->text().toInt();
			for (int k=0;k<i;k++)
			{
				int r = i - k - 1;
				if (((Ui::QtPLCDialogClass*)ui)->tableWidget->item(r, 2)->text()=="-")
				{
					((Ui::QtPLCDialogClass*)ui)->tableWidget->setItem(r, 2, new QTableWidgetItem(QString::number(hexTofloat(HMU_ResultForce))));
					((Ui::QtPLCDialogClass*)ui)->tableWidget->item(r, 2)->setFlags(((Ui::QtPLCDialogClass*)ui)->tableWidget->item(r, 2)->flags() & (~Qt::ItemIsEditable));
					break;
				}
			}
		}
		//weight
		if (m_index != m_Input_Bufer[ActData_GroupIndex] && m_Input_Bufer[ActData_GroupIndex] != 0)
		{
			sumNo = hexToeightbytefloat(ActData_GroupSum) - sumNo;
			if (m_row == 0)
			{
				mi = sumNo;
				ma = sumNo;
			}
			else
			{
				if (mi > sumNo)
				{
					mi = sumNo;
				}
				if (ma < sumNo)
				{
					ma = sumNo;
				}
			}

			data_One << sumNo;

			((Ui::QtPLCDialogClass*)ui)->tableWidget->insertRow(0);
			((Ui::QtPLCDialogClass*)ui)->tableWidget->setVerticalHeaderItem(0, new QTableWidgetItem(QString::number(++m_row)));
			((Ui::QtPLCDialogClass*)ui)->tableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(sumNo,'f',3)));
			((Ui::QtPLCDialogClass*)ui)->tableWidget->setItem(0, 1, new QTableWidgetItem("-"));
			((Ui::QtPLCDialogClass*)ui)->tableWidget->setItem(0, 2, new QTableWidgetItem("-"));
			((Ui::QtPLCDialogClass*)ui)->tableWidget->item(0, 0)->setFlags(((Ui::QtPLCDialogClass*)ui)->tableWidget->item(0, 0)->flags() & (~Qt::ItemIsEditable));				
			((Ui::QtPLCDialogClass*)ui)->tableWidget->item(0, 1)->setFlags(((Ui::QtPLCDialogClass*)ui)->tableWidget->item(0, 1)->flags() & (~Qt::ItemIsEditable));
			((Ui::QtPLCDialogClass*)ui)->tableWidget->item(0, 2)->setFlags(((Ui::QtPLCDialogClass*)ui)->tableWidget->item(0, 2)->flags() & (~Qt::ItemIsEditable));

			if (Thicknesslst.size() > 0)
			{
				((Ui::QtPLCDialogClass*)ui)->tableWidget->item(0, 1)->setText(Thicknesslst.at(0));
				Thicknesslst.removeAt(0);
			}
			if (sumNo < hexTofloat(ActData_TUnderload) || sumNo > hexTofloat(ActData_TOverload))
			{
				((Ui::QtPLCDialogClass*)ui)->tableWidget->item(0, 0)->setBackground(QBrush(QColor(255, 0, 0)));//red
			}
			else if (((sumNo >= hexTofloat(ActData_TUnderload)) && (sumNo < hexTofloat(ActData_InterUnderLoad))) || ((sumNo >= hexTofloat(ActData_InterOverLoad)) && (sumNo <= hexTofloat(ActData_TOverload))))
			{
				((Ui::QtPLCDialogClass*)ui)->tableWidget->item(0, 0)->setBackground(QBrush(QColor(255, 255, 0)));//yellow
			}
			else
			{
				((Ui::QtPLCDialogClass*)ui)->tableWidget->item(0, 0)->setBackground(QBrush(QColor(0, 255, 0)));//green
			}
			//((Ui::QtPLCDialogClass*)ui)->tableWidget->item(0, 0)->setFlags(((Ui::QtPLCDialogClass*)ui)->tableWidget->item(0, 0)->flags() & (~Qt::ItemIsSelectable));
			sumNo = hexToeightbytefloat(ActData_GroupSum);
			m_index = m_Input_Bufer[ActData_GroupIndex];

			if (data_One.size() < 7)
			{
				axisx->setTickCount(data_One.size() + 2);
			}
			else
			{
				axisx->setTickCount(9);
			}
			axisx->setRange(0, data_One.size() + 1);

			axisy->setTickCount(6);
			if (mi == ma)
			{
				axisy->setRange(0, 1);
			}
			else
			{
				axisy->setRange(mi, ma);
			}

			if (isVisible()) {
				splineSeries->clear();
				int dx = 1;// maxX / (maxSize - 1);
				for (int i = 0; i < data_One.size(); i++) {
					splineSeries->append((i + 1)*dx, data_One.at(i));
					//scatterSeries->append(i*dx, data.at(i));
				}
			}
			/*}*/
		}

		if (m_Input_Bufer[GroupDone] == 1)
		{
			QString numb = QString::number(m_Input_Bufer[ActData_GroupNo] + m_Input_Bufer[ActData_GroupNo + 1] * 65536 - 1);
			m_row = 0;
			sumNo = 0;
			m_index = m_Input_Bufer[ActData_GroupIndex];

			if (data_One.size() > 0)
			{
				QString str = "";
				for (int i = 0; i < data_One.size(); i++)
				{
					if (i + 1 < data_One.size())
					{
						str += QString::number(data_One.at(i)) + ",";
					}
					else
					{
						str += QString::number(data_One.at(i));
					}
				}
				QString ymdhm = YearMonthDay();
				QSettings configIniRead(AppPath + "\\data\\data.ini", QSettings::IniFormat);
				configIniRead.setValue(numb + "/data", str);
				QString lkstr = numb + "," + ymdhm + "," + ((Ui::QtPLCDialogClass*)ui)->lE_BatchName->text();
				configIniRead.setValue(numb + "/gn", lkstr);
				configIniRead.setValue(numb + "/theory", QString::number(hexTofloat(ActData_TDemand),'f',3));
				
				str = ThicknessSummary.join(",");
				configIniRead.setValue(numb + "/thick", str);
				str = HardnessSummary.join(",");
				configIniRead.setValue(numb + "/hard", str);
				/*if (m_iHideprint2 == 0)
				{
					configIniRead.setValue(QString::number(m_data->Status.CapDataDisp.GroupNo) + "/CustomerName", m_cn);
					configIniRead.setValue(QString::number(m_data->Status.CapDataDisp.GroupNo) + "/MedicineName", m_mn);
					configIniRead.setValue(QString::number(m_data->Status.CapDataDisp.GroupNo) + "/Low", m_l);
					configIniRead.setValue(QString::number(m_data->Status.CapDataDisp.GroupNo) + "/High", m_h);
					if (m_data->ActData.Feedmode == 0)
					{
						configIniRead.setValue(QString::number(m_data->Status.CapDataDisp.GroupNo) + "/PureShell", m_ps);
					}
					else
					{
						configIniRead.setValue(QString::number(m_data->Status.CapDataDisp.GroupNo) + "/Pressure", m_pressure);
					}
					configIniRead.setValue(QString::number(m_data->Status.CapDataDisp.GroupNo) + "/Yield", m_yield);
					configIniRead.setValue(QString::number(m_data->Status.CapDataDisp.GroupNo) + "/Speed", m_speed);
				}*/

				QSettings timIni(AppPath + "\\data\\time.ini", QSettings::IniFormat);
				QString str1tmp = ymdhm.mid(0, 10);
				str1tmp.remove("/");
				QString str2tmp = ymdhm.remove("/");
				str2tmp.remove(" ");
				str2tmp.remove(":");
				timIni.setValue(str1tmp + "/" + str2tmp, numb);

				QSettings inq(AppPath + "\\data\\inquire.ini", QSettings::IniFormat);
				QString strinqu = inq.value("alldt/data", "").toString();
				if (strinqu.mid(0, 8) != str1tmp)
				{
					if (strinqu != "")
					{
						inq.setValue("alldt/data", str1tmp + "," + strinqu);
					}
					else
					{
						inq.setValue("alldt/data", str1tmp);
					}
				}
				m_imeasured = 0;
				m_iHardmeasured = 0;
				Thicknesslst.clear();
				m_ihardnum = m_Input_Bufer[ActData_HardnessChkCnt];
				HardnessSummary.clear();
				ThicknessSummary.clear();

				data_One.clear();

				if (((Ui::QtPLCDialogClass*)ui)->gB_update->isChecked() == false)
				{
					if (!((Ui::QtPLCDialogClass*)ui)->lE_print1->hasFocus() && !((Ui::QtPLCDialogClass*)ui)->lE_print2->hasFocus())
					{
						if (m_iAutoUpdateFlag == 0)
						{
							((Ui::QtPLCDialogClass*)ui)->lE_print1->setText(numb);
							m_iAutoUpdateFlag = 1;
						}
						//((Ui::QtPLCDialogClass*)ui)->lE_print1->setText(QString::number(m_data->Status.CapDataDisp.GroupNo - 1));
						((Ui::QtPLCDialogClass*)ui)->lE_print2->setText(numb);
					}
				}
				else
				{
					m_iAutoUpdateFlag = 0;
				}
			}
		}
	}
	else
	{
		m_imeasured = 0;
		m_iHardmeasured = 0;
		Thicknesslst.clear();
		HardnessSummary.clear();
		ThicknessSummary.clear();
		m_ihardnum = m_Input_Bufer[ActData_HardnessChkCnt];

		data_One.clear();
		m_row = 0;
		sumNo = 0;
		m_index = m_Input_Bufer[ActData_GroupIndex];
	}
#endif
}//PC显示数据
#pragma endregion
void QtPLCDialogClass::on_lW_data_itemDoubleClicked(QListWidgetItem *item)
{
	QString str = item->text();
	if (((Ui::QtPLCDialogClass*)ui)->lW_data->item(0)->text() == QString::fromLocal8Bit("符合组号") || ((Ui::QtPLCDialogClass*)ui)->lW_data->item(0)->text() == QString::fromLocal8Bit("Matched"))
	{
		if (str == QString::fromLocal8Bit("符合组号") || str == QString::fromLocal8Bit("Matched"))
		{
			((Ui::QtPLCDialogClass*)ui)->lW_data->setVisible(false);
			((Ui::QtPLCDialogClass*)ui)->lb_search->setVisible(false);
			((Ui::QtPLCDialogClass*)ui)->tableWidget->setVisible(true);
		}
		return;
	}
	((Ui::QtPLCDialogClass*)ui)->pB_inquirecheckable->setChecked(false);
	((Ui::QtPLCDialogClass*)ui)->lE_year1->setText(str.mid(0, 4));
	((Ui::QtPLCDialogClass*)ui)->lE_month1->setText(str.mid(4, 2));
	((Ui::QtPLCDialogClass*)ui)->lE_day1->setText(str.mid(6, 2));
}
QString QtPLCDialogClass::setYearMonthDay()
{
	QString strTime;
	QDateTime current_time = QDateTime::currentDateTime();
	QString logYear = QString::number(current_time.date().year());
	logYear = logYear.length() < 4 ? ("0" + logYear) : logYear;
	((Ui::QtPLCDialogClass*)ui)->lE_year1->setText(logYear);
	QString logMonth = QString::number(current_time.date().month());
	logMonth = logMonth.length() < 2 ? ("0" + logMonth) : logMonth;
	((Ui::QtPLCDialogClass*)ui)->lE_month1->setText(logMonth);
	QString logDay = QString::number(current_time.date().day());
	logDay = logDay.length() < 2 ? ("0" + logDay) : logDay;
	((Ui::QtPLCDialogClass*)ui)->lE_day1->setText(logDay);
	QString logHour = QString::number(current_time.time().hour());
	logHour = logHour.length() < 2 ? ("0" + logHour) : logHour;
	/*((Ui::QtPLCDialogClass*)ui)->lE_hour1->setText(logHour);
	((Ui::QtPLCDialogClass*)ui)->lE_hour2->setText(logHour);*/
	((Ui::QtPLCDialogClass*)ui)->lE_hour1->setText("00");
	((Ui::QtPLCDialogClass*)ui)->lE_hour2->setText("23");
	QString logMinute = QString::number(current_time.time().minute());
	logMinute = logMinute.length() < 2 ? ("0" + logMinute) : logMinute;
	/*((Ui::QtPLCDialogClass*)ui)->lE_minute1->setText(logMinute);
	((Ui::QtPLCDialogClass*)ui)->lE_minute2->setText(logMinute);*/
	((Ui::QtPLCDialogClass*)ui)->lE_minute1->setText("00");
	((Ui::QtPLCDialogClass*)ui)->lE_minute2->setText("59");
	strTime = logYear + "/" //z=a>b?x:y
		+ logMonth + "/"
		+ logDay + " "
		+ logHour + ":"
		+ logMinute;
	return strTime;
}
QString QtPLCDialogClass::YearMonthDay()
{
	QString strTime;
	QDateTime current_time = QDateTime::currentDateTime();
	QString logYear = QString::number(current_time.date().year());
	logYear = logYear.length() < 4 ? ("0" + logYear) : logYear;
	QString logMonth = QString::number(current_time.date().month());
	logMonth = logMonth.length() < 2 ? ("0" + logMonth) : logMonth;
	QString logDay = QString::number(current_time.date().day());
	logDay = logDay.length() < 2 ? ("0" + logDay) : logDay;
	QString logHour = QString::number(current_time.time().hour());
	logHour = logHour.length() < 2 ? ("0" + logHour) : logHour;
	QString logMinute = QString::number(current_time.time().minute());
	logMinute = logMinute.length() < 2 ? ("0" + logMinute) : logMinute;
	strTime = logYear + "/" //z=a>b?x:y
		+ logMonth + "/"
		+ logDay + " "
		+ logHour + ":"
		+ logMinute;
	return strTime;
}
#pragma region popup window

void QtPLCDialogClass::initDlg()
{

}

void QtPLCDialogClass::setWindowMinimized()
{
	((Ui::QtPLCDialogClass*)ui)->pB_dtDlgcheckable->setChecked(false);
}

int QtPLCDialogClass::showMsgBox(const char* titleStr, const char* contentStr, const char* button1Str, const char* button2Str)
{
	if (QString::fromLocal8Bit(button2Str) == "")
	{
		QMessageBox msg(QMessageBox::Information, QString::fromLocal8Bit(titleStr), QString::fromLocal8Bit(contentStr), QMessageBox::Yes);
		msg.setButtonText(QMessageBox::Yes, QString::fromLocal8Bit(button1Str));
		msg.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
		msg.setWindowIcon(QIcon("./ico/dr.ico"));
		return msg.exec();
	}
	else
	{
		QMessageBox msg(QMessageBox::Question, QString::fromLocal8Bit(titleStr), QString::fromLocal8Bit(contentStr), QMessageBox::Yes | QMessageBox::No);
		msg.setButtonText(QMessageBox::No, QString::fromLocal8Bit(button2Str));
		msg.setButtonText(QMessageBox::Yes, QString::fromLocal8Bit(button1Str));
		msg.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
		msg.setWindowIcon(QIcon("./ico/dr.ico"));
		return msg.exec();
	}

	//  QMessageBox::NoIcon
	//	QMessageBox::Question
	//	QMessageBox::Information
	//	QMessageBox::Warning
	//	QMessageBox::Critical
}
//void QtPLCDialogClass::emit showWindowOut(QString str)
//{
//	levelOut = new WindowOut(this);
//	levelOut->setWindowCount(0);
//	levelOut->getString(str, 2000);
//	levelOut->show();
//}
#pragma endregion

#pragma region ui run slots

void QtPLCDialogClass::on_lE_year1_editingFinished()//超重重量,单位g
{
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_year1->text();
	int index = str.toInt();
	if (index < 2020)
	{
		index = 2020;
	}
	if (index > 9999)
	{
		index = 9999;
	}
	str = QString::number(index);
	str = str.length() < 4 ? ("0" + str) : str;
	((Ui::QtPLCDialogClass*)ui)->lE_year1->setText(str);
}
void QtPLCDialogClass::on_lE_month1_editingFinished()//超重重量,单位g
{
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_month1->text();
	int index = str.toInt();
	if (index < 1)
	{
		index = 1;
	}
	if (index > 12)
	{
		index = 12;
	}
	str = QString::number(index);
	str = str.length() < 2 ? ("0" + str) : str;
	((Ui::QtPLCDialogClass*)ui)->lE_month1->setText(str);
}
void QtPLCDialogClass::on_lE_day1_editingFinished()//超重重量,单位g
{
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_day1->text();
	int index = str.toInt();
	if (index<1)
	{
		index = 1;
	}
	if (index>31)
	{
		index = 31;
	}
	str = QString::number(index);
	str = str.length() < 2 ? ("0" + str) : str;
	((Ui::QtPLCDialogClass*)ui)->lE_day1->setText(str);
}

void QtPLCDialogClass::on_lE_hour1_editingFinished()//超重重量,单位g
{
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_hour1->text();
	int index = str.toInt();
	if (index < 0)
	{
		index = 0;
	}
	if (index > 23)
	{
		index = 23;
	}
	str = QString::number(index);
	str = str.length() < 2 ? ("0" + str) : str;
	((Ui::QtPLCDialogClass*)ui)->lE_hour1->setText(str);
}
void QtPLCDialogClass::on_lE_hour2_editingFinished()//超重重量,单位g
{
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_hour2->text();
	int index = str.toInt();
	if (index < 0)
	{
		index = 0;
	}
	if (index > 23)
	{
		index = 23;
	}
	str = QString::number(index);
	str = str.length() < 2 ? ("0" + str) : str;
	((Ui::QtPLCDialogClass*)ui)->lE_hour2->setText(str);
}
void QtPLCDialogClass::on_lE_minute1_editingFinished()//超重重量,单位g
{
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_minute1->text();
	int index = str.toInt();
	if (index < 0)
	{
		index = 0;
	}
	if (index > 23)
	{
		index = 23;
	}
	str = QString::number(index);
	str = str.length() < 2 ? ("0" + str) : str;
	((Ui::QtPLCDialogClass*)ui)->lE_minute1->setText(str);
}
void QtPLCDialogClass::on_lE_minute2_editingFinished()//超重重量,单位g
{
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_minute2->text();
	int index = str.toInt();
	if (index < 0)
	{
		index = 0;
	}
	if (index > 59)
	{
		index = 59;
	}
	str = QString::number(index);
	str = str.length() < 2 ? ("0" + str) : str;
	((Ui::QtPLCDialogClass*)ui)->lE_minute2->setText(str);
}


void QtPLCDialogClass::on_lE_SysOveride_editingFinished()//系统速度，0-10000对应0-100%
{
	m_str_sendRegisters = m_str_registers;
	if (((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->text().toUShort() < 0)
		((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->setText("0");
	else if (((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->text().toUShort() > 100)
		((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->setText("100");

	m_iDontReadRegistersFlag = 1;
	QString oldstr = m_str_sendRegisters.mid(ActData_SysOveride * 4, 4);
	ushort a = ((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->text().toUShort() * 100;
	QString str = QString("%1").arg(a, 4, 16, QLatin1Char('0'));
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(ActData_SysOveride * 4, 4, str);
	((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->blockSignals(false);
}
void QtPLCDialogClass::on_lE_GroupSet_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	if (((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->text().toUShort() < 0)
		((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->setText("0");
	else if (((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->text().toUShort() > 100)
		((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->setText("100");

	m_iDontReadRegistersFlag = 1;
	QString oldstr = m_str_sendRegisters.mid(ActData_GroupSet * 4, 4);
	ushort a = ((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->text().toUShort();
	QString str = QString("%1").arg(a, 4, 16, QLatin1Char('0'));
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(ActData_GroupSet * 4, 4, str);
	((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->blockSignals(false);
}

void QtPLCDialogClass::on_lE_GroupCounter_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	if (((Ui::QtPLCDialogClass*)ui)->lE_GroupCounter->text().toUShort() < 0)
		((Ui::QtPLCDialogClass*)ui)->lE_GroupCounter->setText("0");
	else if (((Ui::QtPLCDialogClass*)ui)->lE_GroupCounter->text().toUShort() > 100)
		((Ui::QtPLCDialogClass*)ui)->lE_GroupCounter->setText("100");
#ifdef MODBUSTCP
	m_iDontReadRegistersFlag = 1;
	QString oldstr = m_str_sendRegisters.mid(ActData_GroupCounter * 4, 4);
	ushort a = ((Ui::QtPLCDialogClass*)ui)->lE_GroupCounter->text().toUShort();
	QString str = QString("%1").arg(a, 4, 16, QLatin1Char('0'));
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_GroupCounter->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_GroupCounter->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_GroupCounter->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(ActData_GroupCounter * 4, 4, str);
	((Ui::QtPLCDialogClass*)ui)->lE_GroupCounter->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_GroupCounter->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_GroupCounter->blockSignals(false);
#endif
}
void QtPLCDialogClass::on_lE_TestInterval_editingFinished()///测试间隔时间,单位s
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;
	QString oldstr = m_str_sendRegisters.mid(ActData_TestInterval * 4, 4);
	ushort a = ((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->text().toUShort();
	if (a < 60) a = 60;
	QString str = QString("%1").arg(a, 4, 16, QLatin1Char('0'));
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(ActData_TestInterval * 4, 4, str);

	((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->blockSignals(false);
}

void QtPLCDialogClass::on_lE_TOverload_editingFinished()//超重重量,单位g
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_TOverload->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(ActData_TOverload * 4, 4);
	QString str2 = m_str_sendRegisters.mid(ActData_TOverload_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TOverload->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_TOverload->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_TOverload->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(ActData_TOverload * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(ActData_TOverload_Reserve * 4, 4, f_hex.mid(0, 4));

	((Ui::QtPLCDialogClass*)ui)->lE_TOverload->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_TOverload->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_TOverload->blockSignals(false);
}

void QtPLCDialogClass::on_lE_TUnderload_editingFinished()//超轻重量,单位g
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(ActData_TUnderload * 4, 4);
	QString str2 = m_str_sendRegisters.mid(ActData_TUnderload_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(ActData_TUnderload * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(ActData_TUnderload_Reserve * 4, 4, f_hex.mid(0, 4));

	((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->blockSignals(false);
}
void QtPLCDialogClass::on_lE_TDemand_editingFinished()///期望重量,单位g	
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_TDemand->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(ActData_TDemand * 4, 4);
	QString str2 = m_str_sendRegisters.mid(ActData_TDemand_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TDemand->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_TDemand->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_TDemand->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(ActData_TDemand * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(ActData_TDemand_Reserve * 4, 4, f_hex.mid(0, 4));

	((Ui::QtPLCDialogClass*)ui)->lE_TDemand->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_TDemand->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_TDemand->blockSignals(false);
}
void QtPLCDialogClass::on_lE_InterOverLoad_editingFinished()//内控线，上限,单位g
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(ActData_InterOverLoad * 4, 4);
	QString str2 = m_str_sendRegisters.mid(ActData_InterOverLoad_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(ActData_InterOverLoad * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(ActData_InterOverLoad_Reserve * 4, 4, f_hex.mid(0, 4));

	((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->blockSignals(false);
}
void QtPLCDialogClass::on_lE_InterUnderLoad_editingFinished()//内控线，下限,单位g
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(ActData_InterUnderLoad * 4, 4);
	QString str2 = m_str_sendRegisters.mid(ActData_InterUnderLoad_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(ActData_InterUnderLoad * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(ActData_InterUnderLoad_Reserve * 4, 4, f_hex.mid(0, 4));

	((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->blockSignals(false);
}
void QtPLCDialogClass::on_lE_SetPillDiam_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_SetPillDiam->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(ActData_SetPillDiam * 4, 4);
	QString str2 = m_str_sendRegisters.mid(ActData_SetPillDiam_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_SetPillDiam->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_SetPillDiam->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_SetPillDiam->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(ActData_SetPillDiam * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(ActData_SetPillDiam_Reserve * 4, 4, f_hex.mid(0, 4));

	((Ui::QtPLCDialogClass*)ui)->lE_SetPillDiam->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_SetPillDiam->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_SetPillDiam->blockSignals(false);
}
void QtPLCDialogClass::on_lE_PillDiamOffset_editingFinished()//内控线，下限,单位g
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_PillDiamOffset->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(ActData_PillDiamOffset * 4, 4);
	QString str2 = m_str_sendRegisters.mid(ActData_PillDiamOffset_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_PillDiamOffset->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_PillDiamOffset->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_PillDiamOffset->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(ActData_PillDiamOffset * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(ActData_PillDiamOffset_Reserve * 4, 4, f_hex.mid(0, 4));

	((Ui::QtPLCDialogClass*)ui)->lE_PillDiamOffset->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_PillDiamOffset->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_PillDiamOffset->blockSignals(false);
}
void QtPLCDialogClass::on_lE_HardnessChkNum_editingFinished()
{
	m_str_sendRegisters = m_str_registers;

	m_iDontReadRegistersFlag = 1;
	QString oldstr = m_str_sendRegisters.mid(ActData_HardnessChkNum * 4, 4);
	int a = ((Ui::QtPLCDialogClass*)ui)->lE_HardnessChkNum->text().toUShort();
	QString str = QString("%1").arg(a, 4, 16, QLatin1Char('0'));
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_HardnessChkNum->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_HardnessChkNum->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_HardnessChkNum->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(ActData_HardnessChkNum * 4, 4, str);

	((Ui::QtPLCDialogClass*)ui)->lE_HardnessChkNum->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_HardnessChkNum->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_HardnessChkNum->blockSignals(false);
}
void QtPLCDialogClass::on_lE_RecipeNo_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	if (((Ui::QtPLCDialogClass*)ui)->lE_RecipeNo->text().toInt() < 0)
		((Ui::QtPLCDialogClass*)ui)->lE_RecipeNo->setText("0");
	m_iDontReadRegistersFlag = 1;
	QString oldstr = m_str_sendRegisters.mid(ActData_RecipeNo * 4, 4);
	int a = ((Ui::QtPLCDialogClass*)ui)->lE_RecipeNo->text().toInt();
	QString str = QString("%1").arg(a, 4, 16, QLatin1Char('0'));
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_RecipeNo->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_RecipeNo->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_RecipeNo->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(ActData_RecipeNo * 4, 4, str);
	((Ui::QtPLCDialogClass*)ui)->lE_RecipeNo->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_RecipeNo->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_RecipeNo->blockSignals(false);

	QTimer *tm = new QTimer();
	connect(tm, &QTimer::timeout, this, [=] {
		m_str_sendRegisters = m_str_registers;
		m_iDontReadRegistersFlag = 1;
		m_str_sendRegisters.replace(Recipe_enable * 4, 4, "0001");
		tm->stop();
		delete tm;
	});
	tm->start(500);
}
void QtPLCDialogClass::on_lE_ThickUpperLimit_editingFinished()
{

	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_ThickUpperLimit->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(ActData_ThickUpperLimit * 4, 4);
	QString str2 = m_str_sendRegisters.mid(ActData_ThickUpperLimit_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_ThickUpperLimit->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_ThickUpperLimit->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_ThickUpperLimit->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(ActData_ThickUpperLimit * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(ActData_ThickUpperLimit_Reserve * 4, 4, f_hex.mid(0, 4));

	((Ui::QtPLCDialogClass*)ui)->lE_ThickUpperLimit->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_ThickUpperLimit->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_ThickUpperLimit->blockSignals(false);
}
void QtPLCDialogClass::on_lE_ThickUnderLimit_editingFinished()
{

	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_ThickUnderLimit->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(ActData_ThickUnderLimit * 4, 4);
	QString str2 = m_str_sendRegisters.mid(ActData_ThickUnderLimit_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_ThickUnderLimit->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_ThickUnderLimit->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_ThickUnderLimit->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(ActData_ThickUnderLimit * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(ActData_ThickUnderLimit_Reserve * 4, 4, f_hex.mid(0, 4));

	((Ui::QtPLCDialogClass*)ui)->lE_ThickUnderLimit->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_ThickUnderLimit->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_ThickUnderLimit->blockSignals(false);
}
void QtPLCDialogClass::on_lE_HMU_paraCalibForce_editingFinished()
{

	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_HMU_paraCalibForce->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(HMU_paraCalibForce * 4, 4);
	QString str2 = m_str_sendRegisters.mid(HMU_paraCalibForce_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_HMU_paraCalibForce->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_HMU_paraCalibForce->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_HMU_paraCalibForce->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(HMU_paraCalibForce * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(HMU_paraCalibForce_Reserve * 4, 4, f_hex.mid(0, 4));

	((Ui::QtPLCDialogClass*)ui)->lE_HMU_paraCalibForce->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_HMU_paraCalibForce->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_HMU_paraCalibForce->blockSignals(false);
}
void QtPLCDialogClass::on_lE_TMU_calibThickness_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_TMU_calibThickness->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(TMU_calibThickness * 4, 4);
	QString str2 = m_str_sendRegisters.mid(TMU_calibThickness_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TMU_calibThickness->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_TMU_calibThickness->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_TMU_calibThickness->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(TMU_calibThickness * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(TMU_calibThickness_Reserve * 4, 4, f_hex.mid(0, 4));

	((Ui::QtPLCDialogClass*)ui)->lE_TMU_calibThickness->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_TMU_calibThickness->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_TMU_calibThickness->blockSignals(false);
}	
void QtPLCDialogClass::on_lE_HMU_Zero_editingFinished()
{
	m_str_sendRegisters = m_str_registers;

	m_iDontReadRegistersFlag = 1;
	QString oldstr = m_str_sendRegisters.mid(ActData_HMU_Zero * 4, 4);
	int a = ((Ui::QtPLCDialogClass*)ui)->lE_HMU_Zero->text().toUShort();
	QString str = QString("%1").arg(a, 4, 16, QLatin1Char('0'));
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_HMU_Zero->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_HMU_Zero->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_HMU_Zero->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(ActData_HMU_Zero * 4, 4, str);

	((Ui::QtPLCDialogClass*)ui)->lE_HMU_Zero->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_HMU_Zero->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_HMU_Zero->blockSignals(false);
}

void QtPLCDialogClass::on_lE_HMU_K_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_HMU_K->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(ActData_HMU_K * 4, 4);
	QString str2 = m_str_sendRegisters.mid(ActData_HMU_K_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_HMU_K->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_HMU_K->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_HMU_K->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(ActData_HMU_K * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(ActData_HMU_K_Reserve * 4, 4, f_hex.mid(0, 4));

	((Ui::QtPLCDialogClass*)ui)->lE_HMU_K->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_HMU_K->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_HMU_K->blockSignals(false);
}
void QtPLCDialogClass::on_lE_TMU_Zero_editingFinished()
{
	m_str_sendRegisters = m_str_registers;

	m_iDontReadRegistersFlag = 1;
	QString oldstr = m_str_sendRegisters.mid(ActData_TMU_Zero * 4, 4);
	int a = ((Ui::QtPLCDialogClass*)ui)->lE_TMU_Zero->text().toUShort();
	QString str = QString("%1").arg(a, 4, 16, QLatin1Char('0'));
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TMU_Zero->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_TMU_Zero->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_TMU_Zero->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(ActData_TMU_Zero * 4, 4, str);

	((Ui::QtPLCDialogClass*)ui)->lE_TMU_Zero->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_TMU_Zero->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_TMU_Zero->blockSignals(false);
}
void QtPLCDialogClass::on_lE_TMU_K_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_TMU_K->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(ActData_TMU_K * 4, 4);
	QString str2 = m_str_sendRegisters.mid(ActData_TMU_K_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TMU_K->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_TMU_K->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_TMU_K->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(ActData_TMU_K * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(ActData_TMU_K_Reserve * 4, 4, f_hex.mid(0, 4));

	((Ui::QtPLCDialogClass*)ui)->lE_TMU_K->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_TMU_K->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_TMU_K->blockSignals(false);
}
void QtPLCDialogClass::on_pB_Read1_clicked()//读取1
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;
	m_str_sendRegisters.replace(System_enable * 4, 4, "0001");
	if (lg == 0)emit showWindowOut(QString::fromLocal8Bit("PLC默认参数\n已读取!"));
	if (lg == 1)emit showWindowOut(QString::fromLocal8Bit("PLC default parameters are read!"));

}

void QtPLCDialogClass::on_pB_Write1_clicked()//写入1
{
	QTimer *tm = new QTimer();
	connect(tm, &QTimer::timeout, this, [=] {
		m_str_sendRegisters = m_str_registers;
		m_iDontReadRegistersFlag = 1;
		m_str_sendRegisters.replace(System_enable * 4, 4, "0002");
		tm->stop();
		delete tm;
	}); 
	tm->start(500);
	if (lg == 0)emit showWindowOut(QString::fromLocal8Bit("PLC默认参数\n已保存!"));
	if (lg == 1)emit showWindowOut(QString::fromLocal8Bit("PLC default Parameters are saved!"));

}
void QtPLCDialogClass::on_pB_Recipe_enable_clicked()//配方保存
{
	QTimer *tm = new QTimer();
	connect(tm, &QTimer::timeout, this, [=] {
		m_str_sendRegisters = m_str_registers;
		m_iDontReadRegistersFlag = 1;
		m_str_sendRegisters.replace(Recipe_enable * 4, 4, "0002");
		tm->stop();
		delete tm;
	});
	tm->start(500);
	if (lg == 0)emit showWindowOut(QString::fromLocal8Bit("配方\n已保存!"));
	if (lg == 1)emit showWindowOut(QString::fromLocal8Bit("Recipe are saved!"));

}

void QtPLCDialogClass::on_lE_StopSignalDelay_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	if (((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->text().toInt() < 0)
		((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->setText("0");
	m_iDontReadRegistersFlag = 1;
	QString oldstr = m_str_sendRegisters.mid(System_StopSignalDelay * 4, 4);
	int a = ((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->text().toInt();
	QString str = QString("%1").arg(a, 4, 16, QLatin1Char('0'));
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_StopSignalDelay * 4, 4, str);
	((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->blockSignals(false);
}
void QtPLCDialogClass::on_lE_paraTurnUpSpd_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	if (((Ui::QtPLCDialogClass*)ui)->lE_paraTurnUpSpd->text().toInt() < 0)
		((Ui::QtPLCDialogClass*)ui)->lE_paraTurnUpSpd->setText("0");
	m_iDontReadRegistersFlag = 1;
	QString oldstr = m_str_sendRegisters.mid(System_paraTurnUpSpd * 4, 4);
	int a = ((Ui::QtPLCDialogClass*)ui)->lE_paraTurnUpSpd->text().toInt();
	QString str = QString("%1").arg(a, 4, 16, QLatin1Char('0'));
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_paraTurnUpSpd->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_paraTurnUpSpd->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_paraTurnUpSpd->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_paraTurnUpSpd * 4, 4, str);
	((Ui::QtPLCDialogClass*)ui)->lE_paraTurnUpSpd->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_paraTurnUpSpd->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_paraTurnUpSpd->blockSignals(false);
}
void QtPLCDialogClass::on_lE_paraTurnDnSpd_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	if (((Ui::QtPLCDialogClass*)ui)->lE_paraTurnDnSpd->text().toInt() < 0)
		((Ui::QtPLCDialogClass*)ui)->lE_paraTurnDnSpd->setText("0");
	m_iDontReadRegistersFlag = 1;
	QString oldstr = m_str_sendRegisters.mid(System_paraTurnDnSpd * 4, 4);
	int a = ((Ui::QtPLCDialogClass*)ui)->lE_paraTurnDnSpd->text().toInt();
	QString str = QString("%1").arg(a, 4, 16, QLatin1Char('0'));
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_paraTurnDnSpd->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_paraTurnDnSpd->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_paraTurnDnSpd->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_paraTurnDnSpd * 4, 4, str);
	((Ui::QtPLCDialogClass*)ui)->lE_paraTurnDnSpd->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_paraTurnDnSpd->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_paraTurnDnSpd->blockSignals(false);
}

void QtPLCDialogClass::on_lE_FeedOveride_editingFinished()///每组测试胶囊数量
{
	QString oldstr = QString::number(m_data->ActData.FeedOveride);
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_FeedOveride->text();
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_FeedOveride->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_FeedOveride->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_FeedOveride->blockSignals(false);
		return;
	}
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.ActData.FeedOveride = ((Ui::QtPLCDialogClass*)ui)->lE_FeedOveride->text().toInt()>200?20000: ((Ui::QtPLCDialogClass*)ui)->lE_FeedOveride->text().toInt()*100;
	m_socket->Communicate_PLC(&typ, nullptr);
	((Ui::QtPLCDialogClass*)ui)->lE_FeedOveride->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_FeedOveride->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_FeedOveride->blockSignals(false);
}

void QtPLCDialogClass::on_lE_MultiCount_editingFinished()///测试间隔时间,单位s
{
	m_str_sendRegisters = m_str_registers;
	if (((Ui::QtPLCDialogClass*)ui)->lE_MultiCount->text().toInt() < 0)
		((Ui::QtPLCDialogClass*)ui)->lE_MultiCount->setText("0");
	m_iDontReadRegistersFlag = 1;
	QString oldstr = m_str_sendRegisters.mid(ActData_FeedAmount * 4, 4);
	int a = ((Ui::QtPLCDialogClass*)ui)->lE_MultiCount->text().toInt();
	QString str = QString("%1").arg(a, 2, 16, QLatin1Char('0'));
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_MultiCount->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_MultiCount->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_MultiCount->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(ActData_FeedAmount * 4, 4, str);
	((Ui::QtPLCDialogClass*)ui)->lE_MultiCount->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_MultiCount->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_MultiCount->blockSignals(false);
}
void QtPLCDialogClass::on_lE_BatchName_textChanged(const QString &arg1)
{
	if (arg1=="")
	{
		QString oldstr = QString(QLatin1String(m_data->ActData.BatchName));
		QString str = ((Ui::QtPLCDialogClass*)ui)->lE_BatchName->text();
			if (oldstr == str)
			{
				((Ui::QtPLCDialogClass*)ui)->lE_BatchName->blockSignals(true);
				((Ui::QtPLCDialogClass*)ui)->lE_BatchName->clearFocus();
				((Ui::QtPLCDialogClass*)ui)->lE_BatchName->blockSignals(false);
				return;
			}
			DataFromPC_typ typ;
			typ = getPCRunData();
			typ.Telegram_typ = 4;
			QByteArray ba = str.toLatin1();
			char *c = ba.data();
			strcpy(typ.ActData.BatchName, c);
			m_socket->Communicate_PLC(&typ, nullptr);
		((Ui::QtPLCDialogClass*)ui)->lE_BatchName->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_BatchName->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_BatchName->blockSignals(false);
	}
}
void QtPLCDialogClass::on_lE_BatchName_editingFinished()//批号字符串
{
	QString oldstr = QString(QLatin1String(m_data->ActData.BatchName));
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_BatchName->text();
	if (str != "")
	{
		if (oldstr == str)
		{
			((Ui::QtPLCDialogClass*)ui)->lE_BatchName->blockSignals(true);
			((Ui::QtPLCDialogClass*)ui)->lE_BatchName->clearFocus();
			((Ui::QtPLCDialogClass*)ui)->lE_BatchName->blockSignals(false);
			return;
		}
		DataFromPC_typ typ;
		typ = getPCRunData();
		typ.Telegram_typ = 4;
		QByteArray ba = str.toLatin1();
		char *c = ba.data();
		strcpy(typ.ActData.BatchName, c);
		m_socket->Communicate_PLC(&typ, nullptr);
	}
	((Ui::QtPLCDialogClass*)ui)->lE_BatchName->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_BatchName->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_BatchName->blockSignals(false);
}

void QtPLCDialogClass::on_pB_cmdAxisFeedRelMov_clicked()//下料相对运动启动，1:执行，自动复位
{
	QTimer *tm = new QTimer();
	connect(tm, &QTimer::timeout, this, [=] {
		m_iDontReadCoilsFlag = 1;
		m_str_sendCoils.replace(axis_fun_axis0_com_rel_pos_start, 1, "1");
		tm->stop();
		delete tm;
	});
	tm->start(500);
}
void QtPLCDialogClass::on_pB_cmdAxisSwingRelMov_clicked()//旋转相对运动启动，1:执行，自动复位
{
	QTimer *tm = new QTimer();
	connect(tm, &QTimer::timeout, this, [=] {
		m_iDontReadCoilsFlag = 1;
		m_str_sendCoils.replace(axis_fun_axis1_com_rel_pos_start, 1, "1");
		tm->stop();
		delete tm;
	});
	tm->start(500);
}
void QtPLCDialogClass::on_lE_AxisFeedRelMovDistance_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;
	QString oldstr = m_str_sendRegisters.mid(axis0_s_rel * 4, 4);
	int a = ((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedRelMovDistance->text().toInt();
	QString str = QString("%1").arg(a, 4, 16, QLatin1Char('0'));
	m_str_sendRegisters.replace(axis0_s_rel * 4, 4, str);
}
void QtPLCDialogClass::on_lE_AxisSwingRelMovDistance_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;
	QString oldstr = m_str_sendRegisters.mid(axis1_s_rel * 4, 4);
	int a = ((Ui::QtPLCDialogClass*)ui)->lE_AxisSwingRelMovDistance->text().toInt();
	QString str = QString("%1").arg(a, 4, 16, QLatin1Char('0'));
	m_str_sendRegisters.replace(axis1_s_rel * 4, 4, str);
}
/*void QtPLCDialogClass::on_lE_GroupNo_editingFinished()//当前组号,单位s
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.ActData.GroupNo = ((Ui::QtPLCDialogClass*)ui)->lE_GroupNo->text().toUInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}*/
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
void QtPLCDialogClass::on_lE_s_trg_stop0_editingFinished()
{

	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop0->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(System_s_trg_stop0 * 4, 4);
	QString str2 = m_str_sendRegisters.mid(System_s_trg_stop0_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop0->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop0->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop0->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_s_trg_stop0 * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(System_s_trg_stop0_Reserve * 4, 4, f_hex.mid(0, 4));

	((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop0->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop0->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop0->blockSignals(false);
}
void QtPLCDialogClass::on_lE_s_trg_stop1_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop1->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(System_s_trg_stop1 * 4, 4);
	QString str2 = m_str_sendRegisters.mid(System_s_trg_stop1_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop1->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop1->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop1->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_s_trg_stop1 * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(System_s_trg_stop1_Reserve * 4, 4, f_hex.mid(0, 4));

	((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop1->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop1->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop1->blockSignals(false);
}
void QtPLCDialogClass::on_lE_s_trg_stop2_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop2->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(System_s_trg_stop2 * 4, 4);
	QString str2 = m_str_sendRegisters.mid(System_s_trg_stop2_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop2->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop2->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop2->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_s_trg_stop2 * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(System_s_trg_stop2_Reserve * 4, 4, f_hex.mid(0, 4));

	((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop2->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop2->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop2->blockSignals(false);
}
void QtPLCDialogClass::on_lE_s_trg_stop3_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop3->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(System_s_trg_stop3 * 4, 4);
	QString str2 = m_str_sendRegisters.mid(System_s_trg_stop3_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop3->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop3->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop3->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_s_trg_stop3 * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(System_s_trg_stop3_Reserve * 4, 4, f_hex.mid(0, 4));

	((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop3->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop3->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop3->blockSignals(false);
}


void QtPLCDialogClass::on_lE_FeedTimeOut_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(System_FeedTimeOut * 4, 4);
	QString str2 = m_str_sendRegisters.mid(System_FeedTimeOut_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_FeedTimeOut * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(System_FeedTimeOut_Reserve * 4, 4, f_hex.mid(0, 4));

	((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->blockSignals(false);
}
void QtPLCDialogClass::on_lE_CapPickInterval_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(System_CapPickInterval * 4, 4);
	QString str2 = m_str_sendRegisters.mid(System_CapPickInterval_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_CapPickInterval * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(System_CapPickInterval_Reserve * 4, 4, f_hex.mid(0, 4));
	((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->blockSignals(false);
}
void QtPLCDialogClass::on_lE_CapBackInterval_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(System_CapBackInterval * 4, 4);
	QString str2 = m_str_sendRegisters.mid(System_CapBackInterval_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_CapBackInterval * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(System_CapBackInterval_Reserve * 4, 4, f_hex.mid(0, 4));
	((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->blockSignals(false);
}

void QtPLCDialogClass::on_lE_TireDelay_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(System_TireDelay * 4, 4);
	QString str2 = m_str_sendRegisters.mid(System_TireDelay_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_TireDelay * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(System_TireDelay_Reserve * 4, 4, f_hex.mid(0, 4));
	((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->blockSignals(false);
}
void QtPLCDialogClass::on_lE_ReadDelay_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(System_ReadDelay * 4, 4);
	QString str2 = m_str_sendRegisters.mid(System_ReadDelay_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_ReadDelay * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(System_ReadDelay_Reserve * 4, 4, f_hex.mid(0, 4));
	((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->blockSignals(false);
}
void QtPLCDialogClass::on_lE_TireWaitTime_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(System_TireWaitTime * 4, 4);
	QString str2 = m_str_sendRegisters.mid(System_TireWaitTime_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_TireWaitTime * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(System_TireWaitTime_Reserve * 4, 4, f_hex.mid(0, 4));
	((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->blockSignals(false);
}

void QtPLCDialogClass::on_lE_paraTurnUpPosition_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;
	QString oldstr = m_str_sendRegisters.mid(System_paraTurnUpPosition * 4, 4);
	ushort a = ((Ui::QtPLCDialogClass*)ui)->lE_paraTurnUpPosition->text().toInt();
	QString str = QString("%1").arg(a, 4, 16, QLatin1Char('0'));
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_paraTurnUpPosition->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_paraTurnUpPosition->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_paraTurnUpPosition->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_paraTurnUpPosition * 4, 4, str);
	((Ui::QtPLCDialogClass*)ui)->lE_paraTurnUpPosition->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_paraTurnUpPosition->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_paraTurnUpPosition->blockSignals(false);
}
void QtPLCDialogClass::on_lE_paraTurnDnPosition_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	QString oldstr = m_str_sendRegisters.mid(System_paraTurnDnPosition * 4, 4);
	ushort a = ((Ui::QtPLCDialogClass*)ui)->lE_paraTurnDnPosition->text().toInt();
	QString str = QString("%1").arg(a, 4, 16, QLatin1Char('0'));
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_paraTurnDnPosition->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_paraTurnDnPosition->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_paraTurnDnPosition->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_paraTurnDnPosition * 4, 4, str);
	((Ui::QtPLCDialogClass*)ui)->lE_paraTurnDnPosition->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_paraTurnDnPosition->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_paraTurnDnPosition->blockSignals(false);
}
void QtPLCDialogClass::on_lE_paraPushDestPosition_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	QString oldstr = m_str_sendRegisters.mid(System_paraPushDestPosition * 4, 4);
	ushort a = ((Ui::QtPLCDialogClass*)ui)->lE_paraPushDestPosition->text().toInt();
	QString str = QString("%1").arg(a, 4, 16, QLatin1Char('0'));
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_paraPushDestPosition->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_paraPushDestPosition->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_paraPushDestPosition->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_paraPushDestPosition * 4, 4, str);
	((Ui::QtPLCDialogClass*)ui)->lE_paraPushDestPosition->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_paraPushDestPosition->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_paraPushDestPosition->blockSignals(false);
}
void QtPLCDialogClass::on_lE_RejectBoxFullNum_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	QString oldstr = m_str_sendRegisters.mid(System_RejectBoxFullNum * 4, 4);
	ushort a = ((Ui::QtPLCDialogClass*)ui)->lE_RejectBoxFullNum->text().toInt();
	QString str = QString("%1").arg(a, 4, 16, QLatin1Char('0'));
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_RejectBoxFullNum->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_RejectBoxFullNum->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_RejectBoxFullNum->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_RejectBoxFullNum * 4, 4, str);
	((Ui::QtPLCDialogClass*)ui)->lE_RejectBoxFullNum->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_RejectBoxFullNum->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_RejectBoxFullNum->blockSignals(false);
}
void QtPLCDialogClass::on_lE_ForceThresholdSlow_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_ForceThresholdSlow->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(System_ForceThresholdSlow * 4, 4);
	QString str2 = m_str_sendRegisters.mid(System_ForceThresholdSlow_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_ForceThresholdSlow->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_ForceThresholdSlow->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_ForceThresholdSlow->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_ForceThresholdSlow * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(System_ForceThresholdSlow_Reserve * 4, 4, f_hex.mid(0, 4));
	((Ui::QtPLCDialogClass*)ui)->lE_ForceThresholdSlow->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_ForceThresholdSlow->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_ForceThresholdSlow->blockSignals(false);
}
void QtPLCDialogClass::on_lE_CapThickValve_t1_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_CapThickValve_t1->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(System_CapThickValve_t1 * 4, 4);
	QString str2 = m_str_sendRegisters.mid(System_CapThickValve_t1_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_CapThickValve_t1->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_CapThickValve_t1->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_CapThickValve_t1->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_CapThickValve_t1 * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(System_CapThickValve_t1_Reserve * 4, 4, f_hex.mid(0, 4));
	((Ui::QtPLCDialogClass*)ui)->lE_CapThickValve_t1->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_CapThickValve_t1->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_CapThickValve_t1->blockSignals(false);
}
void QtPLCDialogClass::on_lE_CapThickValve_t2_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_CapThickValve_t2->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(System_CapThickValve_t2 * 4, 4);
	QString str2 = m_str_sendRegisters.mid(System_CapThickValve_t2_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_CapThickValve_t2->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_CapThickValve_t2->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_CapThickValve_t2->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_CapThickValve_t2 * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(System_CapThickValve_t2_Reserve * 4, 4, f_hex.mid(0, 4));
	((Ui::QtPLCDialogClass*)ui)->lE_CapThickValve_t2->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_CapThickValve_t2->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_CapThickValve_t2->blockSignals(false);
}
void QtPLCDialogClass::on_lE_CapTurnValve_t1_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_CapTurnValve_t1->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(System_CapTurnValve_t1 * 4, 4);
	QString str2 = m_str_sendRegisters.mid(System_CapTurnValve_t1_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_CapTurnValve_t1->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_CapTurnValve_t1->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_CapTurnValve_t1->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_CapTurnValve_t1 * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(System_CapTurnValve_t1_Reserve * 4, 4, f_hex.mid(0, 4));
	((Ui::QtPLCDialogClass*)ui)->lE_CapTurnValve_t1->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_CapTurnValve_t1->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_CapTurnValve_t1->blockSignals(false);
}
void QtPLCDialogClass::on_lE_CapTurnValve_t2_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_CapTurnValve_t2->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(System_CapTurnValve_t2 * 4, 4);
	QString str2 = m_str_sendRegisters.mid(System_CapTurnValve_t2_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_CapTurnValve_t2->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_CapTurnValve_t2->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_CapTurnValve_t2->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_CapTurnValve_t2 * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(System_CapTurnValve_t2_Reserve * 4, 4, f_hex.mid(0, 4));
	((Ui::QtPLCDialogClass*)ui)->lE_CapTurnValve_t2->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_CapTurnValve_t2->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_CapTurnValve_t2->blockSignals(false);
}

void QtPLCDialogClass::on_lE_HMU_PressStopPercent_editingFinished()
{
	m_str_sendRegisters = m_str_registers;
	m_iDontReadRegistersFlag = 1;

	float f = ((Ui::QtPLCDialogClass*)ui)->lE_HMU_PressStopPercent->text().toFloat();
	uint f_uint = *(uint*)&f;
	QString f_hex = QString("%1").arg(f_uint, 8, 16, QLatin1Char('0'));

	QString str1 = m_str_sendRegisters.mid(System_HMU_PressStopPercent * 4, 4);
	QString str2 = m_str_sendRegisters.mid(System_HMU_PressStopPercent_Reserve * 4, 4);
	QString str = str2 + str1;
	if (f_hex == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_HMU_PressStopPercent->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_HMU_PressStopPercent->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_HMU_PressStopPercent->blockSignals(false);
		return;
	}
	m_str_sendRegisters.replace(System_HMU_PressStopPercent * 4, 4, f_hex.mid(4, 4));
	m_str_sendRegisters.replace(System_HMU_PressStopPercent_Reserve * 4, 4, f_hex.mid(0, 4));
	((Ui::QtPLCDialogClass*)ui)->lE_HMU_PressStopPercent->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_HMU_PressStopPercent->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_HMU_PressStopPercent->blockSignals(false);
}
#pragma endregion

#pragma region ui cmd slots
//DateTimeStructTyp		DateTimeSet;		//设定日期时间目标
//unsigned char		cmdChangeDT;					//修改日期时间,1:执行，自动复位

void QtPLCDialogClass::on_pB_startSearch_clicked()
{
	CompareYearMonthDay();
}
void QtPLCDialogClass::on_pB_copyIn_clicked()
{
	if (((Ui::QtPLCDialogClass*)ui)->gB_update->isChecked() == false)
	{
		/*int i = showMsgBox("冲突提示", "此操作需要将组号由实时更新更改为人工输入，是否更改？", "是", "否");
		if (i == QMessageBox::No)
		{
			return;
		}*/
		((Ui::QtPLCDialogClass*)ui)->gB_update->setChecked(true);
	}
	((Ui::QtPLCDialogClass*)ui)->lE_print1->setText(m_gn1);
	((Ui::QtPLCDialogClass*)ui)->lE_print2->setText(m_gn2);
	((Ui::QtPLCDialogClass*)ui)->lE_print2->setFocus();
}

void QtPLCDialogClass::on_pB_printData_clicked()//数据
{

}
void QtPLCDialogClass::on_pB_printCurve_clicked()//曲线
{
	//((Ui::QtPLCDialogClass*)ui)->pB_printData->setEnabled(false);
	//((Ui::QtPLCDialogClass*)ui)->pB_printCurve->setEnabled(false);
	int p1 = ((Ui::QtPLCDialogClass*)ui)->lE_print1->text().toInt();
	int p2 = ((Ui::QtPLCDialogClass*)ui)->lE_print2->text().toInt();
	((Ui::QtPLCDialogClass*)ui)->lE_print1->setText(QString::number(p1));
	((Ui::QtPLCDialogClass*)ui)->lE_print2->setText(QString::number(p2));
	if (p1 > p2)
	{
		if (lg == 0)emit showWindowOut(QString::fromLocal8Bit("无满足条件\n打印数据!"));
		if (lg == 1)emit showWindowOut(QString::fromLocal8Bit("No Data!"));
		((Ui::QtPLCDialogClass*)ui)->pB_printCurve->setEnabled(true);
		return;
	}
	else if (p1 + 20 < p2)
	{
		if (lg == 0)emit showWindowOut(QString::fromLocal8Bit("选择区间不得\n大于20!")); 
		if (lg == 1)emit showWindowOut(QString::fromLocal8Bit("The Interval\nShould <=20!"));
		((Ui::QtPLCDialogClass*)ui)->pB_printCurve->setEnabled(true);
		return;
	}
	else if (p1 == p2)
	{
		QSettings configIniRead(AppPath + "\\data\\data.ini", QSettings::IniFormat);
		QString str = configIniRead.value(QString::number(p1) + "/data", 0).toString();
		if (str == "0")
		{
			if (lg == 0)emit showWindowOut(QString::fromLocal8Bit("无满足条件\n打印数据!"));
			if (lg == 1)emit showWindowOut(QString::fromLocal8Bit("No Data!"));
			((Ui::QtPLCDialogClass*)ui)->pB_printCurve->setEnabled(true);
			return;
		}

		emit TODRAWPICTURE(1,"21",p1,p2);
		return;
	}
	else
	{
		QSettings configIniRead(AppPath + "\\data\\data.ini", QSettings::IniFormat);
		QVector<QString> GroupNumber;
		for (int i = p1; i < p2 + 1; i++)
		{
			QString str = configIniRead.value(QString::number(i)+"/data" , 0).toString();
			if (str != "0")
			{
				GroupNumber << configIniRead.value(QString::number(i) + "/gn", "0").toString();
				break;
			}
		}

		if (GroupNumber.size() > 0)
		{
			emit TODRAWPICTURE(1, "21", p1, p2);
		}
		
		else
		{
			if (lg == 0)emit showWindowOut(QString::fromLocal8Bit("无打印数据!"));
			if (lg == 1)emit showWindowOut(QString::fromLocal8Bit("No Data!"));
			return;
		}
	}
}
void QtPLCDialogClass::on_Input(bool checked)
{
	QPushButton *btn = (QPushButton*)sender();

	if (checked)
	{
		btn->setEnabled(false);
		btn->setStyleSheet("background-color:rgb(0,255,0)");
		QTimer *tm = new QTimer();
		connect(tm, &QTimer::timeout, this, [=] {
			btn->setEnabled(true);
			btn->setStyleSheet("background-color:");
			btn->blockSignals(true);
			btn->setChecked(false);
			btn->blockSignals(false);
			tm->stop();
			delete tm;
		});
		if (btn->objectName().contains("pB_TMUStartDelayRelease"))
		{
			tm->start(2000);
		}
		else
		{
			tm->start(100);
		}

	}
}
void QtPLCDialogClass::on_gB_update_toggled(bool arg1)
{
	if (arg1)
	{
		if (lg == 0) ((Ui::QtPLCDialogClass*)ui)->gB_update->setTitle(QString::fromLocal8Bit("人工输入"));
		if (lg == 1) ((Ui::QtPLCDialogClass*)ui)->gB_update->setTitle(QString::fromLocal8Bit("Manual Input"));
		((Ui::QtPLCDialogClass*)ui)->lE_print1->setEnabled(true);
		((Ui::QtPLCDialogClass*)ui)->lE_print2->setEnabled(true);
	}
	else
	{
		if (lg == 0) ((Ui::QtPLCDialogClass*)ui)->gB_update->setTitle(QString::fromLocal8Bit("自动更新"));
		if (lg == 1) ((Ui::QtPLCDialogClass*)ui)->gB_update->setTitle(QString::fromLocal8Bit("Auto Update"));
		((Ui::QtPLCDialogClass*)ui)->lE_print1->setEnabled(false);
		((Ui::QtPLCDialogClass*)ui)->lE_print2->setEnabled(false);
	}
}
void QtPLCDialogClass::on_pB_cmdScaleTire_clicked()//秤清零,1:执行，自动复位
{
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(Scale_cmdTire, 1, "1");
}

//void QtPLCDialogClass::on_cB_paraScaleSetStable_currentIndexChanged(int index)//稳定状态设定目标，0:非常稳定,1:稳定,2:不稳定,3:非常不稳定
//{
//	DataFromPC_typ typ;
//	typ.Telegram_typ = 1;
//	typ.Machine_Cmd.cmdScaleSetStable = index;
//	m_socket->Communicate_PLC(&typ, nullptr);
//}
void QtPLCDialogClass::on_pB_cmdScaleCalibExt_clicked()//秤外部校正,1:执行，自动复位
{
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(Scale_cmdCalibExt, 1, "1");
}


void QtPLCDialogClass::on_pB_showPrt_toggled(bool checked)//
{
	emit SHOWPRT(checked);
}

void QtPLCDialogClass::on_pB_enHMUcheckable_toggled(bool checked)//
{
#ifdef MODBUSTCP
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(ActData_enHMU, 1, checked ? "1" : "0");
	if (checked)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_enHMUcheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_enHMUcheckable->setStyleSheet("font: bold;font-size:20pt");
	}
#endif
}
void QtPLCDialogClass::on_pB_enTMUcheckable_toggled(bool checked)//
{
#ifdef MODBUSTCP
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(ActData_enTMU, 1, checked ? "1" : "0");
	if (checked)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_enTMUcheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_enTMUcheckable->setStyleSheet("font: bold;font-size:20pt");
	}
#endif
}
void QtPLCDialogClass::on_pB_HMUStart_clicked()
{
#ifdef MODBUSTCP
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(HMU_cmdStart, 1, "1");
#endif
}
void QtPLCDialogClass::on_pB_HMUStop_clicked()
{
#ifdef MODBUSTCP
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(HMU_cmdStop, 1, "1");
#endif
}
void QtPLCDialogClass::on_pB_HMUHome_clicked()
{
#ifdef MODBUSTCP
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(HMU_cmdHome, 1, "1");
#endif
}
void QtPLCDialogClass::on_pB_HMUZero_clicked()
{
#ifdef MODBUSTCP
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(HMU_cmdZero, 1, "1");
#endif
}
void QtPLCDialogClass::on_pB_HMUCalibStd_clicked()
{
#ifdef MODBUSTCP
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(HMU_cmdCalibStd, 1, "1");
#endif
}
void QtPLCDialogClass::on_pB_HMUTurn_clicked()
{
#ifdef MODBUSTCP
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(HMU_cmdTurn, 1, "1");
#endif
}
void QtPLCDialogClass::on_pB_HMUReject_clicked()
{
#ifdef MODBUSTCP
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(HMU_cmdReject, 1, "1");
#endif
}
void QtPLCDialogClass::on_pB_cmdStartcheckable_toggled(bool checked)//启动 停止
{

	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(Machine_cmdStart, 2, checked ? "10" : "01");
	QPixmap pix;
	((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setEnabled(false);
	m_istartFlag = 1;
	QTimer *tm = new QTimer();
	connect(tm, &QTimer::timeout, this, [=] {
		((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setEnabled(true);
		m_istartFlag = 0;
		tm->stop();
		delete tm;
	});
	tm->start(3000);
	if (checked)
	{
		data_One.clear();
		if (lg == 0) pix.load(AppPath + "/ico/stop.png");
		if (lg == 1) pix.load(AppPath + "/ico/E/stop.png");
		ExitBtn->setEnabled(false);
	}
	else
	{
		if (lg == 0)pix.load(AppPath + "/ico/start.png");
		if (lg == 1)pix.load(AppPath + "/ico/E/start.png");
		ExitBtn->setEnabled(true);
	}
	((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setIcon(pix);
	((Ui::QtPLCDialogClass*)ui)->lE_BatchName->setEnabled(false);
	btnTimer->start(1);
}

void QtPLCDialogClass::on_pB_TMUStartDelayRelease_toggled(bool checked)
{
	if (!checked)
	{
		return;
	}
#ifdef MODBUSTCP
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(TMU_cmdStart, 1, "1");
#endif
}
void QtPLCDialogClass::on_pB_TMUStop_clicked()
{
#ifdef MODBUSTCP
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(TMU_cmdStop, 1, "1");
#endif
}
void QtPLCDialogClass::on_pB_TMUZero_clicked()
{
#ifdef MODBUSTCP
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(TMU_cmdZero, 1, "1");
#endif
}
void QtPLCDialogClass::on_pB_TMUCalib_clicked()
{
#ifdef MODBUSTCP
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(TMU_cmdCalib, 1, "1");
#endif
}
void QtPLCDialogClass::pB_cmdAlarmReset()
{
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(AlarmReset, 1, "1");
}
void QtPLCDialogClass::on_pB_cmdFeedSingle_clicked()//单粒下料，1:执行，自动复位
{
#ifdef MODBUSTCP
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(cmdFeedSingle, 1, "1");
#else
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdFeedSingle = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
#endif
}
void QtPLCDialogClass::on_pB_cmdFeedFive_clicked()//胶囊落料五粒
{
#ifdef MODBUSTCP
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(cmdFeedFive, 1, "1");
#else
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdFeedFive = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
#endif
}
void QtPLCDialogClass::on_pB_cmdFeedSingleStop_clicked()//单粒下料停止，1:执行，自动复位
{
#ifdef MODBUSTCP
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(cmdFeedSingleStop, 1, "1");
#else
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdFeedSingleStop = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
#endif
}
void QtPLCDialogClass::on_pB_cmdSwing_clicked()//旋转单工位,1:执行，自动复位
{
#ifdef MODBUSTCP
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(cmdSwing, 1, "1");
#else
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdSwing = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
#endif
}
void QtPLCDialogClass::on_pB_inquirecheckable_toggled(bool checked)
{
	((Ui::QtPLCDialogClass*)ui)->lW_data->setVisible(checked);
	((Ui::QtPLCDialogClass*)ui)->lb_search->setVisible(checked);
	((Ui::QtPLCDialogClass*)ui)->tableWidget->setVisible(!checked);
	if (checked)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_inquirecheckable->setStyleSheet("background: rgb(0,255,0);");
		((Ui::QtPLCDialogClass*)ui)->lW_data->clear();
		QSettings inq(AppPath + "\\data\\inquire.ini", QSettings::IniFormat);
		QString strinqu = inq.value("alldt/data", "").toString();
		if (strinqu == "")
		{
			return;
		}
		QStringList lst = strinqu.split(",");
		((Ui::QtPLCDialogClass*)ui)->lW_data->addItems(lst);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_inquirecheckable->setStyleSheet("");
	}
}
void QtPLCDialogClass::pB_cmdCounterZero()
{
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(SetCounterZero, 1, "1");
}
void QtPLCDialogClass::on_pB_cmdCapClean_clicked()
{
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(cmdCapClean, 1, "1");
}
void QtPLCDialogClass::on_pB_cmdGetCap_clicked()
{
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(cmdGetCap, 1, "1");
}
void QtPLCDialogClass::on_pB_cmdFeedAmount_clicked()
{
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(cmdFeedAmount, 1, "1");
}
//output

void QtPLCDialogClass::on_pB_cmdCapGetcheckable_toggled(bool checked)//
{
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(Output_CapGet, 1, checked ? "1" : "0");
	if (checked)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdCapGetcheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdCapGetcheckable->setStyleSheet("font: bold;font-size:20pt");
	}
}
void QtPLCDialogClass::on_pB_cmdAlarmOutcheckable_toggled(bool checked)//
{
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(Output_AlarmOut, 1, checked ? "1" : "0");
	if (checked)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAlarmOutcheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAlarmOutcheckable->setStyleSheet("font: bold;font-size:20pt");
	}
}
void QtPLCDialogClass::on_pB_cmdStopSignal_clicked()//
{
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(Output_StopSignal, 1, "1");
}
void QtPLCDialogClass::on_pB_cmdAlarmSignal_clicked()//
{
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(Output_AlarmSignal, 1, "1");
}
void QtPLCDialogClass::on_pB_cmdYellowAlarmoutcheckable_toggled(bool checked)//
{
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(Output_YellowAlarmout, 1, checked ? "1" : "0");
	if (checked)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdYellowAlarmoutcheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdYellowAlarmoutcheckable->setStyleSheet("font: bold;font-size:20pt");
	}
}
void QtPLCDialogClass::on_pB_cmdBafflecheckable_toggled(bool checked)//
{
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(Output_Baffle, 1, checked ? "1" : "0");
	if (checked)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdBafflecheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdBafflecheckable->setStyleSheet("font: bold;font-size:20pt");
	}
}
void QtPLCDialogClass::on_pB_cmdCapTurnValvecheckable_toggled(bool checked)//
{
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(Output_CapTurnValve, 1, checked ? "1" : "0");
	if (checked)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdCapTurnValvecheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdCapTurnValvecheckable->setStyleSheet("font: bold;font-size:20pt");
	}
}
void QtPLCDialogClass::on_pB_cmdCapThickValvecheckable_toggled(bool checked)//
{
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(Output_CapThickValve, 1, checked ? "1" : "0");
	if (checked)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdCapThickValvecheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdCapThickValvecheckable->setStyleSheet("font: bold;font-size:20pt");
	}
}

void QtPLCDialogClass::on_pB_cmdAxisFeedPosMov_clicked()//下料正向连续运动启动，1:执行，自动复位
{
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(axis_fun_axis0_com_pos_move, 1, "1");
}
void QtPLCDialogClass::on_pB_cmdAxisFeedStopMov_clicked()//下料停止运动，1:执行，自动复位
{
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(cmdFeedSingleStop, 1, "1");
}

void QtPLCDialogClass::on_pB_cmdAxisSwingPosMov_clicked()//旋转正向连续运动启动，1:执行，自动复位
{
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(axis_fun_axis1_com_pos_move, 1, "1");
}
void QtPLCDialogClass::on_pB_cmdAxisSwingStopMov_clicked()//旋转停止运动，1:执行，自动复位
{
	m_iDontReadCoilsFlag = 1;
	m_str_sendCoils.replace(axis_fun_axis1_com_stop_move, 1, "1");
}
void QtPLCDialogClass::on_tabWidget_currentChanged(int index)
{
	((Ui::QtPLCDialogClass*)ui)->pB_showPrt->setChecked(false);
}
void QtPLCDialogClass::on_tabWidget_PLC_currentChanged(int index)
{
	((Ui::QtPLCDialogClass*)ui)->pB_showPrt->setChecked(false);
}


/*
void QtPLCDialogClass::updateParentItem(QTreeWidgetItem* item)
{
	QTreeWidgetItem* parent = item->parent();
	if (parent == NULL)
		return;
	int nSelectedCount = 0;//选中数
	int nHalfSelectedCount = 0;//半选中数
	int childCount = parent->childCount();//孩子数
	for (int i = 0; i < childCount; i++) //判断有多少个子项被选中
	{
		QTreeWidgetItem* childItem = parent->child(i);
		if (childItem->checkState(0) == Qt::Checked)
		{
			nSelectedCount++;
		}
		else if (childItem->checkState(0) == Qt::PartiallyChecked)
		{
			nHalfSelectedCount++;
		}
	}
	if ((nSelectedCount + nHalfSelectedCount) <= 0)  //如果没有子项被选中，父项设置为未选中状态
		parent->setCheckState(0, Qt::Unchecked);
	else if ((childCount > nHalfSelectedCount && nHalfSelectedCount > 0) || (childCount > nSelectedCount && nSelectedCount > 0))// && nSelectedCount < childCount)    //如果有部分子项被选中，父项设置为部分选中状态，即用灰色显示
		parent->setCheckState(0, Qt::PartiallyChecked);
	else if (nSelectedCount == childCount)    //如果子项全部被选中，父项则设置为选中状态
		parent->setCheckState(0, Qt::Checked);
	updateParentItem(parent);//
}
void QtPLCDialogClass::onTreeItemChanged(QTreeWidgetItem* item)//利用changed自动递归。
{
	int count = item->childCount(); //返回子项的个数
	if (Qt::Checked == item->checkState(0))
	{
		item->setCheckState(0, Qt::Checked);
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				item->child(i)->setCheckState(0, Qt::Checked);
			}
		}
		else { updateParentItem(item); }
	}
	else if (Qt::Unchecked == item->checkState(0))
	{
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				item->child(i)->setCheckState(0, Qt::Unchecked);
			}
		}
		else { updateParentItem(item); }
	}
}*/
//上面是树型多选框函数
void QtPLCDialogClass::updateCheckPermission(const QString& str)
{
	checkPermissionGroup->setText(0, str);
	QTreeWidgetItemIterator it(((Ui::QtPLCDialogClass*)ui)->treeWidget_2);
	if (lg == 0)
	{
		if (checkPermissionGroup->text(0) == QString::fromLocal8Bit("管理员"))//0
		{
			while (*it) {
				if ((*it)->text(0) == QString::fromLocal8Bit("设备运行")
					|| (*it)->text(0) == QString::fromLocal8Bit("设置"))
				{
					(*it)->setCheckState(0, Qt::Checked);
				}
				++it;
			}
		}
		if (checkPermissionGroup->text(0) == QString::fromLocal8Bit("代码人员"))//3
		{
			while (*it) {
				if ((*it)->text(0) == QString::fromLocal8Bit("设备运行")
					|| (*it)->text(0) == QString::fromLocal8Bit("设置"))
				{
					(*it)->setCheckState(0, Qt::Checked);
				}
				++it;
			}
		}
		else if (checkPermissionGroup->text(0) == QString::fromLocal8Bit("工程师"))//1
		{
			while (*it) {
				if ((*it)->text(0) == QString::fromLocal8Bit("设备运行")
					|| (*it)->text(0) == QString::fromLocal8Bit("设置"))
				{
					(*it)->setCheckState(0, Qt::Checked);
				}
				if ((*it)->text(0) == QString::fromLocal8Bit("用户管理"))
				{
					(*it)->setCheckState(0, Qt::Unchecked);
				}
				++it;
			}
		}
		else if (checkPermissionGroup->text(0) == QString::fromLocal8Bit("操作员"))//2
		{
			while (*it) {
				if ((*it)->text(0) == QString::fromLocal8Bit("设备运行"))
				{
					(*it)->setCheckState(0, Qt::Checked);
				}
				if ((*it)->text(0) == QString::fromLocal8Bit("设置"))
				{
					(*it)->setCheckState(0, Qt::Unchecked);
				}
				++it;
			}
		}
	}
	else if (lg == 1)
	{
		if (checkPermissionGroup->text(0) == QString::fromLocal8Bit("Admin"))//0
		{
			while (*it) {
				if ((*it)->text(0) == QString::fromLocal8Bit("Operation")
					|| (*it)->text(0) == QString::fromLocal8Bit("Setup"))
				{
					(*it)->setCheckState(0, Qt::Checked);
				}
				++it;
			}
		}
		if (checkPermissionGroup->text(0) == QString::fromLocal8Bit("Coder"))//3
		{
			while (*it) {
				if ((*it)->text(0) == QString::fromLocal8Bit("Operation")
					|| (*it)->text(0) == QString::fromLocal8Bit("Setup"))
				{
					(*it)->setCheckState(0, Qt::Checked);
				}
				++it;
			}
		}
		else if (checkPermissionGroup->text(0) == QString::fromLocal8Bit("Engineer"))//1
		{
			while (*it) {
				if ((*it)->text(0) == QString::fromLocal8Bit("Operation")
					|| (*it)->text(0) == QString::fromLocal8Bit("Setup"))
				{
					(*it)->setCheckState(0, Qt::Checked);
				}
				if ((*it)->text(0) == QString::fromLocal8Bit("Users"))
				{
					(*it)->setCheckState(0, Qt::Unchecked);
				}
				++it;
			}
		}
		else if (checkPermissionGroup->text(0) == QString::fromLocal8Bit("Operator"))//2
		{
			while (*it) {
				if ((*it)->text(0) == QString::fromLocal8Bit("Operation"))
				{
					(*it)->setCheckState(0, Qt::Checked);
				}
				if ((*it)->text(0) == QString::fromLocal8Bit("Setup"))
				{
					(*it)->setCheckState(0, Qt::Unchecked);
				}
				++it;
			}
		}
	}
}


void QtPLCDialogClass::selectedName(int r, int c)
{
	if (c == 0)
	{
		m_SelectedName = ((QTableWidget*)sender())->item(r, c)->text();
	}
	else
	{
		m_SelectedName = "";
	}
}

void QtPLCDialogClass::btn_Enabled(int i)
{
	if (i == 0)
	{
		((Ui::QtPLCDialogClass*)ui)->widget_UsersChoice_2->setVisible(1);
	}
	else {
		((Ui::QtPLCDialogClass*)ui)->widget_UsersChoice_2->setVisible(0);
	}
}
void QtPLCDialogClass::on_pB_Users_Delete_clicked()
{
	if (m_SelectedName == "")
	{
		if (lg == 0)emit showWindowOut(QString::fromLocal8Bit("请先选择用户\n然后进行删除！"));
		if (lg == 1)emit showWindowOut(QString::fromLocal8Bit("Please select user first\nthen delete it！"));
		return;
	}
	else if (m_SelectedName == "Admin")
	{
		if (lg == 0)emit showWindowOut(QString::fromLocal8Bit("管理员账户\n不可删除！"));
		if (lg == 1)emit showWindowOut(QString::fromLocal8Bit("Admin account\n can't be deleted!"));
		return;
	}
	else
	{
		if (lg == 0)
		{
			if (QMessageBox::Yes == showMsgBox("删除确认", "确认删除该用户？", "确认", "取消"))
			{
				QSettings Dir(AppPath + "/ModelFile/ProgramSet.ini", QSettings::IniFormat);//所有结果文件
				QString path = AppPath + "/ModelFile/ProgramSet.ini";
				QString fullName = "USER_" + m_SelectedName;
				Dir.remove(fullName);
				//emit showWindowOut(QString::fromLocal8Bit("恭喜\n") + m_SelectedName + QString::fromLocal8Bit("\n删除成功!"));
				initTableWidget();
				((Ui::QtPLCDialogClass*)ui)->tabWidget_Users->removeTab(1);
				m_SelectedName = "";
			}
		}
		else if (lg == 1)
		{
			if (QMessageBox::Yes == showMsgBox("delete confirm", "Delete the user?", "Yes", "Cancel"))
			{
				QSettings Dir(AppPath + "/ModelFile/ProgramSet.ini", QSettings::IniFormat);//所有结果文件
				QString path = AppPath + "/ModelFile/ProgramSet.ini";
				QString fullName = "USER_" + m_SelectedName;
				Dir.remove(fullName);
				//emit showWindowOut(QString::fromLocal8Bit("恭喜\n") + m_SelectedName + QString::fromLocal8Bit("\n删除成功!"));
				initTableWidget();
				((Ui::QtPLCDialogClass*)ui)->tabWidget_Users->removeTab(1);
				m_SelectedName = "";
			}
		}
	}
}
void QtPLCDialogClass::addUser()
{
	QSettings Dir(AppPath + "/ModelFile/ProgramSet.ini", QSettings::IniFormat);//所有结果文件
	QStringList str = Dir.childGroups();
	int count = str.size();
	for (int i = 0; i < count; i++)
	{
		QString One = str.at(i);//节点
		if (One.mid(0, 4) == "USER")
		{
			QString j0 = One.mid(5);
			QString ad = "Admin";
			if (!((Ui::QtPLCDialogClass*)ui)->lE_SetUserName->text().compare(j0, Qt::CaseInsensitive))//不区分大小写比较
			{
				if (!((Ui::QtPLCDialogClass*)ui)->lE_SetUserName->text().compare(ad, Qt::CaseInsensitive))
				{
					if (lg == 0)showMsgBox("非法修改", "管理员账号不可修改！", "我知道了", "");
					if (lg == 1)showMsgBox("illegal change", "Admin account can't be changed!", "I see", "");
					return;
				}
				if (lg == 0)
				{
					if (QMessageBox::Yes == showMsgBox("冲突确认", "用户名已存在(大小写不敏感)，是否更新？", "确认", "取消"))
					{
						Dir.setValue("USER_" + ((Ui::QtPLCDialogClass*)ui)->lE_SetUserName->text() + "/Password", ((Ui::QtPLCDialogClass*)ui)->lE_SetUserSecretNum->text());//写当前模板
						Dir.setValue("USER_" + ((Ui::QtPLCDialogClass*)ui)->lE_SetUserName->text() + "/Level", QString::number(((Ui::QtPLCDialogClass*)ui)->cB_SetUserPermission->currentIndex()));//写当前模板
						emit showWindowOut(QString::fromLocal8Bit("恭喜\n用户更新成功!"));
						initTableWidget();
						((Ui::QtPLCDialogClass*)ui)->tabWidget_Users->removeTab(1);
						return;
					}
					else
					{
						return;
					}
				}
				else if (lg == 1)
				{
					if (QMessageBox::Yes == showMsgBox("Conflict", "User is already exist,update the password?", "Yes", "Cancel"))
					{
						Dir.setValue("USER_" + ((Ui::QtPLCDialogClass*)ui)->lE_SetUserName->text() + "/Password", ((Ui::QtPLCDialogClass*)ui)->lE_SetUserSecretNum->text());//写当前模板
						Dir.setValue("USER_" + ((Ui::QtPLCDialogClass*)ui)->lE_SetUserName->text() + "/Level", QString::number(((Ui::QtPLCDialogClass*)ui)->cB_SetUserPermission->currentIndex()));//写当前模板
						emit showWindowOut(QString::fromLocal8Bit("Congratulations\n password is update!"));
						initTableWidget();
						((Ui::QtPLCDialogClass*)ui)->tabWidget_Users->removeTab(1);
						return;
					}
					else
					{
						return;
					}
				}
			}
		}
	}
	Dir.setValue("USER_" + ((Ui::QtPLCDialogClass*)ui)->lE_SetUserName->text() + "/Password", ((Ui::QtPLCDialogClass*)ui)->lE_SetUserSecretNum->text());//写当前模板
	Dir.setValue("USER_" + ((Ui::QtPLCDialogClass*)ui)->lE_SetUserName->text() + "/Level", QString::number(((Ui::QtPLCDialogClass*)ui)->cB_SetUserPermission->currentIndex()));//写当前模板
	if (lg == 0)emit showWindowOut(QString::fromLocal8Bit("恭喜\n新建用户成功!"));
	if (lg == 1)emit showWindowOut(QString::fromLocal8Bit("Congratulations\ncreat new user account success!"));
	initTableWidget();
	((Ui::QtPLCDialogClass*)ui)->tabWidget_Users->removeTab(1);
}
void QtPLCDialogClass::on_lE_SetUserSecretNum_returnPressed()
{
	if (((Ui::QtPLCDialogClass*)ui)->pB_AddUser->isEnabled())
	{
		addUser();
	}
}
void QtPLCDialogClass::on_lE_SetUserName_returnPressed()
{
	((Ui::QtPLCDialogClass*)ui)->lE_SetUserSecretNum->setFocus();
}
//新建用户
void QtPLCDialogClass::on_lE_SetUserName_textChanged(const QString &arg1)
{
	if (arg1 != "")
	{
		((Ui::QtPLCDialogClass*)ui)->cB_SetUserPermission->setEnabled(true);
		((Ui::QtPLCDialogClass*)ui)->lE_SetUserSecretNum->setEnabled(true);
		if (((Ui::QtPLCDialogClass*)ui)->lE_SetUserSecretNum->text().length() >= 4)
		{
			((Ui::QtPLCDialogClass*)ui)->pB_AddUser->setEnabled(true);
		}
	}
	else {
		((Ui::QtPLCDialogClass*)ui)->cB_SetUserPermission->setEnabled(false);
		((Ui::QtPLCDialogClass*)ui)->lE_SetUserSecretNum->setEnabled(false);
		((Ui::QtPLCDialogClass*)ui)->pB_AddUser->setEnabled(false);
	}
}
void QtPLCDialogClass::on_lE_SetUserSecretNum_textChanged(const QString &arg1)
{
	if (arg1.length() >= 4)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_AddUser->setEnabled(true);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pB_AddUser->setEnabled(false);
	}
}

void QtPLCDialogClass::updateParentItem(QTreeWidgetItem* item)
{
	QTreeWidgetItem* parent = item->parent();
	if (parent == NULL)
		return;
	int nSelectedCount = 0;//选中数
	int nHalfSelectedCount = 0;//半选中数
	int childCount = parent->childCount();//孩子数
	for (int i = 0; i < childCount; i++) //判断有多少个子项被选中
	{
		QTreeWidgetItem* childItem = parent->child(i);
		if (childItem->checkState(0) == Qt::Checked)
		{
			nSelectedCount++;
		}
		else if (childItem->checkState(0) == Qt::PartiallyChecked)
		{
			nHalfSelectedCount++;
		}
	}
	if ((nSelectedCount + nHalfSelectedCount) <= 0)  //如果没有子项被选中，父项设置为未选中状态
		parent->setCheckState(0, Qt::Unchecked);
	else if ((childCount > nHalfSelectedCount && nHalfSelectedCount > 0) || (childCount > nSelectedCount && nSelectedCount > 0))// && nSelectedCount < childCount)    //如果有部分子项被选中，父项设置为部分选中状态，即用灰色显示
		parent->setCheckState(0, Qt::PartiallyChecked);
	else if (nSelectedCount == childCount)    //如果子项全部被选中，父项则设置为选中状态
		parent->setCheckState(0, Qt::Checked);
	updateParentItem(parent);//
}
void QtPLCDialogClass::onTreeItemChanged(QTreeWidgetItem* item)//利用changed自动递归。
{
	int count = item->childCount(); //返回子项的个数
	if (Qt::Checked == item->checkState(0))
	{
		item->setCheckState(0, Qt::Checked);
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				item->child(i)->setCheckState(0, Qt::Checked);
			}
		}
		else { updateParentItem(item); }
	}
	else if (Qt::Unchecked == item->checkState(0))
	{
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				item->child(i)->setCheckState(0, Qt::Unchecked);
			}
		}
		else { updateParentItem(item); }
	}
}
#pragma endregion

void QtPLCDialogClass::OnUnconnectedState()
{
	((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setChecked(false);
	((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setEnabled(false);
	((Ui::QtPLCDialogClass*)ui)->lb_Alarm->setStyleSheet("color: rgb(255, 0,0);font-size:20pt");
	if (lg == 0)
	{
		((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("设备未就绪~");
		showMsgBox("提示", "PLC未连接!", "我知道了", "");
	}
	if (lg == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("Not Ready~");
		showMsgBox("Warning", "PLC Unconnected!", "I Know", "");
	}
}
void QtPLCDialogClass::OnShowState(QString str)
{
	emit showWindowOut(str);
	//QMessageBox::about(nullptr, str,str);
}
void QtPLCDialogClass::OnShowValueCountFlag(int index)
{
	if (m_index == index)
	{
		return;
	}
	m_index = index;
	QString str=QString::number(index);
	QMessageBox::about(nullptr, str, QString::fromLocal8Bit("个数: ")+str);
}
void QtPLCDialogClass::on_lW_data_itemClicked(QListWidgetItem *item)
{
	if (((Ui::QtPLCDialogClass*)ui)->lW_data->item(0)->text() != QString::fromLocal8Bit("符合组号") && ((Ui::QtPLCDialogClass*)ui)->lW_data->item(0)->text() != QString::fromLocal8Bit("Matched"))
	{
		return;
	}
	QString str = item->text();
	if (str != QString::fromLocal8Bit("符合组号") && str != QString::fromLocal8Bit("Matched"))
	{
		((Ui::QtPLCDialogClass*)ui)->gB_update->setChecked(true);
		if (leflag == 0)
		{
			leflag = 1;
			((Ui::QtPLCDialogClass*)ui)->lE_print1->setText(str);
		}
		else
		{
			leflag = 0;
			((Ui::QtPLCDialogClass*)ui)->lE_print2->setText(str);
		}
	}
}
void QtPLCDialogClass::OnClosingState()
{
	showMsgBox("提示", "PLC Closing!", "我知道了", "");
}

void QtPLCDialogClass::dtClose()
{
	((Ui::QtPLCDialogClass*)ui)->pB_dtDlgcheckable->setChecked(false);
}
void QtPLCDialogClass::startMovie()
{
	animation1->start();
	animation2->start();
	btnTimer->stop();
}
void QtPLCDialogClass::pB_ChangeLanguage()
{
	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	int langu = configIniRead.value("Language/currentLanguage", "").toInt();
	if (langu == 0)
	{
		configIniRead.setValue("Language/currentLanguage", 1);
		showMsgBox("Information", "Change to English,\nRestart software then work!", "I see", "");
	}
	else
	{
		configIniRead.setValue("Language/currentLanguage", 0);
		showMsgBox("提示信息", "改为中文,\n重启软件后生效!", "我知道了", "");
	}
	return;
}
void QtPLCDialogClass::ChangeLanguage()
{
	((Ui::QtPLCDialogClass*)ui)->pB_Recipe_enable->setText("Save");

	((Ui::QtPLCDialogClass*)ui)->gB_update->setTitle(QString::fromLocal8Bit("Auto Update"));

	((Ui::QtPLCDialogClass*)ui)->pB_inquirecheckable->setText("Inquire");
	((Ui::QtPLCDialogClass*)ui)->label_51->setText("to");
	((Ui::QtPLCDialogClass*)ui)->label_24->setText("to");

	((Ui::QtPLCDialogClass*)ui)->groupBox_11->setTitle("Print");
	((Ui::QtPLCDialogClass*)ui)->label_36->setText("Search:");
	((Ui::QtPLCDialogClass*)ui)->label_61->setText("Result:");
	((Ui::QtPLCDialogClass*)ui)->label_35->setText("GroupNum:");
	((Ui::QtPLCDialogClass*)ui)->pB_copyIn->setText("Copy in"+QString::fromLocal8Bit("↓"));
	((Ui::QtPLCDialogClass*)ui)->pB_startSearch->setText("Search");
	((Ui::QtPLCDialogClass*)ui)->pB_printCurve->setText("Print Data&&Curve");
	//((Ui::QtPLCDialogClass*)ui)->label_37->setText("to");

		((Ui::QtPLCDialogClass*)ui)->label_9->setText("GroupNum");
		((Ui::QtPLCDialogClass*)ui)->label->setText("Times");
		((Ui::QtPLCDialogClass*)ui)->label_3->setText("Total(g)");
		((Ui::QtPLCDialogClass*)ui)->label_7->setText("Average(g)");
		((Ui::QtPLCDialogClass*)ui)->label_6->setText("Max(g)");
		((Ui::QtPLCDialogClass*)ui)->label_34->setText("MaxRatio(%)");
		((Ui::QtPLCDialogClass*)ui)->label_8->setText("Min(g)");
		((Ui::QtPLCDialogClass*)ui)->label_29->setText("MinRatio(%)");
	
		//输入输出
		((Ui::QtPLCDialogClass*)ui)->label_40->setText("Drop detection");
		((Ui::QtPLCDialogClass*)ui)->label_46->setText("Zero position of\nhardness test");
		//((Ui::QtPLCDialogClass*)ui)->pB_cmdReject->setText("Reject");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdCapGetcheckable->setText("CapGet");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdCapTurnValvecheckable->setText("Shaping cylinder");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdCapThickValvecheckable->setText("Thickness cylinder");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAlarmOutcheckable->setText("AlarmOut");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdStopSignal->setText("StopSignal");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAlarmSignal->setText("AlarmSignal");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdYellowAlarmoutcheckable->setText("YellowAlarmout");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdBafflecheckable->setText("Baffle");
		//((Ui::QtPLCDialogClass*)ui)->label_2->setText("Analog Output");

		//下料旋转
		((Ui::QtPLCDialogClass*)ui)->label_62->setText("Feed count");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedJogPos->setText("JogPos");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedJogNeg->setText("JogNeg");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedRelMov->setText("RelMov");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedPosMov->setText("PosMov");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisFeedStopMov->setText("StopMov");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedSingle->setText("FeedSingle");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedSingleStop->setText("FeedSingleStop");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingJogPos->setText("JogPos");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingJogNeg->setText("JogNeg");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingRelMov->setText("RelMov");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingPosMov->setText("PosMov");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdAxisSwingStopMov->setText("StopMov");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdSwing->setText("Swing");

		//称重打印
		//((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedShake->setText("FeedShake");
		//((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedshakestop->setText("Feedshakestop");
		//((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedshakelevel->setText("Feedshakelevel");
		//((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedhome->setText("Feedhome");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedAmount->setText("FeedAmount");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedFive->setText("FeedFive");
		//((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedShakefive->setText("FeedShakefive");
		//((Ui::QtPLCDialogClass*)ui)->pB_cmdScaleRead->setText("ScaleRead");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdScaleTire->setText("ScaleTire");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdScaleCalibExt->setText("ScaleCalibExt");
		//((Ui::QtPLCDialogClass*)ui)->pB_cmdScaleSetStable->setText("ScaleSetStable");
		//((Ui::QtPLCDialogClass*)ui)->pB_showPrt->setText("showPrt");
		//((Ui::QtPLCDialogClass*)ui)->pB_cmdAlogtest->setText("Alogtest");
		((Ui::QtPLCDialogClass*)ui)->groupBox_12->setTitle("Hardness Testing Unit");
		((Ui::QtPLCDialogClass*)ui)->pB_enHMUcheckable->setText("Enable");
		((Ui::QtPLCDialogClass*)ui)->pB_HMUStart->setText("Start");
		((Ui::QtPLCDialogClass*)ui)->pB_HMUStop->setText("Stop");
		((Ui::QtPLCDialogClass*)ui)->pB_HMUZero->setText("Zero");
		((Ui::QtPLCDialogClass*)ui)->pB_HMUCalibStd->setText("CalibStd");

		((Ui::QtPLCDialogClass*)ui)->pB_HMUHome->setText("Home");
		((Ui::QtPLCDialogClass*)ui)->pB_HMUTurn->setText("Turn");
		((Ui::QtPLCDialogClass*)ui)->pB_HMUReject->setText("Reject");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdRollingOverNeg->setText("RollingOverNeg");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdRollingOverPos->setText("RollingOverPos");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdPushNeg->setText("PushNeg");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdPushPos->setText("PushPos");
		

		((Ui::QtPLCDialogClass*)ui)->label_2->setText("HardnessChkCnt");
		((Ui::QtPLCDialogClass*)ui)->label_19->setText("ResultForce");
		((Ui::QtPLCDialogClass*)ui)->label_11->setText("ResultDiam");
		((Ui::QtPLCDialogClass*)ui)->label_84->setText("ActForce");
		

		((Ui::QtPLCDialogClass*)ui)->groupBox_13->setTitle("Thickness Testing Unit");
		((Ui::QtPLCDialogClass*)ui)->pB_enTMUcheckable->setText("Enable");
		((Ui::QtPLCDialogClass*)ui)->pB_TMUStartDelayRelease->setText("Start");
		((Ui::QtPLCDialogClass*)ui)->pB_TMUStop->setText("Stop");
		((Ui::QtPLCDialogClass*)ui)->pB_TMUZero->setText("Zero"); 
		((Ui::QtPLCDialogClass*)ui)->pB_TMUCalib->setText("CalibStd"); 

		((Ui::QtPLCDialogClass*)ui)->label_74->setText("ThicknessResult");
		((Ui::QtPLCDialogClass*)ui)->label_103->setText("ThickRejectCount");


		((Ui::QtPLCDialogClass*)ui)->groupBox_8->setTitle("GetCap && CapClean");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdGetCap->setText("GetCap");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdCapClean->setText("CapClean");
		((Ui::QtPLCDialogClass*)ui)->label_63->setText("FeedDone");
		((Ui::QtPLCDialogClass*)ui)->groupBox_5->setTitle("ThickRejectCount");
		//系统参数
		((Ui::QtPLCDialogClass*)ui)->label_71->setText("Thickness cylinder");
		((Ui::QtPLCDialogClass*)ui)->label_70->setText("Zero position of\nFlap");
		((Ui::QtPLCDialogClass*)ui)->label_30->setText("Shaping cylinder");
		((Ui::QtPLCDialogClass*)ui)->label_64->setText("Swing arm");
		((Ui::QtPLCDialogClass*)ui)->pB_Read1->setText("Read");
		((Ui::QtPLCDialogClass*)ui)->pB_Write1->setText("Write");

		//运行参数
		((Ui::QtPLCDialogClass*)ui)->label_14->setText("Expected(g)");
		((Ui::QtPLCDialogClass*)ui)->label_13->setText("Over Limit(g)");
		((Ui::QtPLCDialogClass*)ui)->label_12->setText("Under Limit(g)");
		((Ui::QtPLCDialogClass*)ui)->label_53->setText("Over Weight(g)");
		((Ui::QtPLCDialogClass*)ui)->label_54->setText("Under Light(g)");
		((Ui::QtPLCDialogClass*)ui)->label_57->setText("Speed");
		
		((Ui::QtPLCDialogClass*)ui)->label_76->setText("SetPillDiam");
		((Ui::QtPLCDialogClass*)ui)->label_82->setText("HardnessChkNum");
		((Ui::QtPLCDialogClass*)ui)->label_86->setText("HMU_Zero");
		((Ui::QtPLCDialogClass*)ui)->label_99->setText("TMU_Zero");
		((Ui::QtPLCDialogClass*)ui)->label_107->setText("HMUparaCalibForce");
		((Ui::QtPLCDialogClass*)ui)->label_72->setText("RecipeNo"); 
		((Ui::QtPLCDialogClass*)ui)->label_52->setText("GroupSet");
		((Ui::QtPLCDialogClass*)ui)->label_58->setText("TestInterval");
		((Ui::QtPLCDialogClass*)ui)->label_56->setText("ThickUpperLimit");
		((Ui::QtPLCDialogClass*)ui)->label_73->setText("ThickUnderLimit");
		((Ui::QtPLCDialogClass*)ui)->label_77->setText("PillDiamOffset");
		((Ui::QtPLCDialogClass*)ui)->label_75->setText("GroupCounter");
		((Ui::QtPLCDialogClass*)ui)->label_100->setText("HMU_K");
		((Ui::QtPLCDialogClass*)ui)->label_101->setText("TMU_K");
		((Ui::QtPLCDialogClass*)ui)->label_106->setText("TMUcalibThickness");
		//((Ui::QtPLCDialogClass*)ui)->label_58->setText("Test Sub.");
		/*((Ui::QtPLCDialogClass*)ui)->pB_Read2->setText("Read");
		((Ui::QtPLCDialogClass*)ui)->pB_Write2->setText("Write");*/

		((Ui::QtPLCDialogClass*)ui)->label_26->setText("FeedOffset(p)");
		((Ui::QtPLCDialogClass*)ui)->label_31->setText("RotateOffset(p)");
		((Ui::QtPLCDialogClass*)ui)->label_27->setText("TurnOffset(p)");
		((Ui::QtPLCDialogClass*)ui)->label_33->setText("PushOffset(p)");
		((Ui::QtPLCDialogClass*)ui)->label_25->setText("CapPickInterval(s)");
		((Ui::QtPLCDialogClass*)ui)->label_4->setText("FeedTimeOut(s)");
		((Ui::QtPLCDialogClass*)ui)->label_32->setText("TireDelay(s)");
		((Ui::QtPLCDialogClass*)ui)->label_5->setText("CapBackInterval");
		((Ui::QtPLCDialogClass*)ui)->label_42->setText("TireWaitTime(s)");
		((Ui::QtPLCDialogClass*)ui)->label_41->setText("ReadDelay(s)");
		((Ui::QtPLCDialogClass*)ui)->label_97->setText("HMU_PressStopPercent");
		((Ui::QtPLCDialogClass*)ui)->label_44->setText("StopSignalDelay");


		((Ui::QtPLCDialogClass*)ui)->label_87->setText("paraTurnUpSpd");
		((Ui::QtPLCDialogClass*)ui)->label_88->setText("paraTurnDnSpd");
		((Ui::QtPLCDialogClass*)ui)->label_89->setText("paraTurnUpPosition");
		((Ui::QtPLCDialogClass*)ui)->label_90->setText("paraTurnDnPosition");
		((Ui::QtPLCDialogClass*)ui)->label_91->setText("paraPushDestPosition");
		((Ui::QtPLCDialogClass*)ui)->label_92->setText("ForceThresholdSlow");
		((Ui::QtPLCDialogClass*)ui)->label_93->setText("CapThickValve_t1");
		((Ui::QtPLCDialogClass*)ui)->label_96->setText("CapThickValve_t2");
		((Ui::QtPLCDialogClass*)ui)->label_94->setText("CapTurnValve_t1");
		((Ui::QtPLCDialogClass*)ui)->label_95->setText("CapTurnValve_t2");
		((Ui::QtPLCDialogClass*)ui)->label_98->setText("RejectBoxFullNum");

		//运行状态
		((Ui::QtPLCDialogClass*)ui)->label_22->setText("MovDistance(p)");
		((Ui::QtPLCDialogClass*)ui)->label_28->setText("MovDistance(p)");

		//用户管理
		((Ui::QtPLCDialogClass*)ui)->label_68->setText("Permission name");
		((Ui::QtPLCDialogClass*)ui)->label_69->setText("Permission description");
		((Ui::QtPLCDialogClass*)ui)->label_65->setText("Add user name");
		((Ui::QtPLCDialogClass*)ui)->label_66->setText("Set user permission");
		((Ui::QtPLCDialogClass*)ui)->label_67->setText("Set password");
		((Ui::QtPLCDialogClass*)ui)->pB_AddUser->setText("Add user");
		((Ui::QtPLCDialogClass*)ui)->pB_Users_Delete->setText("Delete user");

		//杂项
		((Ui::QtPLCDialogClass*)ui)->gB_User->setTitle("Custom user");
		((Ui::QtPLCDialogClass*)ui)->groupBox_2->setTitle("Feed");
		((Ui::QtPLCDialogClass*)ui)->groupBox_3->setTitle("Rotate");
		//((Ui::QtPLCDialogClass*)ui)->groupBox_9->setTitle("Cutting");
		//((Ui::QtPLCDialogClass*)ui)->groupBox_5->setTitle("Weighing settings");



}

void QtPLCDialogClass::on_pB_SetUpcheckable_toggled(bool checked)//设置
{
	if (checked)
	{
		((Ui::QtPLCDialogClass*)ui)->frame->setVisible(false);
		QPixmap pix;
		if (lg == 0) pix.load(AppPath + "/ico/sz.png");
		if (lg == 1) pix.load(AppPath + "/ico/E/sz.png");
		((Ui::QtPLCDialogClass*)ui)->pB_SetUpcheckable->setIcon(pix);
		((Ui::QtPLCDialogClass*)ui)->pB_SetUpcheckable->setIconSize(QSize(347, 99));
		((Ui::QtPLCDialogClass*)ui)->pB_dtDlgcheckable->setChecked(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->frame->setVisible(true);
		QPixmap pix;
		if (lg == 0) pix.load(AppPath + "/ico/sznt.png");
		if (lg == 1) pix.load(AppPath + "/ico/E/sznt.png");
		((Ui::QtPLCDialogClass*)ui)->pB_SetUpcheckable->setIcon(pix);
		((Ui::QtPLCDialogClass*)ui)->pB_SetUpcheckable->setIconSize(QSize(347, 99));
		if (((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText == QString::fromLocal8Bit("设备运行正常~"))
		{
			//((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->setEnabled(true);
		}
	}
}
void QtPLCDialogClass::on_pB_dtDlgcheckable_toggled(bool checked)//数据dialog
{
	if (checked)
	{
		//dtCurve->show();
		QPixmap pix;
		if (lg == 0)pix.load(AppPath + "/ico/data1.png");
		if (lg == 1)pix.load(AppPath + "/ico/E/data1.png");
		((Ui::QtPLCDialogClass*)ui)->pB_dtDlgcheckable->setIcon(pix);
		((Ui::QtPLCDialogClass*)ui)->widget_cv->setVisible(true);
	}
	else
	{
		//dtCurve->hide();
		QPixmap pix;
		if (lg == 0) pix.load(AppPath + "/ico/data2.png");
		if (lg == 1) pix.load(AppPath + "/ico/E/data2.png");
		((Ui::QtPLCDialogClass*)ui)->pB_dtDlgcheckable->setIcon(pix);
		((Ui::QtPLCDialogClass*)ui)->widget_cv->setVisible(false);
	}
}
