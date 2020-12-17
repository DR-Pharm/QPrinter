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
	int innerWidth = pixWidth - edgeOffset;
	int innerHeight = pixHeight - edgeOffset;

	QRect rect(0, 0, pixWidth, pixHeight);
	//����ͼ���û�ˢ�׵�
	painter->fillRect(rect, QColor(255, 255, 255));
	painter->drawRect(rect);
	//�����ݲ��ֵ�����
	painter->setPen(QPen(QColor(0, 0, 0), 3));
	QVector<QLine> lines;
	lines.append(QLine(QPoint(edgeOffset, edgeOffset), QPoint(innerWidth, edgeOffset)));//�ϱ�
	lines.append(QLine(QPoint(innerWidth, edgeOffset), QPoint(innerWidth, innerHeight)));//�ұ�
	lines.append(QLine(QPoint(edgeOffset, innerHeight), QPoint(innerWidth, innerHeight)));//�±�
	lines.append(QLine(QPoint(edgeOffset, edgeOffset), QPoint(edgeOffset, innerHeight)));//���
	lines.append(QLine(QPoint(edgeOffset, 120), QPoint(innerWidth, 120)));//�����±�
	lines.append(QLine(QPoint(edgeOffset, 180), QPoint(innerWidth, 180)));//��Ʒ�±�
	lines.append(QLine(QPoint(edgeOffset, 240), QPoint(innerWidth, 240)));//������Ŀ�±�
	lines.append(QLine(QPoint(edgeOffset, 515), QPoint(innerWidth, 515)));//������ϸ�±�

	lines.append(QLine(QPoint(400, 180), QPoint(400, 515)));//����������ÿ������֮��
	lines.append(QLine(QPoint(edgeOffset, (innerHeight - 100)/2-80), QPoint(innerWidth, (innerHeight - 100) / 2 - 80)));//2#������ǩ���ϲ�
	lines.append(QLine(QPoint(edgeOffset, (innerHeight - 100) / 2), QPoint(innerWidth, (innerHeight - 100) / 2)));//1/2#�ָ���
	lines.append(QLine(QPoint(edgeOffset, innerHeight - 80), QPoint(innerWidth, innerHeight - 80)));//2#������ǩ���ϲ�

	//������ϵ
	int of = 10;
	lines.append(QLine(QPoint(200, 600), QPoint(200, (innerHeight - 100) / 2 - 200)));//Y
	lines.append(QLine(QPoint(200-of, 600+of), QPoint(200, 600)));
	lines.append(QLine(QPoint(200+of, 600+of), QPoint(200, 600)));
	lines.append(QLine(QPoint(200, (innerHeight - 100) / 2 - 200), QPoint(innerWidth-150, (innerHeight - 100) / 2 - 200)));//X
	lines.append(QLine(QPoint(innerWidth - 150 - of, (innerHeight - 100) / 2 - 200 - of), QPoint(innerWidth - 150, (innerHeight - 100) / 2 - 200)));
	lines.append(QLine(QPoint(innerWidth - 150 - of, (innerHeight - 100) / 2 - 200 + of), QPoint(innerWidth - 150, (innerHeight - 100) / 2 - 200)));

	painter->drawLines(lines);
	lines.clear();
	//��ÿ��������
	painter->setPen(QPen(QColor(0, 0, 0), 1));
	for (int i = 1; i < 5; i++)
	{
		lines.append(QLine(QPoint(400, 240 + i * 55), QPoint(innerWidth, 240 + i * 55)));
	}
	for (int i = 1; i < 16; i++)
	{
		lines.append(QLine(QPoint(400 + i * 103.125, 240), QPoint(400 + i * 103.125, 515)));
	}
	painter->drawLines(lines);
	lines.clear();

	painter->setPen(QPen(QColor(0, 0, 0), 3));

	QFont font;
	font.setPointSize(20);
	font.setFamily("����");


	font.setItalic(true);
	painter->setFont(font);
	//��һ����
	painter->drawText(0, 0, pixWidth - 1600, 50, Qt::AlignCenter, QString::fromLocal8Bit("��Ȩ����:Dr.Pharm"));// ui->lE_unit->text());//��λ����
	//painter->drawText(0, 0, pixWidth+1400, 50, Qt::AlignCenter, "No:");	
	//painter->drawText(0, 0, pixWidth + 1100, 50, Qt::AlignCenter, QString::fromLocal8Bit("�豸�ͺ�/���:"));
	painter->drawText(50, 50, innerWidth + 1400, 70, Qt::AlignCenter, QString::fromLocal8Bit("�豸�ͺ�/���:1#��"));
	font.setPointSize(30);
	painter->setFont(font);
	painter->drawText(0, 0, pixWidth, 170, Qt::AlignCenter, QString::fromLocal8Bit("��챨��"));// ui->lE_report->text());//��������
	font.setPointSize(20);
	painter->setFont(font);
	//�ڶ�����

	painter->drawText(50, 120, 200, 60, Qt::AlignCenter, QString::fromLocal8Bit("��Ʒ����:"));// +ui->lE_means->text());
	painter->drawText(50, 120, 1300, 60, Qt::AlignCenter, QString::fromLocal8Bit("��Ʒ���:"));// +ui->lE_instrument->text());
	painter->drawText(50, 120, 2400, 60, Qt::AlignCenter, QString::fromLocal8Bit("��Ʒ����:"));// +ui->lE_instrument->text());
	//��������

	painter->drawText(50, 180, 370, 60, Qt::AlignCenter, QString::fromLocal8Bit("��������"));
	painter->drawText(400, 180, innerWidth - 400, 60, Qt::AlignCenter, QString::fromLocal8Bit("ÿ������(g)"));
	//���Ĳ���
	painter->drawText(70, 240, 400, 60, Qt::AlignVCenter, QString::fromLocal8Bit("���ֵ(g):") + QString::number(m_dmax, 'f', 3));
	painter->drawText(70, 295, 400, 60, Qt::AlignVCenter, QString::fromLocal8Bit("��Сֵ(g):") + QString::number(m_dmin, 'f', 3));
	painter->drawText(70, 350, 400, 60, Qt::AlignVCenter, QString::fromLocal8Bit("ƽ��ֵ(g):") + QString::number(m_dave, 'f', 4));
	painter->drawText(70, 405, 400, 60, Qt::AlignVCenter, QString::fromLocal8Bit("����ֵ(��):") + QString::number(m_dmaxoff, 'f', 2) + "%");
	painter->drawText(70, 455, 400, 60, Qt::AlignVCenter, QString::fromLocal8Bit("����ֵ(С):") + QString::number(m_dminoff, 'f', 2) + "%");

	for (int i = 0; i < data_One.size(); i++) {
		painter->drawText(400+i%16* 103.125, 240+i/16%5*55, 103.125, 55, Qt::AlignCenter, QString::number(data_One.at(i), 'f', 3));
	}
	//���岿��
	painter->drawText(50, (innerHeight - 100) / 2 - 80, 1900, 80, Qt::AlignCenter, QString::fromLocal8Bit("ǩ��:"));// +ui->lE_code->text());

	painter->drawText(50, (innerHeight - 100) / 2 - 80, 3000, 80, Qt::AlignCenter, QString::fromLocal8Bit("����:"));// +ui->lE_reportDate->text());
	painter->drawText(50, innerHeight - 80, 1900, 80, Qt::AlignCenter, QString::fromLocal8Bit("ǩ��:"));// +ui->lE_code->text());

	painter->drawText(50, innerHeight - 80, 3000, 80, Qt::AlignCenter, QString::fromLocal8Bit("����:"));// +ui->lE_reportDate->text());

	painter->end();
}