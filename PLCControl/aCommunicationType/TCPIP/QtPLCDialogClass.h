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
#include <QListWidgetItem>
using namespace QtCharts;

class QtPLCDialogClass : public QDialog

{
	Q_OBJECT

signals:
	void CLOSESIGNAL();
	void SHOWEVERYPLCVALUE(DataToPC_typ);
	void GETSTRING(QString);
	void SHOWPRT(bool);
	void TODATACURVE(int,float, float, float, QList<qreal>);
	void TODRAWPICTURE(int,QString,int p1,int p2,QString pdfpath);//MODE 0:one curve,1:one dataAverage,2:two curve,3:two dataAverage
	void showWindowOut(QString str);
public:
	QtPLCDialogClass(QDialog *parent = Q_NULLPTR);
	~QtPLCDialogClass();
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
	//void showWindowOut(QString str);
	//全是中文
	void SetSocket(QtSocket_Class*);
	void setStyleCommand(QPushButton*, QString, QFont, QString);

	void CompareYearMonthDay();

	void BeforePrint();
	QString setYearMonthDay();
	QString LEADOUTYMD();
	QString YearMonthDay();
	void SWITCHOSK();//快捷键
	QString gettime();
private:
	QString m_sTempPathForLeadout="";
	bool m_bFeedModeFlag1 = 0;
	bool m_bFeedModeFlag2 = 0;
	QString m_cn;
	QString m_mn;
	int m_l;
	int m_h;
	int m_ps; 
	int m_speed;
	int	m_yield;
	int m_pressure;

	int m_iHideprint1;
	int m_iHideprint2;

	QString cb;//第一位打印哪个 0曲线 1试机记录；第二位打印哪种试机记录 0胶囊 1片剂
	int m_iAutoUpdateFlag = 0;
	MyPushButton *LanguageBtn;
	MyPushButton *ExitBtn;
	double sumNo = 0;
	int m_index = 0;
	int m_row = 0;
	double mi, ma;
	int maxSize;  // data 最多存储 maxSize 个元素
	int maxX;
	int maxY;
	int maxSizeAve;  // data 最多存储 maxSize 个元素
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
	int deskWidth;                  //桌面宽度
	int deskHeight;                 //桌面高度
	int frmWidth;                   //窗体宽度
	int frmHeight;                  //窗体高度
	QPoint movePoint;

	QString g_QSUserName;
	int g_IUserLevel;

	keyBoard *key=nullptr;
	void* ui;
	QTimer *btnTimer = nullptr;
	//DataToPC_typ *m_data;	//获取的PLC数据
	//WindowOut *levelOut;//show默认为非模态modal，如果是局部变量会闪现消失
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
	//弹跳特效
	QPropertyAnimation * animation1 = nullptr;
	QPropertyAnimation * animation2 = nullptr;

	WindowOut *levelOut;//show默认为非模态modal，如果是局部变量会闪现消失

	QFont font;
	QTreeWidgetItem* checkPermissionGroup=nullptr;
	QWidget *tab=nullptr;
	QTableWidget* tableWidget= nullptr;
	QString m_SelectedName;

	QString m_gn1;
	QString m_gn2;
	int lg = 0;
	bool leflag = 0;
	int m_iFeedMode = 23;
	bool m_b = 1;
	QString sp;
	int m_istartFlag = 0;
public slots:

	void ErrorConnect();
	DataFromPC_typ getPCParaData();
	DataFromPC_typ getPCRunData();

	void initChartOne();


	void getPLCData(void*);

	void on_pB_keyboard_clicked();

	void on_Input(bool checked);


	void getUdisk();
	void on_pB_LeadOut_clicked();

	void setg_IUserLevel(int);

	void on_lE_SysOveride_editingFinished();
	void OnGetLeadoutPath(QString str);
	void on_lE_year1_editingFinished();
	void on_lE_month1_editingFinished();
	void on_lE_day1_editingFinished();
	void on_lE_hour1_editingFinished();
	void on_lE_hour2_editingFinished();
	void on_lE_minute1_editingFinished();
	/*passcount
	void on_lE_RejectCount_editingFinished();
	void on_lE_ProdCount_editingFinished();
	void on_lE_TOCount_editingFinished();
	void on_lE_TUCount_editingFinished();*/
	void on_lE_minute2_editingFinished();
	void on_lE_TOverload_editingFinished();
	void on_lE_TUnderload_editingFinished();
	void on_lE_InterOverLoad_editingFinished();
	void on_lE_InterUnderLoad_editingFinished();
	void on_lE_TDemand_editingFinished();
	void on_cB_TireMode_currentIndexChanged(int index);
	void on_lE_GroupSet_editingFinished();
	void on_lE_FeedOveride_editingFinished();
	void on_lE_TestInterval_editingFinished();
	void on_lE_MultiCount_editingFinished();
	void on_lE_BatchName_textChanged(const QString & arg1);
	void on_lE_BatchName_editingFinished();

