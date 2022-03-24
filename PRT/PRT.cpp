#include "PRT.h"
#include <QMetaType> 
#include <QPdfWriter>
QString g_QSUserName = "hanlinzhineng_123_nengzhilinhan_321";
int g_IUserLevel;

PRT::PRT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QtLoginDlg* dlg = new QtLoginDlg((QDialog*)this);
	dlg->exec();
	if (g_QSUserName == "hanlinzhineng_123_nengzhilinhan_321")
	{
		exit(-1);
	}
	qRegisterMetaType<QVector<float>>("QVector<float>");
	qRegisterMetaType<QVector<float>>("QVector<float>&");//注册opencv函数，在槽函数中避免出错
	wt = new QWaiting();
	//initDog(); //remeber to note off
	setWindowFlags(Qt::FramelessWindowHint);//无边框  
	setWindowIcon(QIcon("./ico/dr.ico"));

	setAttribute(Qt::WA_AcceptTouchEvents, true);

	AppPath = qApp->applicationDirPath();//exe所在目录
	RWini = new QSettings(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	lg = configIniRead.value("Language/currentLanguage", "").toInt();
	initData();
	initPrinter();
	initUI();
	initPLC();

	ui.groupBox->raise();
	ui.groupBox->setVisible(false);

	installEventFilter(this);

	QString LogInfo;
	LogInfo.sprintf("%p", QThread::currentThread());
	qDebug() << "PRT" << "threadID : " << LogInfo;
}
PRT::~PRT()
{

}

#pragma region PLC
void PRT::initPLC()
{
	
	m_pPlclib = new QtPLCControl();//dll
	lib_PLCThread = new QThread();
	m_pPlclib->moveToThread(lib_PLCThread);
	lib_PLCThread->start();

	dlg = (QDialog *)(m_pPlclib->QtCreateDialog(1)); 

	bool b = connect(this, SIGNAL(STARTCONNECTPLC()), m_pPlclib, SLOT(ConnectPlc()));
	//emit STARTCONNECTPLC();
	b = connect(m_pPlclib, SIGNAL(SOCKETERROR()), this, SLOT(ErrorConnect()));
	b = connect(m_pPlclib, SIGNAL(signal_SUCCESSFULCONNECTED()), this, SLOT(SuccessConnect()));
	if (tm_ReConnect == nullptr)
	{
		tm_ReConnect = new QTimer();
	}
	b = connect(tm_ReConnect, SIGNAL(timeout()), this, SLOT(EmitReconnect()));
	tm_ReConnect->start(2000);

	//char *pathvar = getenv("CODERCOMPUTER");//自己电脑上创建的环境变量CODERCOMPUTER 值：coder
	//QString envStr = QString::fromLocal8Bit(pathvar);

	//if (envStr != "coder")//第二个参数：自己的电脑跟随软件关闭而关闭的功能无效
	{
		wt->setTxt(QString::fromLocal8Bit("正在连接PLC,请稍等..."));
		wt->show();
	}
	
	b = connect(dlg, SIGNAL(SHOWPRT(bool)), this, SLOT(showPrt(bool)));
	b = connect(dlg, SIGNAL(showWindowOut(QString)), this, SLOT(showWindowOut(QString)));
	//b = connect(this, SIGNAL(TOPLCDLG(QString)), dlg, SLOT(OnGetLeadoutPath(QString)));
	b = connect(dlg, SIGNAL(CLOSESIGNAL()), this, SLOT(on_ToClose()));
	b = connect(dlg, SIGNAL(TODRAWPICTURE(int,QString,int,int,QString)), this, SLOT(getVec(int,QString,int,int,QString)));
	dlg->setParent(ui.centralWidget);
	dlg->move(0, 0);
	b = connect(this, SIGNAL(MINI()), m_pPlclib, SLOT(setWinMini()));

	b = connect(this, SIGNAL(SETUSERLEVEL(int)), dlg, SLOT(setg_IUserLevel(int)));
	emit SETUSERLEVEL(g_IUserLevel);
}
#pragma endregion

#pragma region data caculate

