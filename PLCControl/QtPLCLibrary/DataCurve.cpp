#include "DataCurve.h"
#include <QIcon>

DataCurve::DataCurve(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowIcon(QIcon(AppPath + "/ico/dr.ico"));
}

DataCurve::~DataCurve()
{
}
