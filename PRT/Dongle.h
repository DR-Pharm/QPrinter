#pragma once

#include <QStringList>
#include <process.h>
#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(DONGLE_LIB)
#  define DONGLE_EXPORT Q_DECL_EXPORT
# else
#  define DONGLE_EXPORT Q_DECL_IMPORT
# endif
#else
# define DONGLE_EXPORT
#endif

class DONGLE_EXPORT Dongle
{
public:
    Dongle();
	void *CameraQstringListInDongle();
	void setTimeData();
	bool initDongle();
	void *get_m_RockeyARM();
	void threadRun();
private:
	void *m_RockeyARM = nullptr;
	QStringList* m_CameraQstringList= new QStringList;
};
