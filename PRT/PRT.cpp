#include "PRT.h"

PRT::PRT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags()&~Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint);
	setWindowIcon(QIcon("./ico/dr.ico"));

	initPrinter();
	initData();
	AppPath = qApp->applicationDirPath();//exe所在目录
	initUI();
}
void PRT::initPrinter()
{
	QPrinterInfo info;
	m_sName = info.defaultPrinterName(); // 默认打印机名字
	ui.lb_PrinterName->setText(QString::fromLocal8Bit("设备型号：") + m_sName);

	m_prt = new QPrinter();
	m_prt->setPrinterName(m_sName);
	painter = new QPainter();
}
void PRT::initData()
{
	m_iDataNum = 5;
	data.resize(m_iDataNum);
	ui.label->setText(QString::fromLocal8Bit("最大可打印数：") + QString::number(m_iDataNum) + QString::fromLocal8Bit("\n1#站:") + QString::number(m_iDataNum - m_iDataNum / 2) + QString::fromLocal8Bit("，2#站:") + QString::number(m_iDataNum / 2));

	data[0] << 0.369 << 0.321 << 0.332 << 0.311 << 0.399 << 0.334 << 0.321 << 0.346 << 0.389 << 0.333
		<< 0.333 << 0.333 << 0.333 << 0.333 << 0.333 << 0.369 << 0.321 << 0.332 << 0.311 << 0.399
		<< 0.334 << 0.321 << 0.346 << 0.389 << 0.333 << 0.323 << 0.333 << 0.333 << 0.333 << 0.333
		<< 0.333 << 0.369 << 0.321 << 0.332 << 0.311 << 0.399 << 0.334 << 0.321 << 0.346 << 0.389
		<< 0.333 << 0.333 << 0.333 << 0.333 << 0.333 << 0.333 << 0.333 << 0.369 << 0.321 << 0.332
		<< 0.311 << 0.399 << 0.334 << 0.321 << 0.346 << 0.389 << 0.333 << 0.333 << 0.333 << 0.333
		<< 0.333 << 0.343 << 0.333 << 0.319;
	data[1] << 0.220 << 0.300 << 0.300 << 1.0 << 2.0 << 3.5;
	data[2] << 3.220 << 2.300 << 5.300 << 1.034 << 7.024 << 3.512;
	data[3] << 0.220;
	data[4] << 3.220 << 1.4;

}
void PRT::initUI()
{
	ui.cB_Curve->setStyleSheet(STYLESHEET);
	ui.cB_Average->setStyleSheet(STYLESHEET);

	QSettings ReadIni(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	QRegExp regx("[0-9]+$");//正则表达式QRegExp,只允许输入中文、数字、字母、下划线以及空格,[\u4e00 - \u9fa5a - zA - Z0 - 9_] + $
	ui.lineEdit->setValidator(new QRegExpValidator(regx, this));
	ui.lineEdit_2->setValidator(new QRegExpValidator(regx, this));
	ui.lineEdit->setText(QString::number(ReadIni.value("ProgramSetting/PrintCurveCount", "0").toInt()));
	ui.lineEdit_2->setText(QString::number(ReadIni.value("ProgramSetting/PrintAveCount", "0").toInt()));
	ui.cB_Curve->setChecked(ReadIni.value("ProgramSetting/PrintCurve", "0").toBool());
	ui.cB_Average->setChecked(ReadIni.value("ProgramSetting/PrintAve", "0").toBool());
	ui.checkBox->setChecked(ReadIni.value("ProgramSetting/PrintCurveAllOrNot", "0").toBool());
	ui.checkBox_2->setChecked(ReadIni.value("ProgramSetting/PrintAveAllOrNot", "0").toBool());
}
int PRT::showMsgBox(const char* titleStr, const char* contentStr, const char* button1Str, const char* button2Str)
{
	QMessageBox msg(QMessageBox::Information, QString::fromLocal8Bit(titleStr), QString::fromLocal8Bit(contentStr), QMessageBox::Yes/* | QMessageBox::No*/);
	msg.setButtonText(QMessageBox::Yes, QString::fromLocal8Bit(button1Str));
	//msg.setButtonText(QMessageBox::No, QString::fromLocal8Bit(button2Str));
	msg.setWindowIcon(QIcon("./ico/dr.ico"));
	return msg.exec();
	//  QMessageBox::NoIcon
	//	QMessageBox::Question
	//	QMessageBox::Information
	//	QMessageBox::Warning
	//	QMessageBox::Critical
}
void PRT::on_cB_Curve_toggled(bool checked)
{
	ui.label_2->setVisible(checked);

	if (!ui.checkBox->isChecked())
	{
		ui.lineEdit->setVisible(checked);
	}

	ui.checkBox->setVisible(checked);
	QSettings WriteIni(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	WriteIni.setValue("ProgramSetting/PrintCurve", QString::number(checked));
	if (!checked && !ui.cB_Average->isChecked())
	{
		ui.pB_Print->setEnabled(false);
		ui.pB_PrintDirect->setEnabled(false);
	}
	else
	{
		ui.pB_Print->setEnabled(true);
		ui.pB_PrintDirect->setEnabled(true);
	}
}
void PRT::on_cB_Average_toggled(bool checked)
{
	ui.label_3->setVisible(checked);
	if (!ui.checkBox_2->isChecked())
	{
		ui.lineEdit_2->setVisible(checked);
	}
	ui.checkBox_2->setVisible(checked);
	QSettings WriteIni(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	WriteIni.setValue("ProgramSetting/PrintAve", QString::number(checked));
	if (!checked && !ui.cB_Curve->isChecked())
	{
		ui.pB_Print->setEnabled(false);
		ui.pB_PrintDirect->setEnabled(false);
	}
	else
	{
		ui.pB_Print->setEnabled(true);
		ui.pB_PrintDirect->setEnabled(true);
	}
}
void PRT::on_checkBox_toggled(bool checked)
{
	ui.lineEdit->setVisible(!checked);
	QSettings WriteIni(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	WriteIni.setValue("ProgramSetting/PrintCurveAllOrNot", QString::number(checked));
}
void PRT::on_checkBox_2_toggled(bool checked)
{
	ui.lineEdit_2->setVisible(!checked);
	QSettings WriteIni(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	WriteIni.setValue("ProgramSetting/PrintAveAllOrNot", QString::number(checked));
}
void PRT::caculateData(QVector<QVector<float>> transData, int ivalue, int half)//0 1 2
{

	data_One[0].resize(0);
	data_One[1].resize(0);
	if (half == 0)
	{
	}
	else if (half == 1)
	{
		data_One[0] = transData[ivalue];
	}
	else
	{
		data_One[0] = transData[ivalue];
		data_One[1] = transData[ivalue + 1];
	}
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

}
void PRT::writeIni()
{
	QSettings WriteIni(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	num1_Le = ui.lineEdit->text().toInt();
	num2_Le_2 = ui.lineEdit_2->text().toInt();

	ui.lineEdit->setText(QString::number(num1_Le));
	ui.lineEdit_2->setText(QString::number(num2_Le_2));

	WriteIni.setValue("ProgramSetting/PrintCurveCount", QString::number(num1_Le));
	WriteIni.setValue("ProgramSetting/PrintAveCount", QString::number(num2_Le_2));
}
bool PRT::caculateCount()
{
	if (ui.cB_Curve->isChecked())
	{
		if (ui.checkBox->isChecked())
		{
			m_iPrintCurveCount = m_iDataNum;
		}
		else
		{
			m_iPrintCurveCount = num1_Le <= m_iDataNum ? num1_Le : m_iDataNum;
		}

	}
	if (ui.cB_Average->isChecked())
	{
		if (ui.checkBox_2->isChecked())
		{
			m_iPrintAveCount = m_iDataNum;
		}
		else
		{
			m_iPrintAveCount = num2_Le_2 <= m_iDataNum ? num2_Le_2 : m_iDataNum;
		}
	}

	if (m_iDataNum == 0)
	{
		showMsgBox("提示", "无可打印数据!", "我知道了", "取消");
		return false;
	}
	if (m_iPrintCurveCount == 0 && m_iPrintAveCount == 0)
	{
		showMsgBox("提示", "打印数设置均为0!", "我知道了", "取消");
		return false;
	}
	return true;
}
void PRT::on_pB_PrintDirect_clicked()
{
	/*直接打印*/
	writeIni();
	//caculateData();
	QPainter painterPixmap(m_prt);
	m_prt->setResolution(QPrinter::HighResolution);
	////自定义纸张大小，特别重要，不然预览效果极差
	//printer->setPrinterName(m_sName);
	m_prt->setPageSize(QPrinter::A4);
	m_prt->setOrientation(QPrinter::Portrait);

	QPixmap pix = QPixmap(pixWidth, pixHeight);
	//这个函数算是画模板的函数吧，毕竟打印时有模板的
	/*if (ui.cB_Mode->currentIndex() == 0)
	{
		createPixCurve(&pix);
	}
	else*/
	{
		createPixAverage(&pix);
	}
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
	writeIni();
	if (!caculateCount())return;

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

	int page1;
	if (m_iPrintCurveCount == 0)
	{
		page1 = 0;
	}
	else
	{
		page1 = m_iPrintCurveCount / 2 < 1 ? 1 : m_iPrintCurveCount / 2 + (m_iPrintCurveCount % 2 == 0 ? 0 : 1);
	}

	int page2;
	if (m_iPrintAveCount == 0)
	{
		page2 = 0;
	}
	else
	{
		page2 = m_iPrintAveCount / 12 < 1 ? 1 : m_iPrintAveCount / 12 + (m_iPrintAveCount % 12 == 0 ? 0 : 1);
	}
	int pages = page1 + page2;
	QVector<QPixmap> pix;
	pix.resize(pages);
	for (int i = 0; i < pix.size(); i++)
	{
		pix[i] = QPixmap(pixWidth, pixHeight);
	}
	//这个函数算是画模板的函数吧，毕竟打印时有模板的

		//纵向：Portrait 横向：Landscape
	//获取界面的图片

	QRect rect = painterPixmap.viewport();
	float x = rect.width()*1.0 / pix[0].width();
	float y = rect.height()*1.0 / pix[0].height();
	//设置图像长宽是原图的多少倍
	painterPixmap.scale(x, y);

	int pageValue = 0;
	if (page1 > 0)
	{
		for (int i = 0; i < page1; i++)
		{
			int tempInt = data.size() - m_iPrintCurveCount + pageValue * 2 + 1;
			if (tempInt == data.size())
			{
				caculateData(data, data.size() - m_iPrintCurveCount + pageValue * 2, 1);
			}
			else
			{
				caculateData(data, data.size() - m_iPrintCurveCount + pageValue * 2, 2);
			}
			if (ui.cB_Curve->isChecked())
			{
				createPixCurve(&pix[pageValue]);
			}
			/*if (ui.cB_Average->isChecked())
			{
				createPixAverage(&pix);
			}*/
			/*pix.save("c:/pt.bmp");*/

			painterPixmap.drawPixmap(0, 0, pix[pageValue++]);
			if (pageValue < pages)
			{
				printer->newPage();
			}
		}

	}
	if (page2 > 0)
	{
		for (int i = 0; i < page2; i++)
		{
			totalMachineCount = 0;
			painter->begin(&pix[pageValue]);
			painter->setRenderHint(QPainter::Antialiasing, true);
			// 设置画笔颜色、宽度
			painter->setPen(QPen(QColor(255, 255, 255), 4));
			// 设置画刷颜色
			painter->setBrush(QColor(255, 255, 255));
			QRect rect(0, 0, pixWidth, pixHeight);
			//整张图设置画刷白底	

			painter->fillRect(rect, QColor(255, 255, 255));
			painter->drawRect(rect);
			int tempRow = 0;
			for (; totalMachineCount < 6; totalMachineCount++)
			{
				int tempInt = data.size() - m_iPrintAveCount + tempRow * 2 + 1;
				if (tempInt > data.size())
				{
					break;
				}
				else if (tempInt == data.size())
				{
					caculateData(data, data.size() - m_iPrintAveCount + tempRow * 2, 1);
				}
				else
				{
					caculateData(data, data.size() - m_iPrintAveCount + tempRow * 2, 2);
				}

				if (ui.cB_Average->isChecked())
				{
					createPixAverage(&pix[pageValue]);
				}
				tempRow++;
			}
			painter->end();
			painterPixmap.drawPixmap(0, 0, pix[pageValue++]);
			if (pageValue < pages)
			{
				printer->newPage();
			}
		}

	}
	/*painterPixmap.drawPixmap(0, 0, pix);*/
}

void PRT::createPixCurve(QPixmap *pix)
{
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
	int firstLine = 110;//大标题下面
	int secondLine = firstLine + 60;
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
	font.setPointSize(25);
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

		//画打印机和站号

		lines.append(QLine(QPoint(edgeOffset + 250, edgeOffset + simpleFun), QPoint(edgeOffset + 250, firstLine + simpleFun)));
		lines.append(QLine(QPoint(edgeOffset + innerW * 1.0 / 3 * 2, edgeOffset + simpleFun), QPoint(edgeOffset + innerW * 1.0 / 3 * 2, firstLine + simpleFun)));
		lines.append(QLine(QPoint(edgeOffset + 250 + innerW * 1.0 / 3 * 2, edgeOffset + simpleFun), QPoint(edgeOffset + 250 + innerW * 1.0 / 3 * 2, firstLine + simpleFun)));
		//画规格型号
		for (int i = 0; i < 3; i++)
		{
			lines.append(QLine(QPoint(edgeOffset + innerW * 1.0 / 3 * (i + 1), firstLine + simpleFun), QPoint(edgeOffset + innerW * 1.0 / 3 * (i + 1), secondLine + simpleFun)));
			lines.append(QLine(QPoint(edgeOffset + 250 + innerW * 1.0 / 3 * i, firstLine + simpleFun), QPoint(edgeOffset + 250 + innerW * 1.0 / 3 * i, secondLine + simpleFun)));
		}
		//画重量结果
		for (int i = 0; i < 4; i++)
		{
			lines.append(QLine(QPoint(edgeOffset + innerW * 1.0 / 4 * (i + 1), betweenweight + 60 + simpleFun), QPoint(edgeOffset + innerW * 1.0 / 4 * (i + 1), weightBottom + simpleFun)));
			lines.append(QLine(QPoint(edgeOffset + 225 + innerW * 1.0 / 4 * i, betweenweight + 60 + simpleFun), QPoint(edgeOffset + 225 + innerW * 1.0 / 4 * i, weightBottom + simpleFun)));
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
			font.setPointSize(20);
			painter->setFont(font);
			painter->drawText(100, 0 + simpleFun, innerW, 50, Qt::AlignVCenter, QString::fromLocal8Bit("版权所有:Dr.Pharm"));// ui->lE_unit->text());//单位名称	
			font.setPointSize(35);
			font.setBold(true);
			painter->setFont(font);
			painter->drawText(0, 0 + simpleFun, pixWidth, 50, Qt::AlignCenter, QString::fromLocal8Bit("抽检报告"));// ui->lE_report->text());//报告名称
		}
		font.setPointSize(25);
		font.setBold(false);
		painter->setFont(font);
		int machnum = totalMachineCount + 1;
		painter->drawText(edgeOffset, edgeOffset + simpleFun, 250, 70, Qt::AlignCenter, QString::fromLocal8Bit("设备型号"));
		painter->drawText(edgeOffset + 275, edgeOffset + simpleFun, innerW * 1.0 / 2 - 250, 70, Qt::AlignVCenter, m_sName);
		painter->drawText(edgeOffset + innerW * 1.0 / 3 * 2, edgeOffset + simpleFun, 250, 70, Qt::AlignCenter, QString::fromLocal8Bit("站号"));
		painter->drawText(edgeOffset + innerW * 1.0 / 3 * 2 + 275, edgeOffset + simpleFun, edgeOffset + innerW * 1.0 / 3 * 2 - 250, 70, Qt::AlignVCenter, QString::number(machnum) + QString::fromLocal8Bit("#"));
		//第二部分

		painter->drawText(edgeOffset, firstLine + simpleFun, 250, 60, Qt::AlignCenter, QString::fromLocal8Bit("产品名称"));// +ui->lE_means->text());
		painter->drawText(edgeOffset + 250 + 25, firstLine + simpleFun, innerW * 1.0 / 3 - 250, 60, Qt::AlignVCenter, QString::fromLocal8Bit("红素片"));// +ui->lE_means->text());

		painter->drawText(edgeOffset + innerW * 1.0 / 3, firstLine + simpleFun, 250, 60, Qt::AlignCenter, QString::fromLocal8Bit("产品规格"));// +ui->lE_instrument->text());
		painter->drawText(edgeOffset + innerW * 1.0 / 3 + 250 + 25, firstLine + simpleFun, innerW * 1.0 / 3 * 2 - 250, 60, Qt::AlignVCenter, QString::fromLocal8Bit("一号片"));// +ui->lE_instrument->text());
		painter->drawText(edgeOffset + innerW * 1.0 / 3 * 2, firstLine + simpleFun, 250, 60, Qt::AlignCenter, QString::fromLocal8Bit("产品批号"));// +ui->lE_instrument->text());
		painter->drawText(edgeOffset + innerW * 1.0 / 3 * 2 + 250 + 25, firstLine + simpleFun, innerW * 1.0 - 250, 60, Qt::AlignVCenter, QString::fromLocal8Bit("123456789"));// +ui->lE_instrument->text());
		//第三部分
		font.setBold(true);
		painter->setFont(font);
		painter->drawText(edgeOffset, weightTop + simpleFun, innerW, 60, Qt::AlignCenter, QString::fromLocal8Bit("每粒重量(g)"));
		painter->drawText(edgeOffset, betweenweight + simpleFun, innerW, 60, Qt::AlignCenter, QString::fromLocal8Bit("重量结果"));
		font.setBold(false);
		painter->setFont(font);
		//第四部分 数据
		//lines.append(QLine(QPoint(edgeOffset + innerW * 1.0 / 4 * i, betweenweight + 60 + simpleFun), QPoint(edgeOffset + innerW * 1.0 / 4 * i, weightBottom + simpleFun)));
		if (data_One[totalMachineCount].size() > 0)
		{
			painter->drawText(edgeOffset, betweenweight + 60 + simpleFun, 225, 60, Qt::AlignCenter, QString::fromLocal8Bit("次  数(次)"));
			painter->drawText(edgeOffset + 250, betweenweight + 60 + simpleFun, innerW * 1.0 / 4 - 225, 60, Qt::AlignVCenter, QString::number(data_One[totalMachineCount].size()));
			painter->drawText(edgeOffset + innerW * 1.0 / 4 * 1, betweenweight + 60 + simpleFun, 225, 60, Qt::AlignCenter, QString::fromLocal8Bit("总  和 (g)"));
			painter->drawText(edgeOffset + 250 + innerW * 1.0 / 4 * 1, betweenweight + 60 + simpleFun, innerW * 1.0 / 4 - 225, 60, Qt::AlignVCenter, QString::number(m_dsum[totalMachineCount], 'f', 3));
			painter->drawText(edgeOffset + innerW * 1.0 / 4 * 2, betweenweight + 60 + simpleFun, 225, 60, Qt::AlignCenter, QString::fromLocal8Bit("平均值 (g)"));
			painter->drawText(edgeOffset + 250 + innerW * 1.0 / 4 * 2, betweenweight + 60 + simpleFun, innerW * 1.0 / 4 - 225, 60, Qt::AlignVCenter, QString::number(m_dave[totalMachineCount], 'f', 4));
			painter->drawText(edgeOffset + innerW * 1.0 / 4 * 3, betweenweight + 60 + simpleFun, 225, 60, Qt::AlignCenter, QString::fromLocal8Bit("理论值 (g)"));
			painter->drawText(edgeOffset + 250 + innerW * 1.0 / 4 * 3, betweenweight + 60 + simpleFun, innerW * 1.0 / 4 - 225, 60, Qt::AlignVCenter, QString::number(m_dtheory[totalMachineCount], 'f', 3));
			painter->drawText(edgeOffset, betweenweight + 120 + simpleFun, 225, 60, Qt::AlignCenter, QString::fromLocal8Bit("最大值 (g)"));
			painter->drawText(edgeOffset + 250, betweenweight + 120 + simpleFun, innerW * 1.0 / 4 - 225, 60, Qt::AlignVCenter, QString::number(m_dmax[totalMachineCount], 'f', 3));
			painter->drawText(edgeOffset + innerW * 1.0 / 4 * 1, betweenweight + 120 + simpleFun, 225, 60, Qt::AlignCenter, QString::fromLocal8Bit("差异值(大)"));
			painter->drawText(edgeOffset + 250 + innerW * 1.0 / 4 * 1, betweenweight + 120 + simpleFun, innerW * 1.0 / 4 - 225, 60, Qt::AlignVCenter, QString::number(m_dmaxoff[totalMachineCount], 'f', 2) + "%");
			painter->drawText(edgeOffset + innerW * 1.0 / 4 * 2, betweenweight + 120 + simpleFun, 225, 60, Qt::AlignCenter, QString::fromLocal8Bit("最小值 (g)"));
			painter->drawText(edgeOffset + 250 + innerW * 1.0 / 4 * 2, betweenweight + 120 + simpleFun, innerW * 1.0 / 4 - 225, 60, Qt::AlignVCenter, QString::number(m_dmin[totalMachineCount], 'f', 3));
			painter->drawText(edgeOffset + innerW * 1.0 / 4 * 3, betweenweight + 120 + simpleFun, 225, 60, Qt::AlignCenter, QString::fromLocal8Bit("差异值(小)"));
			painter->drawText(edgeOffset + 250 + innerW * 1.0 / 4 * 3, betweenweight + 120 + simpleFun, innerW * 1.0 / 4 - 225, 60, Qt::AlignVCenter, QString::number(m_dminoff[totalMachineCount], 'f', 2) + "%");

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

void PRT::createPixAverage(QPixmap *pix)
{

	QFont font;
	font.setPointSize(25);
	font.setFamily("宋体");
	font.setItalic(true);
	painter->setFont(font);

	int edgeOffset = 50;
	int innerW = pixWidth - 2 * edgeOffset;
	int inner50percentW = innerW / 2;
	int innerH = pixHeight - 2 * edgeOffset;
	int inner50percentH = innerH / 2;
	int rightW = pixWidth - edgeOffset;
	int bottomH = pixHeight - edgeOffset + 10;
	int firstLine = 110;//大标题下面
	int secondLine = firstLine + 60;

	int wthOff = 25;
	int firstwth = 125;
	int secondPoint = edgeOffset + firstwth;
	int secondwth = 400;
	int thirdPoint = secondPoint + secondwth;
	int thirdwth = firstwth;
	int forthPoint = thirdPoint + thirdwth;
	int forthwth = secondwth;
	int fifthPoint = forthPoint + forthwth;
	int fifthwth = 250;
	float sixthPoint = fifthPoint + fifthwth;
	float sixthwth = (innerW - firstwth - secondwth - thirdwth - forthwth - fifthwth * 2)*1.0 / 2;
	float sevenPoint = sixthPoint + sixthwth;
	float sevenwth = fifthwth;
	float eightPoint = sevenPoint + sevenwth;
	float eightWidth = sixthwth;



	//画数据部分的线条
	painter->setPen(QPen(QColor(0, 0, 0), 3));
	QVector<QLine> lines;


	int simpleFun = 480 * totalMachineCount;
	lines.append(QLine(QPoint(edgeOffset, edgeOffset), QPoint(rightW, edgeOffset)));//上边
	lines.append(QLine(QPoint(rightW, edgeOffset), QPoint(rightW, bottomH)));//右边
	lines.append(QLine(QPoint(edgeOffset, bottomH), QPoint(rightW, bottomH)));//下边
	lines.append(QLine(QPoint(edgeOffset, edgeOffset), QPoint(edgeOffset, bottomH)));//左边

	lines.append(QLine(QPoint(edgeOffset, firstLine + simpleFun), QPoint(rightW, firstLine + simpleFun)));
	lines.append(QLine(QPoint(edgeOffset, secondLine + simpleFun), QPoint(rightW, secondLine + simpleFun)));
	lines.append(QLine(QPoint(edgeOffset, secondLine + 360 + simpleFun), QPoint(rightW, secondLine + 360 + simpleFun)));

	painter->drawLines(lines);
	lines.clear();

	painter->setPen(QPen(QColor(0, 0, 0), 1));

	//画打印机和站号

	lines.append(QLine(QPoint(secondPoint, edgeOffset + simpleFun), QPoint(secondPoint, firstLine + simpleFun)));
	lines.append(QLine(QPoint(forthPoint, edgeOffset + simpleFun), QPoint(forthPoint, firstLine + simpleFun)));
	lines.append(QLine(QPoint(sixthPoint, edgeOffset + simpleFun), QPoint(sixthPoint, firstLine + simpleFun)));
	lines.append(QLine(QPoint(eightPoint, edgeOffset + simpleFun), QPoint(eightPoint, firstLine + simpleFun)));
	painter->drawLines(lines);
	lines.clear();

	painter->setPen(QPen(QColor(0, 0, 0), 3));
	lines.append(QLine(QPoint(thirdPoint, edgeOffset + simpleFun), QPoint(thirdPoint, firstLine + simpleFun)));
	lines.append(QLine(QPoint(fifthPoint, edgeOffset + simpleFun), QPoint(fifthPoint, firstLine + simpleFun)));
	lines.append(QLine(QPoint(sevenPoint, edgeOffset + simpleFun), QPoint(sevenPoint, firstLine + simpleFun)));

	painter->drawLines(lines);
	lines.clear();

	//第一部分
	if (totalMachineCount == 0)
	{
		font.setPointSize(20);
		painter->setFont(font);
		painter->drawText(100, 0, innerW, 50, Qt::AlignVCenter, QString::fromLocal8Bit("版权所有:Dr.Pharm"));// ui->lE_unit->text());//单位名称	
		painter->drawText(50, 0, innerW - 50, 50, Qt::AlignRight | Qt::AlignVCenter, QString::fromLocal8Bit("设备型号:") + m_sName);
	}
	font.setPointSize(25);
	painter->setFont(font);

	//第二部分

	painter->drawText(edgeOffset, secondLine + simpleFun, 250, 300, Qt::AlignCenter, QString::fromLocal8Bit("签名:"));
	painter->drawText(edgeOffset, edgeOffset + simpleFun, firstwth, 60, Qt::AlignCenter, QString::fromLocal8Bit("日期"));
	painter->drawText(secondPoint + 25, edgeOffset + simpleFun, secondwth, 60, Qt::AlignVCenter, QString::fromLocal8Bit("2020-12-12 12:12:12"));
	painter->drawText(thirdPoint, edgeOffset + simpleFun, thirdwth, 60, Qt::AlignCenter, QString::fromLocal8Bit("批号"));
	painter->drawText(forthPoint + 25, edgeOffset + simpleFun, forthwth, 60, Qt::AlignVCenter, QString::fromLocal8Bit("123456789"));
	painter->drawText(fifthPoint, edgeOffset + simpleFun, fifthwth, 60, Qt::AlignCenter, QString::fromLocal8Bit("1#站平均重量"));
	painter->drawText(sixthPoint + 25, edgeOffset + simpleFun, sixthwth, 60, Qt::AlignVCenter, QString::number(m_dave[0], 'f', 4) + "g");
	painter->drawText(sevenPoint, edgeOffset + simpleFun, sevenwth, 60, Qt::AlignCenter, QString::fromLocal8Bit("2#站平均重量"));
	if (data_One[1].size() == 0)
	{
		painter->drawText(eightPoint + 25, edgeOffset + simpleFun, eightWidth, 60, Qt::AlignVCenter, "-");
	}
	else
	{
		painter->drawText(eightPoint + 25, edgeOffset + simpleFun, eightWidth, 60, Qt::AlignVCenter, QString::number(m_dave[1], 'f', 4) + "g");
	}
}
