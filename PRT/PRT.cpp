#include "PRT.h"
#include <QMetaType> 

PRT::PRT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	qRegisterMetaType<QVector<float>>("QVector<float>");
	qRegisterMetaType<QVector<float>>("QVector<float>&");//ע��opencv�������ڲۺ����б������
	wt = new QWaiting();
	//initDog(); //remeber to note off
	setWindowFlags(Qt::FramelessWindowHint);//�ޱ߿�  
	//setAttribute(Qt::WA_AcceptTouchEvents);
	setWindowIcon(QIcon("./ico/dr.ico"));
	AppPath = qApp->applicationDirPath();//exe����Ŀ¼
	RWini = new QSettings(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
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
	if (m_dong != nullptr)
	{
		if (!m_bFlagWriteDongleFinally)//��������й��д���Ͳ�д���ˣ��������дһ��ʱ��
		{
			m_dong->setTimeData();
		}		

		delete m_dong;
		m_dong = nullptr;

	}
}

#pragma region PLC
void PRT::initPLC()
{
	m_pPlclib = new QtPLCControl();//dll
	lib_PLCThread = new QThread();
	m_pPlclib->moveToThread(lib_PLCThread);
	lib_PLCThread->start();

	bool b = connect(this, SIGNAL(STARTCONNECTPLC()), m_pPlclib, SLOT(ConnectPlc()));
	//emit STARTCONNECTPLC();
	b = connect(m_pPlclib, SIGNAL(SOCKETERROR()), this, SLOT(ErrorConnect()));
	b = connect(m_pPlclib, SIGNAL(signal_SUCCESSFULCONNECTED()), this, SLOT(SuccessConnect()));
	if (tm_ReConnect == nullptr)
	{
		tm_ReConnect = new QTimer();
	}
	b = connect(tm_ReConnect, SIGNAL(timeout()), this, SLOT(EmitReconnect()));
	tm_ReConnect->start(10);

	wt->setTxt(QString::fromLocal8Bit("��������PLC,���Ե�..."));
	dlg = (QDialog *)(m_pPlclib->QtCreateDialog(1));
	b = connect(dlg, SIGNAL(SHOWPRT(bool)), this, SLOT(showPrt(bool)));
	b = connect(dlg, SIGNAL(TODRAWPICTURE(QVector<float>,int)), this, SLOT(getVec(QVector<float>,int)));
	dlg->setParent(ui.widget);
	dlg->move(0, 0);
	b = connect(this, SIGNAL(MINI()), m_pPlclib, SLOT(setWinMini()));
}
#pragma endregion

#pragma region dongle
void PRT::initDog()
{
	m_dong = new Dongle();
	connect(m_dong->get_m_RockeyARM(), SIGNAL(DONGLEERRORCODE(int)), this, SLOT(closes(int)));

	if (m_dong->initDongle())
	{
		m_dong->threadRun();
		lst = new QStringList();
		//lst = (QStringList *)(m_dong->CameraQstringListInDongle());

	}
	else
	{
		exit(-1);
	}
}
void PRT::closes(int index)
{
	if (index == 0)
	{
		showMsgBox("��ʾ", "δ�ҵ����ܹ�!", "��֪����", "");
		//QMessageBox::about(nullptr, "0", "can not FIND dongle!");
		m_bFlagWriteDongleFinally = true;
		m_bCloseSignal = true;
		close();
	}
	else if (index == 1)
	{
		showMsgBox("��ʾ", "���ܹ���ʧ��!", "��֪����", "");
		//QMessageBox::about(nullptr, "1", "can not OPEN dongle!");
		m_bFlagWriteDongleFinally = true;
		m_bCloseSignal = true;
		close();
	}
	else if (index == 2)
	{
		showMsgBox("��ʾ", "���ܹ���֤ʧ��!", "��֪����", "");
		//QMessageBox::about(nullptr, "2", "can not VERIFY dongle!");
		m_bFlagWriteDongleFinally = true;
		m_bCloseSignal = true;
		close();
	}
	else if (index == 3)
	{
		showMsgBox("��ʾ", "���ܹ���ȡʧ��!", "��֪����", "");
		//QMessageBox::about(nullptr, "3", "can not READ dongle!");
		m_bFlagWriteDongleFinally = true;
		m_bCloseSignal = true;
		close();
	}
	else if (index == 4)
	{
		showMsgBox("��ʾ", "���ܹ�д��ʧ��!", "��֪����", "");
		//QMessageBox::about(nullptr, "4", "can not WRITE dongle!");
		m_bFlagWriteDongleFinally = true;
		m_bCloseSignal = true;
		close();
	}
	else if (index == 10)
	{
		showMsgBox("��ʾ", "ϵͳʱ�䱻�Ƿ��޸�!", "��֪����", "");
		//QMessageBox::about(nullptr, "10", "system time be changed ILLEGALLY!");
		m_bFlagWriteDongleFinally = true;
		m_bCloseSignal = true;
		close();
	}
	else if (index == 11)
	{
		showMsgBox("��ʾ", "���ܹ���Ȩ�ѹ���!", "��֪����", "");
		//QMessageBox::about(nullptr, "11", "the dongle is RUN OUT!");
		m_bFlagWriteDongleFinally = true;
		m_bCloseSignal = true;
		close();
	}
	else
	{
		m_bFlagWriteDongleFinally = false;
	}
}
#pragma endregion