bool PRT::nativeEvent(const QByteArray & eventType, void * message, long * result)
{
	if (eventType == "windows_generic_MSG")
	{

		bool bResult = false;

		MSG* msg = reinterpret_cast<MSG*>(message);

		PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)msg->lParam;

		if (msg->message == WM_DEVICECHANGE && msg->wParam >= DBT_DEVICEARRIVAL)
		{
			switch (msg->wParam)
			{
			case DBT_DEVICEARRIVAL:
			{
				PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
				char i;
				ULONG lg = lpdbv->dbcv_unitmask;
				for (i = 0; i < 26; ++i)
				{
					if (lg & 0x1)
						break;
					lg = lg >> 1;
				}
				QString outdisk = (i + 'A');
				//ui.lineEdit->setText(outdisk);
				QString m_sTempPathForLeadout = outdisk;

				showWindowOut(QString::fromLocal8Bit("已插入U盘"));
				emit TOPLCDLG(m_sTempPathForLeadout);
				break;
			}
			case DBT_DEVICEREMOVECOMPLETE:
			{
				showWindowOut(QString::fromLocal8Bit("U盘已拔下!"));
				//ui.lineEdit->setText("EXPORT");
				QString m_sTempPathForLeadout = "";// AppPath + "/EXPORT";
				emit TOPLCDLG(m_sTempPathForLeadout);
				break;
			}

			default:
				/*TODO*/
				bResult = false;
				break;
			}
		}

		return bResult;
	}
	else
	{
		return QWidget::nativeEvent(eventType, message, result);
	}
}
QString PRT::YearMonthDay()
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
void PRT::initData()
{
	//m_iDataNum = 2;//到后面设置
	//data.resize(2);

	//data[0] << 0.369;
	//data[1] << 0.390 << 0.321 << 0.332 << 0.311 << 0.399;

	/*m_iDataNum = 2;
	data.resize(2);


	data[0] << 12 << 3;
	data[1] << 23 << 2;

	data.resize(2);

	data[1] << 23 << 2;
	data.clear();*/

}
bool PRT::caculateCount()
{
	if (ui.cB_Curve->isChecked())
	{
		if (ui.checkBox->isChecked())
		{
			m_iPrintCurveCount = m_iDataNum;
		}
		else
		{
			m_iPrintCurveCount = num1_Le <= m_iDataNum ? num1_Le : m_iDataNum;
		}

	}
	else
	{
		m_iPrintCurveCount = 0;
	}
	if (ui.cB_Average->isChecked())
	{
		if (ui.checkBox_2->isChecked())
		{
			m_iPrintAveCount = m_iDataNum;
		}
		else
		{
			m_iPrintAveCount = num2_Le_2 <= m_iDataNum ? num2_Le_2 : m_iDataNum;
		}
	}
	else
	{
		m_iPrintAveCount = 0;
	}
	if (m_iDataNum == 0 || data.size()==0)
	{
		showMsgBox("提示", "无可打印数据!", "我知道了", "");
		return false;
	}
	if (m_iPrintCurveCount == 0 && m_iPrintAveCount == 0)
	{
		showMsgBox("提示", "打印数设置均为0!", "我知道了", "");
		return false;
	}
	return true;
}
#pragma endregion

