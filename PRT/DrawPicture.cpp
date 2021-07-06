#include "DrawPicture.h"
#include <QSettings>

DrawPicture::DrawPicture(QObject *parent)
	: QObject(parent)
{
	painter = new QPainter();
	QString AppPath = qApp->applicationDirPath();
	QSettings configIniRead(AppPath + "\\ModelFile\\ProgramSet.ini", QSettings::IniFormat);
	m_ptnm = configIniRead.value("PrintEquipment/type", "A4 printer").toString();
}
DrawPicture::~DrawPicture()
{
}

void DrawPicture::drawPic(QPrinter *printer)
{
	//QCoreApplication::processEvents();
	QPrinterInfo info;
	QString ptName = info.defaultPrinterName(); // Ĭ�ϴ�ӡ������		
	//emit TOUI(QString::fromLocal8Bit("Ĭ���豸�ͺţ�\n") + ptName);

	m_sName = printer->printerName();
	//QPrinter *printer = new QPrinter(QPrinter::HighResolution);
	printer->setResolution(QPrinter::HighResolution);
	////�Զ���ֽ�Ŵ�С���ر���Ҫ����ȻԤ��Ч������
	//printer->setPrinterName(m_sName);
	printer->setPageSize(QPrinter::A4);
	printer->setOrientation(QPrinter::Portrait);

	printer->setFullPage(true);//first

	QPagedPaintDevice::Margins marg;//second
	marg.left = 0;
	marg.top = 5;
	printer->setMargins(marg);

	//printer->setPrintRange(QPrinter::PageRange);//2
	//printer->setPrintRange(QPrinter::AllPages);//0
	int prtMode = printer->printRange();
	int firstPg = printer->fromPage();
	int endPg = printer->toPage();
	int allornot;
	if (prtMode == 0)
	{
		allornot = 1;
	}
	else
	{
		if (firstPg == 0 && endPg == 0)
		{
			printer->setFromTo(1, 1);
			firstPg = 1;
			endPg = 1;
		}
		firstPg -= 1;
		endPg -= 1;
		allornot = 0;
	}
	painterPixmap.begin(printer);
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
		QCoreApplication::processEvents();
		pix[i] = QPixmap(pixWidth, pixHeight);
	}
	//����������ǻ�ģ��ĺ����ɣ��Ͼ���ӡʱ��ģ���

		//����Portrait ����Landscape
	//��ȡ�����ͼƬ
	painterPixmap.setWindow(0, 0, pix[0].width()+75, pix[0].height());
	//painterPixmap.setViewport(5, 5, pix[0].width()-10, pix[0].height()-10);

	int pageValue = 0;
	if (page1 > 0)
	{
		for (int i = 0; i < page1; i++)
		{
			int tempInt = data.size() - m_iPrintCurveCount + pageValue * 2 + 1;
			if (tempInt == data.size())
			{
				caculateData(data,m_gn, data.size() - m_iPrintCurveCount + pageValue * 2, 1);
			}
			else
			{
				caculateData(data, m_gn, data.size() - m_iPrintCurveCount + pageValue * 2, 2);
			}
			if (CurveChecked)
			{
				QCoreApplication::processEvents();
				createPixCurve(&pix[pageValue]);
			}
			/*if (ui.cB_Average->isChecked())
			{
				createPixAverage(&pix);
			}*/
			//pix[0].save("c:/pt.bmp");

			if (allornot == 1 || (allornot == 0 && pageValue >= firstPg && pageValue <= endPg))
			{
				QCoreApplication::processEvents();
				painterPixmap.drawPixmap(0, 0, pix[pageValue]);
				if (pageValue + 1 < pages)
				{
					if ((allornot == 0 && pageValue < endPg) || allornot == 1)
					{
						printer->newPage();
					}
				}

			}
			pageValue++;
		}

	}
	if (page2 > 0)
	{
		for (int i = 0; i < page2; i++)
		{
			totalMachineCount = 0;
			painter->begin(&pix[pageValue]);
			painter->setRenderHint(QPainter::Antialiasing, true);
			// ���û�����ɫ�����
			painter->setPen(QPen(QColor(255, 255, 255), 4));
			// ���û�ˢ��ɫ
			painter->setBrush(QColor(255, 255, 255));
			QRect rect(0, 0, pixWidth, pixHeight);
			//����ͼ���û�ˢ�׵�	

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
					caculateData(data, m_gn,data.size() - m_iPrintAveCount + tempRow * 2, 1);
				}
				else
				{
					caculateData(data, m_gn, data.size() - m_iPrintAveCount + tempRow * 2, 2);
				}

				if (AveChecked)
				{
					QCoreApplication::processEvents();
					createPixAverage(&pix[pageValue]);
				}
				tempRow++;
			}
			painter->end();
			if (allornot == 1 || (allornot == 0 && pageValue >= firstPg && pageValue <= endPg))
			{
				QCoreApplication::processEvents();
				painterPixmap.drawPixmap(0, 0, pix[pageValue]);
				if (pageValue + 1 < pages)
				{
					if ((allornot == 0 && pageValue < endPg) || allornot == 1)
					{
						printer->newPage();
					}
				}
			}
			pageValue++;
		}

	}
	/*painterPixmap.drawPixmap(0, 0, pix);*/

	//pix[0].save("c:/pt.bmp");
	painterPixmap.end();
}

