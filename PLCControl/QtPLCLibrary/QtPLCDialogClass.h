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
	void initContinueKick();//连剔4个widgets
	int showMsgBox(QMessageBox::Icon icon, const char* titleStr, const char* contentStr, const char* button1Str, const char* button2Str);//全是中文
	void SetSocket(QtSocket_Class*);
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
public slots:
	//void savePLCParaInPLCTxt(int);//将combobox修改的phototimes写入txt
	void on_pb_cmdParaSave_clicked();//保存PLC参数到本机plc.txt
	void on_pb_cmdParaLoad_clicked();//将本机plc.txt内PLC参数写入到PLC
	void MoveOut();//键盘弹出
	void MoveOutWhenWrite();
	//确定修改后键盘隐藏
	void on_pB_changeIPPort_clicked();
	void on_pB_ContinueKickOK_clicked();//保存连剔
	void on_pB_ContinueKickCancel_clicked();//取消连剔

	//void onStartStore(bool);
	void onSendPLCCommand(bool);
	void onDebugMode(bool);//气缸一直动
	void updateCyclinderSituation();
	DataFromPC_typ getPCData();//PC数值发送给PLC
	void getPLCData(void*, int, int, int, int);
public:
	//MESSAGE_HANDLER ShowFunc(void* context, DataToPC_typ);
	void connectBtnGroup();
	void setm_iCameraTotal(int index);
};

#pragma once


