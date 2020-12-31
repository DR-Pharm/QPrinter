#include "RockeyARM.h"
#include <process.h>

RockeyARM::RockeyARM(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

RockeyARM::~RockeyARM()
{
	
}
void RockeyARM::threadProgram()
{

	HANDLE hThread;
	unsigned threadID;

	hThread = (HANDLE)_beginthreadex(NULL, 0, &RockeyARM::ReceivingThrd, (LPVOID)this, 0, &threadID);
}
unsigned __stdcall RockeyARM::ReceivingThrd(void * pParam)
{
	//getEvent();
	((RockeyARM *)pParam)->beatHeart();
	return 0;
}
std::string RockeyARM::byteToHexStr(unsigned char byte_arr[], int arr_len)
{
	std::string hexstr;
	for (int i = 0; i < arr_len; i++)
	{
		char hex1;
		char hex2;
		int value = byte_arr[i]; //直接将unsigned char赋值给整型的值，系统会正动强制转换
		int v1 = value / 16;
		int v2 = value % 16;

		//将商转成字母
		if (v1 >= 0 && v1 <= 9)
			hex1 = (char)(48 + v1);
		else
			hex1 = (char)(55 + v1);

		//将余数转成字母
		if (v2 >= 0 && v2 <= 9)
			hex2 = (char)(48 + v2);
		else
			hex2 = (char)(55 + v2);

		//将字母连接成串
		hexstr = hexstr + hex1 + hex2;
	}
	return hexstr;
}

QString RockeyARM::getCurrentTimeString()
{
	//当前时间
	QDateTime current_time = QDateTime::currentDateTimeUtc();//标准时间0
	QString logYear = QString::number(current_time.date().year());
	logYear = logYear.length() < 4 ? ("0" + logYear) : logYear;
	QString logMonth = QString::number(current_time.date().month());
	logMonth = logMonth.length() < 2 ? ("0" + logMonth) : logMonth;
	QString logDay = QString::number(current_time.date().day());
	logDay = logDay.length() < 2 ? ("0" + logDay) : logDay;
	QString logHour = QString::number(current_time.time().hour());
	logHour = logHour.length() < 2 ? ("0" + logHour) : logHour;
	QString logMinute = QString::number(current_time.time().minute());
	logMinute = logMinute.length() < 2 ? ("0" + logMinute) : logMinute;
	QString logsecond = QString::number(current_time.time().second());
	logsecond = logsecond.length() < 2 ? ("0" + logsecond) : logsecond;

	QString strMyTime = logYear + logMonth + logDay + logHour + logMinute + logsecond;
	return strMyTime;
}

bool RockeyARM::writeTimeData(QString strTime)
{
	memset(bSysTime, 0x00, 8);						   
	bSysTime[0] = strTime.mid(0, 2).toInt() / 10 * 16 + strTime.mid(0, 2).toInt() % 10;
	bSysTime[1] = strTime.mid(2, 2).toInt() / 10 * 16 + strTime.mid(2, 2).toInt() % 10;
	bSysTime[2] = strTime.mid(4, 2).toInt() / 10 * 16 + strTime.mid(4, 2).toInt() % 10;
	bSysTime[3] = strTime.mid(6, 2).toInt() / 10 * 16 + strTime.mid(6, 2).toInt() % 10;
	bSysTime[4] = strTime.mid(8, 2).toInt() / 10 * 16 + strTime.mid(8, 2).toInt() % 10;
	bSysTime[5] = strTime.mid(10, 2).toInt() / 10 * 16 + strTime.mid(10, 2).toInt() % 10;
	bSysTime[6] = strTime.mid(12, 2).toInt() / 10 * 16 + strTime.mid(12, 2).toInt() % 10;

	dwRet = Dongle_WriteData(hDongle, 0x1FF0, bSysTime, 8);
	if (dwRet != DONGLE_SUCCESS)
	{
		emit DONGLEERRORCODE(4);//加密狗写入失败
		return 0;
	}
	return 1;
}

QStringList * RockeyARM::getCameraQstringList()
{
	return m_StringList;
}

bool RockeyARM::beatHeart()
{
	while(true)
	{ 
		//验证开发商PIN码 开发商pin码：67853F1E5DD17AC1   前六位是用户PIN码
		char AdminPin[] = "67853F1E5DD17AC1";//开发商PIN码
		dwRet = Dongle_VerifyPIN(hDongle, FLAG_ADMINPIN, AdminPin, &nRemainCount);
		if (dwRet != DONGLE_SUCCESS)
		{
			emit DONGLEERRORCODE(2);//加密狗未验证成功
			return false;
		}

		//获取当前日期
		QString strCurrentTime = getCurrentTimeString();

		//当前系统时间不能早于上次保存的时间
		if (0 < strLastTime.toLongLong() - strCurrentTime.toLongLong())//dongle time should be no larger than systime;
		{
			emit DONGLEERRORCODE(10);//日期数据有改动
			return false;
		}
		strLastTime = strCurrentTime;
		//到期时间减去狗存储的时间不能小于0
		if (0 >= strEndTime.toLongLong() - strCurrentTime.toLongLong())
		{
			emit DONGLEERRORCODE(11);//到期
			return false;
		}
	}
	return true;
}

bool RockeyARM::init()
{
	//获取加密狗信息

	dwRet = Dongle_Enum(NULL, &nCount);//枚举锁的数量
	if (dwRet != DONGLE_SUCCESS)
	{
		emit DONGLEERRORCODE(0);//不存在加密狗
		return false;
	}

	pDongleInfo = (DONGLE_INFO *)malloc(nCount * sizeof(DONGLE_INFO));
	if (NULL == pDongleInfo)
	{
		emit DONGLEERRORCODE(0);
		return false;
	}

	dwRet = Dongle_Enum(pDongleInfo, &nCount);//获取加密锁的相关信息
	if (dwRet != DONGLE_SUCCESS)
	{
		emit DONGLEERRORCODE(0);
		return false;
	}

	//验证开发商PIN
	//打开锁
	dwRet = Dongle_Open(&hDongle, 0);
	if (dwRet != DONGLE_SUCCESS)
	{
		emit DONGLEERRORCODE(1);//加密狗打开失败
		return false;
	}
	//......................................................................................
	//验证开发商PIN码 开发商pin码：67853F1E5DD17AC1   前六位是用户PIN码
	char AdminPin[] = "67853F1E5DD17AC1";//开发商PIN码
	dwRet = Dongle_VerifyPIN(hDongle, FLAG_ADMINPIN, AdminPin, &nRemainCount);
	if (dwRet != DONGLE_SUCCESS)
	{
		emit DONGLEERRORCODE(2);//加密狗未验证成功
		return false;
	}

	//读数据区最近更新日期
	memset(bReadDataSec, 0, 16);//字节
	dwRet = Dongle_ReadData(hDongle, 0x1FF0, bReadDataSec, 16);//字节
	if (dwRet != DONGLE_SUCCESS)
	{
		emit DONGLEERRORCODE(3);//加密狗读取错误
		return false;
	}

	//读Time所在字节内容 16字节对应32个10进制数字
	std::string strTimeTemp = byteToHexStr(bReadDataSec, 16);//字节
	QString strTime = QString::fromStdString(strTimeTemp);//string to QString

	//上次保存的系统时间 精度1s 如果无错误需要保存 开关的时候都要保存一次
	strLastTime = strTime.mid(0, 14);//数字位 

	//获取当前日期
	strCurrentTime = getCurrentTimeString();

	//当前系统时间不能早于上次保存的时间
	if (0 < strLastTime.toLongLong() - strCurrentTime.toLongLong())//dongle time should be no larger than systime;
	{
		emit DONGLEERRORCODE(10);//系统时间被非法改动
		return false;
	}
	strLastTime = strCurrentTime;
	//写数据区，匿名和用户权限可写前4k(0~4095),开发商有所有8k的写权限
	if(!writeTimeData(strLastTime)) return false;

	//到期时间。。。。。。。。。。
	strEndTime = strTime.mid(16, 14);//数字位 到期时间

	//到期时间减去狗存储的时间不能小于0
	if (0 >= strEndTime.toLongLong() - strCurrentTime.toLongLong())
	{
		emit DONGLEERRORCODE(11);//产品试用期已过
		return false;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
		//读数据区Camera	
	memset(bReadDataSec, 0, 40);//字节 camera所在40个字节处
	dwRet = Dongle_ReadData(hDongle, 0x1000, bReadDataSec, 40);//字节
	if (dwRet != DONGLE_SUCCESS)
	{
		emit DONGLEERRORCODE(3);//加密狗读取错误
		return false;
	}

	//读camera所在字节内容 40字节对应80个10进制数字
	std::string strCamTemp = byteToHexStr(bReadDataSec, 40);//字节 
	QString strCam = QString::fromStdString(strCamTemp); //将string转为Qstring


	m_StringList = new QStringList;
	//将相机序列号放到QStringList //这个list要return到外部
	for (int i = 0; i < 80; i += 8)//数字位
	{
		if (strCam.mid(i, 8) != "00000000") m_StringList->append(strCam.mid(i, 8));//数字位
		else break;
	}
	return true;
}