	void on_cB_Feedmode_currentIndexChanged(int index);

	void on_lE_AxisFeedRelMovDistance_editingFinished();
	void on_lE_AxisSwingRelMovDistance_editingFinished();
	//void on_lE_GroupNo_editingFinished();

	//void on_cB_enable_currentIndexChanged(int index);
	void on_lE_s_trg_stop0_editingFinished();
	void on_lE_s_trg_stop1_editingFinished();
	void on_lE_Feed_shakeoffset_editingFinished();
	void on_lE_FeedTimeOut_editingFinished();
	void on_lE_CapPickInterval_editingFinished();
	void on_lE_CapBackInterval_editingFinished();
	void on_lE_TireDelay_editingFinished();
	void on_lE_ReadDelay_editingFinished();
	void on_lE_TireWaitTime_editingFinished();
	void on_lE_StopSignalDelay_editingFinished();

	void on_pB_startSearch_clicked();
	void on_lW_data_itemDoubleClicked(QListWidgetItem * item);
	void on_lW_data_itemClicked(QListWidgetItem * item);
	void on_pB_copyIn_clicked();
	void on_pB_printData_clicked();


	void on_pB_printTestingRecords_clicked();

	void on_pB_printCurve_clicked();

	void on_pB_Read1_clicked();

	void on_pB_Read2_clicked();

	void on_pB_Write1_clicked();

	void on_pB_Write2_clicked();

	void on_pB_cmdScaleRead_clicked();
	void on_pB_cmdScaleTire_clicked();
	void on_pB_cmdScaleSetStable_clicked();
	/*void on_cB_paraScaleSetStable_currentIndexChanged(int index);*/
	void on_pB_cmdScaleCalibExt_clicked();
	void on_pB_cmdAxisFeedJogPos_pressed();
	void on_pB_cmdAxisFeedJogPos_released();
	void on_pB_cmdAxisFeedJogNeg_pressed();
	void on_pB_cmdAxisFeedJogNeg_released();
	void on_pB_cmdAxisFeedRelMov_clicked();
	void on_pB_cmdAxisFeedPosMov_clicked();
	void on_pB_cmdAxisFeedStopMov_clicked();
	void on_pB_cmdAxisSwingJogPos_pressed();
	void on_pB_cmdAxisSwingJogPos_released();
	void on_pB_cmdAxisSwingJogNeg_pressed();
	void on_pB_cmdAxisSwingJogNeg_released();
	void on_pB_cmdAxisSwingRelMov_clicked();
	void on_pB_cmdAxisSwingPosMov_clicked();
	void on_pB_cmdAxisSwingStopMov_clicked();
	void on_pB_cmdFeedSingle_clicked();
	void on_pB_cmdFeedSingleStop_clicked();
	void on_pB_cmdSwing_clicked();
	void on_pB_ChangeLanguage();
	void on_pB_inquirecheckable_toggled(bool checked);
	void on_pB_showPrt_toggled(bool checked);

	void on_gB_update_toggled(bool arg1);

	void on_pB_cmdStartcheckable_toggled(bool checked);
	void on_pB_cmdAlarmReset_clicked();
	void on_pB_cmdCounterZero_clicked();
	void ChangeLanguage();
	void on_pB_cmdCapClean_clicked();
	void on_pB_cmdAlogtest_clicked();
	void on_pB_cmdFeedShake_clicked();
	void on_pB_cmdFeedshakestop_clicked();
	void on_pB_cmdFeedshakelevel_clicked();
	void on_pB_cmdFeedhome_clicked();
	void on_pB_cmdFeedFive_clicked();
	void on_pB_cmdFeedShakefive_clicked();
	void on_pB_SetUpcheckable_toggled(bool checked);
	void on_pB_dtDlgcheckable_toggled(bool checked);
	void dtClose();
	void startMovie();

	void on_pb_cmdRejectcheckable_toggled(bool checked);
	void on_pb_cmdChannelSwithcheckable_toggled(bool checked);
	void on_pb_cmdVaccumcheckable_toggled(bool checked);
	void on_pb_cmdCapGetcheckable_toggled(bool checked);
	void on_pb_cmdCapGetValvecheckable_toggled(bool checked);
	void on_pb_cmdCapBackValvecheckable_toggled(bool checked);
	void on_pb_cmdAlarmOutcheckable_toggled(bool checked);
	void on_pb_cmdStopSignalcheckable_toggled(bool checked);
	void on_pb_cmdAlarmSignalcheckable_toggled(bool checked);
	void on_pb_cmdYellowAlarmoutcheckable_toggled(bool checked);
	void on_pb_cmdBafflecheckable_toggled(bool checked);
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
	void OnConnectingState();
	void OnConnectedState();
	void OnClosingState();
};

#pragma once


