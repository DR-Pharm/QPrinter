#include "DataCurve.h"
#include <QIcon>

DataCurve::DataCurve(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowIcon(QIcon(AppPath + "/ico/dr.ico"));
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
	setWindowTitle(QString::fromLocal8Bit("���������ϸ��"));

	//m_dtDlg->setFixedSize(QSize(797, 550));
}

DataCurve::~DataCurve()
{
}
