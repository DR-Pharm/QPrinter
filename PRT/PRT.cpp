#include "PRT.h"

PRT::PRT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QPrinterInfo info;
	m_sName = info.defaultPrinterName(); // 默认打印机名字
	ui.lb_PrinterName->setText(QString::fromLocal8Bit("当前连接打印机：") + m_sName);

	m_prt = new QPrinter();
	m_prt->setPrinterName(m_sName);

	data_One << 0.369 << 0.321 << 0.332 << 0.311 << 0.399 << 0.334 << 0.321 << 0.346 << 0.389 << 0.333
		<< 0.333 << 0.333 << 0.333 << 0.333 << 0.333 << 0.369 << 0.321 << 0.332 << 0.311 << 0.399
		<< 0.334 << 0.321 << 0.346 << 0.389 << 0.333 << 0.323 << 0.333 << 0.333 << 0.333 << 0.333
		<< 0.333 << 0.369 << 0.321 << 0.332 << 0.311 << 0.399 << 0.334 << 0.321 << 0.346 << 0.389
		<< 0.333 << 0.333 << 0.333 << 0.333 << 0.333 << 0.333 << 0.333 << 0.369 << 0.321 << 0.332
		<< 0.311 << 0.399 << 0.334 << 0.321 << 0.346 << 0.389 << 0.333 << 0.333 << 0.333 << 0.333
		<< 0.333 << 0.343 << 0.333;
	m_dmax = data_One.at(0);
	m_dmin = data_One.at(0);
	m_dsum = 0;
	m_dtheory = 0.35;
	for (int i = 0; i < data_One.size(); i++) {
		if (m_dmin > data_One.at(i)) m_dmin = data_One.at(i);
		if (m_dmax < data_One.at(i)) m_dmax = data_One.at(i);
		m_dsum += data_One.at(i);
	}
	m_dave = m_dsum/data_One.size();
	m_dminoff = (m_dmin - m_dtheory) / m_dtheory*100;//%
	m_dmaxoff = (m_dmax - m_dtheory) / m_dtheory*100;
	//data_One.clear();
}
void PRT::on_pB_PrintDirect_clicked()
{
	/*直接打印*/

	QPainter painterPixmap(m_prt);
	m_prt->setResolution(QPrinter::HighResolution);
	////自定义纸张大小，特别重要，不然预览效果极差
	//printer->setPrinterName(m_sName);
	m_prt->setPageSize(QPrinter::A4);
	m_prt->setOrientation(QPrinter::Portrait);

	QPixmap pix = QPixmap(pixWidth, pixHeight);
	//这个函数算是画模板的函数吧，毕竟打印时有模板的
	createPix(&pix);
	pix.save("c:/pt.bmp");
	//纵向：Portrait 横向：Landscape
	//获取界面的图片

	painterPixmap.begin(m_prt);
	QRect rect = painterPixmap.viewport();
	float x = rect.width()*1.0 / pix.width();
	float y = rect.height()*1.0 / pix.height();
	//设置图像长宽是原图的多少倍
	painterPixmap.scale(x, y);
	painterPixmap.drawPixmap(0, 0, pix);
	painterPixmap.end();
}
void PRT::on_pB_Print_clicked()
{
	QPrintPreviewDialog preview;// 创建打印预览对话框

	preview.setWindowState(Qt::WindowMaximized);
	/*
	 * QPrintPreviewDialog类提供了一个打印预览对话框，里面功能比较全，
	 * paintRequested(QPrinter *printer)是系统提供的，
	 * 当preview.exec()执行时该信号被触发，
	 * drawPic(QPrinter *printer)是自定义的槽函数，图像的绘制就在这个函数里。
	 */
	connect(&preview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(drawPic(QPrinter*)));
	preview.exec();
}
void PRT::drawPic(QPrinter *printer)
{
	QPainter painterPixmap(printer);
	//QPrinter *printer = new QPrinter(QPrinter::HighResolution);
	printer->setResolution(QPrinter::HighResolution);
	////自定义纸张大小，特别重要，不然预览效果极差
	//printer->setPrinterName(m_sName);
	printer->setPageSize(QPrinter::A4);
	printer->setOrientation(QPrinter::Portrait);

	QPixmap pix = QPixmap(pixWidth, pixHeight);
	//这个函数算是画模板的函数吧，毕竟打印时有模板的
	createPix(&pix);
	pix.save("c:/pt.bmp");
	//纵向：Portrait 横向：Landscape
	//获取界面的图片

	//painterPixmap.begin(printer);
	QRect rect = painterPixmap.viewport();
	float x = rect.width()*1.0 / pix.width();
	float y = rect.height()*1.0 / pix.height();
	//设置图像长宽是原图的多少倍
	painterPixmap.scale(x, y);
	painterPixmap.drawPixmap(0, 0, pix);
	//painterPixmap.end();
}

