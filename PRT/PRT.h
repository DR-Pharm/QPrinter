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
	void createPix(QPixmap *);
private:
	int pixWidth = 2970;
	int pixHeight = 2100;
    Ui::PRTClass ui; 
	QString m_sName; 
	QPrinter *m_prt = nullptr;
public slots:

	void on_pB_Print_clicked();
	void on_pB_PrintDirect_clicked();
	void drawPic(QPrinter * pt);
};