#pragma region ui
void PRT::showPrt(bool b)
{
		ui.groupBox->setVisible(b);//lower
}
void PRT::initUI()
{
	ui.pB_PrintDirect->setIconSize(QSize(64, 64));
	ui.pB_PrintDirect->setIcon(QIcon(AppPath + "/ico/pt.ico"));

	ui.cB_Curve->setStyleSheet(STYLESHEET);
	ui.cB_Average->setStyleSheet(STYLESHEET);

	QRegExp regx("[0-9]+$");//正则表达式QRegExp,只允许输入中文、数字、字母、下划线以及空格,[\u4e00 - \u9fa5a - zA - Z0 - 9_] + $
	ui.lineEdit->setValidator(new QRegExpValidator(regx, this));
	ui.lineEdit_2->setValidator(new QRegExpValidator(regx, this));
	ui.lineEdit->setText(QString::number(RWini->value("ProgramSetting/PrintCurveCount", "0").toInt()));
	ui.lineEdit_2->setText(QString::number(RWini->value("ProgramSetting/PrintAveCount", "0").toInt()));
	ui.cB_Curve->setChecked(RWini->value("ProgramSetting/PrintCurve", "0").toBool());
	ui.cB_Average->setChecked(RWini->value("ProgramSetting/PrintAve", "0").toBool());
	ui.checkBox->setChecked(RWini->value("ProgramSetting/PrintCurveAllOrNot", "0").toBool());
	ui.checkBox_2->setChecked(RWini->value("ProgramSetting/PrintAveAllOrNot", "0").toBool());
	m_iPrintMode = RWini->value("ProgramSetting/PrintMode", "0").toInt();
	ui.cB_PrintMode->setCurrentIndex(m_iPrintMode);
	judgeLabelText(m_iPrintMode);

	/*lbDr = new QLabel(this);
	lbDr->resize(1280, 800);
	lbDr->move(0, 0);
	lbDr->setPixmap(QPixmap(AppPath + "/ico/touming.png"));
	lbDr->setScaledContents(true);
	lbDr->setAttribute(Qt::WA_TransparentForMouseEvents);*/
}
void PRT::judgeLabelText(int index)
{
	if (index == 0)
	{
		/*ui.label->setText(QString::fromLocal8Bit("最大可打印数：") + QString::number(m_iDataNum) + QString::fromLocal8Bit("\n1#站: ") + QString::number(m_iDataNum - m_iDataNum / 2) + QString::fromLocal8Bit("\n2#站: ") + QString::number(m_iDataNum / 2));*/
	}
	else
	{
		ui.label->setText(QString::fromLocal8Bit("曲线图表: 2组数据"));/*\n均值图表:12组数据*/
	}

}
void PRT::writeIni()
{
	num1_Le = 20;// ui.lineEdit->text().toInt();
	num2_Le_2 = 20;// ui.lineEdit_2->text().toInt();

	/*ui.lineEdit->setText(QString::number(num1_Le));
	ui.lineEdit_2->setText(QString::number(num2_Le_2));

	RWini->setValue("ProgramSetting/PrintCurveCount", QString::number(num1_Le));
	RWini->setValue("ProgramSetting/PrintAveCount", QString::number(num2_Le_2));*/
}
#pragma endregion

#pragma region printer
void PRT::initPrinter()
{
	m_drawpicture = new DrawPicture(nullptr);
	m_drawpictureThread = new QThread();
	m_drawpicture->moveToThread(m_drawpictureThread);
	m_drawpictureThread->start();

	connect(m_drawpicture, SIGNAL(TOUI(QString)), this, SLOT(showPrintName(QString)));
	QPrinterInfo info;
	QString ptName = info.defaultPrinterName(); // 默认打印机名字		
	showPrintName(QString::fromLocal8Bit("默认设备型号：\n") + ptName);
	m_prt = new QPrinter();
	m_prt->setPrinterName(ptName);

	//emit TOUI(QString::fromLocal8Bit("默认设备型号：\n") + ptName);

	m_prt->setResolution(QPrinter::HighResolution);
	////自定义纸张大小，特别重要，不然预览效果极差
	//printer->setPrinterName(m_sName);
	m_prt->setPageSize(QPrinter::A4);
	m_prt->setOrientation(QPrinter::Portrait);

	m_prt->setFullPage(true);//first

	QPagedPaintDevice::Margins marg;//second
	marg.left = 0;
	marg.top = 5;
	m_prt->setMargins(marg);
}
void PRT::showPrintName(QString str)
{
	ui.lb_PrinterName->setText(str);
}
void PRT::toDraw(QPrinter *p)
{
	//	dlg.setWindowOpacity(0.8);
		//dlg.setWindowFlags(Qt::FramelessWindowHint);//设置为对话框风格，并且去掉边框
		//dlg.setWindowModality(Qt::WindowModal);//设置为模式对话框，同时在构造该对话框时要设置父窗口
	wt->show();
	QPdfWriter w("d:/text1.pdf");
	m_drawpicture->drawPic(p,&w,0);
	wt->close();
	wt->setTxt(QString::fromLocal8Bit("打印正在进行,请稍等..."));
}
#pragma endregion

