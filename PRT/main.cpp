#include "PRT.h"
#include <QtWidgets/QApplication>
#include "WindowOut.h"

#include <QStyleFactory>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QSharedMemory mem("PRT");//��ϵͳexe����Ϊ���������干���ڴ�mem
	WindowOut* levelOut = new WindowOut();
	levelOut->setWindowCount(0);//����������������ֹ����

	QApplication::setStyle(QStyleFactory::create("Fusion"));//������
	if (!mem.create(1))//���������ڴ�mem������ù����ڴ��Ѵ��ڣ��򵯳���ʾ�Ի��򣬲��˳�
	{
		levelOut->getString(QString::fromLocal8Bit("ϵͳ������һʵ���������ظ�������"), 2000);
		levelOut->exec();
		return 0;
	}
    PRT w;
    w.show();
    return a.exec();
}
