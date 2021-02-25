#pragma once

#include <QDialog>
#include <QMessageBox>
#include <QDateTime>
#include <iostream> 
#include <QString>
#include <malloc.h>

#include "../../Lib/Dongle_API.h"
#ifdef _WIN64 
#pragma comment(lib, "../../LIB/x64/Dongle_s.lib")
#else
#pragma comment(lib, "../../LIB/x86/Dongle_s.lib")
#endif

#include "x64/Debug/uic/ui_RockeyARM.h"

class RockeyARM : public QDialog
{
	Q_OBJECT
signals:
	void DONGLEERRORCODE(int);//错误信息发送出去
public:
	RockeyARM(QWidget *parent = Q_NULLPTR);
	~RockeyARM();

	QString byteToHexStr(unsigned char byte_arr[], int arr_len);
	QString getCurrentTimeString();
	bool writeTimeData(QString);//开关机时写系统时间
	QStringList *getCameraQstringList();
	bool beatHeart();
	bool init();
	void threadProgram();
	static unsigned __stdcall ReceivingThrd(void * pParam);
private:
	Ui::RockeyARM ui;

	DWORD dwRet = 0;
	int nCount = 0;//加密狗数量
	int nRemainCount = 0;
	DONGLE_HANDLE hDongle = NULL;
	DONGLE_INFO *pDongleInfo = NULL;//加密狗信息

	QStringList *m_StringList = nullptr;//camera list
	BYTE  bReadDataSec[40];//数据区总大小8k 8192 此处是Camera所在40个字节

	BYTE  bSysTime[8];

	QString strLastTime="";//最新日期
	QString strCurrentTime = "";//当前系统日期
	QString strEndTime = "";//到期日
};