#pragma	region events
void PRT::mousePressEvent(QMouseEvent* p)
{
	if (p->button() == Qt::LeftButton) {       // 如果是鼠标左键按下
		m_offset = p->globalPos() - pos();    // 获取指针位置和窗口位置的差值
	}
}
void PRT::mouseMoveEvent(QMouseEvent * event)
{
	return;
	if (event->buttons() & Qt::LeftButton) {      // 这里必须使用buttons()
		QPoint temp;
		temp = event->globalPos() - m_offset;// 使用鼠标指针当前的位置减去差值，就得到了窗口应该移动的位置
		if (temp.y() > 750)
		{
			/*if (QMessageBox::Yes == showMsgBox("退出确认", "是否确认退出该系统?", "确认", "取消"))
			{
				m_bCloseSignal = true;
				close();
			}*/
			showMinimized(); 
			emit MINI();
			showWindowOut(QString::fromLocal8Bit("系统界面已最小化至任务栏"));
		}
		if (temp.x() > 1250)
		{
			
		}
	}
}
void PRT::closeEvent(QCloseEvent *event)
{/*
	if (!m_bCloseSignal)
	{
		event->ignore();
		return;
	}
*/
	if (m_pPlclib != nullptr)
	{
		m_pPlclib->QtDestroyDlg();
	}
}

bool PRT::eventFilter(QObject* obj, QEvent* event)
{
	//if (obj == this)
	//{
	//	switch (event->type())
	//	{
	//	case QKeyEvent::KeyPress:
	//	{
	//		int key_type = static_cast<QKeyEvent*>(event)->key();
	//		if (key_type == Qt::Key_Alt)
	//			m_bAltKeyPressed = true;
	//		break;
	//	}
	//	case QEvent::KeyRelease:
	//	{
	//		int key_type = static_cast<QKeyEvent*>(event)->key();
	//		if (key_type == Qt::Key_Alt)
	//			m_bAltKeyPressed = false;
	//		break;
	//	}
	//	case QEvent::Close:
	//	{
	//		if (m_bAltKeyPressed)
	//		{//屏蔽ALT+F4
	//			event->ignore();
	//			return true;
	//			break;
	//		}
	//	}
	//	default:break;
	//	}
	//}
	return QObject::eventFilter(obj, event);
}
#pragma endregion

#pragma region popup window
int PRT::showMsgBox(const char* titleStr, const char* contentStr, const char* button1Str, const char* button2Str)
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
void PRT::showWindowOut(QString str)
{
	levelOut = new WindowOut;
	levelOut->setWindowCount(0);
	levelOut->getString(str, 2000);
	levelOut->show();
}
void PRT::SuccessConnect()
{
	tm_ReConnect->stop();
	delete tm_ReConnect;
	tm_ReConnect = nullptr;

	wt->close();
	if (lg == 0)showWindowOut(QString::fromLocal8Bit("PLC连接正常"));
	if (lg == 1)showWindowOut(QString::fromLocal8Bit("PLC Connect Success"));


	//bool b = connect(m_pPlclib, SIGNAL(SOCKETERROR()), this, SLOT(ErrorConnect()));
	//b = disconnect(m_pPlclib, SIGNAL(signal_SUCCESSFULCONNECTED()), this, SLOT(SuccessConnect()));
}
void PRT::ErrorConnect()
{
	//char *pathvar = getenv("CODERCOMPUTER");//自己电脑上创建的环境变量CODERCOMPUTER 值：coder
	//QString envStr = QString::fromLocal8Bit(pathvar);

	//if (envStr == "coder")//第二个参数：自己的电脑跟随软件关闭而关闭的功能无效
	//{
	//	return;
	//}
	if (tm_ReConnect == nullptr)
	{
		wt->show();
		tm_ReConnect = new QTimer();
	}
	else
	{
		return;
	}
	bool b = connect(tm_ReConnect, SIGNAL(timeout()), this, SLOT(EmitReconnect()));
	tm_ReConnect->start(2000);
	return;
	wt->close();
	if (lg == 0)showMsgBox("通讯错误", "连接PLC出错,请修复后重启程序!", "我去查查", "");
	if (lg == 1)showMsgBox("Communication Error", "Connect PLC timeout,Please fix and restart the software!", "check", "");

}
void PRT::EmitReconnect()
{
	//char *pathvar = getenv("CODERCOMPUTER");//自己电脑上创建的环境变量CODERCOMPUTER 值：coder
	//QString envStr = QString::fromLocal8Bit(pathvar);

	//if (envStr == "coder")//第二个参数：自己的电脑跟随软件关闭而关闭的功能无效
	//{
	//	return;
	//}
	wt->show();//remeber to note off
	//tm_ReConnect->stop();
	//delete tm_ReConnect;
	//tm_ReConnect = nullptr;
	emit STARTCONNECTPLC();
}
#pragma endregion

