#pragma once

#include <QObject>
#include <QDebug>
#include <QPrinter>
#include <QPrinterInfo>
#include <QPainter>
#include <QLine>
#include <QThread>
#include <QCoreApplication>
#include <QMessageBox>
#include <QDateTime>
class DrawPicture : public QObject
{
	Q_OBJECT
signals:
	void TOUI(QString);
private:
	QVector<QVector<float>> m_Thickness;
	QVector<QVector<float>> m_Hardness;

	QString m_ptnm;
	int pixWidth = 2100;
	int pixHeight = 2970;
	QString m_sName;
	QPainter *painter = nullptr;
	QPainter painterPixmap;

	QVector<QVector<float>>data;
	QVector<QString> m_gn;
	QVector<float> data_One[2];
	QString gn_One[2];
	double m_dmax[2];
	double m_dmin[2];
	double m_dsum[2];
	double m_dave[2];
	QVector<float> m_ftheory;
	double m_dtheory[2];
	double m_dminoff[2];
	double m_dmaxoff[2];

	int totalMachineCount;
	int m_iTestingCount;
	int m_iPrintCurveCount = 0;
	int m_iPrintAveCount = 0;

	bool CurveChecked;
	bool AveChecked; 
	int m_iTestingRecords;

	QVector<QString> m_CustomerName;
	QVector<QString> m_MedicineName;
	QVector<int> m_Low;
	QVector<int> m_High;
	QVector<int> m_PureShell;

	QVector<int> m_Pressure;//平均压力
	QVector<int> m_Yield;//产量
	QVector<int> m_Speed;//压片机速度
	QString m_cb;
public:
	DrawPicture(QObject *parent);
	~DrawPicture();
	void drawPic2(QPrinter * printer);
	void createTestingRecordsOnePage(QPixmap * pix);
	void createTestingRecordsOnePage2(QPixmap * pix);
	QString YearMonthDay();
	void createTestingRecords(QPixmap * pix,int pagei);
	void createTestingRecords2(QPixmap * pix, int pagei);
	void createPixCurve(QPixmap * pix);
	void createPixAverage(QPixmap * pix);
	void caculateData(QVector<QVector<float>> transData,QVector<QString>, int ivalue, int half, QVector<float> theory);

	void setCurveChecked(bool);
	void setAveChecked(bool);
	void setData(QVector<QVector<float>> sourcedata, QVector<QString>, int i, int j, QVector<float> f, QVector<QString>, QVector<QString>, QVector<int>, QVector<int>, QVector<int>,QString cb, QVector<int>, QVector<int>, QVector<int>, QVector<QVector<float>>, QVector<QVector<float>>);
public slots:
	void drawPic(QPrinter * pt);

};