#pragma region data caculate
void PRT::initData()
{
	//m_iDataNum = 2;//����������
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
		showMsgBox("��ʾ", "�޿ɴ�ӡ����!", "��֪����", "");
		return false;
	}
	if (m_iPrintCurveCount == 0 && m_iPrintAveCount == 0)
	{
		showMsgBox("��ʾ", "��ӡ�����þ�Ϊ0!", "��֪����", "");
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

	QRegExp regx("[0-9]+$");//������ʽQRegExp,ֻ�����������ġ����֡���ĸ���»����Լ��ո�,[\u4e00 - \u9fa5a - zA - Z0 - 9_] + $
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

	lbDr = new QLabel(this);
	lbDr->resize(1280, 800);
	lbDr->move(0, 0);
	lbDr->setPixmap(QPixmap(AppPath + "/ico/dr.png"));
	lbDr->setScaledContents(true);
	lbDr->setAttribute(Qt::WA_TransparentForMouseEvents);
}
void PRT::judgeLabelText(int index)
{
	if (index == 0)
	{
		/*ui.label->setText(QString::fromLocal8Bit("���ɴ�ӡ����") + QString::number(m_iDataNum) + QString::fromLocal8Bit("\n1#վ: ") + QString::number(m_iDataNum - m_iDataNum / 2) + QString::fromLocal8Bit("\n2#վ: ") + QString::number(m_iDataNum / 2));*/
	}
	else
	{
		ui.label->setText(QString::fromLocal8Bit("����ͼ��: 2������"));/*\n��ֵͼ��:12������*/
	}

}
void PRT::writeIni()
{
	num1_Le = ui.lineEdit->text().toInt();
	num2_Le_2 = ui.lineEdit_2->text().toInt();

	ui.lineEdit->setText(QString::number(num1_Le));
	ui.lineEdit_2->setText(QString::number(num2_Le_2));

	RWini->setValue("ProgramSetting/PrintCurveCount", QString::number(num1_Le));
	RWini->setValue("ProgramSetting/PrintAveCount", QString::number(num2_Le_2));
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
	QString ptName = info.defaultPrinterName(); // Ĭ�ϴ�ӡ������		
	showPrintName(QString::fromLocal8Bit("Ĭ���豸�ͺţ�\n") + ptName);
	m_prt = new QPrinter();
	m_prt->setPrinterName(ptName);
}
void PRT::showPrintName(QString str)
{
	ui.lb_PrinterName->setText(str);
}
void PRT::toDraw(QPrinter *p)
{
	//	dlg.setWindowOpacity(0.8);
		//dlg.setWindowFlags(Qt::FramelessWindowHint);//����Ϊ�Ի����񣬲���ȥ���߿�
		//dlg.setWindowModality(Qt::WindowModal);//����Ϊģʽ�Ի���ͬʱ�ڹ���öԻ���ʱҪ���ø�����
	wt->show();
	m_drawpicture->drawPic(p);
	wt->close();
	wt->setTxt(QString::fromLocal8Bit("��ӡ���ڽ���,���Ե�..."));
}
#pragma endregion

#pragma	region events
void PRT::mousePressEvent(QMouseEvent* p)
{
	if (p->button() == Qt::LeftButton) {       // ���������������
		m_offset = p->globalPos() - pos();    // ��ȡָ��λ�úʹ���λ�õĲ�ֵ
	}
}
void PRT::mouseMoveEvent(QMouseEvent * event)
{
	if (event->buttons() & Qt::LeftButton) {      // �������ʹ��buttons()
		QPoint temp;
		temp = event->globalPos() - m_offset;// ʹ�����ָ�뵱ǰ��λ�ü�ȥ��ֵ���͵õ��˴���Ӧ���ƶ���λ��
		if (temp.y() > 750)
		{
			showMinimized(); 
			emit MINI();
			showWindowOut(QString::fromLocal8Bit("ϵͳ��������С����������"));
		}
		if (temp.x() > 1250)
		{
			if (QMessageBox::Yes == showMsgBox("�˳�ȷ��", "�Ƿ�ȷ���˳���ϵͳ?", "ȷ��", "ȡ��"))
			{
				m_bCloseSignal = true;
				close();
			}
		}
	}
}
void PRT::closeEvent(QCloseEvent *event)
{
	if (!m_bCloseSignal)
	{
		event->ignore();
		return;
	}

	if (m_pPlclib != nullptr)
	{
		m_pPlclib->QtDestroyDlg();
	}
}

