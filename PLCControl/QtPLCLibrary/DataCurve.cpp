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

	QStringList str1;
	str1 << QString::fromLocal8Bit("����");
	ui.tableWidget->setColumnCount(1);
	ui.tableWidget->setHorizontalHeaderLabels(str1);//��ˮƽ��ͷ ÿ�м����ڽ��
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//��������ͷ

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
	axisy->setTickCount(10);
	axisy->setRange(0.210, 0.250);
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
void DataCurve::dataReceived(int count,float value,float ma, float mi, QList<qreal> lst)
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
	axisx->setRange(0, data_One.size()+1);

	axisy->setTickCount(9);
	if (mi==ma)
	{
		axisy->setRange(0, ma);
	}
	else
	{
		axisy->setRange(mi, ma);
	}
	//���ݸ��������������������ɾ���������ݣ���ͷ��ʼ��
	//while (data_One.size() > maxSize) {
	//	//data.clear();//
	//	data_One.removeFirst();
	//}
	// ���汻���غ��û�б�Ҫ�������ݵ�������
	if (isVisible()) {
		splineSeries->clear();
		int dx = 1;// maxX / (maxSize - 1);
		float f_sum = 0;
		for (int i = 0; i < data_One.size(); ++i) {
			f_sum += data_One.at(i);
			splineSeries->append((i + 1)*dx, data_One.at(i));
			//scatterSeries->append(i*dx, data.at(i));
		}
		ui.lE_Max->setText(QString::number(ma));
		ui.lE_Min->setText(QString::number(mi));
		ui.lE_Sum->setText(QString::number(f_sum));
		ui.lE_Ave->setText(QString::number(f_sum / count, 'f', 4));
		ui.lE_Ct->setText(QString::number(count));

		ui.tableWidget->insertRow(0);
		ui.tableWidget->setVerticalHeaderItem(0, new QTableWidgetItem(QString::number(count)));
		ui.tableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(value)));
	}
}
DataCurve::~DataCurve()
{
}
