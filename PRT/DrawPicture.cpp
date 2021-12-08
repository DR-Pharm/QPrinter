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
void DrawPicture::drawPic3(QPrinter *printer)
{
	m_ptnm = printer->printerName();
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
		
	int pages = data.size();

	QVector<QPixmap> pix;
	pix.resize(pages);
	QPixmap pixtmp(pixWidth, pixHeight);
	pixtmp.fill(Qt::white);

	for (int i = 0; i < pix.size(); i++)
	{
		QCoreApplication::processEvents();
		pix[i] = pixtmp;
	}
	painterPixmap.setWindow(QRect(0, 0, pix[0].width() + 75, pix[0].height() + 25));

	for (int i = 0; i < pages; i++)
	{
		painter->begin(&pix[i]);
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

		QCoreApplication::processEvents();


		caculateData(data, m_gn, 0, 1, m_ftheory);
		createThreeParaRecords(&pix[i],i);//test
		

		data.removeFirst();
		m_gn.removeFirst(); 
		m_ftheory.removeFirst();

		painter->end();
		if (allornot == 1 || (allornot == 0 && i >= firstPg && i <= endPg))
		{
			QCoreApplication::processEvents();
			painterPixmap.drawPixmap(0, 0, pix[i]);
			if (i + 1 < pages)
			{
				if ((allornot == 0 && i < endPg) || allornot == 1)
				{
					printer->newPage();
				}
			}
		}

	}
	painterPixmap.end();
}
void DrawPicture::drawPic2(QPrinter *printer)
{
	m_ptnm = printer->printerName();
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

	int page2;
	if (m_cb.mid(1, 1) == "0")
	{
		page2 = m_iTestingRecords / 3 < 1 ? 1 : m_iTestingRecords / 3 + (m_iTestingRecords % 3 == 0 ? 0 : 1);
	}
	else
	{
		page2 = m_iTestingRecords / 4 < 1 ? 1 : m_iTestingRecords / 4 + (m_iTestingRecords % 4 == 0 ? 0 : 1);
	}
	if (page2 > 2) page2 = 2;
	int pages = page2+1;//�и���ҳ
	QVector<QPixmap> pix;
	pix.resize(pages);
	QPixmap pixtmp(pixWidth, pixHeight);
	pixtmp.fill(Qt::white);
	for (int i = 0; i < pix.size(); i++)
	{
		QCoreApplication::processEvents();
		pix[i] = pixtmp;
	}
	painterPixmap.setWindow(QRect(0, 0, pix[0].width()+75, pix[0].height()+25));
	int pageValue = 0;

	painter->begin(&pix[pageValue]);
	if (m_cb.mid(1,1)== "0")
	{
		createTestingRecordsOnePage(&pix[pageValue]);
	}
	else
	{
		createTestingRecordsOnePage2(&pix[pageValue]);
	}
	painter->end();
	painterPixmap.drawPixmap(0, 0, pix[pageValue]);
	printer->newPage();
	pageValue += 1;

	m_iTestingCount = 0;
	for (int i = 0; i < page2; i++)
	{
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
		
		QCoreApplication::processEvents();	
		if (m_cb.mid(1, 1) == "0")
		{
			createTestingRecords(&pix[pageValue], m_iTestingCount);//test
		}
		else
		{
			createTestingRecords2(&pix[pageValue], m_iTestingCount);
		}
			m_iTestingCount++;
		
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
	painterPixmap.end();
}
void DrawPicture::drawPic(QPrinter *printer)
{
	m_ptnm = printer->printerName();
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
	QPixmap pixtmp(pixWidth, pixHeight);
	pixtmp.fill(Qt::white);
	for (int i = 0; i < pix.size(); i++)
	{
		QCoreApplication::processEvents();
		//pix[i] = QPixmap(pixWidth, pixHeight);
		pix[i] = pixtmp;
	}
	//����������ǻ�ģ��ĺ����ɣ��Ͼ���ӡʱ��ģ���

		//����Portrait ����Landscape
	//��ȡ�����ͼƬ
	painterPixmap.setWindow(0, 0, pix[0].width()+75, pix[0].height()+25);

	int pageValue = 0;
	if (page1 > 0)
	{
		for (int i = 0; i < page1; i++)
		{
			int tempInt = data.size() - m_iPrintCurveCount + pageValue * 2 + 1;
			if (tempInt == data.size())
			{
				caculateData(data,m_gn, data.size() - m_iPrintCurveCount + pageValue * 2, 1, m_ftheory);
			}
			else
			{
				caculateData(data, m_gn, data.size() - m_iPrintCurveCount + pageValue * 2, 2, m_ftheory);
			}
			if (CurveChecked)//���������������bug��,Դ������Ѿ�checked���ٴ�checked�������ۺ���
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
					caculateData(data, m_gn,data.size() - m_iPrintAveCount + tempRow * 2, 1,m_ftheory);
				}
				else
				{
					caculateData(data, m_gn, data.size() - m_iPrintAveCount + tempRow * 2, 2, m_ftheory);
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
void DrawPicture::createThreeParaRecords(QPixmap *pix,int pagei)
{
	//painter->setRenderHints(QPainter::SmoothPixmapTransform);//����� 
	painter->begin(pix);

	painter->setRenderHint(QPainter::Antialiasing, true);//������
	//QRect rect(0, 0, pixWidth, pixHeight);
	//painter->fillRect(rect, Qt::white);

	// ���û�����ɫ�����
	painter->setPen(QPen(QColor(255, 255, 255), 1));
	// ���û�ˢ��ɫ
	painter->setBrush(QColor(255, 255, 255));

	int edgeOffset = 80;
	int innerW = pixWidth - 2 * edgeOffset;
	int inner50percentW = innerW / 2;
	int innerH = pixHeight - 2 * edgeOffset;
	int inner50percentH = innerH / 2;
	int rightW = pixWidth - edgeOffset;
	int bottomH = pixHeight - edgeOffset;
	int firstLine = edgeOffset + 60;//���������
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

	//����ͼ���û�ˢ�׵�	
	QFont font;
	font.setPointSize(23);
	font.setFamily("����");
	//font.setItalic(true);//б��
	painter->setFont(font);
	//painter->fillRect(rect, QColor(255, 255, 255));//maybe a bug
	//painter->drawRect(rect);

	//�����ݲ��ֵ�����


	painter->setPen(QPen(QColor(0, 0, 0), 3));
	QVector<QLine> lines;


	int totalMachineCount = 0;
	
		QStringList lst = m_gn[totalMachineCount].split(",");
		if (lst.size() < 3)
		{
			lst.clear();
			lst << " " << " " << " ";
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
		lines.append(QLine(QPoint(edgeOffset, pixHeight / 2 - 80 + 60), QPoint(rightW, pixHeight / 2 - 80 + 60)));
		//����ȸ�
		lines.append(QLine(QPoint(edgeOffset, pixHeight / 2 - 80 + 60 + weightRowAve * weightRowCount), QPoint(rightW, pixHeight / 2 - 80 + 60 + weightRowAve * weightRowCount)));
		lines.append(QLine(QPoint(edgeOffset, pixHeight / 2 - 80 + 2 * 60 + weightRowAve * weightRowCount), QPoint(rightW, pixHeight / 2 - 80 + 2 * 60 + weightRowAve * weightRowCount)));
		lines.append(QLine(QPoint(edgeOffset, pixHeight / 2 - 80 + 2 * 60 + 2*weightRowAve * weightRowCount), QPoint(rightW, pixHeight / 2 - 80 + 2 * 60 + 2 * weightRowAve * weightRowCount)));
		//��Ӳ�ȸ�����
		//lines.append(QLine(QPoint(edgeOffset, pixHeight / 2), QPoint(rightW, pixHeight / 2)));//1/2#�ָ���
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

		//lines.append(QLine(QPoint(edgeOffset, pixHeight / 2 + 5), QPoint(rightW, pixHeight / 2 + 5)));//1/2#�ָ���
		//lines.append(QLine(QPoint(edgeOffset, pixHeight / 2 - 5), QPoint(rightW, pixHeight / 2 - 5)));//1/2#�ָ���
		//lines   200,rightW-250 pixHeight/2-825 pixHeight/2-275   250start point
		painter->drawText(basePointX - 40, basePointY + simpleFun, 50, 50, Qt::AlignVCenter, "0");//0
		if (data[totalMachineCount].size() > 0)
		{

			if (m_dmin[totalMachineCount] == m_dmax[totalMachineCount])//min==max
			{
				painter->drawText(90, actualTop + actualHight / 2 - 25 + simpleFun, 150, 50, Qt::AlignVCenter, QString::number(m_dmax[totalMachineCount], 'f', 3));//only one
				lines.append(QLine(QPoint(basePointX - 5, actualTop + actualHight / 2 + simpleFun), QPoint(dotLineRight, actualTop + actualHight / 2 + simpleFun)));//only one
			}
			else
			{
				painter->drawText(edgeOffset + 10, actualBottom - 25 + simpleFun, 150, 50, Qt::AlignVCenter, QString::number(m_dmin[totalMachineCount], 'f', 3));//MIN
				painter->drawText(edgeOffset + 10, actualTop - 25 + simpleFun, 150, 50, Qt::AlignVCenter, QString::number(m_dmax[totalMachineCount], 'f', 3));//MAX
				painter->drawText(edgeOffset + 10, actualBottom - 25 + simpleFun - (m_dave[totalMachineCount] - m_dmin[totalMachineCount]) / (m_dmax[totalMachineCount] - m_dmin[totalMachineCount]) * YActualLength, 150, 50, Qt::AlignVCenter, QString::number(m_dave[totalMachineCount], 'f', 4));//AVE			
				lines.append(QLine(QPoint(basePointX - 5, actualBottom + simpleFun), QPoint(dotLineRight, basePointY - 50 + simpleFun)));//MIN
				lines.append(QLine(QPoint(basePointX - 5, actualTop + simpleFun), QPoint(dotLineRight, actualTop + simpleFun)));//MAX
				lines.append(QLine(QPoint(basePointX - 5, actualBottom + simpleFun - (m_dave[totalMachineCount] - m_dmin[totalMachineCount]) / (m_dmax[totalMachineCount] - m_dmin[totalMachineCount]) * YActualLength), QPoint(dotLineRight, actualBottom + simpleFun - (m_dave[totalMachineCount] - m_dmin[totalMachineCount]) / (m_dmax[totalMachineCount] - m_dmin[totalMachineCount]) * YActualLength)));//AVE
			}
			painter->drawText(100, YTop - 50 + simpleFun, 150, 50, Qt::AlignVCenter, QString::fromLocal8Bit("����(g)"));//����
			painter->drawText(XRight, basePointY + simpleFun, 150, 50, Qt::AlignVCenter, QString::fromLocal8Bit("����"));//����


			if (data[totalMachineCount].size() > 1)
			{
				painter->drawText(actualLeft - 25, basePointY + simpleFun, 50, 50, Qt::AlignCenter, "1");//1
				painter->drawText(actualRight - 25, basePointY + simpleFun, 50, 50, Qt::AlignCenter, QString::number(data[totalMachineCount].size()));//size()
				lines.append(QLine(QPoint(basePointX + 50, basePointY + 5 + simpleFun), QPoint(basePointX + 50, dotLineUp + simpleFun)));//1111111111
				lines.append(QLine(QPoint(dotLineRight - 25, basePointY + 5 + simpleFun), QPoint(dotLineRight - 25, dotLineUp + simpleFun)));//808080808080
			}
			else
			{
				painter->drawText(actualLeft + actualWidth / 2 - 25, basePointY + simpleFun, 50, 50, Qt::AlignCenter, "1");//1
				lines.append(QLine(QPoint(actualLeft + actualWidth / 2, basePointY + 5 + simpleFun), QPoint(actualLeft + actualWidth / 2, dotLineUp + simpleFun)));//1111111111

				painter->setPen(QPen(QColor(0, 0, 0), 6));
				for (int i = 0; i < data[totalMachineCount].size(); i++)
				{
					painter->drawPoint(actualLeft + actualWidth / 2, actualTop + actualHight / 2 + simpleFun);
				}
				painter->setPen(QPen(QColor(0, 0, 0), 1, Qt::DashLine));

			}

			painter->drawLines(lines);
			lines.clear();

			if (data[totalMachineCount].size() > 1)
			{
				//����
				painter->setPen(QPen(QColor(0, 0, 0), 2));

				for (int i = 0; i < data[totalMachineCount].size() - 1; i++)
				{
					if (m_dmin[totalMachineCount] != m_dmax[totalMachineCount])
					{
						lines.append(QLine(QPoint(actualLeft + actualWidth * 1.0 / (data[totalMachineCount].size() - 1)*i, actualBottom + simpleFun - (data[totalMachineCount].at(i) - m_dmin[totalMachineCount])*1.0 / (m_dmax[totalMachineCount] - m_dmin[totalMachineCount]) * actualHight), QPoint(actualLeft + actualWidth * 1.0 / (data[totalMachineCount].size() - 1)*(i + 1), actualBottom + simpleFun - (data[totalMachineCount].at(i + 1) - m_dmin[totalMachineCount])*1.0 / (m_dmax[totalMachineCount] - m_dmin[totalMachineCount]) * actualHight)));
					}
					else
					{
						lines.append(QLine(QPoint(actualLeft, actualTop + actualHight / 2 + simpleFun), QPoint(actualRight, actualTop + actualHight / 2 + simpleFun)));
					}
				}
				painter->setPen(QPen(QColor(0, 0, 0), 6));
				for (int i = 0; i < data[totalMachineCount].size(); i++)
				{
					painter->drawPoint(actualLeft + actualWidth * 1.0 / (data[totalMachineCount].size() - 1)*i, actualBottom + simpleFun - (data[totalMachineCount].at(i) - m_dmin[totalMachineCount])*1.0 / (m_dmax[totalMachineCount] - m_dmin[totalMachineCount]) * actualHight);
				}
				painter->setPen(QPen(QColor(0, 0, 0), 2));
				painter->drawLines(lines);
				lines.clear();
			}
		}
		painter->setPen(QPen(QColor(0, 0, 0), 1));

		//����ӡ����վ��

		lines.append(QLine(QPoint(edgeOffset + 250, edgeOffset + simpleFun), QPoint(edgeOffset + 250, firstLine + simpleFun)));//����1
		lines.append(QLine(QPoint(edgeOffset + innerW * 1.0 / 3 * 2, edgeOffset + simpleFun), QPoint(edgeOffset + innerW * 1.0 / 3 * 2, firstLine + simpleFun)));//����2
		lines.append(QLine(QPoint(edgeOffset + 250 + innerW * 1.0 / 3 * 2, edgeOffset + simpleFun), QPoint(edgeOffset + 250 + innerW * 1.0 / 3 * 2, firstLine + simpleFun)));//����3
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
		lines.append(QLine(QPoint(edgeOffset, betweenweight + 2 * 60 + simpleFun), QPoint(rightW, betweenweight + 2 * 60 + simpleFun)));
		//��ÿ��������

		for (int i = 1; i < weightRowCount; i++)
		{
			lines.append(QLine(QPoint(edgeOffset, weightMiddle + i * weightRowAve + simpleFun), QPoint(rightW, weightMiddle + i * weightRowAve + simpleFun)));
			lines.append(QLine(QPoint(edgeOffset, pixHeight / 2 - 80 + 60 + i * weightRowAve + simpleFun), QPoint(rightW, pixHeight / 2 - 80 + 60 + i * weightRowAve + simpleFun)));
			lines.append(QLine(QPoint(edgeOffset, pixHeight / 2 - 80 + 2 * 60 + weightRowAve * weightRowCount + i * weightRowAve + simpleFun), QPoint(rightW, pixHeight / 2 - 80 + 2 * 60 + weightRowAve * weightRowCount + i * weightRowAve + simpleFun)));
		}
		for (int i = 1; i < weightColumnCount; i++)
		{
			lines.append(QLine(QPoint(edgeOffset + i * weightColumnAve, weightMiddle + simpleFun), QPoint(edgeOffset + i * weightColumnAve, betweenweight + simpleFun)));			
			lines.append(QLine(QPoint(edgeOffset + i * weightColumnAve, pixHeight / 2 - 80 + 60), QPoint(edgeOffset + i * weightColumnAve, pixHeight / 2 - 80 + 60 + weightRowAve*weightRowCount + simpleFun)));
			lines.append(QLine(QPoint(edgeOffset + i * weightColumnAve, pixHeight / 2 - 80 + 2 * 60 + weightRowAve * weightRowCount), QPoint(edgeOffset + i * weightColumnAve, pixHeight / 2 - 80 + 2 * 60 + 2*weightRowAve * weightRowCount)));

		}
		for (int i = 0; i < weightColumnCount; i++)//order no.
		{
			lines.append(QLine(QPoint(edgeOffset + i * weightColumnAve + 60, weightMiddle + simpleFun), QPoint(edgeOffset + i * weightColumnAve + 60, betweenweight + simpleFun)));
			lines.append(QLine(QPoint(edgeOffset + i * weightColumnAve + 60, pixHeight / 2 - 80 + 60), QPoint(edgeOffset + i * weightColumnAve + 60, pixHeight / 2 - 80 + 60 + weightRowAve * weightRowCount + simpleFun)));
			lines.append(QLine(QPoint(edgeOffset + i * weightColumnAve + 60, pixHeight / 2 - 80 + 2 * 60 + weightRowAve * weightRowCount), QPoint(edgeOffset + i * weightColumnAve + 60, pixHeight / 2 - 80 + 2 * 60 + 2 * weightRowAve * weightRowCount)));
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
		painter->drawText(edgeOffset, edgeOffset + simpleFun, 250, 60, Qt::AlignCenter, QString::fromLocal8Bit("�豸�ͺ�"));
		painter->drawText(edgeOffset + 275, edgeOffset + simpleFun, innerW * 1.0 / 2 - 250, 60, Qt::AlignVCenter, m_ptnm);
		painter->drawText(edgeOffset + innerW * 1.0 / 3 * 2, edgeOffset + simpleFun, 250, 60, Qt::AlignCenter, QString::fromLocal8Bit("���"));

		painter->drawText(edgeOffset + innerW * 1.0 / 3 * 2 + 275, edgeOffset + simpleFun, edgeOffset + innerW * 1.0 / 3 * 2 - 250, 60, Qt::AlignVCenter, lst.at(0));
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
		painter->drawText(edgeOffset, pixHeight / 2 - 80, innerW, 60, Qt::AlignCenter, QString::fromLocal8Bit("ÿ�����(mm)"));
		painter->drawText(edgeOffset, pixHeight / 2 - 80 + 60 + weightRowAve * weightRowCount, innerW, 60, Qt::AlignCenter, QString::fromLocal8Bit("ÿ��Ӳ��(Kg)"));
		painter->drawText(edgeOffset, betweenweight + simpleFun, innerW, 60, Qt::AlignCenter, QString::fromLocal8Bit("�������"));
		font.setBold(false);
		painter->setFont(font);
		//���Ĳ��� ����
		//lines.append(QLine(QPoint(edgeOffset + innerW * 1.0 / 4 * i, betweenweight + 60 + simpleFun), QPoint(edgeOffset + innerW * 1.0 / 4 * i, weightBottom + simpleFun)));
		if (data[totalMachineCount].size() > 0)
		{
			painter->drawText(edgeOffset, betweenweight + 60 + simpleFun, 225, 60, Qt::AlignCenter, QString::fromLocal8Bit("��  ��"));
			painter->drawText(edgeOffset + 250, betweenweight + 60 + simpleFun, innerW * 1.0 / 4 - 225, 60, Qt::AlignVCenter, QString::number(data[totalMachineCount].size()));
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

			for (int i = 0; i < data[totalMachineCount].size(); i++) {
				painter->drawText(edgeOffset + i % weightColumnCount * weightColumnAve, weightMiddle + simpleFun + i / weightColumnCount % weightRowCount * weightRowAve, 60, weightRowAve, Qt::AlignCenter, QString::number(i + 1));
			}
			if (m_Thickness.size()>= 1)
			{
				if (m_Thickness[pagei].size()>1||(m_Thickness[pagei].size() == 1 && m_Thickness[pagei].at(0)!=0))
				{
				for (int i = 0; i < m_Thickness[pagei].size(); i++) {
					painter->drawText(edgeOffset + i % weightColumnCount * weightColumnAve, pixHeight / 2 - 80 + 60 + simpleFun + i / weightColumnCount % weightRowCount * weightRowAve, 60, weightRowAve, Qt::AlignCenter, QString::number(i + 1));
					painter->drawText(edgeOffset + i % weightColumnCount * weightColumnAve + 70, pixHeight / 2 - 80 + 60 + simpleFun + i / weightColumnCount % weightRowCount * weightRowAve, weightColumnAve - 60, weightRowAve, Qt::AlignVCenter, QString::number(m_Thickness[pagei].at(i)));
				}
				}
			}

			if (m_Hardness.size() >= pagei+1)
			{
				if (m_Hardness[pagei].size() > 1 || (m_Hardness[pagei].size() == 1 && m_Hardness[pagei].at(0) != 0))
				{
					for (int i = 0; i < m_Hardness[pagei].size(); i++) {
						painter->drawText(edgeOffset + i % weightColumnCount * weightColumnAve, pixHeight / 2 - 80 + 2 * 60 + weightRowAve * weightRowCount + simpleFun + i / weightColumnCount % weightRowCount * weightRowAve, 60, weightRowAve, Qt::AlignCenter, QString::number(i + 1));
						painter->drawText(edgeOffset + i % weightColumnCount * weightColumnAve + 70, pixHeight / 2 - 80 + 2 * 60 + weightRowAve * weightRowCount + simpleFun + i / weightColumnCount % weightRowCount * weightRowAve, weightColumnAve - 60, weightRowAve, Qt::AlignVCenter, QString::number(m_Hardness[pagei].at(i)));
					}
				}
			}
			float fsum = 0;
			for (int i = 0; i < data[totalMachineCount].size(); i++) {
				painter->drawText(edgeOffset + i % weightColumnCount * weightColumnAve + 70, weightMiddle + simpleFun + i / weightColumnCount % weightRowCount * weightRowAve, weightColumnAve - 60, weightRowAve, Qt::AlignVCenter, QString::number(data[totalMachineCount].at(i), 'f', 3));
				fsum += data[totalMachineCount].at(i);
			}
			QString str;
			float SD = 0.0;
			float RSD = 0.0;
			if (data[totalMachineCount].size() == 1 || m_dave[totalMachineCount] == 0)
			{

			}
			else
			{
				for (int i = 0; i < data[totalMachineCount].size(); i++)
				{
					SD += (data[totalMachineCount].at(i) * 1000 - m_dave[totalMachineCount] * 1000)* (data[totalMachineCount].at(i) * 1000 - m_dave[totalMachineCount] * 1000);
				}
				SD = SD / (data[totalMachineCount].size() - 1);
				SD = sqrt(SD);
				RSD = SD / (m_dave[totalMachineCount] * 1000) * 100;
			}
			str = QString::fromLocal8Bit("RSD = ") + QString::number(RSD, 'f', 2) + "%";
			painter->drawText(innerW - 300, YTop - 50 + simpleFun, 300, 50, Qt::AlignCenter, str);//����
		}
		//���岿��
		simpleFun = inner50percentH * 1;
		painter->drawText(50, pixHeight / 2 - 80 + simpleFun, 1900, 80, Qt::AlignCenter, QString::fromLocal8Bit("ǩ��:"));// +ui->lE_code->text());

		painter->drawText(50, pixHeight / 2 - 80 + simpleFun, 3000, 80, Qt::AlignCenter, QString::fromLocal8Bit("����:") + lst.at(1));


	painter->end();
}
void DrawPicture::createTestingRecordsOnePage(QPixmap *pix)
{

	QFont font;
	font.setPointSize(35);
	font.setFamily("����");
	//font.setItalic(true);//б��
	painter->setFont(font);

	int edgeOffset = 80;
	int innerW = pixWidth - 2 * edgeOffset;
	int inner50percentW = innerW / 2;
	int innerH = pixHeight - 2 * edgeOffset;
	int inner50percentH = innerH / 2;
	int rightW = pixWidth - edgeOffset;
	int bottomH = pixHeight - edgeOffset - 50;//Ϊ����Ԥ��50
	int firstLine = edgeOffset + 20;//���������
	int secondLine = firstLine + 8;

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
	QVector<QLine> lines;
	int tbl = secondLine;//�˴���Ϊͷ
	float everyRow = (bottomH - tbl) / 31.0;
	float everyColumn = (rightW - edgeOffset) / 13.0;

	painter->setPen(QPen(QColor(0, 0, 0), 2));
	lines.append(QLine(QPoint(edgeOffset, secondLine), QPoint(rightW, secondLine)));//ϸ
	lines.append(QLine(QPoint(edgeOffset, bottomH + 30), QPoint(rightW, bottomH + 30)));//ϸ
	painter->drawLines(lines);
	lines.clear();

	painter->setPen(QPen(QColor(0, 0, 0), 5));
	lines.append(QLine(QPoint(edgeOffset, firstLine), QPoint(rightW, firstLine)));//��
	lines.append(QLine(QPoint(edgeOffset, bottomH + 38), QPoint(rightW, bottomH + 38)));//��
	painter->drawLines(lines);
	lines.clear();



	font.setPointSize(50);
	painter->setFont(font);
	painter->drawText(edgeOffset, 0, innerW, 100, Qt::AlignHCenter | Qt::AlignVCenter, QString::fromLocal8Bit("���ֺ���Ƽ���չ�ɷݹ�˾"));

	font.setPointSize(35);
	painter->setFont(font);
	QDateTime dt = QDateTime::currentDateTime();
	painter->drawText(edgeOffset, 0, innerW, 90, Qt::AlignRight | Qt::AlignBottom, QString::fromLocal8Bit("���ڣ�") + YearMonthDay());

	font.setPointSize(45);
	painter->setFont(font);

	painter->drawText(edgeOffset, tbl, innerW, everyRow, Qt::AlignHCenter | Qt::AlignBottom, QString::fromLocal8Bit("���ҳ�����Ի���¼ (�ֹ���д)"));
	float z = everyRow + tbl;
	painter->drawText(edgeOffset, z, innerW, everyRow, Qt::AlignHCenter | Qt::AlignBottom, QString::fromLocal8Bit("Capsule Filling Machine Testing Records"));

	font.setPointSize(30);
	painter->setFont(font);
	z += everyRow;
	float offs = 150;
	painter->drawText(edgeOffset, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("�Ի����� Customer��"));
	painter->drawText(edgeOffset + innerW / 2 + offs, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("ҩ������ Name of powder��"));
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("�豸�ͺ� Equipment mode��"));
	painter->drawText(edgeOffset + innerW / 2 + offs, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("Ҫ���� Required filling weight��"));
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("����ģ���ͺ� Capsule size��"));
	painter->drawText(edgeOffset + innerW / 2 + offs, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("(                    )mg"));
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("�Ի�����̺� Dosing disk thickness(mm)��"));
	painter->drawText(edgeOffset + innerW / 2 + offs, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("���ҳ��� Capsule shell supplier��"));
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("�����̺� Suggested dosing disk thickness(mm)��"));
	painter->drawText(edgeOffset + innerW / 2 + offs, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("�������ͣ�  ����  θ��  ֲ��"));
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("����΢�� Pellet��"));
	painter->drawText(edgeOffset + innerW / 2 + offs, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("�����¶� Temperature(��)��"));
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("�豸FAT̨�� Equipment FAT��"));
	painter->drawText(edgeOffset + innerW / 2 + offs, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("���ʪ�� Relative humidity(%)��"));
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("�����Ի� Pre-sales testing �� , ��ģ��  �� , �������� Testing dosing disk �� "));
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("Ѱ�������� Seek Solutions for Special Requirements��(�豸���������ղ���)"));


	z += everyRow;
	z += everyRow;
	float tbt = z;
	float k1 = everyRow + edgeOffset;
	float k2 = innerW / 4 + k1;
	float k3 = 7 * innerW / 24 + k2;
	float ff = 20;
	painter->setPen(QPen(QColor(0, 0, 0), 2));
	lines.append(QLine(QPoint(edgeOffset, z), QPoint(rightW, z)));//�����	
	painter->drawText(edgeOffset, z, everyRow, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("��"));
	painter->drawText(k1 + ff, z, k2 - k1, everyRow, Qt::AlignVCenter | Qt::AlignLeft, QString::fromLocal8Bit("�г����ֲ�״̬��"));
	painter->drawText(k2 + ff, z, k3 - k2, everyRow, Qt::AlignVCenter | Qt::AlignLeft, QString::fromLocal8Bit("ʢ�ۻ���״��"));
	painter->drawText(k3 + ff, z, rightW - k3, everyRow, Qt::AlignVCenter | Qt::AlignLeft, QString::fromLocal8Bit("�������ܶ�(g/ml)��"));

	z += everyRow;
	painter->drawText(edgeOffset, z, everyRow, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("λ"));
	painter->drawText(k1 + ff, z, k2 - k1, everyRow, Qt::AlignVCenter | Qt::AlignLeft, QString::fromLocal8Bit("Distribution of"));
	painter->drawText(k2 + ff, z, k3 - k2, everyRow, Qt::AlignVCenter | Qt::AlignLeft, QString::fromLocal8Bit("Shape of powder bowl"));
	painter->drawText(k3 + ff, z, rightW - k3, everyRow, Qt::AlignVCenter | Qt::AlignLeft, QString::fromLocal8Bit("ѹ����(%)��"));

	z += everyRow;
	painter->drawText(edgeOffset, z, everyRow, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("��"));
	painter->drawText(k1 + ff, z, k2 - k1, everyRow, Qt::AlignVCenter | Qt::AlignLeft, QString::fromLocal8Bit("Tamping pin holders"));
	painter->drawText(k3 + ff, z, rightW - k3, everyRow, Qt::AlignVCenter | Qt::AlignLeft, QString::fromLocal8Bit("��ʵ�ܶ�(g/ml)��"));
	z += everyRow;
	lines.append(QLine(QPoint(edgeOffset, z), QPoint(rightW, z)));//�����2
	painter->drawText(edgeOffset, z, everyRow, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("1"));
	painter->drawText(k2 + ff, z, k3 - k2, everyRow, Qt::AlignVCenter | Qt::AlignLeft, QString::fromLocal8Bit("ͭ�̼����̼�϶(mm)��"));
	painter->drawText(k3 + ff, z, rightW - k3, everyRow, Qt::AlignVCenter | Qt::AlignLeft, QString::fromLocal8Bit("��ɫ�����ȷ�Χ��"));

	z += everyRow;
	lines.append(QLine(QPoint(edgeOffset, z), QPoint(k2, z)));//�����3
	painter->drawText(edgeOffset, z, everyRow, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("2"));
	painter->drawText(k2 + ff, z, k3 - k2, everyRow, Qt::AlignVCenter | Qt::AlignLeft, QString::fromLocal8Bit("Space between dosing"));
	painter->drawText(k3 + ff, z, rightW - k3, everyRow, Qt::AlignVCenter | Qt::AlignLeft, QString::fromLocal8Bit("ѹ�������״̬��"));
	z += everyRow;
	lines.append(QLine(QPoint(edgeOffset, z), QPoint(k2, z)));//�����4
	painter->drawText(edgeOffset, z, everyRow, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("3"));
	painter->drawText(k2 + ff, z, k3 - k2, everyRow, Qt::AlignVCenter | Qt::AlignLeft, QString::fromLocal8Bit("disk & copper ring��"));
	painter->drawText(k3 + ff, z, rightW - k3, everyRow, Qt::AlignVCenter | Qt::AlignLeft, QString::fromLocal8Bit("���ճ�������"));
	painter->drawText(k3 + ff + (rightW - k3) / 2 + 100, z, rightW - k3, everyRow, Qt::AlignVCenter | Qt::AlignLeft, QString::fromLocal8Bit("�����ԣ�"));
	z += everyRow;
	lines.append(QLine(QPoint(edgeOffset, z), QPoint(k2, z)));//�����5
	painter->drawText(edgeOffset, z, everyRow, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("4"));
	painter->drawText(k3 + ff, z, rightW - k3, everyRow, Qt::AlignVCenter | Qt::AlignLeft, QString::fromLocal8Bit("��ʪ�ԣ�"));
	painter->drawText(k3 + ff + (rightW - k3) / 3, z, rightW - k3, everyRow, Qt::AlignVCenter | Qt::AlignLeft, QString::fromLocal8Bit("͸���ԣ�"));
	painter->drawText(k3 + ff + 2 * (rightW - k3) / 3, z, rightW - k3, everyRow, Qt::AlignVCenter | Qt::AlignLeft, QString::fromLocal8Bit("ˮ�֣�"));
	z += everyRow;
	lines.append(QLine(QPoint(edgeOffset, z), QPoint(k2, z)));//�����6
	painter->drawText(edgeOffset, z, everyRow, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("5"));
	z += everyRow;
	lines.append(QLine(QPoint(edgeOffset, z), QPoint(rightW, z)));//�����7
	lines.append(QLine(QPoint(k1, tbt), QPoint(k1, z)));//�����2
	lines.append(QLine(QPoint(k2, tbt), QPoint(k2, z)));//�����3
	lines.append(QLine(QPoint(k3, tbt), QPoint(k3, z)));//�����4
	painter->drawText(edgeOffset + ff, z, innerW / 2, everyRow, Qt::AlignVCenter | Qt::AlignLeft, QString::fromLocal8Bit("�����̼��㹫ʽ��"));
	painter->drawText(edgeOffset + innerW / 2, z, innerW / 2, everyRow, Qt::AlignVCenter | Qt::AlignLeft, QString::fromLocal8Bit("(����Ӧȡ20��~100��������)"));
	z += everyRow;
	painter->drawText(edgeOffset + ff, z, innerW, everyRow, Qt::AlignVCenter | Qt::AlignLeft, QString::fromLocal8Bit("�������̺� = ����װֵ �� ʵ��װ������ �� �Ի��̺� (ȥ�Ǻ�ʵ��װ�����ȶ�ֵӦ��5%)"));
	z += everyRow;
	lines.append(QLine(QPoint(edgeOffset, z), QPoint(rightW, z)));//����

	float tbb = z;
	lines.append(QLine(QPoint(edgeOffset, tbt), QPoint(edgeOffset, z)));//�����
	lines.append(QLine(QPoint(rightW, tbt), QPoint(rightW, z)));//�����	
	painter->drawText(edgeOffset, z, innerW, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("����������������õ�����������(��ճ��ˡ����Ͽ���װ�á��¶ȵ���������ʡ����)"));
	painter->drawLines(lines);
	lines.clear();

	z += everyRow;
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("�����ٶ� Speed(��/����)��"));
	painter->drawText(edgeOffset + innerW / 2 + offs, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("������Ƶʱ��(����)��"));
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("���ҿǾ��ؼ���ȣ�       mg (      --      )mg"));
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW / 3, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("�����Ի�ʱ���������"));
	painter->drawText(edgeOffset + innerW / 3, z, innerW / 3, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("�Ի���������(Kg)��"));
	painter->drawText(edgeOffset + 2 * innerW / 3, z, innerW / 3, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("����,��Ʒ�Ƿ�Ļأ�"));

	z += everyRow;
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("�Ի�ʱ�䣺      ��   ��   ��   ʱ   ��"));
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("�ͻ���˾���Ʋ�ǩ��ȷ�ϣ�"));
	painter->drawText(edgeOffset + innerW / 2 + offs, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("������Աǩ�֣�"));
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("��(�Ի����ݼ���ӡ��)"));

	painter->drawText(edgeOffset, bottomH + 38, innerW, 60, Qt::AlignCenter, "1");
}
void DrawPicture::createTestingRecordsOnePage2(QPixmap *pix)
{

	QFont font;
	font.setPointSize(35);
	font.setFamily("����");
	//font.setItalic(true);//б��
	painter->setFont(font);

	int edgeOffset = 80;
	int innerW = pixWidth - 2 * edgeOffset;
	int inner50percentW = innerW / 2;
	int innerH = pixHeight - 2 * edgeOffset;
	int inner50percentH = innerH / 2;
	int rightW = pixWidth - edgeOffset;
	int bottomH = pixHeight - edgeOffset - 50;//Ϊ����Ԥ��50
	int firstLine = edgeOffset + 20;//���������
	int secondLine = firstLine + 8;

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
	QVector<QLine> lines;
	int tbl = secondLine;//�˴���Ϊͷ
	float everyRow = (bottomH - tbl) / 31.0;
	float everyColumn = (rightW - edgeOffset) / 13.0;

	painter->setPen(QPen(QColor(0, 0, 0), 2));
	lines.append(QLine(QPoint(edgeOffset, secondLine), QPoint(rightW, secondLine)));//ϸ
	lines.append(QLine(QPoint(edgeOffset, bottomH + 30), QPoint(rightW, bottomH + 30)));//ϸ
	painter->drawLines(lines);
	lines.clear();

	painter->setPen(QPen(QColor(0, 0, 0), 5));
	lines.append(QLine(QPoint(edgeOffset, firstLine), QPoint(rightW, firstLine)));//��
	lines.append(QLine(QPoint(edgeOffset, bottomH + 38), QPoint(rightW, bottomH + 38)));//��
	painter->drawLines(lines);
	lines.clear();



	font.setPointSize(50);
	painter->setFont(font);
	painter->drawText(edgeOffset, 0, innerW, 100, Qt::AlignHCenter | Qt::AlignVCenter, QString::fromLocal8Bit("���ֺ���Ƽ���չ�ɷݹ�˾"));

	font.setPointSize(35);
	painter->setFont(font);
	QDateTime dt = QDateTime::currentDateTime();
	painter->drawText(edgeOffset, 0, innerW, 90, Qt::AlignRight | Qt::AlignBottom, QString::fromLocal8Bit("���ڣ�") + YearMonthDay());

	font.setPointSize(45);
	painter->setFont(font);

	painter->drawText(edgeOffset, tbl, innerW, everyRow, Qt::AlignHCenter | Qt::AlignBottom, QString::fromLocal8Bit("����ѹƬ���Ի���¼ (�ֹ���д)"));
	float z = everyRow + tbl;
	//painter->drawText(edgeOffset, z, innerW, everyRow, Qt::AlignHCenter | Qt::AlignBottom, QString::fromLocal8Bit("Capsule Filling Machine Testing Records"));

	font.setPointSize(30);
	painter->setFont(font);
	float offs = 150;
	painter->drawText(edgeOffset, z, innerW / 3, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("�Ի����ң�"));
	painter->drawText(edgeOffset + innerW / 3 + offs, z, innerW / 3, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("ѹƬ���ͣ�"));
	painter->drawText(edgeOffset + 2*innerW / 3 + offs, z, innerW / 3, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("���ʪ��(%)��"));
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW / 3, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("ҩ�����ƣ�"));
	painter->drawText(edgeOffset + innerW / 3 + offs, z, innerW / 3, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("װ�߹��"));
	painter->drawText(edgeOffset + 2*innerW / 3 + offs, z, innerW / 3, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("�����¶�(��)��"));
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW / 3, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("ҩ�����ͣ�  ��ҩ   ��ҩ"));
	painter->drawText(edgeOffset + innerW / 3 + offs, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("ˮ��(%)��"));
	painter->drawText(edgeOffset + 2*innerW / 3 + offs, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("���ܶ�(g/ml)��"));
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW / 3, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("ҩ������������"));
	z += everyRow;
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW / 3, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("�Ի�Ŀ�ģ��豸FAT ��"));
	painter->drawText(edgeOffset + innerW / 3 + offs, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("��ǰ���� ��"));
	painter->drawText(edgeOffset + 2*innerW / 3 + offs, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("������� ��"));
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("          �豸��ţ�"));
	z += everyRow;
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("�����Է�����(kg)��"));
	painter->drawText(edgeOffset + innerW / 2 + offs, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("������Ƶʱ��(����)��"));
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("���ϡ���Ʒ�Ƿ񷵻أ�"));
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("����������������õ����⼼����"));
	z += everyRow;
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("�ͻ����Ƽ�ȷ��ǩ�֣�"));
	painter->drawText(edgeOffset + innerW / 2 + offs, z, innerW / 2, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("���ֵ�����Աǩ�֣�"));

	z += everyRow;
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("�Ի����ڣ�      ��   ��   ��"));

	z += everyRow;
	z += everyRow;
	painter->drawText(edgeOffset, z, innerW, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("�������"));


	z += everyRow;
	float tbt = z;
	float k1 = innerW / 9.0 + edgeOffset;
	float k2 = innerW / 9.0 * 2 + k1;
	float k3 = innerW / 9.0 * 4 + k1;
	float k4 = innerW / 9.0 * 6 + k1;
	float ff = 20;
	painter->setPen(QPen(QColor(0, 0, 0), 2));
	lines.append(QLine(QPoint(edgeOffset, z), QPoint(rightW, z)));//�����	
	painter->drawText(k1, z, k2 - k1, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("��1��(˫������վ)"));
	painter->drawText(k2, z, k3 - k2, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("��2��(˫������վ)"));
	painter->drawText(k3, z, k4 - k3, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("��3��(˫������վ)"));
	painter->drawText(k4, z, rightW - k4, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("��4��(˫������վ)"));

	z += everyRow;
	lines.append(QLine(QPoint(edgeOffset, z), QPoint(rightW, z)));//�����2
	painter->drawText(edgeOffset, z, innerW / 9.0, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("Ƭ��"));
	painter->drawText(k1, z, k2 - k1, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("(       -       )mm"));
	painter->drawText(k2, z, k3 - k2, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("(       -       )mm"));
	painter->drawText(k3, z, k4 - k3, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("(       -       )mm"));
	painter->drawText(k4, z, rightW - k4, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("(       -       )mm"));
	z += everyRow;
	lines.append(QLine(QPoint(edgeOffset, z), QPoint(rightW, z)));//�����3
	painter->drawText(edgeOffset, z, innerW / 9.0, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("�����"));
	painter->drawText(k1, z, k2 - k1, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("                 %"));
	painter->drawText(k2, z, k3 - k2, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("                 %"));
	painter->drawText(k3, z, k4 - k3, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("                 %"));
	painter->drawText(k4, z, rightW - k4, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("                 %"));

	z += everyRow;
	lines.append(QLine(QPoint(edgeOffset, z), QPoint(rightW, z)));//�����4
	painter->drawText(edgeOffset, z, innerW / 9.0, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("Ӳ��"));
	painter->drawText(k1, z, k2 - k1, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("(       -       )kg"));
	painter->drawText(k2, z, k3 - k2, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("(       -       )kg"));
	painter->drawText(k3, z, k4 - k3, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("(       -       )kg"));
	painter->drawText(k4, z, rightW - k4, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("(       -       )kg"));
	z += everyRow;
	lines.append(QLine(QPoint(edgeOffset, z), QPoint(rightW, z)));//�����5
	painter->drawText(edgeOffset, z, innerW / 9.0, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("����ʱ��"));
	painter->drawText(k1, z, k2 - k1, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("                 min"));
	painter->drawText(k2, z, k3 - k2, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("                 min"));
	painter->drawText(k3, z, k4 - k3, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("                 min"));
	painter->drawText(k4, z, rightW - k4, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("                 min"));

	z += everyRow;
	lines.append(QLine(QPoint(edgeOffset, z), QPoint(rightW, z)));//����

	lines.append(QLine(QPoint(k1, tbt), QPoint(k1, z)));//�����2
	lines.append(QLine(QPoint(k2, tbt), QPoint(k2, z)));//�����3
	lines.append(QLine(QPoint(k3, tbt), QPoint(k3, z)));//�����4
	lines.append(QLine(QPoint(k4, tbt), QPoint(k4, z)));//�����5

	float tbb = z;
	lines.append(QLine(QPoint(edgeOffset, tbt), QPoint(edgeOffset, z)));//�����
	lines.append(QLine(QPoint(rightW, tbt), QPoint(rightW, z)));//�����	

	z += everyRow;
	painter->drawText(edgeOffset, z, innerW, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("�������"));
	z += everyRow;

	tbt = z;
	painter->setPen(QPen(QColor(0, 0, 0), 2));
	lines.append(QLine(QPoint(edgeOffset, z), QPoint(rightW, z)));//�����	
	painter->drawText(k1, z, k2 - k1, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("��5��(˫������վ)"));
	painter->drawText(k2, z, k3 - k2, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("��6��(˫������վ)"));
	painter->drawText(k3, z, k4 - k3, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("��7��(˫������վ)"));
	painter->drawText(k4, z, rightW - k4, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("��8��(˫������վ)"));

	z += everyRow;
	lines.append(QLine(QPoint(edgeOffset, z), QPoint(rightW, z)));//�����2
	painter->drawText(edgeOffset, z, innerW / 9.0, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("Ƭ��"));
	painter->drawText(k1, z, k2 - k1, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("(       -       )mm"));
	painter->drawText(k2, z, k3 - k2, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("(       -       )mm"));
	painter->drawText(k3, z, k4 - k3, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("(       -       )mm"));
	painter->drawText(k4, z, rightW - k4, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("(       -       )mm"));
	z += everyRow;
	lines.append(QLine(QPoint(edgeOffset, z), QPoint(rightW, z)));//�����3
	painter->drawText(edgeOffset, z, innerW / 9.0, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("�����"));
	painter->drawText(k1, z, k2 - k1, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("                 %"));
	painter->drawText(k2, z, k3 - k2, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("                 %"));
	painter->drawText(k3, z, k4 - k3, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("                 %"));
	painter->drawText(k4, z, rightW - k4, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("                 %"));

	z += everyRow;
	lines.append(QLine(QPoint(edgeOffset, z), QPoint(rightW, z)));//�����4
	painter->drawText(edgeOffset, z, innerW / 9.0, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("Ӳ��"));
	painter->drawText(k1, z, k2 - k1, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("(       -       )kg"));
	painter->drawText(k2, z, k3 - k2, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("(       -       )kg"));
	painter->drawText(k3, z, k4 - k3, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("(       -       )kg"));
	painter->drawText(k4, z, rightW - k4, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("(       -       )kg"));
	z += everyRow;
	lines.append(QLine(QPoint(edgeOffset, z), QPoint(rightW, z)));//�����5
	painter->drawText(edgeOffset, z, innerW / 9.0, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("����ʱ��"));
	painter->drawText(k1, z, k2 - k1, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("                 min"));
	painter->drawText(k2, z, k3 - k2, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("                 min"));
	painter->drawText(k3, z, k4 - k3, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("                 min"));
	painter->drawText(k4, z, rightW - k4, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("                 min"));

	z += everyRow;
	lines.append(QLine(QPoint(edgeOffset, z), QPoint(rightW, z)));//����

	lines.append(QLine(QPoint(k1, tbt), QPoint(k1, z)));//�����2
	lines.append(QLine(QPoint(k2, tbt), QPoint(k2, z)));//�����3
	lines.append(QLine(QPoint(k3, tbt), QPoint(k3, z)));//�����4
	lines.append(QLine(QPoint(k4, tbt), QPoint(k4, z)));//�����5

	tbb = z;
	lines.append(QLine(QPoint(edgeOffset, tbt), QPoint(edgeOffset, z)));//�����
	lines.append(QLine(QPoint(rightW, tbt), QPoint(rightW, z)));//�����	

	painter->drawLines(lines);
	lines.clear();
	painter->drawText(edgeOffset, z, innerW, everyRow, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit("��(Ƭ�����ݼ���ӡ��)"));

	painter->drawText(edgeOffset, bottomH + 38, innerW, 60, Qt::AlignCenter, "1");
}
QString DrawPicture::YearMonthDay()
{
	QString strTime;
	QDateTime current_time = QDateTime::currentDateTime();
	QString logYear = QString::number(current_time.date().year());
	logYear = logYear.length() < 4 ? ("0" + logYear) : logYear;
	QString logMonth = QString::number(current_time.date().month());
	logMonth = logMonth.length() < 2 ? ("0" + logMonth) : logMonth;
	QString logDay = QString::number(current_time.date().day());
	logDay = logDay.length() < 2 ? ("0" + logDay) : logDay;
	strTime = logYear + QString::fromLocal8Bit("��")
		+ logMonth + QString::fromLocal8Bit("��")
		+ logDay + QString::fromLocal8Bit("��");
	return strTime;
}
void DrawPicture::createTestingRecords(QPixmap *pix,int pagei)
{

	QFont font;
	font.setPointSize(35);
	font.setFamily("����");
	//font.setItalic(true);//б��
	painter->setFont(font);

	int edgeOffset = 80;
	int innerW = pixWidth - 2 * edgeOffset;
	int inner50percentW = innerW / 2;
	int innerH = pixHeight - 2 * edgeOffset;
	int inner50percentH = innerH / 2;
	int rightW = pixWidth - edgeOffset;
	int bottomH = pixHeight - edgeOffset-50;//Ϊ����Ԥ��50
	int firstLine = edgeOffset+20;//���������
	int secondLine = firstLine + 8;

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
	QVector<QLine> lines;
	int tbl = edgeOffset + 120;
	float everyRow = (bottomH - tbl) / 32.0;
	float everyColumn = (rightW - edgeOffset) / 13.0;

		painter->setPen(QPen(QColor(0, 0, 0), 2));
		lines.append(QLine(QPoint(edgeOffset, tbl), QPoint(rightW, tbl)));//�ϱ�
		lines.append(QLine(QPoint(rightW, tbl), QPoint(rightW, bottomH)));//�ұ�
		lines.append(QLine(QPoint(edgeOffset, bottomH), QPoint(rightW, bottomH)));//�±�
		lines.append(QLine(QPoint(edgeOffset, tbl), QPoint(edgeOffset, bottomH)));//���
		lines.append(QLine(QPoint(edgeOffset, secondLine), QPoint(rightW, secondLine)));//ϸ
		lines.append(QLine(QPoint(edgeOffset, bottomH+30), QPoint(rightW, bottomH + 30)));//ϸ

		for (int i = 0; i < 3; i++)
		{
			lines.append(QLine(QPoint(edgeOffset + everyColumn * (1 + 4 * i), tbl), QPoint(edgeOffset + everyColumn * (1 + 4 * i), bottomH)));//�
			lines.append(QLine(QPoint(edgeOffset + everyColumn * (4 * (i + 1) - 1), tbl + everyRow), QPoint(edgeOffset + everyColumn * (4 * (i + 1) - 1), bottomH - 5 * everyRow)));//����м�
		}
		for (int i = 0; i < 6; i++)
		{
			lines.append(QLine(QPoint(edgeOffset + everyColumn * (2 * (i+1)), tbl+everyRow), QPoint(edgeOffset + everyColumn * (2 * (1+i)), bottomH-5* everyRow)));//�������
		}
		for (int i = 0; i < 28; i++)
		{
			lines.append(QLine(QPoint(edgeOffset, tbl + (everyRow*(1 + i))), QPoint(rightW, tbl + (everyRow*(1 + i)))));
			if (i<26)
			{
				painter->drawText(edgeOffset, tbl + (everyRow*(1 + i)), everyColumn, everyRow, Qt::AlignCenter, QString::number(i + 1));

			}
		}
		//painter->drawText(edgeOffset, tbl + everyRow * 27, everyColumn, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("����"));
		painter->drawText(edgeOffset, tbl + everyRow * 29, everyColumn, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("ȥ��"));
		QString s = QString::number(m_PureShell[pagei*3]) + "mg";
		painter->drawText(edgeOffset, tbl + everyRow * 30, everyColumn, everyRow, Qt::AlignCenter, s);

		painter->drawLines(lines);
		lines.clear();

		painter->setPen(QPen(QColor(0, 0, 0), 5));
		lines.append(QLine(QPoint(edgeOffset, firstLine), QPoint(rightW, firstLine)));//��
		lines.append(QLine(QPoint(edgeOffset, bottomH + 38), QPoint(rightW, bottomH + 38)));//��
		painter->drawLines(lines);
		lines.clear();


		font.setPointSize(30);
		painter->setFont(font);
		painter->drawText(edgeOffset, bottomH + 38, innerW, 60, Qt::AlignCenter, QString::number(pagei+2));

		font.setPointSize(50);
		painter->setFont(font);
		painter->drawText(edgeOffset, 0, innerW, 100, Qt::AlignHCenter | Qt::AlignVCenter, QString::fromLocal8Bit("���ֺ���Ƽ���չ�ɷݹ�˾"));

		font.setPointSize(35);
		painter->setFont(font);
		painter->drawText(edgeOffset, 0, innerW, 90, Qt::AlignRight | Qt::AlignBottom, QString::fromLocal8Bit("���ڣ�") + YearMonthDay());
		s = QString::fromLocal8Bit("�Ի�����:")+ m_CustomerName[pagei * 3];
		painter->drawText(edgeOffset, secondLine, innerW / 2, tbl - secondLine, Qt::AlignLeft | Qt::AlignVCenter, s);
		s = QString::fromLocal8Bit("ҩƷ����:") + m_MedicineName[pagei * 3];
		painter->drawText(edgeOffset + innerW / 3 + 100, secondLine, innerW / 2, tbl - secondLine, Qt::AlignLeft | Qt::AlignVCenter, s);
		s = QString::fromLocal8Bit("Ҫ���ط�Χ:") + QString::number(m_Low[pagei * 3])+ "mg - "+ QString::number(m_High[pagei * 3])+"mg";
		painter->drawText(edgeOffset + 2 * innerW / 3+50, secondLine, innerW / 2, tbl - secondLine, Qt::AlignLeft | Qt::AlignVCenter, s);

	painter->setBrush(QBrush(Qt::gray, Qt::SolidPattern));//���û�ˢ��ʽ 
	for (int k=0;k<3;k++)
	{
		int j = pagei * 3 + k;
		if (j >= data.size())
		{
			break;
		}
		QVector<float> d = data[j];
		auto max = std::max_element(std::begin(d), std::end(d));
		float fmax = *max;
		int imax = fmax * 1000;
		auto min = std::min_element(std::begin(d), std::end(d));
		float fmin = *min;
		int imin = fmin * 1000;
		float fsum = 0;
		for (int i=0;i<d.size();i++)
		{
			int id = d[i] * 1000;
			if (id==imin||id==imax)
			{
				painter->drawRect(edgeOffset + everyColumn * (1 + i / 26 + 4 * (k % 3)), tbl + (everyRow*(1 + i % 26)), everyColumn, everyRow);
			}
			painter->drawText(edgeOffset + everyColumn * (1 + i / 26 + 4 * (k % 3)), tbl + (everyRow*(1 + i%26)) , everyColumn, everyRow, Qt::AlignCenter, QString::number(id));
			fsum += d[i];
		}
		float fave = fsum * 1000 / d.size();
		QString str = QString::fromLocal8Bit("���Ǿ��أ�") + QString::number(fave, 'f', 1) + "mg";
		painter->drawText(edgeOffset + everyColumn * (1 + 4 * (k % 3)), tbl + (everyRow * 27), everyColumn * 4, everyRow, Qt::AlignCenter, str);
		float fave2 = fsum * 1000  / d.size() - m_PureShell[j];
		str = QString::fromLocal8Bit("���أ�") + QString::number(fave2, 'f', 1) + "mg";
		painter->drawText(edgeOffset + everyColumn * (1 + 4 * (k % 3)), tbl + (everyRow * 28), everyColumn * 4, everyRow, Qt::AlignCenter, str);
		float SD = 0.0;
		float RSD = 0.0;
		if (d.size()==1||fave2==0)
		{

		}
		else
		{
			for (int i = 0; i < d.size(); i++)
			{
				SD += (d[i] * 1000- m_PureShell[pagei * 3] - fave2)* (d[i] * 1000 - m_PureShell[pagei * 3] - fave2);
			}
			SD = SD / (d.size()-1);
			SD = sqrt(SD);
			RSD = SD / fave2*100;
		}
		str = QString::fromLocal8Bit("RSD��") + QString::number(RSD, 'f', 2) + "%";
		painter->drawText(edgeOffset + everyColumn * (1 + 4 * (k % 3)), tbl + (everyRow * 29), everyColumn * 4, everyRow, Qt::AlignCenter, str);
		str = QString::fromLocal8Bit("���أ�") + QString::number(imax- m_PureShell[j]) + "mg";
		painter->drawText(edgeOffset + everyColumn * (1 + 4 * (k % 3)), tbl + (everyRow * 30), everyColumn * 4, everyRow, Qt::AlignCenter, str);
		str = QString::fromLocal8Bit("���᣺") + QString::number(imin- m_PureShell[j]) + "mg";
		painter->drawText(edgeOffset + everyColumn * (1 + 4 * (k % 3)), tbl + (everyRow * 31), everyColumn * 4, everyRow, Qt::AlignCenter, str);

		QStringList gnum = m_gn[k + pagei * 3].split(",");
		painter->drawText(edgeOffset + everyColumn * (1 + 4 * (k % 3)), tbl, everyColumn * 4, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("��") + QString::number(k + pagei * 3 + 1) + QString::fromLocal8Bit("�� (ID:") +gnum.at(0) + ")");
	}

}
void DrawPicture::createTestingRecords2(QPixmap *pix, int pagei)
{

	QFont font;
	font.setPointSize(35);
	font.setFamily("����");
	//font.setItalic(true);//б��
	painter->setFont(font);

	int edgeOffset = 80;
	int innerW = pixWidth - 2 * edgeOffset;
	int inner50percentW = innerW / 2;
	int innerH = pixHeight - 2 * edgeOffset;
	int inner50percentH = innerH / 2;
	int rightW = pixWidth - edgeOffset;
	int bottomH = pixHeight - edgeOffset - 50;//Ϊ����Ԥ��50
	int firstLine = edgeOffset + 20;//���������
	int secondLine = firstLine + 8;

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
	QVector<QLine> lines;
	int tbl = edgeOffset + 120;
	float everyRow = (bottomH - tbl) / 39.0;
	float everyColumn = (rightW - edgeOffset) / 13.0;

	painter->setPen(QPen(QColor(0, 0, 0), 2));
	lines.append(QLine(QPoint(edgeOffset, tbl), QPoint(rightW, tbl)));//�ϱ�
	lines.append(QLine(QPoint(rightW, tbl), QPoint(rightW, bottomH)));//�ұ�
	lines.append(QLine(QPoint(edgeOffset, bottomH), QPoint(rightW, bottomH)));//�±�
	lines.append(QLine(QPoint(edgeOffset, tbl), QPoint(edgeOffset, bottomH)));//���
	lines.append(QLine(QPoint(edgeOffset, secondLine), QPoint(rightW, secondLine)));//ϸ
	lines.append(QLine(QPoint(edgeOffset, bottomH + 30), QPoint(rightW, bottomH + 30)));//ϸ

	painter->drawText(edgeOffset, tbl, everyColumn, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("����"));
	painter->drawText(edgeOffset, tbl + everyRow, everyColumn, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("ѹ��"));
	painter->drawText(edgeOffset, tbl + everyRow * 2, everyColumn, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("ת��"));
	painter->drawText(edgeOffset, tbl + everyRow * 3, everyColumn, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("ȡ��"));
	painter->drawText(edgeOffset, tbl + everyRow * 4, everyColumn, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("���"));

	for (int i = 0; i < 4; i++)
	{
		int j = pagei * 4 + i;
		lines.append(QLine(QPoint(edgeOffset + everyColumn * (1 + 3 * i), tbl), QPoint(edgeOffset + everyColumn * (1 + 3 * i), bottomH)));//�
		lines.append(QLine(QPoint(edgeOffset + everyColumn * (3 * (i + 1) - 1), tbl + 5 * everyRow), QPoint(edgeOffset + everyColumn * (3 * (i + 1) - 1), bottomH - 4 * everyRow)));//�����
		lines.append(QLine(QPoint(edgeOffset + everyColumn * (3 * (i + 1)), tbl + 5 * everyRow), QPoint(edgeOffset + everyColumn * (3 * (i + 1)), bottomH - 4 * everyRow)));//�����

	}

	for (int i = 0; i < 38; i++)
	{
		lines.append(QLine(QPoint(edgeOffset, tbl + (everyRow*(1 + i))), QPoint(rightW, tbl + (everyRow*(1 + i)))));
		if (i <= 33 && i>=4)
		{
			painter->drawText(edgeOffset, tbl + (everyRow*(1 + i)), everyColumn, everyRow, Qt::AlignCenter, QString::number(i-3));

		}
	}
	painter->drawText(edgeOffset, tbl + everyRow * 35, everyColumn, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("����"));
	painter->drawText(edgeOffset, tbl + everyRow * 36, everyColumn, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("RSD"));
	painter->drawText(edgeOffset, tbl + everyRow * 37, everyColumn, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("����"));
	painter->drawText(edgeOffset, tbl + everyRow * 38, everyColumn, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("����"));

	QString s;
	/*painter->drawText(edgeOffset, tbl + everyRow * 30, everyColumn, everyRow, Qt::AlignCenter, s);*/

	painter->drawLines(lines);
	lines.clear();

	painter->setPen(QPen(QColor(0, 0, 0), 5));
	lines.append(QLine(QPoint(edgeOffset, firstLine), QPoint(rightW, firstLine)));//��
	lines.append(QLine(QPoint(edgeOffset, bottomH + 38), QPoint(rightW, bottomH + 38)));//��
	painter->drawLines(lines);
	lines.clear();


	font.setPointSize(30);
	painter->setFont(font);
	painter->drawText(edgeOffset, bottomH + 38, innerW, 60, Qt::AlignCenter, QString::number(pagei + 2));

	font.setPointSize(50);
	painter->setFont(font);
	painter->drawText(edgeOffset, 0, innerW, 100, Qt::AlignHCenter | Qt::AlignVCenter, QString::fromLocal8Bit("���ֺ���Ƽ���չ�ɷݹ�˾"));

	font.setPointSize(35);
	painter->setFont(font);
	painter->drawText(edgeOffset, 0, innerW, 90, Qt::AlignRight | Qt::AlignBottom, QString::fromLocal8Bit("���ڣ�") + YearMonthDay());
	s = QString::fromLocal8Bit("�Ի�����:") + m_CustomerName[pagei * 3];
	painter->drawText(edgeOffset, secondLine, innerW / 2, tbl - secondLine, Qt::AlignLeft | Qt::AlignVCenter, s);
	s = QString::fromLocal8Bit("ҩƷ����:") + m_MedicineName[pagei * 3];
	painter->drawText(edgeOffset + innerW / 3 + 100, secondLine, innerW / 2, tbl - secondLine, Qt::AlignLeft | Qt::AlignVCenter, s);
	s = QString::fromLocal8Bit("Ҫ��Ƭ�ط�Χ:") + QString::number(m_Low[pagei * 3]) + "mg - " + QString::number(m_High[pagei * 3]) + "mg";
	painter->drawText(edgeOffset + 2 * innerW / 3 + 50, secondLine, innerW / 2, tbl - secondLine, Qt::AlignLeft | Qt::AlignVCenter, s);

	painter->setBrush(QBrush(Qt::gray, Qt::SolidPattern));//���û�ˢ��ʽ 
	for (int k = 0; k < 4; k++)
	{
		int j = pagei * 4 + k;
		if (j >= data.size())
		{
			break;
		}
		QVector<float> d = data[j];
		auto max = std::max_element(std::begin(d), std::end(d));
		float fmax = *max;
		int imax = fmax * 1000;
		auto min = std::min_element(std::begin(d), std::end(d));
		float fmin = *min;
		int imin = fmin * 1000;
		float fsum = 0;
		for (int i = 0; i < d.size(); i++)
		{
			int id = d[i] * 1000;
			if (id == imin || id == imax)
			{
				painter->drawRect(edgeOffset + everyColumn * (1 + i / 30 + 3 * (k % 4)), tbl + (everyRow*(5 + i % 30)), everyColumn, everyRow);
			}
			painter->drawText(edgeOffset + everyColumn * (1 + i / 30 + 3 * (k % 4)), tbl + (everyRow*(5 + i % 30)), everyColumn, everyRow, Qt::AlignCenter, QString::number(id));
			fsum += d[i];
		}
		QString str;
		/*float fave = fsum * 1000 / d.size();
		str = QString::fromLocal8Bit("���Ǿ��أ�") + QString::number(fave, 'f', 1) + "mg";
		painter->drawText(edgeOffset + everyColumn * (1 + 4 * (k % 4)), tbl + (everyRow * 34), everyColumn * 3, everyRow, Qt::AlignCenter, str);*/
		float fave2 = fsum * 1000 / d.size();
		str = /*QString::fromLocal8Bit("���أ�") + */QString::number(fave2, 'f', 1) + "mg";
		painter->drawText(edgeOffset + everyColumn * (1 + 3 * (k % 4)), tbl + (everyRow * 35), everyColumn * 3, everyRow, Qt::AlignCenter, str);
		float SD = 0.0;
		float RSD = 0.0;
		if (d.size() == 1 || fave2 == 0)
		{

		}
		else
		{
			for (int i = 0; i < d.size(); i++)
			{
				SD += (d[i] * 1000 - fave2)* (d[i] * 1000- fave2);
			}
			SD = SD / (d.size() - 1);
			SD = sqrt(SD);
			RSD = SD / fave2 * 100;
		}
		str = /*QString::fromLocal8Bit("RSD��") + */QString::number(RSD, 'f', 2) + "%";
		painter->drawText(edgeOffset + everyColumn * (1 + 3 * (k % 4)), tbl + (everyRow * 36), everyColumn * 3, everyRow, Qt::AlignCenter, str);
		str = /*QString::fromLocal8Bit("���أ�") + */QString::number(imax) + "mg";
		painter->drawText(edgeOffset + everyColumn * (1 + 3 * (k % 4)), tbl + (everyRow * 37), everyColumn * 3, everyRow, Qt::AlignCenter, str);
		str =/* QString::fromLocal8Bit("���᣺") + */QString::number(imin) + "mg";
		painter->drawText(edgeOffset + everyColumn * (1 + 3 * (k % 4)), tbl + (everyRow * 38), everyColumn * 3, everyRow, Qt::AlignCenter, str);		
		
		painter->drawText(edgeOffset + everyColumn * (1 + 3 * (k % 4)), tbl, everyColumn * 3, everyRow, Qt::AlignCenter, QString::number(m_Yield[j]) + QString::fromLocal8Bit("��Ƭ/Сʱ"));
		painter->drawText(edgeOffset + everyColumn * (1 + 3 * (k % 4)), tbl + everyRow, everyColumn * 3, everyRow, Qt::AlignCenter, QString::number(m_Pressure[j]) + "KN");
		painter->drawText(edgeOffset + everyColumn * (1 + 3 * (k % 4)), tbl + everyRow * 2, everyColumn * 3, everyRow, Qt::AlignCenter, QString::number(m_Speed[j]) + QString::fromLocal8Bit("ת/��"));
		if (k % 2 == 0)
		{
			painter->drawText(edgeOffset + everyColumn * (1 + 3 * (k % 4)), tbl + everyRow * 3, everyColumn * 3, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("��") + QString::number(k + pagei * 3 + 1) + QString::fromLocal8Bit("��(˫������վ)"));
		}
		else
		{
			painter->drawText(edgeOffset + everyColumn * (1 + 3 * (k % 4)), tbl + everyRow * 3, everyColumn * 3, everyRow, Qt::AlignCenter, QString::fromLocal8Bit("��") + QString::number(k + pagei * 3 + 1) + QString::fromLocal8Bit("��(˫������վ)"));
		}		
		QStringList gnum = m_gn[k + pagei * 4].split(",");
		painter->drawText(edgeOffset + everyColumn * (1 + 3 * (k % 4)), tbl + everyRow * 4, everyColumn * 3, everyRow, Qt::AlignCenter, gnum.at(0));

	}

}
void DrawPicture::createPixCurve(QPixmap *pix)
{
	//painter->setRenderHints(QPainter::SmoothPixmapTransform);//����� 
	painter->begin(pix);

	painter->setRenderHint(QPainter::Antialiasing, true);//������
	//QRect rect(0, 0, pixWidth, pixHeight);
	//painter->fillRect(rect, Qt::white);

	// ���û�����ɫ�����
	painter->setPen(QPen(QColor(255, 255, 255), 1));
	// ���û�ˢ��ɫ
	painter->setBrush(QColor(255, 255, 255));

	int edgeOffset = 80;
	int innerW = pixWidth - 2 * edgeOffset;
	int inner50percentW = innerW / 2;
	int innerH = pixHeight - 2 * edgeOffset;
	int inner50percentH = innerH / 2;
	int rightW = pixWidth - edgeOffset;
	int bottomH = pixHeight - edgeOffset;
	int firstLine = edgeOffset+60;//���������
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

	//����ͼ���û�ˢ�׵�	
	QFont font;
	font.setPointSize(23);
	font.setFamily("����");
	//font.setItalic(true);//б��
	painter->setFont(font);
	//painter->fillRect(rect, QColor(255, 255, 255));//maybe a bug
	//painter->drawRect(rect);

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
			lst << " " << " " << " ";
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
				painter->drawText(edgeOffset+10, actualBottom - 25 + simpleFun, 150, 50, Qt::AlignVCenter, QString::number(m_dmin[totalMachineCount], 'f', 3));//MIN
				painter->drawText(edgeOffset + 10, actualTop - 25 + simpleFun, 150, 50, Qt::AlignVCenter, QString::number(m_dmax[totalMachineCount], 'f', 3));//MAX
				painter->drawText(edgeOffset + 10, actualBottom - 25 + simpleFun - (m_dave[totalMachineCount] - m_dmin[totalMachineCount]) / (m_dmax[totalMachineCount] - m_dmin[totalMachineCount]) * YActualLength, 150, 50, Qt::AlignVCenter, QString::number(m_dave[totalMachineCount], 'f', 4));//AVE			
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

		lines.append(QLine(QPoint(edgeOffset + 250, edgeOffset + simpleFun), QPoint(edgeOffset + 250, firstLine + simpleFun)));//����1
		lines.append(QLine(QPoint(edgeOffset + innerW * 1.0 / 3 * 2, edgeOffset + simpleFun), QPoint(edgeOffset + innerW * 1.0 / 3 * 2, firstLine + simpleFun)));//����2
		lines.append(QLine(QPoint(edgeOffset + 250 + innerW * 1.0 / 3 * 2, edgeOffset + simpleFun), QPoint(edgeOffset + 250 + innerW * 1.0 / 3 * 2, firstLine + simpleFun)));//����3
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
		painter->drawText(edgeOffset, edgeOffset + simpleFun, 250, 60, Qt::AlignCenter, QString::fromLocal8Bit("�豸�ͺ�"));
		painter->drawText(edgeOffset + 275, edgeOffset + simpleFun, innerW * 1.0 / 2 - 250, 60, Qt::AlignVCenter, m_ptnm);
		painter->drawText(edgeOffset + innerW * 1.0 / 3 * 2, edgeOffset + simpleFun, 250, 60, Qt::AlignCenter, QString::fromLocal8Bit("���"));

		painter->drawText(edgeOffset + innerW * 1.0 / 3 * 2 + 275, edgeOffset + simpleFun, edgeOffset + innerW * 1.0 / 3 * 2 - 250, 60, Qt::AlignVCenter, lst.at(0));
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
			float fsum = 0;
			for (int i = 0; i < data_One[totalMachineCount].size(); i++) {
				painter->drawText(edgeOffset + i % weightColumnCount * weightColumnAve + 70, weightMiddle + simpleFun + i / weightColumnCount % weightRowCount * weightRowAve, weightColumnAve - 60, weightRowAve, Qt::AlignVCenter, QString::number(data_One[totalMachineCount].at(i), 'f', 3));
				fsum += data_One[totalMachineCount].at(i);
			}
			QString str;
			float SD = 0.0;
			float RSD = 0.0;
			if (data_One[totalMachineCount].size() == 1 || m_dave[totalMachineCount] == 0)
			{

			}
			else
			{
				for (int i = 0; i < data_One[totalMachineCount].size(); i++)
				{
					SD += (data_One[totalMachineCount].at(i) * 1000 - m_dave[totalMachineCount] * 1000)* (data_One[totalMachineCount].at(i) * 1000 - m_dave[totalMachineCount]*1000);
				}
				SD = SD / (data_One[totalMachineCount].size() - 1);
				SD = sqrt(SD);
				RSD = SD / (m_dave[totalMachineCount] * 1000) * 100;
			}
			str = QString::fromLocal8Bit("RSD = ") + QString::number(RSD, 'f', 2) + "%"; 
			painter->drawText(innerW-300, YTop - 50 + simpleFun, 300, 50, Qt::AlignCenter, str);//����
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

	int edgeOffset = 60;
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

void DrawPicture::caculateData(QVector<QVector<float>> transData,QVector<QString> gn, int ivalue, int half, QVector<float> theory)//0 1 2
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
		m_dtheory[0] = theory[ivalue];
	}
	else
	{
		data_One[0] = transData[ivalue];
		data_One[1] = transData[ivalue + 1];
		gn_One[0] = gn[ivalue];
		gn_One[1] = gn[ivalue + 1];
		m_dtheory[0] = theory[ivalue];
		m_dtheory[1] = theory[ivalue+1];
	}
	for (int i = 0; i < 2; i++)
	{
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

void DrawPicture::setData(QVector<QVector<float>> sourcedata,QVector<QString> gn, int i, int j, QVector<float> f,QVector<QString> CustomerName, QVector<QString> MedicineName, QVector<int> lo, QVector<int> hi, QVector<int> pureshell, QString cb, QVector<int> yed, QVector<int> pre, QVector<int> spd, QVector<QVector<float>>thickness, QVector<QVector<float>>hardness)
{
	data = sourcedata;
	m_gn = gn;
	m_ftheory = f;
	m_iPrintCurveCount = i;
	m_iPrintAveCount = 0;
	m_iTestingRecords = j;

	m_CustomerName = CustomerName;
	m_MedicineName = MedicineName;
	m_Low = lo;
	m_High = hi;
	m_PureShell = pureshell;
	m_cb = cb;


	m_Yield = yed;
	m_Pressure = pre;
	m_Speed = spd;

	m_Thickness = thickness;
	m_Hardness = hardness;
}