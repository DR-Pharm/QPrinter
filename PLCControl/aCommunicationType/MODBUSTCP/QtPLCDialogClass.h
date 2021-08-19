#pragma once
#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QTreeWidgetItem>

#include "PLCRelayHead.h"
#include "QtSocket_Class.h"
#include "mypushbutton.h"
#include "WindowOut.h"

#include <windows.h>
#include "Keyboard.h"
namespace spd = spdlog;

#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>
#include <QHBoxLayout>
using namespace QtCharts;
#include "textticker.h"

class QtPLCDialogClass : public QDialog

{
	Q_OBJECT

signals:
	void CLOSESIGNAL();
	void SHOWEVERYPLCVALUE(DataToPC_typ);
	void GETSTRING(QString);
	void SHOWPRT(bool);
	void TODATACURVE(int,float, float, float, QList<qreal>);
	void TODRAWPICTURE(QVector<QVector<float>>,QVector<QString>,int, QVector<float>);//MODE 0:one curve,1:one dataAverage,2:two curve,3:two dataAverage
	void showWindowOut(QString str);
public:
	QtPLCDialogClass(QDialog *parent = Q_NULLPTR);
	~QtPLCDialogClass();

	bool event(QEvent *event);
	void initUser();
	void initTableOfUserPermission();
	void checkPermission();
	void initTableWidget();
	void initMovie();
	void initUI();
	void inittabicon();
	void initFont();
	void initDlg();

	void setWindowMinimized();

	int showMsgBox(const char* titleStr, const char* contentStr, const char* button1Str, const char* button2Str);
	/*void showWindowOut(QString str);*/
	//ȫ������
	void SetSocket(QtSocket_Class*);
	void setStyleCommand(QPushButton*, QString, QFont, QString);

	void CompareYearMonthDay();

	QString setYearMonthDay();
	QString YearMonthDay();
	float hexTofloat(int i);
private:
	int m_flag = 0;
	MyPushButton *LanguageBtn;
	MyPushButton *ExitBtn;
	double sumNo = 0;
	int m_row = 0;
	double mi, ma;
	int maxSize;  // data ���洢 maxSize ��Ԫ��
	int maxX;
	int maxY;
	int maxSizeAve;  // data ���洢 maxSize ��Ԫ��
	int maxXAve;
	int maxYAve;

	QChart *chart;
	QChartView *chartView;
	//QSplineSeries *splineSeries;
	QLineSeries *splineSeries;
	QLineSeries *splineSeries_Average;
	QLineSeries *splineSeries_Average2;
	QScatterSeries *scatterSeries;

	QValueAxis *axisx;
	QValueAxis *axisy;

	QPoint mousePoint;
	int deskWidth;                  //������
	int deskHeight;                 //����߶�
	int frmWidth;                   //������
	int frmHeight;                  //����߶�
	QPoint movePoint;

	QString g_QSUserName;
	int g_IUserLevel;

	keyBoard *key=nullptr;
	void* ui;
	QTimer *btnTimer = nullptr;
	//DataToPC_typ *m_data;	//��ȡ��PLC����
	//WindowOut *levelOut;//showĬ��Ϊ��ģ̬modal������Ǿֲ�������������ʧ
	QString m_objname = "";
	QString m_tempname = "";
	QtSocket_Class *m_socket = nullptr;
	QString AppPath = qApp->applicationDirPath();
	DataToPC_typ *m_data = nullptr;

	QPushButton* obj = nullptr;//pushbutton le;

	QFont setupFont;
	QFont startFont;
	QFont contentFont;

	QLabel *lb_dataNow;

	QVector<float> data_One;
	//������Ч
	QPropertyAnimation * animation1 = nullptr;
	QPropertyAnimation * animation2 = nullptr;

	WindowOut *levelOut;//showĬ��Ϊ��ģ̬modal������Ǿֲ�������������ʧ

