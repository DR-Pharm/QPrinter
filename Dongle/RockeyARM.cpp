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
		int value = byte_arr[i]; //ֱ�ӽ�unsigned char��ֵ�����͵�ֵ��ϵͳ������ǿ��ת��
		int v1 = value / 16;
		int v2 = value % 16;

		//����ת����ĸ
		if (v1 >= 0 && v1 <= 9)
			hex1 = (char)(48 + v1);
		else
			hex1 = (char)(55 + v1);

		//������ת����ĸ
		if (v2 >= 0 && v2 <= 9)
			hex2 = (char)(48 + v2);
		else
			hex2 = (char)(55 + v2);

		//����ĸ���ӳɴ�
		hexstr = hexstr + hex1 + hex2;
	}
	return hexstr;
}

QString RockeyARM::getCurrentTimeString()
{
	//��ǰʱ��
	QDateTime current_time = QDateTime::currentDateTimeUtc();//��׼ʱ��0
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
		emit DONGLEERRORCODE(4);//���ܹ�д��ʧ��
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
		//��֤������PIN�� ������pin�룺67853F1E5DD17AC1   ǰ��λ���û�PIN��
		char AdminPin[] = "67853F1E5DD17AC1";//������PIN��
		dwRet = Dongle_VerifyPIN(hDongle, FLAG_ADMINPIN, AdminPin, &nRemainCount);
		if (dwRet != DONGLE_SUCCESS)
		{
			emit DONGLEERRORCODE(2);//���ܹ�δ��֤�ɹ�
			return false;
		}

		//��ȡ��ǰ����
		QString strCurrentTime = getCurrentTimeString();

		//��ǰϵͳʱ�䲻�������ϴα����ʱ��
		if (0 < strLastTime.toLongLong() - strCurrentTime.toLongLong())//dongle time should be no larger than systime;
		{
			emit DONGLEERRORCODE(10);//���������иĶ�
			return false;
		}
		strLastTime = strCurrentTime;
		//����ʱ���ȥ���洢��ʱ�䲻��С��0
		if (0 >= strEndTime.toLongLong() - strCurrentTime.toLongLong())
		{
			emit DONGLEERRORCODE(11);//����
			return false;
		}
	}
	return true;
}

bool RockeyARM::init()
{
	//��ȡ���ܹ���Ϣ

	dwRet = Dongle_Enum(NULL, &nCount);//ö����������
	if (dwRet != DONGLE_SUCCESS)
	{
		emit DONGLEERRORCODE(0);//�����ڼ��ܹ�
		return false;
	}

	pDongleInfo = (DONGLE_INFO *)malloc(nCount * sizeof(DONGLE_INFO));
	if (NULL == pDongleInfo)
	{
		emit DONGLEERRORCODE(0);
		return false;
	}

	dwRet = Dongle_Enum(pDongleInfo, &nCount);//��ȡ�������������Ϣ
	if (dwRet != DONGLE_SUCCESS)
	{
		emit DONGLEERRORCODE(0);
		return false;
	}

	//��֤������PIN
	//����
	dwRet = Dongle_Open(&hDongle, 0);
	if (dwRet != DONGLE_SUCCESS)
	{
		emit DONGLEERRORCODE(1);//���ܹ���ʧ��
		return false;
	}
	//......................................................................................
	//��֤������PIN�� ������pin�룺67853F1E5DD17AC1   ǰ��λ���û�PIN��
	char AdminPin[] = "67853F1E5DD17AC1";//������PIN��
	dwRet = Dongle_VerifyPIN(hDongle, FLAG_ADMINPIN, AdminPin, &nRemainCount);
	if (dwRet != DONGLE_SUCCESS)
	{
		emit DONGLEERRORCODE(2);//���ܹ�δ��֤�ɹ�
		return false;
	}

	//�������������������
	memset(bReadDataSec, 0, 16);//�ֽ�
	dwRet = Dongle_ReadData(hDongle, 0x1FF0, bReadDataSec, 16);//�ֽ�
	if (dwRet != DONGLE_SUCCESS)
	{
		emit DONGLEERRORCODE(3);//���ܹ���ȡ����
		return false;
	}

	//��Time�����ֽ����� 16�ֽڶ�Ӧ32��10��������
	std::string strTimeTemp = byteToHexStr(bReadDataSec, 16);//�ֽ�
	QString strTime = QString::fromStdString(strTimeTemp);//string to QString

	//�ϴα����ϵͳʱ�� ����1s ����޴�����Ҫ���� ���ص�ʱ��Ҫ����һ��
	strLastTime = strTime.mid(0, 14);//����λ 

	//��ȡ��ǰ����
	strCurrentTime = getCurrentTimeString();

	//��ǰϵͳʱ�䲻�������ϴα����ʱ��
	if (0 < strLastTime.toLongLong() - strCurrentTime.toLongLong())//dongle time should be no larger than systime;
	{
		emit DONGLEERRORCODE(10);//ϵͳʱ�䱻�Ƿ��Ķ�
		return false;
	}
	strLastTime = strCurrentTime;
	//д���������������û�Ȩ�޿�дǰ4k(0~4095),������������8k��дȨ��
	if(!writeTimeData(strLastTime)) return false;

	//����ʱ�䡣������������������
	strEndTime = strTime.mid(16, 14);//����λ ����ʱ��

	//����ʱ���ȥ���洢��ʱ�䲻��С��0
	if (0 >= strEndTime.toLongLong() - strCurrentTime.toLongLong())
	{
		emit DONGLEERRORCODE(11);//��Ʒ�������ѹ�
		return false;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
		//��������Camera	
	memset(bReadDataSec, 0, 40);//�ֽ� camera����40���ֽڴ�
	dwRet = Dongle_ReadData(hDongle, 0x1000, bReadDataSec, 40);//�ֽ�
	if (dwRet != DONGLE_SUCCESS)
	{
		emit DONGLEERRORCODE(3);//���ܹ���ȡ����
		return false;
	}

	//��camera�����ֽ����� 40�ֽڶ�Ӧ80��10��������
	std::string strCamTemp = byteToHexStr(bReadDataSec, 40);//�ֽ� 
	QString strCam = QString::fromStdString(strCamTemp); //��stringתΪQstring


	m_StringList = new QStringList;
	//��������кŷŵ�QStringList //���listҪreturn���ⲿ
	for (int i = 0; i < 80; i += 8)//����λ
	{
		if (strCam.mid(i, 8) != "00000000") m_StringList->append(strCam.mid(i, 8));//����λ
		else break;
	}
	return true;
}