bool PRT::eventFilter(QObject* obj, QEvent* event)
{
	if (obj == this)
	{
		switch (event->type())
		{
		case QKeyEvent::KeyPress:
		{
			int key_type = static_cast<QKeyEvent*>(event)->key();
			if (key_type == Qt::Key_Alt)
				m_bAltKeyPressed = true;
			break;
		}
		case QEvent::KeyRelease:
		{
			int key_type = static_cast<QKeyEvent*>(event)->key();
			if (key_type == Qt::Key_Alt)
				m_bAltKeyPressed = false;
			break;
		}
		case QEvent::Close:
		{
			if (m_bAltKeyPressed)
			{//����ALT+F4
				event->ignore();
				return true;
				break;
			}
		}
		default:break;
		}
	}
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
	wt->close();
	showWindowOut(QString::fromLocal8Bit("PLC��������"));

	//bool b = connect(m_pPlclib, SIGNAL(SOCKETERROR()), this, SLOT(ErrorConnect()));
	//b = disconnect(m_pPlclib, SIGNAL(signal_SUCCESSFULCONNECTED()), this, SLOT(SuccessConnect()));
}
void PRT::ErrorConnect()
{
	wt->close();
	showMsgBox("ͨѶ����", "����PLC����,���޸�����������!", "��ȥ���", "");

}
void PRT::EmitReconnect()
{
	//wt->show();//remeber to note off
	tm_ReConnect->stop();
	delete tm_ReConnect;
	tm_ReConnect = nullptr;
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
void PRT::on_pB_PrintDirect_clicked()
{
	/*ֱ�Ӵ�ӡ*/
	writeIni();

	if (!caculateCount())return;
	if (QMessageBox::Yes == showMsgBox("��ӡȷ��", "ȷ�ϴ�ӡ����?", "ȷ��", "ȡ��"))
	{
		m_drawpicture->setData(data, m_iPrintCurveCount, m_iPrintAveCount);
		wt->show();
		m_drawpicture->drawPic(m_prt);
		wt->close();
	}

}
void PRT::on_pB_Print_clicked()
{
	writeIni();
	if (!caculateCount())return;

	QPrintPreviewDialog preview;// ������ӡԤ���Ի���
	preview.setWindowTitle(QString::fromLocal8Bit("��ӡԤ��"));
	preview.setWindowIcon(QIcon("./ico/dr.ico"));
	preview.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
	//preview.setModal(Qt::WindowModal);
	preview.setMinimumWidth(1262);
	preview.setMinimumHeight(755);
	preview.setMaximumWidth(1262);
	preview.setMaximumHeight(755);
	/*
	 * QPrintPreviewDialog���ṩ��һ����ӡԤ���Ի������湦�ܱȽ�ȫ��
	 * paintRequested(QPrinter *printer)��ϵͳ�ṩ�ģ�
	 * ��preview.exec()ִ��ʱ���źű�������
	 * drawPic(QPrinter *printer)���Զ���Ĳۺ�����ͼ��Ļ��ƾ�����������
	 */
	m_drawpicture->setData(data, m_iPrintCurveCount, m_iPrintAveCount);
	wt->setTxt(QString::fromLocal8Bit("��ӡԤ���������ڿ���..."));//��ӡ���ڽ���,���Ե�...
	connect(&preview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(toDraw(QPrinter*)));
	preview.exec();
}
void PRT::on_cB_PrintMode_currentIndexChanged(int index)
{
	judgeLabelText(index);
	RWini->setValue("ProgramSetting/PrintMode", QString::number(ui.cB_PrintMode->currentIndex()));
	m_iPrintMode = index;
}


void PRT::getVec(QVector<float> a,int mode)
{
	if (mode==0)//MODE 0:one curve,1:one dataAverage,2:two curve,3:two dataAverage
	{
		on_cB_Curve_toggled(true);
		on_cB_Average_toggled(false); 
		m_iDataNum = 1;
		data.resize(1);

		data[0] = a;

		on_pB_Print_clicked();
		data.clear();
	}
	else if (mode == 1)
	{
		on_cB_Curve_toggled(false);
		on_cB_Average_toggled(true);
		m_iDataNum = 1;
		data.resize(1);

		data[0] = a;

		on_pB_Print_clicked();
		data.clear();
	}
	else if (mode == 2)
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
	}
	
}
#pragma endregion