	QFont font;
	QTreeWidgetItem* checkPermissionGroup=nullptr;
	QWidget *tab=nullptr;
	QTableWidget* tableWidget= nullptr;
	QString m_SelectedName;

	QString m_gn1;
	QString m_gn2;

	int COILS = 120;
	int REGISTERS = 240;
	quint16 *dtcoils;
	quint16 *dtregisters;
	quint16 *m_Coils_Bufer = new quint16[COILS+1];
	quint16 *m_Input_Bufer = new quint16[REGISTERS+1];

	int m_InputFlag = 0;
	int m_CoilsFlag = 0;
	QString m_str_registers = ",,,,";//row four byte
	QString m_str_sendRegisters = "";
	QString m_str_coils = ",";//row 2byte but used 1byte,case bool
	QString m_str_sendCoils = "";

	int m_iDontReadCoilsFlag = 0;
	int m_iDontReadRegistersFlag = 0;
	int lg = 0;
public slots:
	DataFromPC_typ getPCParaData();
	DataFromPC_typ getPCRunData();

	void initChartOne();
	void getPLCData(void*); 
	void getPLCHolding(void*);
	void on_WriteCoils();
	void on_WriteHolding();
	void setg_IUserLevel(int);
	void on_lE_SysOveride_editingFinished();
	void on_lE_year1_editingFinished();
	void on_lE_month1_editingFinished();
	void on_lE_day1_editingFinished();
	void on_lE_hour1_editingFinished();
	void on_lE_hour2_editingFinished();
	void on_lE_minute1_editingFinished();
	/*void on_lE_RejectCount_editingFinished();
	void on_lE_ProdCount_editingFinished();
	void on_lE_TOCount_editingFinished();
	void on_lE_TUCount_editingFinished();*/
	void on_lE_minute2_editingFinished();
	void on_lE_TOverload_editingFinished();
	void on_lE_TUnderload_editingFinished();
	void on_lE_InterOverLoad_editingFinished();
	void on_lE_InterUnderLoad_editingFinished();
	void on_lE_SetPillDiam_editingFinished();
	void on_lE_PillDiamOffset_editingFinished();
	void on_lE_HardnessChkNum_editingFinished();
	void on_lE_TDemand_editingFinished();
	void on_lE_GroupSet_editingFinished();
	void on_lE_GroupCounter_editingFinished();
	void on_lE_RecipeNo_editingFinished();
	void on_lE_ThickUpperLimit_editingFinished();
	void on_lE_ThickUnderLimit_editingFinished();
	void on_lE_HMU_paraCalibForce_editingFinished();
	void on_lE_TMU_calibThickness_editingFinished();
	void on_lE_FeedOveride_editingFinished();
	void on_lE_TestInterval_editingFinished();
	void on_lE_MultiCount_editingFinished();
	void on_lE_BatchName_editingFinished();
	void on_lE_AxisFeedRelMovDistance_editingFinished();
	void on_lE_AxisSwingRelMovDistance_editingFinished();
	//void on_lE_GroupNo_editingFinished();
	//void on_cB_enable_currentIndexChanged(int index);
	void on_lE_s_trg_stop0_editingFinished();
	void on_lE_s_trg_stop1_editingFinished();
	void on_lE_s_trg_stop2_editingFinished();
	void on_lE_s_trg_stop3_editingFinished();
	void on_lE_FeedTimeOut_editingFinished();
	void on_lE_CapPickInterval_editingFinished();
	void on_lE_CapBackInterval_editingFinished();
	void on_lE_TireDelay_editingFinished();
	void on_lE_ReadDelay_editingFinished();
	void on_lE_TireWaitTime_editingFinished();
	void on_lE_paraTurnUpPosition_editingFinished();
	void on_lE_paraTurnDnPosition_editingFinished();
	void on_lE_paraPushDestPosition_editingFinished();
	void on_lE_ForceThresholdSlow_editingFinished();
	void on_lE_StopSignalDelay_editingFinished();
	void on_lE_paraTurnUpSpd_editingFinished();
	void on_lE_paraTurnDnSpd_editingFinished();
	void on_lE_HMU_PressStopPercent_editingFinished();
	void on_lE_RejectBoxFullNum_editingFinished();
	void on_pB_startSearch_clicked();
	void on_pB_copyIn_clicked();
	void on_pB_printData_clicked();
	void on_pB_printCurve_clicked();
	void on_pB_Read1_clicked();
	void on_pB_Write1_clicked();
	void on_pB_cmdScaleTire_clicked();
	/*void on_cB_paraScaleSetStable_currentIndexChanged(int index);*/
	void on_pB_cmdScaleCalibExt_clicked();
	void on_pB_cmdAxisFeedRelMov_clicked();
	void on_pB_cmdAxisFeedPosMov_clicked();
	void on_pB_cmdAxisFeedStopMov_clicked();
	void on_pB_cmdAxisSwingRelMov_clicked();
	void on_pB_cmdAxisSwingPosMov_clicked();
	void on_pB_cmdAxisSwingStopMov_clicked();
	void on_pB_cmdFeedSingle_clicked();
	void on_pB_cmdFeedSingleStop_clicked();
	void on_pB_cmdSwing_clicked();
	void on_pB_showPrt_toggled(bool checked);
	void on_pB_HMUStart_clicked();
	void on_pB_HMUStop_clicked();
	void on_pB_HMUHome_clicked();
	void on_pB_HMUZero_clicked();
	void on_pB_HMUCalibStd_clicked();
	void on_pB_HMUTurn_clicked();
	void on_pB_HMUReject_clicked();
	void on_pB_cmdStart_toggled(bool checked);
	void on_pB_TMUStart_clicked();
	void on_pB_TMUStop_clicked();
	void on_pB_TMUZero_clicked();
	void on_pB_TMUCalib_clicked();
	void pB_cmdAlarmReset();
	void pB_cmdCounterZero();
	void ChangeLanguage();
	void on_pB_cmdCapClean_clicked();
	void on_pB_cmdGetCap_clicked();
	void on_pB_cmdFeedAmount_clicked();
	void on_pB_cmdFeedFive_clicked();
	void on_pB_SetUp_toggled(bool checked);
	void on_pB_dtDlg_toggled(bool checked); 
	void dtClose();
	void startMovie();
	void pB_ChangeLanguage();
	void on_pB_enHMU_toggled(bool checked);
	void on_pB_enTMU_toggled(bool checked);
	void on_pB_cmdCapGet_toggled(bool checked);
	void on_pB_cmdCapTurnValve_toggled(bool checked);
	void on_pB_cmdCapThickValve_toggled(bool checked);
	void on_pB_cmdAlarmOut_toggled(bool checked);
	void on_pB_cmdStopSignal_clicked();
	void on_pB_cmdAlarmSignal_clicked();
	void on_pB_cmdYellowAlarmout_toggled(bool checked);
	void on_pB_cmdBaffle_toggled(bool checked);
	void on_tabWidget_currentChanged(int index);
	void on_tabWidget_PLC_currentChanged(int index);
	void updateCheckPermission(const QString & str);
	void selectedName(int r, int c);
	void btn_Enabled(int i);
	void on_pB_Users_Delete_clicked();
	void addUser();
	void on_lE_SetUserSecretNum_returnPressed();
	void on_lE_SetUserName_returnPressed();
	void on_lE_SetUserName_textChanged(const QString &arg1);
	void on_lE_SetUserSecretNum_textChanged(const QString &arg1);
	void updateParentItem(QTreeWidgetItem* item);
	void onTreeItemChanged(QTreeWidgetItem * item);
	void OnUnconnectedState();
	void OnShowState(QString str);
	void OnClosingState();
};

#pragma once


