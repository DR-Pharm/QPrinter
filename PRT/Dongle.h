#pragma once

#include "dongle_global.h"
#include "RockeyARM.h"
#include <QStringList>

class DONGLE_EXPORT Dongle
{
public:
    Dongle();
	void *CameraQstringListInDongle();
	void setTimeData();
	bool initDongle();
	RockeyARM *get_m_RockeyARM();
	void threadRun();
private:
	RockeyARM *m_RockeyARM = nullptr;
	QStringList* m_CameraQstringList= new QStringList;
};
