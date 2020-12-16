#include "PRT.h"

PRT::PRT(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this); 
	QPrinterInfo info;
	m_sName = info.defaultPrinterName(); // 默认打印机名字
	ui.lb_PrinterName->setText(QString::fromLocal8Bit("当前连接打印机：")+ m_sName);

	m_prt = new QPrinter();
	m_prt->setPrinterName(m_sName);

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
	connect(&preview, SIGNAL(paintRequested(QPrinter*)),this,SLOT(drawPic(QPrinter*)));
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

	QPixmap pix= QPixmap(pixWidth, pixHeight);
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

	QRect rect(0, 0, pixWidth, pixHeight);
	//整张图设置画刷白底
	painter->fillRect(rect, QColor(255, 255, 255));
	painter->drawRect(rect);
	//画数据部分的线条
	painter->setPen(QPen(QColor(0, 0, 0), 3));
	QVector<QLine> lines;
	int edgeOffset = 50;
	lines.append(QLine(QPoint(edgeOffset, edgeOffset), QPoint(pixWidth-edgeOffset, edgeOffset)));//上边
	lines.append(QLine(QPoint(pixWidth-edgeOffset, edgeOffset), QPoint(pixWidth-edgeOffset, pixHeight-edgeOffset)));//右边
	lines.append(QLine(QPoint(edgeOffset, pixHeight-edgeOffset), QPoint(pixWidth - edgeOffset, pixHeight - edgeOffset)));//下边
	lines.append(QLine(QPoint(edgeOffset, edgeOffset), QPoint(edgeOffset, pixHeight - edgeOffset)));//左边
	lines.append(QLine(QPoint(edgeOffset, 120), QPoint(pixWidth - edgeOffset, 120)));//名称下边
	lines.append(QLine(QPoint(edgeOffset, 180), QPoint(pixWidth - edgeOffset, 180)));//信息下边
	lines.append(QLine(QPoint(edgeOffset, 200), QPoint(pixWidth - edgeOffset, 200)));//条目下边
	lines.append(QLine(QPoint(edgeOffset, 490), QPoint(pixWidth - edgeOffset, 490)));//数据下边
	lines.append(QLine(QPoint(120, 180), QPoint(120, 200)));//类型分割边
	lines.append(QLine(QPoint(190, 180), QPoint(190, 200)));//类型分割边
	lines.append(QLine(QPoint(260, 180), QPoint(260, 200)));//类型分割边
	lines.append(QLine(QPoint(330, 180), QPoint(330, 200)));//类型分割边
	lines.append(QLine(QPoint(400, 180), QPoint(400, 490)));//结果和曲线分割边
	painter->drawLines(lines);
	QFont font;
	font.setPointSize(40);
	font.setFamily("宋体");
	

	font.setItalic(true);
	painter->setFont(font);
	//第一部分
	painter->drawText(50, 50, 700, 40, Qt::AlignCenter, "Dr.Pharm");// ui->lE_unit->text());//单位名称
	painter->drawText(QPoint(650, 110), "No:");
	font.setPointSize(20);
	painter->setFont(font);
	painter->drawText(50, 80, 700, 40, Qt::AlignCenter, QString::fromLocal8Bit("抽检报告"));// ui->lE_report->text());//报告名称
	font.setPointSize(20);
	painter->setFont(font);
	//第二部分
	painter->drawText(50, 120, 700, 60, Qt::AlignVCenter, QString::fromLocal8Bit("样本ID： ") + QString("11111111"));
	painter->drawText(210, 120, 700, 60, Qt::AlignVCenter, QString::fromLocal8Bit("标本类型： ") + QString("ABC"));
	painter->drawText(370, 120, 700, 60, Qt::AlignVCenter, QString::fromLocal8Bit("检测方法： "));// +ui->lE_means->text());
	painter->drawText(600, 120, 700, 60, Qt::AlignVCenter, QString::fromLocal8Bit("仪器： "));// +ui->lE_instrument->text());
	//第三部分
	painter->drawText(50, 180, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("序号"));
	painter->drawText(120, 180, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("检测项目"));
	painter->drawText(190, 180, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("Ct"));
	painter->drawText(260, 180, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("检测下限"));
	painter->drawText(330, 180, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("结果"));
	//第四部分
	painter->drawText(50, 210, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("1"));
	painter->drawText(120, 210, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("我"));
	painter->drawText(190, 210, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("真的"));
	painter->drawText(260, 210, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("不知道"));
	painter->drawText(330, 210, 70, 20, Qt::AlignCenter, QString::fromLocal8Bit("写啥"));
	//第五部分
	painter->drawText(50, 490, 700, 30, Qt::AlignVCenter, QString::fromLocal8Bit("送检者： "));// +ui->lE_inspect->text());
	painter->drawText(230, 490, 700, 30, Qt::AlignVCenter, QString::fromLocal8Bit("代码： "));// +ui->lE_code->text());
	painter->drawText(410, 490, 700, 30, Qt::AlignVCenter, QString::fromLocal8Bit("检验者： "));// +ui->lE_detection->text());
	painter->drawText(590, 490, 700, 30, Qt::AlignVCenter, QString::fromLocal8Bit("审核者： "));// +ui->lE_audit->text());
	painter->drawText(50, 520, 700, 30, Qt::AlignVCenter, QString::fromLocal8Bit("送检日期： "));// +ui->lE_inspectDate->text());
	painter->drawText(410, 520, 700, 30, Qt::AlignVCenter, QString::fromLocal8Bit("报告日期： "));// +ui->lE_reportDate->text());

	painter->end();
}