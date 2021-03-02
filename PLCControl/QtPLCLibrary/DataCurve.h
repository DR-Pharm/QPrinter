#pragma once

#include <QDialog>
#include "ui_DataCurve.h"
#include <QChartView>
#include <QChart>
#include <QSplineSeries>
#include <QScatterSeries>
#include <QValueAxis>
#include <QHBoxLayout>
using namespace QtCharts;

class DataCurve : public QDialog
{
	Q_OBJECT

public:
	DataCurve(QWidget *parent = Q_NULLPTR);
	void initChartOne();
	~DataCurve();

public slots:
	//void addAverageData();
	void dataReceived(float, float, QList<qreal>);
private:
	Ui::DataCurve ui;
	QString AppPath = qApp->applicationDirPath();
	
	int maxSize;  // data ���洢 maxSize ��Ԫ��
	int maxX;
	int maxY;
	int maxSizeAve;  // data ���洢 maxSize ��Ԫ��
	int maxXAve;
	int maxYAve;

	QList<double> data_One;// �洢ҵ�����ݵ� list

	QChart *chart;
	QChartView *chartView;
	//QSplineSeries *splineSeries;
	QLineSeries *splineSeries;
	QLineSeries *splineSeries_Average;
	QLineSeries *splineSeries_Average2;
	QScatterSeries *scatterSeries;

	QValueAxis *axisx;
	QValueAxis *axisy;
};
