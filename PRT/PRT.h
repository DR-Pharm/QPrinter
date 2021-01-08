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

	void initMovie();

	~PRT();
	void initPLC();
	void initDog();
	void initData();
	void initUI();
	int showMsgBox(const char* titleStr, const char* contentStr, const char* button1Str, const char* button2Str);
	int showMsgBox2(const char * titleStr, const char * contentStr, const char * button1Str, const char * button2Str);
	void writeIni();
	bool caculateCount();
	void showWindowOut(QString str);
	void initPrinter();	
	bool eventFilter(QObject*, QEvent*);

private:
	bool m_bAltKeyPressed = false;
	QWaiting *wt;
	WindowOut *levelOut;//show默认为非模态modal，如果是局部变量会闪现消失

	Ui::PRTClass ui;

	QPoint m_offset;
	//QList<double> data_One[2];	
	QVector<QVector<float>>data;


	QString AppPath;
	int m_iDataNum;//数据存储数量0135...1#     2468...2#
	int m_iPrintCurveCount=0;
	int m_iPrintAveCount=0;

	int num1_Le;
	int num2_Le_2; 

	DrawPicture *m_drawpicture = nullptr;
	QThread *m_drawThread = nullptr;
	//dog
	Dongle *m_dong = nullptr;
	QStringList *lst = nullptr;
	bool m_bFlagWriteDongleFinally = false;

	QtPLCControl *m_pPlclib = nullptr;//dll
	QThread *lib_PLCThread = nullptr;
	QDialog *dlg = nullptr;

	QString m_sName;
	QPrinter *m_prt = nullptr;

	bool m_bCloseSignal = false;
public slots:
	void on_pB_Print_clicked();
	void on_pB_PrintDirect_clicked();
	void on_checkBox_toggled(bool checked);
	void on_checkBox_2_toggled(bool checked);
	void on_cB_Curve_toggled(bool checked);
	void on_cB_Average_toggled(bool checked);
	void closes(int index);
	void showPrintName(QString str);
	void toDraw(QPrinter * p);
};
