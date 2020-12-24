#pragma once

#include <QtWidgets/QMainWindow>
#include <QPrinter>
#include <QPrinterInfo>
#include <QPainter>
#include <QPrintPreviewDialog>
#include <QPrintDialog>
#include <QSettings>
#include <QRegExpValidator>
#include <QMessageBox>
#include "ui_PRT.h"
#define STYLESHEET "QCheckBox{ background:transparent}QCheckBox::indicator {width: 40px; height: 40px; }QCheckBox::indicator:unchecked{background:url(./240.png)}QCheckBox::indicator:checked{background:url(./140.png)}"
class PRT : public QMainWindow
{
    Q_OBJECT

public:
	PRT(QWidget *parent = Q_NULLPTR);
	void initPrinter();
	void initData();
	void initUI();
	int showMsgBox(const char* titleStr, const char* contentStr, const char* button1Str, const char* button2Str);
	void createPixCurve(QPixmap *);
	void createPixAverage(QPixmap *);
	void caculateData();
	void writeIni();
private:
	int pixWidth = 2100;
	int pixHeight = 2970;
    Ui::PRTClass ui; 
	QString m_sName; 
	QPrinter *m_prt = nullptr; 
	QPainter *painter = nullptr;
	//QList<double> data_One[2];	
	QVector<QVector<float>>data;
	QVector<float> data_One[2];
	double m_dmax[2];
	double m_dmin[2];
	double m_dsum[2];
	double m_dave[2];
	double m_dtheory[2];
	double m_dminoff[2];
	double m_dmaxoff[2];

	int m_iMaxPrint;//maxprintno. group_______no./2=group
	QString AppPath; 
	int m_iDataNum;
public slots:

	void on_pB_Print_clicked();
	void on_pB_PrintDirect_clicked();
	void drawPic(QPrinter * pt);
	void on_checkBox_toggled(bool checked);
	void on_checkBox_2_toggled(bool checked);
	void on_cB_Curve_toggled(bool checked);
	void on_cB_Average_toggled(bool checked);
};
