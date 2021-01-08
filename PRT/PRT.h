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
#include "Dongle.h"
#include "QWaiting.h"
#pragma comment(lib,"Dongle.lib")

#include "QtPLCControl.h"

#define STYLESHEET "QCheckBox{ background:transparent}QCheckBox::indicator {width: 40px; height: 40px; }QCheckBox::indicator:unchecked{background:url(./240.png)}QCheckBox::indicator:checked{background:url(./140.png)}"
class PRT : public QMainWindow
{
    Q_OBJECT
signals:
	void STARTCONNECTPLC(); 

protected:
	virtual void closeEvent(QCloseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

public:
	PRT(QWidget *parent = Q_NULLPTR);
	~PRT();
	//dog
	void initDog();
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
	void showWindowOut(QString str);
	//event
	bool eventFilter(QObject*, QEvent*);

private:
	Ui::PRTClass ui;
	//data calculate
	QVector<QVector<float>>data;
	int m_iDataNum;//���ݴ洢����0135...1#     2468...2#
	int m_iPrintCurveCount=0;
	int m_iPrintAveCount=0;
	int num1_Le;
	int num2_Le_2; 
	//dog
	Dongle *m_dong = nullptr;
	QStringList *lst = nullptr;
	bool m_bFlagWriteDongleFinally = false;
	//plc
	QtPLCControl *m_pPlclib = nullptr;//dll
	QThread *lib_PLCThread = nullptr;
	QDialog *dlg = nullptr;
	//printer
	DrawPicture *m_drawpicture = nullptr;
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
	WindowOut *levelOut;//showĬ��Ϊ��ģ̬modal������Ǿֲ�������������ʧ
public slots:
	//dog
	void closes(int index);
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
};
