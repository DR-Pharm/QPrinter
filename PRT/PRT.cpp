#include "PRT.h"

PRT::PRT(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this); 
	QPrinterInfo info;
	m_sName = info.defaultPrinterName(); // Ĭ�ϴ�ӡ������
	ui.lb_PrinterName->setText(QString::fromLocal8Bit("��ǰ���Ӵ�ӡ����")+ m_sName);

	m_prt = new QPrinter();
	m_prt->setPrinterName(m_sName);

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
	connect(&preview, SIGNAL(paintRequested(QPrinter*)),this,SLOT(drawPic(QPrinter*)));
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

	QPixmap pix= QPixmap(pixWidth, pixHeight);
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
	int innerHeight= pixHeight - edgeOffset;

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
	lines.append(QLine(QPoint(edgeOffset, 505), QPoint(innerWidth, 505)));//������ϸ�±�

	lines.append(QLine(QPoint(420, 180), QPoint(420, 505)));//����������ÿ������֮��
	lines.append(QLine(QPoint(edgeOffset, innerHeight-80), QPoint(innerWidth, innerHeight-80)));//������ǩ���ϲ�
	painter->drawLines(lines);
	QFont font;
	font.setPointSize(20);
	font.setFamily("����");
	

	font.setItalic(true);
	painter->setFont(font);
	//��һ����
	painter->drawText(0,0, pixWidth-1600,50,Qt::AlignCenter, QString::fromLocal8Bit("��Ȩ����:Dr.Pharm"));// ui->lE_unit->text());//��λ����
	//painter->drawText(0, 0, pixWidth+1400, 50, Qt::AlignCenter, "No:");	
	//painter->drawText(0, 0, pixWidth + 1100, 50, Qt::AlignCenter, QString::fromLocal8Bit("�豸�ͺ�/���:"));
	painter->drawText(50, 50, innerWidth+1000, 70, Qt::AlignCenter, QString::fromLocal8Bit("�豸�ͺ�/���:"));
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
	painter->drawText(420, 180, innerWidth-420, 60, Qt::AlignCenter, QString::fromLocal8Bit("ÿ������(g)"));
	//���Ĳ���
	painter->drawText(50, 240, 200, 60, Qt::AlignCenter, QString::fromLocal8Bit("���ֵ(g):"));
	painter->drawText(50, 295, 200, 60, Qt::AlignCenter, QString::fromLocal8Bit("��Сֵ(g):"));
	painter->drawText(50, 345, 200, 60, Qt::AlignCenter, QString::fromLocal8Bit("ƽ��ֵ(g):"));
	painter->drawText(50, 395, 200, 60, Qt::AlignCenter, QString::fromLocal8Bit("����ֵ(��):"));
	painter->drawText(50, 445, 200, 60, Qt::AlignCenter, QString::fromLocal8Bit("����ֵ(С):"));
	//painter->drawText(120, 210, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("��"));
	//painter->drawText(190, 210, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("���"));
	//painter->drawText(260, 210, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("��֪��"));
	//painter->drawText(330, 210, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("дɶ"));
	//���岿��
	painter->drawText(50, innerHeight-80, 1000, 80, Qt::AlignCenter, QString::fromLocal8Bit("������:"));// +ui->lE_inspect->text());
	painter->drawText(50, innerHeight - 80, 1900, 80, Qt::AlignCenter, QString::fromLocal8Bit("������:"));// +ui->lE_code->text());

	painter->drawText(50, innerHeight - 80, 3000, 80, Qt::AlignCenter, QString::fromLocal8Bit("��������:"));// +ui->lE_reportDate->text());

	painter->end();
}