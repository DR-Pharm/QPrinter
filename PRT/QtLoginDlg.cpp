#include "QtLoginDlg.h"
extern QString g_QSUserName;
extern int g_IUserLevel;
//extern QString AppPath;
//extern QString style1;
//extern QString style2;
#include <QButtonGroup>
#include <QBitmap>
#include <QPainter>
#include <QMovie>
QtLoginDlg::QtLoginDlg(QDialog* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowIcon(QIcon("./dr.ico"));//文件copy到了exe所在目录

	AppPath = qApp->applicationDirPath();//exe所在目录

	this->resize(QSize(421, 690));
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	this->setWindowOpacity(0.95);//透明度
	this->setWindowModality(Qt::ApplicationModal);
	ui.label->setPixmap(QPixmap(AppPath + "/ico/user.ico"));
	ui.label->setScaledContents(true);
	ui.label_2->setPixmap(QPixmap(AppPath + "/ico/sec.ico"));
	ui.label_2->setScaledContents(true);
	ui.pB_Exit->setStyleSheet("color: rgb(0, 170, 127);font-size:20pt");
	ui.pB_Login->setStyleSheet("font-size:20pt");
	// 	QMovie *movie = new QMovie("./ico/capsule.gif");
	// 	movie->setScaledSize(QSize(50, 60));
	// 	ui.label_4->setMovie(movie);
	// 	movie->start();
	connect(ui.pB_more, &QPushButton::clicked, [=]() {
		if (ui.pB_more->text()==QString::fromLocal8Bit("︾"))
		{
			ui.pB_more->setText(QString::fromLocal8Bit("︽"));
		this->resize(QSize(421, 760));
		//设置窗口圆角
		QBitmap bmp(this->size());
		bmp.fill();
		QPainter p(&bmp);
		p.setPen(Qt::NoPen);
		p.setBrush(Qt::black);
		p.drawRoundedRect(bmp.rect(), 5, 5);
		setMask(bmp);
		//👆👆👆
		ui.cB_style->setVisible(true);
	ui.cB_turnOn->setVisible(true);
	ui.cB_turnOff->setVisible(true);
		}
		else 
		{
			ui.pB_more->setText(QString::fromLocal8Bit("︾"));
			this->resize(QSize(421, 690));
			//设置窗口圆角
			QBitmap bmp(this->size());
			bmp.fill();
			QPainter p(&bmp);
			p.setPen(Qt::NoPen);
			p.setBrush(Qt::black);
			p.drawRoundedRect(bmp.rect(), 5, 5);
			setMask(bmp);
			//👆👆👆
			ui.cB_style->setVisible(false);
			ui.cB_turnOn->setVisible(false);
			ui.cB_turnOff->setVisible(false);
		}
		});
	ui.cB_style->setVisible(false);
	ui.cB_turnOn->setVisible(false);
	ui.cB_turnOff->setVisible(false);
	ui.pB_more->setVisible(false);
	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	QString text = configIniRead.value("ProgramSetting/Style", "").toString();	
	lg = configIniRead.value("Language/currentLanguage", "").toInt();
	if (lg == 1)
	{
		ui.label_3->setFont(QFont("Times", 30, QFont::Black));
		ui.label_3->setText("Welcome");
		ui.lE_Password->setPlaceholderText("Password");
		ui.pB_Login->setText("Entry");
		ui.pB_Exit->setText("Quit");
	}
	if (text == "Default Style")
	{
		ui.cB_style->setCurrentIndex(0);
	}
	else if (text == "Iron Man")
	{
		ui.cB_style->setCurrentIndex(1);
	}
	else if (text == "zxc")
	{
		ui.cB_style->setCurrentIndex(2);
	}
	else if (text == "qdh")
	{
		ui.cB_style->setCurrentIndex(3);
	}
	connect(ui.cB_style, QOverload<const QString&>::of(&QComboBox::activated),
		[=](const QString& text) {
			QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
			if (text == QString::fromLocal8Bit("默认风格"))
			{
				configIniRead.setValue("ProgramSetting/Style", "Default Style");//写当前模板
			}
			else if (text == "Iron Man")
			{
				configIniRead.setValue("ProgramSetting/Style", "Iron Man");//写当前模板
			}
			else if (text == QString::fromLocal8Bit("大话西游"))
			{
				configIniRead.setValue("ProgramSetting/Style", "zxc");//写当前模板
			}
			else if (text == QString::fromLocal8Bit("千岛湖"))
			{
				configIniRead.setValue("ProgramSetting/Style", "qdh");//写当前模板
			}
		});
	QString key_turnOn = configIniRead.value("ProgramSetting/AutoRun", "").toString();
	if (key_turnOn=="1")
	{
		ui.cB_turnOn->setChecked(true);
	}
	else
	{
		ui.cB_turnOn->setChecked(false);
	}
	connect(ui.cB_turnOn, SIGNAL(toggled(bool)), this, SLOT(setAutoRun(bool)));
	QString key_turnOff = configIniRead.value("ProgramSetting/AutoClose", "").toString();
	if (key_turnOff == "1")
	{
		ui.cB_turnOff->setChecked(true);
	}
	else
	{
		ui.cB_turnOff->setChecked(false);
	}
	connect(ui.cB_turnOff, SIGNAL(toggled(bool)), this, SLOT(setAutoClose(bool)));
	//设置窗口圆角
	QBitmap bmp(this->size());
	bmp.fill();
	QPainter p(&bmp);
	p.setPen(Qt::NoPen);
	p.setBrush(Qt::black);
	p.drawRoundedRect(bmp.rect(), 5, 5);
	setMask(bmp);
	//👆👆👆
	char* configpath = new char[256];
	strcpy(configpath, (AppPath + "\\ModelFile\\ProgramSet.ini").toStdString().c_str());//c_str返回char*
	QVector<std::string> v_line;//存储相机序列号
	std::ifstream cin(configpath);//将文件路径放入标准流
	delete configpath;
	std::string filename;
	std::string line;
	int r_n = 0, ipos = 0;
	QStringList ls_user;
	if (cin) // 有该文件  
	{//确定ini文件中有多少相机配置文件，并将IP存入v_line
		while (getline(cin, line)) // line中不包括每行的换行符  
		{
			if (line.find("USER_") != std::string::npos)//std::string::npos指不存在
			{
				line.erase(0, 6);
				line.erase(line.length() - 1, 1);
				ls_user.push_back(line.c_str());
			}
		}
	}
	if (ls_user.size() != 0)
	{
		ui.cB_ListUser->addItems(ls_user);
	}
	ui.pB_Login->setEnabled(false);
	connect(ui.pB_Login, SIGNAL(clicked()), this, SLOT(onEnsure()));
	connect(ui.cB_ListUser, SIGNAL(currentTextChanged(QString)), this, SLOT(onUserListChange(QString)));
	connect(ui.lE_Password, SIGNAL(cursorPositionChanged(int, int)), this, SLOT(onLineeditChanged()));
	connect(ui.pB_Exit, &QPushButton::clicked, [=]() {
		if (ui.pB_Exit->text() == QString::fromLocal8Bit("退出")||ui.pB_Exit->text() == QString::fromLocal8Bit("Quit"))
		{
			close();
		}
		else
		{
			ui.lE_Password->clear();
		}});
	connect(ui.btn_Group, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),
		[=](QAbstractButton* button) {ui.lE_Password->setText(ui.lE_Password->text() + button->text()); });
	installEventFilter(this);
	ui.btn_Group->installEventFilter(this);
	ui.cB_ListUser->installEventFilter(this);
	ui.lE_Password->installEventFilter(this);
	ui.lE_Password->setFocus();
}
bool QtLoginDlg::eventFilter(QObject* obj, QEvent* event)
{
	QDialog* pDialog = qobject_cast<QDialog*>(obj);
	if (pDialog != NULL)
	{
		switch (event->type())
		{
		case QEvent::KeyPress:
		{
			QKeyEvent* pKeyEvent = static_cast<QKeyEvent*>(event);
			if (pKeyEvent->key() == Qt::Key_Escape)
			{
				return true;
			}
			if (pKeyEvent->key() == Qt::Key_Return || pKeyEvent->key() == Qt::Key_Enter)
			{
				onEnsure();
				return true;
			}
			if (pKeyEvent->key() == Qt::Key_Down)
			{
				int i = ui.cB_ListUser->count();
				int c = ui.cB_ListUser->currentIndex();
				ui.cB_ListUser->setCurrentIndex(c + 1 == i ? 0 : c + 1);
			}
			if (pKeyEvent->key() == Qt::Key_Up)
			{
				int i = ui.cB_ListUser->count();
				int c = ui.cB_ListUser->currentIndex();
				ui.cB_ListUser->setCurrentIndex(c - 1 < 0 ? i - 1 : c - 1);
			}
		}
		}
	}
	return QObject::eventFilter(obj, event);
}
QtLoginDlg::~QtLoginDlg()
{
	
}
void QtLoginDlg::onUserListChange(QString)
{
	ui.lE_Password->clear();
}
void QtLoginDlg::onLineeditChanged()
{
	int i = ui.lE_Password->text().length();
	if (i>0)
	{
		if (lg==0)
		{
			ui.pB_Exit->setText(QString::fromLocal8Bit("清空"));
		}
		else
		{
			ui.pB_Exit->setText(QString::fromLocal8Bit("Empty"));
		}
	}
	if (i == 0)
	{
		if (lg == 0)
		{
			ui.pB_Exit->setText(QString::fromLocal8Bit("退出"));
		}
		else
		{
			ui.pB_Exit->setText(QString::fromLocal8Bit("Quit"));
		}
		ui.pB_Login->setEnabled(false);
		ui.pB_Login->setStyleSheet("font-size:20pt");
	}
	else if (i == 1)
	{
		ui.pB_Login->setEnabled(false);
		ui.pB_Login->setStyleSheet("font-size:23pt");
	}
	else if (i == 2)
	{
		ui.pB_Login->setEnabled(false);
		ui.pB_Login->setStyleSheet("font-size:26pt");
	}
	else if (i == 3)
	{
		ui.pB_Login->setEnabled(false);
		ui.pB_Login->setStyleSheet("font-size:29pt");
	}
	else
	{
		ui.pB_Login->setEnabled(true);
		ui.pB_Login->setStyleSheet("background-color: rgba(0, 170, 0, 125);font-size:29pt");
	}
}
void QtLoginDlg::keyPressEvent(QKeyEvent* ev)
{
}
void QtLoginDlg::onEnsure()
{
	QString username = ui.cB_ListUser->currentText();
	username = "USER_" + username;
	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);//读取ini文件
	QString password = configIniRead.value(username + "/Password", -1).toString(); //密码
	if (password != ui.lE_Password->text())
	{
		static int i = 1;
		QString str;
		if (lg == 0) str = QString::fromLocal8Bit("密码输入错误") + QString::number(i++) + QString::fromLocal8Bit("次!");
		if (lg == 1) str = QString::fromLocal8Bit("Input password ") + QString::number(i++) + QString::fromLocal8Bit(" times!");
		if (i==100)
		{
			showMsgBox(QMessageBox::Question, "系统退出", "<img src = './ico/critical.png'/>\t密码连续101次输入错误，系统自动退出!", "我知道了", "");
			this->close();
		}
		levelOut = new WindowOut;
		if (lg == 0) levelOut->getString(QString::fromLocal8Bit("密码输入错误，请确认后重新输入！"), 2000);
		if (lg == 1) levelOut->getString(QString::fromLocal8Bit("Password is incorrect,please try again!"), 2000);
		levelOut->setWindowCount(0);
		levelOut->show();
		ui.lE_Password->setText("");
		//logAddLine("warning", QString::fromLocal8Bit(dest) + QString::fromLocal8Bit("登录成功"));
		return;
	}
	int userlevel = configIniRead.value(username + "/Level", -1).toInt();//用户等级
	g_QSUserName = username;
	g_IUserLevel = userlevel;
	this->close();
}
bool QtLoginDlg::copyDirectoryFiles(const QString& fromDir, const QString& toDir, bool coverFileIfExist)
{
	QDir sourceDir(fromDir);
	QDir targetDir(toDir);
	if (!targetDir.exists()) {    /**< 如果目标目录不存在,则进行创建 */
		if (!targetDir.mkpath(targetDir.absolutePath()))
		{
			return false;
		}
	}
	QFileInfoList fileInfoList = sourceDir.entryInfoList();
	foreach(QFileInfo fileInfo, fileInfoList) {
		if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
			continue;
		if (fileInfo.isDir()) {    /**< 当为目录时,递归的进行copy */
			if (!copyDirectoryFiles(fileInfo.filePath(),
				targetDir.filePath(fileInfo.fileName()),
				coverFileIfExist))
				return false;
		}
		else {            /**< 当允许覆盖操作时,将旧文件进行删除操作 */
			if (coverFileIfExist && targetDir.exists(fileInfo.fileName())) {
				targetDir.remove(fileInfo.fileName());
			}
			/// 进行文件copy
			if (!QFile::copy(fileInfo.filePath(),
				targetDir.filePath(fileInfo.fileName()))) {
				return false;
			}
		}
	}
	return true;
}
bool QtLoginDlg::deleteDir(const QString& path)//eg：deleteDir(AppPath + "/DefaultModel");//删除文件夹/目录功能
{
	if (path.isEmpty()) {
		return false;
	}
	QDir dir(path);
	if (!dir.exists()) {
		return true;
	}
	dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); //设置过滤
	QFileInfoList fileList = dir.entryInfoList(); // 获取所有的文件信息
	foreach(QFileInfo file, fileList) { //遍历文件信息
		if (file.isFile()) { // 是文件，删除
			file.dir().remove(file.fileName());
		}
		else { // 递归删除
			deleteDir(file.absoluteFilePath());
		}
	}
	return dir.rmpath(dir.absolutePath()); // 删除文件夹
}
void QtLoginDlg::setAutoRun(bool isAutoRun)
{
	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	if (isAutoRun)
	{
		configIniRead.setValue("ProgramSetting/AutoRun", 1);//写当前模板
		char *pathvar = getenv("CODERCOMPUTER");
		QString envStr = QString::fromLocal8Bit(pathvar);
		if (envStr != "coder")
		{ 
		copyDirectoryFiles(AppPath+"/startup", m_autoStartPath, true);
		}
	}
	else
	{
		configIniRead.setValue("ProgramSetting/AutoRun", 0);//写当前模板
		deleteDir(m_autoStartPath);
	}
}	
void QtLoginDlg::setAutoClose(bool isAutoClose)
{
	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	if (isAutoClose)
	{
		configIniRead.setValue("ProgramSetting/AutoClose", 1);//写当前模板
		//copyDirectoryFiles(AppPath + "/startup", autoStartPath, true);
	}
	else
	{
		configIniRead.setValue("ProgramSetting/AutoClose", 0);//写当前模板
		//deleteDir(autoStartPath);
	}
}
int QtLoginDlg::showMsgBox(QMessageBox::Icon icon, const char* titleStr, const char* contentStr, const char* button1Str, const char* button2Str)//全是中文
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
		msg.setWindowIcon(QIcon("./ico/dr.ico"));
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
		msg.setWindowIcon(QIcon("./ico/dr.ico"));
		return msg.exec();
	}
	//  QMessageBox::NoIcon
	//	QMessageBox::Question
	//	QMessageBox::Information
	//	QMessageBox::Warning
	//	QMessageBox::Critical
}

