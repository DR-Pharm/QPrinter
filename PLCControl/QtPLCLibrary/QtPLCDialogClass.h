#pragma once


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
	void initContinueKick();//����4��widgets
	int showMsgBox(QMessageBox::Icon icon, const char* titleStr, const char* contentStr, const char* button1Str, const char* button2Str);//ȫ������
	void SetSocket(QtSocket_Class*);
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
public slots:
	//void savePLCParaInPLCTxt(int);//��combobox�޸ĵ�phototimesд��txt
	void on_pb_cmdParaSave_clicked();//����PLC����������plc.txt
	void on_pb_cmdParaLoad_clicked();//������plc.txt��PLC����д�뵽PLC
	void MoveOut();//���̵���
	void MoveOutWhenWrite();
	//ȷ���޸ĺ��������
	void on_pB_changeIPPort_clicked();
	void on_pB_ContinueKickOK_clicked();//��������
	void on_pB_ContinueKickCancel_clicked();//ȡ������

	//void onStartStore(bool);
	void onSendPLCCommand(bool);
	void onDebugMode(bool);//����һֱ��
	void updateCyclinderSituation();
	DataFromPC_typ getPCData();//PC��ֵ���͸�PLC
	void getPLCData(void*, int, int, int, int);
public:
	//MESSAGE_HANDLER ShowFunc(void* context, DataToPC_typ);
	void connectBtnGroup();
	void setm_iCameraTotal(int index);
};

#pragma once


