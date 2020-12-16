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

	QRect rect(0, 0, pixWidth, pixHeight);
	//����ͼ���û�ˢ�׵�
	painter->fillRect(rect, QColor(255, 255, 255));
	painter->drawRect(rect);
	//�����ݲ��ֵ�����
	painter->setPen(QPen(QColor(0, 0, 0), 3));
	QVector<QLine> lines;
	int edgeOffset = 50;
	lines.append(QLine(QPoint(edgeOffset, edgeOffset), QPoint(pixWidth-edgeOffset, edgeOffset)));//�ϱ�
	lines.append(QLine(QPoint(pixWidth-edgeOffset, edgeOffset), QPoint(pixWidth-edgeOffset, pixHeight-edgeOffset)));//�ұ�
	lines.append(QLine(QPoint(edgeOffset, pixHeight-edgeOffset), QPoint(pixWidth - edgeOffset, pixHeight - edgeOffset)));//�±�
	lines.append(QLine(QPoint(edgeOffset, edgeOffset), QPoint(edgeOffset, pixHeight - edgeOffset)));//���
	lines.append(QLine(QPoint(edgeOffset, 120), QPoint(pixWidth - edgeOffset, 120)));//�����±�
	lines.append(QLine(QPoint(edgeOffset, 180), QPoint(pixWidth - edgeOffset, 180)));//��Ϣ�±�
	lines.append(QLine(QPoint(edgeOffset, 200), QPoint(pixWidth - edgeOffset, 200)));//��Ŀ�±�
	lines.append(QLine(QPoint(edgeOffset, 490), QPoint(pixWidth - edgeOffset, 490)));//�����±�
	lines.append(QLine(QPoint(120, 180), QPoint(120, 200)));//���ͷָ��
	lines.append(QLine(QPoint(190, 180), QPoint(190, 200)));//���ͷָ��
	lines.append(QLine(QPoint(260, 180), QPoint(260, 200)));//���ͷָ��
	lines.append(QLine(QPoint(330, 180), QPoint(330, 200)));//���ͷָ��
	lines.append(QLine(QPoint(400, 180), QPoint(400, 490)));//��������߷ָ��
	painter->drawLines(lines);
	QFont font;
	font.setPointSize(40);
	font.setFamily("����");
	

	font.setItalic(true);
	painter->setFont(font);
	//��һ����
	painter->drawText(50, 50, 700, 40, Qt::AlignCenter, "Dr.Pharm");// ui->lE_unit->text());//��λ����
	painter->drawText(QPoint(650, 110), "No:");
	font.setPointSize(20);
	painter->setFont(font);
	painter->drawText(50, 80, 700, 40, Qt::AlignCenter, QString::fromLocal8Bit("��챨��"));// ui->lE_report->text());//��������
	font.setPointSize(20);
	painter->setFont(font);
	//�ڶ�����
	painter->drawText(50, 120, 700, 60, Qt::AlignVCenter, QString::fromLocal8Bit("����ID�� ") + QString("11111111"));
	painter->drawText(210, 120, 700, 60, Qt::AlignVCenter, QString::fromLocal8Bit("�걾���ͣ� ") + QString("ABC"));
	painter->drawText(370, 120, 700, 60, Qt::AlignVCenter, QString::fromLocal8Bit("��ⷽ���� "));// +ui->lE_means->text());
	painter->drawText(600, 120, 700, 60, Qt::AlignVCenter, QString::fromLocal8Bit("������ "));// +ui->lE_instrument->text());
	//��������
	painter->drawText(50, 180, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("���"));
	painter->drawText(120, 180, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("�����Ŀ"));
	painter->drawText(190, 180, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("Ct"));
	painter->drawText(260, 180, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("�������"));
	painter->drawText(330, 180, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("���"));
	//���Ĳ���
	painter->drawText(50, 210, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("1"));
	painter->drawText(120, 210, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("��"));
	painter->drawText(190, 210, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("���"));
	painter->drawText(260, 210, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("��֪��"));
	painter->drawText(330, 210, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("дɶ"));
	//���岿��
	painter->drawText(50, 490, 700, 30, Qt::AlignVCenter, QString::fromLocal8Bit("�ͼ��ߣ� "));// +ui->lE_inspect->text());
	painter->drawText(230, 490, 700, 30, Qt::AlignVCenter, QString::fromLocal8Bit("���룺 "));// +ui->lE_code->text());
	painter->drawText(410, 490, 700, 30, Qt::AlignVCenter, QString::fromLocal8Bit("�����ߣ� "));// +ui->lE_detection->text());
	painter->drawText(590, 490, 700, 30, Qt::AlignVCenter, QString::fromLocal8Bit("����ߣ� "));// +ui->lE_audit->text());
	painter->drawText(50, 520, 700, 30, Qt::AlignVCenter, QString::fromLocal8Bit("�ͼ����ڣ� "));// +ui->lE_inspectDate->text());
	painter->drawText(410, 520, 700, 30, Qt::AlignVCenter, QString::fromLocal8Bit("�������ڣ� "));// +ui->lE_reportDate->text());

	painter->end();
}