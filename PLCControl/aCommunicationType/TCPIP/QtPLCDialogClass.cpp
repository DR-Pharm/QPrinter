#include "QtPLCDialogClass.h"
#include "ui_QtPLCDialogClass.h"
#include <QPropertyAnimation>
#include <QFont>
#include <QBitmap>
#include <QPainter>
#include "mypushbutton.h"
#include "Keyboard.h"
#include <QDesktopWidget>
#include <dbt.h>

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

	((Ui::QtPLCDialogClass*)ui)->setupUi(this);

	QFile fl(AppPath + "/ico/PLC.qss");
	if (fl.open(QFile::ReadOnly))
	{
		QString ss = fl.readAll();
		setStyleSheet(ss);
		fl.close();
	}

	((Ui::QtPLCDialogClass*)ui)->frame->move(0, 0);

	m_data = new DataToPC_typ;
	memset(m_data, 0, sizeof(DataToPC_typ));//主界面用
	//int jdd = sizeof(m_data->ActData.BatchName);//40
	memset(m_data->ActData.BatchName, '\0', sizeof(m_data->ActData.BatchName));

	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	lg = configIniRead.value("Language/currentLanguage", "").toInt();

	initFont();
	initDlg();
	initUI();
	initMovie();
	inittabicon();
	initUser();
	if (lg == 1) ChangeLanguage();
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
	((Ui::QtPLCDialogClass*)ui)->pB_SetUpcheckable->setStyleSheet("\
		QPushButton\
		{\
		border:0px;\
		}\
		QPushButton::checked\
		{\
		Padding-left:0px;\
		Padding-top:0px;\
		}");
	QPixmap pix;
	bool ret;
	if (lg == 0) ret = pix.load(AppPath + "/ico/sznt.png");
	if (lg == 1) ret = pix.load(AppPath + "/ico/E/sznt.png");
	((Ui::QtPLCDialogClass*)ui)->pB_SetUpcheckable->setIcon(pix);
	((Ui::QtPLCDialogClass*)ui)->pB_SetUpcheckable->setIconSize(QSize(347, 99));
	int firstbtnY = 20; 
	int firstbtnX = 15;
	((Ui::QtPLCDialogClass*)ui)->pB_SetUpcheckable->move(firstbtnX, firstbtnY);
	int offsetBTN = 105;
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
	AlarmResetBtn->move(firstbtnX, firstbtnY +offsetBTN);
	connect(AlarmResetBtn, &MyPushButton::clicked, [=]() {
		on_pB_cmdAlarmReset_clicked(); });

	if (lg == 0) AlarmResetBtn = new MyPushButton(AppPath + "/ico/jsqlnt.png", AppPath + "/ico/jsql.png", 347, 99);
	if (lg == 1) AlarmResetBtn = new MyPushButton(AppPath + "/ico/E/jsqlnt.png", AppPath + "/ico/E/jsql.png", 347, 99);
	AlarmResetBtn->setParent(((Ui::QtPLCDialogClass*)ui)->frame_20);
	AlarmResetBtn->move(firstbtnX, firstbtnY + 2 * offsetBTN);
	connect(AlarmResetBtn, &MyPushButton::clicked, [=]() {
		on_pB_cmdCounterZero_clicked(); });

	if (lg == 0) LanguageBtn = new MyPushButton(AppPath + "/ico/languageCNnt.png", AppPath + "/ico/languageCN.png", 347, 99);
	if (lg == 1) LanguageBtn = new MyPushButton(AppPath + "/ico/E/languageCNnt.png", AppPath + "/ico/E/languageCN.png", 347, 99);
	LanguageBtn->setParent(((Ui::QtPLCDialogClass*)ui)->frame_20);
	LanguageBtn->move(firstbtnX, firstbtnY + 3 * offsetBTN);
	connect(LanguageBtn, &MyPushButton::clicked, [=]() {
		on_pB_ChangeLanguage(); });

	if (lg == 0) ExitBtn = new MyPushButton(AppPath + "/ico/exitnt.png", AppPath + "/ico/exit.png", 347, 99);
	if (lg == 1) ExitBtn = new MyPushButton(AppPath + "/ico/E/exitnt.png", AppPath + "/ico/E/exit.png", 347, 99);
	ExitBtn->setParent(((Ui::QtPLCDialogClass*)ui)->frame_20);
	ExitBtn->move(firstbtnX, firstbtnY + 4 * offsetBTN);
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
	//开始

	((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setFixedSize(380, 230);
	((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setStyleSheet("\
		QPushButton\
		{\
		border:0px;\
		}\
		QPushButton::checked\
		{\
		Padding-left:0px;\
		Padding-top:0px;\
		}");
	if (lg == 0) ret = pix.load(AppPath + "/ico/start.png");
	if (lg == 1) ret = pix.load(AppPath + "/ico/E/start.png");
	((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setIcon(pix);
	((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setIconSize(QSize(380, 230));
	((Ui::QtPLCDialogClass*)ui)->lb_Alarm->setStyleSheet("color: rgb(255, 0,0);font-size:20pt");
	if (lg == 0) ((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("设备未就绪~");
	if (lg == 1) ((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("Not Ready~");
	//指示灯部分
	((Ui::QtPLCDialogClass*)ui)->lb_00->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));
	((Ui::QtPLCDialogClass*)ui)->lb_10->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));
	((Ui::QtPLCDialogClass*)ui)->lb_20->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));

	btnTimer = new QTimer();
	connect(btnTimer, SIGNAL(timeout()), this, SLOT(startMovie()));

	((Ui::QtPLCDialogClass*)ui)->widget_cv->move(0, 0);
	((Ui::QtPLCDialogClass*)ui)->widget_cv->setVisible(false);
	initChartOne();
	QStringList str1;
	if (lg == 0) str1 << QString::fromLocal8Bit("重量");
	if (lg == 1) str1 << QString::fromLocal8Bit("Weight");
	((Ui::QtPLCDialogClass*)ui)->tableWidget->setColumnCount(1);
	((Ui::QtPLCDialogClass*)ui)->tableWidget->setHorizontalHeaderLabels(str1);//加水平表头 每行加日期结果
	((Ui::QtPLCDialogClass*)ui)->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//均分填充表头

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

	((Ui::QtPLCDialogClass*)ui)->lW_data->setVisible(false);

	QSettings WriteIni(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	m_iFeedMode = WriteIni.value("ProgramSetting/FeedMode", 23).toInt();

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

	lbDr = new QLabel(((Ui::QtPLCDialogClass*)ui)->frame_PLC);
	lbDr->resize(1280, 800);
	lbDr->move(0, 0);
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
	if (lg == 0)group24->setText(0, QString::fromLocal8Bit("运行状态"));
	if (lg == 1)group24->setText(0, QString::fromLocal8Bit("Status"));
	group24->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group24->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group25 = new QTreeWidgetItem(group2);
	if (lg == 0)group25->setText(0, QString::fromLocal8Bit("用户管理"));
	if (lg == 1)group25->setText(0, QString::fromLocal8Bit("Users"));
	group25->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group25->setCheckState(0, Qt::Checked);
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
	if (lg == 0)group213->setText(0, QString::fromLocal8Bit("其它"));
	if (lg == 1)group213->setText(0, QString::fromLocal8Bit("Others"));
	group213->setCheckState(0, Qt::Checked);
	//QTreeWidgetItem* group2131 = new QTreeWidgetItem(group213);
	//group2131->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	//group2131->setText(0, QString::fromLocal8Bit("下料"));
	//group2131->setCheckState(0, Qt::Checked);
	//QTreeWidgetItem* group2132 = new QTreeWidgetItem(group213);
	//group2132->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	//group2132->setText(0, QString::fromLocal8Bit("称重设置"));
	//group2132->setCheckState(0, Qt::Checked);
	//QTreeWidgetItem* group2133 = new QTreeWidgetItem(group213);
	//group2133->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	//group2133->setText(0, QString::fromLocal8Bit("打印设置"));
	//group2133->setCheckState(0, Qt::Checked);
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
	QTreeWidgetItem* group241 = new QTreeWidgetItem(group25);
	if (lg == 0)group241->setText(0, QString::fromLocal8Bit("添加用户"));
	if (lg == 1)group241->setText(0, QString::fromLocal8Bit("Add user"));
	group241->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group241->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group242 = new QTreeWidgetItem(group25);
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
	//((Ui::QtPLCDialogClass*)ui)->lb_speed->setVisible(false);
	//((Ui::QtPLCDialogClass*)ui)->lE_speed->setVisible(false);
	//((Ui::QtPLCDialogClass*)ui)->label_speed->setVisible(false);
	//((Ui::QtPLCDialogClass*)ui)->lb_yield->setVisible(false);
	//((Ui::QtPLCDialogClass*)ui)->lE_yield->setVisible(false);
	//((Ui::QtPLCDialogClass*)ui)->label_yield->setVisible(false);
	//((Ui::QtPLCDialogClass*)ui)->groupBox_11->setFixedHeight(211);//211 241
	//((Ui::QtPLCDialogClass*)ui)->widget_2->move(((Ui::QtPLCDialogClass*)ui)->widget_2->x(),279);//279 309 
	//((Ui::QtPLCDialogClass*)ui)->widget_2->setFixedHeight(311);//311 281
	gettime();
	QStringList strlst;
	if (lg == 0) strlst << QString::fromLocal8Bit("胶囊") << QString::fromLocal8Bit("片剂");
	if (lg == 1) strlst << QString::fromLocal8Bit("Capsule") << QString::fromLocal8Bit("Tablet");
	((Ui::QtPLCDialogClass*)ui)->cB_Feedmode->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->cB_Feedmode->addItems(strlst);
	((Ui::QtPLCDialogClass*)ui)->cB_Feedmode->blockSignals(false);

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

	((Ui::QtPLCDialogClass*)ui)->lE_print1->setValidator(new QRegExpValidator(regx, this));
	((Ui::QtPLCDialogClass*)ui)->lE_print2->setValidator(new QRegExpValidator(regx, this));


	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	m_iHideprint1 = configIniRead.value("ProgramSetting/HidePrint1", 0).toInt();
	m_iHideprint2 = configIniRead.value("ProgramSetting/HidePrint2", 0).toInt();

	if (m_iHideprint1==1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_printCurve->setVisible(false);
	}
	if (m_iHideprint2 == 0)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_low->setValidator(new QRegExpValidator(regx, this));
		((Ui::QtPLCDialogClass*)ui)->lE_high->setValidator(new QRegExpValidator(regx, this));
		((Ui::QtPLCDialogClass*)ui)->lE_pure->setValidator(new QRegExpValidator(regx, this));
		((Ui::QtPLCDialogClass*)ui)->lE_speed->setValidator(new QRegExpValidator(regx, this));
		((Ui::QtPLCDialogClass*)ui)->lE_yield->setValidator(new QRegExpValidator(regx, this));

		m_cn = configIniRead.value("Customer/CustomerName", "").toString();
		m_mn = configIniRead.value("Customer/MedicineName", "").toString();
		m_l = configIniRead.value("Customer/Low", 0).toInt();
		m_h = configIniRead.value("Customer/High", 0).toInt();
		m_ps = configIniRead.value("Customer/PureShell", 0).toInt();
		m_speed = configIniRead.value("Customer/Speed", 0).toInt();
		m_yield = configIniRead.value("Customer/Yield", 0).toInt();
		m_pressure = configIniRead.value("Customer/Pressure", 0).toInt();

		((Ui::QtPLCDialogClass*)ui)->lE_customer->setText(m_cn);
		((Ui::QtPLCDialogClass*)ui)->lE_medicineName->setText(m_mn);
		((Ui::QtPLCDialogClass*)ui)->lE_low->setText(QString::number(m_l));
		((Ui::QtPLCDialogClass*)ui)->lE_high->setText(QString::number(m_h));
		//((Ui::QtPLCDialogClass*)ui)->lE_pure->setText(QString::number(m_ps));
		((Ui::QtPLCDialogClass*)ui)->lE_speed->setText(QString::number(m_speed));
		((Ui::QtPLCDialogClass*)ui)->lE_yield->setText(QString::number(m_yield));
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->lb_speed->setVisible(false);
		((Ui::QtPLCDialogClass*)ui)->lE_speed->setVisible(false);
		((Ui::QtPLCDialogClass*)ui)->label_speed->setVisible(false);
		((Ui::QtPLCDialogClass*)ui)->lb_yield->setVisible(false);
		((Ui::QtPLCDialogClass*)ui)->lE_yield->setVisible(false);
		((Ui::QtPLCDialogClass*)ui)->label_yield->setVisible(false);

		((Ui::QtPLCDialogClass*)ui)->label_51->setVisible(false);
		((Ui::QtPLCDialogClass*)ui)->label_55->setVisible(false);
		((Ui::QtPLCDialogClass*)ui)->lE_customer->setVisible(false);
		((Ui::QtPLCDialogClass*)ui)->lE_medicineName->setVisible(false);
		((Ui::QtPLCDialogClass*)ui)->label_59->setVisible(false);
		((Ui::QtPLCDialogClass*)ui)->label_70->setVisible(false);
		((Ui::QtPLCDialogClass*)ui)->lE_low->setVisible(false);
		((Ui::QtPLCDialogClass*)ui)->label_63->setVisible(false);
		((Ui::QtPLCDialogClass*)ui)->lE_high->setVisible(false);
		((Ui::QtPLCDialogClass*)ui)->lE_pure->setVisible(false);
		((Ui::QtPLCDialogClass*)ui)->label_64->setVisible(false);
		((Ui::QtPLCDialogClass*)ui)->label_71->setVisible(false);
		((Ui::QtPLCDialogClass*)ui)->label_72->setVisible(false);
		((Ui::QtPLCDialogClass*)ui)->pB_printTestingRecords->setVisible(false);

		((Ui::QtPLCDialogClass*)ui)->groupBox_11->setFixedHeight(161);//161 221 251
		((Ui::QtPLCDialogClass*)ui)->widget_2->move(((Ui::QtPLCDialogClass*)ui)->widget_2->x(), 219);//279 309 
		((Ui::QtPLCDialogClass*)ui)->widget_2->setFixedHeight(411);//351 321 411
	}
	((Ui::QtPLCDialogClass*)ui)->pB_copyIn->setEnabled(false);

	QRegExp regx_2("[a-zA-Z0-9_]+$");
	((Ui::QtPLCDialogClass*)ui)->lE_BatchName->setValidator(new QRegExpValidator(regx_2, this));
	lb_dataNow = new QLabel(((Ui::QtPLCDialogClass*)ui)->frame);

	lb_dataNow->move(30, 16);
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
		((Ui::QtPLCDialogClass*)ui)->label_10->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_10.png"));
		((Ui::QtPLCDialogClass*)ui)->label_15->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_15.png"));
		((Ui::QtPLCDialogClass*)ui)->label_18->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_18.png"));
		((Ui::QtPLCDialogClass*)ui)->label_79->setPixmap(QPixmap(AppPath + "/ico/fontImage/dqzh.png"));
		((Ui::QtPLCDialogClass*)ui)->label_78->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_78.png"));
		((Ui::QtPLCDialogClass*)ui)->label_80->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_80.png"));
		((Ui::QtPLCDialogClass*)ui)->label_39->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_39.png"));
		((Ui::QtPLCDialogClass*)ui)->label_50->setPixmap(QPixmap(AppPath + "/ico/fontImage/yxbz.png"));
		((Ui::QtPLCDialogClass*)ui)->label_49->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_49.png"));
		((Ui::QtPLCDialogClass*)ui)->label_16->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_16.png"));
		((Ui::QtPLCDialogClass*)ui)->label_17->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_17.png"));
		((Ui::QtPLCDialogClass*)ui)->label_48->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_48.png"));
	}
	else if (lg == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->label_10->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/label_10.png"));
		((Ui::QtPLCDialogClass*)ui)->label_15->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/label_15.png"));
		((Ui::QtPLCDialogClass*)ui)->label_18->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/label_18.png"));
		((Ui::QtPLCDialogClass*)ui)->label_79->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/dqzh.png"));
		((Ui::QtPLCDialogClass*)ui)->label_78->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/label_78.png"));
		((Ui::QtPLCDialogClass*)ui)->label_80->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/label_80.png"));
		((Ui::QtPLCDialogClass*)ui)->label_39->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/label_39.png"));
		((Ui::QtPLCDialogClass*)ui)->label_50->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/yxbz.png"));
		((Ui::QtPLCDialogClass*)ui)->label_49->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/label_49.png"));
		((Ui::QtPLCDialogClass*)ui)->label_16->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/label_16.png"));
		((Ui::QtPLCDialogClass*)ui)->label_17->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/label_17.png"));
		((Ui::QtPLCDialogClass*)ui)->label_48->setPixmap(QPixmap(AppPath + "/ico/fontImage/E/label_48.png"));
	}
	((Ui::QtPLCDialogClass*)ui)->label_10->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_15->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_18->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_79->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_78->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_80->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_39->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_50->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_49->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_16->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_17->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_48->setScaledContents(true);

	QString text1 = configIniRead.value("DistanceSetting/AxisFeedRelMovDistance", "").toString();
	QString text2 = configIniRead.value("DistanceSetting/AxisSwingRelMovDistance", "").toString();
	((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedRelMovDistance->setText(text1);	//下料电机相对运动距离，单位unit
	((Ui::QtPLCDialogClass*)ui)->lE_AxisSwingRelMovDistance->setText(text2);//旋转电机相对运动距离，单位unit


	int i_feedMode = configIniRead.value("ProgramSetting/FeedModeEnabled", 0).toInt();
	int i_showAO= configIniRead.value("ProgramSetting/i_showAO", 0).toInt();
	if (i_feedMode == 0) ((Ui::QtPLCDialogClass*)ui)->cB_Feedmode->setEnabled(false);
	if (i_showAO == 0) ((Ui::QtPLCDialogClass*)ui)->groupBox_8->setVisible(false);
	

	setYearMonthDay();
}

void QtPLCDialogClass::inittabicon()
{
	((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setIconSize(QSize(132, 33));
	((Ui::QtPLCDialogClass*)ui)->tabWidget->setIconSize(QSize(132, 33));
	if (lg == 0)
	{
		((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(0, QIcon(AppPath + "/ico/fontImage/xtjk.png"));
		((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(1, QIcon(AppPath + "/ico/fontImage/xtcs.png"));
		((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(2, QIcon(AppPath + "/ico/fontImage/yxcs.png"));
		((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(3, QIcon(AppPath + "/ico/fontImage/yxzt.png"));
		((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(4, QIcon(AppPath + "/ico/fontImage/yhgl.png"));
		((Ui::QtPLCDialogClass*)ui)->tabWidget->setTabIcon(0, QIcon(AppPath + "/ico/fontImage/srsc.png"));
		((Ui::QtPLCDialogClass*)ui)->tabWidget->setTabIcon(1, QIcon(AppPath + "/ico/fontImage/xlxz.png"));
		((Ui::QtPLCDialogClass*)ui)->tabWidget->setTabIcon(2, QIcon(AppPath + "/ico/fontImage/others.png"));
	}
	else if (lg == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(0, QIcon(AppPath + "/ico/fontImage/E/xtjk.png"));
		((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(1, QIcon(AppPath + "/ico/fontImage/E/xtcs.png"));
		((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(2, QIcon(AppPath + "/ico/fontImage/E/yxcs.png"));
		((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(3, QIcon(AppPath + "/ico/fontImage/E/yxzt.png"));
		((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(4, QIcon(AppPath + "/ico/fontImage/E/yhgl.png"));
		((Ui::QtPLCDialogClass*)ui)->tabWidget->setTabIcon(0, QIcon(AppPath + "/ico/fontImage/E/srsc.png"));
		((Ui::QtPLCDialogClass*)ui)->tabWidget->setTabIcon(1, QIcon(AppPath + "/ico/fontImage/E/xlxz.png"));
		((Ui::QtPLCDialogClass*)ui)->tabWidget->setTabIcon(2, QIcon(AppPath + "/ico/fontImage/E/others.png"));
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
void QtPLCDialogClass::setg_IUserLevel(int index)
{
	g_IUserLevel = index;	
	//user part
	if (g_IUserLevel == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->removeTab(4);
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
	bool b = connect(m_socket, SIGNAL(signal_FROMPLC(void*)), this, SLOT(getPLCData(void*)));
	b = connect(m_socket, SIGNAL(signal_SOCKETERROR()), this, SLOT(ErrorConnect()));

	b = connect(m_socket, SIGNAL(statechange_Connected()), this, SLOT(OnConnectedState()));
	b = connect(m_socket, SIGNAL(statechange_Connecting()), this, SLOT(OnConnectingState()));
	b = connect(m_socket, SIGNAL(statechange_Unconnected()), this, SLOT(OnUnconnectedState()));
	b = connect(m_socket, SIGNAL(statechange_Closing()), this, SLOT(OnClosingState()));
}
#pragma endregion

void QtPLCDialogClass::ErrorConnect()
{
	((Ui::QtPLCDialogClass*)ui)->lb_Alarm->setStyleSheet("color: rgb(255, 0,0);font-size:20pt");
	if (lg == 0) ((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("设备未就绪~");
	if (lg == 1) ((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("Not Ready~");
}
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

	
	tmp.Machine_Cmd.Outputs.Reject = m_data->Outputs.Reject;					//排废电磁铁
	tmp.Machine_Cmd.Outputs.ChannelSwith = m_data->Outputs.ChannelSwith;			//胶囊通道切换
	tmp.Machine_Cmd.Outputs.Vaccum = m_data->Outputs.Vaccum;					//真空发生器
	tmp.Machine_Cmd.Outputs.CapGet = m_data->Outputs.CapGet;					//取料电磁铁
	tmp.Machine_Cmd.Outputs.CapGetValve = m_data->Outputs.CapGetValve;			//取料电磁阀
	tmp.Machine_Cmd.Outputs.CapBackValve = m_data->Outputs.CapBackValve;			//回料电磁阀
	tmp.Machine_Cmd.Outputs.AlarmOut = m_data->Outputs.AlarmOut;				//报警蜂鸣器
	tmp.Machine_Cmd.Outputs.StopSignal = m_data->Outputs.StopSignal;				//停机信号
	tmp.Machine_Cmd.Outputs.AlarmSignal = m_data->Outputs.AlarmSignal;			//报警输出
	tmp.Machine_Cmd.Outputs.YellowAlarmout = m_data->Outputs.YellowAlarmout;			//黄灯报警
	tmp.Machine_Cmd.Outputs.Baffle = m_data->Outputs.Baffle;					//挡板
	tmp.Machine_Cmd.Outputs.Analogoutput = m_data->Outputs.Analogoutput;			//模拟量输出
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
	if (lg == 1) splineSeries->setName(QString::fromLocal8Bit("Group Data Curve"));


	chart = new QChart();
	chart->legend()->hide();
	if (lg == 0) chart->setTitle(QString::fromLocal8Bit("组重量曲线"));
	if (lg == 1) chart->setTitle(QString::fromLocal8Bit("Group Data Curve"));

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
	memcpy(m_data, (DataToPC_typ*)data, sizeof(DataToPC_typ));//主界面用

	//运行数据
#pragma region run
	if (!((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->hasFocus())//系统速度，0-10000对应0-100%
	{
		((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->setText(QString::number(m_data->ActData.SysOveride / 100));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_PassCount->hasFocus())//通过计数
	{
		//((Ui::QtPLCDialogClass*)ui)->lE_PassCount->setText(QString::number(m_data->ActData.PassCount));
		((Ui::QtPLCDialogClass*)ui)->lE_PassCount->setText(QString::number(m_data->ActData.ProdCount - m_data->ActData.RejectCount));
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
		((Ui::QtPLCDialogClass*)ui)->lE_TOverload->setText(QString::number(m_data->ActData.TOverload, 'f', 3));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->hasFocus())//超轻重量,单位g
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->setText(QString::number(m_data->ActData.TUnderload, 'f', 3));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->hasFocus())//内控线，上限,单位g
	{
		((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->setText(QString::number(m_data->ActData.InterOverLoad, 'f', 3));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->hasFocus())//内控线，下限,单位g
	{
		((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->setText(QString::number(m_data->ActData.InterUnderLoad, 'f', 3));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TDemand->hasFocus())//期望重量, 单位g
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TDemand->setText(QString::number(m_data->ActData.TDemand, 'f', 3));
	}

	if (!((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->hasFocus())//每组测试胶囊数量
	{
		((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->setText(QString::number(m_data->ActData.GroupSet));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_FeedOveride->hasFocus())//每组测试胶囊数量
	{
		((Ui::QtPLCDialogClass*)ui)->lE_FeedOveride->setText(QString::number(m_data->ActData.FeedOveride/100));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->hasFocus())////测试间隔时间,单位s
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->setText(QString::number(m_data->ActData.TestInterval));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_MultiCount->hasFocus())////测试间隔时间,单位s
	{
		((Ui::QtPLCDialogClass*)ui)->lE_MultiCount->setText(QString::number(m_data->ActData.MultiCount));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_BatchName->hasFocus())//BatchName[40];			//批号字符串
	{
		((Ui::QtPLCDialogClass*)ui)->lE_BatchName->setText(QString(QLatin1String(m_data->ActData.BatchName)));//Cause kinco has a bug when input this parameter,but use PC to input,we do not have this bug,so don't need to change.
	}

	((Ui::QtPLCDialogClass*)ui)->lE_GroupNo->setText(QString::number(m_data->ActData.GroupNo));

	((Ui::QtPLCDialogClass*)ui)->lE_GroupNo_2->setText(QString::number(m_data->Status.CapDataDisp.GroupNo));
	((Ui::QtPLCDialogClass*)ui)->lE_GroupIndex_2->setText(QString::number(m_data->Status.CapDataDisp.GroupIndex));
	((Ui::QtPLCDialogClass*)ui)->lE_GroupSum->setText(QString::number(m_data->ActData.GroupSum));
	((Ui::QtPLCDialogClass*)ui)->lE_GroupAvg->setText(QString::number(m_data->Status.CapDataDisp.GroupAvg));
	((Ui::QtPLCDialogClass*)ui)->lE_GroupMax->setText(QString::number(m_data->Status.CapDataDisp.GroupMax));
	((Ui::QtPLCDialogClass*)ui)->lE_GroupMin->setText(QString::number(m_data->Status.CapDataDisp.GroupMin));
	((Ui::QtPLCDialogClass*)ui)->lE_GroupMaxRatio->setText(QString::number(m_data->Status.CapDataDisp.GroupMaxRatio));
	((Ui::QtPLCDialogClass*)ui)->lE_GroupMinRatio->setText(QString::number(m_data->Status.CapDataDisp.GroupMinRatio));

	if (((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->isChecked())
	{
		if (/*m_data->ActData.GroupSum!=0 || */m_index != m_data->Status.GroupIndex && m_data->Status.GroupIndex!=0)
		{
			/*if (m_data->ActData.GroupSum != sumNo || m_index != m_data->Status.GroupIndex)
			{*/
				sumNo = m_data->ActData.GroupSum-sumNo;
				if (m_row==0)
				{
					mi = sumNo;
					ma = sumNo;
				}
				else
				{
					if (mi>sumNo)
					{
						mi = sumNo;
					}
					if (ma<sumNo)
					{
						ma = sumNo;
					}
				}

				data_One << sumNo;

				((Ui::QtPLCDialogClass*)ui)->tableWidget->insertRow(0);
				((Ui::QtPLCDialogClass*)ui)->tableWidget->setVerticalHeaderItem(0, new QTableWidgetItem(QString::number(++m_row)));
				((Ui::QtPLCDialogClass*)ui)->tableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(sumNo)));
				((Ui::QtPLCDialogClass*)ui)->tableWidget->item(0, 0)->setFlags(((Ui::QtPLCDialogClass*)ui)->tableWidget->item(0, 0)->flags() & (~Qt::ItemIsEditable));
				if (sumNo < m_data->ActData.TUnderload || sumNo > m_data->ActData.TOverload)
				{
					((Ui::QtPLCDialogClass*)ui)->tableWidget->item(0, 0)->setBackground(QBrush(QColor(255, 0, 0)));//red
				}
				else if (((sumNo >= m_data->ActData.TUnderload) && (sumNo < m_data->ActData.InterUnderLoad)) || ((sumNo >= m_data->ActData.InterOverLoad) && (sumNo <= m_data->ActData.TOverload)))
				{
					((Ui::QtPLCDialogClass*)ui)->tableWidget->item(0, 0)->setBackground(QBrush(QColor(255, 255, 0)));//yellow
				}
				else
				{
					((Ui::QtPLCDialogClass*)ui)->tableWidget->item(0, 0)->setBackground(QBrush(QColor(0, 255, 0)));//green
				}
				//((Ui::QtPLCDialogClass*)ui)->tableWidget->item(0, 0)->setFlags(((Ui::QtPLCDialogClass*)ui)->tableWidget->item(0, 0)->flags() & (~Qt::ItemIsSelectable));
				sumNo = m_data->ActData.GroupSum;
				m_index = m_data->Status.GroupIndex;

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

		if (m_data->Status.Finished==1)
		{
			m_row = 0;
			sumNo = 0;
			/*sumNo = m_data->ActData.GroupSum;*/
			m_index = m_data->Status.GroupIndex;

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
				configIniRead.setValue(QString::number(m_data->Status.CapDataDisp.GroupNo)+ "/data", str);
				QString lkstr = QString::number(m_data->Status.CapDataDisp.GroupNo) + "," + ymdhm + "," + ((Ui::QtPLCDialogClass*)ui)->lE_BatchName->text();
				configIniRead.setValue(QString::number(m_data->Status.CapDataDisp.GroupNo) + "/gn", lkstr);
				configIniRead.setValue(QString::number(m_data->Status.CapDataDisp.GroupNo) + "/theory", QString::number(m_data->ActData.TDemand, 'f', 3));
				if (m_iHideprint2 == 0)
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
				}

				QSettings timIni(AppPath + "\\data\\time.ini", QSettings::IniFormat);
				QString str1tmp = ymdhm.mid(0, 10);
				str1tmp.remove("/");
				QString str2tmp = ymdhm.remove("/");
				str2tmp.remove(" ");
				str2tmp.remove(":");
				timIni.setValue(str1tmp + "/"+ str2tmp, QString::number(m_data->Status.CapDataDisp.GroupNo));

				QSettings inq(AppPath + "\\data\\inquire.ini", QSettings::IniFormat);
				QString strinqu = inq.value("alldt/data", "").toString();
				if (strinqu.mid(0, 8) != str1tmp)
				{
					if (strinqu!="")
					{
						inq.setValue("alldt/data", str1tmp + "," + strinqu);
					}
					else
					{
						inq.setValue("alldt/data", str1tmp);
					}
				}
				data_One.clear();

				if (((Ui::QtPLCDialogClass*)ui)->gB_update->isChecked() == false)
				{
					if (!((Ui::QtPLCDialogClass*)ui)->lE_print1->hasFocus() && !((Ui::QtPLCDialogClass*)ui)->lE_print2->hasFocus())
					{
						if (m_iAutoUpdateFlag == 0)
						{
							((Ui::QtPLCDialogClass*)ui)->lE_print1->setText(QString::number(m_data->Status.CapDataDisp.GroupNo));
							m_iAutoUpdateFlag = 1;
						}
						//((Ui::QtPLCDialogClass*)ui)->lE_print1->setText(QString::number(m_data->Status.CapDataDisp.GroupNo - 1));
						((Ui::QtPLCDialogClass*)ui)->lE_print2->setText(QString::number(m_data->Status.CapDataDisp.GroupNo));
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
		data_One.clear();
		m_row = 0;
		sumNo = 0;
		/*sumNo = m_data->ActData.GroupSum;*/
		m_index = m_data->Status.GroupIndex;
	}


	if (!((Ui::QtPLCDialogClass*)ui)->cB_Feedmode->hasFocus())//0:每组去皮重,1:每次称重去皮重
	{
		/*if (m_iFeedMode<3)
		{
			on_cB_Feedmode_currentIndexChanged(m_iFeedMode);
		}
		else
		{
			on_cB_Feedmode_currentIndexChanged(m_data->ActData.Feedmode);
		}*/
		((Ui::QtPLCDialogClass*)ui)->cB_Feedmode->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->cB_Feedmode->setCurrentIndex(m_data->ActData.Feedmode);
		((Ui::QtPLCDialogClass*)ui)->cB_Feedmode->blockSignals(false);	

		if (m_data->ActData.Feedmode == 0 && m_bFeedModeFlag1 == 0)
		{
			m_bFeedModeFlag1 = 1;
			m_bFeedModeFlag2 = 0;
			((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedShake->setEnabled(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedshakestop->setEnabled(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedshakelevel->setEnabled(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedhome->setEnabled(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedFive->setEnabled(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedShakefive->setEnabled(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapClean->setEnabled(true);
			((Ui::QtPLCDialogClass*)ui)->lE_Feed_shakeoffset->setVisible(false);
			((Ui::QtPLCDialogClass*)ui)->label_30->setVisible(false);
			if (m_iHideprint2==0)
			{
			((Ui::QtPLCDialogClass*)ui)->lb_speed->setVisible(false);
			((Ui::QtPLCDialogClass*)ui)->lE_speed->setVisible(false);
			((Ui::QtPLCDialogClass*)ui)->label_speed->setVisible(false);
			((Ui::QtPLCDialogClass*)ui)->lb_yield->setVisible(false);
			((Ui::QtPLCDialogClass*)ui)->lE_yield->setVisible(false);
			((Ui::QtPLCDialogClass*)ui)->label_yield->setVisible(false);

			((Ui::QtPLCDialogClass*)ui)->groupBox_11->setFixedHeight(231);//221 251
			((Ui::QtPLCDialogClass*)ui)->widget_2->move(((Ui::QtPLCDialogClass*)ui)->widget_2->x(), 279);//279 309
			((Ui::QtPLCDialogClass*)ui)->widget_2->setFixedHeight(351);//351 321 411

			if (lg == 0)
			{
				((Ui::QtPLCDialogClass*)ui)->label_70->setText(QString::fromLocal8Bit("壳    重："));
			}
			else
			{
				((Ui::QtPLCDialogClass*)ui)->label_70->setText("Shell Weight:");

			}
			((Ui::QtPLCDialogClass*)ui)->label_71->setText(QString::fromLocal8Bit("mg"));
			((Ui::QtPLCDialogClass*)ui)->lE_pure->setText(QString::number(m_ps));
		}
		}
		else if (m_data->ActData.Feedmode == 1 && m_bFeedModeFlag2 == 0)
		{
			m_bFeedModeFlag1 = 0;
			m_bFeedModeFlag2 = 1;
			((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedShake->setEnabled(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedshakestop->setEnabled(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedshakelevel->setEnabled(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedhome->setEnabled(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedFive->setEnabled(false);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedShakefive->setEnabled(true);
			((Ui::QtPLCDialogClass*)ui)->pB_cmdCapClean->setEnabled(false);
			((Ui::QtPLCDialogClass*)ui)->lE_Feed_shakeoffset->setVisible(true);
			((Ui::QtPLCDialogClass*)ui)->label_30->setVisible(true);

			if (m_iHideprint2==0)
			{
				((Ui::QtPLCDialogClass*)ui)->lb_speed->setVisible(true);
				((Ui::QtPLCDialogClass*)ui)->lE_speed->setVisible(true);
				((Ui::QtPLCDialogClass*)ui)->label_speed->setVisible(true);
				((Ui::QtPLCDialogClass*)ui)->lb_yield->setVisible(true);
				((Ui::QtPLCDialogClass*)ui)->lE_yield->setVisible(true);
				((Ui::QtPLCDialogClass*)ui)->label_yield->setVisible(true);

				((Ui::QtPLCDialogClass*)ui)->groupBox_11->setFixedHeight(261);
				((Ui::QtPLCDialogClass*)ui)->widget_2->move(((Ui::QtPLCDialogClass*)ui)->widget_2->x(), 309);//279 309
				((Ui::QtPLCDialogClass*)ui)->widget_2->setFixedHeight(321);//351 321 411
				if (lg == 0)
				{
					((Ui::QtPLCDialogClass*)ui)->label_70->setText(QString::fromLocal8Bit("平均压力："));
				}
				else
				{
					((Ui::QtPLCDialogClass*)ui)->label_70->setText("Pressure:");
				}
				((Ui::QtPLCDialogClass*)ui)->label_71->setText(QString::fromLocal8Bit("KN"));
				((Ui::QtPLCDialogClass*)ui)->lE_pure->setText(QString::number(m_pressure));
			}
		}

	}																						  //int				Language;				//当前语言，0：中文，1：英文
	//float			UserAnalogoutput;		//用户模拟量输入
	//float			Adjustvalue;			//自动调整系数
	//unsigned int	DeltaInput;				//装量调整偏差值
	//int				cmdAutoPrint;			//自动打印，1:自动，0：手动
#pragma endregion
	//系统状态	
#pragma region status	
	((Ui::QtPLCDialogClass*)ui)->lE_Finished->setText(QString::number(m_data->Status.Finished));//本组结束
	((Ui::QtPLCDialogClass*)ui)->lE_GroupIndex->setText(QString::number(m_data->Status.GroupIndex));//本组序号
	//((Ui::QtPLCDialogClass*)ui)->lE_Weight->setText(QString::number(m_data->Status.Weight, 'f', 3));//本次重量
	((Ui::QtPLCDialogClass*)ui)->lE_ScaleResult->setText(QString::number(m_data->Status.ScaleResult, 'f', 3));//天平当前读数，单位g
	//((Ui::QtPLCDialogClass*)ui)->cB_ScaleStableState->setCurrentIndex(m_data->Status.ScaleStableState);//天平当前稳定状态,0:非常稳定,1:稳定,2:不稳定,3:非常不稳定

	((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedStep->setText(QString::number(m_data->Status.AxisFeedStep));			//下料电机状态机步骤
	((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedErrorNo->setText(QString::number(m_data->Status.AxisFeedErrorNo));		//下料电机错误代码
	//((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedRelMovDistance->setText(QString::number(m_data->Status.AxisFeedRelMovDistance));	//下料电机相对运动距离，单位unit
	((Ui::QtPLCDialogClass*)ui)->lE_AxisSwingStep->setText(QString::number(m_data->Status.AxisSwingStep));			//旋转电机状态机步骤
	((Ui::QtPLCDialogClass*)ui)->lE_AxisSwingErrorNo->setText(QString::number(m_data->Status.AxisSwingErrorNo));		//旋转电机错误代码
	//((Ui::QtPLCDialogClass*)ui)->lE_AxisSwingRelMovDistance->setText(QString::number(m_data->Status.AxisSwingRelMovDistance));//旋转电机相对运动距离，单位unit
	((Ui::QtPLCDialogClass*)ui)->lE_MachineStep->setText(QString::number(m_data->Status.MachineStep));			//系统运行状态机步骤
	if (m_b && m_data->Status.MachineStep != 0)
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
	((Ui::QtPLCDialogClass*)ui)->lE_TimeInterval->setText(QString::number(m_data->Status.TimeInterval, 'f', 2));			//测量实际间隔时间
	((Ui::QtPLCDialogClass*)ui)->lE_AlarmStatus->setText(QString::number(m_data->Status.AlarmStatus));
	if (m_data->Status.Alarm[0] >> 0 & 1 == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setEnabled(false);
		((Ui::QtPLCDialogClass*)ui)->lb_Alarm->setStyleSheet("color: rgb(255,0,0);font-size:20pt");
		if (lg == 0)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("落料步进报警! ");
		if (lg == 1)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("F-Motor err!");
	}
	else if (m_data->Status.Alarm[0] >> 1 & 1 == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setEnabled(false);
		((Ui::QtPLCDialogClass*)ui)->lb_Alarm->setStyleSheet("color: rgb(255,0,0);font-size:20pt");
		if (lg == 0)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("旋转步进报警!");
		if (lg == 1)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("R-Motor err!");
	}
	else if (m_data->Status.Alarm[0] >> 2 & 1 == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->lb_Alarm->setStyleSheet("color: rgb(255,0,0);font-size:20pt");
		if (lg == 0)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("落料超时!");
		if (lg == 1)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("Feeding err!");
	}
	else if (m_data->Status.Alarm[0] >> 3 & 1 == 1)
	{
		((Ui::QtPLCDialogClass*)ui)->lb_Alarm->setStyleSheet("color: rgb(255,0,0);font-size:20pt");
		if (lg == 0)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("秤读数超时!");
		if (lg == 1)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("Weighing err!");
	}
	else
	{
		if (m_istartFlag == 0)
		{
			((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setEnabled(true);
		}
		((Ui::QtPLCDialogClass*)ui)->lb_Alarm->setStyleSheet("color: rgb(0, 170, 127);font-size:20pt");
		if (lg == 0)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("设备运行正常~");
		if (lg == 1)((Ui::QtPLCDialogClass*)ui)->lb_Alarm->m_showText = QString::fromLocal8Bit("System normal");
	}
	char *str1 = (char*)(m_data->Status.Alarm);
//	((Ui::QtPLCDialogClass*)ui)->lE_Alarm16->setText(QString(QLatin1String(str1)));
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
	if (!((Ui::QtPLCDialogClass*)ui)->lE_Feed_shakeoffset->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_Feed_shakeoffset->setText(QString::number(m_data->Machine_Para.Feed_shakeoffset));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->setText(QString::number(m_data->Machine_Para.FeedTimeOut));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->setText(QString::number(m_data->Machine_Para.CapPickInterval, 'f', 1));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->setText(QString::number(m_data->Machine_Para.CapBackInterval, 'f', 1));
	}

	if (!((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->setText(QString::number(m_data->Machine_Para.TireDelay, 'f', 1));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->setText(QString::number(m_data->Machine_Para.ReadDelay, 'f', 1));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->setText(QString::number(m_data->Machine_Para.TireWaitTime, 'f', 1));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->setText(QString::number(m_data->Machine_Para.StopSignalDelay));
	}
#pragma endregion
	//输入点
#pragma region input
	if (!m_data->Inputs.FeedTrigger)
	{
		((Ui::QtPLCDialogClass*)ui)->lb_00->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->lb_00->setPixmap(QPixmap(AppPath + "/ico/redGreen.png"));

	}

	if (!m_data->Inputs.SwingTrigger)
	{
		((Ui::QtPLCDialogClass*)ui)->lb_10->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->lb_10->setPixmap(QPixmap(AppPath + "/ico/redGreen.png"));

	}

	if (!m_data->Inputs.FeedTrigger1)
	{
		((Ui::QtPLCDialogClass*)ui)->lb_20->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->lb_20->setPixmap(QPixmap(AppPath + "/ico/redGreen.png"));

	}
#pragma endregion
	//输出点
#pragma region output
	((Ui::QtPLCDialogClass*)ui)->lE_Analogoutput->setText(QString::number(m_data->Outputs.Analogoutput));		//模拟量输出
	if (m_data->Outputs.Reject)			//排废电磁铁
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdRejectcheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdRejectcheckable->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdRejectcheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdRejectcheckable->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdRejectcheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdRejectcheckable->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdRejectcheckable->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdRejectcheckable->blockSignals(false);
	}
	if (m_data->Outputs.ChannelSwith)	//胶囊通道切换
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwithcheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwithcheckable->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwithcheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwithcheckable->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwithcheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwithcheckable->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwithcheckable->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwithcheckable->blockSignals(false);
	}
	if (m_data->Outputs.Vaccum)//真空发生器
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccumcheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccumcheckable->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccumcheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccumcheckable->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccumcheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccumcheckable->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccumcheckable->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccumcheckable->blockSignals(false);
	}
	if (m_data->Outputs.CapGet)//取料电磁铁
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetcheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetcheckable->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetcheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetcheckable->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetcheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetcheckable->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetcheckable->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetcheckable->blockSignals(false);
	}
	if (m_data->Outputs.CapGetValve)//取料电磁阀
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValvecheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValvecheckable->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValvecheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValvecheckable->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValvecheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValvecheckable->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValvecheckable->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValvecheckable->blockSignals(false);
	}
	if (m_data->Outputs.CapBackValve)//回料电磁阀
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValvecheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValvecheckable->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValvecheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValvecheckable->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValvecheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValvecheckable->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValvecheckable->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValvecheckable->blockSignals(false);
	}
	if (m_data->Outputs.AlarmOut)//报警蜂鸣器
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOutcheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOutcheckable->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOutcheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOutcheckable->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOutcheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOutcheckable->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOutcheckable->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOutcheckable->blockSignals(false);
	}
	if (m_data->Outputs.StopSignal)//停机信号
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignalcheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignalcheckable->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignalcheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignalcheckable->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignalcheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignalcheckable->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignalcheckable->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignalcheckable->blockSignals(false);
	}
	if (m_data->Outputs.AlarmSignal)//报警输出
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignalcheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignalcheckable->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignalcheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignalcheckable->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignalcheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignalcheckable->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignalcheckable->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignalcheckable->blockSignals(false);
	}
	if (m_data->Outputs.YellowAlarmout)//黄灯报警
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmoutcheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmoutcheckable->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmoutcheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmoutcheckable->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmoutcheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmoutcheckable->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmoutcheckable->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmoutcheckable->blockSignals(false);
	}
	if (m_data->Outputs.Baffle)//挡板
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBafflecheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBafflecheckable->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBafflecheckable->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBafflecheckable->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBafflecheckable->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBafflecheckable->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBafflecheckable->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBafflecheckable->blockSignals(false);
	}

#pragma endregion
}//PC显示数据
bool sortImgLists(QString a, QString b)//排序方法
{
	return a.toLongLong() > b.toLongLong();
}
void QtPLCDialogClass::SWITCHOSK()//快捷键
{
	QProcess pro;
	QString strPath = "C:\\Windows\\System32\\osk.exe";
	pro.startDetached(strPath);
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
	((Ui::QtPLCDialogClass*)ui)->lE_hour1->setText("00");
	((Ui::QtPLCDialogClass*)ui)->lE_hour2->setText("23");
	QString logMinute = QString::number(current_time.time().minute());
	logMinute = logMinute.length() < 2 ? ("0" + logMinute) : logMinute;
	((Ui::QtPLCDialogClass*)ui)->lE_minute1->setText("00");
	((Ui::QtPLCDialogClass*)ui)->lE_minute2->setText("59");
	strTime = logYear + "/" //z=a>b?x:y
		+ logMonth + "/"
		+ logDay + " "
		+ logHour + ":"
		+ logMinute;
	return strTime;
}
QString QtPLCDialogClass::LEADOUTYMD()
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
	QString logSecond = QString::number(current_time.time().second());
	logSecond = logSecond.length() < 2 ? ("0" + logSecond) : logSecond;
	strTime = logYear + "_" //z=a>b?x:y
		+ logMonth + "_"
		+ logDay + "_"
		+ logHour + "_"
		+ logMinute + "_"
		+ logSecond;
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
	QString logSecond = QString::number(current_time.time().second());
	logSecond = logSecond.length() < 2 ? ("0" + logSecond) : logSecond;
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
void QtPLCDialogClass::on_lE_SysOveride_editingFinished()//系统速度，0-10000对应0-100%
{
	QString oldstr = QString::number(m_data->ActData.SysOveride / 100);
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->text();
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->blockSignals(false);
		return;
	}
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	if (((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->text().toInt() > 100)
		((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->setText("100");
	typ.ActData.SysOveride = ((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->text().toInt() * 100;
	m_socket->Communicate_PLC(&typ, nullptr);
	((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->blockSignals(false);

}
void QtPLCDialogClass::OnGetLeadoutPath(QString str)
{
	m_sTempPathForLeadout = str+"/EXPORT/" +LEADOUTYMD();
	if (m_sTempPathForLeadout =="/EXPORT/" + LEADOUTYMD())
	{
		m_sTempPathForLeadout = "";
	}
}
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
//passcount//通过计数
/*void QtPLCDialogClass::on_lE_RejectCount_editingFinished()//剔废计数
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.ActData.RejectCount = ((Ui::QtPLCDialogClass*)ui)->lE_RejectCount->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_ProdCount_editingFinished()//称重计数
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.ActData.ProdCount = ((Ui::QtPLCDialogClass*)ui)->lE_ProdCount->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_TOCount_editingFinished()//过重计数
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.ActData.TOCount = ((Ui::QtPLCDialogClass*)ui)->lE_TOCount->text().toUInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_lE_TUCount_editingFinished()//过轻计数
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.ActData.TUCount = ((Ui::QtPLCDialogClass*)ui)->lE_TUCount->text().toUInt();
	m_socket->Communicate_PLC(&typ, nullptr);
}*/
void QtPLCDialogClass::on_lE_TOverload_editingFinished()//超重重量,单位g
{
	QString oldstr = QString::number(m_data->ActData.TOverload, 'f', 3);
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_TOverload->text();
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TOverload->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_TOverload->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_TOverload->blockSignals(false);
		return;
	}
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.ActData.TOverload = ((Ui::QtPLCDialogClass*)ui)->lE_TOverload->text().toFloat();
	m_socket->Communicate_PLC(&typ, nullptr);
	((Ui::QtPLCDialogClass*)ui)->lE_TOverload->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_TOverload->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_TOverload->blockSignals(false);
}
void QtPLCDialogClass::on_lE_TUnderload_editingFinished()//超轻重量,单位g
{
	QString oldstr = QString::number(m_data->ActData.TUnderload, 'f', 3);
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->text();
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->blockSignals(false);
		return;
	}
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.ActData.TUnderload = ((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->text().toFloat();
	m_socket->Communicate_PLC(&typ, nullptr);
	((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_TUnderload->blockSignals(false);
}
void QtPLCDialogClass::on_lE_InterOverLoad_editingFinished()//内控线，上限,单位g
{
	QString oldstr = QString::number(m_data->ActData.InterOverLoad, 'f', 3);
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->text();
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->blockSignals(false);
		return;
	}
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.ActData.InterOverLoad = ((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->text().toFloat();
	m_socket->Communicate_PLC(&typ, nullptr);
	((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_InterOverLoad->blockSignals(false);
}
void QtPLCDialogClass::on_lE_InterUnderLoad_editingFinished()//内控线，下限,单位g
{
	QString oldstr = QString::number(m_data->ActData.InterUnderLoad, 'f', 3);
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->text();
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->blockSignals(false);
		return;
	}
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.ActData.InterUnderLoad = ((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->text().toFloat();
	m_socket->Communicate_PLC(&typ, nullptr);
	((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_InterUnderLoad->blockSignals(false);
}
void QtPLCDialogClass::on_lE_TDemand_editingFinished()///期望重量,单位g	
{
	QString oldstr = QString::number(m_data->ActData.TDemand, 'f', 3);
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_TDemand->text();
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TDemand->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_TDemand->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_TDemand->blockSignals(false);
		return;
	}
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.ActData.TDemand = ((Ui::QtPLCDialogClass*)ui)->lE_TDemand->text().toFloat();
	m_socket->Communicate_PLC(&typ, nullptr);
	((Ui::QtPLCDialogClass*)ui)->lE_TDemand->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_TDemand->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_TDemand->blockSignals(false);
}
void QtPLCDialogClass::on_cB_TireMode_currentIndexChanged(int index)
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.ActData.TireMode = index;
	m_socket->Communicate_PLC(&typ, nullptr);
}

void QtPLCDialogClass::on_lE_GroupSet_editingFinished()///每组测试胶囊数量
{
	QString oldstr = QString::number(m_data->ActData.GroupSet);
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->text();
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->blockSignals(false);
		return;
	}
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.ActData.GroupSet = ((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);
	((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_GroupSet->blockSignals(false);
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
void QtPLCDialogClass::on_lE_TestInterval_editingFinished()///测试间隔时间,单位s
{
	QString oldstr = QString::number(m_data->ActData.TestInterval);
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->text();
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->blockSignals(false);
		return;
	}
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	int i= ((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->text().toInt();
	if (i<60)
	{
		i = 60;
	}
	typ.ActData.TestInterval = i;

	m_socket->Communicate_PLC(&typ, nullptr);
	((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->blockSignals(false);
}
void QtPLCDialogClass::on_lE_MultiCount_editingFinished()///测试间隔时间,单位s
{
	QString oldstr = QString::number(m_data->ActData.MultiCount);
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_MultiCount->text();
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_MultiCount->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_MultiCount->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_MultiCount->blockSignals(false);
		return;
	}
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.ActData.MultiCount = ((Ui::QtPLCDialogClass*)ui)->lE_MultiCount->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);
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
void QtPLCDialogClass::on_cB_Feedmode_currentIndexChanged(int index)
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.ActData.Feedmode = index;
	m_socket->Communicate_PLC(&typ, nullptr);

	QSettings WriteIni(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	WriteIni.setValue("ProgramSetting/FeedMode", index);
	m_iFeedMode = index;

}
void QtPLCDialogClass::on_lE_AxisFeedRelMovDistance_editingFinished()
{
	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	int i1 = configIniRead.value("DistanceSetting/AxisFeedRelMovDistance", 0).toInt();
	if (((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedRelMovDistance->text().toInt()!=i1)
	{
		configIniRead.setValue("DistanceSetting/AxisFeedRelMovDistance", ((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedRelMovDistance->text());//写当前模板
	}
}
void QtPLCDialogClass::on_lE_AxisSwingRelMovDistance_editingFinished()
{
	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	int i2 = configIniRead.value("DistanceSetting/AxisSwingRelMovDistance", 0).toInt();
	if (((Ui::QtPLCDialogClass*)ui)->lE_AxisSwingRelMovDistance->text().toInt() != i2)
	{
		configIniRead.setValue("DistanceSetting/AxisSwingRelMovDistance", ((Ui::QtPLCDialogClass*)ui)->lE_AxisSwingRelMovDistance->text());//写当前模板
	}
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
	QString oldstr = QString::number(m_data->Machine_Para.s_trg_stop[0]);
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop0->text();
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop0->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop0->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop0->blockSignals(false);
		return;
	}
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.s_trg_stop[0] = ((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop0->text().toFloat();
	m_socket->Communicate_PLC(&typ, nullptr);
	((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop0->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop0->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop0->blockSignals(false);
}
void QtPLCDialogClass::on_lE_s_trg_stop1_editingFinished()
{
	QString oldstr = QString::number(m_data->Machine_Para.s_trg_stop[1]);
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop1->text();
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop1->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop1->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop1->blockSignals(false);
		return;
	}
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.s_trg_stop[1] = ((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop1->text().toFloat();
	m_socket->Communicate_PLC(&typ, nullptr);
	((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop1->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop1->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_s_trg_stop1->blockSignals(false);
}

void QtPLCDialogClass::on_lE_Feed_shakeoffset_editingFinished()
{
	QString oldstr = QString::number(m_data->Machine_Para.Feed_shakeoffset);
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_Feed_shakeoffset->text();
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_Feed_shakeoffset->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_Feed_shakeoffset->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_Feed_shakeoffset->blockSignals(false);
		return;
	}
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.Feed_shakeoffset = ((Ui::QtPLCDialogClass*)ui)->lE_Feed_shakeoffset->text().toFloat();
	m_socket->Communicate_PLC(&typ, nullptr);
	((Ui::QtPLCDialogClass*)ui)->lE_Feed_shakeoffset->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_Feed_shakeoffset->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_Feed_shakeoffset->blockSignals(false);
}//lE_Feed_shakeoffset
void QtPLCDialogClass::on_lE_FeedTimeOut_editingFinished()
{
	QString oldstr = QString::number(m_data->Machine_Para.FeedTimeOut);
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->text();
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->blockSignals(false);
		return;
	}
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.FeedTimeOut = ((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->text().toFloat();
	m_socket->Communicate_PLC(&typ, nullptr);
	((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_FeedTimeOut->blockSignals(false);
}
void QtPLCDialogClass::on_lE_CapPickInterval_editingFinished()
{
	QString oldstr = QString::number(m_data->Machine_Para.CapPickInterval, 'f', 2);
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->text();
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->blockSignals(false);
		return;
	}
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.CapPickInterval = ((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->text().toFloat();
	m_socket->Communicate_PLC(&typ, nullptr);
	((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->blockSignals(false);
}
void QtPLCDialogClass::on_lE_CapBackInterval_editingFinished()
{
	QString oldstr = QString::number(m_data->Machine_Para.CapBackInterval, 'f', 2);
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->text();
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->blockSignals(false);
		return;
	}
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.CapBackInterval = ((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->text().toFloat();
	m_socket->Communicate_PLC(&typ, nullptr);
	((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->blockSignals(false);
}

void QtPLCDialogClass::on_lE_TireDelay_editingFinished()
{
	QString oldstr = QString::number(m_data->Machine_Para.TireDelay, 'f', 2);
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->text();
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->blockSignals(false);
		return;
	}
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.TireDelay = ((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->text().toFloat();
	m_socket->Communicate_PLC(&typ, nullptr);
	((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->blockSignals(false);
}
void QtPLCDialogClass::on_lE_ReadDelay_editingFinished()
{
	QString oldstr = QString::number(m_data->Machine_Para.ReadDelay, 'f', 2);
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->text();
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->blockSignals(false);
		return;
	}
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.ReadDelay = ((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->text().toFloat();
	m_socket->Communicate_PLC(&typ, nullptr);
	((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->blockSignals(false);
}
void QtPLCDialogClass::on_lE_TireWaitTime_editingFinished()
{
	QString oldstr = QString::number(m_data->Machine_Para.TireWaitTime, 'f', 2);
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->text();
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->blockSignals(false);
		return;
	}
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.TireWaitTime = ((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->text().toFloat();
	m_socket->Communicate_PLC(&typ, nullptr);
	((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->blockSignals(false);
}
void QtPLCDialogClass::on_lE_StopSignalDelay_editingFinished()
{
	QString oldstr = QString::number(m_data->Machine_Para.StopSignalDelay);
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->text();
	if (oldstr == str)
	{
		((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->clearFocus();
		((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->blockSignals(false);
		return;
	}
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.StopSignalDelay = ((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);
	((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_StopSignalDelay->blockSignals(false);
}
#pragma endregion

#pragma region ui cmd slots
//DateTimeStructTyp		DateTimeSet;		//设定日期时间目标
//unsigned char		cmdChangeDT;					//修改日期时间,1:执行，自动复位

void QtPLCDialogClass::on_pB_startSearch_clicked()
{
	((Ui::QtPLCDialogClass*)ui)->pB_inquirecheckable->setChecked(false);
	on_lE_year1_editingFinished();
	on_lE_month1_editingFinished();
	on_lE_day1_editingFinished();
	on_lE_hour1_editingFinished();
	on_lE_minute1_editingFinished();
	on_lE_hour2_editingFinished();
	on_lE_minute2_editingFinished();
	CompareYearMonthDay();
}
void QtPLCDialogClass::on_lW_data_itemDoubleClicked(QListWidgetItem *item)
{
	QString str = item->text();
	if (((Ui::QtPLCDialogClass*)ui)->lW_data->item(0)->text()==QString::fromLocal8Bit("符合组号")|| ((Ui::QtPLCDialogClass*)ui)->lW_data->item(0)->text() == QString::fromLocal8Bit("Matched"))
	{
		if (str== QString::fromLocal8Bit("符合组号") ||str == QString::fromLocal8Bit("Matched"))
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
void QtPLCDialogClass::on_lW_data_itemClicked(QListWidgetItem *item)
{
	if (((Ui::QtPLCDialogClass*)ui)->lW_data->item(0)->text() != QString::fromLocal8Bit("符合组号")&& ((Ui::QtPLCDialogClass*)ui)->lW_data->item(0)->text() != QString::fromLocal8Bit("Matched"))
	{
		return;
	}
	QString str = item->text();
	if (str!= QString::fromLocal8Bit("符合组号") && str != QString::fromLocal8Bit("Matched"))
	{
		((Ui::QtPLCDialogClass*)ui)->gB_update->setChecked(true);
		if (leflag==0)
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
void QtPLCDialogClass::BeforePrint()
{
	//((Ui::QtPLCDialogClass*)ui)->pB_printData->setEnabled(false);
//((Ui::QtPLCDialogClass*)ui)->pB_printCurve->setEnabled(false);
	int p1 = ((Ui::QtPLCDialogClass*)ui)->lE_print1->text().toInt();
	int p2 = ((Ui::QtPLCDialogClass*)ui)->lE_print2->text().toInt();
	((Ui::QtPLCDialogClass*)ui)->lE_print1->setText(QString::number(p1));
	((Ui::QtPLCDialogClass*)ui)->lE_print2->setText(QString::number(p2));

	if (p1 > p2)
	{
		if (lg == 0)emit showWindowOut(QString::fromLocal8Bit("无满足条件数据!"));
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
			if (lg == 0)emit showWindowOut(QString::fromLocal8Bit("无满足条件数据!"));
			if (lg == 1)emit showWindowOut(QString::fromLocal8Bit("No Data!"));
			((Ui::QtPLCDialogClass*)ui)->pB_printCurve->setEnabled(true);
			return;
		}

		else
		{
			if (cb.mid(0,1) == "3")
			{
				emit showWindowOut(QString::fromLocal8Bit("导出目录：") + m_sTempPathForLeadout);
			}
			emit TODRAWPICTURE(1, cb, p1, p2, m_sTempPathForLeadout + "/report.pdf");
			return;
		}


	}
	else
	{
		QSettings configIniRead(AppPath + "\\data\\data.ini", QSettings::IniFormat);
		QVector<QString> GroupNumber;
		for (int i = p1; i < p2 + 1; i++)
		{
			QString str = configIniRead.value(QString::number(i) + "/data", 0).toString();
			if (str != "0")
			{
				GroupNumber << configIniRead.value(QString::number(i) + "/gn", "0").toString();
				break;
			}
		}

		if (GroupNumber.size() > 0)
		{
			if (cb.mid(0, 1) == "3")
			{
				emit showWindowOut(QString::fromLocal8Bit("导出目录：") + m_sTempPathForLeadout);
			}
			emit TODRAWPICTURE(1, cb, p1, p2, m_sTempPathForLeadout + "/report.pdf");
		}

		else
		{
			if (lg == 0)emit showWindowOut(QString::fromLocal8Bit("无打印数据!"));
			if (lg == 1)emit showWindowOut(QString::fromLocal8Bit("No Data!"));
			return;
		}
	}
}
void QtPLCDialogClass::on_pB_keyboard_clicked()
{
	SWITCHOSK();
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
void QtPLCDialogClass::getUdisk()
{
	QString UDiskPath = "";
	foreach(const QStorageInfo &storage, QStorageInfo::mountedVolumes())
	{
		if (storage.isValid() && storage.isReady())
		{
			UDiskPath = storage.rootPath();
			if (UDiskPath!="C:/" && UDiskPath != "Z:/")
			{
				m_sTempPathForLeadout = UDiskPath+"EXPORT/"+LEADOUTYMD();
			}
		}

	}
}
void QtPLCDialogClass::on_pB_LeadOut_clicked()//记录
{

	getUdisk();
	if (m_sTempPathForLeadout == "")
	{
		emit showWindowOut(QString::fromLocal8Bit("请插入U盘!"));
		return;
	}
	

	if (m_data->ActData.Feedmode == 0)
	{
		cb = "0";
	}
	else
	{
		cb = "1";
	}
	cb = "3" + cb;
	BeforePrint();
}
void QtPLCDialogClass::on_pB_printTestingRecords_clicked()//记录
{
	if (m_data->ActData.Feedmode == 0)
	{
		cb = "0";
	}
	else
	{
		cb = "1";
	}
	cb = "1" + cb;
	BeforePrint();
}
void QtPLCDialogClass::on_pB_printCurve_clicked()//曲线
{
	if (m_data->ActData.Feedmode == 0)
	{
		cb = "0";
	}
	else
	{
		cb = "1";
	}
	cb = "0" + cb;
	BeforePrint();
}
void QtPLCDialogClass::on_pB_Read1_clicked()//读取1
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.enable = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
	emit showWindowOut(QString::fromLocal8Bit("PLC默认参数\n已读取!"));
}
void QtPLCDialogClass::on_pB_Read2_clicked()//读取2
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.enable = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
	emit showWindowOut(QString::fromLocal8Bit("PLC默认参数\n已读取!"));
}
void QtPLCDialogClass::on_pB_Write1_clicked()//写入1
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.enable = 2;
	m_socket->Communicate_PLC(&typ, nullptr);
	emit showWindowOut(QString::fromLocal8Bit("PLC默认参数\n已保存!"));
}
void QtPLCDialogClass::on_pB_Write2_clicked()//写入2
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.enable = 2;
	m_socket->Communicate_PLC(&typ, nullptr);
	emit showWindowOut(QString::fromLocal8Bit("PLC默认参数\n已保存!"));
}
void QtPLCDialogClass::on_pB_cmdScaleRead_clicked()//秤读数命令,1:执行，自动复位
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdScaleRead = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdScaleTire_clicked()//秤清零,1:执行，自动复位
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdScaleTire = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdScaleSetStable_clicked()//设定秤稳定状态,1:执行，自动复位
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdScaleSetStable = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
//void QtPLCDialogClass::on_cB_paraScaleSetStable_currentIndexChanged(int index)//稳定状态设定目标，0:非常稳定,1:稳定,2:不稳定,3:非常不稳定
//{
//	DataFromPC_typ typ;
//	typ = getPCParaData();
//typ.Telegram_typ = 1;
//	typ.Machine_Cmd.cmdScaleSetStable = index;
//	m_socket->Communicate_PLC(&typ, nullptr);
//}
void QtPLCDialogClass::on_pB_cmdScaleCalibExt_clicked()//秤外部校正,1:执行，自动复位
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdScaleCalibExt = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisFeedJogPos_pressed()//下料正转点动，1:执行，0:停止
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisFeedJogPos = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisFeedJogPos_released()//下料正转点动，1:执行，0:停止 
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisFeedJogPos = 0;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisFeedJogNeg_pressed()//下料反转点动，1:执行，0:停止
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisFeedJogNeg = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisFeedJogNeg_released()//下料反转点动，1:执行，0:停止
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisFeedJogNeg = 0;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisFeedRelMov_clicked()//下料相对运动启动，1:执行，自动复位
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisFeedRelMov = 1;
	typ.Machine_Cmd.AxisFeedRelMovDistance = ((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedRelMovDistance->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);


	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);

	configIniRead.setValue("DistanceSetting/AxisFeedRelMovDistance", ((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedRelMovDistance->text());//写当前模板
	configIniRead.setValue("DistanceSetting/AxisSwingRelMovDistance", ((Ui::QtPLCDialogClass*)ui)->lE_AxisSwingRelMovDistance->text());//写当前模板
}
void QtPLCDialogClass::on_pB_cmdAxisFeedPosMov_clicked()//下料正向连续运动启动，1:执行，自动复位
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisFeedPosMov = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisFeedStopMov_clicked()//下料停止运动，1:执行，自动复位
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisFeedStopMov = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisSwingJogPos_pressed()//旋转正转点动，1:执行，0:停止
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisSwingJogPos = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisSwingJogPos_released()//旋转正转点动，1:执行，0:停止
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisSwingJogPos = 0;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisSwingJogNeg_pressed()//旋转反转点动，1:执行，0:停止
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisSwingJogNeg = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisSwingJogNeg_released()//旋转反转点动，1:执行，0:停止
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisSwingJogNeg = 0;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisSwingRelMov_clicked()//旋转相对运动启动，1:执行，自动复位
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisSwingRelMov = 1;
	
	typ.Machine_Cmd.AxisSwingRelMovDistance = ((Ui::QtPLCDialogClass*)ui)->lE_AxisSwingRelMovDistance->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);


	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);

	configIniRead.setValue("DistanceSetting/AxisFeedRelMovDistance", ((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedRelMovDistance->text());//写当前模板
	configIniRead.setValue("DistanceSetting/AxisSwingRelMovDistance", ((Ui::QtPLCDialogClass*)ui)->lE_AxisSwingRelMovDistance->text());//写当前模板
}
void QtPLCDialogClass::on_pB_cmdAxisSwingPosMov_clicked()//旋转正向连续运动启动，1:执行，自动复位
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisSwingPosMov = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisSwingStopMov_clicked()//旋转停止运动，1:执行，自动复位
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisSwingStopMov = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdFeedSingle_clicked()//单粒下料，1:执行，自动复位
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdFeedSingle = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdFeedSingleStop_clicked()//单粒下料停止，1:执行，自动复位
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdFeedSingleStop = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdSwing_clicked()//旋转单工位,1:执行，自动复位
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdSwing = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}

void QtPLCDialogClass::on_pB_inquirecheckable_toggled(bool checked)//
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
		if (strinqu=="")
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
void QtPLCDialogClass::on_pB_showPrt_toggled(bool checked)//
{
	emit SHOWPRT(checked);
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
void QtPLCDialogClass::on_pB_cmdStartcheckable_toggled(bool checked)//启动 停止
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;

	((Ui::QtPLCDialogClass*)ui)->lW_data->setVisible(false);
	((Ui::QtPLCDialogClass*)ui)->lb_search->setVisible(false);
	((Ui::QtPLCDialogClass*)ui)->tableWidget->setVisible(true);

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
		((Ui::QtPLCDialogClass*)ui)->lE_BatchName->setEnabled(false);
		ExitBtn->setEnabled(false);
		typ.Machine_Cmd.cmdStart = 1;

		if (m_iHideprint2 == 0)
		{
			((Ui::QtPLCDialogClass*)ui)->lE_low->setText(QString::number(((Ui::QtPLCDialogClass*)ui)->lE_low->text().toInt()));
			((Ui::QtPLCDialogClass*)ui)->lE_high->setText(QString::number(((Ui::QtPLCDialogClass*)ui)->lE_high->text().toInt()));
			((Ui::QtPLCDialogClass*)ui)->lE_pure->setText(QString::number(((Ui::QtPLCDialogClass*)ui)->lE_pure->text().toInt()));//两个功能
			((Ui::QtPLCDialogClass*)ui)->lE_yield->setText(QString::number(((Ui::QtPLCDialogClass*)ui)->lE_yield->text().toInt()));
			((Ui::QtPLCDialogClass*)ui)->lE_speed->setText(QString::number(((Ui::QtPLCDialogClass*)ui)->lE_speed->text().toInt()));

			QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);

			configIniRead.setValue("Customer/CustomerName", (((Ui::QtPLCDialogClass*)ui)->lE_customer->text()));
			configIniRead.setValue("Customer/MedicineName", (((Ui::QtPLCDialogClass*)ui)->lE_medicineName->text()));
			configIniRead.setValue("Customer/Low", (((Ui::QtPLCDialogClass*)ui)->lE_low->text()));
			configIniRead.setValue("Customer/High", (((Ui::QtPLCDialogClass*)ui)->lE_high->text()));
			if (m_data->ActData.Feedmode==0)
			{
				configIniRead.setValue("Customer/PureShell", (((Ui::QtPLCDialogClass*)ui)->lE_pure->text()));
			}
			else
			{
				configIniRead.setValue("Customer/Pressure", (((Ui::QtPLCDialogClass*)ui)->lE_pure->text()));
			}
			configIniRead.setValue("Customer/Yield", (((Ui::QtPLCDialogClass*)ui)->lE_yield->text()));
			configIniRead.setValue("Customer/Speed", (((Ui::QtPLCDialogClass*)ui)->lE_speed->text()));


			m_speed = configIniRead.value("Customer/Speed", 0).toInt();
			m_yield = configIniRead.value("Customer/Yield", 0).toInt();
			m_pressure = configIniRead.value("Customer/Pressure", 0).toInt();


			m_cn = configIniRead.value("Customer/CustomerName", "").toString();
			m_mn = configIniRead.value("Customer/MedicineName", "").toString();
			m_l = configIniRead.value("Customer/Low", 0).toInt();
			m_h = configIniRead.value("Customer/High", 0).toInt();
			m_ps = configIniRead.value("Customer/PureShell", 0).toInt();
		}
	}
	else
	{
		if (lg == 0)pix.load(AppPath + "/ico/start.png");
		if (lg == 1)pix.load(AppPath + "/ico/E/start.png");
		((Ui::QtPLCDialogClass*)ui)->lE_BatchName->setEnabled(true); 
		ExitBtn->setEnabled(true);
		typ.Machine_Cmd.cmdStop = 1;
	}
	((Ui::QtPLCDialogClass*)ui)->pB_cmdStartcheckable->setIcon(pix);
	btnTimer->start(1);
	m_socket->Communicate_PLC(&typ, nullptr);
}
//unsigned char		cmdStart;						//启动称重，1:执行，自动复位
//unsigned char		cmdEStop;						//急停，1:执行，自动复位

//unsigned char		cmdStop;						//停止,1:执行，自动复位
//unsigned char		cmdInit;						//初始化，1:执行，自动复位
void QtPLCDialogClass::on_pB_cmdAlarmReset_clicked()
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAlarmReset = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdCounterZero_clicked()
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdCounterZero = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_ChangeLanguage()
{
	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	int langu = configIniRead.value("Language/currentLanguage", "").toInt();
	if (langu == 0)
	{
		configIniRead.setValue("Language/currentLanguage", 1);
		showMsgBox("Information", "Change to English,\nRestart software then worked!", "I know", "");
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
	if (1) {
		((Ui::QtPLCDialogClass*)ui)->label_yield->setText("Ten Thousand/h");
		((Ui::QtPLCDialogClass*)ui)->lb_yield->setText("Yield:");
		((Ui::QtPLCDialogClass*)ui)->label_speed->setText("r/min");
		((Ui::QtPLCDialogClass*)ui)->lb_speed->setText("Speed:");

		((Ui::QtPLCDialogClass*)ui)->gB_update->setTitle(QString::fromLocal8Bit("Auto Update"));
		((Ui::QtPLCDialogClass*)ui)->pB_keyboard->setText("Keyboard");
		((Ui::QtPLCDialogClass*)ui)->label_51->setText("Customer:");
		((Ui::QtPLCDialogClass*)ui)->label_59->setText("Qualified:");
		((Ui::QtPLCDialogClass*)ui)->label_55->setText("Medicine:");
		((Ui::QtPLCDialogClass*)ui)->label_63->setText("to");
		if (m_data->ActData.Feedmode == 0)
		{
			((Ui::QtPLCDialogClass*)ui)->label_70->setText("Shell Weight:");
		}
		else
		{
			((Ui::QtPLCDialogClass*)ui)->label_70->setText("Pressure:");
		}
		((Ui::QtPLCDialogClass*)ui)->pB_printTestingRecords->setText("Print Testing Records");

		//((Ui::QtPLCDialogClass*)ui)->groupBox_11->setTitle("Print");
		((Ui::QtPLCDialogClass*)ui)->label_36->setText("Search:");
		((Ui::QtPLCDialogClass*)ui)->label_61->setText("Result:");
		((Ui::QtPLCDialogClass*)ui)->label_35->setText("GroupNum:");
		((Ui::QtPLCDialogClass*)ui)->pB_copyIn->setText("Copy in" + QString::fromLocal8Bit("↓"));
		((Ui::QtPLCDialogClass*)ui)->pB_startSearch->setText("Start Search");
		((Ui::QtPLCDialogClass*)ui)->pB_inquirecheckable->setText("Inquire");
		((Ui::QtPLCDialogClass*)ui)->pB_printCurve->setText("Print Data&&Curve");
		((Ui::QtPLCDialogClass*)ui)->label_37->setText("to");
		((Ui::QtPLCDialogClass*)ui)->label_23->setText("to");

		((Ui::QtPLCDialogClass*)ui)->label_9->setText("GroupNum");
		((Ui::QtPLCDialogClass*)ui)->label->setText("Times");
		((Ui::QtPLCDialogClass*)ui)->label_3->setText("Total(g)");
		((Ui::QtPLCDialogClass*)ui)->label_7->setText("Average(g)");
		((Ui::QtPLCDialogClass*)ui)->label_6->setText("Max(g)");
		((Ui::QtPLCDialogClass*)ui)->label_34->setText("MaxRatio(%)");
		((Ui::QtPLCDialogClass*)ui)->label_8->setText("Min(g)");
		((Ui::QtPLCDialogClass*)ui)->label_29->setText("MinRatio(%)");
		//输入输出
		((Ui::QtPLCDialogClass*)ui)->label_40->setText("Capsule Drop");
		((Ui::QtPLCDialogClass*)ui)->label_11->setText("Swing Arm");
		((Ui::QtPLCDialogClass*)ui)->label_46->setText("Capsule Drop1");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdRejectcheckable->setText("Reject");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwithcheckable->setText("ChannelSwith");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccumcheckable->setText("Vaccum");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetcheckable->setText("CapGet");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValvecheckable->setText("CapGetValve");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValvecheckable->setText("CapBackValve");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOutcheckable->setText("AlarmOut");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignalcheckable->setText("StopSignal");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignalcheckable->setText("AlarmSignal");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmoutcheckable->setText("YellowAlarmout");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBafflecheckable->setText("Baffle");
		((Ui::QtPLCDialogClass*)ui)->label_2->setText("Analog Output");

		//下料旋转
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
		((Ui::QtPLCDialogClass*)ui)->pB_cmdSwing->setText("RotateOnce");
		((Ui::QtPLCDialogClass*)ui)->label_62->setText("Amount Set");

		//称重打印
		((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedShake->setText("Shake");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedshakestop->setText("Stop");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedshakelevel->setText("Horizontal");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedhome->setText("Home");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedFive->setText("Five");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdFeedShakefive->setText("Amount");
		//((Ui::QtPLCDialogClass*)ui)->pB_cmdScaleRead->setText("ScaleRead");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdScaleTire->setText("ScaleTire");
		((Ui::QtPLCDialogClass*)ui)->pB_cmdScaleCalibExt->setText("ScaleCalibExt");
		//((Ui::QtPLCDialogClass*)ui)->pB_cmdScaleSetStable->setText("ScaleSetStable");


		//系统参数
		((Ui::QtPLCDialogClass*)ui)->label_26->setText("Stop Pos(mm)");
		((Ui::QtPLCDialogClass*)ui)->label_30->setText("Swing Dis");
		((Ui::QtPLCDialogClass*)ui)->label_25->setText("Rec Cycle(s)");
		((Ui::QtPLCDialogClass*)ui)->label_32->setText("Delay(s)");
		((Ui::QtPLCDialogClass*)ui)->label_42->setText("Wait(s)");
		((Ui::QtPLCDialogClass*)ui)->label_31->setText("Stop Pos2(mm)");
		((Ui::QtPLCDialogClass*)ui)->label_4->setText("Overtime(s)");
		((Ui::QtPLCDialogClass*)ui)->label_5->setText("Return(s)");
		((Ui::QtPLCDialogClass*)ui)->label_41->setText("Read Delay(s)");
		((Ui::QtPLCDialogClass*)ui)->label_44->setText("Overrun Shutdown(s)");
		((Ui::QtPLCDialogClass*)ui)->pB_Read1->setText("Read");
		((Ui::QtPLCDialogClass*)ui)->pB_Write1->setText("Write");

		//运行参数
		((Ui::QtPLCDialogClass*)ui)->label_14->setText("Expected weight(g)");
		((Ui::QtPLCDialogClass*)ui)->label_13->setText("Upper Limit(g)");
		((Ui::QtPLCDialogClass*)ui)->label_12->setText("Lower Limit(g)");
		((Ui::QtPLCDialogClass*)ui)->label_53->setText("Overweight(g)");
		((Ui::QtPLCDialogClass*)ui)->label_54->setText("Ultra Light(g)");
		((Ui::QtPLCDialogClass*)ui)->label_52->setText("Number");
		((Ui::QtPLCDialogClass*)ui)->label_57->setText("Cutting Speed");
		((Ui::QtPLCDialogClass*)ui)->label_58->setText("Test Sub.(s)");
		((Ui::QtPLCDialogClass*)ui)->label_56->setText("Interval Time");

		//运行状态
		((Ui::QtPLCDialogClass*)ui)->label_21->setText("State Mac.");
		((Ui::QtPLCDialogClass*)ui)->label_19->setText("error code");
		((Ui::QtPLCDialogClass*)ui)->label_22->setText("RelMovDistance");
		((Ui::QtPLCDialogClass*)ui)->label_24->setText("State Mac.");
		((Ui::QtPLCDialogClass*)ui)->label_27->setText("error code");
		((Ui::QtPLCDialogClass*)ui)->label_28->setText("RelMovDistance");
		((Ui::QtPLCDialogClass*)ui)->label_20->setText("Alarm status");
		((Ui::QtPLCDialogClass*)ui)->label_33->setText("Actual Interval Time(s)");

		//用户管理
		((Ui::QtPLCDialogClass*)ui)->label_68->setText("Permission name");
		((Ui::QtPLCDialogClass*)ui)->label_69->setText("Permission description");
		((Ui::QtPLCDialogClass*)ui)->label_65->setText("Add user name");
		((Ui::QtPLCDialogClass*)ui)->label_66->setText("Set user permissions");
		((Ui::QtPLCDialogClass*)ui)->label_67->setText("Set password");
		((Ui::QtPLCDialogClass*)ui)->pB_AddUser->setText("AddUser");
		((Ui::QtPLCDialogClass*)ui)->pB_Users_Delete->setText("Users Delete");

		//杂项
		((Ui::QtPLCDialogClass*)ui)->gB_User->setTitle("Custom user");
		((Ui::QtPLCDialogClass*)ui)->groupBox_4->setTitle(tr("Feeding motor"));
		((Ui::QtPLCDialogClass*)ui)->groupBox_6->setTitle("Rotating motor");
		((Ui::QtPLCDialogClass*)ui)->groupBox_2->setTitle("Feed");
		((Ui::QtPLCDialogClass*)ui)->groupBox_3->setTitle("Rotate");
		((Ui::QtPLCDialogClass*)ui)->groupBox_9->setTitle("Cutting");
		((Ui::QtPLCDialogClass*)ui)->groupBox_5->setTitle("Weighing settings");

	}

}


//unsigned char		cmdPrintStart;					//启动打印,1:执行，自动复位
//unsigned char		cmdPrintStartE;					//启动英文打印，1:执行，自动复位
void QtPLCDialogClass::on_pB_cmdCapClean_clicked()
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdCapClean = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAlogtest_clicked()//模拟量输出测试,1:执行，自动复位
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAlogtest = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdFeedShake_clicked()//下料摇摆
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdFeedShake = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdFeedshakestop_clicked()//下料摇摆停止
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdFeedshakestop = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdFeedshakelevel_clicked()//下料摇摆水平
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdFeedshakelevel = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdFeedhome_clicked()//下料寻参
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdFeedhome = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdFeedFive_clicked()//胶囊落料五粒
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdFeedFive = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdFeedShakefive_clicked()//片剂落料五粒
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdFeedShakefive = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
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
//output
void QtPLCDialogClass::on_pb_cmdRejectcheckable_toggled(bool checked)//
{
#ifdef TCPIP
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.Reject = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
#endif
#ifdef MODBUSTCP
	m_socket->Write_modbus_tcp_Coils(QString::number(checked), 92, 1);
#endif
}
void QtPLCDialogClass::on_pb_cmdChannelSwithcheckable_toggled(bool checked)//
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.ChannelSwith = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pb_cmdVaccumcheckable_toggled(bool checked)//
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.Vaccum = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pb_cmdCapGetcheckable_toggled(bool checked)//
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.CapGet = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pb_cmdCapGetValvecheckable_toggled(bool checked)//
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.CapGetValve = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pb_cmdCapBackValvecheckable_toggled(bool checked)//
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.CapBackValve = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pb_cmdAlarmOutcheckable_toggled(bool checked)//
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.AlarmOut = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pb_cmdStopSignalcheckable_toggled(bool checked)//
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.StopSignal = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pb_cmdAlarmSignalcheckable_toggled(bool checked)//
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.AlarmSignal = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pb_cmdYellowAlarmoutcheckable_toggled(bool checked)//
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.YellowAlarmout = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pb_cmdBafflecheckable_toggled(bool checked)//
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.Baffle = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
}

void QtPLCDialogClass::on_tabWidget_currentChanged(int index)
{
}
void QtPLCDialogClass::on_tabWidget_PLC_currentChanged(int index)
{
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
		if (lg == 0)emit emit showWindowOut(QString::fromLocal8Bit("请先选择用户\n然后进行删除！"));
		if (lg == 1)emit emit showWindowOut(QString::fromLocal8Bit("Please select user first\nthen delete it！"));
		return;
	}
	else if (m_SelectedName == "Admin")
	{
		if (lg == 0)emit emit showWindowOut(QString::fromLocal8Bit("管理员账户\n不可删除！"));
		if (lg == 1)emit emit showWindowOut(QString::fromLocal8Bit("Admin account\n can't be deleted!"));
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
				//emit emit showWindowOut(QString::fromLocal8Bit("恭喜\n") + m_SelectedName + QString::fromLocal8Bit("\n删除成功!"));
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
				//emit emit showWindowOut(QString::fromLocal8Bit("恭喜\n") + m_SelectedName + QString::fromLocal8Bit("\n删除成功!"));
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
					if (lg == 1)showMsgBox("illegal change", "Admin account can't be changed!", "I know", "");
					return;
				}
				if (lg == 0)
				{
					if (QMessageBox::Yes == showMsgBox("冲突确认", "用户名已存在(大小写不敏感)，是否更新？", "确认", "取消"))
					{
						Dir.setValue("USER_" + ((Ui::QtPLCDialogClass*)ui)->lE_SetUserName->text() + "/Password", ((Ui::QtPLCDialogClass*)ui)->lE_SetUserSecretNum->text());//写当前模板
						Dir.setValue("USER_" + ((Ui::QtPLCDialogClass*)ui)->lE_SetUserName->text() + "/Level", QString::number(((Ui::QtPLCDialogClass*)ui)->cB_SetUserPermission->currentIndex()));//写当前模板
						emit emit showWindowOut(QString::fromLocal8Bit("恭喜\n用户更新成功!"));
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
						emit emit showWindowOut(QString::fromLocal8Bit("Congratulations\n password is update!"));
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
	if (lg == 0)emit emit showWindowOut(QString::fromLocal8Bit("恭喜\n新建用户成功!"));
	if (lg == 1)emit emit showWindowOut(QString::fromLocal8Bit("Congratulations\ncreat new user account success!"));
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
	showMsgBox("提示", "PLC Unconnected!", "我知道了", "");
}
void QtPLCDialogClass::OnConnectingState()
{
	emit showWindowOut(QString::fromLocal8Bit("Connecting"));
}
void QtPLCDialogClass::OnConnectedState()
{
	emit showWindowOut(QString::fromLocal8Bit("Connected!"));
	//showMsgBox("恭喜", "Connected!", "我知道了", "");
}
void QtPLCDialogClass::OnClosingState()
{
	showMsgBox("提示", "PLC Closing!", "我知道了", "");
}

