#pragma once
#include <QDebug>
#include <QLabel>
#include "PLCRelayHead.h"
#include "QtSocket_Class.h"
namespace spd = spdlog;

class QtPLCDialogClass : public QDialog

{
	Q_OBJECT

signals:
	void CLOSESIGNAL();
	void SHOWEVERYPLCVALUE(DataToPC_typ);
	void GETSTRING(QString);

public:
	QtPLCDialogClass(QDialog *parent = Q_NULLPTR);
	~QtPLCDialogClass();
	void initFont();
	int showMsgBox(QMessageBox::Icon icon, const char* titleStr, const char* contentStr, const char* button1Str, const char* button2Str);//全是中文
	void SetSocket(QtSocket_Class*);
	void setStyleCommand(QPushButton*, QString, QFont, QString);
private:
	void* ui;
	bool m_currentSituationOfCyclinder = true;
	QTimer *cyclinderTimer = nullptr;
	//DataToPC_typ *m_data;	//获取的PLC数据
	//WindowOut *levelOut;//show默认为非模态modal，如果是局部变量会闪现消失
	QString m_objname = "";
	QString m_tempname = "";
	QtSocket_Class *m_socket = nullptr;
	QString AppPath = qApp->applicationDirPath();
	DataToPC_typ *m_data = nullptr;

	QPushButton* obj = nullptr;//pushbutton le;

	QLabel *lb_01 = nullptr;
	QLabel *lb_11 = nullptr;

	QFont setupFont;
	QFont startFont;

public slots:

	void onSendPLCCommand(bool);
	DataFromPC_typ getPCData();//PC数值发送给PLC
	void getPLCData(void*, int, int, int, int);

	void on_pB_cmdScaleRead_clicked();
	void on_pB_cmdScaleTire_clicked();
	void on_pB_cmdScaleSetStable_clicked();
	void on_cB_paraScaleSetStable_currentIndexChanged(int index);
	void on_pB_cmdScaleCalibExt_clicked();

	void on_pB_SetUp_toggled(bool checked);
	void on_pB_cmdStart_toggled(bool checked);
	void on_pB_cmdCounterZero_clicked();
	void on_pB_cmdAlarmReset_clicked();
	void on_pB_cmdCapClean_clicked();
};

#pragma once


