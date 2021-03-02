#include "DataCurve.h"
#include <QIcon>
#include <QTimer>

DataCurve::DataCurve(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowIcon(QIcon(AppPath + "/ico/dr.ico"));
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
	setWindowTitle(QString::fromLocal8Bit("���������ϸ��"));

	initChartOne();
}
////////////////////////////////����
void DataCurve::initChartOne()
{
	maxX = 41;
	maxSize = maxX - 1; // ֻ�洢���µ� 31 ������
	maxY = 255;
	splineSeries = new QLineSeries();
	splineSeries->setPointLabelsFormat("@yPoint");
	splineSeries->setPointLabelsClipping(false);
	splineSeries->setPointsVisible(true);
	splineSeries->setPointLabelsVisible(false);
	splineSeries->setName(QString::fromLocal8Bit("����������"));

	chart = new QChart();
	chart->legend()->hide();
	chart->setTitle(QString::fromLocal8Bit("����������"));

	chart->addSeries(splineSeries);

	axisx = new QValueAxis;
	axisx->setLabelFormat("%d");
	axisx->setTickCount(2);
	axisx->setRange(0, 1);
	axisx->setGridLineVisible(true);
	chart->setAxisX(axisx, splineSeries);
	chart->addAxis(axisx, Qt::AlignBottom);

	axisy = new QValueAxis;
	//axisy->setLabelFormat("%d");
	axisy->setLabelFormat("%.3f");
	axisy->setTickCount(9);
	axisy->setRange(0, 1);
	axisy->setGridLineVisible(true);
	chart->setAxisY(axisy, splineSeries);
	chart->addAxis(axisy, Qt::AlignLeft);

	chart->setTheme(QChart::ChartThemeBlueCerulean);
	chartView = new QChartView(chart);

	chartView->setRenderHint(QPainter::Antialiasing);

	ui.gridLayout_One->addWidget(chartView);
}
// 	QTimer *timerCt;
// 	timerCt = new QTimer(nullptr);
// 	bool b = connect(timerCt, SIGNAL(timeout()), this, SLOT(addAverageData()));
// 
// 	timerCt->start(5000);
// }
// void DataCurve::addAverageData()
// {
// 	dataReceived(1);
// }
void DataCurve::dataReceived(float ma, float mi, QList<qreal> lst)
{
	data_One = lst;
	if (data_One.size()<7)
	{
		axisx->setTickCount(data_One.size()+2);
	}
	else
	{
		axisx->setTickCount(9);
	}
	axisx->setRange(0, data_One.size() + 1);
	axisy->setRange(mi, ma);

	//���ݸ��������������������ɾ���������ݣ���ͷ��ʼ��
	//while (data_One.size() > maxSize) {
	//	//data.clear();//
	//	data_One.removeFirst();
	//}
	// ���汻���غ��û�б�Ҫ�������ݵ�������
	if (isVisible()) {
		splineSeries->clear();
		//scatterSeries->clear();
		int dx = 1;// maxX / (maxSize - 1);
		for (int i = 0; i < data_One.size(); ++i) {
			splineSeries->append((i + 1)*dx, data_One.at(i));
			//scatterSeries->append(i*dx, data.at(i));
		}
	}
}
DataCurve::~DataCurve()
{
}
