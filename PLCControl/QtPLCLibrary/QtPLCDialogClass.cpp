#include "QtPLCDialogClass.h"
#include "ui_QtPLCDialogClass.h"
#include <QPropertyAnimation>
#include <QFont>
#include <QBitmap>
#include <QPainter>
#include "mypushbutton.h"
#include "Keyboard.h"

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
	initUser();
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

	MyPushButton * AlarmResetBtn = new MyPushButton(AppPath + "/ico/bjfwnt.png", AppPath + "/ico/bjfw.png", 347, 99);
	AlarmResetBtn->setParent(((Ui::QtPLCDialogClass*)ui)->frame_20);
	AlarmResetBtn->move(15, 120);
	connect(AlarmResetBtn, &MyPushButton::clicked, [=]() {
		on_pB_cmdAlarmReset_clicked(); });

	AlarmResetBtn = new MyPushButton(AppPath + "/ico/qkjnnt.png", AppPath + "/ico/qkjn.png", 347, 99);
	AlarmResetBtn->setParent(((Ui::QtPLCDialogClass*)ui)->frame_20);
	AlarmResetBtn->move(15, 230);
	connect(AlarmResetBtn, &MyPushButton::clicked, [=]() {
		on_pB_cmdCapClean_clicked(); });

	AlarmResetBtn = new MyPushButton(AppPath + "/ico/jsqlnt.png", AppPath + "/ico/jsql.png", 347, 99);
	AlarmResetBtn->setParent(((Ui::QtPLCDialogClass*)ui)->frame_20);
	AlarmResetBtn->move(15, 340);
	connect(AlarmResetBtn, &MyPushButton::clicked, [=]() {
		on_pB_cmdCounterZero_clicked(); });

	//AlarmResetBtn = new MyPushButton(AppPath + "/ico/jtnt.png", AppPath + "/ico/jt.png", 347, 99);
	AlarmResetBtn = new MyPushButton(AppPath + "/ico/dr_keyboard.ico", AppPath + "/ico/dr_keyboard.ico", 347, 99);
	AlarmResetBtn->setParent(((Ui::QtPLCDialogClass*)ui)->frame_20);
	AlarmResetBtn->move(15, 450);
	connect(AlarmResetBtn, &MyPushButton::clicked, [=]() {
		if (key == nullptr) key = new keyBoard(this);
		if (key->isVisible())
		{
			key->close();
		}
		else
		{
			key->show();
		}});

	//开始

	((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->setFixedSize(347, 200);
	((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->setStyleSheet("QPushButton{border:0px;}");
	ret = pix.load(AppPath + "/ico/start.png");
	((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->setIcon(pix);
	((Ui::QtPLCDialogClass*)ui)->pB_cmdStart->setIconSize(QSize(347, 200));
	//指示灯部分
	((Ui::QtPLCDialogClass*)ui)->lb_00->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));
	((Ui::QtPLCDialogClass*)ui)->lb_10->setPixmap(QPixmap(AppPath + "/ico/redLed.png"));

	btnTimer = new QTimer();
	connect(btnTimer, SIGNAL(timeout()), this, SLOT(startMovie()));

	dtCurve = new DataCurve();	
	connect(dtCurve, SIGNAL(rejected()), this, SLOT(dtClose()));
	connect(this, SIGNAL(TODATACURVE(int,float, float, float, QList<qreal>)), dtCurve, SLOT(dataReceived(int, float, float, float, QList<qreal>)));
	dtCurve->move(0, 0);
	//dtCurve->setFixedSize(QSize(860, 755));//1280 800

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
	QRegExp regx2("[0-9]+$");//正则表达式QRegExp,只允许输入中文、数字、字母、下划线以及空格,[\u4e00 - \u9fa5a - zA - Z0 - 9_] + $
	((Ui::QtPLCDialogClass*)ui)->lE_SetUserSecretNum->setValidator(new QRegExpValidator(regx2, this));
	((Ui::QtPLCDialogClass*)ui)->lE_SetUserSecretNum->setEnabled(false);
	((Ui::QtPLCDialogClass*)ui)->pB_AddUser->setEnabled(false);

	connect(((Ui::QtPLCDialogClass*)ui)->treeWidget_2, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(onTreeItemChanged(QTreeWidgetItem*)));

	updateCheckPermission(QString::fromLocal8Bit("管理员"));



}
void QtPLCDialogClass::initTableOfUserPermission()
{
	//QFont font;
	//font = ui.tabWidget_CameraVec->font();//左下角白框的字体——[SimSun,21]
	//font.setPointSize(21);
	QWidget* tab = new QWidget();//新建tab
	tab->setFont(font);//设置tab字体
	tab->setObjectName(QString::fromUtf8("tab_0"));//tab_23170685
	((Ui::QtPLCDialogClass*)ui)->tabWidget_Users->addTab(tab, QString::fromLocal8Bit("用户权限"));//将tab添加到左下角tabwidget boject name:tab_23170685 tttle:23170685
	QTableWidget* tableWidget = new QTableWidget(tab);//tab下面加tablewidget
	tableWidget->setObjectName(QString::fromLocal8Bit("tableWidget_permission"));//tableWidget_23170685
	tableWidget->setGeometry(QRect(9, 9, tab->height() - 50, tab->width() - 80));//设置widget尺寸 黑边是边界
	QStringList strlist;
	strlist << QString::fromLocal8Bit("权限名称") << QString::fromLocal8Bit("权限级别");
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
	tableWidget->setItem(currentcolumn, 0, new QTableWidgetItem(QString::fromLocal8Bit("管理员")));//0列设置
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
	tableWidget->setItem(currentcolumn, 0, new QTableWidgetItem(QString::fromLocal8Bit("工程师")));
	tableWidget->item(currentcolumn, 0)->setFlags(tableWidget->item(currentcolumn, 0)->flags() & (~Qt::ItemIsEditable));
	tableWidget->item(currentcolumn, 0)->setFlags(tableWidget->item(currentcolumn, 0)->flags() & (~Qt::ItemIsSelectable));
	tableWidget->setItem(currentcolumn, 1, new QTableWidgetItem(QString::number(1)));
	tableWidget->item(currentcolumn, 1)->setFlags(tableWidget->item(currentcolumn, 1)->flags() & (~Qt::ItemIsEditable));
	tableWidget->item(currentcolumn, 1)->setFlags(tableWidget->item(currentcolumn, 1)->flags() & (~Qt::ItemIsSelectable));
	currentcolumn = tableWidget->rowCount();
	tableWidget->insertRow(currentcolumn);
	tableWidget->setItem(currentcolumn, 0, new QTableWidgetItem(QString::fromLocal8Bit("操作员")));
	tableWidget->item(currentcolumn, 0)->setFlags(tableWidget->item(currentcolumn, 0)->flags() & (~Qt::ItemIsEditable));
	tableWidget->item(currentcolumn, 0)->setFlags(tableWidget->item(currentcolumn, 0)->flags() & (~Qt::ItemIsSelectable));
	tableWidget->setItem(currentcolumn, 1, new QTableWidgetItem(QString::number(2)));
	tableWidget->item(currentcolumn, 1)->setFlags(tableWidget->item(currentcolumn, 1)->flags() & (~Qt::ItemIsEditable));
	tableWidget->item(currentcolumn, 1)->setFlags(tableWidget->item(currentcolumn, 1)->flags() & (~Qt::ItemIsSelectable));
	currentcolumn = tableWidget->rowCount();
	tableWidget->insertRow(currentcolumn);
	tableWidget->setItem(currentcolumn, 0, new QTableWidgetItem(QString::fromLocal8Bit("代码人员")));
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
	group1->setText(0, QString::fromLocal8Bit("设备运行"));  //设置子项显示的文本
	group1->setCheckState(0, Qt::Checked); //设置子选项的显示格式和状态
	QTreeWidgetItem* group2 = new QTreeWidgetItem(checkPermissionGroup);
	group2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group2->setText(0, QString::fromLocal8Bit("设置"));
	group2->setCheckState(0, Qt::Checked);
	//设置蓝色group2->setBackground(0, QBrush(QColor("#0000FF")));
	//父亲项
	QTreeWidgetItem* group21 = new QTreeWidgetItem(group2);
	group21->setText(0, QString::fromLocal8Bit("系统监控"));
	group21->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group21->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group22 = new QTreeWidgetItem(group2);
	group22->setText(0, QString::fromLocal8Bit("系统参数"));
	group22->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group22->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group23 = new QTreeWidgetItem(group2);
	group23->setText(0, QString::fromLocal8Bit("运行参数"));
	group23->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group23->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group24 = new QTreeWidgetItem(group2);
	group24->setText(0, QString::fromLocal8Bit("运行状态"));
	group24->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group24->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group25 = new QTreeWidgetItem(group2);
	group25->setText(0, QString::fromLocal8Bit("用户管理"));
	group25->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group25->setCheckState(0, Qt::Checked);
	//孙子项1
	QTreeWidgetItem* group211 = new QTreeWidgetItem(group21);   //指定子项属于哪一个父项
	group211->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group211->setText(0, QString::fromLocal8Bit("输入输出"));
	group211->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group212 = new QTreeWidgetItem(group21);
	group212->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group212->setText(0, QString::fromLocal8Bit("下料旋转"));
	group212->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group213 = new QTreeWidgetItem(group21);
	group213->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group213->setText(0, QString::fromLocal8Bit("称重打印"));
	group213->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group2131 = new QTreeWidgetItem(group213);
	group2131->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group2131->setText(0, QString::fromLocal8Bit("称重设置"));
	group2131->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group2132 = new QTreeWidgetItem(group213);
	group2132->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group2132->setText(0, QString::fromLocal8Bit("打印设置"));
	group2132->setCheckState(0, Qt::Checked);
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
	group241->setText(0, QString::fromLocal8Bit("添加用户"));
	group241->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	group241->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* group242 = new QTreeWidgetItem(group24);
	group242->setText(0, QString::fromLocal8Bit("删除用户"));
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
	((Ui::QtPLCDialogClass*)ui)->tabWidget_Users->addTab(tab, QString::fromLocal8Bit("自定义用户"));//将tab添加到左下角tabwidget boject name:tab_23170685 tttle:23170685
	tableWidget->setObjectName(QString::fromLocal8Bit("tableWidget_username"));//tableWidget_23170685
	tableWidget->setGeometry(QRect(9, 9, tab->height() - 50, tab->width() - 80));//设置widget尺寸 黑边是边界
	QStringList strlist2;
	strlist2 << QString::fromLocal8Bit("用户名") << QString::fromLocal8Bit("权限级别");
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
	//QRegExp regx("[a-zA-Z0-9_]+$");//正则表达式QRegExp,只允许输入中文、数字、字母、下划线以及空格,[\u4e00 - \u9fa5a - zA - Z0 - 9_] + $
	QRegExp regx("[0-9]+$");
	((Ui::QtPLCDialogClass*)ui)->lE_SysOveride->setValidator(new QRegExpValidator(regx, this));
	QRegExp regx_2("[a-zA-Z0-9_]+$");
	((Ui::QtPLCDialogClass*)ui)->lE_BatchName->setValidator(new QRegExpValidator(regx_2, this));
	lb_dataNow = new QLabel(((Ui::QtPLCDialogClass*)ui)->frame);
	lb_dataNow->resize(140, 35);
	lb_dataNow->move(30, 16);
	lb_dataNow->setPixmap(QPixmap(AppPath + "/ico/fontImage/datanow.png"));
	lb_dataNow->setScaledContents(true);

	((Ui::QtPLCDialogClass*)ui)->label_15->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_15.png"));
	((Ui::QtPLCDialogClass*)ui)->label_15->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_18->setPixmap(QPixmap(AppPath + "/ico/fontImage/label_18.png"));
	((Ui::QtPLCDialogClass*)ui)->label_18->setScaledContents(true);
	((Ui::QtPLCDialogClass*)ui)->label_79->setPixmap(QPixmap(AppPath + "/ico/fontImage/dqzh.png"));
	((Ui::QtPLCDialogClass*)ui)->label_79->setScaledContents(true);
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

	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	QString text1 = configIniRead.value("DistanceSetting/AxisFeedRelMovDistance", "").toString();
	QString text2 = configIniRead.value("DistanceSetting/AxisSwingRelMovDistance", "").toString();
	((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedRelMovDistance->setText(text1);	//下料电机相对运动距离，单位unit
	((Ui::QtPLCDialogClass*)ui)->lE_AxisSwingRelMovDistance->setText(text2);//旋转电机相对运动距离，单位unit
}

void QtPLCDialogClass::inittabicon()
{
	((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setIconSize(QSize(132, 33));
	((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(0, QIcon(AppPath + "/ico/fontImage/xtjk.png"));
	((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(1, QIcon(AppPath + "/ico/fontImage/xtcs.png"));
	((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(2, QIcon(AppPath + "/ico/fontImage/yxcs.png"));
	((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(3, QIcon(AppPath + "/ico/fontImage/yxzt.png"));
	((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->setTabIcon(4, QIcon(AppPath + "/ico/fontImage/yhgl.png"));

	((Ui::QtPLCDialogClass*)ui)->tabWidget->setIconSize(QSize(132, 33));
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
		((Ui::QtPLCDialogClass*)ui)->tabWidget_PLC->removeTab(4);
	}
	else if (g_IUserLevel == 2)
	{
		((Ui::QtPLCDialogClass*)ui)->pB_SetUp->setEnabled(false);
	}
}
#pragma endregion

#pragma region socket
void QtPLCDialogClass::SetSocket(QtSocket_Class *sc)
{
	m_socket = sc;
	bool b = connect(m_socket, SIGNAL(signal_FROMPLC(void*)), this, SLOT(getPLCData(void*)));
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
	tmp.ActData.TireMode = m_data->ActData.TireMode;				//0:每组去皮重,1:每次称重去皮重	 new11
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

	memset(tmp.ActData.BatchName, '\0', sizeof(tmp.ActData.BatchName));
	QString str = ((Ui::QtPLCDialogClass*)ui)->lE_BatchName->text();
	QByteArray ba = str.toLatin1();
	char *c = ba.data();
	strcpy(tmp.ActData.BatchName, c);

	return tmp;
}
void QtPLCDialogClass::getPLCData(void* data)
{
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
	if (!((Ui::QtPLCDialogClass*)ui)->lE_FeedOveride->hasFocus())//每组测试胶囊数量
	{
		((Ui::QtPLCDialogClass*)ui)->lE_FeedOveride->setText(QString::number(m_data->ActData.FeedOveride));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->hasFocus())////测试间隔时间,单位s
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->setText(QString::number(m_data->ActData.TestInterval));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_BatchName->hasFocus())//BatchName[40];			//批号字符串
	{
		((Ui::QtPLCDialogClass*)ui)->lE_BatchName->setText(QString(QLatin1String(m_data->ActData.BatchName)));//Cause kinco has a bug when input this parameter,but use PC to input,we do not have this bug,so don't need to change.
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_GroupNo->hasFocus())//GroupNo;				//当前组号
	{
		((Ui::QtPLCDialogClass*)ui)->lE_GroupNo->setText(QString::number(m_data->ActData.GroupNo));
	}

	if (!((Ui::QtPLCDialogClass*)ui)->cB_Feedmode->hasFocus())//0:每组去皮重,1:每次称重去皮重
	{
		((Ui::QtPLCDialogClass*)ui)->cB_Feedmode->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->cB_Feedmode->setCurrentIndex(m_data->ActData.Feedmode);
		((Ui::QtPLCDialogClass*)ui)->cB_Feedmode->blockSignals(false);
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
	((Ui::QtPLCDialogClass*)ui)->lE_Weight->setText(QString::number(m_data->Status.Weight, 'f', 3));//本次重量
	((Ui::QtPLCDialogClass*)ui)->lE_ScaleResult->setText(QString::number(m_data->Status.ScaleResult, 'f', 3));//天平当前读数，单位g
	((Ui::QtPLCDialogClass*)ui)->cB_ScaleStableState->setCurrentIndex(m_data->Status.ScaleStableState);//天平当前稳定状态,0:非常稳定,1:稳定,2:不稳定,3:非常不稳定

	//Group Data

	int i = m_data->Status.GroupIndex;
	int j = data_One.size();
	//float k = m_data->Status.CapDataDisp.GroupMax;
	//float l = m_data->Status.CapDataDisp.GroupMin;
	if (m_data->Status.GroupIndex==0)
	{
		data_One.clear(); 
		dataToDraw.clear();
	}
	if (m_data->Status.GroupIndex == 1)
	{
		m_fMax = m_data->Status.Weight;
		m_fMin = m_data->Status.Weight;
	}
	if ((m_data->Status.GroupIndex > 0) && (i-1 == j))//有数据进来
	{
		if (m_data->Status.Weight > 0)
		{
			data_One << m_data->Status.Weight;
			dataToDraw << m_data->Status.Weight;//for draw picture CLASS

			if (m_fMax< m_data->Status.Weight)
			{
				m_fMax = m_data->Status.Weight;
			}
			if (m_fMin > m_data->Status.Weight)
			{
				m_fMin = m_data->Status.Weight;
			}
			emit TODATACURVE(i, m_data->Status.Weight,m_fMax, m_fMin, data_One);
		}
	}
	if (m_data->Status.Finished==1)
	{
		m_fMax = 0;
		m_fMin = 0;
		if (dataToDraw.size()>0)
		{
			/*if (0)
			{
				emit TODRAWPICTURE(dataToDraw, 0);//MODE 0:one curve,1:one dataAverage,2:two curve,3:two dataAverage
			}
			else if (1)
			{
				emit TODRAWPICTURE(dataToDraw, 1);
			}
			else if (2)
			{
				emit TODRAWPICTURE(dataToDraw, 2);
			}
			else if (3)*/
			{
				emit TODRAWPICTURE(dataToDraw, 2);
			}
			dataToDraw.clear();
		}
	}
	((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedStep->setText(QString::number(m_data->Status.AxisFeedStep));			//下料电机状态机步骤
	((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedErrorNo->setText(QString::number(m_data->Status.AxisFeedErrorNo));		//下料电机错误代码
	//((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedRelMovDistance->setText(QString::number(m_data->Status.AxisFeedRelMovDistance));	//下料电机相对运动距离，单位unit
	((Ui::QtPLCDialogClass*)ui)->lE_AxisSwingStep->setText(QString::number(m_data->Status.AxisSwingStep));			//旋转电机状态机步骤
	((Ui::QtPLCDialogClass*)ui)->lE_AxisSwingErrorNo->setText(QString::number(m_data->Status.AxisSwingErrorNo));		//旋转电机错误代码
	//((Ui::QtPLCDialogClass*)ui)->lE_AxisSwingRelMovDistance->setText(QString::number(m_data->Status.AxisSwingRelMovDistance));//旋转电机相对运动距离，单位unit
	((Ui::QtPLCDialogClass*)ui)->lE_MachineStep->setText(QString::number(m_data->Status.MachineStep));			//系统运行状态机步骤
	((Ui::QtPLCDialogClass*)ui)->lE_TimeInterval->setText(QString::number(m_data->Status.TimeInterval, 'f', 2));			//测量实际间隔时间
	((Ui::QtPLCDialogClass*)ui)->lE_AlarmStatus->setText(QString::number(m_data->Status.AlarmStatus));
	char *str1 = (char*)(m_data->Status.Alarm);
	((Ui::QtPLCDialogClass*)ui)->lE_Alarm16->setText(QString(QLatin1String(str1)));
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
		((Ui::QtPLCDialogClass*)ui)->lE_CapPickInterval->setText(QString::number(m_data->Machine_Para.CapPickInterval, 'f', 2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_CapBackInterval->setText(QString::number(m_data->Machine_Para.CapBackInterval, 'f', 2));
	}

	if (!((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TireDelay->setText(QString::number(m_data->Machine_Para.TireDelay, 'f', 2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_ReadDelay->setText(QString::number(m_data->Machine_Para.ReadDelay, 'f', 2));
	}
	if (!((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->hasFocus())
	{
		((Ui::QtPLCDialogClass*)ui)->lE_TireWaitTime->setText(QString::number(m_data->Machine_Para.TireWaitTime, 'f', 2));
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
		((Ui::QtPLCDialogClass*)ui)->pb_cmdReject->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdReject->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdReject->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdReject->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdReject->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdReject->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdReject->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdReject->blockSignals(false);
	}
	if (m_data->Outputs.ChannelSwith)	//胶囊通道切换
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwith->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwith->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwith->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwith->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwith->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwith->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwith->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdChannelSwith->blockSignals(false);
	}
	if (m_data->Outputs.Vaccum)//真空发生器
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccum->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccum->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccum->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccum->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccum->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccum->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccum->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdVaccum->blockSignals(false);
	}
	if (m_data->Outputs.CapGet)//取料电磁铁
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGet->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGet->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGet->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGet->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGet->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGet->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGet->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGet->blockSignals(false);
	}
	if (m_data->Outputs.CapGetValve)//取料电磁阀
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValve->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValve->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValve->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValve->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValve->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValve->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValve->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapGetValve->blockSignals(false);
	}
	if (m_data->Outputs.CapBackValve)//回料电磁阀
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValve->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValve->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValve->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValve->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValve->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValve->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValve->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdCapBackValve->blockSignals(false);
	}
	if (m_data->Outputs.AlarmOut)//报警蜂鸣器
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOut->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOut->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOut->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOut->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOut->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOut->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOut->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmOut->blockSignals(false);
	}
	if (m_data->Outputs.StopSignal)//停机信号
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignal->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignal->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignal->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignal->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignal->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignal->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignal->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdStopSignal->blockSignals(false);
	}
	if (m_data->Outputs.AlarmSignal)//报警输出
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignal->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignal->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignal->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignal->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignal->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignal->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignal->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdAlarmSignal->blockSignals(false);
	}
	if (m_data->Outputs.YellowAlarmout)//黄灯报警
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmout->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmout->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmout->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmout->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmout->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmout->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmout->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdYellowAlarmout->blockSignals(false);
	}
	if (m_data->Outputs.Baffle)//挡板
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBaffle->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBaffle->setChecked(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBaffle->setStyleSheet("font: bold;background: rgb(0,255,0);font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBaffle->blockSignals(false);
	}
	else
	{
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBaffle->blockSignals(true);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBaffle->setChecked(false);
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBaffle->setStyleSheet("font: bold;font-size:20pt");
		((Ui::QtPLCDialogClass*)ui)->pb_cmdBaffle->blockSignals(false);
	}

#pragma endregion
}//PC显示数据
#pragma endregion

#pragma region popup window

void QtPLCDialogClass::initDlg()
{

}

void QtPLCDialogClass::setWindowMinimized()
{
	((Ui::QtPLCDialogClass*)ui)->pB_dtDlg->setChecked(false);
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
void QtPLCDialogClass::showWindowOut(QString str)
{
	levelOut = new WindowOut(this);
	levelOut->setWindowCount(0);
	levelOut->getString(str, 2000);
	levelOut->show();
}
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

	showWindowOut(QString::fromLocal8Bit("运行速度\n已更改!"));

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

	showWindowOut(QString::fromLocal8Bit("超重重量\n已更改!"));
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

	showWindowOut(QString::fromLocal8Bit("超轻重量\n已更改!"));
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

	showWindowOut(QString::fromLocal8Bit("内控上限\n已更改!"));
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

	showWindowOut(QString::fromLocal8Bit("内控下限\n已更改!"));
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

	showWindowOut(QString::fromLocal8Bit("期望重量\n已更改!"));
}
void QtPLCDialogClass::on_cB_TireMode_currentIndexChanged(int index)//0:每组去皮重,1:每次称重去皮重
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.ActData.TireMode = index;
	m_socket->Communicate_PLC(&typ, nullptr);
	showWindowOut(QString::fromLocal8Bit("去皮方式\n已更改!"));
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

	showWindowOut(QString::fromLocal8Bit("每组检测数\n已更改!"));
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
	typ.ActData.GroupSet = ((Ui::QtPLCDialogClass*)ui)->lE_FeedOveride->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);
	((Ui::QtPLCDialogClass*)ui)->lE_FeedOveride->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_FeedOveride->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_FeedOveride->blockSignals(false);

	showWindowOut(QString::fromLocal8Bit("下料速度\n已更改!"));
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
	typ.ActData.TestInterval = ((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->text().toInt();
	m_socket->Communicate_PLC(&typ, nullptr);
	((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->blockSignals(true);
	((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->clearFocus();
	((Ui::QtPLCDialogClass*)ui)->lE_TestInterval->blockSignals(false);

	showWindowOut(QString::fromLocal8Bit("组间隔\n已更改!"));
}
void QtPLCDialogClass::on_lE_BatchName_editingFinished()//批号字符串
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

	showWindowOut(QString::fromLocal8Bit("生产批号\n已更改!"));
}
void QtPLCDialogClass::on_cB_Feedmode_currentIndexChanged(int index)//0:每组去皮重,1:每次称重去皮重
{
	DataFromPC_typ typ;
	typ = getPCRunData();
	typ.Telegram_typ = 4;
	typ.ActData.Feedmode = index;
	m_socket->Communicate_PLC(&typ, nullptr);
	showWindowOut(QString::fromLocal8Bit("去皮方式\n已更改!"));
}
void QtPLCDialogClass::on_lE_AxisFeedRelMovDistance_editingFinished()
{
	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	int i1 = configIniRead.value("DistanceSetting/AxisFeedRelMovDistance", 0).toInt();
	if (((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedRelMovDistance->text()!=i1)
	{
		configIniRead.setValue("DistanceSetting/AxisFeedRelMovDistance", ((Ui::QtPLCDialogClass*)ui)->lE_AxisFeedRelMovDistance->text());//写当前模板
		showWindowOut(QString::fromLocal8Bit("下料电机\n相对运动距离\n已更改!"));
	}
}
void QtPLCDialogClass::on_lE_AxisSwingRelMovDistance_editingFinished()
{
	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	int i2 = configIniRead.value("DistanceSetting/AxisSwingRelMovDistance", 0).toInt();
	if (((Ui::QtPLCDialogClass*)ui)->lE_AxisSwingRelMovDistance->text() != i2)
	{
		configIniRead.setValue("DistanceSetting/AxisSwingRelMovDistance", ((Ui::QtPLCDialogClass*)ui)->lE_AxisSwingRelMovDistance->text());//写当前模板

		showWindowOut(QString::fromLocal8Bit("旋转电机\n相对运动距离\n已更改!"));
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

	showWindowOut(QString::fromLocal8Bit("停止位置1\n已更改!"));
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

	showWindowOut(QString::fromLocal8Bit("停止位置2\n已更改!"));
}
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

	showWindowOut(QString::fromLocal8Bit("下料超时时间\n已更改!"));
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

	showWindowOut(QString::fromLocal8Bit("自动取料周期\n已更改!"));
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

	showWindowOut(QString::fromLocal8Bit("成品返还周期\n已更改!"));
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

	showWindowOut(QString::fromLocal8Bit("去皮延迟启动时间\n已更改!"));
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

	showWindowOut(QString::fromLocal8Bit("读数延迟启动时间\n已更改!"));
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

	showWindowOut(QString::fromLocal8Bit("去皮等待时间\n已更改!"));
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

	showWindowOut(QString::fromLocal8Bit("连续超限停机数\n已更改!"));
}
#pragma endregion

#pragma region ui cmd slots
//DateTimeStructTyp		DateTimeSet;		//设定日期时间目标
//unsigned char		cmdChangeDT;					//修改日期时间,1:执行，自动复位
void QtPLCDialogClass::on_pB_Read1_clicked()//读取1
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.enable = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
	showWindowOut(QString::fromLocal8Bit("PLC默认参数\n已读取!"));
}
void QtPLCDialogClass::on_pB_Read2_clicked()//读取2
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.enable = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
	showWindowOut(QString::fromLocal8Bit("PLC默认参数\n已读取!"));
}
void QtPLCDialogClass::on_pB_Write1_clicked()//写入1
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.enable = 2;
	m_socket->Communicate_PLC(&typ, nullptr);
	showWindowOut(QString::fromLocal8Bit("PLC默认参数\n已保存!"));
}
void QtPLCDialogClass::on_pB_Write2_clicked()//写入2
{
	DataFromPC_typ typ;
	typ = getPCParaData();
	typ.Telegram_typ = 2;
	typ.Machine_Para.enable = 2;
	m_socket->Communicate_PLC(&typ, nullptr);
	showWindowOut(QString::fromLocal8Bit("PLC默认参数\n已保存!"));
}
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
//void QtPLCDialogClass::on_cB_paraScaleSetStable_currentIndexChanged(int index)//稳定状态设定目标，0:非常稳定,1:稳定,2:不稳定,3:非常不稳定
//{
//	DataFromPC_typ typ;
//	typ.Telegram_typ = 1;
//	typ.Machine_Cmd.cmdScaleSetStable = index;
//	m_socket->Communicate_PLC(&typ, nullptr);
//}
void QtPLCDialogClass::on_pB_cmdScaleCalibExt_clicked()//秤外部校正,1:执行，自动复位
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdScaleCalibExt = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisFeedJogPos_pressed()//下料正转点动，1:执行，0:停止
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisFeedJogPos = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisFeedJogPos_released()//下料正转点动，1:执行，0:停止 
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisFeedJogPos = 0;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisFeedJogNeg_pressed()//下料反转点动，1:执行，0:停止
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisFeedJogNeg = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisFeedJogNeg_released()//下料反转点动，1:执行，0:停止
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisFeedJogNeg = 0;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisFeedRelMov_clicked()//下料相对运动启动，1:执行，自动复位
{
	DataFromPC_typ typ;
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
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisFeedPosMov = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisFeedStopMov_clicked()//下料停止运动，1:执行，自动复位
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisFeedStopMov = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisSwingJogPos_pressed()//旋转正转点动，1:执行，0:停止
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisSwingJogPos = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisSwingJogPos_released()//旋转正转点动，1:执行，0:停止
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisSwingJogPos = 0;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisSwingJogNeg_pressed()//旋转反转点动，1:执行，0:停止
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisSwingJogNeg = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisSwingJogNeg_released()//旋转反转点动，1:执行，0:停止
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdAxisSwingJogNeg = 0;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdAxisSwingRelMov_clicked()//旋转相对运动启动，1:执行，自动复位
{
	DataFromPC_typ typ;
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
void QtPLCDialogClass::on_pB_showPrt_toggled(bool checked)//
{
	emit SHOWPRT(checked);
}
void QtPLCDialogClass::on_pB_cmdStart_toggled(bool checked)//启动 停止
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	if (checked)
	{
		data_One.clear();

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
		if (g_IUserLevel!=2)
		{
			((Ui::QtPLCDialogClass*)ui)->pB_SetUp->setEnabled(true);
		}
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
	typ.Machine_Cmd.cmdAlogtest = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdFeedShake_clicked()//下料摇摆
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdFeedShake = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdFeedshakestop_clicked()//下料摇摆停止
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdFeedshakestop = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdFeedshakelevel_clicked()//下料摇摆水平
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdFeedshakelevel = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdFeedhome_clicked()//下料寻参
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdFeedhome = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdFeedFive_clicked()//胶囊落料五粒
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdFeedFive = 1;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pB_cmdFeedShakefive_clicked()//片剂落料五粒
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.cmdFeedShakefive = 1;
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
		dtCurve->show();
		QPixmap pix;
		bool ret = pix.load(AppPath + "/ico/data1.png");
		((Ui::QtPLCDialogClass*)ui)->pB_dtDlg->setIcon(pix);
		((Ui::QtPLCDialogClass*)ui)->pB_dtDlg->setIconSize(QSize(170, 140));
	}
	else
	{
		dtCurve->hide();
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
//output
void QtPLCDialogClass::on_pb_cmdReject_toggled(bool checked)//
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.Reject = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pb_cmdChannelSwith_toggled(bool checked)//
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.ChannelSwith = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pb_cmdVaccum_toggled(bool checked)//
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.Vaccum = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pb_cmdCapGet_toggled(bool checked)//
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.CapGet = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pb_cmdCapGetValve_toggled(bool checked)//
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.CapGetValve = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pb_cmdCapBackValve_toggled(bool checked)//
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.CapBackValve = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pb_cmdAlarmOut_toggled(bool checked)//
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.AlarmOut = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pb_cmdStopSignal_toggled(bool checked)//
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.StopSignal = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pb_cmdAlarmSignal_toggled(bool checked)//
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.AlarmSignal = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pb_cmdYellowAlarmout_toggled(bool checked)//
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.YellowAlarmout = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
}
void QtPLCDialogClass::on_pb_cmdBaffle_toggled(bool checked)//
{
	DataFromPC_typ typ;
	typ.Telegram_typ = 1;
	typ.Machine_Cmd.Outputs.Baffle = checked;
	m_socket->Communicate_PLC(&typ, nullptr);
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
	if (checkPermissionGroup->text(0) == QString::fromLocal8Bit("管理员"))//0
	{
		while (*it) {
			if ((*it)->text(0) == QString::fromLocal8Bit("设备运行")
				|| (*it)->text(0) == QString::fromLocal8Bit("设置")
				|| (*it)->text(0) == QString::fromLocal8Bit("数据导出"))
			{
				(*it)->setCheckState(0, Qt::Checked);
			}
			if ((*it)->text(0) == QString::fromLocal8Bit("打印设置"))
			{
				(*it)->setCheckState(0, Qt::Unchecked);
			}
			++it;
		}
	}	
	if (checkPermissionGroup->text(0) == QString::fromLocal8Bit("代码人员"))//3
	{
		while (*it) {
			if ((*it)->text(0) == QString::fromLocal8Bit("设备运行")
				|| (*it)->text(0) == QString::fromLocal8Bit("设置")
				|| (*it)->text(0) == QString::fromLocal8Bit("数据导出"))
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
			if ((*it)->text(0) == QString::fromLocal8Bit("用户管理")
				|| (*it)->text(0) == QString::fromLocal8Bit("数据导出"))
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
			if ((*it)->text(0) == QString::fromLocal8Bit("设置")
				|| (*it)->text(0) == QString::fromLocal8Bit("数据导出"))
			{
				(*it)->setCheckState(0, Qt::Unchecked);
			}
			++it;
		}
	}
	//else if (checkPermissionGroup->text(0) == QString::fromLocal8Bit("代码人员"))//3
	//{
	//	while (*it) {
	//		if ((*it)->text(0) == QString::fromLocal8Bit("数据导出"))
	//		{
	//			(*it)->setCheckState(0, Qt::Checked);
	//		}
	//		if ((*it)->text(0) == QString::fromLocal8Bit("设备运行")
	//			|| (*it)->text(0) == QString::fromLocal8Bit("设置"))
	//		{
	//			(*it)->setCheckState(0, Qt::Unchecked);
	//		}
	//		++it;
	//	}
	//}
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
		showWindowOut(QString::fromLocal8Bit("请先选择用户\n然后进行删除！"));
		return;
	}
	else if (m_SelectedName == "Admin")
	{
		showWindowOut(QString::fromLocal8Bit("管理员账户\n不可删除！"));
		return;
	}
	else
	{
		if (QMessageBox::Yes == showMsgBox("删除确认", "确认删除该用户？", "确认", "取消"))
		{
			QSettings Dir(AppPath + "/ModelFile/ProgramSet.ini", QSettings::IniFormat);//所有结果文件
			QString path = AppPath + "/ModelFile/ProgramSet.ini";
			QString fullName = "USER_" + m_SelectedName;
			Dir.remove(fullName);
			showWindowOut(QString::fromLocal8Bit("恭喜\n") + m_SelectedName + QString::fromLocal8Bit("\n删除成功!"));
			initTableWidget();
			((Ui::QtPLCDialogClass*)ui)->tabWidget_Users->removeTab(1);
			m_SelectedName = "";
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
					showMsgBox("非法修改", "管理员账号不可修改！", "我知道了", "");
					return;
				}
				if (QMessageBox::Yes == showMsgBox("冲突确认", "用户名已存在(大小写不敏感)，是否更新？", "确认", "取消"))
				{
					Dir.setValue("USER_" + ((Ui::QtPLCDialogClass*)ui)->lE_SetUserName->text() + "/Password", ((Ui::QtPLCDialogClass*)ui)->lE_SetUserSecretNum->text());//写当前模板
					Dir.setValue("USER_" + ((Ui::QtPLCDialogClass*)ui)->lE_SetUserName->text() + "/Level", QString::number(((Ui::QtPLCDialogClass*)ui)->cB_SetUserPermission->currentIndex()));//写当前模板
					showWindowOut(QString::fromLocal8Bit("恭喜\n用户更新成功!"));
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
	Dir.setValue("USER_" + ((Ui::QtPLCDialogClass*)ui)->lE_SetUserName->text() + "/Password", ((Ui::QtPLCDialogClass*)ui)->lE_SetUserSecretNum->text());//写当前模板
	Dir.setValue("USER_" + ((Ui::QtPLCDialogClass*)ui)->lE_SetUserName->text() + "/Level", QString::number(((Ui::QtPLCDialogClass*)ui)->cB_SetUserPermission->currentIndex()));//写当前模板
	showWindowOut(QString::fromLocal8Bit("恭喜\n新建用户成功!"));
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

