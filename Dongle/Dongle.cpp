#include "Dongle.h"

Dongle::Dongle()
{
	m_RockeyARM = new RockeyARM();
}

void * Dongle::CameraQstringListInDongle()
{
	m_CameraQstringList = m_RockeyARM->getCameraQstringList();
	return m_CameraQstringList;
}

void Dongle::setTimeData()
{
	QString strCurrentTime = m_RockeyARM->getCurrentTimeString();
	m_RockeyARM->writeTimeData(strCurrentTime);
}

bool Dongle::initDongle()
{
	return m_RockeyARM->init();
}

RockeyARM *Dongle::get_m_RockeyARM()
{
	return m_RockeyARM;
}

void Dongle::threadRun()
{
	m_RockeyARM->threadProgram();
}