void DrawPicture::createPixCurve(QPixmap *pix)
{
	painter->begin(pix);
	painter->setRenderHint(QPainter::Antialiasing, true);
	// ���û�����ɫ�����
	painter->setPen(QPen(QColor(255, 255, 255), 4));
	// ���û�ˢ��ɫ
	painter->setBrush(QColor(255, 255, 255));

	int edgeOffset = 50;
	int innerW = pixWidth - 2 * edgeOffset;
	int inner50percentW = innerW / 2;
	int innerH = pixHeight - 2 * edgeOffset;
	int inner50percentH = innerH / 2;
	int rightW = pixWidth - edgeOffset;
	int bottomH = pixHeight - edgeOffset;
	int firstLine = 110;//���������
	int secondLine = firstLine + 60;
	int weightTop = firstLine + 60;
	int weightMiddle = firstLine + 2 * 60;
	int weightRowCount = 8;
	int weightRowAve = 55;
	int betweenweight = weightMiddle + weightRowAve * weightRowCount;
	int weightColumnCount = 10;
	float weightColumnAve = (rightW - edgeOffset)*1.0 / weightColumnCount;//12������
	int weightBottom = betweenweight + 180;


	//����ϵ
	int of = 10;//��ͷ
	int basePointX = 200;
	int basePointY = pixHeight / 2 - 150;
	int XRight = rightW - 150;
	int dotLineRight = XRight - 75;
	int YTop = weightBottom + 100;
	int dotLineUp = YTop + 25;

	//ʵ�ʻ�ͼ��
	int actualTop = YTop + 50;
	int actualBottom = basePointY - 50;
	int actualLeft = basePointX + 50;
	int actualRight = dotLineRight - 25;
	int actualWidth = actualRight - actualLeft;
	int actualHight = actualBottom - actualTop;
	int YActualLength = actualBottom - actualTop;

	QRect rect(0, 0, pixWidth, pixHeight);
	//����ͼ���û�ˢ�׵�	
	QFont font;
	font.setPointSize(23);
	font.setFamily("����");
	font.setItalic(true);
	painter->setFont(font);
	painter->fillRect(rect, QColor(255, 255, 255));
	painter->drawRect(rect);
	//�����ݲ��ֵ�����
	painter->setPen(QPen(QColor(0, 0, 0), 3));
	QVector<QLine> lines;

	int totalMachineCount = 0;
	for (; totalMachineCount < 2; totalMachineCount++)
	{
		QStringList lst = gn_One[totalMachineCount].split(",");
		if (lst.size()<3)
		{
			lst.clear();
			lst << "" << "" << "";
		}
		int simpleFun = inner50percentH * totalMachineCount;
		lines.append(QLine(QPoint(edgeOffset, edgeOffset), QPoint(rightW, edgeOffset)));//�ϱ�
		lines.append(QLine(QPoint(rightW, edgeOffset), QPoint(rightW, bottomH)));//�ұ�
		lines.append(QLine(QPoint(edgeOffset, bottomH), QPoint(rightW, bottomH)));//�±�
		lines.append(QLine(QPoint(edgeOffset, edgeOffset), QPoint(edgeOffset, bottomH)));//���
		for (int i = 0; i < 3; i++)
		{
			lines.append(QLine(QPoint(edgeOffset, firstLine + i * 60 + simpleFun), QPoint(rightW, firstLine + i * 60 + simpleFun)));//�����±�//��Ʒ�±�//������Ŀ�±�	
		}
		for (int i = 0; i < 4; i++)
		{
			if (i != 2)
			{
				lines.append(QLine(QPoint(edgeOffset, betweenweight + i * 60 + simpleFun), QPoint(rightW, betweenweight + i * 60 + simpleFun)));//ÿ�������±�
			}
		}
		//lines.append(QLine(QPoint(betweenweight, weightTop), QPoint(betweenweight, weightBottom)));//����������ÿ������֮��
		lines.append(QLine(QPoint(edgeOffset, pixHeight / 2 - 80 + simpleFun), QPoint(rightW, pixHeight / 2 - 80 + simpleFun)));//1#������ǩ���ϲ�
		lines.append(QLine(QPoint(edgeOffset, pixHeight / 2), QPoint(rightW, pixHeight / 2)));//1/2#�ָ���
		//lines.append(QLine(QPoint(edgeOffset, bottomH - 80), QPoint(rightW, bottomH -80)));//2#������ǩ���ϲ�


		//������ϵ

		lines.append(QLine(QPoint(basePointX, basePointY + simpleFun), QPoint(basePointX, YTop + simpleFun)));//Y
		lines.append(QLine(QPoint(basePointX - of, YTop + of + simpleFun), QPoint(basePointX, YTop + simpleFun)));
		lines.append(QLine(QPoint(basePointX + of, YTop + of + simpleFun), QPoint(basePointX, YTop + simpleFun)));
		lines.append(QLine(QPoint(basePointX, basePointY + simpleFun), QPoint(XRight, basePointY + simpleFun)));//X
		lines.append(QLine(QPoint(XRight - of, basePointY - of + simpleFun), QPoint(XRight, basePointY + simpleFun)));
		lines.append(QLine(QPoint(XRight - of, basePointY + of + simpleFun), QPoint(XRight, basePointY + simpleFun)));

		painter->drawLines(lines);
		lines.clear();

		painter->setPen(QPen(QColor(0, 0, 0), 1, Qt::DashLine));

		lines.append(QLine(QPoint(edgeOffset, pixHeight / 2 + 5), QPoint(rightW, pixHeight / 2 + 5)));//1/2#�ָ���
		lines.append(QLine(QPoint(edgeOffset, pixHeight / 2 - 5), QPoint(rightW, pixHeight / 2 - 5)));//1/2#�ָ���
		//lines   200,rightW-250 pixHeight/2-825 pixHeight/2-275   250start point
		painter->drawText(basePointX - 40, basePointY + simpleFun, 50, 50, Qt::AlignVCenter, "0");//0
		if (data_One[totalMachineCount].size() > 0)
		{

			if (m_dmin[totalMachineCount] == m_dmax[totalMachineCount])//min==max
			{
				painter->drawText(90, actualTop + actualHight / 2 - 25 + simpleFun, 150, 50, Qt::AlignVCenter, QString::number(m_dmax[totalMachineCount], 'f', 3));//only one
				lines.append(QLine(QPoint(basePointX - 5, actualTop + actualHight / 2 + simpleFun), QPoint(dotLineRight, actualTop + actualHight / 2 + simpleFun)));//only one
			}
			else
			{
				painter->drawText(90, actualBottom - 25 + simpleFun, 150, 50, Qt::AlignVCenter, QString::number(m_dmin[totalMachineCount], 'f', 3));//MIN
				painter->drawText(90, actualTop - 25 + simpleFun, 150, 50, Qt::AlignVCenter, QString::number(m_dmax[totalMachineCount], 'f', 3));//MAX
				painter->drawText(70, actualBottom - 25 + simpleFun - (m_dave[totalMachineCount] - m_dmin[totalMachineCount]) / (m_dmax[totalMachineCount] - m_dmin[totalMachineCount]) * YActualLength, 150, 50, Qt::AlignVCenter, QString::number(m_dave[totalMachineCount], 'f', 4));//AVE			
				lines.append(QLine(QPoint(basePointX - 5, actualBottom + simpleFun), QPoint(dotLineRight, basePointY - 50 + simpleFun)));//MIN
				lines.append(QLine(QPoint(basePointX - 5, actualTop + simpleFun), QPoint(dotLineRight, actualTop + simpleFun)));//MAX
				lines.append(QLine(QPoint(basePointX - 5, actualBottom + simpleFun - (m_dave[totalMachineCount] - m_dmin[totalMachineCount]) / (m_dmax[totalMachineCount] - m_dmin[totalMachineCount]) * YActualLength), QPoint(dotLineRight, actualBottom + simpleFun - (m_dave[totalMachineCount] - m_dmin[totalMachineCount]) / (m_dmax[totalMachineCount] - m_dmin[totalMachineCount]) * YActualLength)));//AVE
			}
			painter->drawText(100, YTop - 50 + simpleFun, 150, 50, Qt::AlignVCenter, QString::fromLocal8Bit("����(g)"));//����
			painter->drawText(XRight, basePointY + simpleFun, 150, 50, Qt::AlignVCenter, QString::fromLocal8Bit("����"));//����


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

				painter->setPen(QPen(QColor(0, 0, 0), 6));
				for (int i = 0; i < data_One[totalMachineCount].size(); i++)
				{
					painter->drawPoint(actualLeft + actualWidth / 2, actualTop + actualHight / 2 + simpleFun);
				}
				painter->setPen(QPen(QColor(0, 0, 0), 1, Qt::DashLine));

			}

			painter->drawLines(lines);
			lines.clear();

			if (data_One[totalMachineCount].size() > 1)
			{
				//����
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
				painter->setPen(QPen(QColor(0, 0, 0), 6));
				for (int i = 0; i < data_One[totalMachineCount].size(); i++)
				{
					painter->drawPoint(actualLeft + actualWidth * 1.0 / (data_One[totalMachineCount].size() - 1)*i, actualBottom + simpleFun - (data_One[totalMachineCount].at(i) - m_dmin[totalMachineCount])*1.0 / (m_dmax[totalMachineCount] - m_dmin[totalMachineCount]) * actualHight);
				}
				painter->setPen(QPen(QColor(0, 0, 0), 2));
				painter->drawLines(lines);
				lines.clear();
			}
		}
		painter->setPen(QPen(QColor(0, 0, 0), 1));

		//����ӡ����վ��

		lines.append(QLine(QPoint(edgeOffset + 250, edgeOffset + simpleFun), QPoint(edgeOffset + 250, firstLine + simpleFun)));
		lines.append(QLine(QPoint(edgeOffset + innerW * 1.0 / 3 * 2, edgeOffset + simpleFun), QPoint(edgeOffset + innerW * 1.0 / 3 * 2, firstLine + simpleFun)));
		lines.append(QLine(QPoint(edgeOffset + 250 + innerW * 1.0 / 3 * 2, edgeOffset + simpleFun), QPoint(edgeOffset + 250 + innerW * 1.0 / 3 * 2, firstLine + simpleFun)));
		//������ͺ�
		for (int i = 0; i < 3; i++)
		{
			lines.append(QLine(QPoint(edgeOffset + innerW * 1.0 / 3 * (i + 1), firstLine + simpleFun), QPoint(edgeOffset + innerW * 1.0 / 3 * (i + 1), secondLine + simpleFun)));
			lines.append(QLine(QPoint(edgeOffset + 250 + innerW * 1.0 / 3 * i, firstLine + simpleFun), QPoint(edgeOffset + 250 + innerW * 1.0 / 3 * i, secondLine + simpleFun)));
		}
		//���������
		for (int i = 0; i < 4; i++)
		{
			lines.append(QLine(QPoint(edgeOffset + innerW * 1.0 / 4 * (i + 1), betweenweight + 60 + simpleFun), QPoint(edgeOffset + innerW * 1.0 / 4 * (i + 1), weightBottom + simpleFun)));
			lines.append(QLine(QPoint(edgeOffset + 225 + innerW * 1.0 / 4 * i, betweenweight + 60 + simpleFun), QPoint(edgeOffset + 225 + innerW * 1.0 / 4 * i, weightBottom + simpleFun)));
		}
		lines.append(QLine(QPoint(edgeOffset, betweenweight + 2 * 60 + simpleFun), QPoint(rightW, betweenweight + 2 * 60 + simpleFun)));//ÿ�������±�
		//��ÿ��������
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


		//��һ����
		if (totalMachineCount == 0)
		{
			font.setPointSize(20);
			painter->setFont(font);
			painter->drawText(100, 0 + simpleFun, innerW, 50, Qt::AlignVCenter, QString::fromLocal8Bit("��Ȩ����:Dr.Pharm"));// ui->lE_unit->text());//��λ����	
			font.setPointSize(35);
			font.setBold(true);
			painter->setFont(font);
			painter->drawText(0, 0 + simpleFun, pixWidth, 50, Qt::AlignCenter, QString::fromLocal8Bit("��챨��"));// ui->lE_report->text());//��������
		}
		font.setPointSize(23);
		font.setBold(false);
		painter->setFont(font);
		int machnum = totalMachineCount + 1;
		painter->drawText(edgeOffset, edgeOffset + simpleFun, 250, 70, Qt::AlignCenter, QString::fromLocal8Bit("�豸�ͺ�"));
		painter->drawText(edgeOffset + 275, edgeOffset + simpleFun, innerW * 1.0 / 2 - 250, 70, Qt::AlignVCenter, m_ptnm);
		painter->drawText(edgeOffset + innerW * 1.0 / 3 * 2, edgeOffset + simpleFun, 250, 70, Qt::AlignCenter, QString::fromLocal8Bit("���"));

		painter->drawText(edgeOffset + innerW * 1.0 / 3 * 2 + 275, edgeOffset + simpleFun, edgeOffset + innerW * 1.0 / 3 * 2 - 250, 70, Qt::AlignVCenter, lst.at(0));
		//�ڶ�����

		painter->drawText(edgeOffset, firstLine + simpleFun, 250, 60, Qt::AlignCenter, QString::fromLocal8Bit("��Ʒ����"));// +ui->lE_means->text());
		painter->drawText(edgeOffset + 250 + 25, firstLine + simpleFun, innerW * 1.0 / 3 - 250, 60, Qt::AlignVCenter, QString::fromLocal8Bit(""));// +ui->lE_means->text());

		painter->drawText(edgeOffset + innerW * 1.0 / 3, firstLine + simpleFun, 250, 60, Qt::AlignCenter, QString::fromLocal8Bit("��Ʒ���"));// +ui->lE_instrument->text());
		painter->drawText(edgeOffset + innerW * 1.0 / 3 + 250 + 25, firstLine + simpleFun, innerW * 1.0 / 3 * 2 - 250, 60, Qt::AlignVCenter, QString::fromLocal8Bit(""));// +ui->lE_instrument->text());
		painter->drawText(edgeOffset + innerW * 1.0 / 3 * 2, firstLine + simpleFun, 250, 60, Qt::AlignCenter, QString::fromLocal8Bit("��������"));// +ui->lE_instrument->text());
		painter->drawText(edgeOffset + innerW * 1.0 / 3 * 2 + 250 + 25, firstLine + simpleFun, innerW * 1.0 - 250, 60, Qt::AlignVCenter, lst.at(2));// +ui->lE_instrument->text());
		//��������
		font.setBold(true);
		painter->setFont(font);
		painter->drawText(edgeOffset, weightTop + simpleFun, innerW, 60, Qt::AlignCenter, QString::fromLocal8Bit("ÿ������(g)"));
		painter->drawText(edgeOffset, betweenweight + simpleFun, innerW, 60, Qt::AlignCenter, QString::fromLocal8Bit("�������"));
		font.setBold(false);
		painter->setFont(font);
		//���Ĳ��� ����
		//lines.append(QLine(QPoint(edgeOffset + innerW * 1.0 / 4 * i, betweenweight + 60 + simpleFun), QPoint(edgeOffset + innerW * 1.0 / 4 * i, weightBottom + simpleFun)));
		if (data_One[totalMachineCount].size() > 0)
		{
			painter->drawText(edgeOffset, betweenweight + 60 + simpleFun, 225, 60, Qt::AlignCenter, QString::fromLocal8Bit("��  ��"));
			painter->drawText(edgeOffset + 250, betweenweight + 60 + simpleFun, innerW * 1.0 / 4 - 225, 60, Qt::AlignVCenter, QString::number(data_One[totalMachineCount].size()));
			painter->drawText(edgeOffset + innerW * 1.0 / 4 * 1, betweenweight + 60 + simpleFun, 225, 60, Qt::AlignCenter, QString::fromLocal8Bit("��  �� (g)"));
			painter->drawText(edgeOffset + 250 + innerW * 1.0 / 4 * 1, betweenweight + 60 + simpleFun, innerW * 1.0 / 4 - 225, 60, Qt::AlignVCenter, QString::number(m_dsum[totalMachineCount], 'f', 3));
			painter->drawText(edgeOffset + innerW * 1.0 / 4 * 2, betweenweight + 60 + simpleFun, 225, 60, Qt::AlignCenter, QString::fromLocal8Bit("ƽ��ֵ (g)"));
			painter->drawText(edgeOffset + 250 + innerW * 1.0 / 4 * 2, betweenweight + 60 + simpleFun, innerW * 1.0 / 4 - 225, 60, Qt::AlignVCenter, QString::number(m_dave[totalMachineCount], 'f', 4));
			painter->drawText(edgeOffset + innerW * 1.0 / 4 * 3, betweenweight + 60 + simpleFun, 225, 60, Qt::AlignCenter, QString::fromLocal8Bit("����ֵ (g)"));
			painter->drawText(edgeOffset + 250 + innerW * 1.0 / 4 * 3, betweenweight + 60 + simpleFun, innerW * 1.0 / 4 - 225, 60, Qt::AlignVCenter, QString::number(m_dtheory[totalMachineCount], 'f', 3));
			painter->drawText(edgeOffset, betweenweight + 120 + simpleFun, 225, 60, Qt::AlignCenter, QString::fromLocal8Bit("���ֵ (g)"));
			painter->drawText(edgeOffset + 250, betweenweight + 120 + simpleFun, innerW * 1.0 / 4 - 225, 60, Qt::AlignVCenter, QString::number(m_dmax[totalMachineCount], 'f', 3));
			painter->drawText(edgeOffset + innerW * 1.0 / 4 * 1, betweenweight + 120 + simpleFun, 225, 60, Qt::AlignCenter, QString::fromLocal8Bit("����ֵ(��)"));
			painter->drawText(edgeOffset + 250 + innerW * 1.0 / 4 * 1, betweenweight + 120 + simpleFun, innerW * 1.0 / 4 - 225, 60, Qt::AlignVCenter, QString::number(m_dmaxoff[totalMachineCount], 'f', 2) + "%");
			painter->drawText(edgeOffset + innerW * 1.0 / 4 * 2, betweenweight + 120 + simpleFun, 225, 60, Qt::AlignCenter, QString::fromLocal8Bit("��Сֵ (g)"));
			painter->drawText(edgeOffset + 250 + innerW * 1.0 / 4 * 2, betweenweight + 120 + simpleFun, innerW * 1.0 / 4 - 225, 60, Qt::AlignVCenter, QString::number(m_dmin[totalMachineCount], 'f', 3));
			painter->drawText(edgeOffset + innerW * 1.0 / 4 * 3, betweenweight + 120 + simpleFun, 225, 60, Qt::AlignCenter, QString::fromLocal8Bit("����ֵ(С)"));
			painter->drawText(edgeOffset + 250 + innerW * 1.0 / 4 * 3, betweenweight + 120 + simpleFun, innerW * 1.0 / 4 - 225, 60, Qt::AlignVCenter, QString::number(m_dminoff[totalMachineCount], 'f', 2) + "%");

			for (int i = 0; i < data_One[totalMachineCount].size(); i++) {
				painter->drawText(edgeOffset + i % weightColumnCount * weightColumnAve, weightMiddle + simpleFun + i / weightColumnCount % weightRowCount * weightRowAve, 60, weightRowAve, Qt::AlignCenter, QString::number(i + 1));
			}
			for (int i = 0; i < data_One[totalMachineCount].size(); i++) {
				painter->drawText(edgeOffset + i % weightColumnCount * weightColumnAve + 70, weightMiddle + simpleFun + i / weightColumnCount % weightRowCount * weightRowAve, weightColumnAve - 60, weightRowAve, Qt::AlignVCenter, QString::number(data_One[totalMachineCount].at(i), 'f', 3));
			}

		}
		//���岿��
		painter->drawText(50, pixHeight / 2 - 80 + simpleFun, 1900, 80, Qt::AlignCenter, QString::fromLocal8Bit("ǩ��:"));// +ui->lE_code->text());

		painter->drawText(50, pixHeight / 2 - 80 + simpleFun, 3000, 80, Qt::AlignCenter, QString::fromLocal8Bit("����:")+lst.at(1));

	}
	painter->end();
}

