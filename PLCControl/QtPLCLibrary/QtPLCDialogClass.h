#pragma once
#include <QDebug>
#include <QLabel>
#include <QPainter>
#include "PLCRelayHead.h"
#include "QtSocket_Class.h"
#include "mypushbutton.h"
#include "WindowOut.h"
namespace spd = spdlog;

class QtPLCDialogClass : public QDialog

{
	Q_OBJECT

signals:
	void CLOSESIGNAL();
	void SHOWEVERYPLCVALUE(DataToPC_typ);
	void GETSTRING(QString);
	void SHOWPRT(bool);
public:
	QtPLCDialogClass(QDialog *parent = Q_NULLPTR);
	~QtPLCDialogClass();
	void initMovie();
	void initUI();
	void inittabicon();
	void initFont();
	void initDlg();
	void createPixCurve(QPixmap * pix);
	void setWindowMinimized();
	int showMsgBox(QMessageBox::Icon icon, const char* titleStr, const char* contentStr, const char* button1Str, const char* button2Str);

	void showWindowOut(QString str);
	//全是中文
	void SetSocket(QtSocket_Class*);
	void setStyleCommand(QPushButton*, QString, QFont, QString);

private:
	void* ui;
	QDialog *m_dtDlg = nullptr;
	bool m_currentSituationOfCyclinder = true;
	QTimer *btnTimer = nullptr;
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
	QFont contentFont;

	QLabel *lb_dataNow;

	//弹跳特效
	QPropertyAnimation * animation1 = nullptr;
	QPropertyAnimation * animation2 = nullptr;

	QPainter *painter = nullptr; 
	QPixmap *pix = nullptr; 
	QLabel *lb = nullptr;

	WindowOut *levelOut;//show默认为非模态modal，如果是局部变量会闪现消失
public slots:

	DataFromPC_typ getPCParaData();
	DataFromPC_typ getPCRunData();

	void getPLCData(void*, int, int, int, int);

	void on_lE_SysOveride_editingFinished();
	/*passcount
	void on_lE_RejectCount_editingFinished();
	void on_lE_ProdCount_editingFinished();
	void on_lE_TOCount_editingFinished();
	void on_lE_TUCount_editingFinished();*/
	void on_lE_TOverload_editingFinished();
	void on_lE_TUnderload_editingFinished();
	void on_lE_InterOverLoad_editingFinished();
	void on_lE_InterUnderLoad_editingFinished();
	void on_lE_TDemand_editingFinished();
	void on_cB_TireMode_currentIndexChanged(int index);
	void on_lE_GroupSet_editingFinished();
	void on_lE_TestInterval_editingFinished();
	void on_lE_BatchName_editingFinished();
	//void on_lE_GroupNo_editingFinished();

	//void on_cB_enable_currentIndexChanged(int index);
	void on_lE_s_trg_stop0_editingFinished();
	void on_lE_s_trg_stop1_editingFinished();
	void on_lE_FeedTimeOut_editingFinished();
	void on_lE_CapPickInterval_editingFinished();
	void on_lE_CapBackInterval_editingFinished();
	void on_lE_TireDelay_editingFinished();
	void on_lE_ReadDelay_editingFinished();
	void on_lE_TireWaitTime_editingFinished();
	void on_lE_StopSignalDelay_editingFinished();

	void on_pB_cmdScaleRead_clicked();
	void on_pB_cmdScaleTire_clicked();
	void on_pB_cmdScaleSetStable_clicked();
	void on_cB_paraScaleSetStable_currentIndexChanged(int index);
	void on_pB_cmdScaleCalibExt_clicked();
	void on_pB_cmdAxisFeedJogPos_clicked();
	void on_pB_cmdAxisFeedJogNeg_clicked();
	void on_pB_cmdAxisFeedRelMov_clicked();
	void on_pB_cmdAxisFeedPosMov_clicked();
	void on_pB_cmdAxisFeedStopMov_clicked();
	void on_pB_cmdAxisSwingJogPos_clicked();
	void on_pB_cmdAxisSwingJogNeg_clicked();
	void on_pB_cmdAxisSwingRelMov_clicked();
	void on_pB_cmdAxisSwingPosMov_clicked();
	void on_pB_cmdAxisSwingStopMov_clicked();
	void on_pB_cmdFeedSingle_clicked();
	void on_pB_cmdFeedSingleStop_clicked();
	void on_pB_cmdSwing_clicked();

	void on_pB_showPrt_toggled(bool checked);

	void on_pB_cmdStart_toggled(bool checked);
	void on_pB_cmdAlarmReset_clicked();
	void on_pB_cmdCounterZero_clicked();
	void on_pB_cmdCapClean_clicked();
	void on_pB_cmdAlogtest_clicked();
	void on_pB_SetUp_toggled(bool checked);
	void on_pB_dtDlg_toggled(bool checked); 
	void dtClose();
	void startMovie();
	void on_pb_cmdReject_toggled(bool checked);
	void on_pb_cmdChannelSwith_toggled(bool checked);
	void on_pb_cmdVaccum_toggled(bool checked);
	void on_pb_cmdCapGet_toggled(bool checked);
	void on_pb_cmdCapGetValve_toggled(bool checked);
	void on_pb_cmdCapBackValve_toggled(bool checked);
	void on_pb_cmdAlarmOut_toggled(bool checked);
	void on_pb_cmdStopSignal_toggled(bool checked);
	void on_pb_cmdAlarmSignal_toggled(bool checked);
	void on_pb_cmdYellowAlarmout_toggled(bool checked);
	void on_pb_cmdBaffle_toggled(bool checked);
	void on_tabWidget_currentChanged(int index);
	void on_tabWidget_PLC_currentChanged(int index);
};

#pragma once


