#pragma once

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
	int showMsgBox(QMessageBox::Icon icon, const char* titleStr, const char* contentStr, const char* button1Str, const char* button2Str);//ȫ������
	void SetSocket(QtSocket_Class*);
	void setStyleCommand(QPushButton*,QString,QFont,QString);
private:
	void* ui;
	bool m_currentSituationOfCyclinder = true;
	QTimer *cyclinderTimer = nullptr;
	//DataToPC_typ *m_data;	//��ȡ��PLC����
	//WindowOut *levelOut;//showĬ��Ϊ��ģ̬modal������Ǿֲ�������������ʧ
	QString m_objname = "";
	QString m_tempname = "";
	QtSocket_Class *m_socket = nullptr;
	QString AppPath = qApp->applicationDirPath();
	DataToPC_typ *m_data = nullptr;

	QPushButton* obj = nullptr;//pushbutton le;

	QLabel *lb_01=nullptr;
	QLabel *lb_11=nullptr;

	QFont setupFont;
	QFont startFont;

public slots:
	//void savePLCParaInPLCTxt(int);//��combobox�޸ĵ�phototimesд��txt
	void on_pb_cmdParaSave_clicked();//����PLC����������plc.txt
	void on_pb_cmdParaLoad_clicked();//������plc.txt��PLC����д�뵽PLC

	void onSendPLCCommand(bool);
	DataFromPC_typ getPCData();//PC��ֵ���͸�PLC
	void getPLCData(void*, int, int, int, int);
	void on_pB_SetUp_toggled(bool checked);

	void on_pB_cmdStart_toggled(bool checked);


};

#pragma once