void DrawPicture::createPixAverage(QPixmap *pix)
{

	QFont font;
	font.setPointSize(23);
	font.setFamily("����");
	font.setItalic(true);
	painter->setFont(font);

	int edgeOffset = 50;
	int innerW = pixWidth - 2 * edgeOffset;
	int inner50percentW = innerW / 2;
	int innerH = pixHeight - 2 * edgeOffset;
	int inner50percentH = innerH / 2;
	int rightW = pixWidth - edgeOffset;
	int bottomH = pixHeight - edgeOffset + 10;
	int firstLine = 110;//���������
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



	//�����ݲ��ֵ�����
	painter->setPen(QPen(QColor(0, 0, 0), 3));
	QVector<QLine> lines;


	int simpleFun = 480 * totalMachineCount;
	lines.append(QLine(QPoint(edgeOffset, edgeOffset), QPoint(rightW, edgeOffset)));//�ϱ�
	lines.append(QLine(QPoint(rightW, edgeOffset), QPoint(rightW, bottomH)));//�ұ�
	lines.append(QLine(QPoint(edgeOffset, bottomH), QPoint(rightW, bottomH)));//�±�
	lines.append(QLine(QPoint(edgeOffset, edgeOffset), QPoint(edgeOffset, bottomH)));//���

	lines.append(QLine(QPoint(edgeOffset, firstLine + simpleFun), QPoint(rightW, firstLine + simpleFun)));
	lines.append(QLine(QPoint(edgeOffset, secondLine + simpleFun), QPoint(rightW, secondLine + simpleFun)));
	lines.append(QLine(QPoint(edgeOffset, secondLine + 360 + simpleFun), QPoint(rightW, secondLine + 360 + simpleFun)));

	painter->drawLines(lines);
	lines.clear();

	painter->setPen(QPen(QColor(0, 0, 0), 1));

	//����ӡ����վ��

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

	//��һ����
	if (totalMachineCount == 0)
	{
		font.setPointSize(20);
		painter->setFont(font);
		painter->drawText(100, 0, innerW, 50, Qt::AlignVCenter, QString::fromLocal8Bit("��Ȩ����:Dr.Pharm"));// ui->lE_unit->text());//��λ����	
		painter->drawText(50, 0, innerW - 50, 50, Qt::AlignRight | Qt::AlignVCenter, QString::fromLocal8Bit("�豸�ͺ�:") + m_sName);
	}
	font.setPointSize(23);
	painter->setFont(font);

	//�ڶ�����

	painter->drawText(edgeOffset, secondLine + simpleFun, 250, 300, Qt::AlignCenter, QString::fromLocal8Bit("ǩ��:"));
	painter->drawText(edgeOffset, edgeOffset + simpleFun, firstwth, 60, Qt::AlignCenter, QString::fromLocal8Bit("����"));
	painter->drawText(secondPoint + 25, edgeOffset + simpleFun, secondwth, 60, Qt::AlignVCenter, QString::fromLocal8Bit(""));
	painter->drawText(thirdPoint, edgeOffset + simpleFun, thirdwth, 60, Qt::AlignCenter, QString::fromLocal8Bit("����"));
	painter->drawText(forthPoint + 25, edgeOffset + simpleFun, forthwth, 60, Qt::AlignVCenter, QString::fromLocal8Bit(""));
	painter->drawText(fifthPoint, edgeOffset + simpleFun, fifthwth, 60, Qt::AlignCenter, QString::fromLocal8Bit("1#վƽ������"));
	painter->drawText(sixthPoint + 25, edgeOffset + simpleFun, sixthwth, 60, Qt::AlignVCenter, QString::number(m_dave[0], 'f', 4) + "g");
	painter->drawText(sevenPoint, edgeOffset + simpleFun, sevenwth, 60, Qt::AlignCenter, QString::fromLocal8Bit("2#վƽ������"));
	if (data_One[1].size() == 0)
	{
		painter->drawText(eightPoint + 25, edgeOffset + simpleFun, eightWidth, 60, Qt::AlignVCenter, "-");
	}
	else
	{
		painter->drawText(eightPoint + 25, edgeOffset + simpleFun, eightWidth, 60, Qt::AlignVCenter, QString::number(m_dave[1], 'f', 4) + "g");
	}
}

void DrawPicture::caculateData(QVector<QVector<float>> transData,QVector<QString> gn, int ivalue, int half)//0 1 2
{

	data_One[0].resize(0);
	data_One[1].resize(0);
	if (half == 0)
	{
	}
	else if (half == 1)
	{
		data_One[0] = transData[ivalue];
		gn_One[0] = gn[ivalue];
		gn_One[1] = "";
	}
	else
	{
		data_One[0] = transData[ivalue];
		data_One[1] = transData[ivalue + 1];
		gn_One[0] = gn[ivalue];
		gn_One[1] = gn[ivalue + 1];
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

void DrawPicture::setCurveChecked(bool b)
{
	CurveChecked = b;
}

void DrawPicture::setAveChecked(bool b)
{
	AveChecked = b;
}

void DrawPicture::setData(QVector<QVector<float>> sourcedata,QVector<QString> gn, int i, int j)
{
	data = sourcedata;
	m_gn = gn;
	m_iPrintCurveCount = i;
	m_iPrintAveCount = j;
}