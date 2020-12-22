#pragma once

#include <QtWidgets/QMainWindow>
#include <QPrinter>
#include <QPrinterInfo>
#include <QPainter>
#include <QPrintPreviewDialog>
#include <QPrintDialog>
#include "ui_PRT.h"

class PRT : public QMainWindow
{
    Q_OBJECT

public:
	PRT(QWidget *parent = Q_NULLPTR);
	void createPixCurve(QPixmap *);
	void createPixAverage(QPixmap *);
private:
	int pixWidth = 2100;
	int pixHeight = 2970;
    Ui::PRTClass ui; 
	QString m_sName; 
	QPrinter *m_prt = nullptr; 
	QPainter *painter = nullptr;
	QList<double> data_One[2];	
	double m_dmax[2];
	double m_dmin[2];
	double m_dsum[2];
	double m_dave[2];
	double m_dtheory[2];
	double m_dminoff[2];
	double m_dmaxoff[2];
public slots:

	void on_pB_Print_clicked();
	void on_pB_PrintDirect_clicked();
	void drawPic(QPrinter * pt);
};
