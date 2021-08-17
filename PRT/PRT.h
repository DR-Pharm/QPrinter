#pragma once

#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QPrinter>
#include <QPrinterInfo>
#include <QPainter>
#include <QPrintPreviewDialog>
#include <QPageSetupDialog>
#include <QPrintDialog>
#include <QSettings>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QMouseEvent>
#include <QDir>
#include <QMovie>
#include <QFileInfoList>
#include "ui_PRT.h"
#include "DrawPicture.h"
#include "WindowOut.h"
#include "QWaiting.h"
#include <QVector>
#include "QtLoginDlg.h"

#include "QtPLCControl.h"
#pragma comment(lib,"Qt_PLC_ConnectLIB.lib")

#define STYLESHEET "QCheckBox{ background:transparent}QCheckBox::indicator {width: 40px; height: 40px; }QCheckBox::indicator:unchecked{background:url(./240.png)}QCheckBox::indicator:checked{background:url(./140.png)}"
class PRT : public QMainWindow
{
    Q_OBJECT
signals:
	void STARTCONNECTPLC();
	void MINI(); 
	void SETUSERLEVEL(int);
protected:
	void closeEvent(QCloseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
public:
	PRT(QWidget *parent = Q_NULLPTR);
	~PRT();
	//PLC
	void initPLC();
	//printer
	void initPrinter();
	//data calculate
	void initData();
	bool caculateCount();
	//ui
	void initUI();
	void writeIni();
	void judgeLabelText(int index);
	//popup window
	int showMsgBox(const char* titleStr, const char* contentStr, const char* button1Str, const char* button2Str);

	//event
	bool eventFilter(QObject*, QEvent*);
	QLabel *lbDr = nullptr;
private:
	Ui::PRTClass ui;
	//data calculate
	QVector<QVector<float>>data;
	QVector<QString> gn;
	QVector<float> theory;
	int m_iDataNum;//数据存储数量0135...1#     2468...2#
	int m_iCurrentGetDataNo = 0;
	int m_iPrintCurveCount=0;
	int m_iPrintAveCount=0;
	int num1_Le;
	int num2_Le_2; 
	//plc
	QtPLCControl *m_pPlclib = nullptr;//dll
	QThread *lib_PLCThread = nullptr;
	QDialog *dlg = nullptr;
	QTimer *tm_ReConnect = nullptr;
	//printer
	DrawPicture *m_drawpicture = nullptr;
	QThread *m_drawpictureThread = nullptr;
	int m_iPrintMode;
	QString m_sName;
	QPrinter *m_prt = nullptr;
	//system
	QString AppPath;
	QPoint m_offset;
	bool m_bCloseSignal = false;
	QSettings *RWini;	
	bool m_bAltKeyPressed = false;
	QWaiting *wt;
	WindowOut *levelOut;//show默认为非模态modal，如果是局部变量会闪现消失
	int lg = 0;
public slots:	
	void showWindowOut(QString str);
	//printer
	void showPrintName(QString str);
	void toDraw(QPrinter * p);
	//ui slots
	void on_pB_Print_clicked();
	void on_pB_PrintDirect_clicked();
	void on_checkBox_toggled(bool checked);
	void on_checkBox_2_toggled(bool checked);
	void on_cB_Curve_toggled(bool checked);
	void on_cB_Average_toggled(bool checked);
	void on_cB_PrintMode_currentIndexChanged(int index);
	void on_ToClose();
	void getVec(QVector<QVector<float>>, QVector<QString>,int, QVector<float> teo);
	void SuccessConnect();
	void ErrorConnect();
	void EmitReconnect();
	void showPrt(bool);
};
