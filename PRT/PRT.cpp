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


	data_One[0] << 0.369 << 0.321 << 0.332 << 0.311 << 0.399 << 0.334 << 0.321 << 0.346 << 0.389 << 0.333
		<< 0.333 << 0.333 << 0.333 << 0.333 << 0.333 << 0.369 << 0.321 << 0.332 << 0.311 << 0.399
		<< 0.334 << 0.321 << 0.346 << 0.389 << 0.333 << 0.323 << 0.333 << 0.333 << 0.333 << 0.333
		<< 0.333 << 0.369 << 0.321 << 0.332 << 0.311 << 0.399 << 0.334 << 0.321 << 0.346 << 0.389
		<< 0.333 << 0.333 << 0.333 << 0.333 << 0.333 << 0.333 << 0.333 << 0.369 << 0.321 << 0.332
		<< 0.311 << 0.399 << 0.334 << 0.321 << 0.346 << 0.389 << 0.333 << 0.333 << 0.333 << 0.333
		<< 0.333 << 0.343 << 0.333 << 0.319;
	data_One[1] << 0.220 << 0.300 << 0.300 << 1.0 << 2.0 << 3.5;
	for (int i = 0; i < 2; i++)
	{
		m_dtheory[i] = 0.35;
		if (data_One[i].size() == 0)
		{
		}
		else
		{
			m_dmax[i] = data_One[i].at(0);
			m_dmin[i] = data_One[i].at(0);
			m_dsum[i] = 0;
			for (int j = 0; j < data_One[i].size(); j++) {
				if (m_dmin[i] > data_One[i].at(j)) m_dmin[i] = data_One[i].at(j);
				if (m_dmax[i] < data_One[i].at(j)) m_dmax[i] = data_One[i].at(j);
				m_dsum[i] += data_One[i].at(j);
			}
			m_dave[i] = m_dsum[i] / data_One[i].size();
			m_dminoff[i] = (m_dmin[i] - m_dtheory[i]) / m_dtheory[i] * 100;//%
			m_dmaxoff[i] = (m_dmax[i] - m_dtheory[i]) / m_dtheory[i] * 100;
		}
	}
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
	int innerW = pixWidth - 2 * edgeOffset;
	int inner50percentW = innerW / 2;
	int innerH = pixHeight - 2 * edgeOffset;
	int inner50percentH = innerH / 2;
	int rightW = pixWidth - edgeOffset;
	int bottomH = pixHeight - edgeOffset;
	int firstLine = 120;//大标题下面
	int weightTop = firstLine + 60;
	int weightMiddle = firstLine + 2 * 60;
	int weightRowCount = 8;
	int weightRowAve = 55;
	int betweenweight = weightMiddle + weightRowAve * weightRowCount;
	int weightColumnCount = 10;
	float weightColumnAve = (rightW - edgeOffset)*1.0 / weightColumnCount;//12个格子
	int weightBottom = betweenweight + 180;


	//坐标系
	int of = 10;//箭头
	int basePointX = 200;
	int basePointY = pixHeight / 2 - 150;
	int XRight = rightW - 150;
	int dotLineRight = XRight - 75;
	int YTop = weightBottom + 100;
	int dotLineUp = YTop + 25;

	//实际绘图内
	int actualTop = YTop + 50;
	int actualBottom = basePointY - 50;
	int actualLeft = basePointX + 50;
	int actualRight = dotLineRight - 25;
	int actualWidth = actualRight - actualLeft;
	int actualHight = actualBottom - actualTop;
	int YActualLength = actualBottom - actualTop;

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

	int totalMachineCount = 0;
	for (; totalMachineCount < 2; totalMachineCount++)
	{
		int simpleFun = inner50percentH * totalMachineCount;
		lines.append(QLine(QPoint(edgeOffset, edgeOffset), QPoint(rightW, edgeOffset)));//上边
		lines.append(QLine(QPoint(rightW, edgeOffset), QPoint(rightW, bottomH)));//右边
		lines.append(QLine(QPoint(edgeOffset, bottomH), QPoint(rightW, bottomH)));//下边
		lines.append(QLine(QPoint(edgeOffset, edgeOffset), QPoint(edgeOffset, bottomH)));//左边
		for (int i = 0; i < 3; i++)
		{
			lines.append(QLine(QPoint(edgeOffset, firstLine + i * 60 + simpleFun), QPoint(rightW, firstLine + i * 60 + simpleFun)));//名称下边//产品下边//重量栏目下边	
		}
		for (int i = 0; i < 4; i++)
		{
			if (i != 2)
			{
				lines.append(QLine(QPoint(edgeOffset, betweenweight + i * 60 + simpleFun), QPoint(rightW, betweenweight + i * 60 + simpleFun)));//每粒重量下边
			}
		}
		//lines.append(QLine(QPoint(betweenweight, weightTop), QPoint(betweenweight, weightBottom)));//重量分析与每粒重量之间
		lines.append(QLine(QPoint(edgeOffset, pixHeight / 2 - 80 + simpleFun), QPoint(rightW, pixHeight / 2 - 80 + simpleFun)));//1#操作人签名上侧
		lines.append(QLine(QPoint(edgeOffset, pixHeight / 2), QPoint(rightW, pixHeight / 2)));//1/2#分割线
		//lines.append(QLine(QPoint(edgeOffset, bottomH - 80), QPoint(rightW, bottomH -80)));//2#操作人签名上侧


		//画坐标系

		lines.append(QLine(QPoint(basePointX, basePointY + simpleFun), QPoint(basePointX, YTop + simpleFun)));//Y
		lines.append(QLine(QPoint(basePointX - of, YTop + of + simpleFun), QPoint(basePointX, YTop + simpleFun)));
		lines.append(QLine(QPoint(basePointX + of, YTop + of + simpleFun), QPoint(basePointX, YTop + simpleFun)));
		lines.append(QLine(QPoint(basePointX, basePointY + simpleFun), QPoint(XRight, basePointY + simpleFun)));//X
		lines.append(QLine(QPoint(XRight - of, basePointY - of + simpleFun), QPoint(XRight, basePointY + simpleFun)));
		lines.append(QLine(QPoint(XRight - of, basePointY + of + simpleFun), QPoint(XRight, basePointY + simpleFun)));

		painter->drawLines(lines);
		lines.clear();

		painter->setPen(QPen(QColor(0, 0, 0), 1, Qt::DashLine));

		lines.append(QLine(QPoint(edgeOffset, pixHeight / 2 + 5), QPoint(rightW, pixHeight / 2 + 5)));//1/2#分割线
		lines.append(QLine(QPoint(edgeOffset, pixHeight / 2 - 5), QPoint(rightW, pixHeight / 2 - 5)));//1/2#分割线
		//lines   200,rightW-250 pixHeight/2-825 pixHeight/2-275   250start point
		painter->drawText(basePointX - 40, basePointY + simpleFun, 50, 50, Qt::AlignVCenter, "0");//0
		if (data_One[totalMachineCount].size() > 0)
		{

			if (m_dmin[totalMachineCount] == m_dmax[totalMachineCount])//min==max
			{
				painter->drawText(100, actualTop + actualHight / 2 - 25 + simpleFun, 150, 50, Qt::AlignVCenter, QString::number(m_dmax[totalMachineCount], 'f', 3));//only one
				lines.append(QLine(QPoint(basePointX - 5, actualTop + actualHight / 2 + simpleFun), QPoint(dotLineRight, actualTop + actualHight / 2 + simpleFun)));//only one
			}
			else
			{
				painter->drawText(100, actualBottom - 25 + simpleFun, 150, 50, Qt::AlignVCenter, QString::number(m_dmin[totalMachineCount], 'f', 3));//MIN
				painter->drawText(100, actualTop - 25 + simpleFun, 150, 50, Qt::AlignVCenter, QString::number(m_dmax[totalMachineCount], 'f', 3));//MAX
				painter->drawText(80, actualBottom - 25 + simpleFun - (m_dave[totalMachineCount] - m_dmin[totalMachineCount]) / (m_dmax[totalMachineCount] - m_dmin[totalMachineCount]) * YActualLength, 150, 50, Qt::AlignVCenter, QString::number(m_dave[totalMachineCount], 'f', 4));//AVE			
				lines.append(QLine(QPoint(basePointX - 5, actualBottom + simpleFun), QPoint(dotLineRight, basePointY - 50 + simpleFun)));//MIN
				lines.append(QLine(QPoint(basePointX - 5, actualTop + simpleFun), QPoint(dotLineRight, actualTop + simpleFun)));//MAX
				lines.append(QLine(QPoint(basePointX - 5, actualBottom + simpleFun - (m_dave[totalMachineCount] - m_dmin[totalMachineCount]) / (m_dmax[totalMachineCount] - m_dmin[totalMachineCount]) * YActualLength), QPoint(dotLineRight, actualBottom + simpleFun - (m_dave[totalMachineCount] - m_dmin[totalMachineCount]) / (m_dmax[totalMachineCount] - m_dmin[totalMachineCount]) * YActualLength)));//AVE
			}
			painter->drawText(100, YTop - 50 + simpleFun, 150, 50, Qt::AlignVCenter, QString::fromLocal8Bit("重量(g)"));//重量
			painter->drawText(XRight, basePointY + simpleFun, 150, 50, Qt::AlignVCenter, QString::fromLocal8Bit("次数(次)"));//粒数


			if (data_One[totalMachineCount].size() > 1)
			{
				painter->drawText(actualLeft - 25, basePointY + simpleFun, 50, 50, Qt::AlignCenter, "1");//1
				painter->drawText(actualRight - 25, basePointY + simpleFun, 50, 50, Qt::AlignCenter, QString::number(data_One[totalMachineCount].size()));//size()
				lines.append(QLine(QPoint(basePointX + 50, basePointY + 5 + simpleFun), QPoint(basePointX + 50, dotLineUp + simpleFun)));//1111111111
				lines.append(QLine(QPoint(dotLineRight - 25, basePointY + 5 + simpleFun), QPoint(dotLineRight - 25, dotLineUp + simpleFun)));//808080808080
			}
			else
			{
				painter->drawText(actualLeft + actualWidth / 2 - 25, basePointY + simpleFun, 50, 50, Qt::AlignCenter, "1");//1
				lines.append(QLine(QPoint(actualLeft + actualWidth / 2, basePointY + 5 + simpleFun), QPoint(actualLeft + actualWidth / 2, dotLineUp + simpleFun)));//1111111111
			}

			painter->drawLines(lines);
			lines.clear();

			if (data_One[totalMachineCount].size() > 1)
			{
				//曲线
				painter->setPen(QPen(QColor(0, 0, 0), 2));

				for (int i = 0; i < data_One[totalMachineCount].size() - 1; i++)
				{
					if (m_dmin[totalMachineCount] != m_dmax[totalMachineCount])
					{
						lines.append(QLine(QPoint(actualLeft + actualWidth * 1.0 / (data_One[totalMachineCount].size() - 1)*i, actualBottom + simpleFun - (data_One[totalMachineCount].at(i) - m_dmin[totalMachineCount])*1.0 / (m_dmax[totalMachineCount] - m_dmin[totalMachineCount]) * actualHight), QPoint(actualLeft + actualWidth * 1.0 / (data_One[totalMachineCount].size() - 1)*(i + 1), actualBottom + simpleFun - (data_One[totalMachineCount].at(i + 1) - m_dmin[totalMachineCount])*1.0 / (m_dmax[totalMachineCount] - m_dmin[totalMachineCount]) * actualHight)));

					}
					else
					{
						lines.append(QLine(QPoint(actualLeft, actualTop + actualHight / 2 + simpleFun), QPoint(actualRight, actualTop + actualHight / 2 + simpleFun)));
					}
				}

				painter->drawLines(lines);
				lines.clear();
			}
		}
		painter->setPen(QPen(QColor(0, 0, 0), 1));
		//画重量结果
		for (int i = 1; i < 4; i++)
		{
			lines.append(QLine(QPoint(edgeOffset + innerW * 1.0 / 4 * i, betweenweight + 60 + simpleFun), QPoint(edgeOffset + innerW * 1.0 / 4 * i, weightBottom + simpleFun)));
		}
		lines.append(QLine(QPoint(edgeOffset, betweenweight + 2 * 60 + simpleFun), QPoint(rightW, betweenweight + 2 * 60 + simpleFun)));//每粒重量下边
		//画每粒重量格
		for (int i = 1; i < weightRowCount; i++)
		{
			lines.append(QLine(QPoint(edgeOffset, weightMiddle + i * weightRowAve + simpleFun), QPoint(rightW, weightMiddle + i * weightRowAve + simpleFun)));
		}
		for (int i = 1; i < weightColumnCount; i++)
		{
			lines.append(QLine(QPoint(edgeOffset + i * weightColumnAve, weightMiddle + simpleFun), QPoint(edgeOffset + i * weightColumnAve, betweenweight + simpleFun)));
		}
		for (int i = 0; i < weightColumnCount; i++)//order no.
		{
			lines.append(QLine(QPoint(edgeOffset + i * weightColumnAve + 60, weightMiddle + simpleFun), QPoint(edgeOffset + i * weightColumnAve + 60, betweenweight + simpleFun)));
		}
		painter->drawLines(lines);
		lines.clear();

		painter->setPen(QPen(QColor(0, 0, 0), 3));


		//第一部分
		if (totalMachineCount == 0)
		{
			painter->drawText(0, 0 + simpleFun, pixWidth - 1600, 50, Qt::AlignCenter, QString::fromLocal8Bit("版权所有:Dr.Pharm"));// ui->lE_unit->text());//单位名称	
			font.setPointSize(30);
			painter->setFont(font);
			painter->drawText(0, 0 + simpleFun, pixWidth, 170, Qt::AlignCenter, QString::fromLocal8Bit("抽检报告"));// ui->lE_report->text());//报告名称
		}
		font.setPointSize(20);
		painter->setFont(font);
		int machnum = totalMachineCount + 1;
		painter->drawText(50, 50 + simpleFun, rightW + 1400, 70, Qt::AlignCenter, QString::fromLocal8Bit("设备型号/编号:") + QString::number(machnum) + QString::fromLocal8Bit("#机"));

		//第二部分

		painter->drawText(100, 120 + simpleFun, 500, 60, Qt::AlignVCenter, QString::fromLocal8Bit("产品名称:红素片"));// +ui->lE_means->text());
		painter->drawText(800, 120 + simpleFun, 500, 60, Qt::AlignVCenter, QString::fromLocal8Bit("产品规格:一号片"));// +ui->lE_instrument->text());
		painter->drawText(1500, 120 + simpleFun, 500, 60, Qt::AlignVCenter, QString::fromLocal8Bit("产品批号:123456789"));// +ui->lE_instrument->text());
		//第三部分

		painter->drawText(edgeOffset, weightTop + simpleFun, innerW, 60, Qt::AlignCenter, QString::fromLocal8Bit("每粒重量(g)"));
		painter->drawText(edgeOffset, betweenweight + simpleFun, innerW, 60, Qt::AlignCenter, QString::fromLocal8Bit("重量结果"));
		//第四部分 数据
		//lines.append(QLine(QPoint(edgeOffset + innerW * 1.0 / 4 * i, betweenweight + 60 + simpleFun), QPoint(edgeOffset + innerW * 1.0 / 4 * i, weightBottom + simpleFun)));
		if (data_One[totalMachineCount].size() > 0)
		{
			painter->drawText(edgeOffset + 25, betweenweight + 60 + simpleFun, innerW * 1.0 / 4, 60, Qt::AlignVCenter, QString::fromLocal8Bit("次  数(次):") + QString::number(data_One[totalMachineCount].size()));
			painter->drawText(edgeOffset + 25 + innerW * 1.0 / 4 * 1, betweenweight + 60 + simpleFun, innerW * 1.0 / 4, 60, Qt::AlignVCenter, QString::fromLocal8Bit("总  和 (g):") + QString::number(m_dsum[totalMachineCount], 'f', 3));
			painter->drawText(edgeOffset + 25 + innerW * 1.0 / 4 * 2, betweenweight + 60 + simpleFun, innerW * 1.0 / 4, 60, Qt::AlignVCenter, QString::fromLocal8Bit("平均值 (g):") + QString::number(m_dave[totalMachineCount], 'f', 4));
			painter->drawText(edgeOffset + 25 + innerW * 1.0 / 4 * 3, betweenweight + 60 + simpleFun, innerW * 1.0 / 4, 60, Qt::AlignVCenter, QString::fromLocal8Bit("理论值 (g):") + QString::number(m_dtheory[totalMachineCount], 'f', 3));
			painter->drawText(edgeOffset + 25, betweenweight + 120 + simpleFun, innerW * 1.0 / 4, 60, Qt::AlignVCenter, QString::fromLocal8Bit("最大值 (g):") + QString::number(m_dmax[totalMachineCount], 'f', 3));
			painter->drawText(edgeOffset + 25 + innerW * 1.0 / 4 * 1, betweenweight + 120 + simpleFun, innerW * 1.0 / 4, 60, Qt::AlignVCenter, QString::fromLocal8Bit("差异值(大):") + QString::number(m_dmaxoff[totalMachineCount], 'f', 2) + "%");
			painter->drawText(edgeOffset + 25 + innerW * 1.0 / 4 * 2, betweenweight + 120 + simpleFun, innerW * 1.0 / 4, 60, Qt::AlignVCenter, QString::fromLocal8Bit("最小值 (g):") + QString::number(m_dmin[totalMachineCount], 'f', 3));
			painter->drawText(edgeOffset + 25 + innerW * 1.0 / 4 * 3, betweenweight + 120 + simpleFun, innerW * 1.0 / 4, 60, Qt::AlignVCenter, QString::fromLocal8Bit("差异值(小):") + QString::number(m_dminoff[totalMachineCount], 'f', 2) + "%");

			for (int i = 0; i < data_One[totalMachineCount].size(); i++) {
				painter->drawText(edgeOffset + i % weightColumnCount * weightColumnAve, weightMiddle + simpleFun + i / weightColumnCount % weightRowCount * weightRowAve, 60, weightRowAve, Qt::AlignCenter, QString::number(i + 1));
			}
			for (int i = 0; i < data_One[totalMachineCount].size(); i++) {
				painter->drawText(edgeOffset + i % weightColumnCount * weightColumnAve + 70, weightMiddle + simpleFun + i / weightColumnCount % weightRowCount * weightRowAve, weightColumnAve - 60, weightRowAve, Qt::AlignVCenter, QString::number(data_One[totalMachineCount].at(i), 'f', 3));
			}

		}
		//第五部分
		painter->drawText(50, pixHeight / 2 - 80 + simpleFun, 1900, 80, Qt::AlignCenter, QString::fromLocal8Bit("签字:张三"));// +ui->lE_code->text());

		painter->drawText(50, pixHeight / 2 - 80 + simpleFun, 3000, 80, Qt::AlignCenter, QString::fromLocal8Bit("日期:20201210"));// +ui->lE_reportDate->text());

	}
	painter->end();
}