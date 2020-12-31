#pragma once

#include <QDialog>
#include <QMessageBox>
#include <QDateTime>
#include <iostream> 
#include <malloc.h>

#include "../../Lib/Dongle_API.h"
#pragma comment(lib, "../../LIB/Dongle_s.lib")

#include "Debug/uic/ui_RockeyARM.h"

class RockeyARM : public QDialog
{
	Q_OBJECT
signals:
	void DONGLEERRORCODE(int);//������Ϣ���ͳ�ȥ
public:
	RockeyARM(QWidget *parent = Q_NULLPTR);
	~RockeyARM();

	std::string byteToHexStr(unsigned char byte_arr[], int arr_len);
	QString getCurrentTimeString();
	bool writeTimeData(QString);//���ػ�ʱдϵͳʱ��
	QStringList *getCameraQstringList();
	bool beatHeart();
	bool init();
	void threadProgram();
	static unsigned __stdcall ReceivingThrd(void * pParam);
private:
	Ui::RockeyARM ui;

	DWORD dwRet = 0;
	int nCount = 0;//���ܹ�����
	int nRemainCount = 0;
	DONGLE_HANDLE hDongle = NULL;
	DONGLE_INFO *pDongleInfo = NULL;//���ܹ���Ϣ

	QStringList *m_StringList = nullptr;//camera list
	BYTE  bReadDataSec[40];//�������ܴ�С8k 8192 �˴���Camera����40���ֽ�

	BYTE  bSysTime[8];

	QString strLastTime="";//��������
	QString strCurrentTime = "";//��ǰϵͳ����
	QString strEndTime = "";//������
};