void PRT::createPix(QPixmap *pix)
{
	QPainter *painter = new QPainter();
	painter->begin(pix);
	painter->setRenderHint(QPainter::Antialiasing, true);
	// 设置画笔颜色、宽度
	painter->setPen(QPen(QColor(255, 255, 255), 4));
	// 设置画刷颜色
	painter->setBrush(QColor(255, 255, 255));

	int edgeOffset = 50;
	int innerW = pixWidth - 2*edgeOffset;
	int innerH = pixHeight - 2 * edgeOffset;
	int rightW = pixWidth - edgeOffset;
	int bottomH= pixHeight - edgeOffset;

	QRect rect(0, 0, pixWidth, pixHeight);
	//整张图设置画刷白底	
	QFont font;
	font.setPointSize(20);
	font.setFamily("宋体");
	font.setItalic(true);
	painter->setFont(font);
	painter->fillRect(rect, QColor(255, 255, 255));
	painter->drawRect(rect);
	//画数据部分的线条
	painter->setPen(QPen(QColor(0, 0, 0), 3));
	QVector<QLine> lines;
	lines.append(QLine(QPoint(edgeOffset, edgeOffset), QPoint(rightW, edgeOffset)));//上边
	lines.append(QLine(QPoint(rightW, edgeOffset), QPoint(rightW, bottomH)));//右边
	lines.append(QLine(QPoint(edgeOffset, bottomH), QPoint(rightW, bottomH)));//下边
	lines.append(QLine(QPoint(edgeOffset, edgeOffset), QPoint(edgeOffset, bottomH)));//左边
	for (int i=0;i<3;i++)
	{
		lines.append(QLine(QPoint(edgeOffset, 120 + i * 60), QPoint(rightW, 120 + i * 60)));
		//名称下边
		//产品下边
		//重量栏目下边
	}
	lines.append(QLine(QPoint(edgeOffset, 515), QPoint(rightW, 515)));//重量明细下边

	lines.append(QLine(QPoint(400, 180), QPoint(400, 515)));//重量分析与每粒重量之间
	lines.append(QLine(QPoint(edgeOffset, pixHeight/2-80), QPoint(rightW, pixHeight/2 - 80)));//1#操作人签名上侧
	lines.append(QLine(QPoint(edgeOffset, pixHeight /2), QPoint(rightW, pixHeight / 2)));//1/2#分割线
	lines.append(QLine(QPoint(edgeOffset, bottomH - 80), QPoint(rightW, bottomH -80)));//2#操作人签名上侧

	//画坐标系
	painter->drawText(160, pixHeight/2-200, 50, 50, Qt::AlignVCenter, "0");//0
		//x
		//y

	int of = 10;
	lines.append(QLine(QPoint(200, 600), QPoint(200, pixHeight / 2 - 200)));//Y
	lines.append(QLine(QPoint(200-of, 600+of), QPoint(200, 600)));
	lines.append(QLine(QPoint(200+of, 600+of), QPoint(200, 600)));
	lines.append(QLine(QPoint(200, pixHeight / 2 - 200), QPoint(rightW - 150, pixHeight / 2 - 200)));//X
	lines.append(QLine(QPoint(rightW - 150 - of, pixHeight / 2 - 200 - of), QPoint(rightW - 150, pixHeight / 2 - 200)));
	lines.append(QLine(QPoint(rightW - 150 - of, pixHeight / 2 - 200 + of), QPoint(rightW - 150, pixHeight / 2 - 200)));

	painter->drawLines(lines);
	lines.clear();

	painter->setPen(QPen(QColor(0, 0, 0), 1));
	painter->drawText(100, pixHeight / 2 - 300, 150, 50, Qt::AlignVCenter, QString::number(m_dmin, 'f', 3));//MIN
	lines.append(QLine(QPoint(200, pixHeight / 2 - 275), QPoint(rightW - 250, pixHeight / 2 - 275)));//MIN
	painter->drawText(100, pixHeight / 2 - 850, 150, 50, Qt::AlignVCenter, QString::number(m_dmax, 'f', 3));//MAX
	painter->drawText(100, pixHeight / 2 - 300 - (m_dave - m_dmin) / (m_dmax - m_dmin) * 550, 150, 50, Qt::AlignVCenter, QString::number(m_dave, 'f', 3));//AVE
	painter->drawLines(lines);

	//画每粒重量格
	for (int i = 1; i < 5; i++)
	{
		lines.append(QLine(QPoint(400, 240 + i * 55), QPoint(rightW, 240 + i * 55)));
	}
	for (int i = 1; i < 16; i++)
	{
		lines.append(QLine(QPoint(400 + i * 103.125, 240), QPoint(400 + i * 103.125, 515)));
	}
	painter->drawLines(lines);
	lines.clear();

	painter->setPen(QPen(QColor(0, 0, 0), 3));


	//第一部分
	painter->drawText(0, 0, pixWidth - 1600, 50, Qt::AlignCenter, QString::fromLocal8Bit("版权所有:Dr.Pharm"));// ui->lE_unit->text());//单位名称
	//painter->drawText(0, 0, pixWidth+1400, 50, Qt::AlignCenter, "No:");	
	//painter->drawText(0, 0, pixWidth + 1100, 50, Qt::AlignCenter, QString::fromLocal8Bit("设备型号/编号:"));
	painter->drawText(50, 50, rightW + 1400, 70, Qt::AlignCenter, QString::fromLocal8Bit("设备型号/编号:1#机"));
	font.setPointSize(30);
	painter->setFont(font);
	painter->drawText(0, 0, pixWidth, 170, Qt::AlignCenter, QString::fromLocal8Bit("抽检报告"));// ui->lE_report->text());//报告名称
	font.setPointSize(20);
	painter->setFont(font);
	//第二部分

	painter->drawText(50, 120, 200, 60, Qt::AlignCenter, QString::fromLocal8Bit("产品名称:"));// +ui->lE_means->text());
	painter->drawText(50, 120, 1300, 60, Qt::AlignCenter, QString::fromLocal8Bit("产品规格:"));// +ui->lE_instrument->text());
	painter->drawText(50, 120, 2400, 60, Qt::AlignCenter, QString::fromLocal8Bit("产品批号:"));// +ui->lE_instrument->text());
	//第三部分

	painter->drawText(50, 180, 370, 60, Qt::AlignCenter, QString::fromLocal8Bit("重量分析"));
	painter->drawText(400, 180, rightW - 400, 60, Qt::AlignCenter, QString::fromLocal8Bit("每粒重量(g)"));
	//第四部分
	painter->drawText(70, 240, 400, 60, Qt::AlignVCenter, QString::fromLocal8Bit("最大值(g):") + QString::number(m_dmax, 'f', 3));
	painter->drawText(70, 295, 400, 60, Qt::AlignVCenter, QString::fromLocal8Bit("最小值(g):") + QString::number(m_dmin, 'f', 3));
	painter->drawText(70, 350, 400, 60, Qt::AlignVCenter, QString::fromLocal8Bit("平均值(g):") + QString::number(m_dave, 'f', 4));
	painter->drawText(70, 405, 400, 60, Qt::AlignVCenter, QString::fromLocal8Bit("差异值(大):") + QString::number(m_dmaxoff, 'f', 2) + "%");
	painter->drawText(70, 455, 400, 60, Qt::AlignVCenter, QString::fromLocal8Bit("差异值(小):") + QString::number(m_dminoff, 'f', 2) + "%");

	for (int i = 0; i < data_One.size(); i++) {
		painter->drawText(400+i%16* 103.125, 240+i/16%5*55, 103.125, 55, Qt::AlignCenter, QString::number(data_One.at(i), 'f', 3));
	}
	//第五部分
	painter->drawText(50, pixHeight/2 - 80, 1900, 80, Qt::AlignCenter, QString::fromLocal8Bit("签字:"));// +ui->lE_code->text());

	painter->drawText(50, pixHeight / 2 - 80, 3000, 80, Qt::AlignCenter, QString::fromLocal8Bit("日期:"));// +ui->lE_reportDate->text());
	painter->drawText(50, bottomH - 80, 1900, 80, Qt::AlignCenter, QString::fromLocal8Bit("签字:"));// +ui->lE_code->text());

	painter->drawText(50, bottomH - 80, 3000, 80, Qt::AlignCenter, QString::fromLocal8Bit("日期:"));// +ui->lE_reportDate->text());

	painter->end();
}