#pragma	region ui slots
void PRT::on_cB_Curve_toggled(bool checked)
{
	m_drawpicture->setCurveChecked(checked);
	ui.label_2->setVisible(checked);

	if (!ui.checkBox->isChecked())
	{
		ui.lineEdit->setVisible(checked);
	}

	ui.checkBox->setVisible(checked);
	QSettings WriteIni(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	WriteIni.setValue("ProgramSetting/PrintCurve", QString::number(checked));
	if (!checked && !ui.cB_Average->isChecked())
	{
		ui.pB_Print->setEnabled(false);
		ui.pB_PrintDirect->setEnabled(false);
	}
	else
	{
		ui.pB_Print->setEnabled(true);
		ui.pB_PrintDirect->setEnabled(true);
	}
}
void PRT::on_cB_Average_toggled(bool checked)
{
	m_drawpicture->setAveChecked(checked);
	ui.label_3->setVisible(checked);
	if (!ui.checkBox_2->isChecked())
	{
		ui.lineEdit_2->setVisible(checked);
	}
	ui.checkBox_2->setVisible(checked);
	QSettings WriteIni(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	WriteIni.setValue("ProgramSetting/PrintAve", QString::number(checked));
	if (!checked && !ui.cB_Curve->isChecked())
	{
		ui.pB_Print->setEnabled(false);
		ui.pB_PrintDirect->setEnabled(false);
	}
	else
	{
		ui.pB_Print->setEnabled(true);
		ui.pB_PrintDirect->setEnabled(true);
	}
}
void PRT::on_checkBox_toggled(bool checked)
{
	ui.lineEdit->setVisible(!checked);
	QSettings WriteIni(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	WriteIni.setValue("ProgramSetting/PrintCurveAllOrNot", QString::number(checked));
}
void PRT::on_checkBox_2_toggled(bool checked)
{
	ui.lineEdit_2->setVisible(!checked);
	QSettings WriteIni(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	WriteIni.setValue("ProgramSetting/PrintAveAllOrNot", QString::number(checked));
}
void PRT::SWITCHOSK()//快捷键
{
	QProcess pro;
	QString strPath = "C:\\Windows\\System32\\osk.exe";
	pro.startDetached(strPath);
}
void PRT::on_pB_PrintDirect_clicked()
{
	/*直接打印*/

	writeIni();
	if (!caculateCount())return;

	wt->setTxt(QString::fromLocal8Bit("正在打印,请稍等..."));
	if (m_cb.mid(0, 1) == "0")//1个参数的
	{
		if (QMessageBox::Yes == showMsgBox("打印确认", "确认打印数据曲线?", "确认", "取消"))
		{
			wt->show();
			m_drawpicture->setData(data, gn, m_iPrintCurveCount, m_iPrintAveCount, theory,m_CustomerName,m_MedicineName,m_Low,m_High,m_PureShell,m_cb,m_Yield, m_Pressure, m_Speed,thickness,hardness);
			QPdfWriter w("");
			m_drawpicture->drawPic(m_prt, &w, 0);
			wt->close();
			showWindowOut(QString::fromLocal8Bit("打印完成!"));
		}	
	}
	else if (m_cb.mid(0, 1) == "1")
	{
		if (QMessageBox::Yes == showMsgBox("打印确认", "确认打印试机记录?", "确认", "取消"))
		{
			int sz = data.size();
			m_drawpicture->setData(data, gn, m_iPrintCurveCount, sz, theory, m_CustomerName, m_MedicineName, m_Low, m_High, m_PureShell, m_cb, m_Yield, m_Pressure, m_Speed, thickness, hardness);
			wt->show();
			m_drawpicture->drawPic2(m_prt);
			wt->close();
			showWindowOut(QString::fromLocal8Bit("打印完成!"));
		}
	}
	else if (m_cb.mid(0, 1) == "2")//多个参数的
	{
		if (QMessageBox::Yes == showMsgBox("打印确认", "确认打印数据曲线?", "确认", "取消"))
		{
			int sz = data.size();
			m_drawpicture->setData(data, gn, m_iPrintCurveCount, sz, theory, m_CustomerName, m_MedicineName, m_Low, m_High, m_PureShell, m_cb, m_Yield, m_Pressure, m_Speed, thickness, hardness);
			wt->show(); 
			QPdfWriter w("");
			m_drawpicture->drawPic3(m_prt,&w,0);
			wt->close();
			showWindowOut(QString::fromLocal8Bit("打印完成!"));
		}
	}

	else if (m_cb.mid(0, 1) == "3")//1个和3个参数的
	{
		if (QMessageBox::Yes == showMsgBox("确认", "确认导出数据?", "确认", "取消"))
		{
			wt->setTxt(QString::fromLocal8Bit("正在导出数据,请稍等..."));
			wt->show();
			int sz = data.size();
			m_drawpicture->setData(data, gn, m_iPrintCurveCount, sz, theory, m_CustomerName, m_MedicineName, m_Low, m_High, m_PureShell, m_cb, m_Yield, m_Pressure, m_Speed, thickness, hardness);
			QPdfWriter *pr=new QPdfWriter(m_PdfPath);
			
			QString str = m_PdfPath.left(m_PdfPath.lastIndexOf("/"));
			QDir dir(str);
			if (!dir.exists())
			{
				bool res = dir.mkpath(str);
			}
#ifndef MODBUSTCP
			m_drawpicture->drawPic(m_prt, pr, 1);
#else
			m_drawpicture->drawPic3(m_prt, pr, 1);
#endif
			delete pr;
			wt->close();
			showWindowOut(QString::fromLocal8Bit("数据已导出!"));
		}
	}

}
void PRT::on_pB_Print_clicked()
{
	writeIni();
	if (!caculateCount())return;

	QPrintPreviewDialog preview;// 创建打印预览对话框
	preview.setWindowTitle(QString::fromLocal8Bit("打印预览"));
	preview.setWindowIcon(QIcon("./ico/dr.ico"));
	preview.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
	//preview.setModal(Qt::WindowModal);
	preview.setMinimumWidth(1262);
	preview.setMinimumHeight(755);
	preview.setMaximumWidth(1262);
	preview.setMaximumHeight(755);
	/*
	 * QPrintPreviewDialog类提供了一个打印预览对话框，里面功能比较全，
	 * paintRequested(QPrinter *printer)是系统提供的，
	 * 当preview.exec()执行时该信号被触发，
	 * drawPic(QPrinter *printer)是自定义的槽函数，图像的绘制就在这个函数里。
	 */
	///*/*/*/*m_drawpicture->setData(data,gn, m_iPrintCurveCount, m_iPrintAveCount, theory, m_CustomerName, m_MedicineName, m_Low, m_High, m_PureShell, m_cb, m_Yield, m_Pressure, m_Speed);*/*/*/*/
	//wt->setTxt(QString::fromLocal8Bit("打印预览功能正在开启..."));//打印正在进行,请稍等...
	connect(&preview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(toDraw(QPrinter*)));
	preview.exec();
}
void PRT::on_cB_PrintMode_currentIndexChanged(int index)
{
	judgeLabelText(index);
	RWini->setValue("ProgramSetting/PrintMode", QString::number(ui.cB_PrintMode->currentIndex()));
	m_iPrintMode = index;
}
void PRT::on_ToClose()
{
	if (lg==0)
	{
		if (QMessageBox::Yes == showMsgBox("退出确认", "是否确认退出该系统?", "确认", "取消"))
		{
			//m_bCloseSignal = true;
			close();
		}
	}
	else if (lg==1)
	{
		if (QMessageBox::Yes == showMsgBox("Information", "Quit the System?", "Yes", "Cancel"))
		{
			//m_bCloseSignal = true;
			close();
		}
	}
}

void PRT::getVec(int mode,QString strCb, int p1,int p2,QString pdfpath) //strCb: 0曲线 1试机 2三参数,3导出，0 胶囊 1片剂
{
	if (mode==0)//MODE 0:dataAverage,1:curve
	{
		/*ui.cB_Curve->setChecked(false);
		ui.cB_Average->setChecked(true);
		m_iDataNum = a.size();
		//data.resize(1);
		data = a;
		//data[0] = a;

		on_pB_PrintDirect_clicked();
		data.clear();*/
	}
	else if (mode == 1)
	{
		QSettings configIniRead(AppPath + "\\temp\\data.ini", QSettings::IniFormat);
		
		for (int i = p1; i < p2 + 1; i++)
		{
			QString str = configIniRead.value(QString::number(i) + "/data", 0).toString();
			if (str != "0")
			{
				QStringList lst = str.split(",");
				QVector<float> data_temp;
				for (int j = 0; j < lst.size(); j++)
				{
					data_temp << lst.at(j).toFloat();
				}
				data << data_temp;

				QVector<float> data_tempThick;
				QString strThick= configIniRead.value(QString::number(i) + "/thick", "").toString();
				//if (strThick != "0")
				{
					QStringList lstThick = strThick.split(",");
					for (int j = 0; j < lstThick.size(); j++)
					{
						data_tempThick << lstThick.at(j).toFloat();
					}
					thickness << data_tempThick;
				}
				QVector<float> data_tempHard;
				QString strhard = configIniRead.value(QString::number(i) + "/hard", "").toString();
				//if (strhard != "")
				{
					QStringList lstHard = strhard.split(",");
					for (int j = 0; j < lstHard.size(); j++)
					{
						data_tempHard << lstHard.at(j).toFloat();
					}
					hardness << data_tempHard;
				}


				gn << configIniRead.value(QString::number(i) + "/gn", "0").toString();
				theory << configIniRead.value(QString::number(i) + "/theory", 1).toFloat();
				m_CustomerName << configIniRead.value(QString::number(i) + "/CustomerName", "").toString();
				m_MedicineName << configIniRead.value(QString::number(i) + "/MedicineName", "").toString();
				m_Low << configIniRead.value(QString::number(i) + "/Low", 0).toInt();
				m_High << configIniRead.value(QString::number(i) + "/High", 0).toInt();
				m_PureShell << configIniRead.value(QString::number(i) + "/PureShell", 0).toInt();
				m_Yield << configIniRead.value(QString::number(i) + "/Yield", 0).toInt();
				m_Pressure << configIniRead.value(QString::number(i) + "/Pressure", 0).toInt();
				m_Speed << configIniRead.value(QString::number(i) + "/Speed", 0).toInt();
			}
		}
		on_cB_Curve_toggled(true);
		ui.cB_Curve->blockSignals(true);
		ui.cB_Curve->setChecked(true);
		ui.cB_Curve->blockSignals(false);
		on_cB_Average_toggled(false);
		ui.cB_Average->blockSignals(true);
		ui.cB_Average->setChecked(false);
		ui.cB_Average->blockSignals(false);
		/*m_iDataNum = 1;
		data.resize(1);*/
		m_iDataNum = data.size();

		m_cb = strCb;

		m_PdfPath = pdfpath;
		on_pB_PrintDirect_clicked();
		
		data.clear();
		gn.clear();
		theory.clear();
		hardness.clear();
		thickness.clear();
		m_CustomerName.clear();
		m_MedicineName.clear();
		m_Low.clear();
		m_High.clear();
		m_PureShell.clear();
		m_Yield.clear();
		m_Pressure.clear();
		m_Speed.clear();

	}
	/*else if (mode == 2)
	{
		on_cB_Curve_toggled(true);
		on_cB_Average_toggled(false);
		m_iDataNum = 2;
		data.resize(2);
		data[m_iCurrentGetDataNo++] = a;

		if (m_iCurrentGetDataNo == 2)
		{
			on_pB_Print_clicked();
			m_iCurrentGetDataNo = 0;
			data.clear();
		}
	}
	else if (mode == 3)
	{
		on_cB_Curve_toggled(false);
		on_cB_Average_toggled(true);
		m_iDataNum = 2;
		data.resize(2);

		data[m_iCurrentGetDataNo++] = a;

		if (m_iCurrentGetDataNo == 2)
		{
			on_pB_Print_clicked();
			m_iCurrentGetDataNo = 0;
			data.clear();
		}
	}*/
	
}
#pragma endregion
