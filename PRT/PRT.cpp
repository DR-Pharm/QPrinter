#include "PRT.h"

PRT::PRT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QPrinterInfo info;
	m_sName = info.defaultPrinterName(); // Ĭ�ϴ�ӡ������
	ui.lb_PrinterName->setText(QString::fromLocal8Bit("��ǰ���Ӵ�ӡ����") + m_sName);

	m_prt = new QPrinter();
	m_prt->setPrinterName(m_sName);

	data_One << 0.369 << 0.321 << 0.332 << 0.311 << 0.399 << 0.334 << 0.321 << 0.346 << 0.389 << 0.333
		<< 0.333 << 0.333 << 0.333 << 0.333 << 0.333 << 0.369 << 0.321 << 0.332 << 0.311 << 0.399
		<< 0.334 << 0.321 << 0.346 << 0.389 << 0.333 << 0.323 << 0.333 << 0.333 << 0.333 << 0.333
		<< 0.333 << 0.369 << 0.321 << 0.332 << 0.311 << 0.399 << 0.334 << 0.321 << 0.346 << 0.389
		<< 0.333 << 0.333 << 0.333 << 0.333 << 0.333 << 0.333 << 0.333 << 0.369 << 0.321 << 0.332
		<< 0.311 << 0.399 << 0.334 << 0.321 << 0.346 << 0.389 << 0.333 << 0.333 << 0.333 << 0.333
		<< 0.333 << 0.343 << 0.333 << 0.319;
	m_dmax = data_One.at(0);
	m_dmin = data_One.at(0);
	m_dsum = 0;
	m_dtheory = 0.35;
	for (int i = 0; i < data_One.size(); i++) {
		if (m_dmin > data_One.at(i)) m_dmin = data_One.at(i);
		if (m_dmax < data_One.at(i)) m_dmax = data_One.at(i);
		m_dsum += data_One.at(i);
	}
	m_dave = m_dsum / data_One.size();
	m_dminoff = (m_dmin - m_dtheory) / m_dtheory * 100;//%
	m_dmaxoff = (m_dmax - m_dtheory) / m_dtheory * 100;
	//data_One.clear();
}
void PRT::on_pB_PrintDirect_clicked()
{
	/*ֱ�Ӵ�ӡ*/

	QPainter painterPixmap(m_prt);
	m_prt->setResolution(QPrinter::HighResolution);
	////�Զ���ֽ�Ŵ�С���ر���Ҫ����ȻԤ��Ч������
	//printer->setPrinterName(m_sName);
	m_prt->setPageSize(QPrinter::A4);
	m_prt->setOrientation(QPrinter::Portrait);

	QPixmap pix = QPixmap(pixWidth, pixHeight);
	//����������ǻ�ģ��ĺ����ɣ��Ͼ���ӡʱ��ģ���
	createPix(&pix);
	pix.save("c:/pt.bmp");
	//����Portrait ����Landscape
	//��ȡ�����ͼƬ

	painterPixmap.begin(m_prt);
	QRect rect = painterPixmap.viewport();
	float x = rect.width()*1.0 / pix.width();
	float y = rect.height()*1.0 / pix.height();
	//����ͼ�񳤿���ԭͼ�Ķ��ٱ�
	painterPixmap.scale(x, y);
	painterPixmap.drawPixmap(0, 0, pix);
	painterPixmap.end();
}
void PRT::on_pB_Print_clicked()
{
	QPrintPreviewDialog preview;// ������ӡԤ���Ի���

	preview.setWindowState(Qt::WindowMaximized);
	/*
	 * QPrintPreviewDialog���ṩ��һ����ӡԤ���Ի������湦�ܱȽ�ȫ��
	 * paintRequested(QPrinter *printer)��ϵͳ�ṩ�ģ�
	 * ��preview.exec()ִ��ʱ���źű�������
	 * drawPic(QPrinter *printer)���Զ���Ĳۺ�����ͼ��Ļ��ƾ�����������
	 */
	connect(&preview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(drawPic(QPrinter*)));
	preview.exec();
}
void PRT::drawPic(QPrinter *printer)
{
	QPainter painterPixmap(printer);
	//QPrinter *printer = new QPrinter(QPrinter::HighResolution);
	printer->setResolution(QPrinter::HighResolution);
	////�Զ���ֽ�Ŵ�С���ر���Ҫ����ȻԤ��Ч������
	//printer->setPrinterName(m_sName);
	printer->setPageSize(QPrinter::A4);
	printer->setOrientation(QPrinter::Portrait);

	QPixmap pix = QPixmap(pixWidth, pixHeight);
	//����������ǻ�ģ��ĺ����ɣ��Ͼ���ӡʱ��ģ���
	createPix(&pix);
	pix.save("c:/pt.bmp");
	//����Portrait ����Landscape
	//��ȡ�����ͼƬ

	//painterPixmap.begin(printer);
	QRect rect = painterPixmap.viewport();
	float x = rect.width()*1.0 / pix.width();
	float y = rect.height()*1.0 / pix.height();
	//����ͼ�񳤿���ԭͼ�Ķ��ٱ�
	painterPixmap.scale(x, y);
	painterPixmap.drawPixmap(0, 0, pix);
	//painterPixmap.end();
}

