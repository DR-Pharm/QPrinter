#pragma once

#include <QDialog>
#include "ui_DataCurve.h"

class DataCurve : public QDialog
{
	Q_OBJECT

public:
	DataCurve(QWidget *parent = Q_NULLPTR);
	~DataCurve();

private:
	Ui::DataCurve ui;
	QString AppPath = qApp->applicationDirPath();
};