void PRT::createPix(QPixmap *pix)
{
	QPainter *painter = new QPainter();
	painter->begin(pix);
	painter->setRenderHint(QPainter::Antialiasing, true);
	// ���û�����ɫ�����
	painter->setPen(QPen(QColor(255, 255, 255), 4));
	// ���û�ˢ��ɫ
	painter->setBrush(QColor(255, 255, 255));

	int edgeOffset = 50;
	int innerW = pixWidth - 2 * edgeOffset;
	int innerH = pixHeight - 2 * edgeOffset;
	int rightW = pixWidth - edgeOffset;
	int bottomH = pixHeight - edgeOffset;
	int firstLine = 120;//���������
	int weightTop = firstLine + 60;
	int weightMiddle = firstLine + 2 * 60;
	int weightRowCount = 8;
	int Betweenweight = 400;
	int weightRowAve = 55;
	int weightColumnCount = 10;
	float weightColumnAve = (rightW - Betweenweight)*1.0 / weightColumnCount;//12������
	int weightBottom = weightMiddle + weightRowAve * weightRowCount;


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
	font.setPointSize(20);
	font.setFamily("����");
	font.setItalic(true);
	painter->setFont(font);
	painter->fillRect(rect, QColor(255, 255, 255));
	painter->drawRect(rect);
	//�����ݲ��ֵ�����
	painter->setPen(QPen(QColor(0, 0, 0), 3));
	QVector<QLine> lines;
	lines.append(QLine(QPoint(edgeOffset, edgeOffset), QPoint(rightW, edgeOffset)));//�ϱ�
	lines.append(QLine(QPoint(rightW, edgeOffset), QPoint(rightW, bottomH)));//�ұ�
	lines.append(QLine(QPoint(edgeOffset, bottomH), QPoint(rightW, bottomH)));//�±�
	lines.append(QLine(QPoint(edgeOffset, edgeOffset), QPoint(edgeOffset, bottomH)));//���
	for (int i = 0; i < 3; i++)
	{
		lines.append(QLine(QPoint(edgeOffset, firstLine + i * 60), QPoint(rightW, firstLine + i * 60)));//�����±�//��Ʒ�±�//������Ŀ�±�	
	}
	lines.append(QLine(QPoint(edgeOffset, weightBottom), QPoint(rightW, weightBottom)));//������ϸ�±�

	lines.append(QLine(QPoint(Betweenweight, weightTop), QPoint(Betweenweight, weightBottom)));//����������ÿ������֮��
	lines.append(QLine(QPoint(edgeOffset, pixHeight / 2 - 80), QPoint(rightW, pixHeight / 2 - 80)));//1#������ǩ���ϲ�
	lines.append(QLine(QPoint(edgeOffset, pixHeight / 2), QPoint(rightW, pixHeight / 2)));//1/2#�ָ���
	//lines.append(QLine(QPoint(edgeOffset, bottomH - 80), QPoint(rightW, bottomH -80)));//2#������ǩ���ϲ�

	//������ϵ

	lines.append(QLine(QPoint(basePointX, basePointY), QPoint(basePointX, YTop)));//Y
	lines.append(QLine(QPoint(basePointX - of, YTop + of), QPoint(basePointX, YTop)));
	lines.append(QLine(QPoint(basePointX + of, YTop + of), QPoint(basePointX, YTop)));
	lines.append(QLine(QPoint(basePointX, basePointY), QPoint(XRight, basePointY)));//X
	lines.append(QLine(QPoint(XRight - of, basePointY - of), QPoint(XRight, basePointY)));
	lines.append(QLine(QPoint(XRight - of, basePointY + of), QPoint(XRight, basePointY)));

	painter->drawLines(lines);
	lines.clear();

	painter->setPen(QPen(QColor(0, 0, 0), 1, Qt::DashLine));
	//lines   200,rightW-250 pixHeight/2-825 pixHeight/2-275   250start point
	painter->drawText(basePointX - 40, basePointY, 50, 50, Qt::AlignVCenter, "0");//0
	painter->drawText(actualLeft-25, basePointY, 50, 50, Qt::AlignCenter, "1");//1
	painter->drawText(actualRight-25, basePointY, 50, 50, Qt::AlignCenter, QString::number(data_One.size()));//size()

	painter->drawText(100, actualBottom - 25, 150, 50, Qt::AlignVCenter, QString::number(m_dmin, 'f', 3));//MIN
	painter->drawText(100, actualTop - 25, 150, 50, Qt::AlignVCenter, QString::number(m_dmax, 'f', 3));//MAX
	painter->drawText(100, actualBottom - 25 - (m_dave - m_dmin) / (m_dmax - m_dmin) * YActualLength, 150, 50, Qt::AlignVCenter, QString::number(m_dave, 'f', 3));//AVE
	painter->drawText(100, YTop - 50, 150, 50, Qt::AlignVCenter, QString::fromLocal8Bit("����(g)"));//����
	painter->drawText(XRight, basePointY, 150, 50, Qt::AlignVCenter, QString::fromLocal8Bit("����(��)"));//����

	lines.append(QLine(QPoint(basePointX - 5, actualBottom), QPoint(dotLineRight, basePointY - 50)));//MIN
	lines.append(QLine(QPoint(basePointX - 5, actualTop), QPoint(dotLineRight, actualTop)));//MAX
	lines.append(QLine(QPoint(basePointX - 5, actualBottom - (m_dave - m_dmin) / (m_dmax - m_dmin) * YActualLength), QPoint(dotLineRight, actualBottom - (m_dave - m_dmin) / (m_dmax - m_dmin) * YActualLength)));//AVE

	lines.append(QLine(QPoint(basePointX + 50, basePointY + 5), QPoint(basePointX + 50, dotLineUp)));//1111111111
	lines.append(QLine(QPoint(dotLineRight - 25, basePointY + 5), QPoint(dotLineRight - 25, dotLineUp)));//808080808080

	painter->drawLines(lines);
	lines.clear();

	//����
	painter->setPen(QPen(QColor(0, 0, 0), 1));
	for (int i = 0; i < data_One.size() - 1; i++)
	{
		lines.append(QLine(QPoint(actualLeft + actualWidth*1.0 / (data_One.size() - 1)*i, actualBottom - (data_One.at(i) - m_dmin)*1.0 / (m_dmax - m_dmin) * actualHight), QPoint(actualLeft + actualWidth*1.0 / (data_One.size() - 1)*(i + 1), actualBottom - (data_One.at(i + 1) - m_dmin)*1.0 / (m_dmax - m_dmin) * actualHight)));
	}
	//��ÿ��������
	for (int i = 1; i < weightRowCount; i++)
	{
		lines.append(QLine(QPoint(Betweenweight, weightMiddle + i * weightRowAve), QPoint(rightW, weightMiddle + i * weightRowAve)));
	}
	for (int i = 1; i < weightColumnCount; i++)
	{
		lines.append(QLine(QPoint(Betweenweight + i * weightColumnAve, weightMiddle), QPoint(Betweenweight + i * weightColumnAve, weightBottom)));
	}	
	for (int i = 0; i < weightColumnCount; i++)//order no.
	{
		lines.append(QLine(QPoint(Betweenweight + i * weightColumnAve+50, weightMiddle), QPoint(Betweenweight + i * weightColumnAve+50, weightBottom)));
	}
	painter->drawLines(lines);
	lines.clear();

	painter->setPen(QPen(QColor(0, 0, 0), 3));


	//��һ����
	painter->drawText(0, 0, pixWidth - 1600, 50, Qt::AlignCenter, QString::fromLocal8Bit("��Ȩ����:Dr.Pharm"));// ui->lE_unit->text());//��λ����
	painter->drawText(50, 50, rightW + 1400, 70, Qt::AlignCenter, QString::fromLocal8Bit("�豸�ͺ�/���:1#��"));
	font.setPointSize(30);
	painter->setFont(font);
	painter->drawText(0, 0, pixWidth, 170, Qt::AlignCenter, QString::fromLocal8Bit("��챨��"));// ui->lE_report->text());//��������
	font.setPointSize(20);
	painter->setFont(font);
	//�ڶ�����

	painter->drawText(100, 120, 500, 60, Qt::AlignVCenter, QString::fromLocal8Bit("��Ʒ����:����Ƭ"));// +ui->lE_means->text());
	painter->drawText(800, 120, 500, 60, Qt::AlignVCenter, QString::fromLocal8Bit("��Ʒ���:һ��Ƭ"));// +ui->lE_instrument->text());
	painter->drawText(1500, 120, 500, 60, Qt::AlignVCenter, QString::fromLocal8Bit("��Ʒ����:123456789"));// +ui->lE_instrument->text());
	//��������

	painter->drawText(50, 180, 370, 60, Qt::AlignCenter, QString::fromLocal8Bit("�������"));
	painter->drawText(400, 180, rightW - 400, 60, Qt::AlignCenter, QString::fromLocal8Bit("ÿ������(g)"));
	//���Ĳ��� ����
	
	int num = 0;	
	painter->drawText(70, weightMiddle + weightRowAve * 8.0 / 7 * num++, Betweenweight, weightRowAve*8.0/7, Qt::AlignVCenter, QString::fromLocal8Bit("��  ��(��):") + QString::number(data_One.size()));
	painter->drawText(70, weightMiddle + weightRowAve * 8.0 / 7 * num++, Betweenweight, weightRowAve*8.0 / 7, Qt::AlignVCenter, QString::fromLocal8Bit("��  �� (g):") + QString::number(m_dsum, 'f', 3));
	painter->drawText(70, weightMiddle + weightRowAve * 8.0 / 7 * num++, Betweenweight, weightRowAve*8.0 / 7, Qt::AlignVCenter, QString::fromLocal8Bit("���ֵ (g):") + QString::number(m_dmax, 'f', 3));
	painter->drawText(70, weightMiddle + weightRowAve * 8.0 / 7 * num++, Betweenweight, weightRowAve*8.0 / 7, Qt::AlignVCenter, QString::fromLocal8Bit("��Сֵ (g):") + QString::number(m_dmin, 'f', 3));
	painter->drawText(70, weightMiddle + weightRowAve * 8.0 / 7 * num++, Betweenweight, weightRowAve*8.0 / 7, Qt::AlignVCenter, QString::fromLocal8Bit("ƽ��ֵ (g):") + QString::number(m_dave, 'f', 4));
	painter->drawText(70, weightMiddle + weightRowAve * 8.0 / 7 * num++, Betweenweight, weightRowAve*8.0 / 7, Qt::AlignVCenter, QString::fromLocal8Bit("����ֵ(��):") + QString::number(m_dmaxoff, 'f', 2) + "%");
	painter->drawText(70, weightMiddle + weightRowAve * 8.0 / 7 * num++, Betweenweight, weightRowAve*8.0 / 7, Qt::AlignVCenter, QString::fromLocal8Bit("����ֵ(С):") + QString::number(m_dminoff, 'f', 2) + "%");

	for (int i = 0; i < data_One.size(); i++) {
		painter->drawText(Betweenweight + i % weightColumnCount * weightColumnAve, weightMiddle + i / weightColumnCount % weightRowCount * weightRowAve, 50, weightRowAve, Qt::AlignCenter, QString::number(i + 1));
	}
	for (int i = 0; i < data_One.size(); i++) {
		painter->drawText(Betweenweight + i % weightColumnCount * weightColumnAve+50, weightMiddle + i / weightColumnCount % weightRowCount * weightRowAve, weightColumnAve-50, weightRowAve, Qt::AlignVCenter, QString::number(data_One.at(i), 'f', 3));
	}
	//���岿��
	painter->drawText(50, pixHeight / 2 - 80, 1900, 80, Qt::AlignCenter, QString::fromLocal8Bit("ǩ��:����"));// +ui->lE_code->text());

	painter->drawText(50, pixHeight / 2 - 80, 3000, 80, Qt::AlignCenter, QString::fromLocal8Bit("����:20201210"));// +ui->lE_reportDate->text());
	//painter->drawText(50, bottomH - 80, 1900, 80, Qt::AlignCenter, QString::fromLocal8Bit("ǩ��:����"));// +ui->lE_code->text());

	//painter->drawText(50, bottomH - 80, 3000, 80, Qt::AlignCenter, QString::fromLocal8Bit("����:20201210"));// +ui->lE_reportDate->text());

	painter->end();
}